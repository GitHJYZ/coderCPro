#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfg_op.h"


#define CFGNAME "c:/mycfg.ini"

void myMenu() {
    printf("=============================\n");
    printf("1 测试写配置文件\n");
    printf("2 测试读配置文件\n");
    printf("0 退出\n");
    printf("=============================\n");
}

//获取配置项
int TGetCfg()
{
    int ret = 0;
    //读配置项
    char name[1024] = { 0 };
    char value[1024] = { 0 };
    int len = 0;
    printf("\n请键入key:");
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

//写配置项
int TWriteCfg()
{
    int ret = 0;
    //写配置项
    char name[1024] = { 0 };
    char value[1024] = { 0 };

    printf("\n请键入key:");
    scanf("%s", name);

    printf("\n请键入value:");
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
        //显示菜单
        scanf("%d", &choice);
        switch (choice)
        {
        case 1: //写配置项
            TWriteCfg();
            break;
        case 2: //读配置项
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
