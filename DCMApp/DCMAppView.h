
// DCMAppView.h : CDCMAppView ��Ľӿ�
//

#pragma once

class CDCMAppView : public CView
{
protected: // �������л�����
	CDCMAppView();
	DECLARE_DYNCREATE(CDCMAppView)

// ����
public:
	CDCMAppDoc* GetDocument() const;
	CStatic *DWILabel;
	CStatic *PWILabel;
	CStatic *mismatchLabel;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//virtual BOOL OnEraseBkgnd(CDC *pDC);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDCMAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DCMAppView.cpp �еĵ��԰汾
inline CDCMAppDoc* CDCMAppView::GetDocument() const
   { return reinterpret_cast<CDCMAppDoc*>(m_pDocument); }
#endif

