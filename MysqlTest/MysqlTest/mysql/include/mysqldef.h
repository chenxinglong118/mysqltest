#ifndef __MYSQLDEF__H_
#define __MYSQLDEF__H_
#include "mysql.h"
#include "errmsg.h"
#include <string>

//mysql_library_init
//mysql_library_end

#pragma pack(1)
struct  tagConnInfo{
	tagConnInfo& operator= (const tagConnInfo& stConnInfo) {
		if (this != &stConnInfo) {
			this->strHost = stConnInfo.strHost;
			this->strUsr = stConnInfo.strUsr;
			this->strPasswd = stConnInfo.strPasswd;
			this->strDbName = stConnInfo.strDbName;
			this->usPort = stConnInfo.usPort;
			this->bReconnect = stConnInfo.bReconnect;
			this->strCharSetName = stConnInfo.strCharSetName;
			this->iTimeOut = stConnInfo.iTimeOut;
		}

		return *this;
	}

	my_bool bReconnect;
	unsigned short usPort;
	int iTimeOut;
	std::string strHost;
	std::string strUsr;
	std::string strPasswd;
	std::string strDbName;
	std::string strCharSetName;
};
#pragma pack()
#endif
