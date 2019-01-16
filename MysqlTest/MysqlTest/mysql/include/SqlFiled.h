#ifndef __CSQLFILED__H_
#define __CSQLFILED__H_
#include "CLogmanager.h"
#include "mysqldef.h"

class CSqlFiled
{
public:
	CSqlFiled(char* pData, unsigned long lDataLen, enum_field_types iType);
	~CSqlFiled();

public:
	unsigned long GetULong();
	float GetFloat();
    double GetDouble();
    char GetChar();
	long GetLong();
    int64_t GetInt64();
    uint64_t GetUint64();
    int GetInt();
    int8_t GetInt8();
    uint8_t GetUint8();
    int16_t GetInt16();
    uint16_t GetUint16();
    int32_t GetInt32();
    uint32_t GetUint32();
    std::string GetStr();
    len_str GetData();

private:
	char* mpData;
    unsigned long mlDataLen;
	enum_field_types miType;
};

#endif