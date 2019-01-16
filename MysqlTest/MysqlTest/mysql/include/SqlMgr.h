#ifndef __CSQLMGR__H_
#define __CSQLMGR__H_
#include "singleton.h"
#include "mysqldef.h"
class CSqlMgr : public CSingleton<CSqlMgr>{
    SINGLE_CLASS_INITIAL(CSqlMgr);
public:
    ~CSqlMgr();

public:
    int Init();
    int UnInit();

private:
    bool mbInit;
};

#endif