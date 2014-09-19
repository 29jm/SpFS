#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "Node.hpp"
#include "File.hpp"

namespace SpFS
{

class Directory : public Node
{
public:
	Directory(const std::string& dirname);
	~Directory();

	std::vector<Node*> getChilds() const;
	Node* getNode(const std::string& nodename) const;
	Directory* getDirectory(const std::string& dirname);
	File* getFile(const std::string& filename) const;

	Node* addNode(Node* n);
	void removeNode(const std::string& nodename);
	void renameNode(const std::string& n, const std::string& newname);

	// Serialization
	virtual void serialize(std::fstream& file) const;
	static Directory* fromFile(std::fstream& file);

	friend class Node;

private:
	std::vector<Node*> nodes;
	std::vector<Node*> removed;
};

}

