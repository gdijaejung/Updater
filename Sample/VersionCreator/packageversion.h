//
// Version 파일 포맷
//
// version = 1
// file1; version
// file2; version
//
// 업로드 과정
//	1. Read()
//	2. Update()
//  3. Write()
//	4. UploadFile()
//
//
//	다운로드 과정
//	1. Read()
//	2. DownLoadFile()
//
#pragma once


class cPackageVersion
{
public:
	cPackageVersion();
	virtual ~cPackageVersion();

	struct sFileInfo
	{
		int version;
		string fileName;
	};

	
	bool Read(const string &fileName);
	bool Write(const string &fileName);
	void Update(const string &updateFileName);
	void UploadFile(const cPackageVersion &oldVer);
	void DownloadFile(const cPackageVersion &oldVer);
	int Find(const string &fileName) const;


	int m_version;
	vector<sFileInfo> m_files;
};
