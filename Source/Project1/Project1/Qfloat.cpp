#include "Qfloat.h"



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
		x1 = str[str.length() - 1];  //Kiểm tra chữ số cuối cùng xem số hiện tại là số lẻ hay số chẳn để gán '1' hay '0'

		if (stoi(x1) % 2 == 0)  //Nếu chữ số cuối cùng là chẳn thì gán '0'
		{
			strChia2 = '0' + strChia2;
		}
		else  //Ngược lại thì gán '0'
		{
			strChia2 = '1' + strChia2;
		}

		/*Thực hiện phép chia 2*/
		for (int i = 0; i < str.length(); i++)
		{
			if (i == (str.length() - 1) && flag == true)  //Nếu số đã xét hết từng chữ và không còn số dư thì break
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

		str = strnew;  //Gán số mới cho str
	}

	return strChia2;
}

/*Chuyển từ chuỗi số thập phân phần không nguyên sang nhị phân bằng cách nhân 2*/
string StrNhan2(string str)
{
	if (str.length() == 1 && str[0] == '0')  //Nếu phần không nguyên = 0 thì ta gán nó 1 chuỗi bit '0'
	{
		return "0";
	}

	string strNhan2 = "";  //Chuỗi nhị phân phần không nguyên

	int numbers = 1;  //Kiểm tra để thuận tiện cho việc dời vị trí khi chuyển sang dạng chuẩn hoán không bị thiếu bit
	while (numbers <= 114)
	{
		string strnew = "";  //Chuỗi mới sang khi nhân
		bool flag = false;  //Kiểm tra dư 1
		bool spare = false;  //Kiểm tra xem số sau khi nhân 2 có lơn hơn 1 hay không để gán '1' hay '0'

		for (int i = str.length() - 1; i >= 0; i--)
		{
			string x1 = "";
			x1 = str[i];  //Lấy phần tử thứ i để kiểm tra

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

		if (flag == true)  //Kiểm tra xem có còn dư 1 hay không
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


/*Cộng 2 chuỗi dạng thập phân(cả phần nguyên và phần không nguyên)*/
string StrCongStr(string str1, string str2)
{
	string str = "";  //Chuỗi sau khi cộng
	string x = "";

	int i = 0, s1, s2, S;
	bool spare = false;  //Kiểm tra dư 1

	/*Thực hiện phép cộng*/
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

	if (spare == true)  //Nếu có dư 1 ta cộng thêm '1' phía trước chuỗi
	{
		str = "1" + str;
	}

	return str;
}


/*Chuỗi thập phân nhân 2(phần nguyên)*/
string StrDecNhan2PhanNguyen(string str)
{
	string strNhan2 = "";  //Chuỗi thập phân sau khi nhân chuỗi nhị phân cho 2

	char *x1 = new char[2];
	x1[1] = '\0';
	bool flag = false;  //Kiểm tra phần dư

	/*Thực hiện phép nhân*/
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
				x1[0] = (char)(48 + (int)(2 * k));
				strNhan2 = string(x1) + strNhan2;
			}
			flag = false;
		}
	}

	if (flag == true)  //Nếu phần dư còn nhớ thì thêm '1' trước strNhan2
	{
		strNhan2 = '1' + strNhan2;
	}

	return strNhan2;
}

/*Chuỗi thập phân nhân 2(phần không nguyên)*/
string StrDecNhan2PhanKhongNguyen(string str)
{
	string strNhan2 = "";  //Chuỗi thập phân sau khi nhân chuỗi nhị phân cho 2

	char *x1 = new char[2];
	x1[1] = '\0';
	int flag = 0;

	/*Thực hiện phép nhân*/
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

/*Nhân bit nhị phân với 2^N(phần nguyên)*/
string BinNhan2MuNPhanNguyen(int N)
{
	if (N == 0)  //Nếu N = 0 thì return '1'
	{
		return "1";
	}

	string str = "2";

	/*Vong lặp for với mục đích thực hiện 2^N*/
	for (int i = 1; i < N; i++)
	{
		str = StrDecNhan2PhanNguyen(str);
	}

	return str;
}

/*Nhân bit nhị phân với 2^N(phần không nguyên)*/
string BinNhan2MuNPhanKhongNguyen(int N)
{
	if (N == 0)  //Nếu N = 0 thì return '0'
	{
		return "0";
	}
	if (N == 1)  //Nếu N = 1 thì return '5'
	{
		return "5";
	}
	string str = "5";
	int flag = 1, count = 0;

	/*Vì phần không nguyên nên thay vì thực hiện 1 chia 2 N lần thì ta thực hiện phép nhân 5 N lần và thêm phần tử '0' vào trước số count lần khi N càng âm(abs(N) càng lớn)*/
	for (int i = 2; i <= N; i++)
	{
		str = StrDecNhan2PhanKhongNguyen(str);  //Thực hiện phép nhân(phần không nguyên)

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

	/*Thêm count phần tử '0' vào trước str khi N càng âm (abs(N) càng lớn)*/
	for (int i = 1; i <= count; i++)
	{
		str = '0' + str;
	}

	return str;
}


/*Hàm chuyển đổi số dạng Qfloat nhị phân sang dạng chuỗi thập phân*/
string BinToDec(Qfloat &x)
{
	string strDataQfloat = "";  //Chuỗi thập phân
	int dataQfloat[128];

	for (int i = 0; i < 128; i++)
	{
		dataQfloat[i] = (x.data[i / 32] >> (128 - 1 - i)) & 1;  //Đọc bit
	}

	int count = 0;
	for (int i = 0; i < 128; i++)
	{
		if (dataQfloat[i] == 0)
		{
			count++;
		}
	}
	if (count == 128)
	{
		return "0.0";
	}

	if (dataQfloat[0] == 1)  //Nếu bit đầu tiên là 1 thì là số âm. Ngược lại là số dương
	{
		strDataQfloat = strDataQfloat + '-';
	}

	int Exponent = 0;
	for (int i = 1; i < 16; i++)
	{
		Exponent = Exponent + dataQfloat[i] * pow(2, 15 - i);
	}

	int E = Exponent - 16383;

	string strPhanNguyen = "";  //Chuỗi chứa phần nguyên dạng nhị phân
	string strPhanKhongNguyen = "";  //Chuỗi chứa dạng phần không nguyên dạng nhị phân

	/*Chuyển từ kiểu qfloat dạng nhị phân sang chuỗi dạng nhị phân*/
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
	else if (E > 0)
	{
		if (E == 112)
		{
			strPhanNguyen = strPhanNguyen + '1';
			for (int i = 16; i < 128; i++)
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

			strPhanKhongNguyen = "0";
		}
		else if (E > 112)
		{
			strPhanNguyen = strPhanNguyen + '1';
			for (int i = 16; i < 128; i++)
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

			for (int j = 1; j <= E - 112; j++)
			{
				strPhanNguyen = strPhanNguyen + '0';//
			}

			strPhanKhongNguyen = "0";
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

			for (int j = E + 16; j < 112; j++)
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
	}
	else
	{
		strPhanNguyen = strPhanNguyen + '0';

		for (int i = 1; i < abs(E); i++)
		{
			strPhanKhongNguyen = strPhanKhongNguyen + '0';
		}

		strPhanKhongNguyen = strPhanKhongNguyen + '1';

		for (int j = 16; j < 128; j++)
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

	string str1 = "0";  //Chứa phần nguyên dạng thập phân
	string str2 = "0";  //Chứa phần không nguyên dạng thập phân

	for (int i = 0; i < strPhanNguyen.length(); i++)
	{
		if (strPhanNguyen[i] == '1')
		{
			string s = BinNhan2MuNPhanNguyen(strPhanNguyen.length() - i - 1);
			str1 = StrCongStr(str1, s);
		}
	}


	for (int i = 0; i < strPhanKhongNguyen.length(); i++)
	{
		if (strPhanKhongNguyen[i] == '1')
		{
			string s = BinNhan2MuNPhanKhongNguyen(i + 1);

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

	/*Kết nối lại: phần nguyên + '.' + phần không nguyên*/
	strDataQfloat = strDataQfloat + str1 + '.' + str2;

	return strDataQfloat;
}

/*Hàm chuyển đổi từ chuỗi dạng thập phân sang Qfloat dạng nhị phân*/
Qfloat DecToBin(string x)
{
	Qfloat DataQfloat;
	string phanNguyen = "", phanKhongNguyen = "";
	int Sign;
	int dataQfloat[128] = { 0 };

	/*Xét TRƯỜNG HỢP ĐẶC BIỆT x = "0" hay x = "0.0"*/
	if (x.length() == 1)
	{
		if (x[0] == '0')
		{
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
	}

	if (x.length() == 3)
	{
		if (x[0] == '0'&&x[1] == '.'&&x[2] == '0')
		{
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
	}

	if (x[0] == '-')  //Kiểm tra vị trí đầu tiên là âm hay dương
	{
		Sign = 1;
		x = x.substr(1);
	}
	else
	{
		Sign = 0;
	}

	/*Phân tách phần dương và phần âm của số dạng thập phân*/
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

	if (phanKhongNguyen.length() == 0)  //Nếu số dạng thập phân là số nguyên(không có phần không nguyên) thì ta gán phần không nguyên = '0'
	{
		phanKhongNguyen = "0";
	}

	phanNguyen = StrChia2(phanNguyen);  //Chuyển sang dạng nhị phân
	phanKhongNguyen = StrNhan2(phanKhongNguyen);  //Chuyển sang dạng nhị phân


	int E = 0;

	/*Tìm vị trí để chuyển hóa về dạng dấu chấm động*/
	for (int i = 0; i < phanNguyen.length(); i++)
	{
		if (phanNguyen[i] == '1')
		{
			E = (phanNguyen.length() - i - 1); break;
		}
	}

	if (E == 0)
	{
		for (int i = 0; i < phanKhongNguyen.length(); i++)
		{
			if (phanKhongNguyen[i] == '1')
			{
				E = -(i + 1); break;
			}
		}
	}

	if (phanNguyen.length() == 1 && phanNguyen[0] == '1')
	{
		E = 0;
	}


	//cout << Exponent << endl;
	int Exponent = E + 16383;  //Số mũ E

	string phanMu = to_string(Exponent);  //Chuyển số mũ từ dạng int sang dạng string

	phanMu = StrChia2(phanMu);  //Chuyển số mũ từ dạng chuỗi số nguyên sang dạng nhị phân
	//cout << phanMu << endl;

	dataQfloat[0] = Sign;  //Gán dấu

	/*Gán phần mũ*/
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

	/*Xét và Gán phần định trị*/
	if (E == 0)
	{
		if (phanKhongNguyen.length() == 112)
		{
			for (int i = 0; i < phanKhongNguyen.length(); i++)
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
		}
		else if (phanKhongNguyen.length() > 112)
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
		else
		{
			for (int i = 0; i < phanKhongNguyen.length(); i++)
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

			for (int j = 0; j < 112 - phanKhongNguyen.length(); j++)
			{
				dataQfloat[phanKhongNguyen.length() + j + 16] = 0;
			}
		}
	}
	else if (E > 0)
	{
		if ((phanNguyen.length() - 1) == 112)
		{
			for (int i = 1; i < phanNguyen.length(); i++)
			{
				if (phanNguyen[i] == '0')
				{
					dataQfloat[i + 16 - 1] = 0;
				}
				else if (phanNguyen[i] == '1')
				{
					dataQfloat[i + 16 - 1] = 1;
				}
			}
		}
		else if ((phanNguyen.length() - 1) > 112)
		{
			for (int i = 1; i < 113; i++)
			{
				if (phanNguyen[i] == '0')
				{
					dataQfloat[i + 16 - 1] = 0;
				}
				else if (phanNguyen[i] == '1')
				{
					dataQfloat[i + 16 - 1] = 0;
				}
			}
		}
		else
		{
			for (int i = 1; i < phanNguyen.length(); i++)
			{
				if (phanNguyen[i] == '0')
				{
					dataQfloat[i + 16 - 1] = 0;
				}
				else if (phanNguyen[i] == '1')
				{
					dataQfloat[i + 16 - 1] = 1;
				}
			}

			int k = phanNguyen.length() - 1;
			if (phanKhongNguyen.length() == (112 - k))
			{
				for (int i = 0; i < phanKhongNguyen.length(); i++)
				{
					if (phanKhongNguyen[i] == '0')
					{
						dataQfloat[k + 16 + i] = 0;
					}
					else if (phanKhongNguyen[i] == '1')
					{
						dataQfloat[k + 16 + i] = 1;
					}
				}
			}
			else if (phanKhongNguyen.length() > (112 - k))
			{
				for (int i = 0; i < 112 - k; i++)
				{
					if (phanKhongNguyen[i] == '0')
					{
						dataQfloat[k + 16 + i] = 0;
					}
					else if (phanKhongNguyen[i] == '1')
					{
						dataQfloat[k + 16 + i] = 1;
					}
				}

				/*Làm tròn số*/
				if (phanKhongNguyen[112 - k] == '1')
				{
					dataQfloat[127] = 1;
				}
			}
			else
			{
				for (int i = 0; i < phanKhongNguyen.length(); i++)
				{
					if (phanKhongNguyen[i] == '0')
					{
						dataQfloat[k + 16 + i] = 0;
					}
					else if (phanKhongNguyen[i] == '1')
					{
						dataQfloat[k + 16 + i] = 1;
					}
				}

				//dataQfloat đã khởi tao dataQfloat[128] = {0} nên không cần gán giá trị 0 cho phần còn lại
			}
		}
	}
	else
	{
		if ((phanKhongNguyen.length() - abs(E)) == 112)
		{
			for (int i = 0; i < 112; i++)
			{
				if (phanKhongNguyen[abs(E) + i] == '0')
				{
					dataQfloat[i + 16] = 0;
				}
				else if (phanKhongNguyen[abs(E) + i] == '1')
				{
					dataQfloat[i + 16] = 1;
				}
			}
		}
		else if ((phanKhongNguyen.length() - abs(E)) > 112)
		{
			for (int i = 0; i < 112; i++)
			{
				if (phanKhongNguyen[abs(E) + i] == '0')
				{
					dataQfloat[i + 16] = 0;
				}
				else if (phanKhongNguyen[abs(E) + i] == '1')
				{
					dataQfloat[i + 16] = 1;
				}
			}

			/*Làm tròn số*/
			if (phanKhongNguyen[112 + abs(E)] == '1')
			{
				dataQfloat[127] = 1;
			}
		}
		else
		{
			for (int i = 0; i < phanKhongNguyen.length(); i++)
			{
				if (phanKhongNguyen[abs(E) + i] == '0')
				{
					dataQfloat[i + 16] = 0;
				}
				else if (phanKhongNguyen[abs(E) + i] == '1')
				{
					dataQfloat[i + 16] = 1;
				}
			}

			//dataQfloat đã khởi tao dataQfloat[128] = {0} nên không cần gán giá trị 0 cho phần còn lại
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

/*Hàm nhập Qfloat với kiểu nhập vào là chuỗi dạng thập phân và lưu dưới dạng nhị phân kiểu Qfloat*/
void ScanQfloat(Qfloat &x)
{
	string str = "";
	cout << "Nhap vao so dau cham dong lon: ";
	getline(cin, str);

	cout << "He 10: ";
	cout << str << endl;

	x = DecToBin(str);  //Chuyển từ chuỗi thập phân sang Qfloat nhị phân
}


/*Xuất Qfloat ra màn hình*/
void PrintQfloat(Qfloat x)
{
	//cout << "He 10: ";
	//cout << BinToDec(x) << endl;


	cout << "He 2: ";
	for (int i = 0; i < 128; i++)
	{
		int k = (x.data[i / 32] >> (128 - 1 - i)) & 1;
		cout << k;
	}
}