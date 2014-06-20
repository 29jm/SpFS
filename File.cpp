#include "File.hpp"

namespace SpFS
{

File::File(const std::string& filename)
{
	parent = nullptr;
	name = filename;
	type = Type::File;
}

void File::append(const std::vector<char>& d)
{
	data.insert(data.end(), d.begin(), d.end());
}

void File::append(const std::string& s)
{
	for (const char c : s)
	{
		data.push_back(c);
	}
}

void File::append(const char& c)
{
	data.push_back(c);
}

std::vector<char> File::getData() const
{
	return data;
}

std::string File::getDataAsString() const
{
	return std::string(data.begin(), data.end());
}

std::string File::serialize() const
{
	std::string text;

	text += " ";
	text += "FILE";
	text += " "+name+" ";
	text += std::to_string(data.size());
	text += " ";
	
	for (const char c : data)
	{
		text += c;
	}

	return text;
}

File* File::fromStream(std::istream& stream)
{
	std::string filename;
	stream >> filename;

	File* file = new File(filename);

	uint64_t size;
	stream >> size;

	// May read leading space/line feed, skip last char
	stream.ignore();
	file->data.reserve(size);
	for (int i = 0; i < size; i++)
	{
		char c;
		stream.get(c);

		file->data.push_back(c);
	}

	return file;
}

}
