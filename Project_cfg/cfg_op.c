#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLine 2048

int GetCfgItem(char* pFileName/*in*/, char* pKey /*in*/, char* pValue /*in out*/, int* pValueLen /*out*/)
{
    FILE* fp = NULL;
    int rv = 0;
    char *pTmp = NULL, * pBegin = NULL, * pEnd = NULL;
    char lineBuf[MaxLine];
    fp = fopen(pFileName, "r");
    if (fp == NULL) {
        rv = -1;
        return rv;
    }
    while (!feof(fp)) {
        memset(lineBuf,0,sizeof(lineBuf));
        //fgets(char* _Buffer,int   _MaxCount,FILE * _Stream);
        fgets(lineBuf, MaxLine, fp);
        //printf("lineBuf:%s ", lineBuf);

        pTmp = strchr(lineBuf, '=');
        if (pTmp == NULL) // 没有 = 号
        {
            continue;
        }

        pTmp = strstr(lineBuf, pKey);
        if (pTmp == NULL) // 判断所在行有没key
        {
            continue;
        }
        pTmp = pTmp + strlen(pKey);//mykey1 = myvalue1 ==>  = myvalue1

        pTmp = strchr(pTmp, '=');
        if (pTmp == NULL) // 判断所在行有没key
        {
            continue;
        }
        pTmp = pTmp + 1; // = myvalue1 ==> myvalue1

        //printf("pTmp:%s ", pTmp);

        while (1) {
            if (*pTmp == ' ')
            {
                pTmp++;
            }
            else {
                pBegin = pTmp;
                if (pBegin == (char *)'\n') {
                    //没有配置value
                    printf("配置项：%s 没有配置value \n", pKey);
                    goto End;
                }
                break;
            }
        }
        //获取value 结束点
        while (1) {
            if (*pTmp == ' ' || *pTmp == '\n') {
                break;
            }
            else {
                pTmp++;
            }
        }
        pEnd = pTmp;

        //赋值
        *pValueLen = pEnd - pBegin;
        memcpy(pValue, pBegin, pEnd - pBegin);
        break;
    }
End:
    if (fp != NULL) {
        fclose(fp);
    }
    return rv;
}

//写配置项
//实现流程
//循环读每一行，检查key配置项是否存在 若存在则修改
//若不存在，文件末尾 添加key = value
//难点，如何修改文件流中的值

int WriteCfgItem(char* pFileName/*in*/, char* pKey /*in*/, char* pValue /*in*/, int ValueLen /*in*/)
{
    int rv = 0, iTag = 0, length = 0;
    FILE* fp = NULL;
    char lineBuf[MaxLine];
    char * pTmp = NULL, * pBegin = NULL, * pEnd = NULL;
    char filebuf[1024 * 8] = { 0 };

    if (pFileName == NULL || pKey == NULL || pValue == NULL)
    {
        rv = -1;
        printf("SetCfgItem() err. param err \n");
        goto End;
    }
    fp = fopen(pFileName, "r+");
    if (fp == NULL)
    {
        rv = -2;
        printf("fopen() err. \n");
    }

    if (fp == NULL)
    {
        fp = fopen(pFileName, "w+t");
        if (fp == NULL)
        {
            rv = -3;
            printf("fopen() err.\n");
            goto End;
        }
    }
    fseek(fp, 0L, SEEK_END); //把文件指针从0位置开始，移动到文件末尾
    //获取文件长度
    length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if (length > 1024 * 8)
    {
        rv = -3;
        printf("文件超过1024*8，unsupport\n");
        goto End;
    }
    while (!feof(fp))
    {
        //读每一行
        memset(lineBuf, 0, sizeof(lineBuf));
        pTmp = fgets(lineBuf, MaxLine, fp);
        if (pTmp == NULL)
        {
            break;
        }
        //key 关键字是否在本行
        pTmp = strstr(lineBuf, pKey);
        if (pTmp == NULL) //key 关键字不在本行，copy到filebuf中
        {
            strcat(filebuf, lineBuf);
            continue;
        }
        else //key 关键字在本行，替换旧的行，再copy到filebuf中
        {
            sprintf(lineBuf, "%s = %s\n", pKey, pValue);
            strcat(filebuf, lineBuf);
            //若存在key
            iTag = 1;
        }
    }

    // 若key 关键字，不存在 追加
    if (iTag == 0)
    {
        fprintf(fp, "%s = %s \n", pKey, pValue);
    }
    else //若key 关键字存在，则重新创建文件
    {
        if (fp != NULL)
        {
            fclose(fp);
            fp = NULL; //避免野指针
        }
        fp = fopen(pFileName, "w+t");
        if (fp == NULL)
        {
            rv = -4;
            printf("fopen() err. \n");
            goto End;
        }
        fputs(filebuf, fp);
        //fwrite(filebuf,sizeof(char),strlen(filebuf),fp);
    }

End:
    if (fp != NULL)
    {
        fclose(fp);
    }
    return rv;
}