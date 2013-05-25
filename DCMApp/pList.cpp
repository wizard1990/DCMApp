// pList.h : CpList 类的实现



// CpList 实现

// 代码生成在 2013年5月10日, 16:15

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

// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[pid]"), m_pid);
	RFX_Text(pFX, _T("[pname]"), m_pname);
	RFX_Text(pFX, _T("[pdir]"), m_pdir);

}
/////////////////////////////////////////////////////////////////////////////
// CpList 诊断

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


