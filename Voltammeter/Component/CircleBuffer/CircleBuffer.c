#include "CircleBuffer.h"

void CircleBuffer_Init(sCircleBuffer* pCBuf, uint32_t Len, CBuf_Type* Buf) {
	pCBuf->pRead = 0;
	pCBuf->pWrite = 0;
	pCBuf->len = Len;
	pCBuf->buf = Buf;
}

uint8_t CircleBuffer_Read(sCircleBuffer* pCBuf, CBuf_Type* Val) {
	/* �������ǿ� */
	if (pCBuf->pRead != pCBuf->pWrite) {
		*Val = pCBuf->buf[pCBuf->pRead];
		pCBuf->pRead++;
		
		/* ��������ͷ����ת����ʼλ�ã��γɻ�· */	
		if (pCBuf->pRead == pCBuf->len) {
			pCBuf->pRead = 0;
		}
		return 1;
	} else {
		return 0;
	}
}

uint8_t CircleBuffer_Write(sCircleBuffer* pCBuf, CBuf_Type Val) {
	uint32_t next_w = pCBuf->pWrite + 1;
	
	/* ��������ͷ����ת����ʼλ�ã��γɻ�· */	
	if (next_w == pCBuf->len) {
		next_w = 0;
	}
	
	/* ������δ����д������ */
	if (next_w != pCBuf->pRead) {
		pCBuf->buf[pCBuf->pWrite] = Val;
		pCBuf->pWrite = next_w;
		return 1;
	} else {
		return 0;	
	}
}
