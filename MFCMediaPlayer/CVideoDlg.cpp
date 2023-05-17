// CVideoDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCMediaPlayer.h"
#include "afxdialogex.h"
#include "CVideoDlg.h"


// CVideoDlg dialog

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIDEODIALOG, pParent)
{

}

CVideoDlg::~CVideoDlg()
{
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoDlg message handlers
