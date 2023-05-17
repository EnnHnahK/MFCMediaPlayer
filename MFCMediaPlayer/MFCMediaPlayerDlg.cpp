
// MFCMediaPlayerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCMediaPlayer.h"
#include "MFCMediaPlayerDlg.h"
#include "afxdialogex.h"
#include <dshow.h>

#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define WM_GRAPHNOTIFY  WM_APP + 1
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCMediaPlayerDlg dialog



CMFCMediaPlayerDlg::CMFCMediaPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMEDIAPLAYER_DIALOG, pParent)
	, m_objPlayListDlg(this)
	, m_objVideoDlg(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICONPROJECT);
}

void CMFCMediaPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SLIDERTIME, m_objSliderCtrl);
    DDX_Control(pDX, IDC_SLIDERVOLUME, m_objVolumeCtrl);
	DDX_Control(pDX, IDC_FILEPLAY, m_statFile);
	DDX_Control(pDX, IDC_PLAYTIME, m_objTimePlay);
}

BEGIN_MESSAGE_MAP(CMFCMediaPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCMediaPlayerDlg::OnBnClickedOk)
	ON_MESSAGE(WM_GRAPHNOTIFY, GraphNotify)
	ON_BN_CLICKED(IDC_LISTBUTTON, &CMFCMediaPlayerDlg::OnBnClickedListbutton)
	ON_BN_CLICKED(IDC_BUTTONMOVE, &CMFCMediaPlayerDlg::OnBnClickedButtonmove)
	ON_BN_CLICKED(IDCANCEL, &CMFCMediaPlayerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_STOPBUTTON, &CMFCMediaPlayerDlg::OnBnClickedStopbutton)
	ON_BN_CLICKED(IDC_PAUSEBUTTON, &CMFCMediaPlayerDlg::OnBnClickedPausebutton)
	ON_BN_CLICKED(IDC_OPENBUTTON, &CMFCMediaPlayerDlg::OnBnClickedOpenbutton)
    ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERVOLUME, &CMFCMediaPlayerDlg::OnNMCustomdrawSlidervolume)
END_MESSAGE_MAP()



// CMFCMediaPlayerDlg message handlers

BOOL CMFCMediaPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	m_objVideoDlg.Create(IDD_VIDEODIALOG, this);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	strcpy_s(m_cFileToPlay, (LPCSTR)(CStringA)"");
	m_PlayState = Running;

	m_objSliderCtrl.EnableWindow(0);
    m_objVolumeCtrl.EnableWindow(0);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCMediaPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CMFCMediaPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    static OAFilterState state;
    static BOOL bStartOfScroll = TRUE;

    short int userReq = nSBCode;
    if (pScrollBar->GetDlgCtrlID() == 1010)
    {
        if (userReq == TB_ENDTRACK || userReq == TB_THUMBTRACK)
        {
            DWORD dwPosition = m_objSliderCtrl.GetPos();
            // Pause when scroll action begins.
            if (bStartOfScroll)
            {
                m_objMediaControl->GetState(10, &state);
                bStartOfScroll = FALSE;
                m_objMediaControl->Pause();
            }
            // Update the position continuously.
            REFERENCE_TIME newTime = (l_time / 100) * dwPosition;
            m_objMediaSeeking->SetPositions(&newTime, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
            // Restore the state at the end.
            if (userReq == TB_ENDTRACK)
            {
                if (state == State_Stopped)
                    m_objMediaControl->Stop();
                else if (state == State_Running)
                    m_objMediaControl->Run();
                bStartOfScroll = TRUE;
            }
        }
    }
    else if (pScrollBar->GetDlgCtrlID() == 1014) {
        OutputDebugStringA("run");
    }
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCMediaPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCMediaPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCMediaPlayerDlg::PlayMedia(CString NameFile)
{
   
	//Copy File Name
	wcsncpy_s(l_wFileName, T2W((LPTSTR)(LPCTSTR)NameFile), wcslen(l_wFileName) - 1);

	HRESULT hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		MessageBox(_T("COM not init"), _T("Warning"), MB_OK | MB_ICONWARNING);
	}

	//create result object on the local system
	m_objHRsult = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_objGraphBuilder);

	if (FAILED(m_objHRsult))
	{
		MessageBox(_T("COM Not Registered"), _T("Warning"), MB_OK | MB_ICONWARNING);
		return;
	}

	CRect rectMain, rectVideo;
	RECT rectt, rectM;
	this->GetWindowRect(&rectVideo);
	m_objVideoDlg.GetWindowRect(&rectMain);
	m_objVideoDlg.GetClientRect(&rectt);

	GetClientRect(&rectM);
	ClientToScreen(&rectM);

	m_objHRsult = m_objGraphBuilder->RenderFile(l_wFileName, NULL);
	m_objHRsult = m_objGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_objMediaControl);
	m_objHRsult = m_objGraphBuilder->QueryInterface(IID_IMediaEventEx, (void**)&m_objMediaEvent);
	m_objHRsult = m_objGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_objVideownd);
	m_objHRsult = m_objGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&m_objMediaSeeking);
	m_objHRsult = m_objGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_objMediaPos);
	m_objHRsult = m_objGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_objBA);
	m_objHRsult = m_objGraphBuilder->QueryInterface(IID_IBasicVideo, (void**)&m_objBV);

	m_objHRsult = m_objGraphBuilder->QueryInterface(__uuidof(IVideoFrameStep), (PVOID*)&m_objVideoFrame);

	m_objMediaEvent->SetNotifyWindow((OAHWND)m_objVideoDlg.GetSafeHwnd(), WM_GRAPHNOTIFY, 0);

	///Sets the owner window
	m_objVideownd->put_Owner((OAHWND)m_objVideoDlg.GetSafeHwnd());
	m_objVideownd->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	LONG lHeight, lWidth;
	HRESULT hrr;
	hrr = m_objBV->GetVideoSize(&lHeight, &lWidth);

    m_objVideoDlg.SetWindowPos(NULL, rectM.left, rectM.top, lWidth, lHeight, SWP_SHOWWINDOW);
    m_objVideoDlg.GetClientRect(&rectt);
    m_objVideownd->SetWindowPosition(rectt.left, rectt.top, rectt.right, rectt.bottom);
}

void CMFCMediaPlayerDlg::Pause()
{
	if (!m_objMediaControl)
	{
		MessageBox(_T("No media ctrl"), _T("Warning"), MB_OK | MB_ICONWARNING);
		return;
	}
	OutputDebugStringA("running");
	if ((m_PlayState == Paused) || (m_PlayState == Stopped))
	{
		if (SUCCEEDED(m_objMediaControl->Run()))
		{
			m_PlayState = Running;
			GetDlgItem(IDC_PAUSEBUTTON)->SetWindowText(TEXT("Pause"));
			OutputDebugStringA("running");
		}
	}
	else
	{
		if (SUCCEEDED(m_objMediaControl->Pause()))
		{
			m_PlayState = Paused;
			GetDlgItem(IDC_PAUSEBUTTON)->SetWindowText(TEXT("Resume"));
			OutputDebugStringA("running");
		}
	}
}

LRESULT CMFCMediaPlayerDlg::GraphNotify(WPARAM pwParam, LPARAM plParam)
{
	HandleGraphEvent();
	return LRESULT();
}

HRESULT CMFCMediaPlayerDlg::HandleGraphEvent()
{
	if (m_objMediaEvent == NULL)
	{
		MessageBox(_T("No media event init"), _T("Warning"), MB_OK | MB_ICONWARNING);
		return S_OK;
	}

	long m_lEvCode, m_lParam1, m_lParam2;
	HRESULT m_iHr = S_OK;

	while (SUCCEEDED(m_objMediaEvent->GetEvent(&m_lEvCode, (LONG_PTR*)&m_lParam1, (LONG_PTR*)&m_lParam2, 0)))
	{
		m_objMediaEvent->FreeEventParams(m_lEvCode, m_lParam1, m_lParam2);

		// If this is the end of the clip, reset to beginning
		if (EC_COMPLETE == m_lEvCode)
		{
			LONGLONG l_pos = 0;

			// Reset to first frame of movie
			m_iHr = m_objMediaSeeking->SetPositions(&l_pos, AM_SEEKING_AbsolutePositioning,
				NULL, AM_SEEKING_NoPositioning);
			if (FAILED(m_iHr))
			{

				if (FAILED(m_iHr = m_objMediaControl->Stop()))
				{
					break;
				}

				if (FAILED(m_iHr = m_objMediaControl->Run()))
				{
					break;
				}
			}
		}
	}
	return m_iHr;
}


void CMFCMediaPlayerDlg::OnBnClickedListbutton()
{
	CRect rect;
	this->GetWindowRect(&rect);
	m_objPlayListDlg.Create(IDD_DIALOGPLAYLIST, this);
	m_objPlayListDlg.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTBUTTON)->EnableWindow(0);
	/*	if(m_objPlayListDlg.IsWindowEnabled()){
		MessageBox(_T("Dialog has been Opened"), _T("Warning"), MB_OK | MB_ICONWARNING);
		m_objPlayListDlg.EndDialog(IDD_DIALOGPLAYLIST);
	}
	*/

}


void CMFCMediaPlayerDlg::OnBnClickedButtonmove()
{
	StepFrameFwd();
}


void CMFCMediaPlayerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCMediaPlayerDlg::OnBnClickedStopbutton()
{
	HRESULT l_hResult;

	if ((!m_objMediaControl) || (!m_objMediaSeeking))
	{
		return;
	}

	if ((m_PlayState == Paused) || (m_PlayState == Running))
	{
		LONGLONG l_tagPos = 0;
		l_hResult = m_objMediaControl->Stop();
		m_PlayState = Stopped;

		// Seek to the beginning
		l_hResult = m_objMediaSeeking->SetPositions(&l_tagPos, AM_SEEKING_AbsolutePositioning,
			NULL, AM_SEEKING_NoPositioning);

		// Display the first frame to indicate the reset condition
		l_hResult = m_objMediaControl->Pause();
	}
}


void CMFCMediaPlayerDlg::OnBnClickedOk()
{
	//Playlist processing
	if (m_objPlayListDlg) {
		//Gets the file name selected from playlist
		int l_selectedItem = m_objPlayListDlg.m_objPlayList.GetCurSel();
		if (l_selectedItem != LB_ERR)
		{
			//Gets Path of file
			strcpy_s(m_cFileToPlay, m_objPlayListDlg.m_cFilePath[l_selectedItem]);

			m_objPlayListDlg.m_objPlayList.GetText(l_selectedItem, m_strFileName);
		}
	}

	sliderAvailable = FALSE;
	caps = AM_SEEKING_CanSeekAbsolute | AM_SEEKING_CanGetDuration;


	//If no file is selected 
	if (m_cFileToPlay[0] == 0)
	{
		MessageBox(_T("Choose a file to play"), _T("Warning"), MB_OK | MB_ICONWARNING);
		return;
	}

	PlayMedia(CString(m_cFileToPlay));


	if (SUCCEEDED(m_objHRsult))
	{
		int i = SetTimer(1, 1000, (TIMERPROC)NULL);
        m_objVideoDlg.ShowWindow(SW_SHOW);

		//Runs media
		m_objHRsult = m_objMediaControl->Run();
		TCHAR* l_strPlay = _T("Playing");
		m_statFile.SetWindowText(_T("Playing ") + m_strFileName);
		m_objVideoDlg.SetWindowText(m_strFileName);
		sliderAvailable = (S_OK == m_objMediaSeeking->CheckCapabilities(&caps));
		if (sliderAvailable)
		{
			m_objSliderCtrl.EnableWindow(1);
            m_objVolumeCtrl.EnableWindow(1);
			m_objMediaSeeking->GetDuration(&l_time);
		}
	}
}


void CMFCMediaPlayerDlg::OnBnClickedPausebutton()
{
	Pause();
}


void CMFCMediaPlayerDlg::OnBnClickedOpenbutton()
{
	TCHAR fileFilters[] = _T("AVI (*.avi)|*.avi|MPEG (*.mpeg)|*.mpeg|MP3 (*.mp3)|*.mp3|MP4 (*.mp4)|*.mp4|");

	CFileDialog m_objFileOpen(TRUE, 0, 0, OFN_FILEMUSTEXIST, fileFilters);

	if (m_objFileOpen.DoModal() == IDOK) {
		if (m_objPlayListDlg) m_objPlayListDlg.m_objPlayList.SetCurSel(-1);

		m_strFileName = m_objFileOpen.GetFileName();
		m_strFilePath = m_objFileOpen.GetPathName();

		strcpy_s(m_cFileToPlay,(LPCSTR)(CStringA)m_strFilePath);
		//OnBnClickedOk();
	}
}

void CMFCMediaPlayerDlg::OnTimer(UINT nIDEvent)
{
	REFERENCE_TIME timeNow;
	CString l_PlayTime;
    CString l_Playtimes;
	if (SUCCEEDED(m_objMediaSeeking->GetCurrentPosition(&timeNow)))
	{
		l_PlayTime.Format(_T("%d"), (timeNow / 10000000) - (timeNow / 10000000 / 60)*60);
        l_Playtimes.Format(_T("%d : "), timeNow / 10000000 / 60);
		m_objTimePlay.SetWindowText(l_Playtimes + l_PlayTime);
		long sliderTick = (long)((timeNow * 100) / l_time);
		m_objSliderCtrl.SetPos(sliderTick);
	}
	CDialog::OnTimer(nIDEvent);


}

HRESULT CMFCMediaPlayerDlg::StepFrameFwd()
{
	HRESULT l_hResult = S_OK;

	if (m_objVideoFrame)
	{
		if (l_hResult = m_objVideoFrame->CanStep(15, NULL) == S_OK)
		{
			if (m_PlayState != Paused)
			{
				Pause();
			}
			l_hResult = m_objVideoFrame->Step(15, NULL);
		}
	}

	return l_hResult;
}


int CMFCMediaPlayerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialogEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}


LRESULT CMFCMediaPlayerDlg::OnNcHitTest(CPoint point)
{
    return CDialogEx::OnNcHitTest(point);
}



void CMFCMediaPlayerDlg::OnNMCustomdrawSlidervolume(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDERVOLUME);
    CStatic* label = (CStatic*)GetDlgItem(IDC_STATIC);
    slider->SetRange(0, 65535);
    int pos = slider->GetPos();
    waveOutSetVolume(NULL, pos);
    *pResult = 0;
}
