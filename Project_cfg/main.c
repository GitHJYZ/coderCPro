#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfg_op.h"


#define CFGNAME "c:/mycfg.ini"

void myMenu() {
    printf("=============================\n");
    printf("1 ����д�����ļ�\n");
    printf("2 ���Զ������ļ�\n");
    printf("0 �˳�\n");
    printf("=============================\n");
}

//��ȡ������
int TGetCfg()
{
    int ret = 0;
    //��������
    char name[1024] = { 0 };
    char value[1024] = { 0 };
    int len = 0;
    printf("\n�����key:");
    scanf("%s", name);

    ret = GetCfgItem(CFGNAME, name, value, &len);
    if (ret != 0)
    {
        printf("func GetCfgItem err %d \n", ret);
        return ret;
    }
    printf("value = %s\n", value);
    return ret;
}

//д������
int TWriteCfg()
{
    int ret = 0;
    //д������
    char name[1024] = { 0 };
    char value[1024] = { 0 };

    printf("\n�����key:");
    scanf("%s", name);

    printf("\n�����value:");
    scanf("%s", value);

    ret = WriteCfgItem(CFGNAME, name, value, (int*)strlen(value));
    if (ret != 0)
    {
        printf("func WriteCfgItem err %d \n", ret);
        return ret;
    }
    printf("%s = %s\n", name, value);
    return ret;
}
void main()
{
    int choice;
    myMenu();
    for (;;) {
        //��ʾ�˵�
        scanf("%d", &choice);
        switch (choice)
        {
        case 1: //д������
            TWriteCfg();
            break;
        case 2: //��������
            TGetCfg();
            break;
        case 0:
            exit(0);
            break;
        default:;
            exit(0);
        }
    }

    printf("hello...\n");
    system("pause");
    return;
}
