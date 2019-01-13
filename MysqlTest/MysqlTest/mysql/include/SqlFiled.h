#ifndef __CSQLFILED__H_
#define __CSQLFILED__H_
#include "CLogmanager.h"
#include "mysqldef.h"

class CSqlFiled
{
public:
	CSqlFiled(char* pData, enum_field_types iType);
	~CSqlFiled();

public:
	short GetShort();
	float GetFloat();
	long GetLong();

private:
	char* mpData;
	enum_field_types miType;
};

#endif