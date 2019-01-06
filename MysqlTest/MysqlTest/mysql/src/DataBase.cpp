#include "DataBase.h"

CDataBase::CDataBase(){
	mpMysql = (MYSQL*)do_malloc(sizeof(MYSQL));
	miLastPing = 0;
	mbInit = false;
	mbQuit = false;
}

CDataBase::~CDataBase(){
	if (mpMysql) {
		DOFREE(mpMysql);
	}
}

void CDataBase::Quit() {
	mbQuit = true;
	mcSem.Post();
}

void CDataBase::SetSqlParam(const tagConnInfo& stConnInfo) {
	mstConnInfo = stConnInfo;
}

int CDataBase::TaskInit() {
	LOG_INFO("Enter CDataBase::TaskInit");
	mysql_thread_init();
	if (!mbInit) {
		do {
			mysql_init(mpMysql);
			//设置长连接然后使用mysql_ping保活
			if (mstConnInfo.bReconnect) {
				if (mysql_options(mpMysql, MYSQL_OPT_RECONNECT, &mstConnInfo.bReconnect)) {
					LOG_ERR("MYSQL_OPT_RECONNECT error %s", mysql_error(mpMysql));
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

			mysql_options(mpMysql, MYSQL_OPT_CONNECT_TIMEOUT, &mstConnInfo.iTimeOut);
			if (!mysql_real_connect(mpMysql, mstConnInfo.strHost.c_str(), mstConnInfo.strUsr.c_str(), mstConnInfo.strPasswd.c_str(), mstConnInfo.strDbName.c_str(), mstConnInfo.usPort, nullptr, CLIENT_MULTI_STATEMENTS)) {
				LOG_ERR("mysql_real_connect error %s", mysql_error(mpMysql));
				break;
			}

			mbInit = true;
		} while (0);
	}

	if (!mbInit) {
		mysql_close(mpMysql);
	}

	return 0;
}

int CDataBase::DoPing() {
	if (mbInit) {
		return mysql_ping(mpMysql);
	}

	return 1;
}

int CDataBase::PushQuery(CSqlQuery* pQuery) {
	ASSERT_RET_VALUE(mbInit && nullptr != pQuery, 1);
	mcQueQueryMutex.Lock();
	mqueQuery.push(pQuery);
	mcQueQueryMutex.UnLock();
	mcSem.Post();
	return 0;
}

CSqlQuery* CDataBase::PopQuery() {
	CSqlQuery* pQuery = nullptr;
	mcQueQueryMutex.Lock();
	if (!mqueQuery.empty()) {
		pQuery = mqueQuery.front();
		mqueQuery.pop();
	}
	mcQueQueryMutex.UnLock();

	return pQuery;
}

void CDataBase::CleanQuery() {
	mcQueQueryMutex.Lock();
	if (!mqueQuery.empty()) {
		CSqlQuery* pQuery = mqueQuery.front();
		mqueQuery.pop();
		DODELETE(pQuery);
	}
	mcQueQueryMutex.UnLock();
}

void CDataBase::ExcuteQuery(CSqlQuery* pQuery) {
	ASSERT_RET(nullptr != pQuery);
	len_str sqlstr = pQuery->PopQueryStr();
	while (sqlstr.iLen > 0 && nullptr != sqlstr.pStr) {
		int iRet = mysql_real_query(mpMysql, (char*)sqlstr.pStr, (unsigned long)sqlstr.iLen);
		if (iRet) {
			if (iRet == CR_COMMANDS_OUT_OF_SYNC) {//命令以一个不适当的次序被执行
				LOG_ERR("Commands is out of sync");
			} else if (iRet == CR_SERVER_GONE_ERROR) {//MySQL服务器关闭了
				LOG_ERR("mysql server gone");
			} else if (iRet == CR_SERVER_LOST) {//对服务器的连接在查询期间失去
				LOG_ERR("mysql server lost");
				DoPing();
				continue;
			} else {//发生一个未知的错误
				LOG_ERR("unknow error");
			}
		}

		pQuery->HandleQueryReult(mysql_store_result(mpMysql));
		sqlstr = pQuery->PopQueryStr();
	}

	DODELETE(pQuery);
}

int CDataBase::TaskExcute() {
	LOG_INFO("Enter CDataBase::TaskExcute");
	while(!mbQuit && mbInit) {
		CSqlQuery* pQuery  = PopQuery();
		if (nullptr == pQuery) {
			mcSem.Wait();
		}

		ExcuteQuery(pQuery);
	}
	return 0;
}

int CDataBase::TaskQuit() {
	LOG_INFO("Enter CDataBase::TaskQuit");
	if (mbInit) {
		mysql_close(mpMysql);
		mbInit = false;
		CleanQuery();
	}
	mysql_thread_end();

	return 0;
}