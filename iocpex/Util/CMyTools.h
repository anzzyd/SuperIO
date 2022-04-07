#pragma once

#include <list>

class CMyTools
{
public:
	CMyTools(void);
	~CMyTools(void);
public:

	/**************************
		�ַ�����������
	***************************/

	// �� Split ��� CString ���б� CStringArray
	// ���ض�ȡ������
	DWORD StringToArrayList(CString& szSource, CStringArray& sList, BYTE Split=',');

	// ���� CStringArray ���һ���ҵ��ģ����� key ��ֵ
	// key = info  // ���� "info"
	bool ListGetKeyValue(CStringArray& list, CString& sKey, CString& sValue, LPCTSTR mark="=");

	// ���� CString ���һ���ҵ��ģ����� key ��ֵ
	// key = info  // ���� "info"
	bool StringGetKeyValue(CString& Text, CString& sKey, CString& sValue, LPCTSTR mark="=");

	/////////////////////////////////////////

	// ����ϵͳʱ�� "2007-11-24 8:00:00"
	void SetSystemTime(LPCTSTR szNewTime);
};

extern CMyTools MyTools;