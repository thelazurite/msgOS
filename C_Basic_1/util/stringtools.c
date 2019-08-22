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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stringtools.h"

#define convertCase 32

bool contains(char * origin, char * term){
    int originLen   = len(origin);
    int termLen     = len(term);
    
    bool matches = false;
    for(int i = 0; i < originLen; i++){
        for (int x = 1; x <= termLen; x++){
            int position = x-1;
            bool charEquals = origin[i+position] == term[position];
            
            if(!charEquals){
                break;
            }
            if(charEquals && x == termLen)
            {
                matches = true;
                break;
            }
        }
        if(matches == true){
            break;
        }
    }
    return matches;
}

bool starts_with(char * origin, char * term){
    int termLen = len(term);
    
    for (int i = 0; i < termLen; i++){
        if(origin[i] != term[i]){
            return false; 
        }
    }
    
    return true;   
}

bool ends_with(char * origin, char * term) {
    int originLen   = len(origin);
    int termLen     = len(term);
    
    for(int i = 0; i < termLen; i++){
        int x = originLen - termLen +i; 
        
        if(origin[x] != term[i]){
            return false;
        }
    }
    
    return true;
}

int len(char * origin) {
    return snprintf(NULL, 0, "%s", origin); 
}


char * to_lower(char * origin) { 
    int memSize         = len(origin);
    char* converted     = malloc(memSize+1);
    
    int i = 0;
    
    while(origin[i] != '\0' && i < memSize){
        if(origin[i] >= 'A' && origin[i] <= 'Z'){
            converted[i] = origin[i] + convertCase;
        }
        else { 
            converted[i] = origin[i];
        }
        i++;
    }
    
    converted[memSize] = '\0';
    return converted;
}

char * to_upper(char * origin) { 
    int memSize         = len(origin);
    char* converted     = malloc(memSize + 1);
    
    int i = 0;
    while(origin[i] != '\0' && i < memSize) {
        if(origin[i] >= 'a' && origin[i] <= 'z'){
            converted[i] = origin[i] - convertCase;
        }
        else {
            converted[i] = origin[i];
        }
        i++;
    }
    
    converted[memSize] = '\0';
    return converted;
}

bool int_convertable(char * origin) { 
    int sp = origin[0] == '-' ? 1 : 0;
    for(int i = sp; i < len (origin); i++){
        if(origin[i] >= '0' && origin[i] <= '9')
            continue;
        return false;
    }
    return true;
}
bool dec_convertable(char * origin) {
    int sp = origin[0] == '-' ? 1 : 0;
    int dp = 0;
    
    for(int i = sp; i < len (origin); i++){
        if(origin[i] >= '0' && origin[i] <= '9')
            continue;
        else if(origin[i] == '.'|| origin[i] == ',')
            dp++;
        
        if(dp > 1)
            return false;
        return false;
    }
    return true;
}