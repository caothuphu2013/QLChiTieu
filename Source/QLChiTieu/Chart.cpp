#include "stdafx.h"
#include "Chart.h"

Chart::Chart() {

}

Chart::~Chart() {

}

Chart::Chart(int _px, int _py, int _radius) {
	this->px = _px;
	this->py = _py;
	this->radius = _radius;
	this->arrType.resize(6);
	this->arrType[0].r = 255;
	this->arrType[1].b = 255;
	this->arrType[2].g = 255;
	this->arrType[3].r = 255;
	this->arrType[3].b = 255;
	this->arrType[4].b = 255;
	this->arrType[4].g = 255;
	this->arrType[5].r = 255;
	this->arrType[5].g = 255;
}

void Chart::updateChart(vector<Type> _arrType, unsigned long totalmoney) {
	for (int i = 0; i < _arrType.size(); i++) {
		this->arrType[i].type = _arrType[i].type;
		this->arrType[i].money = _arrType[i].money;
	}

	for (int i = 0; i < _arrType.size(); i++) {
		arrType[i].angle = (float)(arrType[i].money * 1.0 / totalmoney) * 360;
	}

	arrType[0].startAngle = 90;
	for (int i = 1; i < _arrType.size(); i++) {
		arrType[i].startAngle = arrType[i - 1].startAngle + arrType[i - 1].angle;
	}
}

void Chart::draw(HDC hdc, int indexFull) {
	if (indexFull == -1) {
		for (int i = 0; i < arrType.size(); i++) {
			if (arrType[i].money != 0) {
				SetDCBrushColor(hdc, RGB(arrType[i].r, arrType[i].b, arrType[i].g));
				SetDCPenColor(hdc, RGB(241, 241, 241));
				SelectObject(hdc, GetStockObject(DC_BRUSH));
				SelectObject(hdc, GetStockObject(DC_PEN));

				BeginPath(hdc);
				MoveToEx(hdc, this->px, this->py, NULL);
				AngleArc(hdc, this->px, this->py, this->radius, arrType[i].startAngle , arrType[i].angle);
				LineTo(hdc, this->px, this->py);
				EndPath(hdc);
				StrokeAndFillPath(hdc);
			}
		}
	}
	else {
		SetDCBrushColor(hdc, RGB(arrType[indexFull].r, arrType[indexFull].b, arrType[indexFull].g));
		SetDCPenColor(hdc, RGB(241, 241, 241));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SelectObject(hdc, GetStockObject(DC_PEN));
		Ellipse(hdc, 785, 70, 1145, 430);
	}
}

void Chart::showNote(HDC hdc, unsigned long totalMoney) {
	HFONT hFontInside = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, VIETNAMESE_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
	HFONT hFontOutside = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, VIETNAMESE_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
	
	struct Point {
		int x, y;
	};
	vector<Point> arrPoint = {
		{ 700, 470 },
		{ 900, 470 },
		{ 1120, 470 },
		{ 700, 540 },
		{ 900, 540 },
		{ 1120, 540 }
	};
	SetBkMode(hdc, TRANSPARENT);
	SelectObject(hdc, hFontInside);
	SetTextColor(hdc, RGB(0, 0, 0));
	int total_percent = 0;

	for (int i = 0; i < this->arrType.size(); ++i)
	{
		SetDCBrushColor(hdc, RGB(arrType[i].r, arrType[i].b, arrType[i].g));
		Rectangle(hdc, arrPoint[i].x, arrPoint[i].y, arrPoint[i].x + 50, arrPoint[i].y + 50);
		RECT rect = { arrPoint[i].x, arrPoint[i].y, arrPoint[i].x + 50, arrPoint[i].y + 50 };
		total_percent += (int)round(arrType[i].money * 1.0 / totalMoney) * 100;
	
		DrawText(hdc, (to_wstring((int)round((arrType[i].money * 1.0 / totalMoney) * 100)) + L'%').c_str(), -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER);
	}

	SelectObject(hdc, hFontInside);
	SetTextColor(hdc, RGB(0, 0, 0));
	for (int i = 0; i < this->arrType.size(); ++i)
	{
		RECT rect = { arrPoint[i].x + 60, arrPoint[i].y, arrPoint[i].x + 150, arrPoint[i].y + 50 };
		DrawText(hdc, arrType[i].type.c_str(), -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_LEFT | DT_VCENTER);
	}
}
