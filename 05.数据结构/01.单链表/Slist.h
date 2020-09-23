#ifndef __SLIST_H
#define __SLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define INI_MIN 0

//�ڵ�
typedef struct node
{
    int data;
    struct node * next;
} Node;

//����
typedef struct slist
{
    Node * head;
} Slist;

Node* makeNode(const int data); //���ɽڵ�
void destroyNode(Node * node); //���ٽڵ�

void sInit(Slist * list);//��ʼ��
bool sInsert(Slist * list, const int data); //����
bool sRemove(Slist * list, const int key); //ɾ��
bool sModify(Slist * list, const int key, const int data); //�޸�
Node* sFind(Slist * list, const int key); //����
void sTreaverse(Slist * list, void (*func)(Node * p)); //����
void sDestroy(Slist * list); //����
void printData(Node* p); //print
void slist_sample(void);

#endif //__SLIST_H

