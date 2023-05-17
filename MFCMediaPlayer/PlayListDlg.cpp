// PlayListDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCMediaPlayer.h"
#include "afxdialogex.h"
#include "PlayListDlg.h"
#include "framework.h"
#include "dshow.h"



// CPlayListDlg dialog

IMPLEMENT_DYNAMIC(CPlayListDlg, CDialogEx)

CPlayListDlg::CPlayListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGPLAYLIST, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDI_ICONMUSIC);
}

CPlayListDlg::~CPlayListDlg()
{
}

void CPlayListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTITEM, m_objPlayList);
	DDX_Control(pDX, IDC_BUTTONADD, m_objAddBtnPlayList);
}


BEGIN_MESSAGE_MAP(CPlayListDlg, CDialogEx)
	ON_BN_CLICKED(IDCLOSE, &CPlayListDlg::OnBnClickedClose)
    ON_WM_LBUTTONDBLCLK()
    ON_WM_NCHITTEST()
    ON_BN_CLICKED(IDC_BUTTONADD, &CPlayListDlg::OnBnClickedButtonadd)
END_MESSAGE_MAP()


// CPlayListDlg message handlers


BOOL CPlayListDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    this->SetWindowText(TEXT("Play List"));
    m_objPlayList.AddString(TEXT(""));
    i = 0;
    CWnd* wnd = GetParent();
    CRect rect, rectPlayWnd;
    wnd->GetWindowRect(&rect);
    this->GetWindowRect(&rectPlayWnd);
    this->MoveWindow(rect.right, rect.top, rectPlayWnd.Width(), rectPlayWnd.Height());

    return 0;
}

void CPlayListDlg::OnBnClickedClose()
{
	OnClose();
}

void CPlayListDlg::OnAddFile()
{
    POSITION ps;;
    USES_CONVERSION;
    int l_nStartPos, l_nPos = 0;
    TCHAR szFilters[] = _T("AVI (*.avi)|*.avi|MPEG (*.mpeg)|*.mpeg|MP3 (*.mp3)|*.mp3||");
    CFileDialog m_objFileDlg(TRUE, _T("avi"), _T("*.avi"), OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER, szFilters);

    CString m_strFilePath[MAX_PATH];
    if (m_objFileDlg.DoModal() == IDOK)
    {
        ps = m_objFileDlg.GetStartPosition();

        while (ps)
        {
            CString m_strFilePth = m_objFileDlg.GetNextPathName(ps);     
            strcpy_s(m_cFilePath[i], CStringA(m_strFilePth).GetString());
            l_nStartPos = m_strFilePth.Find(_T("\\"), l_nPos);
    
            do
            {
                l_nPos = l_nStartPos + 1;            
                l_nStartPos = m_strFilePth.Find(_T("\\"), l_nPos);

            } while (l_nStartPos > 0);
            m_strFileName = m_strFilePth.Mid(l_nPos, m_strFilePth.GetLength());
            m_objPlayList.InsertString(i, m_strFileName);
            OutputDebugStringA(m_cFilePath[i]);             
            ++i;
        }

    }
}


void CPlayListDlg::OnRemoveFile()
{
    int l_iCurrSel = m_objPlayList.GetCurSel();
    m_objPlayList.DeleteString(l_iCurrSel);
}


void CPlayListDlg::OnClose() {
	EndDialog(0);
	isActive = FALSE;
}



void CPlayListDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    CDialogEx::OnLButtonDblClk(nFlags, point);
}


LRESULT CPlayListDlg::OnNcHitTest(CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    return CDialogEx::OnNcHitTest(point);
}


void CPlayListDlg::OnBnClickedButtonadd()
{
    CMenu l_objMenuAdd;
    VERIFY(l_objMenuAdd.LoadMenu(IDR_MENUADD));
    CMenu* l_pobjPopupMenu = l_objMenuAdd.GetSubMenu(0);
    ASSERT(l_pobjPopupMenu != NULL);

    CRect  l_tagRectButton;
    m_objAddBtnPlayList.GetWindowRect(&l_tagRectButton);

    int l_nMenuName = l_pobjPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD, l_tagRectButton.left, l_tagRectButton.bottom, GetParent());

    switch (l_nMenuName)
    {
    case ID_ADD_ADDFILE:
        OnAddFile();
        break;
    case ID_ADD_REMOVEFILE:
        OnRemoveFile();
        break;
    }
}
