#ifndef __SENSOR_H
#define __SENSOR_H
#include "main.h"

/*�������汾*/
/*
	0��˫ͨ��
	1: ��ͨ������ǿ
	2: ��ͨ��������ǿ
*/
#define SENSOR_VERSION 0

/*���������ݽṹ*/
typedef struct
{
    int Serial_Number 	 ;	/*���*/
    int Tp1_Signal_Value ;	/*ͨ��1�ź�ֵ*/
    int Tp1_Devalue 	 ;	/*ͨ��1��ֵ*/
    int Tp2_Signal_Value ;	/*ͨ��2�ź�ֵ*/
    int Tp2_Devalue 	 ;	/*ͨ��2��ֵ*/
    int Tp1_Light_Value  ;	/*ͨ��1��ǿ*/
    int Tp2_Light_Value  ;	/*ͨ��2��ǿ*/
} Sensor_Data_Format      ;
extern __IO Sensor_Data_Format sensor_data ;


/*����˫ͨ�����ݸ�ʽ�ṹ��*/
typedef struct
{
    int Para1 ;
    int Para2 ;
    int Para3 ;
    int Para4 ;
    int Para5 ;
    int Para6 ;
    int Para7 ;
} Parse_Double_Passage_Data_Format ;

/*������ͨ������ǿ���ݸ�ʽ�ṹ��*/
typedef struct
{
    int Para1 ;
    int Para2 ;
    int Para3 ;
    int Para4 ;
} Parse_Single_Passage_Have_Light_Value ;

/*������ͨ��������ǿ���ݸ�ʽ�ṹ��*/
typedef struct
{
    int Para1 ;
    int Para2 ;
    int Para3 ;
} Parse_Single_Passage_DHave_Light_Value ;

/*��ȡ����������*/
void Get_Sensor_Data(char *data, Sensor_Data_Format *sensor_data);


#endif //__SENSOR_H

