#include "hdr/tmp_Readfile.h"
#include "hdr/adt_file_handle.h"
#include "hdr/adt_def.h"

#define PATH_TO_FILE "DATAFILE"

typedef void (*SetData)(void* instance);

struct FileReader{
    Handle handle;
    EventHandler eventhandler;
};

Handle getHandle(void* instance){
    FileReaderPtr newFile=instance;
    return newFile->handle;
}


void readfrfile(void* instance){
    FileReaderPtr newFile=instance;
    /*fopen to write to the file*/
    printf("Event: newFile %p\n",newFile);
    printf("Event: readfrfile %p\n",newFile->eventhandler.data);
    F_Handle fd=createFileHandle(PATH_TO_FILE);
    if (fd){
        printf("outside Event: fd %p\n",fd);
        NodePtr head=(NodePtr)newFile->eventhandler.data;
        printf("Event: head %p\n",head);
        while(fd->pos!=-1){
            ReadFile(fd);
            if(fd->data){
                addNode(head,(InfoNodePtr)fd->data);
            }
        }        
        destroyFileHandle(&fd);        
    }    
}

/*create */
FileReaderPtr enableRead(NodePtr head){
    FileReaderPtr newFile=malloc(sizeof *newFile);
    if(newFile){
        newFile->handle=0; //file handle
        newFile->eventhandler.instance=newFile;
        newFile->eventhandler.getHandle=getHandle;
        newFile->eventhandler.handleEvent=readfrfile;
        newFile->eventhandler.data=(void*)head;
        printf("enable read data address %p\n",newFile->eventhandler.data);
        Register(&newFile->eventhandler,EVT_READ_FILE);
    }
    return newFile;
}



/*destroy and free*/
void disableRead(FileReaderPtr *ptr){
    Unregister(&(*ptr)->eventhandler);
    if (*ptr) {
        free(*ptr);
        *ptr=NULL;
    }
}