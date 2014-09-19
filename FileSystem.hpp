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

private:
	std::fstream file;
	std::string filename;
	Directory* root;
	bool valid_state;
};

}

