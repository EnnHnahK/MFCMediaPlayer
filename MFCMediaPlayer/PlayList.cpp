#include "pch.h"
#include "PlayList.h"

IMPLEMENT_DYNAMIC(CPlayList, CListBox)

BEGIN_MESSAGE_MAP(CPlayList, CListBox)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


CPlayList::CPlayList()
{
}

CPlayList::~CPlayList()
{
}

void CPlayList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CListBox::OnLButtonDblClk(nFlags, point);
}