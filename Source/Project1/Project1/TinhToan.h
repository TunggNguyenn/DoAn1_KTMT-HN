#ifndef __TINHTOAN_H__
#define __TINHTOAN_H__
#include <iostream>
#include <string>
#include <malloc.h>
using namespace std;

//Khởi tạo
struct QIntTemp
{
	int array[128];
	int& operator [](int n)
	{
		return array[n];
	}
	QIntTemp& operator =(QIntTemp src)
	{
		for (int i = 0; i < 128; i++)
		{
			array[i] = src.array[i];
		}
		return *this;
	}
};
void taoQIntTemp(QIntTemp &ts, QIntTemp &src);
void taoQIntTemp(QIntTemp &ts, int * src, int n);

//tự động điền vào cho đủ 128 phần tử
void autofill(QIntTemp &ts, string a);  //khởi tạo phần tử mới theo chuổi a
void autofill(QIntTemp &ts);	//thêm số O cho đủ 128 phần tử

void input(QIntTemp &ts);
void output(QIntTemp &ts);

//tìm số 1 thứ n
int serialNum1(QIntTemp &ts, int n);
//dấu lượng
bool isNegative(QIntTemp &ts);  //kiểm tra số âm
void changeSign(QIntTemp &ts);	//đảo dấu
void changeSign(QIntTemp &ts, bool n); //ép dấu
//phép toán
QIntTemp operator +(QIntTemp &ts, QIntTemp &src);
QIntTemp operator -(QIntTemp &ts, QIntTemp &src);
QIntTemp operator *(QIntTemp &ts, QIntTemp &src);
QIntTemp operator /(QIntTemp &ts, QIntTemp &src);
//dịch bit
void shiftRight(QIntTemp &ts);
void shiftLeft(QIntTemp &ts);
void rotateLeft(QIntTemp &ts);
void rotateRight(QIntTemp &ts);

void shiftRight(QIntTemp &ts, int n);
void shiftLeft(QIntTemp &ts, int n);
void rotateLeft(QIntTemp &ts, int n);
void rotateRight(QIntTemp &ts, int n);
//toán tử so sánh
bool operator ==(QIntTemp &ts, QIntTemp &src);
bool operator <(QIntTemp &ts, QIntTemp &src);
bool operator >(QIntTemp &ts, QIntTemp &src);
bool operator <=(QIntTemp &ts, QIntTemp &src);
bool operator >=(QIntTemp &ts, QIntTemp &src);
bool operator !=(QIntTemp &ts, QIntTemp &src);

QIntTemp operator &(QIntTemp &ts, QIntTemp &src);
QIntTemp operator |(QIntTemp &ts, QIntTemp &src);
QIntTemp operator ^(QIntTemp &ts, QIntTemp &src);
QIntTemp NOT(QIntTemp &ts);

//liên quan đến số 0
bool isZero(QIntTemp &ts); //kiểm tra xem có phải số 0
void Zero(QIntTemp &ts);	// biến thành số 0

//các hàm bổ trợ thêm
void xoaychuoi(string &a);   //đảo chiều chuổi string
void bu2(QIntTemp &ts);		//biến thành số bù 2
void bu1(QIntTemp &ts);		//biến thành số bù 1
string outString(QIntTemp &ts);		//trích QIntTemp thành kiểu string

#endif // !__TINHTOAN_H__
