#include "StdAfx.h"
#include "CMyTools.h"
#include <ATLComTime.h>

CMyTools MyTools;

CMyTools::CMyTools(void)
{
}

CMyTools::~CMyTools(void)
{
}

/* 以 Split 拆分 CString 到列表 CStringArray
 * 返回读取的行数
 */
DWORD CMyTools::StringToArrayList(CString& szSource, CStringArray& sList, BYTE Split)
{
	int count = 0;
	CString line;
	for (int i=0; i<szSource.GetLength(); i++)
	{
		if (szSource.GetAt(i) == Split)
		{
			line.Trim();
			sList.Add(line);
			count++;
			line.Empty();
			continue;
		}

		line.AppendChar(szSource.GetAt(i));
	}

	if (!line.IsEmpty())
	{
		sList.Add(line);
		count++;
	}

	return count;
}

// 返回 CStringArray 里第一个找到的，包含 key 的值
// key = info test  // 返回 "info test"
bool CMyTools::ListGetKeyValue(CStringArray& list, CString& sKey, CString& sValue, LPCTSTR mark)
{
	sValue.Empty();

	CString line;
	INT_PTR count = list.GetCount();
	for (INT_PTR pos=0; pos<count; pos++)
	{
		line = list.GetAt(pos);

		if (StringGetKeyValue(line, sKey, sValue, mark))
		{
			return true;
		}
	}
	return false;
}

bool CMyTools::StringGetKeyValue(CString& Source, CString& sKey, CString& sValue, LPCTSTR mark)
{
	sValue.Empty();

	int SourceLen = Source.GetLength();
	int MarkLen = strlen(mark);

	CString left;
	int p;
	p = Source.Find(mark);
	if (p != -1)
	{
		left = Source.Left(p);
		left.Trim();

		if (left.CompareNoCase(sKey) == 0)
		{
			if (SourceLen - p+MarkLen > 0)
			{
				sValue = Source.Mid(p+MarkLen);
				sValue.Trim();
				sValue.Trim("\"");
				return true;
			}
		}
	}

	return false;
}

// 设置系统时间 "2007-11-24 8:00:00"
void CMyTools::SetSystemTime(LPCTSTR szNewTime)
{
	COleDateTime tm;
	tm.ParseDateTime(szNewTime);

	SYSTEMTIME st;
	tm.GetAsSystemTime(st);
	SetLocalTime(&st);
}