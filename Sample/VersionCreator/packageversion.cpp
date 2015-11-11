
#include "stdafx.h"
#include "packageversion.h"


cPackageVersion::cPackageVersion()
{
	m_files.reserve(512);
}

cPackageVersion::~cPackageVersion()
{
}


// ���� ������ �д´�.
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


// ���� ������ �����Ѵ�.
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


// ������Ʈ�� ���ϸ���� ����, ���������� ������Ʈ �Ѵ�.
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
			// ������Ʈ�� ������ ã���� Version �� ������Ʈ �Ѵ�.
			if (fileName == it->fileName)
			{
				++it->version;
				break;
			}
			++it;
		}
		// ����Ʈ�� ���ٸ�, �߰��� �����̴�.
		if (it == m_files.end())
		{
			sFileInfo info;
			info.fileName = fileName;
			info.version = 1;
			m_files.push_back(info);
		}
	}
}


// ���� ������ ���� ��, �ٲ� ������ �ٿ�ε� �Ѵ�.
void cPackageVersion::DownloadFile(const cPackageVersion &oldVer)
{
	for each (auto info in m_files)
	{
		const int idx = oldVer.Find(info.fileName);
		if (idx >= 0)
		{
			// ������Ʈ �� ����
			if (info.version > oldVer.m_files[idx].version)
			{
				// �ٿ�ε�

			}
		}
		else
		{
			// �߰� �� ������ ���, �ٿ�ε�
		}
	}
}


// �����̸����� �˻��ؼ�, ã���� index�� �����Ѵ�.
int cPackageVersion::Find(const string &fileName) const
{
	for (u_int i = 0; i < m_files.size(); ++i)
	{
		if (m_files[i].fileName == fileName)
			return i;
	}
	return -1;
}


// �� ���Ϲ����� ����, �ٲ� ������ ���ε� �Ѵ�.
void cPackageVersion::UploadFile(const cPackageVersion &oldVer)
{
	for each (auto info in m_files)
	{
		const int idx = oldVer.Find(info.fileName);
		if (idx >= 0)
		{
			// ������Ʈ �� ����
			if (info.version > oldVer.m_files[idx].version)
			{
				// ���ε�

			}
		}
		else
		{
			// �߰� �� ������ ���, ���ε�
		}		
	}
}
