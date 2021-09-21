
// MFCMemoProDlg.h: 헤더 파일
//

#pragma once


// CMFCMemoProDlg 대화 상자
class CMFCMemoProDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCMemoProDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMEMOPRO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMnuMenuOpen();
	afx_msg void OnMnuMenuSave();
	afx_msg void OnMnuMenuSaveas();
	afx_msg void OnMnuMenuExit();
	afx_msg void OnMnuViewUpper();
	afx_msg void OnMnuViewLower();
	afx_msg void OnMnuViewHexa();
	afx_msg void OnMnuViewReturn();
	CEdit CMemo1;
	afx_msg void OnMnuInfoProginfo();
//	afx_msg void OnBnClickedcbupper();
//	afx_msg void OnBnClickedcblower();
//	afx_msg void OnBnClickedcbhexa();
	afx_msg void OnBnClickedbtnreturn();
	afx_msg void OnBnClickedcbupper();
	afx_msg void OnBnClickedcblower();
	afx_msg void OnBnClickedcbhexa();
};
