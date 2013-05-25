
// DCMAppDoc.h : CDCMAppDoc ��Ľӿ�
//

#pragma once
#include<memory>
using namespace std;

class DCMPatientInfo;
class ADOConn;

class CDCMAppDoc : public CDocument
{
protected: // �������л�����
	CDCMAppDoc();
	DECLARE_DYNCREATE(CDCMAppDoc)

// ����
public:
	DCMPatientInfo *mInfo;
	double mPWIVol;
	double mDWIVol;
	shared_ptr<ADOConn> DBManager;
// ����
public:
	void calculateMismatch();
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CDCMAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
