#include <iostream>
#include "FtpClient/FTPClient.h"
#include <sstream>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

void main()
{
	nsFTP::CFTPClient ftpClient;
	nsFTP::CLogonInfo logonInfo(L"jjuiddong.co.kr", 21, L"jjuiddong",L"ddong800");

	// connect to server
	if (!ftpClient.Login(logonInfo))
	{
		cout << "login error" << endl;
		return;
	}

	// get directory listing
	nsFTP::TFTPFileStatusShPtrVec list;
	ftpClient.List(_T("/"), list);

	// iterate listing
	for (nsFTP::TFTPFileStatusShPtrVec::iterator it = list.begin();
		it != list.end(); ++it)
		printf("\n%s", (*it)->Name().c_str());

	// do file operations
	//ftpClient.DownloadFile(_T("/www/gdi/Test.txt"), _T("test2.txt"));
	ftpClient.MakeDirectory(L"www/gdi/test");
	ftpClient.UploadFile(_T("Test.txt"), _T("/www/gdi/Test.txt"));

// 	for (int i = 0; i < 100; ++i)
// 	{
// 		wstringstream ss;
// 		ss << "/www/gdi/Test";
// 		ss << i;
// 		ss << ".txt";		
// 		ftpClient.UploadFile(_T("Test.txt"), ss.str());
// 		cout << ".";
// 	}

	//ftpClient.Rename(_T("/upload/test.txt"), _T("/upload/NewName.txt"));
	//ftpClient.Delete(_T("/upload/NewName.txt"));

	// disconnect
	ftpClient.Logout();
}
