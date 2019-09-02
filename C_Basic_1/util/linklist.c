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
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

item_char* add(item_char* head, char * value){
    bool isEntered = false;
    item_char * current = head;
    
    while(!isEntered){
        if(current->next == NULL){
            current->next = malloc(sizeof(item_char));
            current->next->value = value;
            current->next->next = NULL;
            current->next->prev = current;
            isEntered = true;
            break;
        } else {
            current = current->next;
        }
    }
    
    return head;
}

void delete(item_char* item){
    item->prev->next = item->next;
    free(item);
}

item_t* add_t(item_t* head, uint8_t * value){
    bool isEntered = false;
    item_t * current = head;
    
    while(!isEntered){
        if(current->next == NULL){
            current->next = malloc(sizeof(item_t));
            current->next->value = value;
            current->next->next = NULL;
            current->next->prev = current;
            isEntered = true;
            break;
        } else {
            current = current->next;
        }
    }
    
    return head;
}

void delete_t(uint8_t * value, item_t * head){
    item_t * current = head;
    while(current != NULL) {
        if(current->value == value){
            current->prev->next = current->next;
            free(current);
            break;
        }
        current = current->next;
    }
}
item_t* pop_t(item_t* head){
    item_t * current = head;
    
    while(current->next != NULL) {
        current = current->next;
    }
    
    if(current->prev != NULL)
        current->prev->next = NULL;

    return current;
}