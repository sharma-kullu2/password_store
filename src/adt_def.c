#include "hdr/adt_def.h"
#include <stdio.h>
#include <stdlib.h>


/*initialises list and returns head*/
NodePtr createList(){
    NodePtr list=malloc(sizeof(Node));
    if (list){
        list->next_node=NULL;
        return list;
        }
    else return NULL;
}

/*private method to delete info allocated memory*/
void resetInfo(InfoNodePtr *info){
    if ((*info)->passowrd) free((*info)->passowrd);
    if ((*info)->username) free((*info)->username);
    free(*info);
    *info=NULL;
}

/*destroys the list*/
void destroyList(NodePtr *list){
    /*while checking next node is NULL; 
    free mem for current node*/
    printf("FREEING LIST ADR: %p\n",*list);
    while ((*list)->next_node!=NULL){
        (*list)=(*list)->next_node;//update current pointer to next node in list 
        resetInfo(&((*list)->info)); //dealloc info
        free(*list); //this doesnot invalidate address or set it to NULL just makes freed memory reusable
    }
    *list=NULL;
}

InfoNodePtr setInfo(char* *user, char* *pass){
    InfoNodePtr info=NULL;
    info=malloc(sizeof(Info));
    if (*pass!=NULL)    info->passowrd=*pass;
    if (*user!=NULL)     info->username=*user;
    return info;
}



void addNode(NodePtr head ,InfoNodePtr info){
    NodePtr newNode=malloc(sizeof(Node));
    newNode->info=info;
    newNode->next_node=NULL;
    /*either insert at head or end of the list*/
    if(head->next_node==NULL){
        head->next_node=newNode;//set next node as new node preserve head
        //printf("--->NEXT NODE ADDR: %p\n",head->next_node);
    }
    else{
        NodePtr temp=NULL;
        temp=head;
        while(temp->next_node!=NULL){
            //printf("(LOOP)--->temp CURRENT ADDRESS: %p\n",temp);
            temp=temp->next_node;
        }
        temp->next_node=newNode;//update linked temporary address as new Node address 
    }
}

void readList(NodePtr head){
    //printf("READING LL :%p\n",head);
    int count=0;
    while (head->next_node!=NULL){
        head=head->next_node;
        //printf("READING ADDRESS OF HEAD : %p INDX NO. :%d INFO :%s\n",head,(count+1),head->info->username);
        count++;     
    }
}


