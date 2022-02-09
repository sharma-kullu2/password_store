#ifndef ADT_FILE_HANDLE_H
#define ADT_FILE_HANDLE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Todo
//
typedef void* (*Ops)(void*Handle,void*Data);

struct file_handle{
    void* Handle;//File type handle (typecasted)
    int pos;//position of the file pointer
    char* filename;
    void* data; //Any Structure or datatype address can be (typecasted)
    Ops ops;
};

typedef struct file_handle* F_Handle;
//Create
F_Handle createFileHandle(char*filename);
//read
void ReadFile(F_Handle);
//write
void WriteFile(F_Handle);
//Destroy
void destroyFileHandle(F_Handle*);
//
#endif