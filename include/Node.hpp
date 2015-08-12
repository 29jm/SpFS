#pragma once

#include <string>

namespace SpFS
{

class fstream;
class File;
class Directory;

class Node
{
public:
	enum class Type {
		Directory, File
	};

	virtual ~Node();

	virtual void serialize(std::fstream& file) const = 0;

	virtual std::string getPath() const;
	virtual std::string getName() const;
	virtual Directory* getParent() const;
	virtual Type getType() const;

protected:
	Node* parent;
	std::string name;
	Type type;

	friend class File;
	friend class Directory;
};

}
