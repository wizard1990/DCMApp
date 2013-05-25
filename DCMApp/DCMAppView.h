
// DCMAppView.h : CDCMAppView 类的接口
//

#pragma once

class CDCMAppView : public CView
{
protected: // 仅从序列化创建
	CDCMAppView();
	DECLARE_DYNCREATE(CDCMAppView)

// 特性
public:
	CDCMAppDoc* GetDocument() const;
	CStatic *DWILabel;
	CStatic *PWILabel;
	CStatic *mismatchLabel;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//virtual BOOL OnEraseBkgnd(CDC *pDC);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDCMAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DCMAppView.cpp 中的调试版本
inline CDCMAppDoc* CDCMAppView::GetDocument() const
   { return reinterpret_cast<CDCMAppDoc*>(m_pDocument); }
#endif

