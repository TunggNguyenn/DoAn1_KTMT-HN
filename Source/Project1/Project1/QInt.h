#ifndef __QINT_H__
#define __QINT_H__
#include "TinhToan.h"
#include<iostream>
#include <string>
#include<fstream>
#include<stdio.h>
#include <malloc.h>
using namespace std;

#define N 128		// 16 bytes = 128 bits

//biến cấu trúc lưu trữ số nguyên lớn
//data[4]: lưu trữ số nguyên lớn dưới dạng bit
struct QInt
{
	unsigned int data[4];
};


//---- ScanQInt

//Chuyển từ dạng chuỗi số nguyên sang dạng chuỗi nhị phân
string strDec2strBin(string str);

//Hàm lấy bù 2 
void BitwiseNot_Plus1(string &strRes);

//hàm nhập số nguyên lớn từ tập tin
//strQInt: số QInt đc lưu trong tập tin
//chose: kiểu dữ liệu nhập vào, 0: số thập phân, 1: số nhị phân
QInt ScanQInt(string strQInt, int chose);

//----PrintQInt

//Hàm nhân chuỗi số nguyên với 2
void Str_x2(string &strA);

//Hàm lấy 2^M, M>=0
string Pow_2_M(int m);

//Hàm đổi kí tự từ 0 -> 9 ra kiểu số nguyên
char ConvertCh2Int(char a);

//Hàm đổi số nguyên từ 0 -> 9 ra thành kí tự tương ứng
char ConvertInt2Ch(char intA);

//Hàm cộng 2 kí tự, các kí tự từ 0 -> 9
//kết quả trả ra kí tự ở hàng đơn vị và kiểm tra phép cộng có nhớ 1 hay không
char ChPlusCh(char a, char b, char &mem);

//Hàm cộng 2 chuỗi
string StrPlusStr(string strA, string strB);

//hàm trả ra chuỗi thập phân của QInt, kiểu trả ra là string để sử dụng xuất ra màn hình hoặc tập tin
string PrintQInt(QInt x);

//Hàm chuyển đổi số QInt thập phân sang nhị phân
bool* DecToBin(QInt x);

//Hàm chuyển đổi số QInt thập phân sang nhị phân
//QInt được lưu trên 128 bit -> mảng bool[128]
char* BinToDec(bool *bit);

//Hàm đổi 4 bit nhị phân thành 1 số hệ thập lục
string NibbleBin2Hex(string strNibble);

//Hàm chuyển đổi số QInt nhị phân sang thập lục phân
char* BinToHex(bool *bit);

//Hàm chuyển đổi số QInt thập phân sang thập lục phân
char* DecToHex(QInt x);

//Hàm đổi 1 bit thập lục thành 4 số hệ nhị phân
string NibbleHex2Bin(char ch);

//Hàm chuyển đổi số QInt thập lục sang thập phân
string HextoBin(string Str);



#endif // !__QINT_H__
