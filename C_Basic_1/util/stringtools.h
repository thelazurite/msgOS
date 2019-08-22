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
 * File:   stringtools.h
 * Author: dylan.eddies
 *
 * Created on 15 August 2019, 14:18
 */


#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H


#define is_bracket(x)   (x == '(' || x == ')')
#define is_wspace(x)    (x == ' ' || x ==  '\n' || x == '\t')
#define is_comment(x)   (x == ';')

#ifdef __cplusplus
extern "C" {
#endif

    #include <stdbool.h>
    
    bool contains(char * origin, char * term);
    bool starts_with(char * origin, char * term);
    bool ends_with(char * origin, char * term);
    char * to_lower(char * origin); 
    char * to_upper(char * origin);
    int len(char * origin);
    bool int_convertable(char * origin);
    bool dec_convertable(char * origin);


#ifdef __cplusplus
}
#endif

#endif /* STRINGTOOLS_H */

