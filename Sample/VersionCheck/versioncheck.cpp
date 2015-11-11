
#include "stdafx.h"
#include "fileversion.h"


using namespace std;

// 	for (int i = 0; i < 100; ++i)
// 	{
// 		stringstream ss;
// 		ss << "E:/FileVersion/New/test";
// 		ss << i;
// 		ss << ".txt";
// 
// 		ofstream ofs(ss.str());
// 		if (ofs.is_open())
// 		{
// 			ofs << "test" << i << endl;
// 		}
// 	}

void main(char argc, char *argv[])
{
	if (argc < 3)
	{
		cout << "command line <new file directory path> <old file directory path>";
		return;
	}

	const string path1 = argv[1];
	const string path2 = argv[2];

	cout << "version check" << endl;
	cout << "path1 = " << path1.c_str() << endl;
	cout << "path2 = " << path2.c_str() << endl;

	list<string> files1;
	common::CollectFiles(list<string>(), path1, files1);
//	cout << "listing path1" << endl;
// 	for each (auto str in files1)
// 		cout << str.c_str() << endl;

	list<string> files2;
	common::CollectFiles(list<string>(), path2, files2);
//	cout << "listing path2" << endl;
// 	for each (auto str in files2)
// 		cout << str.c_str() << endl;

	list<string> relateFiles;
	for each (auto str in files2)
	{
		string tmpPath = path2;
		tmpPath[path2.size() - 1] = NULL;
		const string fileName = common::RelativePathTo(tmpPath, str);
		relateFiles.push_back(fileName);
	}

	
	// 업데이트 시킬 파일 목록
	ofstream ofs("updatefiles.txt");

	cout << endl << "compare file list" << endl;
	for each (auto str in files1)
	{
		string tmpPath = path1;
		tmpPath[path1.size() - 1] = NULL;
		const string fileName1 = common::RelativePathTo(tmpPath, str);
		auto it = find(relateFiles.begin(), relateFiles.end(), fileName1);
		if (it == relateFiles.end())
		{
			// 없는 파일은 업데이트 시킨다.
			ofs << str << endl;
		}
		else
		{
			if (filever::CompareFile(str, path2 + fileName1))
			{
				// 다른 버젼의 파일일 때, 이름출력
				//cout << "different file" << endl;
				ofs << str << endl;
			}
		}
	}
}
