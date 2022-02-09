#ifndef ADT_DEF_H
#define ADT_DEF_H

/*Ref::http://adampetersen.se/Patterns%20in%20C%201.pdf*/

//first structure
struct base_node {
    int id;//id as in position in the linked list | updated as per insert/delete op 
    int unique_id;// id as per incremental number per insertion of new node to ll | updated once only
    struct info_node* info;// pointer to data member of ll
    char* password;//future for encryption
    char* username;//as above
    struct base_node *next_node;//next pointer
//TODO head pointer
};

//second structure
struct info_node{
    char* username;
    char* passowrd;
};


typedef struct base_node Node; //temp

typedef struct info_node Info;

/* A pointer to an incomplete type (hides the implementation details). */
typedef Node* NodePtr;

typedef Info* InfoNodePtr;

/* Create a list and return a handle to it. */
NodePtr createList();

/* Destroy the given List. All handles to it will be invalidated. */
void destroyList(NodePtr*);

/*load information on Node*/
InfoNodePtr setInfo(char* *user, char* *pass);

/*Add node to list*/
void addNode(NodePtr head ,InfoNodePtr info);

/*Read List*/
void readList(NodePtr head);
/*TODO-other methods*/

#endif