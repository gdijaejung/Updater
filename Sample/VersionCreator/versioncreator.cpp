
#include "stdafx.h"
#include "packageversion.h"


using namespace std;

void main(char argc, char *argv[])
{
	cout << "version creator" << endl;
 
 	if (argc < 4)
 	{
 		cout << "commandline <old version filename> <updatefile filename> <new version filename>" << endl;
 		return;
 	}

	const string oldVerFileName = argv[1];
	const string updateFileName = argv[2];
	const string newVerFileName = argv[3];

	cPackageVersion pkgVer;
	pkgVer.Read(oldVerFileName);
	pkgVer.Update(updateFileName);
}
