#pragma once
#ifndef CFG_OP_H__
#define CFG_OP_H__

#ifdef __cplusplus
extern "C" {
#endif

	//ªÒ»°≈‰÷√œÓ
	int GetCfgItem(char* pFileName/*in*/, char* pKey /*in*/, char* pValue /*in out*/, int* pValueLen /*out*/);

	int WriteCfgItem(char* pFileName/*in*/, char* pItemName /*in*/, char* pItemValue /*in*/, int* itemValueLen /*in*/);

#ifdef __cplusplus
}
#endif

#endif