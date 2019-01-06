#include "SqlResult.h"

CSqlResult::CSqlResult(){
	mpResult = nullptr;
	mpFields = nullptr;
	miNumFields = 0;
}

CSqlResult::~CSqlResult(){
}

int CSqlResult::HandleQueryReult(MYSQL_RES *pResult) {
	ASSERT_RET_VALUE(nullptr != pResult, 1);
	mpResult = pResult;
	miNumFields = mysql_num_fields(mpResult);
	mpFields = mysql_fetch_fields(mpResult); 
	
	return 0;
}