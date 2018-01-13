#pragma once

#include "resource.h"
#include <Commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include <string>
#include <vector>
#include "File.h"
#include "Chart.h"
#include <ctime>


using namespace std;

vector<wstring> defaultType = {
	L"Ăn uống",
	L"Di chuyển",
	L"Nhà cửa",
	L"Xe cộ",
	L"Nhu yếu phẩm",
	L"Dịch vụ"
};

File file("data.txt");
Chart chart(965, 250, 180);
LVCOLUMN lvCol;
LVITEM lv;
HWND g_ListView;
HWND g_comboType, g_editContent, g_editMoney, g_btnAdd, g_TotalMoney, g_editBenefice, g_btnCheckSaving, g_SavingMoney;
HWND st_groupbox;
HMENU h_PopUp;
Category category;
vector<Category> arrCategory;
vector<Type> arrType;
HDC hdc;
unsigned long total_money;
int sttRow = -1;
int indexFull;

WCHAR* buffer;
int size;

wstring typeExpense;
wstring contentExpense;
unsigned long moneyExpense;
wstring timeExpense;
unsigned long incomeMoney = 0;

void initArrType(vector<wstring> defaultType);
BOOL onCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void onCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void onPaint(HWND hwnd);
void onDestroy(HWND hwnd);
LRESULT onListviewNotify(HWND hWnd, int idFrom, NMHDR* pnm);

void initType();
bool checkInfo(HWND hwnd);
unsigned long setTotalMoney(HWND hwnd);
void displayListView(Category category, int index);
void deleteItem(HWND hwnd);
wstring getStringMoney(unsigned long money);
bool checkInfoIncome(HWND hwnd);
void drawChartRec(HDC &hdc);