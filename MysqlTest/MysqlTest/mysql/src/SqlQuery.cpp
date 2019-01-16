#include "SqlQuery.h"

CSqlQuery::CSqlQuery() {
	mpCb = NULL;
	mpCbParam = NULL;
}

CSqlQuery::~CSqlQuery() {
	Clean();
}

std::string CSqlQuery::SetCb(sql_callback pCb, void* pCbParam) {
	mpCb = pCb;
	mpCbParam = pCbParam;
    mstrGuid = sGuidTool->CreateGuid();
    return mstrGuid;
}

void CSqlQuery::Clean() {
	while (!mqueQueryStr.empty()) {
		len_str tmpStr = mqueQueryStr.front();
		mqueQueryStr.pop();
		DOFREE(tmpStr.pStr);
	}
}

len_str CSqlQuery::PopQueryStr() {
	len_str tmpStr;
	if (mqueQueryStr.empty()) {
		tmpStr.pStr = NULL;
		tmpStr.iLen = 0;
	} else {
		tmpStr = mqueQueryStr.front();
		mqueQueryStr.pop();
	}

	return tmpStr;
}

int CSqlQuery::AddQuery(char* pQueryStr, size_t iLen) {
	ASSERT_RET_VALUE(NULL != pQueryStr && iLen > 0, 1);
	len_str tmpStr;
	tmpStr.iLen = iLen;
	tmpStr.pStr = (char*)malloc(iLen * sizeof(char)); 
	memcpy(tmpStr.pStr, pQueryStr, iLen);
	mqueQueryStr.push(tmpStr);
	return 0;
}