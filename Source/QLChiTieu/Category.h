#include <string>

using namespace std;

class Category {
private:
	wstring type;
	wstring content;
	unsigned long money;
	wstring time;
public:
	Category();
	~Category();
	Category(wstring _type, wstring _content, unsigned long _money, wstring _time);

	wstring getType();
	wstring getContent();
	unsigned long getMoney();
	wstring getTime();

	void setType(wstring _type);
	void setContent(wstring _content);
	void setMoney(unsigned long _money);
	void setTime(wstring _time);
};