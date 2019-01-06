#ifndef __CSQLQUERY__H_
#define __CSQLQUERY__H_
#include "CLogmanager.h"
#include "SqlResult.h"
#include <queue>

typedef int(*sql_callback)(CSqlResult* pResult, void* pParam);
class CSqlQuery{
public:
	CSqlQuery();
	~CSqlQuery();

public:
	int AddQuery(unsigned char* pQueryStr, size_t iLen);
	len_str PopQueryStr();
	void SetCb(sql_callback pCb, void* pCbParam);
	int HandleQueryReult(MYSQL_RES *pResult);

private:
	void CleanQueryStr();

private:
	std::queue<len_str> mqueQueryStr;
	sql_callback mpCb;
	void* mpCbParam;
	CSqlResult* mpSqlReult;
};

#endif