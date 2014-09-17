#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Node.hpp"

namespace SpFS
{

class File : public Node
{
public:
	File(const std::string& filename);

	void append(const std::vector<char>& d);
	void append(const std::string& s);
	void append(const char& c);

	std::vector<char> getData() const;
	std::string getDataAsString() const;

	// Serialization
	virtual void serialize(std::fstream& file) const;
	static File* fromFile(std::fstream& file);

private:
	std::vector<char> data;
};

}
