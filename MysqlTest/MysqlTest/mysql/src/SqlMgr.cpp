#include "SqlMgr.h"

CSqlMgr::CSqlMgr(){
    mbInit = false;
}

CSqlMgr::~CSqlMgr(){
}

int CSqlMgr::Init() {
    if (!mbInit) {
        mysql_library_init(0, NULL, NULL);
        mbInit = true;
    }

    return 0;
}

int CSqlMgr::UnInit() {
    if (mbInit) {
        mbInit = false;
        mysql_library_end();
    }

    return 0;
}