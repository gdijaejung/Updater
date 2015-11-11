
#include "stdafx.h"
#include "fileversion.h"
#include <winver.h>

#pragma comment(lib, "Version.lib")


using namespace filever;


// 파일의 내용이 바꼈다면 true를 리턴한다.
// 비교 내용
//	- 수정날짜
//	- 파일크기
bool filever::CompareFile(const string &fileName1, const string &fileName2)
{
	using namespace std;
	//cout << "comparefile " << fileName1.c_str() << " : " << fileName2.c_str() << endl;

	HANDLE hFile1 = CreateFileA(fileName1.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (!hFile1)
		return false;

	HANDLE hFile2 = CreateFileA(fileName2.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (!hFile2)
		return false;

	DWORD fileSizeH1;
	DWORD fileSizeL1 = GetFileSize(hFile1, &fileSizeH1);
	DWORD fileSizeH2;
	DWORD fileSizeL2 = GetFileSize(hFile2, &fileSizeH2);

	FILETIME crTime1, accessTime1, writeTime1;
	FILETIME crTime2, accessTime2, writeTime2;
	GetFileTime(hFile1, &crTime1, &accessTime1, &writeTime1);
	GetFileTime(hFile2, &crTime2, &accessTime2, &writeTime2);
	
	bool retVal = false;

	if (fileSizeL1 != fileSizeL2)
		retVal = true;

	if ((writeTime1.dwLowDateTime != writeTime2.dwLowDateTime) ||
		(writeTime1.dwHighDateTime != writeTime2.dwHighDateTime))
		retVal = true;

 	CloseHandle(hFile1);
	CloseHandle(hFile2);

	return retVal;
}
