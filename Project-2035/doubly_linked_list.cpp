// Copy your DLL Code here
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

LLNode* create_llnode(void* data) {

    LLNode* newNode = (LLNode*) malloc(sizeof(LLNode));
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = data;

    return newNode; 
}

DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

int getSize(DLinkedList* dLinkedList){

  int sizeOfDLL = dLinkedList->size;

  return sizeOfDLL;
}

LLNode* getHead(DLinkedList* dLinkedList){

  LLNode* DLLHead = dLinkedList->head;

  return DLLHead; 
}

LLNode* getTail(DLinkedList* dLinkedList){

  LLNode* DLLTail = dLinkedList->tail;

  return DLLTail; // replace this
}

LLNode* getNext(LLNode* node){

  LLNode* DLLNext = node->next;

  return DLLNext; // replace this
}

LLNode* getPrev(LLNode* node){

  LLNode* DLLPrev = node->prev;

  return DLLPrev; // replace this
}

void* getData(LLNode* node){

  void* DLLData = node->data;

  return DLLData; // replace this
}

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
  if (prev_node == NULL) {
    printf("the given previous node cannot be NULL");
    return;
  }
  if ((prev_node->next) == NULL) {
    insertTail(dLinkedList, data); //come back
  }
  LLNode* newNode = create_llnode(data);
  LLNode* nextNode = getNext(prev_node);
  newNode->prev = prev_node;
  newNode->next = nextNode;
  prev_node->next = newNode;
  nextNode->prev = newNode;

  return;
}

void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
  if (next_node == NULL) {
    printf("the given next node cannot be NULL");
    return;
  }
  if ((next_node->prev) == NULL) {
    insertHead(dLinkedList, data);
  }
  LLNode* newNode = create_llnode(data);
  LLNode* prevNode = getPrev(next_node);
  newNode->prev = prevNode;
  newNode->next = next_node;
  prevNode->next = newNode;
  next_node->prev = newNode;

  return;
}

void insertHead(DLinkedList* dLinkedList, void* data){
  if(dLinkedList->head == NULL){                        //if the list is empty
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    LLNode* newNode = create_llnode(data);
    LLNode* oldHead = getHead(dLinkedList);
    newNode->next = oldHead;
    oldHead->prev = newNode;
    dLinkedList->head = newNode;
    dLinkedList->size++;
    return; 
  }
}

void insertTail(DLinkedList* dLinkedList, void* data){
if(dLinkedList->head == NULL){                          //if the list is empty
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    LLNode* newNode = create_llnode(data);
    LLNode* oldTail = getTail(dLinkedList);
    newNode->prev = oldTail;
    oldTail->next = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++;
    return; 
  }

}

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){
  if (Node == NULL) {
    return;
  }
  if (dLinkedList->head == Node && dLinkedList->tail == Node) {         //if size of list = 1
    dLinkedList->head = NULL;
    dLinkedList->tail = NULL;
  } else if ((Node->prev) == NULL) {                   //if the node is the head
      LLNode* nextNode = getNext(Node);
      dLinkedList->head = nextNode;
      nextNode->prev = NULL;
    } else if ((Node->next) == NULL) {                    //if the node is the tail
        LLNode* prevNode = getPrev(Node);
        dLinkedList->tail = prevNode;
        prevNode->next = NULL;
      } else {
        LLNode* nextNode = getNext(Node);
        LLNode* prevNode = getPrev(Node);
        nextNode->prev = prevNode;
        prevNode->next = nextNode;
      }
  dLinkedList->size--;                                  //decrease the size
  free(Node->data);                                     //free the data
  free(Node);                                           //free the node
}

void destroyList(DLinkedList* dLinkedList){
  if (dLinkedList == NULL) {
    return;
  }
  LLNode* current = dLinkedList->head;
  while (current != NULL) {
    LLNode* nextNode = current->next;
    deleteNode(dLinkedList, current);
    current = nextNode;
  }

  free(dLinkedList);
}

void reverse(DLinkedList* dLinkedList)
{
  if (dLinkedList == NULL || dLinkedList->head == NULL) {
    return;
  }
  LLNode* current = dLinkedList->head;
  LLNode* temp = NULL;
  while (current != NULL) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;

    current = current->prev;
  }

  temp = dLinkedList->tail; 
  dLinkedList->tail = dLinkedList->head;
  dLinkedList->head = temp;

}