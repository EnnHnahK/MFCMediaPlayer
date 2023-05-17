#pragma once
#include "playlist.h"
#include "afxdialogex.h"
#include "CollectionUtils.h"


// CPlayListDlg dialog

struct listFile	
{
	char m_cFilePath[MAX_PATH];
	struct listFile* m_ptrNext;
	struct listFile* m_ptrPrev;

};

class CPlayListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPlayListDlg)

public:
	CPlayListDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPlayListDlg();

	void OnClose();
	BOOL isActive;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGPLAYLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_objPlayList;
	virtual BOOL OnInitDialog();
	CButton m_objAddBtnPlayList;
	afx_msg void OnBnClickedClose();
	afx_msg void OnAddFile();
	listFile* l_tagFile;
	CCollectionTempt<listFile> l_tempFilePath;
    int i;

	char m_cFilePath[MAX_PATH][MAX_PATH];

    CString m_strFileName;

    afx_msg void OnRemoveFile();


    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg void OnBnClickedButtonadd();
};
