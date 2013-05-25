
#include "StdAfx.h"
#include "ADOConn.h"
#include "pList.h"
#include "DCMConst.h"

ADOConn::ADOConn(void)
{
	/*try{
		m_db.Open(m_rs->GetDefaultConnect(), CDatabase::noOdbcDialog);
	}
	catch (CDBException* ex){
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	catch (CMemoryException *ex){
		ex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	catch (CException *e){
		TCHAR szError[100];
		e->GetErrorMessage(szError,100);
		AfxMessageBox(szError);
	}*/
	m_rs = new CpList(&m_db);
}

ADOConn::~ADOConn(void)
{
	m_rs->Close();//¹Ø±Õ¼ÇÂ¼
	delete m_rs;
	m_db.Close();
}

shared_ptr<ADOConn> ADOConn::sharedSingleton()
{
	static shared_ptr<ADOConn> ptr;
	if (ptr.get() == NULL){
		ptr = shared_ptr<ADOConn>(new ADOConn);
	}
	return ptr;
}

CString ADOConn::searchDirByPId(const string& pId) const
{
	const char *ch = pId.c_str();
	m_rs->m_strFilter.Format(_T("pid = '%s'"),CStringW(ch));
	try{
		if (m_rs->IsOpen()){
			m_rs->Requery();
		}
		else{
			m_rs->Open();
		}
	}
	catch (CDBException *e)
	{
		AfxMessageBox(e->m_strError);
	}
	return m_rs->m_pdir;
}

void ADOConn::addPatient(const string& pId, const string& pName, const string& pDir)
{
	m_rs->AddNew();
	m_rs->m_pid.Format(_T("%s"),pId.c_str());
	m_rs->m_pname.Format(_T("%s"),pName.c_str());
	m_rs->m_pdir.Format(_T("%s"),pDir.c_str());
	m_rs->Update();
}

void ADOConn::refreshData()
{
	const char* p = testDir;
	CString path = CString(p);
	CString filenames[1024];
	int count = 0;
	findAllFile(path, filenames, count);
	//todo::add to database according to pid
}

void ADOConn::findAllFile(CString path, CString* filenames, int& count)
{
	CFileFind finder;
	BOOL working = finder.FindFile(path + "\\*.*");
	while (working) {
		working = finder.FindNextFile();
		if (finder.IsDots())
			continue;
		if (finder.IsDirectory()) {
			//FindAllFile(finder.GetFilePath(), filenames, count);
		}
		else {
			CString filename = finder.GetFileName();
			filenames[count++] = filename;
		}
	}
}