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
 * File:   link_list.h
 * Author: dylan.eddies
 *
 * Created on 15 August 2019, 14:08
 */

#ifndef LINK_LIST_H
#define LINK_LIST_H

#ifdef __cplusplus
extern "C" {
#endif
    #include <stdlib.h>
    #include <stdint.h>
    
    typedef struct item { 
        struct item * previous; 
        char * value;
        struct item * next; 
    } item_char;

    item_char* add(item_char* head, char * value);
    item_char* delete(item_char* value);
    
    typedef struct item_uint { 
        struct item * previous; 
        uint8_t * value;
        struct item * next; 
    } item_t;

    item_t* add_t(item_t* head, uint8_t * value);
    item_t* delete_t(uint8_t* value, item_t * head);
    item_char* find(char* value);
    

#ifdef __cplusplus
}
#endif

#endif /* LINK_LIST_H */

