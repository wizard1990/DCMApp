
// DCMAppView.cpp : CDCMAppView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DCMApp.h"
#endif

#include "DCMAppDoc.h"
#include "DCMAppView.h"
#include "DCMDisplayUtil.h"
#include "DCMPatientInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDCMAppView

IMPLEMENT_DYNCREATE(CDCMAppView, CView)

BEGIN_MESSAGE_MAP(CDCMAppView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDCMAppView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDCMAppView 构造/析构

CDCMAppView::CDCMAppView()
{
	// TODO: 在此处添加构造代码
	PWILabel = DWILabel = mismatchLabel = NULL;
}

CDCMAppView::~CDCMAppView()
{
	if(PWILabel != NULL) delete PWILabel;
	if(DWILabel != NULL) delete DWILabel;
	if(mismatchLabel != NULL) delete mismatchLabel;
}

BOOL CDCMAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//COLORREF m_bgcolor;
	//m_bgcolor = RGB(255,0,0);
	//cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,(HBRUSH)::GetStockObject(m_bgcolor),0); //这里默认为白色画刷 WHITE_BRUSH ,现在修改为m_bgcolor
	return CView::PreCreateWindow(cs);
}

// CDCMAppView 绘制

void CDCMAppView::OnDraw(CDC* pDC)
{
	CDCMAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rectClient; 
	CBrush brushBkColor; 
	GetClientRect(rectClient);
	brushBkColor.CreateSolidBrush(RGB(0,0,0)); 
	pDC->DPtoLP(rectClient); 
	pDC->FillRect(rectClient,&brushBkColor); 

	for (int i = 0; i < 18; i++){
		ImageMatrix *imgMatrix = pDoc->mInfo->mDWIImageList[i];
		int posX = i % 5;
		int posY = i / 5;
		DCMDisplayUtil::displayMatrix(pDC, imgMatrix, posX * imgMatrix->getColumns(), posY * imgMatrix->getRows(), 1.0, true);
	}

	for (int i = 0; i < 18; i++){
		ImageMatrix *imgMatrix = pDoc->mInfo->mPWIImageList[i];
		int posX = i % 5;
		int posY = i / 5;
		DCMDisplayUtil::displayMatrix(pDC, imgMatrix, 700 + posX * imgMatrix->getColumns() / 2, posY * imgMatrix->getRows() / 2, 0.5, true);
	}

	double x = pDoc->mInfo->getDWIVolumn();
	double y = pDoc->mInfo->getPWIVolumn();
	
	DWILabel = new CStatic();
	CString s1;
	s1.Format(_T("DWI Volumn:%.2lf"),x);
	DWILabel->Create(s1, WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(200,520,300,570), this);

	PWILabel = new CStatic();
	CString s2;
	s2.Format(_T("PWI Volumn:%.2lf"),y);
	PWILabel->Create(s2, WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(1080,520,1180,570), this);

	mismatchLabel = new CStatic();
	CString s3;
	double mismatch = y / x;
	s3.Format(_T("Mismatch:%.2lf"),mismatch);
	mismatchLabel->Create(s3, WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(600,520,700,570), this);
	
	//printf("%lf",y/x);
	
}

//背景
/*BOOL CDCMAppView::OnEraseBkgnd(CDC *pDC)
{
 // TODO: Add your message handler code here and/or call default
    CBrush   brush(RGB(0,0,0));   
    CBrush*   pOldOne   =   pDC->SelectObject(&brush);   
    CRect   rc;   
    pDC->GetClipBox(&rc); 
    pDC->PatBlt(rc.left,   rc.top,   rc.Width(),   rc.Height(),   PATCOPY);   
    pDC->SelectObject(pOldOne);   
    return TRUE;   
}*/


// CDCMAppView 打印


void CDCMAppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDCMAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDCMAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDCMAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDCMAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDCMAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDCMAppView 诊断

#ifdef _DEBUG
void CDCMAppView::AssertValid() const
{
	CView::AssertValid();
}

void CDCMAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDCMAppDoc* CDCMAppView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDCMAppDoc)));
	return (CDCMAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CDCMAppView 消息处理程序
