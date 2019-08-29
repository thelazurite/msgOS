/*
 * The MIT License
 *
 * Copyright 2019 dylan.eddies.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   main.c
 * Author: dylan.eddies
     *
 * Created on 13 August 2019, 20:45
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "util/linklist.h"
#include "util/stringtools.h"
#include "util/calc_crc.h"
#include "typedefs.h"

static uint8_t currFormId = 0x00;  

static FILE* fi;
static int lookup = 0;
static item_char * data;

static form_t * forms; 
static form_t * currForm;

static token_t types[9] = {
    { "FORM",       0x00 },
    { "FUNC",       0x01 },
    { "VAR",        0x02 },
    { "U08",        0x10 },
    { "I32",        0x11 },
    { "I64",        0x12 },
    { "D32",        0x13 },
    { "BLOB",       0x20 },
    { "NIL",        0xFF }
};

static token_t tokens[28] = {
    { "map",        0x00 },
    { "reduce",     0x01 },
    { "apply",      0x02 },
    { "if",         0x03 },
    { "when",       0x04 },
    { "cat",        0x05 },
    { "fn",         0x06 },
    { "=",          0x0A },
    { "+",          0x0B },
    { "-",          0x0C },
    { "*",          0x0D },
    { "/",          0x0E },
    { "//",         0x0F },
    { "%",          0x10 },
    { "~",          0x11 },
    { "&",          0x12 },
    { "|",          0x13 },
    { "^",          0x14 },
    { "<<",         0x15 },
    { ">>",         0x16 },
    { "const",      0x3F },
    { "let",        0x40 },
    { "var",        0x41 },
    { "set",        0x42 },
    { "reset",      0x43 },
    { "msg!" ,      0x80 },
    { "hook!" ,     0x81 },
    { "call",       0xFF }
};

void create_next_form(int * indent){
    // initialises the new form.
    printf("\ncreating a form\n");
    currForm->next = malloc(sizeof(form_t));
    currForm->next->prev = currForm;
    currForm->next->type = &types[0];
    printf("%s", currForm->next->type->token);
    currForm->next->id = &currFormId;
    currForm->next->formName = malloc(sizeof(char*));
    currForm->next->params = malloc(sizeof(param_t));
    
    // order the children. 
    if(indent > 0) {
        // check if this is the first child.
        if(currForm->childForm == NULL){
            printf("hit");

            currForm->childForm = malloc(sizeof(child_t));
            currForm->childForm->prev = NULL;
            currForm->childForm->id = malloc(sizeof(uint8_t));
            memcpy(currForm->childForm->id, currForm->next->id, sizeof(uint8_t));
        } else { 
            child_t* currChild = currForm->childForm;
            
            while(currChild->next != NULL){
                currChild = currChild->next;
            }
            
            currChild->next = malloc(sizeof(child_t));
            currChild->next->prev = currChild;
            memcpy(currChild->next->id, currForm->next->id, sizeof(uint8_t));
        }
    }
    
    currForm = currForm->next;
    
    ++currFormId;
}

int form_representation(){
    bool read = true;
    item_char* iter = data;
    
    bool lookForm = false;
    bool lookParam = false;
    int *  indent = 0; 

    item_t* idt;
    bool first = true;
    
    char* ch = malloc(sizeof(char*));
    
    forms = malloc(sizeof(form_t));
    forms->prev = NULL;
    forms->type = &types[0];
    printf("%s", forms->type->token);
    forms->id = &currFormId;
    forms->formName = malloc(sizeof(char*));
    forms->params = malloc(sizeof(param_t));
    ++currFormId;
    
    currForm = forms;
    param_t * param = forms->params;
    
    while(read == true) {
        bool startForm = strcmp("(", iter->value) == 0;
        bool endForm = strcmp(")", iter->value) == 0;
        bool whiteSpace = strcmp(" ", iter->value) == 0 || strcmp("\n", iter->value) == 0;

        if(startForm){
           lookForm = true;
           lookParam = false;
           
           if(!first){
               if(currForm->next == NULL){
                  create_next_form(indent);
               } else {
                   
                   // add the parent to return to (FILO)
                   if(idt == NULL){
                       idt = malloc(sizeof(item_t));
                       memcpy(idt->value, currForm->id, sizeof(uint8_t));
                       idt->next = NULL;
                       idt->previous = NULL;
                   }
                   else {
                       add_t(idt, currForm->id);
                   }
                   while(currForm->next != NULL){
                       currForm = currForm->next;
                   }
                   create_next_form(indent);
               }
               printf("form created");
               param = currForm->params;
           } else {
              first = false;
           }
           ++indent;
        }
        if(endForm){
            --indent;

            if(indent > 0)
                lookParam = true;
            
            else if(indent < 0) {
                printf("Unexpected closure");
                return -1;
            }
        }
        
        if(iter->next == NULL){
            read = false;
        }
        
        if(lookForm && !startForm){
            if(!whiteSpace){
                 ch = realloc(ch, sizeof(ch)+1);
                 sprintf(ch, "%s%s", ch, iter->value);
            }
            else if(whiteSpace || endForm) { 
                lookForm = false;
                lookParam = true;
                bool found = false;
                for(int i = 0; i < 26; i++){
                    if(strcmp(tokens[i].token, ch) == 0){
                        printf("\n Func Found: %s %hhu %hhu \n ", tokens[i].token, tokens[i].code, currFormId-1);
                        printf("%s", ch);
                        strcpy(currForm->formName, tokens[i].token);
                        found = true;
                    }
                }
                if(found == false){
                    printf("\nCouldn't find %s \n", ch);
                    return -1;
                }
                
                ch = malloc(sizeof(char*));
            }
        } else if(lookParam) {
            // reading a parameter that isn't const text.
            bool rdp = !whiteSpace && !endForm && !startForm;
            // double quote
            bool dbq = strcmp("\"",iter->value) == 0;
            // single quote
            bool sgq = strcmp("'", iter->value) == 0;
                     
            if(dbq || sgq){ 
                bool rdc = true;
                item_char* cCurr = iter->next;
                ch = realloc(ch, sizeof(ch)+1);
                sprintf(ch, "%s%s", ch, iter->value);
                while(rdc) {
                    // if the const value uses single or double quote and the next value is expected to be the ending quote
                    // check if the escape character is being used.
                    bool cdbq = strcmp("\"",cCurr->value) == 0;
                    bool csgq = strcmp("'", cCurr->value) == 0;
                    
                    if((dbq && cdbq) || (sgq && csgq)) {
                        if(strcmp("\\",cCurr->previous->value) !=0){
                            rdc = false;
                        }
                    }
                    else if(cCurr->next == NULL) {
                        printf("\nE: Const value was not closed\n");
                        free(ch);
                        return -1;
                    }
                    ch = realloc(ch, sizeof(ch)+(sizeof(char*)*1));
                    sprintf(ch, "%s%s", ch, cCurr->value);
                    cCurr = cCurr->next;
                }
                iter = cCurr;
                rdp = false;
            }
            else if(rdp){
                ch = realloc(ch, sizeof(ch)+1);
                sprintf(ch, "%s%s", ch, iter->value);
            }
            
            if(!rdp) {
                bool empty = true;
                for(int i = 0; i < len(ch); i++){
                    if(empty && ch[i] == ' ') {
                        empty = true;
                    }
                    else { 
                        empty = false;
                    }
                    if(!empty)
                        break;
                }

                if(!empty) {
                    if(( ( starts_with(ch,"\"") || starts_with(ch,"'") ) && 
                            ( ends_with(ch,"\"") || ends_with(ch,"'") )) || dec_convertable(ch) || int_convertable(ch))
                    {
                        param->constVal = malloc(sizeof(char*));
                        strcpy(param->constVal, ch);
                        printf("Saved Param {%s} ", param->constVal);
                    } else {
                        param->paramName = malloc(sizeof(char*));
                        
                        strcpy(param->paramName, ch);
                        printf("Saved ref Param {%s}_CRC_{%u}", param->paramName, compute_crc32(ch));
                    }
                    
                }
                ch = malloc(sizeof(char*));
            }
        }
        
        iter = iter->next;
    }
    
    free(ch);
    printf("%i", indent);
    return(indent != 0x00) ? -1 : 0;
}

void print_list(item_char * head){
    item_char * current = head;
    while(current != NULL) {
        printf("%s", current->value);
        
        current = current->next;
    }
}

int analyze_file(char* fname){
    fi = fopen(fname, "r");

    char lastChar = getc(fi);
    bool comment = false;
    data = malloc(sizeof(item_char));
    while(lastChar != EOF) {
        
        if(is_comment(lastChar)) {
            comment = true;
        }
        if (lastChar == '\n'){
            comment = false;
        }
        if(comment == false){
            if(data->value == NULL){
                char*a = malloc(sizeof(char));
                sprintf(a, "%c", lastChar);
                data->value = a;
            }
            else {
                char*a = malloc(sizeof(char));
                sprintf(a, "%c", lastChar);
                add(data, a);
            }
        }
        lastChar = getc(fi);
    }
    
    fclose(fi);
    free(fi);
    print_list(data);

    return form_representation();
}

int main(int argc, char* argv[]) {
    int result = 0;
    
    for(int i = 0; i < 1; i++){
//        if(!ends_with(argv[i], ".ch")){
//            continue;
//        }

        int result = analyze_file("./example1.ch");//argv[i]);
        printf("\nCompileStatus: %i\n", result);
        item_char* curr = data;
        while(curr) {
            if(curr->previous != NULL)
                free(curr->previous);

            free(curr->value);
            curr = curr->next;
        }

        if(result < 0) {
            break;
        }
    }
    
    return (result < 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}