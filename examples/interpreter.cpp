#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <SpFS/SpFS.hpp>

using namespace std;
using namespace SpFS;

bool moveFromDisk(const string& source, Directory* dest);
bool moveFromPartition(File* source, const string& dest);
void list_directory(Directory* dir);
void remove(File* file);

vector<string>& split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);

int main()
{
	FileSystem sys;
	int choice = 0;
	string fs_name;

	cout << "1. Load filesystem\n";
	cout << "2. Create filesystem\n";
	cout << "Choice: ";
	cin >> choice;

	cout << "Name of the filesystem: ";
	cin >> fs_name;

	if (choice == 1) {
		if (sys.load(fs_name)) {
			cout << "Filesystem loaded successfully\n";
		}
		else {
			cout << "Failed to load filesystem\n";
			return 1;
		}
	}
	else if (choice == 2) {
		if (sys.create(fs_name)) {
			cout << "Filesystem created successfully\n";
		}
		else {
			cout << "Failed to create filesystem\n";
			return 1;
		}
	}
	else {
		cout << "Try again\n";
	}

	cin.ignore();
	Directory* actual_dir = sys.getRoot();

	bool running = true;
	while (running) {
		string command;

		cout << "SpFS::" << actual_dir->getName() << "$ ";
		getline(cin, command);

		if (command.empty()) {
			continue;
		}

		vector<string> tokens(split(command, ' '));
		if (tokens[0] == "moveFromDisk") {
			if (tokens.size() < 3) {
				continue;
			}

			if (!moveFromDisk(tokens[1], actual_dir->getDirectory(tokens[2]))) {
				cout << "Failed to copy " << tokens[1] << " to " << tokens[2] << endl;
			}
		}

		if (tokens[0] == "moveFromPartition") {
			if (tokens.size() < 3) {
				continue;
			}

			if (!moveFromPartition(actual_dir->getFile(tokens[1]), tokens[2])) {
				cout << "Failed to copy " << tokens[1] << " to " << tokens[2] << endl;
			}
		}

		if (tokens[0] == "ls") {
			list_directory(actual_dir);
		}

		if (tokens[0] == "rm") {
			if (tokens.size() < 2) {
				continue;
			}

			remove(actual_dir->getFile(tokens[1]));
		}

		if (tokens[0] == "exit") {
			running = false;
		}
	}

	sys.flush();
}

bool moveFromDisk(const string& source, Directory* dest)
{
	if (!dest) {
		return false;
	}

	ifstream input_file(source, ios::binary);
	if (!input_file) {
		return false;
	}

	cout << "Copying " << source << " to SpFS::" << dest->getPath() << endl;

	File* new_file = new File(source);

	// Get the file's size
	streampos file_size;
	input_file.seekg(0, ios::end);
	file_size = input_file.tellg();
	input_file.seekg(0, ios::beg);

	vector<char> file_data(file_size);
	input_file.read(&file_data[0], file_size);

	new_file->setData(file_data);
	dest->addNode(new_file);

	return true;
}

bool moveFromPartition(File* source, const string& dest)
{
	if (!source) {
		return false;
	}

	ofstream file(dest, ios::binary);
	if (!file) {
		return false;
	}

	cout << "Copying SpFS::" << source->getPath() << " to " << dest << endl;

	vector<char> data(source->getData());
	file.write(&data[0], data.size());

	return true;
}

void list_directory(Directory* dir)
{
	if (!dir) {
		return;
	}

	cout << dir->getSize() << " elements\n";
	for (Node* n : dir->getChilds()) {
		cout << n->getName() << endl;
	}
}

void remove(File* file)
{
	if (!file) {
		return;
	}

	Directory* parent = file->getParent();
	parent->removeNode(file->getName());
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}

	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
