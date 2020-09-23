#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASHSIZE 101

//��ϣ��Ԫ��
typedef struct nodelist
{
    struct nodelist *next; //����������
    char *key; //��ϣ��key
    char *value; //��ϣ��ֵ
} Nodelist;

//��ϣ��
static Nodelist *hashTable[HASHSIZE]; 


//ɢ�к���--����ɢ�з�
unsigned hash(char *key);

//��ѯkey
Nodelist *search(char *key);

//���뵽��ϣ��
Nodelist *insert_hash_table(char *key, char *value);

//����key��ȡֵ
char * get_value(char *key);

void hash_table_sample(void);

#endif //__HASH_TABLE_H
