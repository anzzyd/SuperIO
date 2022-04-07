
using namespace std;
#include <vector>

struct SENDQUEUE
{
	int sqPlayerIndex;
	int sqPlayerUserId;
	char szMessage[1024];
};

class SendQueuePost
{
public:
	SendQueuePost(void);
	~SendQueuePost(void);
	CRITICAL_SECTION m_critical;

	void Lock();
	BOOL TryLock();
	void UnLock();

	std::vector<SENDQUEUE>		vSendQueue;
	void vSetSendQueue(int playerindex,int playeruid,char szMessage[]);
	void ExecuteOne();
};

extern SendQueuePost g_SendQueue;