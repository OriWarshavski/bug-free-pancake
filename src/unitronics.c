#include "unitronics.h"
#include <stdio.h>
#include <math.h>

#define BYTE_SIZE 8

static void ExtractMetadata(Metadata* a_mData, int** a_dstOffsets, int** a_dstSizes, TYPE** a_dstTypes, int* a_numElements);
static void ConvertBinaryToBuffer(BYTE* runner, int a_size, unsigned char* a_dstBufferStart);
static void ConvertNumToBuffer(BYTE* a_runner, int a_size, unsigned char* a_dstBufferStart);
// static void ConvertStrToBuffer(BYTE* a_runner, int a_size, unsigned char* a_dstBufferStart) ;

static void ConvertBufferToBinary(const unsigned char* a_srcBufferStart, int a_size, BYTE* a_dstRunnerStart);
static void ConvertBufferToNum(const unsigned char* a_srcBufferStart, int a_size, BYTE* a_dstRunnerStart, TYPE a_type) ;

int StructToBuffer(const void* a_srcStruct, unsigned char* a_dstBuffer, int a_dstBufferSize, Metadata* a_mData)
{
    int i, nElement, expectedSize = 0;
    int* offsets, *sizes;
    TYPE* types;
    BYTE* runner;
    if(a_srcStruct == NULL || a_dstBuffer == NULL || a_mData == NULL) {
        return -1;
    }
    runner = (BYTE*)a_srcStruct;
    ExtractMetadata(a_mData, &offsets, &sizes, &types, &nElement);

    for(i = 0; i < nElement; ++i) {
        if(types[i] == STR ) {
            expectedSize += sizes[i];
        }
        else {
            ++expectedSize;
        }
    }

    if(expectedSize > a_dstBufferSize) {
        return -1;
    }

    for (i = 0; i < nElement; ++i) {
        if(types[i] == BINARY) {
            ConvertBinaryToBuffer(runner + offsets[i], sizes[i], a_dstBuffer + i);
        }
        // else if(types[i] == STR) {
        //     ConvertStrToBuffer(runner + offsets[i], sizes[i], a_dstBuffer + i);
        // }
        else {
            ConvertNumToBuffer(runner + offsets[i], sizes[i], a_dstBuffer + i);
        }
    }
    return expectedSize;
}

int BufferToStruct(const unsigned char* a_srcBuffer, int a_dataLen, void* a_dstStruct, Metadata* a_mData)
{
    int i, nElement;
    int* offsets, *sizes;
    TYPE* types;
    BYTE* runner;

    if(a_srcBuffer == NULL || a_dstStruct == NULL || a_mData == NULL) {
        return -1;
    }

    runner = (BYTE*)a_dstStruct;

    ExtractMetadata(a_mData, &offsets, &sizes, &types, &nElement);

    for (i = 0; i < nElement; ++i) {
        if(types[i] == BINARY) {
            ConvertBufferToBinary(a_srcBuffer + i, sizes[i], runner + offsets[i]);
        }

        else{
            ConvertBufferToNum(a_srcBuffer + i, sizes[i], runner + offsets[i], types[i]);
        }
    }
    return 0;
}


static void ExtractMetadata(Metadata* a_mData, int** a_dstOffsets, int** a_dstSizes, TYPE** a_dstTypes, int* a_numElements)
{
    *a_dstOffsets = a_mData -> m_offsets;
    *a_dstSizes = a_mData -> m_sizes;
    *a_dstTypes = a_mData -> m_types;
    *a_numElements = a_mData -> m_numElements;
}

static void ConvertBinaryToBuffer(BYTE* a_runner, int a_size, unsigned char* a_dstBufferStart)
{
    int i, result = 0;
    a_runner = a_runner + a_size - 1;
    for(i = a_size - 1; i >= 0; --i, --a_runner) {
        if(*a_runner == 1) {
            result += pow(2, a_size - 1 - i);
        }
    }
    *a_dstBufferStart = result;
}

static void ConvertNumToBuffer(BYTE* a_runner, int a_size, unsigned char* a_dstBufferStart) 
{
    int i;
    for(i = 0; i < a_size; ++i, ++a_runner) {
        *(a_dstBufferStart + i) = *a_runner;
    }
}

// static void ConvertStrToBuffer(BYTE* a_runner, int a_size, unsigned char* a_dstBufferStart) 
// {
//     int i;
//     for(i = 0; i < a_size; ++i, ++a_runner) {
//         *(a_dstBufferStart + i) = *a_runner;
//     }
// }

static void ConvertBufferToBinary(const unsigned char* a_srcBufferStart, int a_size, BYTE* a_dstRunnerStart)
{
    int i;
    unsigned char val;
    a_dstRunnerStart = a_dstRunnerStart + a_size - 1; //go to the end
    val = *a_srcBufferStart;

    for(i = a_size - 1; i >= 0; --i, --a_dstRunnerStart) {
        *a_dstRunnerStart = val % 2;
        val /= 2;
    }
}

static void ConvertBufferToNum(const unsigned char* a_srcBufferStart, int a_size, BYTE* a_dstRunnerStart, TYPE a_type) 
{
    int i;
    // BYTE* runner = a_dstRunnerStart
    for(i = 0; i < a_size; ++i, ++a_dstRunnerStart) {
        *a_dstRunnerStart = *(a_srcBufferStart + i);
    }
    if(a_type == STR) {
        *a_dstRunnerStart = '\0';
    }
}
