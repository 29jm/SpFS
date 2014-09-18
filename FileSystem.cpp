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

bool FileSystem::load(const std::string& filename)
{
	if (valid_state)
	{
		// Reloading would cause memory leak
		return false;
	}

	file.open(filename, std::ios::in|std::ios::out|std::ios::binary);
	if (!file)
	{
		std::cout << "failed to open file\n";
		return false;
	}

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

bool FileSystem::create(const std::string& filename)
{
	if (root)
	{
		return false;
	}

	file.open(filename,
		std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc);
	if (!file)
	{
		std::cout << "failed to open file" << std::endl;
		return false;
	}

	root = new Directory("/");

	return true;
}

void FileSystem::flush()
{
	if (!root)
	{
		return;
	}

	root->serialize(file);
}

Directory* FileSystem::getRoot() const
{
	return root;
}

}

