

#pragma once

#include <vector>
using namespace std;

enum
{
	FW_SPEAKR = 1,
	FW_DATASTRING,
	FW_TZ_PLAYERLOGIN
};

struct DataString_S
{
	int index;
	int uid;
	char m_DataBuffer[4096];
};

struct TzPlayerLoginRet
{
	int result;
	int key;
	char szEngName[48];
	char szChsName[48];
};

class CForwardData
{
public:
	CForwardData();
	~CForwardData();
	int type;
	void* data;
};

class MyForward
{
public:
	MyForward(void);
	~MyForward(void);
	CRITICAL_SECTION m_critical;
	void Lock();
	BOOL TryLock();
	void UnLock();
	std::vector<CForwardData *> m_ForwardDataList;
	void Clear();
	void Execute();

	void AddDataString(CString DataString);
	void AddDataString(int index,int uid,CString DataString);
};

extern MyForward g_MyForward;
extern int g_response_fwd;