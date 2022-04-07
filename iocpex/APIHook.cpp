#include "stdafx.h"
#include <windows.h>
#include <mmsystem.h>
#include <map>
#include <vector>
#include <list>
#include <tlhelp32.h>
#include "APIHook.h"
//#include "LogFile.h"

const int OP_eins = -1;
const int OPnull = 0;
const int OPeins = 1;
const int OPzwei = 2;
const int OPdrei = 3;
const int OPvier = 4;
const int OPfuenf = 5;
const int OPsechs = 6;
const int OPsieben = 7;
const int OPacht = 8;
const int OPneun = 9;
const int OPzehn = 10;
const int OPtable7 = 11;
const int OPtable2 = 12;
const int OPtable5 = 15; 
const int OPtable6 = 16; 
const int OPtableFF = 17;
const int OPtableF7 = 18;
const int OPtable8 = 19;
const int OPtableFE = 20;
const int OPtableDD = 21; 
const int OPtable0F = 22;
const int OPtable = 23;

const int firsttable[256] =
{
	OPtable2, OPtable2, OPtable2, OPtable2, OPeins, OPvier, OPnull, OPnull, OPtable2, OPtable2, OPtable2, OPtable2, OPeins, OPvier, OPnull, OPtable0F,
	OPtable2, OPtable2, OPtable2, OPtable2, OPeins, OPvier, OPnull, OPnull, OPtable2, OPtable2, OPtable2, OPtable2, OPeins, OPvier, OPnull, OPnull,
	OPtable2, OPtable2, OPtable2, OPtable2, OPeins, OPvier, OPtable, OPnull, OPtable2, OPtable2, OPtable2, OPtable2, OPeins, OPvier, OPtable, OPnull,
	OPtable2, OPtable2, OPtable2, OPtable2, OPeins, OPvier, OPtable, OPnull, OPtable2, OPtable2, OPtable2, OPtable2, OPeins, OPvier, OPtable, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPtable2, OPtable2, OPtable, OPtable, OPtable, OPtable5, OPvier, OPtable6, OPeins, OPtable7, OPnull, OPnull, OPnull, OPnull,
	OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins,
	OPtable7, OPtable6, OPtable7, OPtable7, OPtable2, OPtable2, OPtable2, OPtable2, OPtable2, OPtable2, OPtable2, OPtable2, OPtable2, OPtable2, OPtable2, OPtable2,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPsechs, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPvier, OPvier, OPvier, OPvier, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier,
	OPtable7, OPzwei, OPzwei, OPnull, OPtable2, OPtable2, OPtable7, OPtable6, OPvier, OPnull, OPzwei, OPnull, OPnull, OPeins, OPnull, OPnull,
	OPtable2, OPtable2, OPtable2, OPtable2, OPeins, OPeins, OPnull, OPnull, OPtable2, OPtable2, OPtable2, OPtable2, OPtable2, OPtableDD, OPtable2, OPtable2,
	OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPvier, OPvier, OPsechs, OPeins, OPnull, OPnull, OPnull, OPnull,
	OPtable, OPnull, OPtable, OPtable, OPnull, OPnull, OPtable8, OPtableF7, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPtableFE, OPtableFF
};

const int secondtable[256] =
{
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull
};

const int fftable[256] =
{
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins
};

const int f7table[256] =
{
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPacht, OPvier, OPvier, OPeins, OPeins, OPeins, OPeins, OPzwei, OPfuenf, OPeins, OPeins,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPvier, OPvier, OPvier, OPvier, OPsechs, OPfuenf, OPfuenf, OPfuenf, OPzwei, OPzwei, OPzwei, OPzwei, OPzwei, OPzwei, OPzwei, OPzwei,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPacht, OPacht, OPacht, OPacht, OPneun, OPacht, OPacht, OPacht, OPfuenf, OPfuenf, OPfuenf, OPfuenf, OPsechs, OPfuenf, OPfuenf, OPfuenf,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull
};

const int table8[256] =
{
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPfuenf, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPfuenf, OPeins, OPeins,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPzwei, OPzwei, OPzwei, OPzwei, OPdrei, OPzwei, OPzwei, OPzwei, OPzwei, OPzwei, OPzwei, OPzwei, OPdrei, OPzwei, OPzwei, OPzwei,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPfuenf, OPfuenf, OPfuenf, OPfuenf, OPsechs, OPfuenf, OPfuenf, OPfuenf, OPfuenf, OPfuenf, OPfuenf, OPfuenf, OPsechs, OPfuenf, OPfuenf, OPfuenf,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull
};

const int fetable[256] =
{
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins
};

const int ddtable[256] =
{
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPeins, OPvier, OPnull, OPnull,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPeins, OPzwei, OPeins, OPeins, OPeins,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPvier, OPvier, OPvier, OPvier, OPfuenf, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPfuenf, OPnull, OPvier, OPvier,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OP_eins, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OP_eins, OPnull, OPnull
};

const int table0f[256] =
{
	OPtable, OPtable, OPtable, OPtable, OP_eins, OP_eins, OPnull, OP_eins, OPnull, OP_eins, OP_eins, OPnull, OP_eins, OPtable, OPnull, OPtable,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPtable, OPtable, OPtable, OPtable, OPtable, OP_eins, OPtable, OP_eins, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins, OP_eins,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OP_eins, OP_eins, OPtable, OPtable,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable,
	OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier, OPvier,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable,
	OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull, OPnull,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable,
	OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable, OPtable
};

typedef FARPROC (WINAPI *GetProcAddressFunc)(HMODULE hModule, LPCSTR lpProcName);
typedef VOID (WINAPI *SleepFunc)(DWORD dwMilliseconds);
typedef VOID (WINAPI *MessageBoxAFunc)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
typedef LONG (APIENTRY *RegOpenKeyExAFunc)(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
typedef LONG (APIENTRY *RegQueryValueExAFunc)(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
typedef LONG (APIENTRY *RegCloseKeyFunc)(HKEY hKey);
typedef HANDLE (WINAPI *OpenProcessFunc)(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
typedef BOOL (WINAPI *TerminateProcessFunc)(HANDLE hProcess, UINT uExitCode);
typedef BOOL (WINAPI *ClientToScreenFunc)(HWND hWnd, LPPOINT lpPoint);
typedef BOOL (WINAPI *ScreenToClientFunc)(HWND hWnd, LPPOINT lpPoint);
typedef LONG (WINAPI *UnhandledExceptionFilterFunc)(struct _EXCEPTION_POINTERS *ExceptionInfo);

FARPROC (WINAPI *pGetProcAddress)(HMODULE hModule, LPCSTR lpProcName);
BOOL (WINAPI *pQueryPerformanceCounter)(LARGE_INTEGER*);
DWORD (WINAPI *ptimeGetTime)(void);
VOID (WINAPI *pExitProcess)(UINT uExitCode);
HMODULE (WINAPI *pLoadLibraryA)(LPCSTR lpLibFileName);
UINT (WINAPI *pGetSystemDirectoryA)(LPSTR lpBuffer, UINT uSize);
DWORD (WINAPI *pGetModuleFileNameA)(HMODULE hModule, LPCH lpFilename,DWORD nSize);
HMODULE (WINAPI *pGetModuleHandleA)(LPCSTR lpModuleName);
BOOL (WINAPI *pGetExitCodeThread)(HANDLE hThread, LPDWORD lpExitCode);
VOID (WINAPI *pSleep)(DWORD dwMilliseconds);
HANDLE (WINAPI *pOpenProcess)(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
BOOL (WINAPI *pToolhelp32ReadProcessMemory)(DWORD th32ProcessID, LPCVOID lpBaseAddress, LPVOID lpBuffer, DWORD cbRead, LPDWORD lpNumberOfBytesRead);
BOOL (WINAPI *pFreeLibrary)(HMODULE hLibModule);
BOOL (WINAPI *pClientToScreen)(HWND hWnd, LPPOINT lpPoint);
BOOL (WINAPI *pScreenToClient)(HWND hWnd, LPPOINT lpPoint);
LPTOP_LEVEL_EXCEPTION_FILTER (WINAPI *pSetUnhandledExceptionFilter)(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
PVOID (WINAPI *pAddVectoredExceptionHandler)(ULONG FirstHandler, PVECTORED_EXCEPTION_HANDLER VectoredHandler);
LONG (WINAPI *pUnhandledExceptionFilter)(struct _EXCEPTION_POINTERS *ExceptionInfo);
HFILE (WINAPI *plopen)(LPCSTR lpPathName, int iReadWrite);
HANDLE (WINAPI *pCreateFileW)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

SleepFunc SleepPtr;
MessageBoxAFunc MessageBoxAPtr;
RegOpenKeyExAFunc RegOpenKeyExAPtr;
RegQueryValueExAFunc RegQueryValueExAPtr;
RegCloseKeyFunc RegCloseKeyPtr;
OpenProcessFunc OpenProcessPtr;
TerminateProcessFunc TerminateProcessPtr;
GetProcAddressFunc GetProcAddressPtr;
ClientToScreenFunc ClientToScreenPtr;
ScreenToClientFunc ScreenToClientPtr;
AddVectoredExceptionHandlerFunc pAddVEH; 
RemoveVectoredExceptionHandlerFunc pRemoveVEH;

FARPROC GetProcAddressEx(HANDLE hModule,LPCSTR lpProcName);

extern bool ThreadActive;

void SetErrorValue(BYTE value);
BYTE GetErrorValue();

PIMAGE_DOS_HEADER  pDosHeader;
PIMAGE_NT_HEADERS  pNTHeaders;
PIMAGE_OPTIONAL_HEADER   pOptHeader;
PIMAGE_IMPORT_DESCRIPTOR  pImportDescriptor;
PIMAGE_THUNK_DATA         pThunkData;
PIMAGE_IMPORT_BY_NAME     pImportByName;
HMODULE hMod;

//HANDLE WINAPI newCreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);
//DWORD gpoffset;
//DWORD gppt=(DWORD)&newCreateFileA;

APIHookList apiHookList;

//===================================================================================
int InStrLength(void* p)
{
	int anzahl = 1;
	bool fertig = false;
	BYTE *b = (BYTE*)p;

	do
	{
		switch(firsttable[*b])
		{
		case -1:
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			anzahl +=firsttable[*b];
			fertig = true;
			break;

		case OPtable:
			anzahl++;
			b++;
			break;

		case OPtable2:
			anzahl++;
			b++;
			anzahl += secondtable[*b];
			fertig = true;
			break;

		case OPtable7:
			anzahl++;
			b++;
			anzahl += secondtable[*b] + 1;
			fertig = true;
			break;

		case OPtable6:
			anzahl++;
			b++;
			anzahl += secondtable[*b] + 4;
			fertig = true;
			break;

		case OPtableFF:
			anzahl++;
			b++;
			anzahl += fftable[*b];
			fertig = true;
			break;

		case OPtableF7:
			anzahl++;
			b++;
			anzahl += f7table[*b];
			fertig = true;
			break;

		case OPtableFE:
			anzahl++;
			b++;
			anzahl += fetable[*b];
			fertig = true;
			break;

		case OPtableDD:
			anzahl++;
			b++;
			anzahl += ddtable[*b];
			fertig = true;
			break;

		case OPtable8:
			anzahl++;
			b++;
			anzahl += table8[*b];
			fertig = true;
			break;

		case OPtable0F:
			anzahl++;
			b ++;
			if ((table0f[*b] >= -1) && (table0f[*b] <= 10))
			{
				anzahl += table0f[*b];
				fertig = true;
			}
			break;

		default :
			fertig = true;
		}
	} while (!fertig);
	return anzahl;
}

//===================================================================================
void memcopy(void *toaddr, void* fromaddr,int a)
{
	BYTE *b1, *b2;
	int i;
	DWORD old, old2;

	VirtualProtect(toaddr, a, PAGE_EXECUTE_READWRITE, &old);
	VirtualProtect(fromaddr, a, PAGE_EXECUTE_READWRITE, &old2);

	for (i = 0; i <a ;i++)
	{
		b1 = (BYTE*) fromaddr + i;
		b2 = (BYTE*) toaddr + i;
		*b2 = *b1;
	}

	VirtualProtect(toaddr, a, old, &old);
	VirtualProtect(fromaddr, a, old2, &old2);
}

//===================================================================================
DWORD GetFuncStartAddress(void* p)
{
	int len = GetFuncLength(p);
	int a = 0;

	int c = 999;
	while (c > len)
	{
		a--;
		c = GetFuncLength((DWORD*)(int(p) + a));
	}

	DWORD StartAddress = (DWORD)(int(p) + a + 1);

	BYTE* b = (BYTE*)StartAddress;
	int d, e;
	e = 0;
	while ((*b == 0x90))
	{
		d = InStrLength(b);
		b = (BYTE *)((int)b + d);
		e += d;
	}

	return StartAddress + e;
}

//===================================================================================
int GetFuncLength(void* p)
{
	BYTE *b;
	int a, c;
	b = (BYTE *)p;
	c = 0;
	while ((*b != 0xC3) && (*b != 0xC2))
	{
		a = InStrLength(b);
		b = (BYTE *)((int)b + a);
		c += a;
	}
	c += InStrLength(b);
	return c;
}

//===================================================================================
FARPROC GetProcAddress_FromExportOrdinal(PIMAGE_NT_HEADERS pNTHdr, DWORD Ordinal)
{
	PIMAGE_EXPORT_DIRECTORY pExpDir;
	DWORD *pFunctionArray;
	DWORD ImageBase;
	DWORD ExportDirSize;
	char szForwardedModule[MAX_PATH];
	char *pszForwardedFunctionName;
	HANDLE hForwardedMod;
	FARPROC Result;

	ExportDirSize = pNTHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
	if (!ExportDirSize) return NULL;

	ImageBase = pNTHdr->OptionalHeader.ImageBase;

	pExpDir = (PIMAGE_EXPORT_DIRECTORY)(pNTHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress + ImageBase);

	pFunctionArray = (DWORD*)(ImageBase + (DWORD)pExpDir->AddressOfFunctions);

	if (pExpDir->NumberOfFunctions <= (Ordinal - pExpDir->Base)) return NULL;

	Result = (FARPROC)*(DWORD**)((DWORD)pFunctionArray + (Ordinal - pExpDir->Base) * sizeof(DWORD));

	if (Result) Result = (FARPROC)((DWORD)Result + ImageBase);

	if (((DWORD)Result >= (DWORD)pExpDir) && ((DWORD)Result < ((DWORD)pExpDir + ExportDirSize))) 
	{
		lstrcpy(szForwardedModule, (LPCSTR)Result);
		pszForwardedFunctionName = (char*)szForwardedModule;
		while (*(char*)pszForwardedFunctionName != '.') 
		{
			pszForwardedFunctionName ++;
		}
		*(char*)pszForwardedFunctionName = 0;

		pszForwardedFunctionName ++;

		hForwardedMod = GetModuleHandle(szForwardedModule);

		return DAC_GetProcAddress(hForwardedMod, pszForwardedFunctionName);
	}

	return Result;
}

//===================================================================================
FARPROC GetProcAddress_FromExportName(PIMAGE_NT_HEADERS pNTHdr, char *lpszProcName)
{
	PIMAGE_EXPORT_DIRECTORY pExpDir;
	DWORD ImageBase;
	DWORD *pNamesArray;
	DWORD *pNameOrdinalsArray;
	char *pszCurName;  
	DWORD NameOrdinal, index;

	if (!pNTHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size) return NULL;

	ImageBase = pNTHdr->OptionalHeader.ImageBase;

	pExpDir = (PIMAGE_EXPORT_DIRECTORY)(pNTHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress + ImageBase);

	if (!pExpDir->NumberOfNames) return NULL;

	pNamesArray = (DWORD*)(ImageBase + (DWORD)pExpDir->AddressOfNames);

	pNameOrdinalsArray = (DWORD*)(ImageBase + (DWORD)pExpDir->AddressOfNameOrdinals);

	for (index = 0;index < pExpDir->NumberOfNames;index ++)
	{
		pszCurName = (char*)(ImageBase + *(DWORD*)((DWORD)pNamesArray + sizeof(DWORD) * index));

		if (!strcmp(pszCurName, lpszProcName)) break;
	}

	if (index == pExpDir->NumberOfNames) return NULL;

	NameOrdinal = *(WORD*)((DWORD)pNameOrdinalsArray + sizeof(WORD) * index);
	return GetProcAddress_FromExportOrdinal(pNTHdr, NameOrdinal + pExpDir->Base);
}

//===================================================================================
FARPROC DAC_GetProcAddress(HANDLE hModule, char *lpProcName)
{
	PIMAGE_DOS_HEADER DosHeaderPt;
	PIMAGE_NT_HEADERS NtHeadersPt;

	if (!hModule) return NULL;
	DosHeaderPt = (PIMAGE_DOS_HEADER)hModule;

	if (DosHeaderPt->e_magic != IMAGE_DOS_SIGNATURE) return NULL;

	NtHeadersPt = (PIMAGE_NT_HEADERS)(int(DosHeaderPt) + DosHeaderPt->e_lfanew);

	if (NtHeadersPt->Signature != IMAGE_NT_SIGNATURE) return NULL;

	if (!HIWORD((DWORD)lpProcName)) 
	{
		return GetProcAddress_FromExportOrdinal(NtHeadersPt, (DWORD)lpProcName);
	}
	else if (!IsBadStringPtr(lpProcName, 0))
	{
		return GetProcAddress_FromExportName(NtHeadersPt, lpProcName);
	}
	return NULL;
}

//===================================================================================
void APIHookItem::Hook(void* oldfkt, void* yourfkt, void*& newfkt)
{
	int anzahl, gesamt;
	DWORD old;
	JumpCode jmpcode;
	jmpcode.nix = 0x65;
	jmpcode.jmp = 0xE9;
	gesamt = 0;

	if (!oldfkt || !yourfkt) return;

	do{
		VirtualProtect(oldfkt,12,PAGE_EXECUTE_READWRITE,&old);
		anzahl = InStrLength(oldfkt);
		VirtualProtect(oldfkt,anzahl,old,&old);
		oldfkt = (DWORD *)((int)oldfkt+anzahl);
		gesamt += anzahl;
	}while (gesamt < sizeof(JumpCode));
	oldfkt = (DWORD *)((int)oldfkt-gesamt);

	nextsize = gesamt + sizeof(JumpCode);

	newfkt = (DWORD*)new BYTE[nextsize];
	VirtualProtect(oldfkt,gesamt,PAGE_EXECUTE_READWRITE,&old);
	VirtualProtect(newfkt,gesamt+sizeof(JumpCode),PAGE_EXECUTE_READWRITE,&old);

	memcopy(newfkt, oldfkt, gesamt);

	gesamtlength = gesamt;
	gesamtcode = (DWORD*)new BYTE[gesamtlength];
	memcopy(gesamtcode, oldfkt, gesamt);

	jmpcode.distance = ((int)oldfkt + gesamt) - ((int)newfkt + gesamt) - 6;
	memcopy((DWORD *)((int)newfkt + gesamt), (DWORD*)&jmpcode, sizeof(JumpCode));

	jmpcode.distance = (int)yourfkt - (int)oldfkt - 6;
	memcopy(oldfkt, (DWORD*)&jmpcode, sizeof(JumpCode));

	VirtualProtect(oldfkt,gesamt,old,&old);
	VirtualProtect(oldfkt,gesamt+sizeof(JumpCode),old,&old);

	int lenght = GetFuncLength(oldfkt);
	VirtualProtect(oldfkt, lenght, PAGE_EXECUTE_READ, &old);

	oldfunc = oldfkt;
	newfunc = yourfkt;
	nextfunc = newfkt;

	Hooked = true;
}

//===================================================================================
bool APIHookItem::CheckHooked()
{
	int gesamt;
	gesamt = 0;

	if (!oldfunc || !newfunc) return false;

	JumpCode jmpcode;
	memcopy((DWORD*)&jmpcode, oldfunc, sizeof(JumpCode));

	if (jmpcode.distance == (DWORD)newfunc - (DWORD)oldfunc - 6)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

//===================================================================================
void APIHookItem::UnHook()
{
	DWORD old;

	if (!oldfunc || !gesamtlength || !gesamtcode) return;

	Hooked = false;

	VirtualProtect(oldfunc, gesamtlength, PAGE_EXECUTE_READWRITE, &old);

	memcopy(oldfunc, gesamtcode, gesamtlength);

	VirtualProtect(oldfunc, gesamtlength, PAGE_EXECUTE_READ, &old);

	gesamtlength = 0;
	gesamtcode = NULL;
}

//===================================================================================
void APIHookList::Hook(void* oldfkt, void* yourfkt, void*& newfkt)
{
	if (!oldfkt || !yourfkt) return;

	APIHookItem Item;
	List.push_back(Item);
	int index = List.size()-1;

	List[index].Hook(oldfkt, yourfkt, newfkt);
}

//===================================================================================
void APIHookList::UnHook(void* oldfkt)
{
	if (!oldfkt) return;
	for (int i=0;i<List.size();i++)
	{
		if (List[i].oldfunc == oldfkt)
		{
			List[i].UnHook();
		}
	}
}

//===================================================================================
bool APIHookList::CheckHooked()
{
	for (int i=0;i<List.size();i++)
	{
		if (List[i].Hooked && !List[i].CheckHooked())
		{
			return false;
		}
	}
	return true;
}
