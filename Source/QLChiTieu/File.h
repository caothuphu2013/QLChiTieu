#include <string>
#include <fstream>
#include <vector>
#include "Category.h"

using namespace std;
class File {
private:
	string nameFile;
public:
	File();
	~File();
	File(string nameFile);
	vector<Category> readFile();
	void saveFile(vector<Category> arrCategory);
};	