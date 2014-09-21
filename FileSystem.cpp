#include "FileSystem.hpp"

namespace SpFS
{

FileSystem::FileSystem()
	: root(nullptr), valid_state(false)
{

}

FileSystem::~FileSystem()
{
	if (valid_state)
	{
		flush();
		delete root;
	}
}

bool FileSystem::load(const std::string& fs_name)
{
	if (valid_state)
	{
		// Reloading would cause memory leak
		return false;
	}

	file.open(fs_name, std::ios::in|std::ios::out|std::ios::binary);
	if (!file)
	{
		std::cout << "failed to open file\n";
		return false;
	}

	filename = fs_name;

	std::string type;
	for (int i = 0; i < 3; i++)
	{
		char c;
		file.read(&c, sizeof(c));
		type += c;
	}
	if (type != "DIR")
	{
		std::cout << "type of root isn't DIR\n";
		return false;
	}

	root = Directory::fromFile(file);
	if (root == nullptr)
	{
		return false;
	}

	valid_state = true;

	return true;
}

bool FileSystem::create(const std::string& fs_name)
{
	if (root)
	{
		return false;
	}

	file.open(fs_name,
		std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc);
	if (!file)
	{
		std::cout << "failed to open file" << std::endl;
		return false;
	}

	filename = fs_name;

	root = new Directory("/");

	return true;
}

void FileSystem::flush()
{
	if (!root)
	{
		return;
	}

	file.close();
	file.clear();
	file.open(filename, std::ios::out|std::ios::binary|std::ios::trunc);
	root->serialize(file);
	file.flush();
}

Directory* FileSystem::getRoot() const
{
	return root;
}

Directory* FileSystem::getDirectory(const std::string& path)
{
	return getDirectory(path, root);
}

Directory* FileSystem::getDirectory(const std::string& path, Directory* base)
{
	return dynamic_cast<Directory*>(getNode(path, base));
}

File* FileSystem::getFile(const std::string& path)
{
	return getFile(path, root);
}

File* FileSystem::getFile(const std::string& path, Directory* base)
{
	return dynamic_cast<File*>(getNode(path, base));
}

Node* FileSystem::getNode(const std::string& path)
{
	return getNode(path, root);
}

Node* FileSystem::getNode(const std::string& path, Directory* base)
{
	return base->getNode(path);
}

}

