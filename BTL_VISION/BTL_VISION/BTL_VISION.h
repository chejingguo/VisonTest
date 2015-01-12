// BTL_VISION.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CBTL_VISIONApp:
// See BTL_VISION.cpp for the implementation of this class
//

class CBTL_VISIONApp : public CWinApp
{
public:
	CBTL_VISIONApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CBTL_VISIONApp theApp;