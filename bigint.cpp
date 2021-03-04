#include "numlib.h"
using numlib::bigint;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::vector;

numlib::bigint::bigint()
{
	number.push_back(0);
	notation = 1;
}
numlib::bigint::bigint(int num)
{
	*this = bigint((long long)num);
}
numlib::bigint::bigint(size_t num)
{
	notation = 1;
	if (num == 0)
	{
		number.push_back(0);
		notation = 1;
		return;
	}
	string str;
	ostringstream in;
	in << num;
	str = in.str();
	string::iterator i;
	for (i = str.begin(); i != str.end(); i++)
	{
		number.push_back(int(*i - '0'));
	}
	return;
}
numlib::bigint::bigint(long long num)
{
	notation = 1;
	if (num == 0)
	{
		number.push_back(0);
		notation = 1;
		return;
	}
	if (num > 0)
	{
		notation = 1;
	}
	else if (num < 0)
	{
		notation = -1;
		num = -num;
	}
	string str;
	ostringstream in;
	in << num;
	str = in.str();
	string::iterator i;
	for (i = str.begin(); i != str.end(); i++)
	{
		number.push_back(int(*i - '0'));
	}
	return;
}
numlib::bigint::bigint(const string& num)
{
	string tem = num;
	notation = 1;
	switch (tem[0]) //判断第一个字符是否为数字或符号
	{
	case '-':
		notation = -1;
	case '+':
		break;
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
		number.push_back(int(tem[0] - '0'));
		break;
	default:
		throw invalid_argument("非法输入");
	}
	string::iterator i;
	for (i = ++tem.begin(); i != tem.end(); i++) //判断后续字符
	{
		switch (*i)
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
			number.push_back(int(*i - '0'));
			break;
		default:
			throw invalid_argument("非法输入");
		}
	}
}

inline size_t numlib::bigint::getDigits()
{
	return number.size();
}
bigint numlib::bigint::getInverse()
{
	bigint tem = *this;
	tem.notation = tem.notation * -1;
	return tem;
}
string numlib::bigint::toString()
{
	string out;
	char figure;
	vector<int>::iterator i;
	for (i = number.begin(); i != number.end(); i++)
	{
		figure = *i + '0';
		out.append(1, figure);
	}
	return out;
}

bigint numlib::bigint::pow(const bigint& opt, const bigint& index)
{
	bigint powed = 1;
	for (bigint i = 0; i < index; i++)
	{
		powed = powed * opt;
	}
	return powed;
}

bigint numlib::bigint::operator-()
{
	return this->getInverse();
}
void numlib::bigint::operator=(const bigint& num)
{
	this->number = num.number;
	this->notation = num.notation;
}
bigint numlib::bigint::operator++()
{
	*this = *this + 1;
	return *this;
}
bigint numlib::bigint::operator++(int num)
{
	bigint tem = *this;
	*this = *this + 1;
	return tem;
}
bigint numlib::bigint::operator--()
{
	*this = *this - 1;
	return *this;
}
bigint numlib::bigint::operator--(int num)
{
	bigint tem = *this;
	*this = *this - 1;
	return tem;
}
bigint numlib::operator+(const bigint& left_i, const bigint& right_i)
{
	bigint left = left_i, right = right_i;
	if (left.notation == right.notation)
	{
		return bigint::_add(left, right);
	}
	else
	{
		return bigint::_subtract(left, right);
	}
}
bigint numlib::operator-(const bigint& left_i, const bigint& right_i)
{
	bigint left = left_i, right = right_i;
	if (left.notation != right.notation)
	{
		return bigint::_add(left, right);
	}
	else
	{
		return bigint::_subtract(left, right);
	}
}
bigint numlib::operator*(const bigint& left_i, const bigint& right_i)
{
	bigint left = left_i, right = right_i;
	return bigint::_multiplie(left, right);
}
bigint numlib::operator/(const bigint& left_i, const bigint& right_i)
{
	bigint left = left_i, right = right_i, quotient, remainder;
	bigint::_divide(left, right, quotient, remainder);
	return quotient;
}
bigint numlib::operator%(const bigint& left_i, const bigint& right_i)
{
	bigint left = left_i, right = right_i, quotient, remainder;
	bigint::_divide(left, right, quotient, remainder);
	return remainder;
}
bool numlib::operator==(const bigint& left, const bigint& right)
{
	return (left.number == right.number) && (left.notation == right.notation);
}
bool numlib::operator!=(const bigint& left, const bigint& right)
{
	return (left.number != right.number) || (left.notation != right.notation);
}
bool numlib::operator<(const bigint& left, const bigint& right)
{
	if ((left.number == right.number) && (left.notation == right.notation))
	{
		return false;
	}
	return (*(left - right).number.begin() * (left - right).notation) < 0;
}
bool numlib::operator<=(const bigint& left, const bigint& right)
{
	return (left < right) || (left == right);
}
bool numlib::operator>(const bigint& left, const bigint& right)
{
	return right < left;
}
bool numlib::operator>=(const bigint& left, const bigint& right)
{
	return (left > right) || (left == right);
}

bigint numlib::bigint::_add(bigint& left, bigint& right)
{
	bigint added;
	size_t len = 0;
	if (left.getDigits() > right.getDigits())
	{
		len = left.getDigits() + 1;
	}
	else
	{
		len = right.getDigits() + 1;
	}
	_reserve(left, len);
	_reserve(right, len);
	_reserve(added, len);
	int carrying = 0;
	vector<int>::reverse_iterator i, j, k;
	for (i = left.number.rbegin(), j = right.number.rbegin(), k = added.number.rbegin(); i != left.number.rend(), j != right.number.rend(); i++, j++, k++)
	{
		*k = ((*i + *j + carrying) % 10);
		carrying = (*i + *j + carrying) / 10;
	}
	added.notation = left.notation;
	return added._regularize();
}
bigint numlib::bigint::_subtract(bigint& left, bigint& right)
{
	if ((right == 0) || (right.getInverse() == 0))
	{
		return left;
	}
	bigint subtracted;
	_sizeFix(left, right);
	bigint right_com = _toComplement(right);
	subtracted = _add(left, right_com);
	if (subtracted.getDigits() > right.getDigits())
	{
		subtracted.number.erase(subtracted.number.begin());
		subtracted.notation = 1;
	}
	else
	{
		subtracted = _toComplement(subtracted);
		subtracted.notation = -1;
	}
	return subtracted._regularize();
}
bigint numlib::bigint::_multiplie(bigint& left, bigint& right)
{
	_sizeFix(left, right);
	bigint multiplied, tem;
	vector<int>::reverse_iterator i, j;
	vector<bigint> toAdd;
	vector<bigint>::iterator k;
	size_t n = 0, m = 0;
	for (i = left.number.rbegin(), m = 0; i != left.number.rend(); i++, m++)
	{
		for (j = right.number.rbegin(), n = m; j != right.number.rend(); j++, n++)
		{
			tem = bigint(*i * *j)._leftShift(n);
			toAdd.push_back(tem);
		}
	}
	for (k = toAdd.begin(); k != toAdd.end(); k++)
	{
		multiplied = multiplied + *k;
	}
	multiplied.notation = left.notation * right.notation;
	return multiplied;
}
void numlib::bigint::_divide(bigint& left, bigint& right, bigint& quotient, bigint& remainder)
{
	quotient = 0, remainder = 0;
	int notation = left.notation * right.notation;
	if (left < 0)
	{
		left = -left;
	}
	if (right < 0)
	{
		right = -right;
	}
	for (size_t i = 0; right <= left; i++)
	{
		left = left - right;
		quotient++;
	}
	quotient.notation = notation;
	remainder = left;
	remainder.notation = notation;
	return;
}

void numlib::bigint::_reserve(bigint& opt, size_t length)
{
	if (opt.getDigits() >= length)
	{
		return;
	}
	else
	{
		for (size_t i = opt.getDigits(); i < length; i++)
		{
			opt.number.insert(opt.number.begin(), 0);
		}
		return;
	}
}
void numlib::bigint::_sizeFix(bigint& left, bigint& right)
{
	size_t len = 0;
	if (left.getDigits() > right.getDigits())
	{
		len = left.getDigits();
	}
	else
	{
		len = right.getDigits();
	}
	_reserve(left, len);
	_reserve(right, len);
	return;
}
bigint numlib::bigint::_toComplement(bigint& num)
{
	bigint opt = num;
	bool isFirstNotZero = true;
	vector<int>::reverse_iterator i;
	for (i = opt.number.rbegin(); i != opt.number.rend(); i++)
	{
		if (isFirstNotZero == false)
		{
			*i = 9 - *i;
		}
		if (isFirstNotZero && (*i != 0))
		{
			isFirstNotZero = false;
			*i = 10 - *i;
		}
	}
	return opt;
}
bigint numlib::bigint::_regularize()
{
	vector<int>::iterator i;
	for (i = this->number.begin(); (*i == 0) && (this->number.size() > 1); i = this->number.begin())
	{
		this->number.erase(i);
	}
	return *this;
}
bigint numlib::bigint::_leftShift(size_t& index)
{
	for (size_t i = 0; i < index; i++)
	{
		this->number.push_back(0);
	}
	return *this;
}