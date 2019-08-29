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
 * File:   typedefs.h
 * Author: dylan.eddies
 *
 * Created on 21 August 2019, 12:15
 */

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct token {
    char * token;
    uint8_t code;
} token_t;

typedef struct child { 
    struct child * prev;
    uint8_t * id; 
    struct child * next;
} child_t;

typedef struct param {
    struct param * prev;    
    token_t * type;
    char * paramName;
    char * constVal; 
    struct param * next;
} param_t;

typedef struct form { 
    struct form * prev;
    token_t * type; 
    uint8_t * id;
    char* formName;
    param_t * params;
    child_t * childForm;
    struct form * next;
} form_t;


#ifdef __cplusplus
}
#endif

#endif /* TYPEDEFS_H */

