#include "SqlFiled.h"

CSqlFiled::CSqlFiled(char* pData, unsigned long lDataLen, enum_field_types iType){
	mpData = pData;
	miType = iType;
    mlDataLen = lDataLen; 
}

CSqlFiled::~CSqlFiled(){
}

unsigned long CSqlFiled::GetULong() {
    ASSERT_RET_VALUE(mpData && mlDataLen >0, (unsigned long)0);
    char* pend;
    unsigned long a = strtoul(mpData, &pend, 10);//10为10进制权值
    ASSERT_RET_VALUE(*pend == '\0', -1);
    return a;
}

float CSqlFiled::GetFloat() {//MYSQL_TYPE_FLOAT == miType
    ASSERT_RET_VALUE(mpData && mlDataLen > 0, (float)0);
    char* pend;
    float a = strtof(mpData, &pend);
    ASSERT_RET_VALUE(*pend == '\0', -1);
    return a;
}

char CSqlFiled::GetChar() {
    ASSERT_RET_VALUE(mpData && mlDataLen > 0, (char)0);
    return mpData[0];
}

double CSqlFiled::GetDouble() {//MYSQL_TYPE_DOUBLE == miType
    ASSERT_RET_VALUE(mpData && mlDataLen > 0, (double)0);
    char* pend;
    double a = strtod(mpData, &pend);
    ASSERT_RET_VALUE(*pend == '\0', -1);
    return a;
}

int64_t CSqlFiled::GetInt64() {//MYSQL_TYPE_LONGLONG == miType
    ASSERT_RET_VALUE(mpData && mlDataLen > 0, (int64_t)0);
    char* pend;
    int64_t a = strtoll(mpData, &pend, 10);//10为10进制权值
    ASSERT_RET_VALUE(*pend == '\0', -1);
    return a;
}

uint64_t CSqlFiled::GetUint64() {
    ASSERT_RET_VALUE(mpData && mlDataLen > 0, (uint64_t)0);
    char* pend;
    uint64_t a = strtoull(mpData, &pend, 10);//10为10进制权值
    ASSERT_RET_VALUE(*pend == '\0', -1);
    return a;
}

long CSqlFiled::GetLong() {//MYSQL_TYPE_LONG == miType
	ASSERT_RET_VALUE(mpData && mlDataLen >0, (long)0);
    char* pend;
    long a = strtol(mpData, &pend, 10);//10为10进制权值
    ASSERT_RET_VALUE(*pend == '\0', -1);
    return a;
}

int CSqlFiled::GetInt() {//MYSQL_TYPE_INT24 == miType
    ASSERT_RET_VALUE(mpData && mlDataLen > 0, (int)0);
    char* pend;
    long a = strtol(mpData, &pend, 10);
    ASSERT_RET_VALUE(*pend == '\0', -1);
    return static_cast<int>(a);
}

int8_t CSqlFiled::GetInt8() {
    return static_cast<int8_t>(GetLong());
}

uint8_t CSqlFiled::GetUint8() {
    return static_cast<uint8_t>(GetLong());
}

int16_t CSqlFiled::GetInt16() {
    return static_cast<int16_t>(GetLong());
}

uint16_t CSqlFiled::GetUint16() {
    return static_cast<uint16_t>(GetLong());
}

int32_t CSqlFiled::GetInt32() {
    return static_cast<int32_t>(GetLong());
}

uint32_t CSqlFiled::GetUint32() {
    return static_cast<uint32_t>(GetLong());
}

std::string CSqlFiled::GetStr() {//MYSQL_TYPE_VAR_STRING == miType
    ASSERT_RET_VALUE(mpData && mlDataLen > 0, "");
    return std::string(mpData, mlDataLen);
}

len_str CSqlFiled::GetData() {
    len_str lRet;
    memset(&lRet, 0, sizeof(lRet));

    ASSERT_RET_VALUE(mpData && mlDataLen >0, lRet);
    lRet.pStr = mpData;
    lRet.iLen = mlDataLen;

    return lRet;
}