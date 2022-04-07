/*=======================================================
				  DCOO Anti-Cheat Source
=========================================================*/

#ifndef APIHOOK_H
#define APIHOOK_H

#include <windows.h>
#include <string>
#include <vector>
#include <tlhelp32.h>

using namespace std;

#pragma pack(1)
struct JumpCode
{
    BYTE nix;
    BYTE jmp;
    int distance;
};
#pragma pack()

class APIHookItem
{
	public: 
		APIHookItem()
		{
			gesamtlength = 0;
			gesamtcode = NULL;

			oldfunc = NULL;
			newfunc = NULL;
			nextfunc = NULL;

			Hooked = false;
		};
		void* gesamtcode;
		int gesamtlength;
		void* oldfunc;
		void* newfunc;
		void* nextfunc;
		int nextsize;
		bool Hooked;
		void Hook(void* oldfkt, void* yourfkt, void*& newfkt);
		void UnHook();
		bool CheckHooked();
};

class APIHookList
{
	public: 
		void Hook(void* oldfkt, void* yourfkt, void*& newfkt);
		void UnHook(void* oldfkt);
		bool CheckHooked();
		vector<APIHookItem> List;
};

void memcopy(void* toaddr, void* fromaddr,int a);
DWORD GetFuncStartAddress(void* p);
int GetFuncLength(void* p);

typedef PVOID (WINAPI *AddVectoredExceptionHandlerFunc)(ULONG FirstHandler, PVECTORED_EXCEPTION_HANDLER VectoredHandler);
typedef ULONG (WINAPI *RemoveVectoredExceptionHandlerFunc)(PVOID VectoredHandlerHandle); 

FARPROC DAC_GetProcAddress(HANDLE hModule, char *lpProcName);

extern APIHookList apiHookList;

#endif