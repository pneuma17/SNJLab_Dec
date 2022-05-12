
// SNJLab_Test3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSNJLab_Test3App:
// See SNJLab_Test3.cpp for the implementation of this class
//

class CSNJLab_Test3App : public CWinApp
{
public:
	CSNJLab_Test3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSNJLab_Test3App theApp;