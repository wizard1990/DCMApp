
// DCMAppDoc.cpp : CDCMAppDoc ���ʵ��
//
#pragma once
#include "stdafx.h"
#include "DCMPatientInfo.h"
#include "ADOConn.h"
#include "DCMConst.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DCMApp.h"
#endif

#include "DCMAppDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDCMAppDoc

IMPLEMENT_DYNCREATE(CDCMAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CDCMAppDoc, CDocument)
END_MESSAGE_MAP()


// CDCMAppDoc ����/����

CDCMAppDoc::CDCMAppDoc()
:mPWIVol(0),mDWIVol(0)
{
	DBManager = ADOConn::sharedSingleton();
	const char *pid = testPid;
	CString dir = DBManager->searchDirByPId(pid);
	DBManager->refreshData();
	//todo::use interface right when UI is finished

	int dwiCount = 25;
	DcmDataset** DWIDatasetList = (DcmDataset**)malloc(dwiCount*sizeof(DcmDataset*));
	for (int i = 0; i < dwiCount; i++) {
		DcmFileFormat *pDicomFile = new DcmFileFormat();
		char path[100];
		sprintf(path, "D:\\425534\\ADC\\ADC_%d.Dcm",i);
		OFCondition oc = pDicomFile->loadFile(path);
		if(oc.good()){
			DcmDataset *pDataset = pDicomFile->getDataset();
			DWIDatasetList[i] = pDataset;
		}
	}

	int pwiCount = 22;
	DcmDataset** PWIDatasetList = (DcmDataset**)malloc(pwiCount*sizeof(DcmDataset*));
	for (int i = 0; i < pwiCount; i++) {
		DcmFileFormat *pDicomFile = new DcmFileFormat();
		char path[100];
		sprintf(path, "D:\\425534\\TTP\\TTP_%d.Dcm",i);
		OFCondition oc = pDicomFile->loadFile(path);
		if(oc.good()){
			DcmDataset *pDataset = pDicomFile->getDataset();
			PWIDatasetList[i] = pDataset;
		}
	}

	mInfo = new DCMPatientInfo(DWIDatasetList, dwiCount, PWIDatasetList, pwiCount);
	calculateMismatch();
}

CDCMAppDoc::~CDCMAppDoc()
{
	delete mInfo;
}

BOOL CDCMAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDCMAppDoc ���л�

void CDCMAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CDCMAppDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CDCMAppDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CDCMAppDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDCMAppDoc ���

#ifdef _DEBUG
void CDCMAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDCMAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDCMAppDoc ����

void CDCMAppDoc::calculateMismatch()
{
	if(!(&mInfo)) return; 
	mPWIVol = mInfo->getPWIVolumn();
	mDWIVol = mInfo->getDWIVolumn();
}
