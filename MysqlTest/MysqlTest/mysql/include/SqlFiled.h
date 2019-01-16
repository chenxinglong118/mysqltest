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
	short GetShort();
	float GetFloat();
	long GetLong();
    len_str GetData();

private:
	char* mpData;
    unsigned long mlDataLen;
	enum_field_types miType;
};

#endif