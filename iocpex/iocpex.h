// iocpex.h : iocpex DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "sdk\amxxmodule.h"
#include <extdll.h>
#include <meta_api.h>

// CiocpexApp
// �йش���ʵ�ֵ���Ϣ������� iocpex.cpp
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