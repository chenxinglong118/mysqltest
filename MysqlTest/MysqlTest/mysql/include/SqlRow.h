#ifndef __CSQLROW__H_
#define __CSQLROW__H_
#include "SqlFiled.h"
class CSqlRow
{
public:
	CSqlRow(MYSQL_FIELD *pFields, unsigned int iNumFields, MYSQL_ROW *pSqlRow);
	~CSqlRow();

private:
	MYSQL_FIELD *mpFields;
	unsigned int miNumFields;
	MYSQL_ROW *mpSqlRow;
};

#endif