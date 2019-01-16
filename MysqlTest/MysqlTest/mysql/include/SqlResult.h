#ifndef __CSQLRESULT__H_
#define __CSQLRESULT__H_
#include "SqlRow.h"

class CSqlResult
{
public:
	CSqlResult();
	~CSqlResult();

public:
	int SetResult(MYSQL_RES *pResult);
    CSqlRow* FetchRow();
    CSqlRow* GetRow(int iIndex);

    void SetAffectRows(my_ulonglong lRows) { mlRows = lRows; }
    my_ulonglong GetAffectRows() { return mlRows; }

    void SetError(std::string strError) { mstrError = strError; }
    std::string& GetError() { return mstrError; }

private:
    void Clean();

private:
	MYSQL_RES *mpResult;
	MYSQL_FIELD *mpFields;
	unsigned int miNumFields;
    std::vector<CSqlRow*> mvecSqlRows;
    my_ulonglong mlRows;
    std::string mstrError;
};

#endif