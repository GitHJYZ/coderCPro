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
        if (pTmp == NULL) // û�� = ��
        {
            continue;
        }

        pTmp = strstr(lineBuf, pKey);
        if (pTmp == NULL) // �ж���������ûkey
        {
            continue;
        }
        pTmp = pTmp + strlen(pKey);//mykey1 = myvalue1 ==>  = myvalue1

        pTmp = strchr(pTmp, '=');
        if (pTmp == NULL) // �ж���������ûkey
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
                    //û������value
                    printf("�����%s û������value \n", pKey);
                    goto End;
                }
                break;
            }
        }
        //��ȡvalue ������
        while (1) {
            if (*pTmp == ' ' || *pTmp == '\n') {
                break;
            }
            else {
                pTmp++;
            }
        }
        pEnd = pTmp;

        //��ֵ
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

//д������
//ʵ������
//ѭ����ÿһ�У����key�������Ƿ���� ���������޸�
//�������ڣ��ļ�ĩβ ���key = value
//�ѵ㣬����޸��ļ����е�ֵ

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
    fseek(fp, 0L, SEEK_END); //���ļ�ָ���0λ�ÿ�ʼ���ƶ����ļ�ĩβ
    //��ȡ�ļ�����
    length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if (length > 1024 * 8)
    {
        rv = -3;
        printf("�ļ�����1024*8��unsupport\n");
        goto End;
    }
    while (!feof(fp))
    {
        //��ÿһ��
        memset(lineBuf, 0, sizeof(lineBuf));
        pTmp = fgets(lineBuf, MaxLine, fp);
        if (pTmp == NULL)
        {
            break;
        }
        //key �ؼ����Ƿ��ڱ���
        pTmp = strstr(lineBuf, pKey);
        if (pTmp == NULL) //key �ؼ��ֲ��ڱ��У�copy��filebuf��
        {
            strcat(filebuf, lineBuf);
            continue;
        }
        else //key �ؼ����ڱ��У��滻�ɵ��У���copy��filebuf��
        {
            sprintf(lineBuf, "%s = %s\n", pKey, pValue);
            strcat(filebuf, lineBuf);
            //������key
            iTag = 1;
        }
    }

    // ��key �ؼ��֣������� ׷��
    if (iTag == 0)
    {
        fprintf(fp, "%s = %s \n", pKey, pValue);
    }
    else //��key �ؼ��ִ��ڣ������´����ļ�
    {
        if (fp != NULL)
        {
            fclose(fp);
            fp = NULL; //����Ұָ��
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