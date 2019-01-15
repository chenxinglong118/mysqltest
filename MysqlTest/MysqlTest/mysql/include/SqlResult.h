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
    CSqlRow* FetchRow();
    CSqlRow* GetRow(int iIndex);

private:
	MYSQL_RES *mpResult;
	MYSQL_FIELD *mpFields;
	unsigned int miNumFields;
    std::vector<CSqlRow*> mvecSqlRows;
};

#endif