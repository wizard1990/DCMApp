// pList.h : CpList ���ʵ��



// CpList ʵ��

// ���������� 2013��5��10��, 16:15

#include "stdafx.h"
#include "pList.h"
IMPLEMENT_DYNAMIC(CpList, CRecordset)

CpList::CpList(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_pid = L"";
	m_pname = L"";
	m_pdir = L"";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CpList::GetDefaultConnect()
{
	return _T("DSN=pList;UID=sa;PWD=19900509;APP=Microsoft\x00ae Visual Studio\x00ae 2010;WSID=THINK-THINK;DATABASE=dicomdb");
}

CString CpList::GetDefaultSQL()
{
	return _T("[dbo].[pList]");
}

void CpList::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[pid]"), m_pid);
	RFX_Text(pFX, _T("[pname]"), m_pname);
	RFX_Text(pFX, _T("[pdir]"), m_pdir);

}
/////////////////////////////////////////////////////////////////////////////
// CpList ���

#ifdef _DEBUG
void CpList::AssertValid() const
{
	CRecordset::AssertValid();
}

void CpList::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


