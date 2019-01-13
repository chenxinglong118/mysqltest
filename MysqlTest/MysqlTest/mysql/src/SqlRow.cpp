#include "SqlRow.h"

CSqlRow::CSqlRow(MYSQL_FIELD *pFields, unsigned int iNumFields, MYSQL_ROW *pSqlRow){
	mpFields = pFields;
	miNumFields = iNumFields;
	mpSqlRow = pSqlRow;
}

CSqlRow::~CSqlRow(){
}