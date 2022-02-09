#ifndef NAME_TO_BE_H
#define NAME_TO_BE_H
//concrete implementation file write operation
#include "EventHandler.h"
#include "Reactor.h"
#include "adt_def.h"

typedef struct FileWriter *FileWriterPtr;

FileWriterPtr enableWrite(NodePtr head);

void disableWrite(FileWriterPtr *ptr);
#endif