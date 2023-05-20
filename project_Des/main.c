#define  _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "des.h"

/**
 * @brief file_encode 文件加密
 * @param input_file   被加密的文件
 * @param output_file  加密后的文件
 * @return
 */
int file_encode(const char* input_file, const char* output_file)
{
    // 用于接收各个步骤的返回值 , 做校验
    int ret = 0;

    // 输入 文件 指针
    FILE* fp_in = NULL;

    // 输出 文件 指针
    FILE* fp_out = NULL;

    // 输入缓冲区 , 大小 4K
    unsigned char input_buffer[4096] = { 0 };

    // 输入数据字节数
    int input_len = 0;

    // 输出文件缓冲区
    unsigned char output_buffer[4096] = { 0 };

    // 输出数据字节数
    int output_len = 0;

    // 输出数据写出字节数 , 用于与上面的 output_len 进行对比
    // 一般情况下这两个值相等 , 如果出错 , 直接退出程序
    int output_tmplen;

    // 打开输入文件
    fp_in = fopen(input_file, "rb");
    if (fp_in == NULL)
    {
        goto END;
    }

    // 打开输出文件
    fp_out = fopen(output_file, "wb");
    if (fp_out == NULL)
    {
        goto END;
    }

    // 循环读取输入文件中的数据
    while (!feof(fp_in))
    {
        // 尝试从输入文件中读取 4K 数据
        input_len = fread(input_buffer, 1, 4096, fp_in);
        // 如果读取完毕 , 直接退出
        if (feof(fp_in))
        {
            break;
        }

        // 加密 4096 字节数据
        ret = des_encode_raw(input_buffer, input_len, output_buffer, &output_len);
        // 如果加密失败, 直接退出
        if (ret != 0)
        {
            printf("error : des_encode_raw \n", ret);
            goto END;
        }

        // 将加密后的数据 , 写出到输出文件中
        output_tmplen = fwrite(output_buffer, 1, output_len, fp_out);
        // 如果写出失败 , 直接退出
        if (output_tmplen != output_len)
        {
            ret = -3;
            printf("error : fwrite\n");
            goto END;
        }
    }

    // 加密小于 4096 字节数据
    ret = des_encode(input_buffer, input_len, output_buffer, &output_len);
    // 加密失败 , 直接退出
    if (ret != 0)
    {
        printf("error : des_encode \n", ret);
        goto END;
    }

    // 将加密后的数据 , 写出到输出文件中
    output_tmplen = fwrite(output_buffer, 1, output_len, fp_out);
    // 如果写出失败 , 直接退出
    if (output_len != output_tmplen)
    {
        ret = -3;
        printf("error : fwrite\n");
        goto END;
    }

END:
    // 关闭输入文件
    if (fp_in != NULL)
    {
        fclose(fp_in);
    }
    // 关闭输出文件
    if (fp_out != NULL)
    {
        fclose(fp_out);
    }
    return 0;
}

int main_encode()
{
    // 接收 子函数 返回值
    int ret = 0;

    // 要加密的文件
    const char* input_file = "D:/File/config.ini";

    // 加密后的文件
    const char* output_file = "D:/File/config_encode.ini";

    // 将 要加密的 input_file 文件加密 , 并输出到 output_file 文件中
    ret = file_encode(input_file, output_file);

    // 加密失败
    if (ret != 0)
    {
        printf("error : file_encoder\n ");
        return ret;
    }

    system("pause");
    return ret;
}

/**
 * @brief file_decode 文件解密
 * @param input_file   被加密的文件
 * @param output_file  加密后的文件
 * @return
 */
int file_decode(const char* input_file, const char* output_file)
{
    // 用于接收各个步骤的返回值 , 做校验
    int ret = 0;

    // 输入 文件 指针
    FILE* fp_in = NULL;

    // 输出 文件 指针
    FILE* fp_out = NULL;

    // 输入缓冲区 , 大小 4K
    unsigned char input_buffer[4096] = { 0 };

    // 输入数据字节数
    int input_len = 0;

    // 输出文件缓冲区
    unsigned char output_buffer[4096] = { 0 };

    // 输出数据字节数
    int output_len = 0;

    // 输出数据写出字节数 , 用于与上面的 output_len 进行对比
    // 一般情况下这两个值相等 , 如果出错 , 直接退出程序
    int output_tmplen;

    // 打开输入文件
    fp_in = fopen(input_file, "rb");
    if (fp_in == NULL)
    {
        goto END;
    }

    // 打开输出文件
    fp_out = fopen(output_file, "wb");
    if (fp_out == NULL)
    {
        goto END;
    }

    // 循环读取输入文件中的数据
    while (!feof(fp_in))
    {
        // 尝试从输入文件中读取 4K 数据
        input_len = fread(input_buffer, 1, 4096, fp_in);
        // 如果读取完毕 , 直接退出
        if (feof(fp_in))
        {
            break;
        }

        // 解密 4096 字节数据
        ret = des_decode_raw(input_buffer, input_len, output_buffer, &output_len);
        // 如果加密失败, 直接退出
        if (ret != 0)
        {
            printf("error : des_encode_raw \n", ret);
            goto END;
        }

        // 将解密后的数据 , 写出到输出文件中
        output_tmplen = fwrite(output_buffer, 1, output_len, fp_out);
        // 如果写出失败 , 直接退出
        if (output_tmplen != output_len)
        {
            ret = -3;
            printf("error : fwrite\n");
            goto END;
        }
    }

    // 解密小于 4096 字节数据
    ret = des_decode(input_buffer, input_len, output_buffer, &output_len);
    // 加密失败 , 直接退出
    if (ret != 0)
    {
        printf("error : des_decode \n", ret);
        goto END;
    }

    // 将解密后的数据 , 写出到输出文件中
    output_tmplen = fwrite(output_buffer, 1, output_len, fp_out);
    // 如果写出失败 , 直接退出
    if (output_len != output_tmplen)
    {
        ret = -3;
        printf("error : fwrite\n");
        goto END;
    }

END:
    // 关闭输入文件
    if (fp_in != NULL)
    {
        fclose(fp_in);
    }
    // 关闭输出文件
    if (fp_out != NULL)
    {
        fclose(fp_out);
    }
    return 0;
}


int main_decode()
{
    // 接收 子函数 返回值
    int ret = 0;

    // 要解密的文件
    const char* input_file = "D:/File/config_encode.ini";

    // 解密后的文件
    const char* output_file = "D:/File/config_decode.ini";

    // 将 要加密的 input_file 文件加密 , 并输出到 output_file 文件中
    ret = file_decode(input_file, output_file);

    // 加密失败
    if (ret != 0)
    {
        printf("error : file_encoder\n ");
        return ret;
    }

    system("pause");
    return ret;
}


int main()
{
    // 文件加密
    //main_encode();

    // 文件解密
    main_decode();

    system("pause");
    return 0;
}
