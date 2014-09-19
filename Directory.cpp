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

	for (Node* n : removed)
	{
		delete n;
	}
}

Node* Directory::addNode(Node* n)
{
	if (getNode(n->name))
	{
		// TODO: throw exception
		return nullptr;
	}

	if (n)
	{
		n->parent = this;
		nodes.push_back(n);

		return n;
	}
	else
	{
		return nullptr;
	}
}

void Directory::removeNode(const std::string& nodename)
{
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->name == nodename)
		{
			removed.push_back(nodes[i]);
			nodes.erase(nodes.begin()+i);
		}
	}
}

void Directory::renameNode(const std::string& n, const std::string& newname)
{
	Node* node = getNode(n);
	if (node)
	{
		node->name = newname;
	}
}

std::vector<Node*> Directory::getChilds() const
{
	return nodes;
}

uint32_t Directory::getSize() const
{
	return nodes.size();
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

Directory* Directory::getDirectory(const std::string& dirname)
{
	if (dirname == ".")
	{
		return this;
	}

	if (dirname == "..")
	{
		return dynamic_cast<Directory*>(parent);
	}

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


void Directory::serialize(std::fstream& file) const
{
	const char* id = "DIR";
	file.write(id, 3);

	uint32_t name_size = name.size();
	file.write(reinterpret_cast<char*>(&name_size), sizeof(name_size));

	file.write(name.c_str(), name_size);
	
	uint64_t num_nodes = nodes.size();
	file.write(reinterpret_cast<char*>(&num_nodes), sizeof(num_nodes));

	for (const Node* n : nodes)
	{
		n->serialize(file);
	}
}

Directory* Directory::fromFile(std::fstream& file)
{
	uint32_t name_size = 0;
	file.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));

	std::string dirname;
	for (uint32_t i = 0; i < name_size; i++)
	{
		char c;
		file.read(&c, sizeof(c));
		dirname += c;
	}

	Directory* dir = new Directory(dirname);
	dir->name = dirname;

	uint64_t num_elements;
	file.read(reinterpret_cast<char*>(&num_elements), sizeof(num_elements));

	for (uint64_t i = 0; i < num_elements; i++)
	{
		std::string type;
		for (int i = 0; i < 3; i++)
		{
			char c;
			file.read(&c, sizeof(c));
			type += c;
		}

		if (type == "DIR")
		{
			Directory* subdir = fromFile(file);
			if (!subdir)
			{
				std::cout << "loading of dir failed\n";
				return nullptr;
			}

			dir->addNode(subdir);
		}
		else if (type == "FIL")
		{
			File* subfile = File::fromFile(file);
			if (!subfile)
			{
				std::cout << "loading of file failed\n";
				return nullptr;
			}

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

