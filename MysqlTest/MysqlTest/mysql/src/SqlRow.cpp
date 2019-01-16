#include "SqlRow.h"

CSqlRow::CSqlRow(MYSQL_FIELD *pFields, unsigned int iNumFields, MYSQL_ROW pSqlRow, unsigned long* pRowLen){
	mpFields = pFields;
	miNumFields = iNumFields;
	mpSqlRow = pSqlRow;
    mplRowLen = pRowLen;
    GetFileds();
}

CSqlRow::~CSqlRow(){
    Clean();
}

void CSqlRow::GetFileds() {
    if (mvecFileds.empty() && mpSqlRow && mplRowLen && mpFields && miNumFields > 0) {
        for (unsigned int i = 0; i < miNumFields; ++i) {
            CSqlFiled* pSqlFiled = new CSqlFiled(mpSqlRow[i], mplRowLen[i], mpFields[i].type);
            if (pSqlFiled) {
                mvecFileds.push_back(pSqlFiled);
            }
        }
    }
}

CSqlFiled* CSqlRow::operator[](unsigned int iIndex) {
    return GetFiled(iIndex);
}

CSqlFiled* CSqlRow::GetFiled(unsigned int iIndex) {
    ASSERT_RET_VALUE(mpSqlRow && mplRowLen && mpFields && miNumFields > iIndex, NULL);
    return mvecFileds[iIndex];
}

void CSqlRow::Clean() {
    while (mvecFileds.size() > 0) {
        std::vector<CSqlFiled*>::iterator iter = mvecFileds.begin();
        CSqlFiled* pSqlFiled = *iter;
        DODELETE(pSqlFiled);
    }
}