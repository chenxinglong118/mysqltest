// MysqlTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CLogmanager.h"
#include "DataBase.h"

int main()
{
	sLog->Init(0, 5, ".");
	CDataBase cBase;
	tagConnInfo stConn;
	stConn.strHost = "192.168.11.128";
	stConn.strUsr = "root";
	stConn.strPasswd = "root";
	stConn.strDbName = "test3";
	stConn.usPort = 3306;
	getchar();

    return 0;
}

