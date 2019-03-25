#include "TinhToan.h"


#define NEGATIVE 1
#define	POSITIVE 0

void taoQIntTemp(QIntTemp &ts, QIntTemp &src)
{
	for (int i = 0; i < 128; i++)
	{
		ts.array[i] = src.array[i];
	}
}
void taoQIntTemp(QIntTemp &ts, int * src, int n)
{
	Zero(ts);
	if (n < 128)
		for (int i = 0; i < n; i++)
		{
			ts.array[128 - n + i] = src[i];
		}
}

void autofill(QIntTemp &ts, string a)
{
	xoaychuoi(a);
	int n = a.length();
	if (n <= 128 && n != -1)
	{
		for (int i = 127; i >= 128 - n; i--)
		{
			ts.array[i] = a[128 - i - 1] - 48;
		}

		for (int i = 128 - n - 1; i >= 0; i--)
		{
			ts.array[i] = 0;
		}
	}
}
void autofill(QIntTemp &ts)
{
	int n = serialNum1(ts, 1);
	for (int i = 0; i < n; i++)
		ts.array[i] = 0;
}

void input(QIntTemp &ts)
{
	string a;
	cin >> a;
	autofill(ts, a);
}
void output(QIntTemp &ts)
{
	for (int i = 0; i < 128; i++)
	{
		cout << ts.array[i];
	}

}

int serialNum1(QIntTemp &ts, int n)
{
	int count = 0;
	for (int i = 0; i < 128; i++)
	{
		if (ts.array[i] == 1) count++;
		if (count == n)	return i;
	}
	return -1;
}

bool isNegative(QIntTemp &ts)
{
	if (ts.array[0] == 0) return false;
	return true;
}
void changeSign(QIntTemp &ts)
{
	if (ts.array[0] == 1) ts.array[0] = 0;
	else ts.array[0] = 1;
}
void changeSign(QIntTemp &ts, bool n)
{
	if (n) ts.array[0] = 1;
	else ts.array[0] = 0;
}

QIntTemp operator +(QIntTemp &ts, QIntTemp &src)
{
	QIntTemp a(ts), b(src);
	QIntTemp result;

	int remind = 0;
	for (int i = 127; i >= 0; i--)
	{
		if (a.array[i] + b.array[i] + remind == 0)
		{
			result.array[i] = 0;
			remind = 0;
		}
		else if (a.array[i] + b.array[i] + remind == 1)
		{
			result.array[i] = 1;
			remind = 0;
		}
		else if (a.array[i] + b.array[i] + remind == 2)
		{
			result.array[i] = 0;
			remind = 1;
		}
		else if (a.array[i] + b.array[i] + remind == 3)
		{
			result.array[i] = 1;
			remind = 1;
		}
	}
	autofill(result);
	return result;
}
QIntTemp operator -(QIntTemp &ts, QIntTemp &src)
{
	QIntTemp a(ts), b(src);
	QIntTemp result;

	bu2(b);
	result = a + b;

	//autofill(result);
	return result;
}
QIntTemp operator *(QIntTemp &ts, QIntTemp &src)
{
	QIntTemp M(ts), Q(src);
	QIntTemp result;
	bool remind;
	if (isNegative(M) == isNegative(Q)) remind = POSITIVE;
	else remind = NEGATIVE;

	changeSign(M, POSITIVE);
	changeSign(Q, POSITIVE);

	if (isZero(M) || isZero(Q))
	{
		Zero(M);
		return M;
	}

	int n = 128 - serialNum1(Q, 1);
	//if (n == 129) return result;

	result = Q;
	for (int i = 0; i < n; i++)
	{
		shiftLeft(M);
	}

	int k = n;
	while (k > 0)
	{
		if (result[127] == 1)
		{
			result = result + M;
		}

		shiftRight(result);
		k--;
	}
	changeSign(result, remind);
	return result;
}
QIntTemp operator /(QIntTemp &ts, QIntTemp &src)
{
	QIntTemp A, Q(ts), M(src), zero;

	Zero(zero);
	if (isZero(M) || isZero(Q) || M > Q)
	{
		return zero;
	}
	if (Q == M)
	{
		zero.array[127] = 1;
		return zero;
	}

	int k = 128 - serialNum1(Q, 1);
	int a0, Qn;
	Qn = serialNum1(Q, 1);

	if (Q > zero)
	{
		Zero(A);
	}
	if (Q < zero)
	{
		Zero(A);
		bu1(A);
	}


	while (k > 0)
	{
		//shift Left [A,Q]
		a0 = Q[Qn];
		shiftLeft(Q);
		Q.array[Qn - 1] = 0;
		shiftLeft(A);
		A.array[127] = a0;
		//A=A-M
		A = A - M;

		if (A < zero)
		{
			//Q0 = 0
			Q.array[127] = 0;
			A = A + M;
		}
		else
		{
			//Q0 = 1
			Q.array[127] = 1;
		}
		k--;
	}

	return Q;
}

QIntTemp operator &(QIntTemp &ts, QIntTemp &src)
{
	QIntTemp r;
	Zero(r);
	for (int i = 0; i < 128; i++)
	{
		if (ts[i] == 1 && src[i] == 1)
			r[i] = 1;
		else r[i] = 0;
	}
	return r;
}
QIntTemp operator |(QIntTemp &ts, QIntTemp &src)
{
	QIntTemp r;
	Zero(r);
	for (int i = 0; i < 128; i++)
	{
		if (ts[i] == 1 || src[i] == 1)
			r[i] = 1;
		else r[i] = 0;
	}
	return r;
}
QIntTemp operator ^(QIntTemp &ts, QIntTemp &src)
{
	QIntTemp r;
	Zero(r);
	for (int i = 0; i < 128; i++)
	{
		if (ts[i] == src[i])
			r[i] = 0;
		else r[i] = 1;
	}
	return r;
}

QIntTemp NOT(QIntTemp &ts)
{
	QIntTemp r;
	Zero(r);
	for (int i = 0; i < 128; i++)
	{
		if (ts[i] == 1)
			r[i] = 0;
		else r[i] = 1;
	}
	return r;
}

void shiftRight(QIntTemp &ts)
{
	for (int i = 127; i > 0; i--)
	{
		ts.array[i] = ts.array[i - 1];
	}
	ts.array[0] = 0;
}
void shiftLeft(QIntTemp &ts)
{
	for (int i = 0; i < 127; i++)
	{
		ts.array[i] = ts.array[i + 1];
	}
	ts.array[127] = 0;
}
void rotateLeft(QIntTemp &ts)
{
	int temp = ts.array[0];
	for (int i = 0; i < 127; i++)
	{
		ts.array[i] = ts.array[i + 1];
	}
	ts.array[127] = temp;
}
void rotateRight(QIntTemp &ts)
{
	int temp = ts.array[127];
	for (int i = 127; i > 0; i--)
	{
		ts.array[i] = ts.array[i - 1];
	}
	ts.array[0] = temp;
}

void shiftRight(QIntTemp &ts, int n)
{
	n = n % 128;
	if (n == 0) return;
	//	if (n > 128/2) n = 128 - n;
	for (int i = n; i < 127; i++)
	{
		ts.array[i] = ts.array[i + n];
	}
	for (int i = 0; i < n; i++)
	{
		ts.array[i] = 0;
	}
}
void shiftLeft(QIntTemp &ts, int n)
{
	n = n % 128;
	if (n == 0) return;

	for (int i = n; i < 127; i++)
	{
		ts.array[i] = ts.array[i + n];
	}
	for (int i = 128 - n; i < 128; i++)
	{
		ts.array[i] = 0;
	}

}
void rotateLeft(QIntTemp &ts, int n)
{
	int* temp = new int[n];
	for (int i = 0; i < n; i++)
	{
		temp[i] = ts.array[i];
	}

	for (int i = 0; i < 128 - n; i++)
	{
		ts.array[i] = ts.array[i + n];
	}
	for (int i = 0; i < n; i++)
	{
		ts.array[128 + i - n] = temp[i];
	}
	delete[] temp;
}
void rotateRight(QIntTemp &ts, int n)
{
	int* temp = new int[n];
	for (int i = 0; i < n; i++)
	{
		temp[i] = ts.array[128 - i - n];
	}
	for (int i = 127; i >= n; i--)
	{
		ts.array[i] = ts.array[i - n];
	}
	for (int i = 0; i < n; i++)
	{
		ts.array[i] = temp[i];
	}
	delete[] temp;
}

bool operator ==(QIntTemp &ts, QIntTemp &src)
{
	for (int i = 0; i < 128; i++)
	{
		if (ts.array[i] != src.array[i]) return false;
	}
	return true;
}
bool operator <(QIntTemp &ts, QIntTemp &src)
{
	QIntTemp temp1(ts), temp2(src);
	if (isZero(temp1))
		changeSign(temp1, POSITIVE);
	if (isZero(temp2))
		changeSign(temp2, POSITIVE);

	if (ts.array[0] == 0 && src.array[0] == 0)
	{
		for (int i = 0; i < 128; i++)
		{
			if (temp1.array[i] < temp2.array[i] && temp1.array[i] != temp2.array[i])
				return true;
			if (temp1.array[i] > temp2.array[i] && temp1.array[i] != temp2.array[i])
				return false;
		}
	}
	if (ts.array[0] == 0 && src.array[0] == 0)
	{
		bu2(temp2); bu2(temp1);
		for (int i = 0; i < 128; i++)
		{
			if (temp1.array[i] < temp2.array[i] && temp1.array[i] != temp2.array[i])
				return false;
			if (temp1.array[i] > temp2.array[i] && temp1.array[i] != temp2.array[i])
				return true;

		}
	}
	if (ts.array[0] == 0)
		return false;
	if (src.array[0] == 0)
		return true;
	return false;
}
bool operator >(QIntTemp &ts, QIntTemp &src)
{
	return !(ts <= src);
}
bool operator <=(QIntTemp &ts, QIntTemp &src)
{
	return (ts < src || ts == src);
}
bool operator >=(QIntTemp &ts, QIntTemp &src)
{
	return !(ts < src);
}
bool operator !=(QIntTemp &ts, QIntTemp &src)
{
	return !(ts == src);
}

bool isZero(QIntTemp &ts)
{
	QIntTemp zero;
	Zero(zero);
	if (zero == ts) {
		return true;
	}
	return false;
}
void Zero(QIntTemp &ts)
{
	for (int i = 0; i < 128; i++)
	{
		ts.array[i] = 0;
	}
}

void xoaychuoi(string &a)
{
	int n = a.length();
	char temp;
	for (int i = 0; i < n / 2; i++)
	{
		temp = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = temp;
	}
}
void bu2(QIntTemp &ts)
{
	QIntTemp one;
	autofill(one, "1");
	for (int i = 0; i < 128; i++)
	{
		if (ts.array[i] == 0) ts.array[i] = 1;
		else ts.array[i] = 0;
	}
	ts = ts + one;
}
void bu1(QIntTemp &ts)
{
	for (int i = 0; i < 128; i++)
	{
		if (ts.array[i] == 0) ts.array[i] = 1;
		else ts.array[i] = 0;
	}
}
string outString(QIntTemp &ts)
{
	string result;
	for (int i = 0; i < 128; i++)
	{
		result.push_back(ts.array[i] + 48);
	}
	return result;
}
