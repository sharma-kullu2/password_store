#include "hdr/tmp_Writefile.h"
#include "hdr/adt_file_handle.h"
#include "hdr/adt_def.h"

#define PATH_TO_FILE "DATAFILE"

typedef void (*SetData)(void* instance);

struct FileWriter{
    Handle handle;
    EventHandler eventhandler;
};

Handle getFileHandle(void* instance){
    FileWriterPtr newFile=instance;
    return newFile->handle;
}


void writetofile(void* instance){
    FileWriterPtr newFile=instance;
    /*fopen to write to the file*/
    printf("Event: newFile %p\n",newFile);
    printf("Event: writetofile %p\n",newFile->eventhandler.data);
    F_Handle fd=createFileHandle(PATH_TO_FILE);
    if (fd){
        printf("outside Event: fd %p\n",fd);
        NodePtr head=(NodePtr)newFile->eventhandler.data;
        printf("Event: head %p\n",head);
        
        while (head->next_node!=NULL)
            {
                head=head->next_node;
                fd->data=(void*)head->info;
                printf("Event: head->info %p\n", fd->data);
                WriteFile(fd);
            }
        destroyFileHandle(&fd);        
    }
    
    
}

/*create */
FileWriterPtr enableWrite(NodePtr head){
    FileWriterPtr newFile=malloc(sizeof *newFile);
    if(newFile){
        newFile->handle=0; //file handle
        newFile->eventhandler.instance=newFile;
        newFile->eventhandler.getHandle=getFileHandle;
        newFile->eventhandler.handleEvent=writetofile;
        newFile->eventhandler.data=(void*)head;
        printf("enable write data address %p\n",newFile->eventhandler.data);
        Register(&newFile->eventhandler,EVT_WRITE_FILE);
    }
    return newFile;
}



/*destroy and free*/
void disableWrite(FileWriterPtr *ptr){
    Unregister(&(*ptr)->eventhandler);
    if (*ptr) {
        free(*ptr);
        *ptr=NULL;
    }
}