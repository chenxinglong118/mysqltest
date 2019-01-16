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
    unsigned int GetFieldsNum() { return miNumFields; }
    my_ulonglong GetRowsNum() { return mlRows; }
    CSqlRow* FetchRow();
    CSqlRow* GetRow(int iIndex);

    void SetAffectRows(my_ulonglong lRows) { mlAffectRows = lRows; }
    my_ulonglong GetAffectRows() { return mlAffectRows; }

    void SetError(unsigned int iErrNo, std::string strError);
    std::string& GetError() { return mstrError; }
    int GetErrNo() { return miErrNo; }

    int FindColIndex(char* pName);
private:
    void Clean();

private:
	MYSQL_RES *mpResult;
	MYSQL_FIELD *mpFields;
	unsigned int miNumFields;
    std::vector<CSqlRow*> mvecSqlRows;
    my_ulonglong mlAffectRows;
    my_ulonglong mlRows;
    std::string mstrError;
    unsigned int miErrNo;
};

#endif