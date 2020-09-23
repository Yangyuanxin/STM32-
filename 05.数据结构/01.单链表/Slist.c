#include "slist.h"

//�����ڵ�
Node* makeNode(const int data)
{
    Node * p = (Node *)malloc(sizeof(Node));
    assert(p != NULL);
    p->data = data;
    p->next = NULL;
    return p;
}

//���ٽڵ�
void destroyNode(Node* node)
{
    free((Node *) node);
}

//��ͷ�ڵ�ĵ�����
void sInit(Slist * list)
{
    list->head = makeNode(INI_MIN);
}

//��˳�����
bool sInsert(Slist * list, const int data)
{
    Node * ptem = list->head;
    Node* current;
    Node * node;
    node = makeNode(data);
    if(ptem->data > data)
    {
        list->head = node;
        node->next = ptem;
    } else {
        while((current = ptem->next) != NULL && current->data < data )
            ptem = ptem->next;
        ptem->next = node;
    }
    return true;
}

//�Ƴ��ڵ�
bool sRemove(Slist * list, const int key)
{
    Node* previous = list->head;
    Node* current;
    //�ҵ�ɾ���ڵ�
    while( ( current = previous->next ) != NULL && current->data != key)
        previous = previous->next;
    if ( current == NULL )
        return false;
    previous->next = current->next;
    free( current );
    return true;
}

//�޸�,��ɾ����룬��Ϊ������������
bool sModify(Slist * list, const int key, const int data)
{
    if( sRemove(list, key) )
        sInsert(list, data);
    else
        return false;
    return true;
}

//�ҵ����عؼ��ֵĽڵ㣬���򷵻�nullָ��
Node* sFind(Slist * list, const int key)
{
    Node * current = list->head;
    while ( (current = current->next) != NULL && current->data != key)
        if( current->data > key )
            return NULL;
    return current;
}

//����
void sTreaverse( Slist * slist, void (*func) (Node* p) )
{
    Node * current = slist->head;
    func(current);
    while ( (current = current->next) != NULL )
        func(current);
}

//���ٽڵ�
void sDestrory(Slist * list)
{
    sTreaverse(list, destroyNode);
    free(list->head);
}

//print
void printData(Node * p)
{
    printf("%d ", p->data);
}

void slist_sample(void)
{
	putchar('\n');
	printf("�������������:\n");
	Slist nlist;
    int num;
    sInit(&nlist); //��ʼ��
    for(num = 1; num < 10; num++)
    {
        sInsert(&nlist, num);  //����
    }
    sTreaverse(&nlist, printData);//������ӡdata
    sRemove(&nlist, 3); //�Ƴ�
    printf("\n");
    sTreaverse(&nlist, printData);
    sModify(&nlist, 8, 44);//�޸�
    printf("\n");
    sTreaverse(&nlist, printData);
}


