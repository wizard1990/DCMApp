
// DCMAppView.cpp : CDCMAppView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDCMAppView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDCMAppView ����/����

CDCMAppView::CDCMAppView()
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//COLORREF m_bgcolor;
	//m_bgcolor = RGB(255,0,0);
	//cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,(HBRUSH)::GetStockObject(m_bgcolor),0); //����Ĭ��Ϊ��ɫ��ˢ WHITE_BRUSH ,�����޸�Ϊm_bgcolor
	return CView::PreCreateWindow(cs);
}

// CDCMAppView ����

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

//����
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


// CDCMAppView ��ӡ


void CDCMAppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDCMAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDCMAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDCMAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CDCMAppView ���

#ifdef _DEBUG
void CDCMAppView::AssertValid() const
{
	CView::AssertValid();
}

void CDCMAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDCMAppDoc* CDCMAppView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDCMAppDoc)));
	return (CDCMAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CDCMAppView ��Ϣ�������
