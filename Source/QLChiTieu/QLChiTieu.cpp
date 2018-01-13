// QLChiTieu.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "QLChiTieu.h"
#include <windowsx.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_QLCHITIEU, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QLCHITIEU));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QLCHITIEU));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_3DFACE+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_QLCHITIEU);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, 3);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, onCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, onCommand);
		HANDLE_MSG(hWnd, WM_PAINT, onPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, onDestroy);
		HANDLE_MSG(hWnd, WM_NOTIFY, onListviewNotify);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL onCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
	HFONT hFont = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, VIETNAMESE_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
	initArrType(defaultType);

	//Thêm chi tiêu
	st_groupbox = CreateWindow(L"Button", L"Thêm chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		10, 10, 600, 100, hwnd, NULL, hInst, NULL);
	SendMessage(st_groupbox, WM_SETFONT, WPARAM(hFont), TRUE);


	st_groupbox = CreateWindow(L"STATIC", L"Loại chi tiêu", WS_CHILD | WS_VISIBLE,
		65, 35, 150, 20, hwnd, NULL, hInst, NULL);
	SendMessage(st_groupbox, WM_SETFONT, WPARAM(hFont), TRUE);

	g_comboType = CreateWindow(L"COMBOBOX", L"MyCombo", CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 
		30, 60, 150, 300, hwnd, (HMENU)ID_COMBOTYPE, hInst, NULL);
	SendMessage(g_comboType, WM_SETFONT, WPARAM(hFont), TRUE);
	for (int i = 0; i < arrType.size(); ++i) {
		SendMessage(g_comboType, CB_ADDSTRING, 0, LPARAM(arrType[i].type.c_str()));
	}

	st_groupbox = CreateWindow(L"STATIC", L"Nội dung chi tiêu", WS_CHILD | WS_VISIBLE,
		230, 35, 150, 20, hwnd, NULL, hInst, NULL);
	SendMessage(st_groupbox, WM_SETFONT, WPARAM(hFont), TRUE);

	g_editContent = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER ,
		200, 60, 150, 22, hwnd, (HMENU)ID_EDITCONTENT, hInst, NULL);
	SendMessage(g_editContent, WM_SETFONT, WPARAM(hFont), LPARAM(L"Nội dung"));

	st_groupbox = CreateWindow(L"STATIC", L"Số tiền", WS_CHILD | WS_VISIBLE,
		410, 35, 130, 20, hwnd, NULL, hInst, NULL);
	SendMessage(st_groupbox, WM_SETFONT, WPARAM(hFont), TRUE);

	g_editMoney = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_RIGHT,
		370, 60, 130, 22, hwnd, (HMENU)ID_EDITMONEY, hInst, NULL);
	Edit_SetCueBannerText(g_editMoney, L"Số tiền");
	SendMessage(g_editMoney, WM_SETFONT, WPARAM(hFont), LPARAM(L"Số tiền"));
	SendMessage(g_editMoney, EM_SETLIMITTEXT, 9, 0);

	g_btnAdd = CreateWindow(L"BUTTON", L"Thêm", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		520, 60, 60, 22, hwnd, (HMENU)ID_BTNADD, hInst, NULL);
	SendMessage(g_btnAdd, WM_SETFONT, WPARAM(hFont), NULL);

	//Danh sách chi tiêu
	st_groupbox = CreateWindow(L"Button", L"Danh sách chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		10, 125, 600, 400, hwnd, NULL, hInst, NULL);
	SendMessage(st_groupbox, WM_SETFONT, WPARAM(hFont), TRUE);

	g_ListView = CreateWindow(WC_LISTVIEW, L"List View", WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_ICON,
		30, 160, 560, 325, hwnd, NULL, hInst, NULL);
	SendMessage(g_ListView, LVM_SETEXTENDEDLISTVIEWSTYLE, WPARAM(hFont), LVS_EX_FULLROWSELECT);

	g_TotalMoney = CreateWindowEx(0, L"STATIC", L"Tổng: 0 VND", WS_CHILD | WS_VISIBLE | SS_RIGHT,
		30, 495, 550, 20, hwnd, NULL, hInst, NULL);
	SendMessage(g_TotalMoney, WM_SETFONT, WPARAM(hFont), TRUE);

	//Quản lý thu nhập
	st_groupbox = CreateWindow(L"Button", L"Quản lý thu nhập", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		10, 540, 600, 100, hwnd, NULL, hInst, NULL);
	SendMessage(st_groupbox, WM_SETFONT, WPARAM(hFont), TRUE);

	st_groupbox = CreateWindow(L"STATIC", L"Thu nhập", WS_CHILD | WS_VISIBLE,
		75, 565, 130, 20, hwnd, NULL, hInst, NULL);
	SendMessage(st_groupbox, WM_SETFONT, WPARAM(hFont), TRUE);
	
	g_editBenefice = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_RIGHT,
		30, 585, 150, 22, hwnd, (HMENU)ID_EDITINCOME, hInst, NULL);
	SendMessage(g_editBenefice, WM_SETFONT, WPARAM(hFont), LPARAM(L"Tiền thu nhập"));
	SendMessage(g_editBenefice, EM_SETLIMITTEXT, 9, 0);

	g_btnCheckSaving = CreateWindow(L"BUTTON", L"Kiểm tra", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		250, 580, 100, 30, hwnd, (HMENU)ID_BTNCHECK, hInst, NULL);
	SendMessage(g_btnCheckSaving, WM_SETFONT, WPARAM(hFont), NULL);

	g_SavingMoney = CreateWindowEx(0, L"STATIC", L"Tiết kiệm: 0 VND", WS_CHILD | WS_VISIBLE | SS_RIGHT,
		350, 585, 230, 30, hwnd, NULL, hInst, NULL);
	SendMessage(g_SavingMoney, WM_SETFONT, WPARAM(hFont), TRUE);


	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 130;
	lvCol.pszText = L"Loại chi tiêu";
	ListView_InsertColumn(g_ListView, 0, &lvCol);

	lvCol.cx = 170;
	lvCol.pszText = L"Nội dung chi tiêu";
	ListView_InsertColumn(g_ListView, 1, &lvCol);

	lvCol.cx = 130;
	lvCol.pszText = L"Số tiền (VND)";
	ListView_InsertColumn(g_ListView, 2, &lvCol);

	lvCol.cx = 130;
	lvCol.pszText = L"Thời gian";
	ListView_InsertColumn(g_ListView, 3, &lvCol);

	// Đọc từ file
	arrCategory = file.readFile();
	for (int i = 0; i < arrCategory.size(); i++) {
		displayListView(arrCategory[i],i + 1);
	}
	total_money = setTotalMoney(g_TotalMoney);


	//Biểu đồ
	st_groupbox = CreateWindow(L"Button", L"Biểu đồ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		650, 10, 630, 630, hwnd, NULL, hInst, NULL);
	SendMessage(st_groupbox, WM_SETFONT, WPARAM(hFont), TRUE);

	chart.updateChart(arrType, total_money);
	return true;
}

void onCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
	switch (id)
	{
	case ID_FILE_NEW:
		ListView_DeleteAllItems(g_ListView);
		SendMessage(g_comboType, CB_SETCURSEL, -1, 0);
		SetWindowText(g_editContent, L"");
		SetWindowText(g_editMoney, L"");
		SetWindowText(g_editBenefice, L"");
		SetWindowText(g_SavingMoney, L"Tiết kiệm: 0 VND");
		arrCategory.clear();
		total_money = setTotalMoney(g_TotalMoney);
		chart.updateChart(arrType, total_money);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case ID_BTNADD:
		checkInfo(hwnd);
		break;
	case ID_BTNCHECK:
	{
						if (checkInfoIncome(hwnd)) {
							if (incomeMoney < total_money) {
								MessageBox(hwnd, (L"Bạn đã lỗ " + getStringMoney(total_money - incomeMoney) + L". Cần tiết kiệm ngay!!!").c_str(), 0, MB_OK | MB_ICONINFORMATION);
								break;
							}
							else {
								SetWindowText(g_SavingMoney, (L"Tiết kiệm: " + getStringMoney(incomeMoney - total_money) + L" VND").c_str());
							}
						}
	}
		break;
	case ID_DELETE:
		deleteItem(g_ListView);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
		break;
	case IDM_EXIT:
		file.saveFile(arrCategory);
		DestroyWindow(hwnd);
		break;
	}
}

void onPaint(HWND hwnd) {
	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);
	
	if (total_money != 0) {
		indexFull = -1;
		//Kiểm tra full tròn
		for (int i = 0; i < arrType.size(); i++) {
			if (arrType[i].money == total_money)
			{
				indexFull = i;
				break;
			}
		}
		chart.draw(hdc, indexFull);
		chart.showNote(hdc, total_money);
	}
	EndPaint(hwnd, &ps);
}

void onDestroy(HWND hwnd) {
	file.saveFile(arrCategory);
	PostQuitMessage(0);
}

LRESULT onListviewNotify(HWND hWnd, int idFrom, NMHDR* pnm) {
	switch (pnm->code) {
	case NM_RCLICK:
		sttRow = SendMessage(g_ListView, LVM_GETNEXTITEM, -1, LVNI_SELECTED); 
		if (sttRow != -1) {
			SendMessage(g_ListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
			h_PopUp = CreatePopupMenu();
			InsertMenu(h_PopUp, 0, MF_BYPOSITION, ID_DELETE, L"Xóa");
			POINT p;
			GetCursorPos(&p);
			TrackPopupMenu(h_PopUp, TPM_TOPALIGN | TPM_LEFTALIGN, p.x, p.y, 0, hWnd, NULL);
		}
		break;
	}
	return 0;
}

void initArrType(vector<wstring> defaultType) {
	for (int i = 0; i < defaultType.size(); i++) {
		Type t;
		t.type = defaultType[i];
		t.money = 0;
		t.startAngle = 0;
		t.angle = 0;
		arrType.push_back(t);
	}
}

bool checkInfo(HWND hwnd) {
	//Loại chi tiêu
	size = SendMessage(g_comboType, CB_GETCURSEL, 0, 0);
	if (size < 0) {
		MessageBox(hwnd, L"Bạn phải chọn một loại chi tiêu!", NULL, MB_OK | MB_ICONERROR);
		return false;
	}
	else {
		int bufferSize = SendMessage(g_comboType, CB_GETLBTEXTLEN, size, 0);
		buffer = new WCHAR[bufferSize + 1];
		SendMessage(g_comboType, CB_GETLBTEXT, size, (LPARAM)buffer);
		typeExpense = buffer;
		delete[] buffer;
	}

	//Nội dung
	size = GetWindowTextLength(g_editContent);
	if (size == 0) {
		MessageBox(hwnd, L"Bạn phải nhập nội dung chi tiêu!", NULL, MB_OK | MB_ICONERROR);
		return false;
	}
	else {
		buffer = new WCHAR[size + 1];
		GetWindowText(g_editContent, buffer, size + 1);
		contentExpense = buffer;
		delete[] buffer;
	}

	size = GetWindowTextLength(g_editMoney);
	if (size == 0) {
		MessageBox(hwnd, L"Bạn phải nhập số tiền!", NULL, MB_OK | MB_ICONERROR);
		return false;
	}
	else {
		buffer = new WCHAR[size + 1];
		GetWindowText(g_editMoney, buffer, size + 1);
		moneyExpense = _wtoll(buffer);
		if (moneyExpense == 0) {
			MessageBox(hwnd, L"Số tiền phải lớn hơn 0!", NULL, MB_OK | MB_ICONERROR);
			return false;
		}
		delete[] buffer;
	}

	time_t t = time(0);
	struct tm *now = localtime(&t);
	timeExpense = to_wstring(now->tm_hour) + L":" + to_wstring(now->tm_min) + L"   " +
		to_wstring(now->tm_mday) + L"/" + to_wstring(now->tm_mon + 1) + L"/" + to_wstring(now->tm_year + 1900);

	Category category(typeExpense, contentExpense, moneyExpense, timeExpense);
	arrCategory.push_back(category);
	displayListView(category, arrCategory.size());
	
	InvalidateRect(hwnd, NULL, TRUE);
	total_money = setTotalMoney(g_TotalMoney);
	chart.updateChart(arrType, total_money);

	//Reset
	SendMessage(g_comboType, CB_SETCURSEL, -1, 0);
	SetWindowText(g_editContent, L"");
	SetWindowText(g_editMoney, L"");
	return true;
}

unsigned long setTotalMoney(HWND hwnd) {
	unsigned long sum = 0;
	for (int i = 0; i < arrType.size(); i++) {
		arrType[i].money = 0;
	}

	for (int i = 0; i < arrCategory.size(); i++) {
		sum += arrCategory[i].getMoney();
		for (int j = 0; j < arrType.size(); j++) {
			if (arrType[j].type == arrCategory[i].getType()) {
				arrType[j].money += arrCategory[i].getMoney();
				break;
			}
		}
	}
	wstring wmoney = getStringMoney(sum);
	wstring result = L"Tổng: " + wmoney + L" VND";
	SetWindowText(hwnd, result.c_str());
	return sum;
}

void displayListView(Category category, int index) {
	lv.mask = LVIF_TEXT;
	lv.iItem = index - 1;

	lv.iSubItem = 0;
	lv.pszText = new WCHAR[category.getType().length() + 1];
	wcscpy(lv.pszText, category.getType().c_str());
	ListView_InsertItem(g_ListView, &lv);

	lv.iSubItem = 1;
	lv.pszText = new WCHAR[category.getContent().length() + 1];
	wcscpy(lv.pszText, category.getContent().c_str());
	ListView_SetItem(g_ListView, &lv);

	lv.iSubItem = 2;
	wstring w_money = getStringMoney(category.getMoney());
	lv.pszText = new WCHAR[w_money.length() + 1];
	wcscpy(lv.pszText, w_money.c_str());
	ListView_SetItem(g_ListView, &lv);

	lv.iSubItem = 3;
	lv.pszText = new WCHAR[category.getTime().length() + 1];
	wcscpy(lv.pszText, category.getTime().c_str());
	ListView_SetItem(g_ListView, &lv);
}


void deleteItem(HWND hwnd) {
	int result = MessageBox(0, L"Bạn có chắc chắn muốn xoá?", L"Thông báo", MB_OKCANCEL | MB_ICONQUESTION);
	if (result == 1)
	{
		arrCategory.erase(arrCategory.begin() + sttRow);
		ListView_DeleteItem(hwnd, sttRow);
		total_money = setTotalMoney(g_TotalMoney);
		chart.updateChart(arrType, total_money);
	}
}

wstring getStringMoney(unsigned long money) {
	wstring w_money = to_wstring(money);
	int count = 1;
	int n = w_money.length();
	for (int i = n - 1; i > 0; i--){
		if (i == n - 3 * count) {
			w_money.insert(w_money.begin() + i, L',');
			count++;
		}
	}
	return w_money;
}

bool checkInfoIncome(HWND hwnd) {
	size = GetWindowTextLength(g_editBenefice);
	if (size == 0) {
		MessageBox(hwnd, L"Bạn phải nhập số tiền!", NULL, MB_OK | MB_ICONERROR);
		return false;
	}
	else {
		buffer = new WCHAR[size + 1];
		GetWindowText(g_editBenefice, buffer, size + 1);
		incomeMoney = _wtoll(buffer);
		if (incomeMoney == 0) {
			MessageBox(hwnd, L"Số tiền phải lớn hơn 0!", NULL, MB_OK | MB_ICONERROR);
			return false;
		}
		delete[] buffer;
	}
	return true;
}
