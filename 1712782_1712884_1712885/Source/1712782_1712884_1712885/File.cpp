#include "File.h"


string CalculateInLine(DataFile datLine, string type)
{
	string Res;
	if (type == "1")		//chế độ số nguyên
	{
		if (datLine.stringNum == 3)	//yêu cầu chuyển đổi từ 1 hệ này sang 1 hệ khác	và phép NOT
		{
			int chose;		//hệ hiện tại, chose = 0 thì là hệ 10, = 1 là hệ nhị phân
			if (datLine.strLine[0] == "10")
			{
				chose = 0;			//ban đầu là hệ 10
				QInt x = ScanQInt(datLine.strLine[2], chose);

				if (datLine.strLine[0] == "2" && datLine.strLine[2] == "~")
				{
					QIntTemp  r;

					autofill(r, datLine.strLine[1]);
					r = NOT(r);
					Res = outString(r);

				}
				else if (datLine.strLine[1] == "2")	//chuyển đổi từ 10 -> 2
				{
					bool* bit = DecToBin(x);
					for (int i = 0; i < N; ++i)		//Chuyển từ bool[128] -> string
					{
						if (bit[i] == 0)	Res.insert(Res.length(), "0");
						else Res.insert(Res.length(), "1");
					}
				}
				else if (datLine.strLine[1] == "16")	//chuyển đổi từ 10 -> 16
				{
					char* temp = DecToHex(x);
					return temp;
				}
			}
			else if (datLine.strLine[0] == "2")
			{
				chose = 1;			//ban đầu là hệ nhị phân
				QInt x = ScanQInt(datLine.strLine[2], chose);

				if (datLine.strLine[0] == "2" && datLine.strLine[2] == "~")
				{
					QIntTemp  r;

					autofill(r, datLine.strLine[1]);
					r = NOT(r);
					Res = outString(r);

				}
				else if (datLine.strLine[1] == "10")	//chuyển đổi từ hệ 2 -> 10
				{
					Res = PrintQInt(x);
				}
				else if (datLine.strLine[1] == "16")	//chuyển đổi từ hệ 2 -> 16
				{
					bool *bit = new bool[N];
					//đọc bit và lưu vào mảng bit 128 phần tử
					for (int i = 0; i < N; ++i)
						bit[i] = (x.data[i / 32] >> (N - 1 - i) & 1);

					char* temp = BinToHex(bit);
					delete[] bit;
					return temp;
				}
			}
			else if (datLine.strLine[0] == "16")
			{
				//trường hợp chuyển từ 16 -> 2
				Res = HextoBin(datLine.strLine[2]);		//lấy kết quả sau khi chuyển từ Hex sang Bin

														//trường hợp chuyển từ 16 - > 10
				if (datLine.strLine[1] == "10")
				{
					QInt x = ScanQInt(Res, 1);
					Res = PrintQInt(x);
				}
			}
		}
		else if (datLine.stringNum == 4)	//yêu cầu tính toán
		{
			if (datLine.strLine[0] == "16")
			{
				//hex to bin
				string temp1, temp2;
				temp1 = HextoBin(datLine.strLine[1]);
				temp2 = HextoBin(datLine.strLine[3]);
				//tao datafile moi gom 1 dong 
				DataFile temp;
				temp.strLine[0] = "2";
				temp.strLine[1] = temp1;
				temp.strLine[2] = datLine.strLine[2];
				temp.strLine[3] = temp2;
				temp.stringNum = 4;

				string result = CalculateInLine(temp, type);
				cout << result << endl;
				bool *bit = new bool[N];
				//đọc bit và lưu vào mảng bit 128 phần tử
				//sao chép mảng result vào bit
				for (int i = 127; i >= 0; i--)
					if (result[i] == '1') bit[i] = true;
					else bit[i] = false;
				//chuyển sang hệ 16
				char* asd = BinToHex(bit);
				delete[] bit;
				return asd;
			}
			if (datLine.strLine[0] == "10")
			{
				//dec to bin
				QInt x, y;
				x = ScanQInt(datLine.strLine[1], 0);
				y = ScanQInt(datLine.strLine[3], 0);
				bool* tempx;
				bool* tempy;

				tempx = DecToBin(x);
				tempy = DecToBin(y);
				string temp1, temp2;
				//sao chép mảng bit sang string
				for (int i = 0; i < 128; i++)
					temp1.push_back(tempx[i] + 48);
				for (int i = 0; i < 128; i++)
					temp2.push_back(tempy[i] + 48);


				//tao datafile moi gom 1 dong 
				DataFile temp;
				temp.strLine[0] = "2";
				temp.strLine[1] = temp1;
				temp.strLine[2] = datLine.strLine[2];
				temp.strLine[3] = temp2;
				temp.stringNum = 4;

				string result = CalculateInLine(temp, type);

				bool *bit = new bool[N];
				cout << result.length();
				for (int i = 127; i >= 0; i--)
					if (result[i] == '1') bit[i] = true;
					else bit[i] = false;
				//chuyển sang hệ 10
				char* asd = BinToDec(bit);
				asd[128] = 0;
				delete[] bit;
				return asd;
			}
			if (datLine.strLine[0] == "2")
			{
				QIntTemp a, b, r;
				//Nhap vao bien 
				autofill(a, datLine.strLine[1]);
				autofill(b, datLine.strLine[3]);
				//thuc hien phep tinh
				if (datLine.strLine[2] == "+")
				{
					r = a + b;
					Res = outString(r);
				}
				if (datLine.strLine[2] == "-")
				{
					r = a - b;
					Res = outString(r);
				}
				if (datLine.strLine[2] == "*")
				{
					r = a * b;
					Res = outString(r);
				}
				if (datLine.strLine[2] == "/")
				{
					QIntTemp zero;
					Zero(zero);
					if (b == zero)
					{
						Res = "Khong the chia cho so 0";
						return Res;
					}
					else;
					r = a / b;
					Res = outString(r);
				}
				if (datLine.strLine[2] == "<")
				{
					if (a < b) Res = "TRUE";
					else Res = "FALSE";
				}
				if (datLine.strLine[2] == "<=")
				{
					if (a <= b) Res = "TRUE";
					else Res = "FALSE";
				}
				if (datLine.strLine[2] == ">")
				{
					if (a > b) Res = "TRUE";
					else Res = "FALSE";
				}
				if (datLine.strLine[2] == ">=")
				{
					if (a >= b) Res = "TRUE";
					else Res = "FALSE";
				}
				if (datLine.strLine[2] == "==")

				{
					if (a == b) Res = "TRUE";
					else Res = "FALSE";
				}
				if (datLine.strLine[2] == "<<")
				{

					QIntTemp one, count;
					Zero(one); Zero(count);
					if (b <= one)
					{
						Res = outString(a);
						return Res;
					}
					one.array[127] = 1;
					int n = 0;
					while (count != b)
					{
						n = n + 1;
						count = count + one;
					}
					shiftLeft(a, n);
					Res = outString(a);
				}
				if (datLine.strLine[2] == ">>")
				{
					QIntTemp one, count;
					Zero(one); Zero(count);
					if (b <= one)
					{
						Res = outString(a);
						return Res;
					}
					one.array[127] = 1;
					int n = 0;
					while (count != b)
					{
						n = n + 1;
						count = count + one;
					}
					shiftRight(a, n);
					Res = outString(a);
				}
				if (datLine.strLine[2] == "ror")
				{
					QIntTemp one, count;
					Zero(one); Zero(count);
					if (b <= one)
					{
						Res = outString(a);
						return Res;
					}
					one.array[127] = 1;
					int n = 0;
					while (count != b)
					{
						n = n + 1;
						count = count + one;
					}
					rotateRight(a, n);
					Res = outString(a);
				}
				if (datLine.strLine[2] == "rol")
				{
					QIntTemp one, count;
					Zero(one); Zero(count);
					if (b <= one)
					{
						Res = outString(a);
						return Res;
					}
					one.array[127] = 1;
					int n = 0;
					while (count != b)
					{
						n = n + 1;
						count = count + one;
					}
					rotateLeft(a, n);
					Res = outString(a);
				}
				if (datLine.strLine[2] == "AND" || datLine.strLine[2] == "&")
				{
					r = a & b;
					Res = outString(r);
				}
				if (datLine.strLine[2] == "OR" || datLine.strLine[2] == "|")
				{
					r = a | b;
					Res = outString(r);
				}
				if (datLine.strLine[2] == "XOR" || datLine.strLine[2] == "^")
				{
					r = a ^ b;
					Res = outString(r);
				}
			}
		}
	}
	else if (type == "2")
	{
		Res = "";
		if (datLine.strLine[0] == "10")
		{
			Qfloat qFloat = DecToBin(datLine.strLine[2]);
			for (int i = 0; i < 128; i++)
			{
				int k = (qFloat.data[i / 32] >> (128 - 1 - i)) & 1;
				if (k == 0)
				{
					Res = Res + '0';
				}
				else if (k == 1)
				{
					Res = Res + '1';
				}
				//outFile << k;
			}
			//outFile << endl;

		}
		else if (datLine.strLine[0] == "2")
		{
			Qfloat qFloat;
			for (int i = 0; i < 128; i++)
			{
				if (datLine.strLine[2][i] == '0')
				{
					qFloat.data[i / 32] = qFloat.data[i / 32] & (~1 << (128 - 1 - i));
				}
				else if (datLine.strLine[2][i] == '1')
				{
					qFloat.data[i / 32] = (1 << (128 - 1 - i)) | qFloat.data[i / 32];
				}
			}

			Res = BinToDec(qFloat);
		}
	}
	return Res;
}

DataFile FragStrLine(string strLine)
{
	DataFile dataFile;
	for (int i = 0; i < 4; i++)
	{
		dataFile.strLine[i] = "";
	}

	int countStr = 0;
	for (int i = 0; i < strLine.length(); i++)
	{
		if (strLine[i] != ' ')
		{
			dataFile.strLine[countStr] = dataFile.strLine[countStr] + strLine[i];
		}

		if (strLine[i] == ' ' || strLine[i] == '\0')
		{
			countStr++;
			dataFile.stringNum = countStr + 1;
		}
	}

	return dataFile;
}

void OpenFile(string inName, string outName, string type)
{
	ifstream inFile(inName, ios::in);	//mo file
	ofstream outFile(outName, ios::out);

	string strLine = "";		//lưu các chuỗi trên 1 dòng
								//Đọc thông tin lần lượt trên dòng cho đến cuối file
	while (!inFile.eof())
	{
		getline(inFile, strLine);		//lấy tất cả chuỗi trên dòng
		DataFile dataFile = FragStrLine(strLine);		//phân mảnh thành các chuỗi nhỏ
		string temp = CalculateInLine(dataFile, type);	//Tính toán và lưu kết quả
		outFile << temp << endl;		// xuất vào OutFile		
	}
	// dong file
	inFile.close();
	outFile.close();
}