#include "FileSystem.hpp"

namespace SpFS
{

FileSystem::FileSystem()
	: root(nullptr)
{

}

FileSystem::FileSystem(const std::string& filename)
	: root(nullptr)
{
	create(filename);
}

FileSystem::~FileSystem()
{
	if (root)
	{
		delete root;
	}

	if (file)
	{
		file.close();
	}
}

bool FileSystem::load(const std::string& filename)
{
	if (root)
	{
		return false;
	}

	if (file.is_open())
	{
		return false;
	}

	file.open(filename, std::ios::in | std::ios::out);
	if (!file)
	{
		return false;
	}

	std::string type;
	file >> type;
	if (type != "DIRECTORY")
	{
		return false;
	}

	root = Directory::fromStream(file);

	return true;
}

bool FileSystem::create(const std::string& filename)
{
	if (root)
	{
		return false;
	}

	file.open(filename, std::ios::out);
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

	file << root->serialize();
}

Directory* FileSystem::getRoot() const
{
	return root;
}

}
