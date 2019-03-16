#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Qfloat
{
	unsigned int data[4];
};

/*Chuyển từ dạng chuỗi số nguyên sang dạng chuỗi nhị phân*/
string StrChia2(string str)
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

/*Chuyển từ chuỗi số phần không nguyên sang nhị phân*/
string StringNhan2(string str)
{
	if (str.length() == 1 && str[0] == '0')
	{
		string str = "";
		for (int i = 0; i < 300; i++)
		{
			str = str + '0';
		}
		return str;
	}

	string strNhan2 = "";

	int numbers = 1;
	while (numbers <= 114)
	{
		string strnew = "";
		bool flag = false;
		bool spare = false;

		for (int i = str.length() - 1; i >= 0; i--)
		{
			string x1 = "";
			x1 = str[i];

			int k = stoi(x1);
			char *x2 = new char[2];
			x2[1] = '\0';

			if (k == 5)
			{
				if (spare == true)
				{
					flag = true;
					strnew = '1' + strnew;
				}
				else
				{
					strnew = '0' + strnew;
				}

				if (i != 0)
				{
					spare = true;
				}
				else
				{
					strNhan2 = strNhan2 + '1';
				}

			}
			else if (k > 5)
			{
				flag = true;

				if (spare == true)
				{
					x2[0] = (char)(48 + 1 + ((int)(k * 2) % 10));

					strnew = string(x2) + strnew;
				}
				else
				{
					x2[0] = (char)(48 + ((int)(k * 2) % 10));

					strnew = string(x2) + strnew;
				}

				if (i != 0)
				{
					spare = true;
				}
				else
				{
					strNhan2 = strNhan2 + '1';
				}


			}
			else
			{
				flag = true;

				if (spare == true)
				{
					x2[0] = (char)(48 + 1 + ((int)(k * 2) % 10));

					strnew = string(x2) + strnew;
				}
				else
				{
					x2[0] = (char)(48 + ((int)(k * 2) % 10));

					strnew = string(x2) + strnew;
				}

				if (i != 0)
				{
					spare = false;
				}
				else
				{
					strNhan2 = strNhan2 + '0';

					if (numbers == 1)
					{
						numbers--;
					}
				}
			}

		}

		if (flag == true)
		{
			str = strnew;
			numbers++;
		}
		else
		{
			break;
		}
	}

	return strNhan2;
}



/*hàm nhập Qfloat với 2 kiểu: nhị phân hoặc thập phân*/
void ScanQfloat(Qfloat &x)
{
	string str = "", phanNguyen = "", phanKhongNguyen = "";
	int choose, Sign;
	int dataQfloat[128] = { 0 };
	cout << "Input 1: Nhap vao Qfloat kieu nhi phan\n";
	cout << "      2: Nhap vao Qfloat kieu thap phan\n";
	cout << "Choose: ";
	cin >> choose;
	cin.ignore();

	if (choose == 1)
	{
		getline(cin, str);
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '0')
			{
				dataQfloat[i] = 0;
			}
			else if (str[i] == '1')
			{
				dataQfloat[i] = 1;
			}
		}
		for (int j = str.length(); j < 128; j++)
		{
			dataQfloat[j] = 0;
		}
	}
	else if (choose == 2)
	{
		getline(cin, str);

		if (str[0] == '-')
		{
			Sign = 1;
			str = str.substr(1);
		}
		else
		{
			Sign = 0;
		}

		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] != '.')
			{
				phanNguyen = phanNguyen + str[i];
			}
			else
			{
				phanKhongNguyen = str.substr(i + 1); break;
			}
		}

		if (phanKhongNguyen.length() == 0)
		{
			phanKhongNguyen = "0";
		}

		phanNguyen = StrChia2(phanNguyen);
		phanKhongNguyen = StringNhan2(phanKhongNguyen);


		int Exponent = 0;
		for (int i = 0; i < phanNguyen.length(); i++)
		{
			if (phanNguyen[i] == '1')
			{
				Exponent = (phanNguyen.length() - i - 1); break;
			}
		}

		if (Exponent == 0)
		{
			for (int i = 0; i < phanKhongNguyen.length(); i++)
			{
				if (phanKhongNguyen[i] == '1')
				{
					Exponent = -(i + 1); break;
				}
			}
		}
		//cout << Exponent << endl;
		int E = Exponent + 16383;

		string phanMu = to_string(E);

		phanMu = StrChia2(phanMu);
		//cout << phanMu << endl;

		dataQfloat[0] = Sign;

		for (int i = phanMu.length() - 1; i >= 0; i--)
		{
			if (phanMu[i] == '0')
			{
				dataQfloat[15 - phanMu.length() + 1 + i] = 0;
			}
			else if (phanMu[i] == '1')
			{
				dataQfloat[15 - phanMu.length() + 1 + i] = 1;
			}
		}

		if (Exponent == 0)
		{
			for (int i = 0; i < 112; i++)
			{
				if (phanKhongNguyen[i] == '0')
				{
					dataQfloat[i + 16] = 0;
				}
				else if (phanKhongNguyen[i] == '1')
				{
					dataQfloat[i + 16] = 1;
				}
			}

			/*Làm tròn số*/
			if (phanKhongNguyen[112] == '1')
			{
				dataQfloat[127] = 1;
			}
		}
		else if (Exponent > 0)
		{
			for (int i = 0; i < Exponent; i++)
			{
				if (phanNguyen[phanNguyen.length() - Exponent + i] == '0')
				{
					dataQfloat[i + 16] = 0;
				}
				else if (phanNguyen[phanNguyen.length() - Exponent + i] == '1')
				{
					dataQfloat[i + 16] = 1;
				}
			}
			for (int j = 0; j < 112 - Exponent; j++)
			{
				if (phanKhongNguyen[j] == '0')
				{
					dataQfloat[j + 16 + Exponent] = 0;
				}
				else if (phanKhongNguyen[j] == '1')
				{
					dataQfloat[j + 16 + Exponent] = 1;
				}
			}

			/*Làm tròn số*/
			if (phanKhongNguyen[112 - Exponent] == '1')
			{
				dataQfloat[127] = 1;
			}
		}
		else
		{
			for (int k = 0; k < 112; k++)
			{
				if (phanKhongNguyen[abs(Exponent) + k] == '0')
				{
					dataQfloat[k + 16] = 0;
				}
				else if (phanKhongNguyen[abs(Exponent) + k] == '1')
				{
					dataQfloat[k + 16] = 1;
				}
			}


			/*Làm tròn số*/
			if (phanKhongNguyen[112 + abs(Exponent)] == '1')
			{
				dataQfloat[127] = 1;
			}
		}
	}
	else
	{
		cout << "Khong hop le.\n";
	}

	/*Bật và tắt bit tại vị trí i của X n bit*/
	for (int i = 0; i < 128; i++)
	{
		if (dataQfloat[i] == 0)  //Tắt bit
		{
			x.data[i / 32] = x.data[i / 32] & (~1 << (128 - 1 - i));
		}
		else if (dataQfloat[i] == 1)  //Bật bit
		{
			x.data[i / 32] = (1 << (128 - 1 - i)) | x.data[i / 32];
		}
	}
}


/*Cộng 2 chuỗi phần nguyên*/
string StrCongStr(string str1, string str2)
{
	string str = "";
	string x = "";

	int i = 0, s1, s2, S;
	bool spare = false;

	while (i < str1.length() || i < str2.length())
	{
		s1 = s2 = 0;

		if (i < str1.length())
		{
			x = str1[str1.length() - 1 - i];
			s1 = stoi(x);
		}

		if (i < str2.length())
		{
			x = str2[str2.length() - 1 - i];
			s2 = stoi(x);
		}

		if (spare == true)
		{
			S = s1 + s2 + 1;
		}
		else
		{
			S = s1 + s2;
		}

		char *x2 = new char[2];
		x2[1] = '\0';

		if (S >= 10)
		{
			x2[0] = (char)(48 + (int)(S % 10));
			str = string(x2) + str;

			spare = true;
		}
		else
		{
			x2[0] = (char)(48 + (int)(S % 10));
			str = string(x2) + str;

			spare = false;
		}
		i++;
	}

	if (spare == true)
	{
		str = "1" + str;
	}
	return str;
}



/*String nhân 2 Phan Nguyen*/
string StrNhan2PhanNguyen(string str)
{
	string strNhan2 = "";

	char *x1 = new char[2];
	x1[1] = '\0';
	bool flag = false;

	for (int i = str.length() - 1; i >= 0; i--)
	{
		string x = "";
		x = str[i];

		int k = stoi(x);

		if (k >= 5)
		{
			if (flag == true)
			{
				x1[0] = (char)(48 + 1 + (int)(2 * (k - 5)));
				strNhan2 = string(x1) + strNhan2;
			}
			else
			{
				x1[0] = (char)(48 + (int)(2 * (k - 5)));
				strNhan2 = string(x1) + strNhan2;
			}
			flag = true;
		}
		else
		{
			if (flag == true)
			{
				x1[0] = (char)(48 + 1 + (int)(2 * k));
				strNhan2 = string(x1) + strNhan2;
			}
			else
			{
				x1[0] = (char)(48 + (int)(2*k));
				strNhan2 = string(x1) + strNhan2;
			}
			flag = false;
		}
	}

	if (flag == true)
	{
		strNhan2 = '1' + strNhan2;
	}

	return strNhan2;
}

/*String nhân 2 phần không nguyên*/
string StrNhan2PhanKhongNguyen(string str)
{
	string strNhan2 = "";

	char *x1 = new char[2];
	x1[1] = '\0';
	int flag = 0;

	for (int i = str.length() - 1; i >= 0; i--)
	{
		string x = "";
		x = str[i];

		int k = stoi(x);

		x1[0] = (char)(48 + flag + (int)(5 * k) % 10);
		strNhan2 = string(x1) + strNhan2;

		flag = (int)(5 * k) / 10;

	}

	if (flag != 0)
	{
		x1[0] = (char)(48 + flag);
		strNhan2 = string(x1) + strNhan2;
	}


	return strNhan2;
}

/*Nhân bit nhị phân với 2^N phần nguyên*/
string Nhan2MuNPhanNguyen(int N)
{
	if (N == 0)
	{
		return "1";
	}

	string str = "2";

	for (int i = 1; i < N; i++)
	{
		str = StrNhan2PhanNguyen(str);
	}

	return str;
}

/*Nhân bit nhị phân với 2^N phân không nguyên*/
string Nhan2MuNPhanKhongNguyen(int N)
{
	if (N == 0)
	{
		return "0";
	}
	if (N == 1)
	{
		return "5";
	}
	string str = "5";
	int flag = 1, count = 0;

	for (int i = 2; i <= N; i++)
	{
		str = StrNhan2PhanKhongNguyen(str);

		flag++;
		if (flag == 0 || flag == 4 || flag == 7)
		{
			count++;
		}

		if (flag == 9)
		{
			flag = -1;
		}
	}

	for (int i = 1; i <= count; i++)
	{
		str = '0' + str;
	}

	return str;
}


/*Hàm chuyển đổi số Qfloat nhị phân sang thập phân*/
string BinToDec(Qfloat &x)
{
	string strDataQfloat = "";
	int dataQfloat[128];

	for (int i = 0; i < 128; i++)
	{
		dataQfloat[i] = (x.data[i / 32] >> (128 - 1 - i)) & 1;
	}

	if (dataQfloat[0] == 1)
	{
		strDataQfloat = strDataQfloat + '-';
	}

	int Exponent = 0;
	for (int i = 1; i < 16; i++)
	{
		Exponent = Exponent + dataQfloat[i] * pow(2, 15 - i);
	}

	int E = Exponent - 16383;

	string strPhanNguyen = "";
	string strPhanKhongNguyen = "";
	if (E == 0)
	{
		strPhanNguyen = strPhanNguyen + '1';
		for (int i = 16; i < 128; i++)
		{
			if (dataQfloat[i] == 0)
			{
				strPhanKhongNguyen = strPhanKhongNguyen + '0';
			}
			else if (dataQfloat[i] == 1)
			{
				strPhanKhongNguyen = strPhanKhongNguyen + '1';
			}
		}
	}
	else if (E < 0)
	{
		strPhanNguyen = strPhanNguyen + '0';

		for (int i = 1; i < abs(E); i++)
		{
			strPhanKhongNguyen = strPhanKhongNguyen + '0';
		}

		for (int j = 16; j < 128 - abs(E); j++)
		{
			if (dataQfloat[j] == 0)
			{
				strPhanKhongNguyen = strPhanKhongNguyen + '0';
			}
			else if (dataQfloat[j] == 1)
			{
				strPhanKhongNguyen = strPhanKhongNguyen + '1';
			}
		}
	}
	else
	{
		strPhanNguyen = strPhanNguyen + '1';
		for (int i = 16; i < E + 16; i++)
		{
			if (dataQfloat[i] == 0)
			{
				strPhanNguyen = strPhanNguyen + '0';
			}
			else if (dataQfloat[i] == 1)
			{
				strPhanNguyen = strPhanNguyen + '1';
			}
		}

		for (int j = E + 16; j < 128 - E; j++)
		{
			if (dataQfloat[j] == 0)
			{
				strPhanKhongNguyen = strPhanKhongNguyen + '0';
			}
			else if (dataQfloat[j] == 1)
			{
				strPhanKhongNguyen = strPhanKhongNguyen + '1';
			}
		}


		string str1 = "0";
		string str2 = "0";

		for (int i = 0; i < strPhanNguyen.length(); i++)
		{
			if (strPhanNguyen[i] == '1')
			{
				string s = Nhan2MuNPhanNguyen(strPhanNguyen.length() - i - 1);
				str1 = StrCongStr(str1, s);
			}
		}


		for (int i = 0; i < strPhanKhongNguyen.length(); i++)
		{
			if (strPhanKhongNguyen[i] == '1')
			{
				string s = Nhan2MuNPhanKhongNguyen(i + 1);

				if (str2.length() > s.length())
				{
					int size = str2.length() - s.length();

					for (int m = 1; m <= size; m++)
					{
						s = s + '0';
					}
				}
				else if (str2.length() < s.length())
				{
					int size = s.length() - str2.length();

					for (int n = 1; n <= size; n++)
					{
						str2 = str2 + '0';
					}
				}

				str2 = StrCongStr(str2, s);
			}
		}

		strDataQfloat = strDataQfloat + str1 + '.' + str2;

		return strDataQfloat;
	}
}

/*Hàm chuyển đổi số Qfloat thập phân sang nhị phân*/
Qfloat DecToBin(string x)
{
	Qfloat DataQfloat;
	string phanNguyen = "", phanKhongNguyen = "";
	int Sign;
	int dataQfloat[128] = { 0 };


	if (x[0] == '-')
	{
		Sign = 1;
		x = x.substr(1);
	}
	else
	{
		Sign = 0;
	}

	for (int i = 0; i < x.length(); i++)
	{
		if (x[i] != '.')
		{
			phanNguyen = phanNguyen + x[i];
		}
		else
		{
			phanKhongNguyen = x.substr(i + 1); break;
		}
	}

	if (phanKhongNguyen.length() == 0)
	{
		phanKhongNguyen = "0";
	}

	phanNguyen = StrChia2(phanNguyen);
	phanKhongNguyen = StringNhan2(phanKhongNguyen);


	int Exponent = 0;
	for (int i = 0; i < phanNguyen.length(); i++)
	{
		if (phanNguyen[i] == '1')
		{
			Exponent = (phanNguyen.length() - i - 1); break;
		}
	}

	if (Exponent == 0)
	{
		for (int i = 0; i < phanKhongNguyen.length(); i++)
		{
			if (phanKhongNguyen[i] == '1')
			{
				Exponent = -(i + 1); break;
			}
		}
	}
	//cout << Exponent << endl;
	int E = Exponent + 16383;

	string phanMu = to_string(E);

	phanMu = StrChia2(phanMu);
	//cout << phanMu << endl;

	dataQfloat[0] = Sign;

	for (int i = phanMu.length() - 1; i >= 0; i--)
	{
		if (phanMu[i] == '0')
		{
			dataQfloat[15 - phanMu.length() + 1 + i] = 0;
		}
		else if (phanMu[i] == '1')
		{
			dataQfloat[15 - phanMu.length() + 1 + i] = 1;
		}
	}

	if (Exponent == 0)
	{
		for (int i = 0; i < 112; i++)
		{
			if (phanKhongNguyen[i] == '0')
			{
				dataQfloat[i + 16] = 0;
			}
			else if (phanKhongNguyen[i] == '1')
			{
				dataQfloat[i + 16] = 1;
			}
		}

		/*Làm tròn số*/
		if (phanKhongNguyen[112] == '1')
		{
			dataQfloat[127] = 1;
		}
	}
	else if (Exponent > 0)
	{
		for (int i = 0; i < Exponent; i++)
		{
			if (phanNguyen[phanNguyen.length() - Exponent + i] == '0')
			{
				dataQfloat[i + 16] = 0;
			}
			else if (phanNguyen[phanNguyen.length() - Exponent + i] == '1')
			{
				dataQfloat[i + 16] = 1;
			}
		}
		for (int j = 0; j < 112 - Exponent; j++)
		{
			if (phanKhongNguyen[j] == '0')
			{
				dataQfloat[j + 16 + Exponent] = 0;
			}
			else if (phanKhongNguyen[j] == '1')
			{
				dataQfloat[j + 16 + Exponent] = 1;
			}
		}

		/*Làm tròn số*/
		if (phanKhongNguyen[112 - Exponent] == '1')
		{
			dataQfloat[127] = 1;
		}
	}
	else
	{
		for (int k = 0; k < 112; k++)
		{
			if (phanKhongNguyen[abs(Exponent) + k] == '0')
			{
				dataQfloat[k + 16] = 0;
			}
			else if (phanKhongNguyen[abs(Exponent) + k] == '1')
			{
				dataQfloat[k + 16] = 1;
			}
		}


		/*Làm tròn số*/
		if (phanKhongNguyen[112 + abs(Exponent)] == '1')
		{
			dataQfloat[127] = 1;
		}
	}

	/*Bật và tắt bit tại vị trí i của X n bit*/
	for (int i = 0; i < 128; i++)
	{
		if (dataQfloat[i] == 0)  //Tắt bit
		{
			DataQfloat.data[i / 32] = DataQfloat.data[i / 32] & (~1 << (128 - 1 - i));
		}
		else if (dataQfloat[i] == 1)  //Bật bit
		{
			DataQfloat.data[i / 32] = (1 << (128 - 1 - i)) | DataQfloat.data[i / 32];
		}
	}

	return DataQfloat;
}


void PrintQfloat(Qfloat x)
{
	cout << "He 10: ";
	cout << BinToDec(x) << endl;


	cout << "He 2: ";
	for (int i = 0; i < 128; i++)
	{
		int k = (x.data[i / 32] >> (128 - 1 - i)) & 1;
		cout << k;
	}
}

int main()
{
	Qfloat x;

	ScanQfloat(x);
	PrintQfloat(x);

	cout << endl;


	system("pause");
	return 0;
}