
// taesync's gui.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtaesyncsguiApp:
// �йش����ʵ�֣������ taesync's gui.cpp
//

class CtaesyncsguiApp : public CWinApp
{
public:
	CtaesyncsguiApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtaesyncsguiApp theApp;