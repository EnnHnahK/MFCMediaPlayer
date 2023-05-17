#pragma once
#include "pch.h"
#include <afxwin.h>
#include "resource.h"		// main symbols

class CPlayList : public CListBox 
{
    DECLARE_DYNAMIC(CPlayList)
public:
    CPlayList();
    virtual ~CPlayList();
protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);


};
