#ifndef __STACK_H
#define __STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define STACK_INIT_SIZE 10 //�洢�ռ�ĳ�ʼ������
#define STACK_INCREMENT 10 //����

typedef int SElemTpye; //Ԫ������
typedef int Status; //Ԫ������

typedef struct
{
   SElemTpye *base;//ջ��ָ��
   SElemTpye *top;//ջ��ָ��
   int size;
} Stack;

Status Stack_Init(Stack *stack);
Status Stack_Push(Stack *s, SElemTpye e);
Status Stack_Pop(Stack *s, SElemTpye *e);
Status Stack_Destroy(Stack *s);
int Test_Stack_Sample(void);


#endif //__STACK_H

