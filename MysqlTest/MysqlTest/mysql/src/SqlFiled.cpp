#include "SqlFiled.h"

CSqlFiled::CSqlFiled(char* pData, unsigned long lDataLen, enum_field_types iType){
	mpData = pData;
	miType = iType;
    mlDataLen = lDataLen;
}

CSqlFiled::~CSqlFiled(){
}

short CSqlFiled::GetShort() {
	ASSERT_RET_VALUE(mpData && mlDataLen >0 && MYSQL_TYPE_SHORT == miType, (short)0);
	return *reinterpret_cast<short*>(mpData);
}

float CSqlFiled::GetFloat() {
	ASSERT_RET_VALUE(mpData && mlDataLen >0 && MYSQL_TYPE_FLOAT == miType, (float)0);
	return *reinterpret_cast<float*>(mpData);
}

long CSqlFiled::GetLong() {
	ASSERT_RET_VALUE(mpData && mlDataLen >0 && MYSQL_TYPE_LONG == miType, (long)0);
	return *reinterpret_cast<long*>(mpData);
}