#ifndef __QFLOAT_H__
#define __QFLOAT_H__
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


/*Đinh nghĩa struct kiểu Qfloat*/
struct Qfloat
{
	unsigned int data[4];
};

/*Hàm chuyển đổi số dạng Qfloat nhị phân sang dạng chuỗi thập phân*/
string BinToDec(Qfloat &x);

/*Hàm chuyển đổi từ chuỗi dạng thập phân sang Qfloat dạng nhị phân*/
Qfloat DecToBin(string x);

/*Hàm nhập Qfloat với kiểu nhập vào là chuỗi dạng thập phân và lưu dưới dạng nhị phân kiểu Qfloat*/
void ScanQfloat(Qfloat &x);

/*Xuất Qfloat ra màn hình*/
void PrintQfloat(Qfloat x);


#endif // !__QFLOAT_H__
