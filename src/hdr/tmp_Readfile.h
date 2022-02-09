#ifndef NAME_TO_BE2_H
#define NAME_TO_BE2_H
//concrete implementation file read operation
#include "EventHandler.h"
#include "Reactor.h"
#include "adt_def.h"

typedef struct FileReader *FileReaderPtr;

FileReaderPtr enableRead(NodePtr head);

void disableRead(FileReaderPtr *ptr);
#endif