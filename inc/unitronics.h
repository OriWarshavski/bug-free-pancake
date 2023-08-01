#ifndef __UNITRONICS_H__
#define __UNITRONICS_H__

typedef unsigned char BYTE;

typedef enum {
    BINARY,
    STR,
    OTHER
} TYPE;

typedef struct Metadata {
    int m_numElements;
    int* m_offsets;
    int* m_sizes;
    TYPE* m_types;
} Metadata;


int StructToBuffer(const void* a_srcStruct, unsigned char* a_dstBuffer, int a_dstBufferSize, Metadata* a_mData);

int BufferToStruct(const unsigned char* a_srcBuffer, int a_dataLen, void* a_dstStruct, Metadata* a_mData);

#endif /* __UNITRONICS_H__ */