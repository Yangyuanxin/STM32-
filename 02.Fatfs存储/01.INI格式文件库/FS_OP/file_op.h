#ifndef __FILE_OP_H
#define __FILE_OP_H
#include "main.h"
//�������¼��csv�ļ�
#define DETECT_CSV "0:SRED_EHS.csv"
//�������ò���
#define SETTING_PARA "0:Para.ini"
//����WIFI�ʺ�
#define WIFI_CONFIG_TXT    "0:SRED_EHS_WIFI_CONFIG.txt"

//������ݴ�С����
#define DETECT_DATA_LEN 50
//�ļ�����С����
#define FILE_NAME_LEN 20
//һ���ļ��洢����¼������
#define DETECT_DATA_INDEX 100

//��¼ҳ���ȡ��������
typedef struct Record_Page_Data
{
    int serial_number ; 		//���
    int year ; 					//2019-
    uint8_t month ; 			//0-12
    uint8_t day ;				//0-31
    uint8_t hour ; 				//0-24
    uint8_t minute ;			//0-59
    int  detect_result ;		//�����
    char Scan_Data[100];			//ɨ����

    /*��ǰλ���ļ�����һ��*/
    __IO int Current_Line;
    /*��ǰ�ļ���Ų�ѯ����*/
    __IO int file_number_index ;
    /*��ǰ��ˮ�ţ�ÿ�μ�¼��ʼ����ʱ��ḳֵһ��*/
    __IO int Current_Serial_Number ;
} RECORD_PARA;

extern RECORD_PARA csv_file_record ;

void Mount_Fatfs(void);
void UMount_Fatfs(void);




/*ɾ����¼����*/
int Detele_Detect_Log(void);
/*��¼���ݱ���*/
int save_record_to_flash(void);
/*����ĳ��csv�ļ���������*/
int GetDetectTotalLineCount(char *Path);
/*��ǰ�����ȡһ������*/
int ReadlLineData(int File_Count, int line_number);


#endif //__FILE_OP_H
