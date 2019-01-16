#ifndef __CSQLQUERY__H_
#define __CSQLQUERY__H_
#include "CLogmanager.h"
#include "GuidTool.h"
#include "SqlResult.h"
#include <queue>

typedef int(*sql_callback)(std::string& strQueryID, std::vector<CSqlResult*>& pResult, void* pParam);
class CSqlQuery{
public:
	CSqlQuery();
	~CSqlQuery();

public:
	int AddQuery(char* pQueryStr, size_t iLen);
	len_str PopQueryStr();
	std::string SetCb(sql_callback pCb, void* pCbParam);
    std::string GetQueryId() { return mstrGuid; }
    void* GetCbParam() { return mpCbParam; }
    sql_callback GetCb() { return mpCb; }

private:
	void Clean();

private:
	std::queue<len_str> mqueQueryStr;
	sql_callback mpCb;
	void* mpCbParam;
    std::string mstrGuid;
};

#endif