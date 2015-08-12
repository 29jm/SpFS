#include "Node.hpp"

namespace SpFS
{

Node::~Node()
{
	
}

std::string Node::getPath() const
{
	if (!this->parent)
	{
		return name;
	}

	std::string path(name);
	const Node* node = this->parent;

	while (node->parent != nullptr)
	{
		path = node->name+"/"+path;
		node = node->parent;
	}

	path = "/"+path;

	return path;
}

std::string Node::getName() const
{
	return name;
}

Directory* Node::getParent() const
{
	return reinterpret_cast<Directory*>(parent);
}

Node::Type Node::getType() const
{
	return type;
}

}
