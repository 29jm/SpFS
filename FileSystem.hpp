#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "SpFS.hpp"

namespace SpFS
{

class FileSystem
{
public:
	FileSystem();

	~FileSystem();

	bool load(const std::string& filename);
	bool create(const std::string& filename);
	void flush();

	Directory* getRoot() const;

	// Default parameter allows to search a subdirectory
	Directory* getDirectory(const std::string& path);
	Directory* getDirectory(const std::string& path, Directory* base);
	File* getFile(const std::string& path, Directory* base);
	File* getFile(const std::string& path);

private:
	Node* getNode(const std::string& path);
	Node* getNode(const std::string& path, Directory* base);

	std::fstream file;
	std::string filename;
	Directory* root;
	bool valid_state;
};

}

