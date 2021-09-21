
// MFCApp1View.cpp: CMFCApp1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApp1.h"
#endif

#include "MFCApp1Doc.h"
#include "MFCApp1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApp1View

IMPLEMENT_DYNCREATE(CMFCApp1View, CEditView)

BEGIN_MESSAGE_MAP(CMFCApp1View, CEditView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApp1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ZOOMIN, &CMFCApp1View::OnZoomin)
	ON_COMMAND(ID_ZOOMOUT, &CMFCApp1View::OnZoomout)
END_MESSAGE_MAP()

// CMFCApp1View 생성/소멸

CMFCApp1View::CMFCApp1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApp1View::~CMFCApp1View()
{
}

BOOL CMFCApp1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 자동 래핑을 사용합니다.

	return bPreCreated;
}


// CMFCApp1View 인쇄


void CMFCApp1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApp1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 CEditView 준비
	return CEditView::OnPreparePrinting(pInfo);
}

void CMFCApp1View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 시작 인쇄
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMFCApp1View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 종료 인쇄
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CMFCApp1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApp1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApp1View 진단

#ifdef _DEBUG
void CMFCApp1View::AssertValid() const
{
	CEditView::AssertValid();
}

void CMFCApp1View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMFCApp1Doc* CMFCApp1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApp1Doc)));
	return (CMFCApp1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApp1View 메시지 처리기

// static은 Memory의 Heap 영역에 존재.
static int fSize = 20;	// 현재 폰트 사이즈
CFont tf;
void CMFCApp1View::OnZoomin()			// 1click 당 1회 
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// Client 영역의 문자 크기를 확대
	LOGFONT lf;						// 이용해 현재 폰트 크기 가져오기
	//ZeroMemory(&lf, sizeof(lf));
	//lf.lfHeight = fSize++;
	if (GetFont() == NULL)
	{																				// System font(보통 크기가 -) 가져오는 작업(GetFont 오류 시, GetStockObject 사용)
		CFont* pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));	// CFont는 사용할 수 있는 속성이 얼마 안 됨.(포인터연산으로 높이나 너비 가져올 수 없음)
		pFont->GetLogFont(&lf);
	}
	else GetFont()->GetLogFont(&lf);		// 현재 font의 값을 가져옴
	if (lf.lfHeight < 0) lf.lfHeight = abs(lf.lfHeight);		// abs(abstract): 절대값 반환	// -면 +로 바꿔라
	lf.lfHeight++;
											// new는 malloc -> 메모리 구조 상 Heap에 생성, Local영역인 stack에 생기면 함수 끝나며 메모리해소
	//CFont* cf = new CFont;					// Font는 Device, 메모리 공간 점유	// Heap에 계속 남아있어서 오류 가능성 증가
	//cf->CreateFontIndirect(&lf);			// Logfont로 세팅
	tf.DeleteObject();
	tf.CreateFontIndirect(&lf);
	SetFont(&tf);		// 적용. 특정 컴포넌트에 적용되는 것이 아니라, SDI에서 View class를 이용하는 이유 

}											// -> font 생성 시 new 사용 X, 규모 있기 때문에 누적되는 것 좋지 않음.
											// 폰트를 임시변수로 선언(tf) 후 이용, ZoomIn 계속 해도 세팅 값이 바뀌지 메모리는 변동 X.


void CMFCApp1View::OnZoomout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LOGFONT lf;						// 이용해 현재 폰트 크기 가져오기
	if (GetFont() == NULL)
	{																				// System font(보통 크기가 -) 가져오는 작업(GetFont 오류 시, GetStockObject 사용)
		CFont* pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));	// CFont는 사용할 수 있는 속성이 얼마 안 됨.(포인터연산으로 높이나 너비 가져올 수 없음)
		pFont->GetLogFont(&lf);
	}
	else GetFont()->GetLogFont(&lf);		// 현재 font의 값을 가져옴
	if (lf.lfHeight < 0) lf.lfHeight = abs(lf.lfHeight);		// abs(abstract)	// -면 +로 바꿔라
	lf.lfHeight--;

	tf.DeleteObject();
	tf.CreateFontIndirect(&lf);
	SetFont(&tf);
}


//BOOL CMFCApp1View::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	switch (pMsg->message)
//	{
//	case WM_KEYDOWN:		// 키보드 눌렀을 때
//		switch (pMsg->wParam)
//		{
//		case 107:
//		case 187:
//			//CMainFrame * p = (CMainFrame*)AfxGetMainWnd();
//			//CMFCApp1View *p1 = (CMFCApp1View*)p->GetActiveView();
//			// CMFCApp1View* p1 = (CMFCApp1View*)((CMainFrame*)AfxGetMainWnd())->GetActiveView(); 위 두 줄과 같음
//			OnZoomin(); return -1;		// 화면 출력 막기 위해 break가 아니라 return	// 0 아니면 됨
//		case 109:
//		case 189:
//			OnZoomout(); return -1;	// 화면 출력 막기 위해 break가 아니라 return
//		/*case VK_F1:
//		{
//			CAboutDlg dlg;
//			dlg.DoModal();
//			return 0;
//		}*/
//		default: break;
//		}
//	case WM_KEYUP:			// 키보드에서 손 뗐을 때
//		
//		break;
//	}
//	
//	return CEditView::PreTranslateMessage(pMsg);	// 부모 클래스의 가상함수 호출하는 것이 좋음.(Defualt)
//}
