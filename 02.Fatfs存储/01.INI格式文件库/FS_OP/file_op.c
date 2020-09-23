#include "file_op.h"
#include "fatfs.h"


uint8_t work[_MAX_SS] ;
RECORD_PARA csv_file_record ;



//�����ļ�ϵͳ
void Mount_Fatfs(void)
{
    retUSER = f_mount(&USERFatFS, USERPath, 1);

    if(retUSER != FR_OK)
    {
        if(retUSER == FR_NO_FILESYSTEM)
        {
            printf("f_mount û���ļ�ϵͳ,��ʼ��ʽ��spi-flash\r\n");
            retUSER = f_mkfs(USERPath, FM_ANY, 0, work, sizeof(work));

            if(retUSER != FR_OK)
            {
                printf("f_mkfs ��ʽ��ʧ�ܣ�err = %d\r\n", retUSER);
            }
            else
            {
                printf("��ʽ���ɹ�����ʼ���¹���spi-flash\r\n");
                retUSER = f_mount(&USERFatFS, USERPath, 1);

                if(retUSER != FR_OK)
                {
                    printf("f_mount ��������err = %d\r\n", retUSER);
                }
                else
                {
                    printf("spi-flash�ļ�ϵͳ���سɹ�\r\n");
                }
            }
        }
        else
        {
            printf("f_mount ������������err = %d\r\n", retUSER);
        }
    }
    else
        printf("spi-flash�ļ�ϵͳ���سɹ�\r\n");
}


/*����ļ�ϵͳ����*/
void UMount_Fatfs(void)
{
    printf("����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ\r\n");
    retUSER = f_mount(NULL, USERPath, 1);

    if(retUSER == FR_OK)
        printf("ȡ�������ļ�ϵͳ�ɹ�\r\n");
    else
        printf("ȡ�������ļ�ϵͳʧ�ܣ�err = %d\r\n", retUSER);
}

/*ɾ������¼*/
int Detele_Detect_Log(void)
{
    //ɾ���ļ�
    retUSER = f_unlink(DETECT_CSV);

    if(FR_OK != retUSER)
    {
        //ɾ���ļ�ʧ��
        printf("ɾ���ļ�ʧ��! %d\n", retUSER);
        return -2 ;
    }

    return 0 ;
}


/*���������ݵ�csv�ļ���*/
int save_record_to_flash(void)
{
    uint32_t count = 0  ;
    char filename[FILE_NAME_LEN] = {0};
    char Detect_Data[100] = {0} ;
    /*���㵱ǰ��ˮ��һ�����Բ������ٸ��ļ���һ���ļ�����100����¼�����Զ������µ��ļ�*/
    int data_serial_num_file_count =  User_Memory_Para.Detect_Log_Serial_Number / DETECT_DATA_INDEX ;
    sprintf(filename, "0:SRED_EHS%d.csv", data_serial_num_file_count);
    retUSER = f_open(&USERFile, filename, FA_OPEN_ALWAYS | FA_WRITE);

    if(FR_OK != retUSER)
    {
        printf("��/����%s�ļ�ʧ�ܣ�err = %d\r\n", filename, retUSER);
        return -1 ;
    }

    printf("��/����%s�ļ��ɹ������ļ�д�����ݡ�\r\n", filename);
    /*ÿһ�ζ�ƫ�Ƶ��ļ���ĩβ*/
    f_lseek(&USERFile, f_size(&USERFile));
    /*��ˮ������*/
    ++User_Memory_Para.Detect_Log_Serial_Number;
    /*��¼��ˮ�ű��洦��*/
    User_Detect_Log_Save_Process();

    /*���ɨ��OK�����¼��������Լ�ɨ��õ�������*/
    if(1 == Scan_ok_flag)
    {
        sprintf(Detect_Data, "%d,%2d/%02d/%02d %02d:%02d,%d,%s\r\n",
                User_Memory_Para.Detect_Log_Serial_Number, current_time.year, current_time.month,	\
                current_time.day, current_time.hour, current_time.minute, sensor_data.Is_Drug_or_Explosive, sensor_data.Scan_Data);
        memset((char *)sensor_data.Scan_Data, 0, 50);
    }
    else
    {
        sprintf(Detect_Data, "%d,%2d/%02d/%02d %02d:%02d,%d\r\n",
                User_Memory_Para.Detect_Log_Serial_Number, current_time.year, current_time.month,	\
                current_time.day, current_time.hour, current_time.minute, sensor_data.Is_Drug_or_Explosive);
    }

    retUSER = f_write(&USERFile, Detect_Data, strlen((char *)Detect_Data), &count);

    if(retUSER != FR_OK)
    {
        printf("f_write ��������err = %d\r\n", retUSER);
        printf("�رմ򿪵�SRED_EHS.csv�ļ�\r\n");
        count = 0;
        memset(Detect_Data, 0, DETECT_DATA_LEN);
        memset(Scaner.ScanerU5Buffer, 0, USART_REC_LEN);
        f_close(&USERFile);
        return -2 ;
    }

    printf("�ļ�д��ɹ���д���ֽ����ݣ�%d\n", count);
    printf("���ļ�д�������Ϊ��\r\n%s\r\n", Detect_Data);
    printf("�رմ򿪵�SRED_EHS.csv�ļ�\r\n");
    count = 0;
    memset(Detect_Data, 0, DETECT_DATA_LEN);
    memset(Scaner.ScanerU5Buffer, 0, USART_REC_LEN);
    f_close(&USERFile);
    return 0 ;
}

int flseek(FIL* fp, long offset, int whence)
{
    int error = 0 ;
    int value = 0 ;

    switch(whence)
    {
        case SEEK_SET:
            value = 0 ;
            break ;

        case SEEK_CUR:
            value = f_tell(fp) ;
            break ;

        case SEEK_END:
            value = f_size(fp) ;
            break ;

        default:
            error = -1 ;
            return error ;
    }

    error = f_lseek(fp, value + offset);

    if(error != FR_OK) return -2 ;

    return 0 ;
}

/*����ĳ��csv�ļ���������*/
int GetDetectTotalLineCount(char *Path)
{
    int line_num = 0 ;
    char *strLine = NULL ;
    /*��̬����50���ֽڵ��ڴ棬Ĭ�ϴ��ڲ�sram����*/
    strLine = malloc(100);
    assert_param(NULL != strLine);
    memset(strLine, 0, 100);
    retUSER = f_open(&USERFile, Path, FA_OPEN_EXISTING | FA_READ);

    if(FR_OK != retUSER)
    {
        printf("��ǰ�ļ�:%s������\n", Path);
        return -1 ;
    }

    flseek(&USERFile, 0, SEEK_SET);

    while(f_gets(strLine, 100, &USERFile))
    {
        line_num++ ;
    }

    flseek(&USERFile, 0, SEEK_SET);
    f_close(&USERFile);
    //�ͷ��ڴ棬�����ڴ�й¶
    free(strLine);
    return line_num ;
}



int ReadlLineData(int File_Count, int line_number)
{
    int WhichLine ;              //ָ��Ҫ��ȡ��һ��
    int CurrentIndex = 0;        //��ǰ��ȡ����
    char *StrLine = NULL ;
    char *ptr = NULL ;
    int data_serial_num_file_count ;
    char filename[FILE_NAME_LEN] = {0};
    WhichLine = line_number - 1;
    StrLine = malloc(100) ;
    assert_param(NULL != strLine);
    /*���㵱ǰ����ˮ������Ӧ���ļ�*/
    data_serial_num_file_count = File_Count ;
    sprintf(filename, "0:SRED_EHS%d.csv", data_serial_num_file_count);
    retUSER = f_open(&USERFile, filename, FA_OPEN_EXISTING | FA_READ);

    if(FR_OK != retUSER)
    {
        printf("��%s�ļ�ʧ�ܣ�err = %d\r\n", filename, retUSER);
        free(StrLine);
        return -2;
    }

    memset(csv_file_record.Scan_Data, 0, 100);

    while(!f_eof(&USERFile))
    {
        if(CurrentIndex == WhichLine)
        {
            //��ȡһ��
            f_gets(StrLine, 100, &USERFile);
            printf("��ǰ����:%s\n", StrLine);
            //Para1:��ȡ��ˮ��
            csv_file_record.serial_number = atoi(StrLine);
            //Para2:��ȡ��
            ptr = strstr(StrLine, ",");
            csv_file_record.year = atoi(ptr + 1);
            //Para3:��ȡ��
            ptr = strstr(ptr + 1, "/");
            csv_file_record.month = atoi(ptr + 1);
            //Para4:��ȡ��
            ptr = strstr(ptr + 1, "/");
            csv_file_record.day = atoi(ptr + 1);
            //Para5:��ȡʱ
            ptr = strstr(ptr + 1, " ");
            csv_file_record.hour = atoi(ptr + 1);
            //Para6:��ȡ��
            ptr = strstr(ptr + 1, ":");
            csv_file_record.minute = atoi(ptr + 1);
            //Para7:��ȡͨ��������===>Ϊ0���Ƕ�Ʒ��Ϊ1���Ǳ�ը��
            ptr = strstr(ptr + 1, ",");
            csv_file_record.detect_result = atoi(ptr + 1);
            /*���ɨ��������ʾ*/
            //Para8:��ȡɨ����
            ptr = strstr(ptr + 1, ",");

            if(ptr != NULL)
                memcpy(csv_file_record.Scan_Data, ptr + 1, strlen(ptr));
        }

        //��ȡһ��,����λ����һ��
        f_gets(StrLine, 100, &USERFile);
        CurrentIndex++;
    }

    f_close(&USERFile);
    free(StrLine);
    return CurrentIndex ;
}



















