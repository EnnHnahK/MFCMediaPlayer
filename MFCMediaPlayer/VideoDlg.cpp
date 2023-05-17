// VideoDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCMediaPlayer.h"
#include "afxdialogex.h"
#include "VideoDlg.h"


// CVideoDlg dialog

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIDEODIALOG, pParent)
{

    m_hIcon = AfxGetApp()->LoadIcon(IDI_ICONVIDEO);
}

CVideoDlg::~CVideoDlg()
{
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
	ON_WM_CREATE()
    ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CVideoDlg message handlers


int CVideoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

    CWnd* cwnd = GetParent();
    CRect rect, rectVideo;
    cwnd->GetWindowRect(&rect);
    ClientToScreen(&rect); 
    GetWindowRect(&rectVideo);
    ClientToScreen(&rectVideo);
    SetWindowPos(this, rect.left, rect.top, rectVideo.Width(), rectVideo.Height(), SWP_NOACTIVATE);
	return 0;
}


LRESULT CVideoDlg::OnNcHitTest(CPoint point)
{
    return HTCAPTION;
}


BOOL CVideoDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
