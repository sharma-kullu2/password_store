#include <stdio.h>
#include <stdlib.h>
#include "src/hdr/adt_def.h"
#include "src/hdr/Reactor.h"
#include "src/hdr/tmp_Writefile.h"
#include "src/hdr/tmp_Readfile.h"

void Header();
void Init_List();
void Read();
void Write(struct base_node *);
void Footer();

int main(){
    int m_input=0;
    Header();
    scanf("%d",&m_input);
    NodePtr m_list=NULL;
    m_list=createList();
    FileWriterPtr  writer= enableWrite(m_list);
    FileReaderPtr reader=enableRead(m_list);
    if(m_list!=NULL) printf("Linked List Initialised\n");

    switch (m_input)
    {
    case 1/* constant-expression */:
        //Read(m_list);/* code */
         DispatchEvent(EVT_READ_FILE);
        break;
    case 2:
        //printf ("------>Entered head address=%p\n",m_list);
        Write(m_list);
        DispatchEvent(EVT_WRITE_FILE);
        break;
    default:
        printf("Not a Valid Entry!!!\n");
        printf("You have entered : %d\n", m_input);
        break;
    }
    //printf ("<-----updated head address=%p\n",m_list);
    readList(m_list);
    destroyList(&m_list);
    disableWrite(&writer);
    disableRead(&reader);
    return 0;
}

void Header(){
    printf("***********WELCOME PASSWORD STORING UTILITY*********\n");
    printf("Read--------------Press 1.\n");
    printf("Write-------------Press 2.\n");
}


void Write(NodePtr list){
    NodePtr l_list=NULL;
    InfoNodePtr l_info=NULL;
    printf("\nEnter User Name[max 20] : ");
    char*user=NULL;
    user=(char*)calloc(20*sizeof(char),0);
    scanf("%s",user);
    printf("\nEnter Pass Word[max 20] : ");
    char*pass;
    pass=(char*)calloc(20*sizeof(char),0);
    scanf("%s",pass);
    l_info=setInfo(&user,&pass);
    addNode(list /*,InfoNodePtr info*/,l_info);
    printf("\nEnter More.......Press[Y]\n");
    char c_input;
    getc(stdin);
    scanf("%c",&c_input);
    if (c_input=='Y'||c_input=='y') Write(list);
}

void Footer(NodePtr list){
    printf ("EXITING............\n");
}
