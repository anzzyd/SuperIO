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

/* �� Split ��� CString ���б� CStringArray
 * ���ض�ȡ������
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

// ���� CStringArray ���һ���ҵ��ģ����� key ��ֵ
// key = info test  // ���� "info test"
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

// ����ϵͳʱ�� "2007-11-24 8:00:00"
void CMyTools::SetSystemTime(LPCTSTR szNewTime)
{
	COleDateTime tm;
	tm.ParseDateTime(szNewTime);

	SYSTEMTIME st;
	tm.GetAsSystemTime(st);
	SetLocalTime(&st);
}