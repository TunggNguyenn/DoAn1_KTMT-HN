#ifndef __FILE_H__
#define __FILE_H__
#include "QInt.h"
#include "TinhToan.h"
#include "Qfloat.h"
#include<iostream>
#include <string>
#include<fstream>
#include<stdio.h>
#include <malloc.h>
using namespace std;


//biến cấu trúc lưu trữ thông tin trên 1 dòng, trên 1 dòng có tối đa là 4 chuỗi
//Xét stringNum và các chuỗi trên dòng, ta sẽ chia thành các trường hợp tính toán
//stringNum = 3: yêu cầu chuyển đổi từ 1 hệ này sang 1 hệ khác		VD: 10 2 8793278316		->stringNum = 3
//	ở trường hợp này xét: lần lượt các chuỗi str[0], str[1], để biết hệ muốn chuyển đổi
//						  str[2] là số QInt cần chuyển đổi
//stringNum = 4: yêu cầu tính toán số QInt.		VD: 2 1111100011101010111 + 01101110110111		-> stringNum =4
//	ở trường hợp này xét: str[2] để xem toán tử tính toán (+, -, *, /, >>, <<)
//						  str[0] để xem hệ của số QInt
//						  str[1] là số QInt và str[3] là tùy trường hợp theo toán tử
struct DataFile
{
	string strLine[4];	//lưu các chuỗi trên từng dòng
	int stringNum;	//lưu số chuỗi trên 1 dòng
};


//Hàm tính toán phép tính trên dòng và trả về 
string CalculateInLine(DataFile datLine, string type);

//Hàm phân mảnh tất cả các chuỗi trong biến strLine
DataFile FragStrLine(string strLine);

//Hàm mở file và lấy dữ liệu từ file
//type = 1 nếu là chế độ số nguyên, 2 là chế độ số thực
void OpenFile(string inName, string outName, string type);

#endif // !__FILE_H__
