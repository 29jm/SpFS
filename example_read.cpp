#include "SpFS.hpp"
#include <iostream>

using namespace std;
using namespace SpFS;

void showStructure(Directory* dir);

int main()
{
	FileSystem sys;
	sys.load("partition.sys");

	showStructure(sys.getRoot());
}

void showStructure(Directory* dir)
{
	for (Node* n : dir->getChilds())
	{
		cout << n->getPath() << endl;
	}

	for (Node* n : dir->getChilds())
	{		
		if (n->getType() == Node::Type::Directory)
		{
			Directory* subdir = dir->getDirectory(n->getName());
			showStructure(subdir);
		}
	}
}
