#ifndef __CSQLROW__H_
#define __CSQLROW__H_
#include "SqlFiled.h"
#include <vector>
class CSqlRow
{
public:
	CSqlRow(MYSQL_FIELD *pFields, unsigned int iNumFields, MYSQL_ROW pSqlRow, unsigned long* pRowLen);
	~CSqlRow();

public:
    void GetFileds();
    CSqlFiled* GetFiled(unsigned int iIndex);

private:
    void Clean();

private:
	MYSQL_FIELD *mpFields;
	unsigned int miNumFields;
	MYSQL_ROW mpSqlRow;
    unsigned long* mplRowLen;
    std::vector<CSqlFiled*> mvecFileds;
};

#endif