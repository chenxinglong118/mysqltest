#ifndef __CSQLRESULT__H_
#define __CSQLRESULT__H_
#include "SqlRow.h"

class CSqlResult
{
public:
	CSqlResult();
	~CSqlResult();

public:
	int HandleQueryReult(MYSQL_RES *pResult);

private:
	MYSQL_RES *mpResult;
	MYSQL_FIELD *mpFields;
	unsigned int miNumFields;
};

#endif