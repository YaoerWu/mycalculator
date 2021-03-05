#include "numlib.h"
#include <math.h>
using numlib::fraction;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using std::string;

numlib::fraction::fraction()
{
	up = 0;
	down = 1;
	return;
}
numlib::fraction::fraction(int up)
{
	this->up = up;
	this->down = 1;
	return;
}
numlib::fraction::fraction(long long up)
{
	this->up = up;
	this->down = 1;
	return;
}
numlib::fraction::fraction(long long up, long long down)
{
	if (down == 0)
	{
		throw invalid_argument("��ĸ����Ϊ0");
		return;
	}
	else
	{
		long long k = _gcd(up, down);
		this->up = up / k;
		this->down = down / k;
		return;
	}
}
numlib::fraction::fraction(string num)
{
	int dot = 0;
	int slash = 0;
	size_t spilt = 0;
	switch (num[0]) //�жϵ�һ���ַ��Ƿ�Ϊ���ֻ����
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
	case '-':
	case '+':
		break;
	default:
		throw invalid_argument("�Ƿ�����");
	}
	for (size_t i = 1; i < num.length(); i++) //�жϺ����ַ�
	{
		switch (num[i])
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
			break;
		case '.':
			dot++;
			spilt = i;
			break;
		case '/':
			slash++;
			spilt = i;
			break;
		default:
			throw invalid_argument("�Ƿ�����");
		}
	}
	if (dot == 0 && slash == 1)
	{
		*this = fraction(_toInt(num.substr(0, spilt)), _toInt(num.substr(size_t(spilt) + 1)));
		return;
	}
	else if (dot == 1 && slash == 0)
	{
		long long numerator = _toInt(num.erase(spilt, 1));
		long long denominator = pow(10, (num.length() - spilt));
		*this = fraction(numerator, denominator);
		return;
	}
	else if (dot == 0 && slash == 0)
	{
		*this = fraction(_toInt(num));
		return;
	}
	else
	{
		throw invalid_argument("�Ƿ�����");
		return;
	}
}
fraction numlib::fraction::getInverse()
{
	fraction fra;
	long long tem = up;
	fra.up = down;
	fra.down = tem;
	return fra;
}

long long numlib::fraction::getNum()
{
	return this->up;
}
long long numlib::fraction::getDen()
{
	return this->down;
}

bool numlib::fraction::isInt()
{
	return this->down == 1;
}

/*fraction numlib::fraction::pow(const fraction& opt, const long long& index)
{
	fraction powed;
	powed.up = long long::pow(opt.up, index);
	return powed;
}*/

fraction numlib::fraction::operator-()
{
	return fraction(-this->up, this->down);
}
void numlib::fraction::operator=(const fraction &num)

{
	this->up = num.up;
	this->down = num.down;
}
fraction numlib::operator+(const fraction &left_i, const fraction &right_i)
{
	fraction left = left_i, right = right_i;
	long long up = (left.up * right.down + right.up * left.down);
	long long down = (left.down * right.down);
	return fraction(up, down);
}
fraction numlib::operator-(const fraction &left_i, const fraction &right_i)
{
	fraction left = left_i, right = right_i;
	return left + (-right);
}
fraction numlib::operator*(const fraction &left_i, const fraction &right_i)
{
	fraction left = left_i, right = right_i;
	fraction fra(left.up * right.up, left.down * right.down);
	return fra;
}
fraction numlib::operator/(const fraction &left_i, const fraction &right_i)
{
	fraction left = left_i, right = right_i;
	return left * right.getInverse();
}
bool numlib::operator==(const fraction &left, const fraction &right)
{
	return (left.up == right.up) && (left.down == right.down);
}
bool numlib::operator!=(const fraction &left, const fraction &right)
{
	return (left.up != right.up) || (left.down != right.down);
}
bool numlib::operator<(const fraction &left, const fraction &right)
{
	fraction tem = left - right;
	return tem.up < 0;
}
bool numlib::operator<=(const fraction &left, const fraction &right)
{
	return (left < right) || (left == right);
}
bool numlib::operator>(const fraction &left, const fraction &right)
{
	return right < left;
}
bool numlib::operator>=(const fraction &left, const fraction &right)
{
	return (left > right) || (left == right);
}

long long numlib::fraction::_gcd(long long m, long long n)
{
	if (m < 0)
	{
		m = -m;
	}
	if (n < 0)
	{
		n = -n;
	}
	long long c;
	while (m > 0)
	{
		c = n % m;
		n = m;
		m = c;
	}
	return n;
}
long long numlib::fraction::_toInt(string opt)
{
	std::istringstream mid(opt);
	long long out;
	mid >> out;
	return out;
}