
// MFCMemoProDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCMemoPro.h"
#include "MFCMemoProDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCMemoProDlg 대화 상자



CMFCMemoProDlg::CMFCMemoProDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMEMOPRO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMemoProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, CMemo1);
}

BEGIN_MESSAGE_MAP(CMFCMemoProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MNU_MENU_OPEN, &CMFCMemoProDlg::OnMnuMenuOpen)
	ON_COMMAND(ID_MNU_MENU_SAVE, &CMFCMemoProDlg::OnMnuMenuSave)
	ON_COMMAND(ID_MNU_MENU_SAVEAS, &CMFCMemoProDlg::OnMnuMenuSaveas)
	ON_COMMAND(ID_MNU_MENU_EXIT, &CMFCMemoProDlg::OnMnuMenuExit)
	ON_COMMAND(ID_MNU_VIEW_UPPER, &CMFCMemoProDlg::OnMnuViewUpper)
	ON_COMMAND(ID_MNU_VIEW_LOWER, &CMFCMemoProDlg::OnMnuViewLower)
	ON_COMMAND(ID_MNU_VIEW_HEXA, &CMFCMemoProDlg::OnMnuViewHexa)
	ON_COMMAND(ID_MNU_VIEW_RETURN, &CMFCMemoProDlg::OnMnuViewReturn)
	ON_COMMAND(ID_MNU_INFO_PROGINFO, &CMFCMemoProDlg::OnMnuInfoProginfo)
//	ON_BN_CLICKED(IDC_cbUpper, &CMFCMemoProDlg::OnBnClickedcbupper)
//	ON_BN_CLICKED(IDC_cbLower, &CMFCMemoProDlg::OnBnClickedcblower)
//	ON_BN_CLICKED(IDC_cbHexa, &CMFCMemoProDlg::OnBnClickedcbhexa)
	ON_BN_CLICKED(IDC_btnReturn, &CMFCMemoProDlg::OnBnClickedbtnreturn)
	ON_BN_CLICKED(IDC_cbUpper, &CMFCMemoProDlg::OnBnClickedcbupper)
	ON_BN_CLICKED(IDC_cbLower, &CMFCMemoProDlg::OnBnClickedcblower)
	ON_BN_CLICKED(IDC_cbHexa, &CMFCMemoProDlg::OnBnClickedcbhexa)
END_MESSAGE_MAP()


// CMFCMemoProDlg 메시지 처리기

BOOL CMFCMemoProDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
//  프레임워크가 이 작업을 자동으로 수행합니다.
SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

// TODO: 여기에 추가 초기화 작업을 추가합니다.

return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCMemoProDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCMemoProDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCMemoProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CMFCMemoProDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


CString strPath;
void CMFCMemoProDlg::OnMnuMenuOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OPENFILENAME ofn;
	char fName[512];
	HWND hWnd = m_hWnd;
	HANDLE hd;
	FILE* fp;

	ZeroMemory(&ofn, sizeof(ofn));						// 메모리 Clear => 0

}


void CMFCMemoProDlg::OnMnuMenuSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (strPath != "")
	{

	}
}


void CMFCMemoProDlg::OnMnuMenuSaveas()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMFCMemoProDlg::OnMnuMenuExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	EndDialog(0);
}


CString origin;												// 원본 텍스트 저장
void CMFCMemoProDlg::OnMnuViewUpper()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString cstr;
	CWnd* pWnd = AfxGetMainWnd();							// EditControl ReadOnly 설정
	HWND hWnd = pWnd->m_hWnd;								// 메인 다이얼로그에 핸들값 받아옴
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDIT1);			// 에디트 컨트롤의 핸들값 받아옴(API 사용하기 때문)

	if (origin.IsEmpty())									// 원본 문자열 비어있다면 실행 // 소문자나 대문자가 중복실행되어 원본 문자열 잃어버리는 것 방지
	{
		CMemo1.GetWindowText(origin);
		cstr = origin;
		CMemo1.SetWindowText(cstr.MakeUpper());
		SendMessageW(hEdit, EM_SETREADONLY, true, 0);		// SendMessageW 통해 속성 변경
															// 에디트 컨트롤의 핸들과 명령어 사용
															// false: ReadOnly 해제, true: ReadOnly 설정
	}
}


void CMFCMemoProDlg::OnMnuViewLower()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString cstr;
	CWnd* pWnd = AfxGetMainWnd();							// EditControl ReadOnly 설정
	HWND hWnd = pWnd->m_hWnd;								// 메인 다이얼로그에 핸들값 받아옴
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDIT1);			// 에디트 컨트롤의 핸들값 받아옴(API 사용하기 때문)

	if (origin.IsEmpty())
	{
		CMemo1.GetWindowText(origin);
		cstr = origin;
		CMemo1.SetWindowText(cstr.MakeLower());
		SendMessageW(hEdit, EM_SETREADONLY, true, 0);		// SendMessageW 통해 속성 변경
															// 에디트 컨트롤의 핸들과 명령어 사용
															// false: ReadOnly 해제, true: ReadOnly 설정
	}
}


void CMFCMemoProDlg::OnMnuViewHexa()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString cstr;
	CWnd* pWnd = AfxGetMainWnd();							// EditControl ReadOnly 설정
	HWND hWnd = pWnd->m_hWnd;								// 메인 다이얼로그에 핸들값 받아옴
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDIT1);			// 에디트 컨트롤의 핸들값 받아옴(API 사용하기 때문)

	if (origin.IsEmpty())
	{
		CMemo1.GetWindowText(origin);
		char ch[512];
		for (int i = 0; i < origin.GetLength(); i++)
		{
			CString temp;
			int value = (int)origin[i];
			temp.Format("%02X ", value);
			if (i % 16 == 0) cstr += "\r\n";				// 16자 입력 후 줄바꿈
			cstr += temp;
		}
		CMemo1.SetWindowText(cstr);
		
		SendMessageW(hEdit, EM_SETREADONLY, true, 0);		// SendMessageW 통해 속성 변경
															// 에디트 컨트롤의 핸들과 명령어 사용
															// false: ReadOnly 해제, true: ReadOnly 설정
	}

}


void CMFCMemoProDlg::OnMnuViewReturn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CWnd* pWnd = AfxGetMainWnd();							// EditControl ReadOnly 설정
	HWND hWnd = pWnd->m_hWnd;								// 메인 다이얼로그에 핸들값 받아옴
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDIT1);			// 에디트 컨트롤의 핸들값 받아옴(API 사용하기 때문)

	SendMessageW(hEdit, EM_SETREADONLY, false, 0);			// SendMessageW 통해 속성 변경
															// 에디트 컨트롤의 핸들과 명령어 사용
															// false: ReadOnly 해제, true: ReadOnly 설정
	if (origin.IsEmpty() != true)							// 원본 문자열이 존재한다면
	{
		CMemo1.SetWindowText(origin);						// 출력하고
		origin.Empty();										// 버퍼삭제	// 존재하지 않는다면 if문 안 타서, 두 번 눌렀을 때 삭제되는 것 방지
	}
}


void CMFCMemoProDlg::OnMnuInfoProginfo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString cstr;
	CWnd* pWnd = AfxGetMainWnd();							// EditControl ReadOnly 설정
	HWND hWnd = pWnd->m_hWnd;								// 메인 다이얼로그에 핸들값 받아옴
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDIT1);			// 에디트 컨트롤의 핸들값 받아옴(API 사용하기 때문)

	if (origin.IsEmpty())
	{
		CMemo1.GetWindowText(origin);
		char ch[512];
		for (int i = 0; i < origin.GetLength(); i++)
		{
			CString temp;
			int value = (int)origin[i];
			temp.Format("%02X ", value);
			if (i % 16 == 0) cstr += "\r\n";
			cstr += temp;
		}
		CMemo1.SetWindowText(cstr);

		SendMessageW(hEdit, EM_SETREADONLY, true, 0);		// SendMessageW 통해 속성 변경
															// 에디트 컨트롤의 핸들과 명령어 사용
															// false: ReadOnly 해제, true: ReadOnly 설정
	}
}

void CMFCMemoProDlg::OnBnClickedcbupper()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstr;
	CWnd* pWnd = AfxGetMainWnd();							// EditControl ReadOnly 설정
	HWND hWnd = pWnd->m_hWnd;								// 메인 다이얼로그에 핸들값 받아옴
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDIT1);			// 에디트 컨트롤의 핸들값 받아옴(API 사용하기 때문)

	if (origin.IsEmpty())									// 원본 문자열 비어있다면 실행 // 소문자나 대문자가 중복실행되어 원본 문자열 잃어버리는 것 방지
	{
		CMemo1.GetWindowText(origin);
		cstr = origin;
		CMemo1.SetWindowText(cstr.MakeUpper());
		SendMessageW(hEdit, EM_SETREADONLY, true, 0);		// SendMessageW 통해 속성 변경
															// 에디트 컨트롤의 핸들과 명령어 사용
															// false: ReadOnly 해제, true: ReadOnly 설정
	}
}


void CMFCMemoProDlg::OnBnClickedcblower()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstr;
	CWnd* pWnd = AfxGetMainWnd();							// EditControl ReadOnly 설정
	HWND hWnd = pWnd->m_hWnd;								// 메인 다이얼로그에 핸들값 받아옴
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDIT1);			// 에디트 컨트롤의 핸들값 받아옴(API 사용하기 때문)

	if (origin.IsEmpty())
	{
		CMemo1.GetWindowText(origin);
		cstr = origin;
		CMemo1.SetWindowText(cstr.MakeLower());
		SendMessageW(hEdit, EM_SETREADONLY, true, 0);		// SendMessageW 통해 속성 변경
															// 에디트 컨트롤의 핸들과 명령어 사용
															// false: ReadOnly 해제, true: ReadOnly 설정
	}
}


void CMFCMemoProDlg::OnBnClickedcbhexa()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMFCMemoProDlg::OnBnClickedbtnreturn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CWnd* pWnd = AfxGetMainWnd();							// EditControl ReadOnly 설정
	HWND hWnd = pWnd->m_hWnd;								// 메인 다이얼로그에 핸들값 받아옴
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDIT1);			// 에디트 컨트롤의 핸들값 받아옴(API 사용하기 때문)

	SendMessageW(hEdit, EM_SETREADONLY, false, 0);			// SendMessageW 통해 속성 변경
															// 에디트 컨트롤의 핸들과 명령어 사용
															// false: ReadOnly 해제, true: ReadOnly 설정
	if (origin.IsEmpty() != true)							// 원본 문자열이 존재한다면
	{
		CMemo1.SetWindowText(origin);						// 출력하고
		origin.Empty();										// 버퍼삭제	// 존재하지 않는다면 if문 안 타서, 두 번 눌렀을 때 삭제되는 것 방지
	}
}