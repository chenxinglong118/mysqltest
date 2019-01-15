#include "SqlResult.h"

CSqlResult::CSqlResult(){
	mpResult = nullptr;
	mpFields = nullptr;
	miNumFields = 0;
}

CSqlResult::~CSqlResult(){
	if (mpResult) {
		mysql_free_result(mpResult);
		mpResult = nullptr;
	}
}

CSqlRow* CSqlResult::FetchRow() {
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

int CSqlResult::HandleQueryReult(MYSQL_RES *pResult) {
	ASSERT_RET_VALUE(nullptr != pResult, 1);
	mpResult = pResult;
	miNumFields = mysql_num_fields(mpResult);
	mpFields = mysql_fetch_fields(mpResult); 
	for (int i = 0; i < miNumFields; ++i) {
		LOG_INFO("%s %d", mpFields[i].name, mpFields[i].type);
	}
	
	return 0;
}