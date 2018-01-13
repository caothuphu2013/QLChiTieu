#include <vector>
#include <string>
using namespace std;

struct Type {
	wstring type;
	int r = 0, b = 0, g = 0;
	unsigned long money;
	float startAngle;
	float angle;
};

class Chart {
private:
	int px;
	int py;
	int radius;
	vector<Type> arrType;
public:
	Chart();
	~Chart();
	Chart(int _px, int _py, int radius);
	void updateChart(vector<Type> _arrType, unsigned long totalmoney);
	void draw(HDC hdc, int indexFull);
	void showNote(HDC hdc, unsigned long totalMoney);
};
