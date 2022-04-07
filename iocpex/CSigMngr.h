/**
 * (C)2003-2006 David "BAILOPAN" Anderson
 * Counter-Strike: Deathmatch
 *
 * Licensed under the GNU General Public License, version 2
 */

#ifndef _INCLUDE_CSIGMNGR_H
#define _INCLUDE_CSIGMNGR_H

struct signature_t
{
	void *allocBase;
	void *memInBase;
	size_t memSize;
	void *offset;
	const char *sig;
	size_t siglen;
};

class CSigMngr
{
public:
	void *ResolveSig(void *memInBase, const char *pattern, size_t siglen);
	int ResolvePattern(void *memInBase, const char *pattern, size_t siglen, int number, ...);
private:
	bool ResolveAddress(signature_t *sigmem);
};

extern CSigMngr g_SigMngr;


#define RESOLVE_SIG_FROM_ADDRESS(arrdess, var, type, sig) \
	var = (type)(g_SigMngr.ResolveSig((void *)arrdess, sig, sig##_BYTES)); 


inline BOOL UTIL_MemProtect(void *addr, int length, int prot)
{
	DWORD old_prot;
	return VirtualProtect(addr, length, prot, &old_prot);
}

inline void ModifyMemory(void* pBase, size_t dwSize, void* pCode)
{
	DWORD dwOldFlag = 0;
	VirtualProtect(pBase, dwSize, PAGE_EXECUTE_READWRITE, &dwOldFlag); // Modify DesFunc Memory Access
	memcpy(pBase, pCode, dwSize);
	VirtualProtect(pBase, dwSize, dwOldFlag, &dwOldFlag); // Fix DesFunc Memory Access
}


/*
// (1)4554 0x35A6C90
// (2)4554 swds.dll + 0x36510
// 3382 // swds.dll + 0x2C830
0359C830   /$  55                 push ebp
0359C831   |.  8BEC               mov ebp,esp
0359C833   |.  D945 08            fld dword ptr ss:[ebp+8]
0359C836   |.  DC1D F8E86B03      fcomp qword ptr ds:[36BE8F8]
0359C83C   |.  53                 push ebx
0359C83D   |.  56                 push esi
0359C83E   |.  57                 push edi
0359C83F   |.  DFE0               fstsw ax
0359C841   |.  F6C4 41            test ah,41
0359C844   |.  7A 07              jpe short swds.0359C84D
0359C846   |.  BB 01000000        mov ebx,1
0359C84B   |.  EB 02              jmp short swds.0359C84F
0359C84D   |>  33DB               xor ebx,ebx
0359C84F   |>  D945 08            fld dword ptr ss:[ebp+8]
0359C852   |.  E8 E93A1000        call swds.036A0340
0359C857   |.  8BC8               mov ecx,eax
0359C859   |.  99                 cdq
...
...
0359C8B3   \.  C3                 retn
*/
#define SWDS_SV_SOUND_16_15 "\x55\x8B\xEC\xD9\x45\x2A\xDC\x1D\x2A\x2A\x2A\x2A\x53\x56\x57\xDF\xE0\xF6\xC4\x2A\x7A\x2A\xBB\x2A\x2A\x2A\x2A\xEB\x2A\x33\xDB\xD9\x45\x2A\xE8\x2A\x2A\x2A\x2A\x8B\xC8\x99"
#define SWDS_SV_SOUND_16_15_BYTES 42

#endif //_INCLUDE_CSIGMNGR_H
