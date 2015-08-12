#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "Node.hpp"
#include "File.hpp"

namespace SpFS
{

std::vector<std::string> split(const std::string& s, char delim);

class Directory : public Node
{
public:
	Directory(const std::string& dirname);
	~Directory();

	std::vector<Node*> getChilds() const;
	uint32_t getSize() const;

	Node* addNode(Node* n);
	void removeNode(const std::string& nodename);
	void renameNode(const std::string& n, const std::string& newname);

	Node* getNode(const std::string& nodename) const;
	File* getFile(const std::string& filename) const;
	// Can return the this pointer so not const-qualified
	Directory* getDirectory(const std::string& dirname);

	// Serialization
	virtual void serialize(std::fstream& file) const;
	static Directory* fromFile(std::fstream& file);

	friend class FileSystem;
	friend class Node;

private:
	std::vector<Node*> nodes;
	std::vector<Node*> removed;
};

}

