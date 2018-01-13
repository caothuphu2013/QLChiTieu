#include "stdafx.h"
#include "File.h"
#include <locale>
#include <codecvt>

File::File() {

}

File::~File() {

}

File::File(string _nameFile) {
	this->nameFile = _nameFile;
}

vector<Category> File::readFile() {
	vector<Category> arrCategory;
	vector<wstring> arrInfo;

	locale loc(locale(), new codecvt_utf8<wchar_t>);
	wifstream f(this->nameFile);
	f.imbue(loc);

	wstring wline = L"", c;
	if (f.is_open()) {
		while (!f.eof()) {
			getline(f, wline);
			if (wline.length() == 0)
				break;
			if ((int)wline[0] == 65279)
				wline.erase(wline.begin());
			wstring wtemp;

			for (auto c : wline) {
				if (c == ';')
				{
					arrInfo.push_back(wtemp);
					wtemp = L"";
				}
				else
					wtemp += c;
			}
			arrInfo.push_back(wtemp);
			wtemp = L"";

			if (arrInfo.size() == 4) {
				Category category(arrInfo[0], arrInfo[1], stol(arrInfo[2]), arrInfo[3]);
				arrCategory.push_back(category);
			}
			else if (arrInfo.size() == 3) {
				Category category(arrInfo[0], arrInfo[1], stol(arrInfo[2]), L"");
				arrCategory.push_back(category);
			}
			else {
				MessageBox(0, L"Nội dung tập tin không đủ dữ liệu hoặc sai định dạng", L"Thông báo", MB_OK | MB_ICONERROR);
			}
			arrInfo.clear();
		}
		f.close(); 
	}
	return arrCategory;
}

void File::saveFile(vector<Category> arrCategory) {
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	wofstream f(this->nameFile);
	f.imbue(loc);

	for (int i = 0; i < arrCategory.size(); i++) {
		wstring temp = arrCategory[i].getType() + L';' + arrCategory[i].getContent() + L';' + to_wstring(arrCategory[i].getMoney()) + L';'+ arrCategory[i].getTime();
		f << temp;
		if (i < arrCategory.size() - 1) 
			f << endl;
	}
	f.close();
}