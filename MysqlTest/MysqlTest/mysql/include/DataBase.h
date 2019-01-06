#ifndef __CDATABASE__H_
#define __CDATABASE__H_
#include "Task.h"
#include "UvSem.h"
#include "UvMutex.h"
#include "SqlQuery.h"

class CDataBase : public CTask{
public:
	CDataBase();
	~CDataBase();

public:
	void SetSqlParam(const tagConnInfo& stConnInfo);
	void Quit();
	int PushQuery(CSqlQuery* pQuery);

protected:
	int TaskInit();
	int TaskExcute();
	int TaskQuit();

private:
	int DoPing();
	CSqlQuery* PopQuery();
	void CleanQuery();
	void ExcuteQuery(CSqlQuery* pQuery);

private:
	tagConnInfo mstConnInfo;
	MYSQL mstMysql;
	MYSQL *mpMysql;
	time_t miLastPing;
	bool mbInit;
	bool mbQuit;
	CUvSem mcSem;

	std::queue<CSqlQuery*> mqueQuery;
	CUvMutex mcQueQueryMutex;
};

#endif