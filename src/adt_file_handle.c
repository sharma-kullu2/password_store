#include "hdr/adt_file_handle.h"
#include "hdr/adt_def.h"

F_Handle createFileHandle(char*filename){
    F_Handle handle=malloc(sizeof *handle);
    if(handle){
        handle->filename=filename;
        if (handle->filename){
            FILE *filePointer;
            filePointer=fopen(handle->filename,"a+");
            if(filePointer==NULL){
                destroyFileHandle(&handle);
            }
            else{
                handle->Handle=(void*)filePointer;
                handle->pos=0; //Reading from file position tracker init
            }
            //fclose(filePointer);
        }
        else{
            destroyFileHandle(&handle);
        }
    }
    return handle;
}

char * getbuffer(char* strA,char* strB ){
    size_t len=strlen(strA)+strlen(strB);
    printf("sizeof buffer=%ld\n",len);
    char* l_buf=malloc(len*sizeof(char));
    sprintf(l_buf,"%s,%s\n",strA,strB);
    printf("buffer content=%s\n",l_buf);
    return l_buf;
}

void freebuffer(char* *ptr){
    free(*ptr);
    *ptr=NULL;
}

void safecopy(char* *dest, char * *src){
    //remove delim from source
    char* tok= strtok(*src,"\n");
    if(tok != NULL) strncpy(*dest,tok,strlen(tok));
    else strncpy(*dest,*src,strlen(*src));
}

void* writefile(void* handle,void* data){
    printf("writefile data %p\n",data);
    InfoNodePtr info=(InfoNodePtr)data;
    printf("data at address %p got info %s will be written\n",info,info->username);
    F_Handle l_handle=(F_Handle)handle;
    //write to file api
    char* buff=getbuffer(info->username,info->passowrd);
    if (buff){
        fputs(buff,l_handle->Handle);
        freebuffer(&buff);
    }
    return (void*)info;
}

void* readfile(void* handle,void* data){
    printf("readfile \n");
    InfoNodePtr info=NULL;
    //populate the info for linked list
    F_Handle l_handle=(F_Handle)handle;
    //read from file api
    printf("READFILE: file seek current pos %d\n",l_handle->pos);
    char* data_from_file=(char*)calloc(20*sizeof(char),0);
    if(l_handle->pos>=0) fseek(l_handle->Handle,l_handle->pos,SEEK_SET);//sets pointer from strting of file
    if (fgets(data_from_file,20*sizeof(char),l_handle->Handle)!=NULL)
    {
        l_handle->pos=ftell(l_handle->Handle);
        printf("READFILE: Future Pos of file ptr for Next Read= %d\n",l_handle->pos);

        //drop \n from the string
        char* tokenstringwithoutslashn=strtok(data_from_file,"\n");
        char* input_to_info[2];
        int iterator=0;
        char* token=strtok(tokenstringwithoutslashn,",");
        // Checks for delimiter
        while (token != NULL) {
            printf(" %s at idx= %d with length %ld\n", token,iterator,strlen(token));
            input_to_info[iterator]=calloc(strlen(token)*sizeof(char),0);           
            strncpy(input_to_info[iterator],token,strlen(token));
            printf("After COPY:input array value at idx=%d, is %s\n",iterator,input_to_info[iterator]);
            iterator++;
            // Use of strtok
            // go through other tokens
            token = strtok(NULL, ",");
        }
        info=setInfo(&input_to_info[0],&input_to_info[1]);   
    }
    else/*possible eof*/
    {
        l_handle->pos=-1;
    }
    free(data_from_file);
    return (void*)info;
}

void* setData(void* data){
    //write data
}

void* getData(void* data){
    //read data
}

void ReadFile(F_Handle handle){
    handle->ops=&readfile;
    handle->data=handle->ops(handle,handle->data);
    printf("handle->data %p After Read OP\n",handle->data);
}

void WriteFile(F_Handle handle){
    handle->ops=&writefile;
    printf("handle->data %p\n",handle->data);
    handle->data=handle->ops(handle,handle->data);
}

void destroyFileHandle(F_Handle *handle){
    printf("destroyFileHandle called\n");
    F_Handle l_handle=*handle;
    if(l_handle->Handle){
        fclose(l_handle->Handle);
    }
    free(*handle);
    *handle=NULL;
}