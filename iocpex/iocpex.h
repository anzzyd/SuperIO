// iocpex.h : iocpex DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "sdk\amxxmodule.h"
#include <extdll.h>
#include <meta_api.h>

// CiocpexApp
// 有关此类实现的信息，请参阅 iocpex.cpp
//

extern AMX_NATIVE_INFO IOCPEX_NATIVES[];

#define SCPCLR_RED		1
#define SCPCLR_GREEN	2
#define SCPCLR_BLUE		3
#define SCPCLR_PERPLE	4
#define SCPCLR_SBLUE	5
#define SCPCLR_YELLOW	6

#define TZ_PLAYERRESP_LOADING	-1
#define TZ_PLAYERRESP_SUCCESS	1