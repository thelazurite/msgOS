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
 * File:   stringtools_test.c
 * Author: dylan.eddies
 *
 * Created on 16-Aug-2019, 02:35:44
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "../stringtools.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void is_bracket_recognizes_open() {
    CU_ASSERT(is_bracket('(') == true);
}

void is_bracket_recognizes_closed() {
    CU_ASSERT(is_bracket(')') == true);
}

void is_bracket_recognizes_not_a_bracket() {
    CU_ASSERT(is_bracket('a') == false);
}

void is_wspace_recognizes_space() {
    CU_ASSERT(is_wspace(' ') == true);
}

void is_wspace_recognizes_new_line() {
    CU_ASSERT(is_wspace('\n') == true);
}
void is_wspace_recognizes_tab() {
    CU_ASSERT(is_wspace('\t') == true);
}
void is_wspace_recognizes_not_wspace() {
    CU_ASSERT(is_wspace('X') == false);
}

void is_comment_recognizes_comment() {
    CU_ASSERT(is_comment(';') == true);
}
void is_comment_recognizes_not_comment() {
    CU_ASSERT(is_comment('X') == false);
}

void contains_matches_when_origin_has_substring() {
    CU_ASSERT(contains("String contains something", "cont") == true);
}

void contains_is_case_sensitive() {
    CU_ASSERT(contains("String contains something", "Cont") == false);
}

void contains_does_not_match() {
    CU_ASSERT(contains("String contains something", "Foo") == false);
}

void starts_with_matches_substring(){
    CU_ASSERT(starts_with("StringShould start with StringShould", "StringShould") == true);
}
void starts_with_is_case_sensitive(){
    CU_ASSERT(starts_with("StringShould start with StringShould", "stringshould") == false);
}
void starts_with_does_not_match(){
    CU_ASSERT(starts_with("StringShould start with StringShould", "FooBar") == false);
}

void ends_with_matches_substring(){
    CU_ASSERT(ends_with("StringShould end with StringShouldEnd", "ShouldEnd") == true);
}
void ends_with_is_case_sensitive(){
    CU_ASSERT(ends_with("StringShould end with StringShouldEnd", "shouldend") == false);
}
void ends_with_does_not_match(){
    CU_ASSERT(ends_with("StringShould end with StringShouldEnd", "FooBar") == false);
}

void to_lower_converts_string_with_number(){
    char* expected = "test 12";
    char* sut  = malloc(8);
    
    int i = 12;
    sprintf(sut, "Test %i", i);
    sut = to_lower(sut);
    printf("\n <Expected>: %s <Actual>: %s\n", expected, sut);

    CU_ASSERT(strcmp(sut,expected) == 0);
    free(sut);
}

void to_lower_converts_string() {
    
    char* sut = malloc(16);
    sut = "TeStInG To LoWeR";
    
    printf("%s\n", sut);

    sut = to_lower(sut);
    printf("%s\n", sut);
    
    CU_ASSERT(strcmp(sut, "testing to lower") == 0);
    free(sut);
}


void to_upper_converts_string_with_number(){
    char* expected = "TEST 12";
    char* sut  = malloc(8);
    
    int i = 12;
    sprintf(sut, "Test %i", i);
    sut = to_upper(sut);
    printf("\n <Expected>: %s <Actual>: %s\n", expected, sut);

    CU_ASSERT(strcmp(sut,expected) == 0);
    free(sut);
}

void to_upper_converts_string() {
    char* sut = malloc(16);
    sut = "TeStInG To UpPer";
    
    printf("%s\n", sut);

    sut = to_upper(sut);
    printf("%s\n", sut);
    
    CU_ASSERT(strcmp(sut, "TESTING TO UPPER") == 0);
    free(sut);
}

void len_gets_correct_length(){
    CU_ASSERT(len("ABC") == 3);
    
    CU_ASSERT(len("AbCh21344")== 9);

}

int main() {
    CU_pSuite pSuite = NULL;

    /* initialise the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("String Tools Tests", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if (
            (NULL == CU_add_test(pSuite, "contains_matches_when_origin_has_substring", contains_matches_when_origin_has_substring)) ||
            (NULL == CU_add_test(pSuite, "contains_is_case_sensitive", contains_is_case_sensitive)) ||
            (NULL == CU_add_test(pSuite, "contains_does_not_match", contains_does_not_match)) ||
            (NULL == CU_add_test(pSuite, "starts_with_matches_substring", starts_with_matches_substring)) ||
            (NULL == CU_add_test(pSuite, "starts_with_is_case_sensitive", starts_with_is_case_sensitive)) ||
            (NULL == CU_add_test(pSuite, "starts_with_does_not_match", starts_with_does_not_match)) ||
            (NULL == CU_add_test(pSuite, "ends_with_matches_substring", ends_with_matches_substring)) ||
            (NULL == CU_add_test(pSuite, "ends_with_is_case_sensitive", ends_with_is_case_sensitive)) ||
            (NULL == CU_add_test(pSuite, "ends_with_does_not_match", ends_with_does_not_match)) ||
            (NULL == CU_add_test(pSuite, "is_bracket_recognizes_open", is_bracket_recognizes_open)) ||
            (NULL == CU_add_test(pSuite, "is_bracket_recognizes_closed", is_bracket_recognizes_closed)) ||
            (NULL == CU_add_test(pSuite, "is_bracket_recognizes_not_a_bracket", is_bracket_recognizes_not_a_bracket)) ||
            (NULL == CU_add_test(pSuite, "is_wspace_recognizes_space", is_wspace_recognizes_space)) ||
            (NULL == CU_add_test(pSuite, "is_wspace_recognizes_new_line", is_wspace_recognizes_new_line)) ||
            (NULL == CU_add_test(pSuite, "is_wspace_recognizes_tab", is_wspace_recognizes_tab)) ||
            (NULL == CU_add_test(pSuite, "is_wspace_recognizes_not_wspace", is_wspace_recognizes_not_wspace)) ||
            (NULL == CU_add_test(pSuite, "is_comment_recognizes_comment", is_comment_recognizes_comment)) ||
            (NULL == CU_add_test(pSuite, "is_comment_recognizes_not_comment", is_comment_recognizes_not_comment)) ||
            (NULL == CU_add_test(pSuite, "to_lower_converts_string_with_number", to_lower_converts_string_with_number)) ||
            (NULL == CU_add_test(pSuite, "to_lower_converts_string", to_lower_converts_string)) ||
            (NULL == CU_add_test(pSuite, "to_upper_converts_string_with_number", to_upper_converts_string_with_number)) ||
            (NULL == CU_add_test(pSuite, "to_upper_converts_string", to_upper_converts_string)) ||
            (NULL == CU_add_test(pSuite, "len_gets_correct_length", len_gets_correct_length))
        )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
