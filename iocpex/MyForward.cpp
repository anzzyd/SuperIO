
#include "stdafx.h"
#include "sdk/amxxmodule.h"
#include "MyForward.h"

MyForward g_MyForward;

CForwardData::CForwardData()
{
	type = 0; 
	data = NULL;
}

CForwardData:: ~CForwardData()
{
	if (data)
	{
		switch (type)
		{
			case FW_DATASTRING:
			{
				delete (DataString_S*)data;
				break;
			}
			default: delete data;
		}
		data = NULL;
	}
}

MyForward::MyForward()
{
	InitializeCriticalSection(&m_critical);	
}

MyForward:: ~MyForward()
{
	DeleteCriticalSection(&m_critical);
}

void MyForward::Lock()
{
	EnterCriticalSection(&m_critical); 
}

BOOL MyForward::TryLock()
{
	return TryEnterCriticalSection(&m_critical); 
}

void MyForward::UnLock()
{
	LeaveCriticalSection(&m_critical);
}

void MyForward::Clear()
{
	for (int i=0; i < m_ForwardDataList.size(); i++)
	{
		if (m_ForwardDataList[i])
		{
			delete m_ForwardDataList[i];
		}
	}

	m_ForwardDataList.clear();
}

void MyForward::Execute()
{
	vector<CForwardData *>::iterator iter;
	iter = m_ForwardDataList.begin();

	while (iter != m_ForwardDataList.end())
	{
		CForwardData *pForwardData = (*iter);

		if (pForwardData)
		{
			switch (pForwardData->type)
			{
				case FW_DATASTRING:
				{
					DataString_S *pfw = (DataString_S*)pForwardData->data;
					if(pfw)
					{
						if (g_response_fwd != -1)
						{
							//MF_Log("[RECV]ID:%d UID:%d RAW:%s", pfw->index, pfw->uid, pfw->m_DataBuffer);
							MF_ExecuteForward(g_response_fwd,pfw->index,pfw->uid,pfw->m_DataBuffer);
						}
					}
					break;
				}
			}
			// Çå³ý
			delete pForwardData;
		}
		iter = m_ForwardDataList.erase(iter);
	}
}

void MyForward::AddDataString(CString DataString)
{
	DataString_S* pData = new DataString_S();
	memset(pData, 0, sizeof(DataString_S));
	pData->index = 0;
	pData->uid = 0;
	snprintf(pData->m_DataBuffer, sizeof(pData->m_DataBuffer), "%s", DataString.GetBuffer());
	DataString.ReleaseBuffer();
	CForwardData *pForwardData = new CForwardData();
	pForwardData->type = FW_DATASTRING;
	pForwardData->data = (void*)pData;
	m_ForwardDataList.push_back(pForwardData);	
}

void MyForward::AddDataString(int index , int uid , CString DataString)
{
	DataString_S* pData = new DataString_S();
	memset(pData, 0, sizeof(DataString_S));
	pData->index = index;
	pData->uid = uid;
	snprintf(pData->m_DataBuffer, sizeof(pData->m_DataBuffer), "%s", DataString.GetBuffer());
	DataString.ReleaseBuffer();
	CForwardData *pForwardData = new CForwardData();
	pForwardData->type = FW_DATASTRING;
	pForwardData->data = (void*)pData;
	m_ForwardDataList.push_back(pForwardData);	
}