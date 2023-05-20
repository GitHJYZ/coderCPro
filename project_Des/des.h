/*********************************************************
 *  des.h
 *  DES 加密算法头文件
 *********************************************************/
#ifndef _DES_H_
#define _DES_H_

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief des_encode_raw DES 加密操作 , 加密 4096 字节数据
     * @param in_data 输入数据
     * @param in_data_len 输入数据长度
     * @param out_data 输出数据
     * @param out_data_len 输出数据长度
     * @return
     */
    int des_encode_raw(
        unsigned char* in_data,
        int            in_data_len,
        unsigned char* out_data,
        int* out_data_len);

    /**
     * @brief des_encode DES 加密操作 , 加密少于 4096 字节数据
     * @param in_data 输入数据
     * @param in_data_len 输入数据长度
     * @param out_data 输出数据
     * @param out_data_len 输出数据长度
     * @return
     */
    int des_encode(
        unsigned char* in_data,
        int            in_data_len,
        unsigned char* out_data,
        int* out_data_len);




    /**
     * @brief des_decode_raw DES 解密操作 , 解密 4096 字节
     * @param in_data 输入数据
     * @param in_data_len 输入数据长度
     * @param out_data 输出数据
     * @param out_data_len 输出数据长度
     * @return
     */
    int des_decode_raw(
        unsigned char* in_data,
        int            in_data_len,
        unsigned char* out_data,
        int* out_data_len);

    /**
     * @brief des_decode DES 解密操作 , 解密少于 4096 字节
     * @param in_data 输入数据
     * @param in_data_len 输入数据长度
     * @param out_data 输出数据
     * @param out_data_len 输出数据长度
     * @return
     */
    int des_decode(
        unsigned char* in_data,
        int            in_data_len,
        unsigned char* out_data,
        int* out_data_len);

#ifdef __cplusplus
}
#endif

#endif
