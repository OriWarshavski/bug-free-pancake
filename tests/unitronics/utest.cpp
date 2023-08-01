#include "mu_test.h"
#include "unitronics.h"

#include <stdio.h> 

#define DST_SIZE 1000
typedef struct ST {
    unsigned char a[8]; //a[8]
    unsigned char b;
    unsigned char bPadding[3];
    short c;
    unsigned char cPadding[2];
    char str[11];
    unsigned char strPadding[1];
} ST;

BEGIN_TEST(test1_correct)
    unsigned char buffer[DST_SIZE] = {0};
    Metadata mData;
    ST st;
    int offsets[4] = {0, 8, 12, 16};
    TYPE types[4] = {BINARY, OTHER, OTHER, STR};
    int sizes[4] = {8, 1, 1, 4};

    mData.m_numElements = 4;
    mData.m_types = types;
    mData.m_offsets = offsets;
    mData.m_sizes = sizes;
    st.a[0] = 1;
    st.a[1] = 0;
    st.a[2] = 0;
    st.a[3] = 0;
    st.a[4] = 0;
    st.a[5] = 0;
    st.a[6] = 0;
    st.a[7] = 1;

    st.b = 5;
    st.c = 100;

    st.str[0] = 'o';
    st.str[1] = 'r';
    st.str[2] = 'i';
    st.str[3] = '\0';
    ASSERT_EQUAL(StructToBuffer(&st, buffer, DST_SIZE, &mData), 7);
    
    ASSERT_EQUAL(buffer[0], 129);
    ASSERT_EQUAL(buffer[1], 5);
    ASSERT_EQUAL(buffer[2], 100);
    ASSERT_EQUAL(buffer[3], 'o');
    ASSERT_EQUAL(buffer[4], 'r');
    ASSERT_EQUAL(buffer[5], 'i');
    ASSERT_EQUAL(buffer[6], '\0');
    printf("string in the buffer: %s\n", &buffer[3]);
END_TEST

BEGIN_TEST(test_small_buffer_size)
    unsigned char buffer[5] = {0};
    Metadata mData;
    ST st;
    int offsets[4] = {0, 8, 12, 16};
    TYPE types[4] = {BINARY, OTHER, OTHER, STR};
    int sizes[4] = {8, 1, 1, 3};

    mData.m_numElements = 4;
    mData.m_types = types;
    mData.m_offsets = offsets;
    mData.m_sizes = sizes;

    st.a[0] = 1;
    st.a[1] = 0;
    st.a[2] = 0;
    st.a[3] = 0;
    st.a[4] = 0;
    st.a[5] = 0;
    st.a[6] = 0;
    st.a[7] = 1;

    st.b = 5;
    st.c = 100;

    st.str[0] = 'o';
    st.str[1] = 'r';
    st.str[2] = 'i';
    // st.str[3] = '\0';

    ASSERT_EQUAL(StructToBuffer(&st, buffer, 5, &mData), -1);
END_TEST

BEGIN_TEST(test3_to_struct)
    unsigned char buffer[DST_SIZE] = {129, 5, 100, 'o', 'r', 'i', '\0'};
    Metadata mData;
    ST st;
    int offsets[4] = {0, 8, 12, 16};
    TYPE types[4] = {BINARY, OTHER, OTHER, STR};
    int sizes[4] = {8, 1, 1, 3};
    mData.m_numElements = 4;
    mData.m_types = types;
    mData.m_offsets = offsets;
    mData.m_sizes = sizes;

    ASSERT_EQUAL(BufferToStruct(buffer, 7, &st, &mData), 0);
    ASSERT_EQUAL(st.a[0], 1);
    ASSERT_EQUAL(st.a[1], 0);
    ASSERT_EQUAL(st.a[2], 0);
    ASSERT_EQUAL(st.a[3], 0);
    ASSERT_EQUAL(st.a[4], 0);
    ASSERT_EQUAL(st.a[5], 0);
    ASSERT_EQUAL(st.a[6], 0);
    ASSERT_EQUAL(st.a[7], 1);
    ASSERT_EQUAL(st.b, 5);
    ASSERT_EQUAL(st.c, 100);  
    ASSERT_EQUAL(st.str[0], 'o');  
    ASSERT_EQUAL(st.str[1], 'r');  
    ASSERT_EQUAL(st.str[2], 'i');  
END_TEST

TEST_SUITE("tests")
    TEST(test1_correct)
    TEST(test_small_buffer_size)
    TEST(test3_to_struct)
END_SUITE
