#include "stdafx.h"
#include "Category.h"

Category::Category() {

}

Category::~Category() {

}

Category::Category(wstring _type, wstring _content, unsigned long _money, wstring _time) {
	this->type = _type;
	this->content = _content;
	this->money = _money;
	this->time = _time;
}

wstring Category::getType() {
	return this->type;
}

wstring Category::getContent() {
	return this->content;
}

unsigned long Category::getMoney() {
	return this->money;
}

wstring Category::getTime() {
	return this->time;
}

void Category::setType(wstring _type) {
	this->type = _type;
}

void Category::setContent(wstring _content) {
	this->content = _content;
}

void Category::setMoney(unsigned long _money) {
	this->money = _money;
}

void Category::setTime(wstring _time) {
	this->time = _time;
}