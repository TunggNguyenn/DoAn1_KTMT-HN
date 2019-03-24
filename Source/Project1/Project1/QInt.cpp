#include "QInt.h"


//---- ScanQInt
string strDec2strBin(string str)
{
	string strChia2 = "";  //Chuỗi nhị phân
	int s = 0, k;

	while (str[0] != NULL && str[0] != '0')
	{
		string strnew = "";  //Xác định kết quả sau khi chia (thương)
		bool flag = false;  //Xác định số dư 1

		string x1 = "";
		x1 = str[str.length() - 1];

		if (stoi(x1) % 2 == 0)
		{
			strChia2 = '0' + strChia2;
		}
		else
		{
			strChia2 = '1' + strChia2;
		}


		for (int i = 0; i < str.length(); i++)
		{
			if (i == (str.length() - 1) && flag == true)
			{
				break;
			}

			string x2 = "";
			x2 = str[i];

			k = stoi(x2);


			if (k < 2)
			{
				if (str[i + 1] != NULL)
				{
					if (i != 0 && flag == false)
					{
						strnew = strnew + '0';
					}


					x2 = x2 + str[i + 1];
					k = stoi(x2);

					char *x3 = new char[2];
					x3[0] = (char)(48 + (int)k / 2);
					x3[1] = '\0';


					strnew = strnew + string(x3);



					if (k % 2 == 0)
					{
						i++;
						flag = false;
					}
					else
					{
						str[i + 1] = '1';
						flag = true;
					}
				}
				else
				{
					strnew = strnew + '0';
					break;
				}

			}
			else
			{

				char *x3 = new char[2];
				x3[0] = (char)(48 + (int)k / 2);
				x3[1] = '\0';

				strnew = strnew + string(x3);

				if (str[i + 1] != NULL)
				{
					if (k % 2 == 0)
					{
						flag = false;
						continue;

					}
					else
					{
						str[i] = '1';
						i--;
						flag = true;
					}
				}
				else
				{
					break;
				}

			}

		}

		str = strnew;
	}

	return strChia2;
}

void BitwiseNot_Plus1(string &strRes)
{
	int i = 1;			//phần bit nhớ +1 hay không
	int flat = 0;		//con chạy trên dãy ́8 bit
	int BitNumber = strRes.length();	//số bit cần lấy bù 2

	while (strRes[flat])	//Chuyên sang bù 1
	{
		if (strRes[flat] == '0') strRes[flat] = '1';
		else strRes[flat] = '0';
		++flat;
	}
	//Chuyển sang bù 2
	for (flat = BitNumber - 1; flat >= 0 && i == 1; --flat)
	{
		if (strRes[flat] == '1')
		{
			strRes[flat] = '0';
			i = 1;
		}
		else
		{
			strRes[flat] = '1';
			i = 0;
		}
	}
}

QInt ScanQInt(string strQInt, int chose)
{
	QInt x;

	//khởi tạo 128 bits của x = 0
	x.data[0] = { 0 };
	x.data[1] = { 0 };
	x.data[2] = { 0 };
	x.data[3] = { 0 };


	//loại bỏ số 0 ở đâu chuỗi khi người dùng nhập thừa
	while (strQInt[0] == '0' && strQInt.length() > 1)
	{
		strQInt.erase(0, 1);
	}

	if (chose == 0)
	{
		//xem QInt là dương hay âm
		char sign = 1;
		if (strQInt[0] == '-')
		{
			strQInt.erase(0, 1);
			sign = -1;
		}

		//chuyển 10 -> 2
		string strBin = strDec2strBin(strQInt);

		//nếu là số âm sign = -1 thì phải lấy bù 2;
		if (sign == -1)
		{
			BitwiseNot_Plus1(strBin);
		}

		//bật bit trên x
		int idStrBin = 0;		//chạy trên strBin
		int idX = N - strBin.length();		// vtri strBin tương ứng trên x
		int id = 0;		// chạy trên x từ 0 -> idX
		if (sign == -1)	//nếu là số âm thì chép các bit 1 chỉ dấu
		{
			while (id < idX)
			{
				x.data[id / 32] = (1 << (N - 1 - id)) | x.data[id / 32];
				++id;
			}
		}
		while (idX < N)
		{
			if (strBin[idStrBin] == '1')
			{
				x.data[idX / 32] = (1 << (N - 1 - idX)) | x.data[idX / 32];
			}
			++idX;
			++idStrBin;
		}
	}
	else if (chose == 1) {
		int id = 0;		//chạy trên strQInt
		int idX = N - strQInt.length();		//chạy trên bit của x.data, tương ứng vị trí strQInt[id] trên đó
		while (idX < N)
		{
			if (strQInt[id] == '1')
			{
				x.data[idX / 32] = (1 << (N - 1 - idX)) | x.data[idX / 32];
			}
			++idX;
			++id;
		}
	}

	return x;
}

//----PrintQInt
void Str_x2(string &strA)
{
	bool temp = 0;	//biến lưu số nhớ (1 hoặc 0) sau khi thực hiện phép nhân
	for (int i = strA.length() - 1; i >= 0; --i)
	{
		switch (strA[i])
		{
		case '0':
			if (temp == 0) strA[i] = '0';
			else strA[i] = '1';
			temp = 0;
			break;
		case '1':
			if (temp == 0) strA[i] = '2';
			else strA[i] = '3';
			temp = 0;
			break;
		case '2':
			if (temp == 0) strA[i] = '4';
			else strA[i] = '5';
			temp = 0;
			break;
		case '3':
			if (temp == 0) strA[i] = '6';
			else strA[i] = '7';
			temp = 0;
			break;
		case '4':
			if (temp == 0) strA[i] = '8';
			else strA[i] = '9';
			temp = 0;
			break;
		case '5':
			if (temp == 0) strA[i] = '0';
			else strA[i] = '1';
			temp = 1;
			break;
		case '6':
			if (temp == 0) strA[i] = '2';
			else strA[i] = '3';
			temp = 1;
			break;
		case '7':
			if (temp == 0) strA[i] = '4';
			else strA[i] = '5';
			temp = 1;
			break;
		case '8':
			if (temp == 0) strA[i] = '6';
			else strA[i] = '7';
			temp = 1;
			break;
		case '9':
			if (temp == 0) strA[i] = '8';
			else strA[i] = '9';
			temp = 1;
			break;
		}

		if (i == 0 && temp == 1)
		{
			strA.insert(0, "1");
		}
	}
}

string Pow_2_M(int m)
{
	string Res;
	if (m == 0) Res = "1";
	else if (m == 1) Res = "2";
	else
	{
		Res = "2";
		for (int i = 2; i <= m; ++i)
			Str_x2(Res);
	}
	return Res;
}

char ConvertCh2Int(char a)
{
	switch (a)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	}
	return -1;
}

char ConvertInt2Ch(char intA)
{
	switch ((int)intA)
	{
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	}
	return -1;
}

char ChPlusCh(char a, char b, char &mem)
{
	char nA = ConvertCh2Int(a);		//kí tự a sau khi đc chuyển thành số nguyên
	char nB = ConvertCh2Int(b);		//kí tự b sau khi đc chuyển thành số nguyên
	char res = nA + nB;

	if ((int)res > 9) mem = '1';		//kiểm tra sau khi cộng có nhớ 1 hay ko
	else mem = '0';

	res = (int)res % 10;	//lấy chữ số hàng đơn vị
	res = ConvertInt2Ch(res); //đổi thành dạng kí tự;

	return res;
}

string StrPlusStr(string strA, string strB)
{
	string Res;
	int idA = strA.length() - 1;
	int idB = strB.length() - 1;
	char mem = '0';		//số nhớ của phép cộng ở hàng hiện tại
	char PreMem = '0';	//số nhớ của phép cộng ở hàng lúc trước
	char chTemp;
	while (idA >= 0 && idB >= 0)
	{
		//cộng 2 chữ số theo hàng
		PreMem = mem;
		chTemp = ChPlusCh(strA[idA], strB[idB], mem);
		chTemp = ChPlusCh(chTemp, PreMem, PreMem);
		if (PreMem == '1' && mem == '0') mem = '1';

		//kết quả của phép tính cộng đc thêm vào chuỗi kết quả
		Res.insert(0, "0");
		Res[0] = chTemp;

		--idA;
		--idB;
	}
	//tiếp tục cộng khi còn số nhớ
	while (idA >= 0)
	{
		chTemp = ChPlusCh(strA[idA], mem, mem);
		//kết quả của phép tính cộng đc thêm vào chuỗi kết quả
		Res.insert(0, "0");
		Res[0] = chTemp;
		--idA;
	}

	while (idB >= 0)
	{
		chTemp = ChPlusCh(strB[idB], mem, mem);
		//kết quả của phép tính cộng đc thêm vào chuỗi kết quả
		Res.insert(0, "0");
		Res[0] = chTemp;
		--idB;
	}
	if (mem == '1')
		Res.insert(0, "1");

	return Res;
}

string PrintQInt(QInt x)
{
	bool *bit = new bool[N];
	//đọc bit và lưu vào mảng bit 128 phần tử
	for (int i = 0; i < N; ++i)
		bit[i] = (x.data[i / 32] >> (N - 1 - i) & 1);


	int m;		//số mũ
	string Res = "0";  //chuỗi lưu QInt nhị phân thành dạng thập phân
	string StrPow_2_M;	//chuỗi lưu kết quả sau khi thực hiện phép tính 2^M
	int sign = 0;	//biến xác định dấu của số thập phân, 0: dương, 1: âm

	//dựa vào dấu lượng xét dạng thập phân là số âm hay dương
	//nếu là số âm thì phải lấy bù 2
	if (bit[0] == 1)
	{
		sign = 1;
		string strTemp;
		for (int i = N - 1; i >= 0; --i)
		{
			if (bit[i] == 0) strTemp.insert(0, "0");
			else strTemp.insert(0, "1");
		}
		BitwiseNot_Plus1(strTemp);
		for (int i = 0; i < N; ++i)
		{
			if (strTemp[i] == '0') bit[i] = 0;
			else bit[i] = 1;
		}
	}

	//sau khi đổi lấy bù 2 của số âm thì tiếp tục đổi ra dạng thập phân, tương tự như đổi số dương
	for (int i = N - 1; i >= 0; --i)
	{
		if (bit[i] == 1)
		{
			m = N - 1 - i;
			StrPow_2_M = Pow_2_M(m);
			Res = StrPlusStr(Res, StrPow_2_M);
		}
	}

	if (sign == 1) Res.insert(0, "-");

	delete[]bit;
	return Res;
}

//----DecToBin
bool* DecToBin(QInt x)
{
	bool *bit = new bool[N];
	//đọc bit 
	for (int i = 0; i < N; ++i)
		bit[i] = (x.data[i / 32] >> (N - 1 - i) & 1);

	return bit;
}

//----BinToDec
char* BinToDec(bool *bit)
{
	char* strRes = new char[N + 1];

	for (int i = 0; i < N; ++i)
	{
		if (bit[i] == 0) strRes[i] = '0';
		else strRes[i] = '1';
	}
	strRes[N] = '\0';
	return strRes;
}

//----BinToHex
string NibbleBin2Hex(string strNibble)
{
	if (strNibble.compare("0000") == 0) return "0";
	else if (strNibble.compare("0001") == 0) return "1";
	else if (strNibble.compare("0010") == 0) return "2";
	else if (strNibble.compare("0011") == 0) return "3";
	else if (strNibble.compare("0100") == 0) return "4";
	else if (strNibble.compare("0101") == 0) return "5";
	else if (strNibble.compare("0110") == 0) return "6";
	else if (strNibble.compare("0111") == 0) return "7";
	else if (strNibble.compare("1000") == 0) return "8";
	else if (strNibble.compare("1001") == 0) return "9";
	else if (strNibble.compare("1010") == 0) return "A";
	else if (strNibble.compare("1011") == 0) return "B";
	else if (strNibble.compare("1100") == 0) return "C";
	else if (strNibble.compare("1101") == 0) return "D";
	else if (strNibble.compare("1110") == 0) return "E";
	else return "F";
}

char* BinToHex(bool *bit)
{
	string strHex;		//lưu chuỗi thập lục
	string strNibble = "0000";	//định nghĩa 4 bit nhị phân để đổi thành 1 số thập lục phân
	int i = N - 1;		//chỉ số của bit*
	int idNib = 3;		//chỉ số của strNibble


	while (1)
	{
		if (i == -1) break;

		// gộp 4 bit nhị phân để đổi thành hệ thập lục phân
		while (idNib != -1 && i != -1)
		{
			if (bit[i] == 1) strNibble[idNib] = '1';
			else strNibble[idNib] = '0';

			--idNib;
			--i;
		}
		//đổi 4 bit thành 1 số hệ thập lục phân 
		//sau đó đưa vào mảng đưa các số hệ thập lục
		strHex.insert(0, NibbleBin2Hex(strNibble));

		//tạo mới để chuỗi tiếp tục nhận 4 bit nhị phân, và tạo mới con trỏ chỉ số idNib
		strNibble = "0000";
		idNib = 3;
	}

	char* strRes = new char[strHex.length() + 1];
	for (int i = 0; i < strHex.length(); ++i)
	{
		strRes[i] = strHex[i];
	}
	strRes[strHex.length()] = '\0';
	return strRes;
}

//----DecToHex
char* DecToHex(QInt x)
{
	bool* bit = DecToBin(x);
	return BinToHex(bit);
}

//----HextoBin

string NibbleHex2Bin(char ch)
{
	if (ch == '0') return "0000";
	else if (ch == '1') return "0001";
	else if (ch == '2') return "0010";
	else if (ch == '3') return "0011";
	else if (ch == '4') return "0100";
	else if (ch == '5') return "0101";
	else if (ch == '6') return "0110";
	else if (ch == '7') return "0111";
	else if (ch == '8') return "1000";
	else if (ch == '9') return "1001";
	else if (ch == 'A') return "1010";
	else if (ch == 'B') return "1011";
	else if (ch == 'C') return "1100";
	else if (ch == 'D') return "1101";
	else if (ch == 'E') return "1110";
	else return "1111";
}

string HextoBin(string Str)
{
	string temp;

	for (int idStr = 0; idStr < Str.length(); ++idStr)
	{
		temp.insert(temp.length(), NibbleHex2Bin(Str[idStr]));
	}

	return temp;
}
