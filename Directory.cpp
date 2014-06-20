#include "Directory.hpp"

namespace SpFS
{

Directory::Directory(const std::string& dirname)
{
	parent = nullptr;
	name = dirname;
	type = Type::Directory;
}

Directory::~Directory()
{
	for (Node* n : nodes)
	{
		delete n;
	}
}

void Directory::addNode(Node* n)
{
	n->parent = this;
	nodes.push_back(n);
}

std::vector<Node*> Directory::getChilds() const
{
	return nodes;
}

Node* Directory::getNode(const std::string& nodename) const
{
	for (Node* n : nodes)
	{
		if (n->name == nodename)
		{
			return n;
		}
	}

	return nullptr;
}

Directory* Directory::getDirectory(const std::string& dirname) const
{
	for (Node* n : nodes)
	{
		if (n->name == dirname && n->type == Type::Directory)
		{
			return dynamic_cast<Directory*>(n);
		}
	}

	return nullptr;
}

File* Directory::getFile(const std::string& filename) const
{
	for (Node* n : nodes)
	{
		if (n->name == filename && n->type == Type::File)
		{
			return dynamic_cast<File*>(n);
		}
	}

	return nullptr;
}


std::string Directory::serialize() const
{
	std::string text;

	text += " ";
	text += "DIRECTORY";
	text += " "+name+" ";
	text += std::to_string(nodes.size());

	for (const Node* n : nodes)
	{
		text += n->serialize();
	}

	return text;
}

Directory* Directory::fromStream(std::istream& stream)
{
	std::string dirname;
	stream >> dirname;

	Directory* dir = new Directory(dirname);

	uint64_t num_elements;
	stream >> num_elements;

	for (int i = 0; i < num_elements; i++)
	{
		std::string type;
		stream >> type;

		if (type == "DIRECTORY")
		{
			Directory* subdir = fromStream(stream);
			dir->addNode(subdir);
		}
		else if (type == "FILE")
		{
			File* subfile = File::fromStream(stream);
			dir->addNode(subfile);
		}
		else
		{
			return nullptr;
		}
	}

	return dir;
}

}
