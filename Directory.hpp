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
	Directory* getDirectory(const std::string& dirname) const;
	File* getFile(const std::string& filename) const;

	void addNode(Node* n);

	// Serialization
	virtual std::string serialize() const;
	static Directory* fromStream(std::istream& stream);

	friend class Node;

private:
	std::vector<Node*> nodes;
};

}