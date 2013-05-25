#pragma once
#include <afxdb.h>
#include <string>
#include <vector>
#include <memory>
using namespace std;
class CpList;

class ADOConn
{
public:
	ADOConn(void);
	~ADOConn(void);
	
	CString searchDirByPId(const string& pId) const;
	void addPatient(const string& pId, const string& pName, const string& pDir);
	void refreshData();

	static shared_ptr<ADOConn> sharedSingleton();
private:
	void findAllFile(CString path, CString* filenames, int& count);
	CDatabase m_db;
	CpList *m_rs;
};



