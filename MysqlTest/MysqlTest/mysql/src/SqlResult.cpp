#include "SqlResult.h"

CSqlResult::CSqlResult(){
	mpResult = NULL;
	mpFields = NULL;
	miNumFields = 0;
    mlRows = 0;
}

CSqlResult::~CSqlResult(){
    Clean();
}

void  CSqlResult::Clean() {
    while (!mvecSqlRows.empty()) {
        std::vector<CSqlRow*>::iterator iter = mvecSqlRows.begin();
        CSqlRow* pSqlRow = *iter;
        DODELETE(pSqlRow);
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

int CSqlResult::SetResult(MYSQL_RES *pResult) {
	ASSERT_RET_VALUE(NULL != pResult, 1);
	mpResult = pResult;
	miNumFields = mysql_num_fields(mpResult);
	mpFields = mysql_fetch_fields(mpResult); 
	
	return 0;
}