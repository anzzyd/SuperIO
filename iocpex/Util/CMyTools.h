#pragma once

#include <list>

class CMyTools
{
public:
	CMyTools(void);
	~CMyTools(void);
public:

	/**************************
		字符串操作函数
	***************************/

	// 以 Split 拆分 CString 到列表 CStringArray
	// 返回读取的行数
	DWORD StringToArrayList(CString& szSource, CStringArray& sList, BYTE Split=',');

	// 返回 CStringArray 里第一个找到的，包含 key 的值
	// key = info  // 返回 "info"
	bool ListGetKeyValue(CStringArray& list, CString& sKey, CString& sValue, LPCTSTR mark="=");

	// 返回 CString 里第一个找到的，包含 key 的值
	// key = info  // 返回 "info"
	bool StringGetKeyValue(CString& Text, CString& sKey, CString& sValue, LPCTSTR mark="=");

	/////////////////////////////////////////

	// 设置系统时间 "2007-11-24 8:00:00"
	void SetSystemTime(LPCTSTR szNewTime);
};

extern CMyTools MyTools;