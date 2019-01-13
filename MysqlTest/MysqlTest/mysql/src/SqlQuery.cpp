#include "SqlQuery.h"

CSqlQuery::CSqlQuery() {
	mpCb = nullptr;
	mpCbParam = nullptr;
	mpSqlReult = nullptr;
}

CSqlQuery::~CSqlQuery() {
	CleanQueryStr();
	if (nullptr != mpSqlReult) {
		DODELETE(mpSqlReult);
	}
}

void CSqlQuery::SetCb(sql_callback pCb, void* pCbParam) {
	mpCb = pCb;
	mpCbParam = pCbParam;
}

void CSqlQuery::CleanQueryStr() {
	while (!mqueQueryStr.empty()) {
		len_str tmpStr = mqueQueryStr.front();
		mqueQueryStr.pop();
		DOFREE(tmpStr.pStr);
	}
}

len_str CSqlQuery::PopQueryStr() {
	len_str tmpStr;
	if (mqueQueryStr.empty()) {
		tmpStr.pStr = nullptr;
		tmpStr.iLen = 0;
	} else {
		tmpStr = mqueQueryStr.front();
		mqueQueryStr.pop();
	}

	return tmpStr;
}

int CSqlQuery::AddQuery(unsigned char* pQueryStr, size_t iLen) {
	ASSERT_RET_VALUE(nullptr != pQueryStr && iLen > 0, 1);
	len_str tmpStr;
	tmpStr.iLen = iLen;
	tmpStr.pStr = (unsigned char*)malloc(iLen * sizeof(unsigned char) + 1);
	memcpy(tmpStr.pStr, pQueryStr, iLen);
	tmpStr.pStr[iLen] = '\0';
	mqueQueryStr.push(tmpStr);
	return 0;
}

int CSqlQuery::HandleQueryReult(MYSQL_RES *pResult) {
	ASSERT_RET_VALUE(nullptr != pResult, 1);
	if (nullptr == mpSqlReult) {
		mpSqlReult = new CSqlResult();
	}

	ASSERT_RET_VALUE(nullptr != mpSqlReult, 1);

	return mpSqlReult->HandleQueryReult(pResult);
}