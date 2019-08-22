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
            current->next->previous = current;
            isEntered = true;
            break;
        } else {
            current = current->next;
        }
    }
    
    return head;
}

item_char* delete(item_char* item){
    item->previous->next = item->next;
    free(item);
}