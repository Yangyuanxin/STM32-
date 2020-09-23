#include "Hash_Table.h"

//ɢ�к���--����ɢ�з�
unsigned hash(char *key)
{
    unsigned hashVal;
    for (hashVal = 0; *key != '\0'; key++)
    {
        hashVal = *key + 31 * hashVal;
    }
    hashVal = 2;
    return hashVal;
}

//��ѯkey
Nodelist *search(char *key)
{
    Nodelist *np;
    for (np = hashTable[hash(key)]; np != NULL; np = np->next)
    {
        if(strcmp(key, np->key) == 0)
            return np;
    }
    return NULL;
}

//���뵽��ϣ��
Nodelist *insert_hash_table(char *key, char *value)
{
    Nodelist *np;
    unsigned hashVal;
    if((np = search(key)) == NULL) 
    {
        np = (Nodelist *) malloc(sizeof(Nodelist));
        if(np == NULL || (np->key = (char *)key) == NULL)
            return NULL;
        np->next = NULL;
        hashVal = hash(key);
        //�����ͬkeyɢ�е�ͬһ��ֵ���������������
        if(hashTable[hashVal] == NULL) {
            hashTable[hashVal] = np;
        }else {
            Nodelist *npTmp = hashTable[hashVal], *preNp;
            while(npTmp != NULL)
            {
                preNp = npTmp;
                npTmp = npTmp->next;
            }
            preNp->next = np;
        }
    } else{
        free((void*)np->value);
    }
    if ((np->value = (char *)value) == NULL)
        return NULL;
    return np;
}

//����key��ȡֵ
char *get_value(char *key)
{
    Nodelist *np;
    unsigned hashVal = hash(key);
    np =  (Nodelist *)hashTable[hashVal];
    while(np != NULL) 
    {
        if(strcmp(key, np->key) == 0) {
            //printf("key:%s value:%s\n", key, np->value);
            return np->value ;
        } 
		else 
		{
            np = np->next;
        }
    }
	return NULL ;
}

void hash_table_sample(void)
{
	putchar('\n');
	insert_hash_table("Name","Yangyx");
	char *value = get_value("Name");  
	printf("���ݼ���ѯ����ֵΪ:%s\n",value);
}
