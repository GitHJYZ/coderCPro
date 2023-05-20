/*********************************************************
 *  des.h
 *  DES �����㷨ͷ�ļ�
 *********************************************************/
#ifndef _DES_H_
#define _DES_H_

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief des_encode_raw DES ���ܲ��� , ���� 4096 �ֽ�����
     * @param in_data ��������
     * @param in_data_len �������ݳ���
     * @param out_data �������
     * @param out_data_len ������ݳ���
     * @return
     */
    int des_encode_raw(
        unsigned char* in_data,
        int            in_data_len,
        unsigned char* out_data,
        int* out_data_len);

    /**
     * @brief des_encode DES ���ܲ��� , �������� 4096 �ֽ�����
     * @param in_data ��������
     * @param in_data_len �������ݳ���
     * @param out_data �������
     * @param out_data_len ������ݳ���
     * @return
     */
    int des_encode(
        unsigned char* in_data,
        int            in_data_len,
        unsigned char* out_data,
        int* out_data_len);




    /**
     * @brief des_decode_raw DES ���ܲ��� , ���� 4096 �ֽ�
     * @param in_data ��������
     * @param in_data_len �������ݳ���
     * @param out_data �������
     * @param out_data_len ������ݳ���
     * @return
     */
    int des_decode_raw(
        unsigned char* in_data,
        int            in_data_len,
        unsigned char* out_data,
        int* out_data_len);

    /**
     * @brief des_decode DES ���ܲ��� , �������� 4096 �ֽ�
     * @param in_data ��������
     * @param in_data_len �������ݳ���
     * @param out_data �������
     * @param out_data_len ������ݳ���
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
