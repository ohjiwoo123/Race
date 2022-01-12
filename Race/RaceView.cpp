
// RaceView.cpp: CRaceView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Race.h"
#endif

#include "RaceDoc.h"
#include "RaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRaceView

IMPLEMENT_DYNCREATE(CRaceView, CView)

BEGIN_MESSAGE_MAP(CRaceView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CRaceView 생성/소멸
CRITICAL_SECTION cs;
HANDLE hMutex;

CRaceView::CRaceView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	CreateMutex(NULL, FALSE, NULL);	// 핸들이 나온다. 인자 3은 남의집과 동기화 

}

CRaceView::~CRaceView()
{
	DeleteCriticalSection(&cs);
	CloseHandle(hMutex);
}

BOOL CRaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CRaceView 그리기

void CRaceView::OnDraw(CDC* /*pDC*/)
{
	CRaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CRaceView 인쇄

BOOL CRaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CRaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CRaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CRaceView 진단

#ifdef _DEBUG
void CRaceView::AssertValid() const
{
	CView::AssertValid();
}

void CRaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRaceDoc* CRaceView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRaceDoc)));
	return (CRaceDoc*)m_pDocument;
}
#endif //_DEBUG


// CRaceView 메시지 처리기
int X;
BOOL Wait = FALSE;

DWORD WINAPI ThreadDog(LPVOID p)
{
	CRaceView* pView = (CRaceView*) p;
	CDC *pDC = pView->GetDC();

	for (int i = 0; i < 100; i++)
	{
		//while (Wait == TRUE) { ; }
		//Wait = TRUE;
		//EnterCriticalSection(&cs);
		WaitForSingleObject(hMutex, INFINITE);
		
		//---------------------------------

		X = 100;
		Sleep(1);
		pDC->TextOut(X, 100, _T("강아지"));

		ReleaseMutex(hMutex);
		//LeaveCriticalSection(&cs);
		//Wait=FALSE;
	}
	pView->ReleaseDC(pDC);
	AfxMessageBox(_T("강아지 종료"));

	return 0;
}

DWORD WINAPI ThreadCat(LPVOID p)
{
	CRaceView* pView = (CRaceView*)p;
	CDC* pDC = pView->GetDC();
	for (int i = 0; i < 100; i++)
	{
		//while (Wait == TRUE) { ; }
		//Wait = TRUE;
		//EnterCriticalSection(&cs);
		WaitForSingleObject(hMutex, INFINITE);

		//-------------------------------------

		X = 200;
		Sleep(1);
		pDC->TextOut(X, 200, _T("고양이"));

		ReleaseMutex(hMutex);
		//LeaveCriticalSection(&cs);
		//Wait=FALSE;
	}
	pView->ReleaseDC(pDC);
	AfxMessageBox(_T("고양이 종료"));
	return 0;
}

void CRaceView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	DWORD ThreadID;
	HANDLE hDog = CreateThread(NULL, 0, ThreadDog, this, 0, &ThreadID);
	HANDLE hCat = CreateThread(NULL, 0, ThreadCat, this, 0, &ThreadID);

	// 강아지와 고양이를 기다려 
	HANDLE h[2] = { hDog,hCat };
	WaitForMultipleObjects(2,h, TRUE,INFINITE); // (인자갯수, 핸들, TRUE=전부기다려, INFINITE=될때까지기다려)
	
	AfxMessageBox(_T("강아지와 고양이가 모두 끝났습니다."));
	
	CloseHandle(hDog);
	CloseHandle(hCat);

	CView::OnLButtonDown(nFlags, point);
}
