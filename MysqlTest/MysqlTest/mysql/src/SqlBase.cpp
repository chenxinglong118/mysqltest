#include "SqlBase.h"

CSqlBase::CSqlBase(){
	mpMysql = NULL;
	miLastPing = 0;
	mbInit = false;
	mbQuit = false;
}

CSqlBase::~CSqlBase(){
}

void CSqlBase::Quit() {
	mbQuit = true;
	mcSem.Post();
}

void CSqlBase::SetSqlParam(const tagConnInfo& stConnInfo) {
	mstConnInfo = stConnInfo;
}

int CSqlBase::TaskInit() {
	LOG_INFO("Enter CSqlBase::TaskInit");
	mysql_thread_init();
	if (!mbInit) {
		do {
			mpMysql = mysql_init(&mstMysql);
			if (mpMysql) {
				//设置长连接然后使用mysql_ping保活
				if (mstConnInfo.bReconnect) {
					if (mysql_options(mpMysql, MYSQL_OPT_RECONNECT, &mstConnInfo.bReconnect)) {
						LOG_ERR("MYSQL_OPT_RECONNECT error %d %s", mysql_errno(mpMysql), mysql_error(mpMysql));
						break;
					}
				}

				if (!mstConnInfo.strCharSetName.empty()) {
					//设置utf8编码
					if (mysql_options(mpMysql, MYSQL_SET_CHARSET_NAME, mstConnInfo.strCharSetName.c_str())) {
						LOG_ERR("MYSQL_SET_CHARSET_NAME error %s", mysql_error(mpMysql));
						break;
					}
				}

				if (mstConnInfo.iTimeOut > 0) {
					mysql_options(mpMysql, MYSQL_OPT_CONNECT_TIMEOUT, &mstConnInfo.iTimeOut);
				}

				if (!mysql_real_connect(mpMysql, mstConnInfo.strHost.c_str(), mstConnInfo.strUsr.c_str(), mstConnInfo.strPasswd.c_str(), mstConnInfo.strDbName.c_str(), mstConnInfo.usPort, nullptr, CLIENT_MULTI_STATEMENTS)) {
					LOG_ERR("mysql_real_connect error %d %s", mysql_errno(mpMysql), mysql_error(mpMysql));
					break;
				}

				mbInit = true;
			} 
		} while (0);
	}

	return 0;
}

int CSqlBase::DoPing() {
	if (mbInit) {
		return mysql_ping(mpMysql);
	}

	return 1;
}

int CSqlBase::PushQuery(CSqlQuery* pQuery) {
	ASSERT_RET_VALUE(mbInit && nullptr != pQuery, 1);
	mcQueQueryMutex.Lock();
	mqueQuery.push(pQuery);
	mcQueQueryMutex.UnLock();
	mcSem.Post();
	return 0;
}

CSqlQuery* CSqlBase::PopQuery() {
	CSqlQuery* pQuery = nullptr;
	mcQueQueryMutex.Lock();
	if (!mqueQuery.empty()) {
		pQuery = mqueQuery.front();
		mqueQuery.pop();
	}
	mcQueQueryMutex.UnLock();

	return pQuery;
}

void CSqlBase::CleanQuery() {
	mcQueQueryMutex.Lock();
	if (!mqueQuery.empty()) {
		CSqlQuery* pQuery = mqueQuery.front();
		mqueQuery.pop();
		DODELETE(pQuery);
	}
	mcQueQueryMutex.UnLock();
}

void CSqlBase::ExcuteQuery(CSqlQuery* pQuery) {
	ASSERT_RET(nullptr != pQuery);
	len_str sqlstr = pQuery->PopQueryStr();
	while (sqlstr.iLen > 0 && nullptr != sqlstr.pStr) {
		int iRet = mysql_real_query(mpMysql, (char*)sqlstr.pStr, (unsigned long)sqlstr.iLen);
		if (iRet) {
			if (iRet == CR_COMMANDS_OUT_OF_SYNC) {//命令以一个不适当的次序被执行
				LOG_ERR("Commands is out of sync");
			}
			else if (iRet == CR_SERVER_GONE_ERROR) {//MySQL服务器关闭了
				LOG_ERR("mysql server gone");
			}
			else if (iRet == CR_SERVER_LOST) {//对服务器的连接在查询期间失去
				LOG_ERR("mysql server lost");
				DoPing();
				continue;
			}
			else {//发生一个未知的错误
				LOG_ERR("unknow error");
			}
		}

		MYSQL_RES *pResult = mysql_store_result(mpMysql);
		if (pResult) {
			pQuery->HandleQueryReult(pResult);
		} else {// mysql_store_result() returned nothing; should it have?
			if (mysql_field_count(mpMysql) == 0) // query does not return data   (it was not a SELECT)
			{
				my_ulonglong iNumRows = mysql_affected_rows(mpMysql);
			}
			else // mysql_store_result() should have returned data
			{
				LOG_ERR("Error: %s %s", mysql_error(mpMysql), (char*)sqlstr.pStr);
			}
		}
		
		sqlstr = pQuery->PopQueryStr();
	}

	DODELETE(pQuery);
}

int CSqlBase::TaskExcute() {
	LOG_INFO("Enter CSqlBase::TaskExcute");
	while(!mbQuit && mbInit) {
		CSqlQuery* pQuery  = PopQuery();
		if (nullptr == pQuery) {
			mcSem.Wait();
			continue;
		}

		ExcuteQuery(pQuery);
	}
	return 0;
}

int CSqlBase::TaskQuit() {
	LOG_INFO("Enter CSqlBase::TaskQuit");
	if (mpMysql) {
		mysql_close(mpMysql);
		mbInit = false;
		CleanQuery();
		mpMysql = NULL;
	}
	mysql_thread_end();

	return 0;
}