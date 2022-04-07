
#include "stdafx.h"
#include "SendQueue.h"
#include "IOCP\DAIOCP.h"
SendQueuePost g_SendQueue;

SendQueuePost::SendQueuePost( void )
{
	InitializeCriticalSection(&m_critical);
}

SendQueuePost::~SendQueuePost( void )
{
	DeleteCriticalSection(&m_critical);
}

void SendQueuePost::Lock()
{
	EnterCriticalSection(&m_critical);
}

BOOL SendQueuePost::TryLock()
{
	return TryEnterCriticalSection(&m_critical);
}

void SendQueuePost::UnLock()
{
	LeaveCriticalSection(&m_critical);
}

void SendQueuePost::vSetSendQueue( int playerindex,int playeruid,char szMessage[] )
{
	//Added item;
	SENDQUEUE addQueue;
	addQueue.sqPlayerIndex = playerindex;
	addQueue.sqPlayerUserId = playeruid;
	sprintf_s(addQueue.szMessage,1023,szMessage);
	vSendQueue.push_back(addQueue);
}

void SendQueuePost::ExecuteOne()
{
	vector<SENDQUEUE>::iterator iter;
	if(vSendQueue.size() == 0 || !daiocp.IsConnected())
		return;
	iter = vSendQueue.begin();
	if(iter != vSendQueue.end())
	{
		daiocp.BuildPostMessageAndSend(daiocp.GetLastContext(), Job_PlayerData, iter->sqPlayerIndex,iter->sqPlayerUserId,iter->szMessage);
	}
	vSendQueue.erase(iter);
}

