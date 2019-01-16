#include "SqlResult.h"

CSqlResult::CSqlResult(){
	mpResult = NULL;
	mpFields = NULL;
	miNumFields = 0;
    mlRows = 0;
    miErrNo = 0;
}

CSqlResult::~CSqlResult(){
    Clean();
}

void CSqlResult::SetError(int iErrNo, std::string strError) {
    mstrError = strError;
    miErrNo = iErrNo;
}

void  CSqlResult::Clean() {
    while (!mvecSqlRows.empty()) {
        std::vector<CSqlRow*>::iterator iter = mvecSqlRows.begin();
        CSqlRow* pSqlRow = *iter;
        DODELETE(pSqlRow);
        mvecSqlRows.erase(iter);
    }

    if (mpResult) {
        mysql_free_result(mpResult);
        mpResult = NULL;
    }
}

CSqlRow* CSqlResult::FetchRow() {
    ASSERT_RET_VALUE(mpResult, NULL);
    CSqlRow* pSqlRow = NULL;
    if (mpResult) {
        MYSQL_ROW pRow = mysql_fetch_row(mpResult);
        unsigned long *pRowLen = mysql_fetch_lengths(mpResult);
        if (pRow && pRowLen) {
            pSqlRow = new CSqlRow(mpFields, miNumFields, pRow, pRowLen);
            if (pSqlRow) {
                mvecSqlRows.push_back(pSqlRow);
            }
        }
    }

    return pSqlRow;
}

CSqlRow* CSqlResult::GetRow(int iIndex) {
    ASSERT_RET_VALUE(iIndex < mvecSqlRows.size(), NULL);
    return mvecSqlRows[iIndex];
}

int CSqlResult::FindColIndex(char* pName) {
    int iRet = -1;
    ASSERT_RET_VALUE(mpFields && pName && strlen(pName) > 0 && miNumFields > 0, 1);
    for (int i = 0; i < (int)miNumFields; ++i) {
        if (str_cmp(mpFields[i].name, pName, true)) {
            iRet = i;
            break;
        }
    }

    return iRet;
}

int CSqlResult::SetResult(MYSQL_RES *pResult) {
	ASSERT_RET_VALUE(NULL != pResult, 1);
	mpResult = pResult;
	miNumFields = mysql_num_fields(mpResult);
	mpFields = mysql_fetch_fields(mpResult); 
	
	return 0;
}