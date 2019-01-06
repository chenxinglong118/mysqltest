// MysqlTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CLogmanager.h"
#include "DataBase.h"
#include "UvTaskPool.h"
//http://blog.chinaunix.net/uid-26743670-id-3479887.html
int main()
{
	mysql_library_init(0, NULL, NULL);
	sLog->Init(0, 5, ".");
	sUvTaskPool->Start();
	CDataBase* pDataBase = new CDataBase();
	tagConnInfo stConn;
	stConn.strHost = "192.168.11.128";
	stConn.strUsr = "root";
	stConn.strPasswd = "root";
	stConn.strDbName = "test";
	stConn.iTimeOut = 0;
	stConn.strCharSetName = "utf8";
	stConn.usPort = 3306;
	pDataBase->SetSqlParam(stConn);
	sUvTaskPool->PushTask((CTask*)pDataBase);
	sleep_ms(1000);
	CSqlQuery* pQuery = new CSqlQuery();
	char *pSql = "select * from score;";
	pQuery->AddQuery((unsigned char*)pSql, strlen(pSql));
	pDataBase->PushQuery(pQuery);
	getchar();

    return 0;
}

