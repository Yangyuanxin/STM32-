#ifndef __HEATER_H
#define __HEATER_H
#include "main.h"

#define STATUS_1 1	/*����δ�ȶ�*/
#define STATUS_2 2	/*����δ�ȶ�����ֽ����*/
#define STATUS_3 3	/*�����ȶ�*/
#define STATUS_4 4	/*�����ȶ�����ֽ����*/

/*���������ݽṹ*/
typedef struct
{
    int Heater_Serial_Number 	 ;	/*���������*/
    int Heater_Signal_Value  	 ;	/*�������ź�ֵ*/
    int Heater_Devalue 		 	 ;	/*��������ֵ*/
    int Heater_Status_Bit 	 	 ;	/*������״̬λ*/
} Heater_Data_Format			 ;
extern __IO Heater_Data_Format heater_data ;

/*�������������ݸ�ʽ�ṹ��*/
typedef struct
{
    int Para1 ;
    int Para2 ;
    int Para3 ;
    int Para4 ;
} Parse_Heater_Data ;

/*��ȡ����������*/
void Get_Heater_Data(char *data, Heater_Data_Format *heater_data);

#endif //__HEATER_H
