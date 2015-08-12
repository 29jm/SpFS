#include "File.hpp"

namespace SpFS
{

File::File(const std::string& filename)
{
	parent = nullptr;
	name = filename.substr(filename.find_last_of("\\/")+1);
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

void File::setData(const std::vector<char>& new_data)
{
	data.clear();
	data = new_data;
}

std::string File::getDataAsString() const
{
	return std::string(data.begin(), data.end());
}

void File::serialize(std::fstream& file) const
{
	const char* id = "FIL";
	file.write(id, 3);

	uint32_t name_size = name.size();
	file.write(reinterpret_cast<char*>(&name_size), sizeof(name_size));
	
	file.write(name.c_str(), name.size());

	uint64_t data_size = data.size();
	file.write(reinterpret_cast<char*>(&data_size), sizeof(data_size));
	
	for (const char c : data)
	{
		file.write(&c, sizeof(c));
	}
}

File* File::fromFile(std::fstream& file)
{
	uint32_t name_size = 0;
	file.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));

	std::string filename;
	for (uint32_t i = 0; i < name_size; i++)
	{
		char c;
		file.read(&c, sizeof(c));
		filename += c;
	}

	File* newfile = new File(filename);
	newfile->name = filename;

	uint64_t size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size));

	newfile->data.reserve(size);
	for (uint64_t i = 0; i < size; i++)
	{
		char c;
		file.read(&c, sizeof(c));
		newfile->data.push_back(c);
	}

	return newfile;
}

}
