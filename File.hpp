#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

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
	virtual std::string serialize() const;
	static File* fromStream(std::istream& stream);

private:
	std::vector<char> data;
};

}
