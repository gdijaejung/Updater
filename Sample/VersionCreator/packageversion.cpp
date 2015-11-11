
#include "stdafx.h"
#include "packageversion.h"


cPackageVersion::cPackageVersion()
{
	m_files.reserve(512);
}

cPackageVersion::~cPackageVersion()
{
}


// 버젼 파일을 읽는다.
bool cPackageVersion::Read(const string &fileName)
{
	using namespace std;
	ifstream ifs(fileName);
	if (!ifs.is_open())
		return false;

	string id;
	string eq;
	ifs >> id >> eq >> m_version;
	if (id != "version")
		return false;

	m_files.clear();

 	while (1)
 	{
		sFileInfo info;
		string semi;

		ifs >> info.fileName >> semi >> info.version;

		if (info.fileName.empty())
			break;

		m_files.push_back(info);
 	}

	return true;
}


// 버젼 파일을 저장한다.
bool cPackageVersion::Write(const string &fileName)
{
	using namespace std;

	ofstream ofs(fileName);
	if (ofs.is_open())
		return false;

	ofs << "version = " << m_version;

	for each (auto &info in m_files)
	{
		ofs << info.fileName << "\t;\t" << info.version << endl;
	}

	return true;
}


// 업데이트될 파일목록을 토대로, 버젼파일을 업데이트 한다.
void cPackageVersion::Update(const string &updateFileName)
{
	using namespace std;
	ifstream ifs(updateFileName);
	if (!ifs.is_open())
		return;

	while (1)
	{
		string fileName;
		ifs >> fileName;
		if (fileName.empty())
			break;

		//for each (auto &info in m_files)
		auto it = m_files.begin();
		while (it != m_files.end())
		{
			// 업데이트될 파일을 찾으면 Version 을 업데이트 한다.
			if (fileName == it->fileName)
			{
				++it->version;
				break;
			}
			++it;
		}
		// 리스트에 없다면, 추가될 파일이다.
		if (it == m_files.end())
		{
			sFileInfo info;
			info.fileName = fileName;
			info.version = 1;
			m_files.push_back(info);
		}
	}
}


// 예전 버젼과 비교한 후, 바뀐 파일을 다운로드 한다.
void cPackageVersion::DownloadFile(const cPackageVersion &oldVer)
{
	for each (auto info in m_files)
	{
		const int idx = oldVer.Find(info.fileName);
		if (idx >= 0)
		{
			// 업데이트 된 파일
			if (info.version > oldVer.m_files[idx].version)
			{
				// 다운로드

			}
		}
		else
		{
			// 추가 된 파일일 경우, 다운로드
		}
	}
}


// 파일이름으로 검색해서, 찾으면 index를 리턴한다.
int cPackageVersion::Find(const string &fileName) const
{
	for (u_int i = 0; i < m_files.size(); ++i)
	{
		if (m_files[i].fileName == fileName)
			return i;
	}
	return -1;
}


// 전 파일버젼과 비교해, 바뀐 파일을 업로드 한다.
void cPackageVersion::UploadFile(const cPackageVersion &oldVer)
{
	for each (auto info in m_files)
	{
		const int idx = oldVer.Find(info.fileName);
		if (idx >= 0)
		{
			// 업데이트 된 파일
			if (info.version > oldVer.m_files[idx].version)
			{
				// 업로드

			}
		}
		else
		{
			// 추가 된 파일일 경우, 업로드
		}		
	}
}
