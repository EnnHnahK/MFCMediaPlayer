
// MFCMediaPlayerDlg.h : header file
//
#include <control.h>
#include <dshow.h>
#include "VideoDlg.h"
#include ".\Slider.h"
#include "PlayListDlg.h"
#include "PlayList.h"
#include "mmsystem.h"
#include "windows.h"




#pragma once

enum PLAYSTATE { Stopped, Paused, Running, Init };

// CMFCMediaPlayerDlg dialog
class CMFCMediaPlayerDlg : public CDialogEx
{
// Construction
public:
	CMFCMediaPlayerDlg(CWnd* pParent = nullptr);	// standard constructor

	IGraphBuilder* m_objGraphBuilder;
	IMediaControl* m_objMediaControl;
	IMediaEventEx* m_objMediaEvent;
	IVideoWindow* m_objVideownd;
	IMediaSeeking* m_objMediaSeeking;
	IMediaPosition* m_objMediaPos;
	IBasicAudio* m_objBA;
	IBasicVideo* m_objBV;
	IVideoFrameStep* m_objVideoFrame;

	HRESULT m_objHRsult;

	CString m_strFileName;          //File name
	CString m_strFilePath;          //File path

	BOOL sliderAvailable;           //Available slider control
	DWORD caps;                     //Captions  


	LONGLONG l_time;
    REFERENCE_TIME t_refTime;

	void PlayMedia(CString);
	void Pause();
	afx_msg LRESULT GraphNotify(WPARAM pwParam, LPARAM plParam);
	WCHAR l_wFileName[260];
	HRESULT HandleGraphEvent();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMEDIAPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedListbutton();
	afx_msg void OnBnClickedButtonmove();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStopbutton();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPausebutton();
	afx_msg void OnBnClickedOpenbutton();
	afx_msg void OnTimer(UINT nIDEvent);

	PLAYSTATE m_PlayState;
	HRESULT StepFrameFwd();

	CVideoDlg m_objVideoDlg;
	CPlayListDlg m_objPlayListDlg;
	CPlayList m_objPlayList;
    CSliderCtrl m_objSliderCtrl;
    CSliderCtrl m_objVolumeCtrl;

;
	CStatic m_statFile;                     //Name file
	CStatic m_objStatPlayTime;              
	CStatic m_objTimePlay;  
    LPCWSTR strPlayFile;

	char m_cFileToPlay[MAX_PATH];
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnNcHitTest(CPoint point);
//    afx_msg void OnNMCustomdrawSlidervolume(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMCustomdrawSlidervolume(NMHDR* pNMHDR, LRESULT* pResult);
};

