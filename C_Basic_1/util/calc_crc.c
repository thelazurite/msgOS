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

#include <stdlib.h>
#include <stdint.h>
#include "calc_crc.h"
#include "stringtools.h"

static const uint8_t divisor8 = 0x1D;
static const uint8_t mask8 = 0x80;

static const uint16_t divisor16 = 0x1021;
static const uint16_t mask16= 0x8000;

static const uint32_t divisor32 = 0x04C11DB7;
static const uint32_t mask32 = 0x80000000;

uint8_t compute_crc8(char*  bytes){
    uint8_t crc8 = 0x00;
    for (int i = 0; i < len(bytes); i++){
        crc8 ^= bytes[i];
        for(int x = 0; x < 8; x++){
            if((crc8&mask8)!=0){
                crc8 = (uint8_t)((crc8<<1)^divisor8);
            } else {
                crc8 <<= 1;
            }
        }
    }
    return crc8;
}

uint16_t compute_crc16(char* bytes){
    uint16_t crc16 = 0x00; 
    for (int i = 0; i < len(bytes); i++){
        crc16 ^= (uint16_t)bytes[i] << 8;
        for(int x =0; x<8; x++) {
            if((crc16 & mask16)!= 0){
                crc16 = (uint16_t)((crc16<<1)^divisor16);
            }else{
                crc16 <<= 1;
            }
        }
    }
    return crc16;
}

uint32_t compute_crc32(char* bytes){
    uint32_t crc32 = 0x00;
    
    for (int i = 0; i < len(bytes); i++) {
        crc32 ^= (uint32_t)bytes[i]<<24;
        for(int x = 0; x < 8; x++){
            if((crc32 & mask32) != 0){
                crc32 = (uint32_t)((crc32 << 1) ^ divisor32);
            } else {
                crc32 <<=1;
            }
        }
    }
    return crc32;
}