#include <SpFS/SpFS.hpp>
#include <iostream>

using namespace SpFS;

int main()
{
	FileSystem sys;
	sys.create("partition.sys");
	Directory* root = sys.getRoot();

	Directory* home = new Directory("home");
	Directory* poney = new Directory("poney");

	File* bashrc = new File(".bashrc");
	bashrc->append("[ -f .bash_aliases ] && . .bash_aliases");

	root->addNode(home);
	home->addNode(poney);
	poney->addNode(bashrc);

	sys.flush();
}
