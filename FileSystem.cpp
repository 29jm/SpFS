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

