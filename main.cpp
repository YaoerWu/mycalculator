#include "numlib.h"

using numlib::bigint;
using numlib::fraction;
using std::cin;
using std::cout;
using std::invalid_argument;
using std::string;
using std::stringstream;

string toString(fraction fra)
{
	stringstream str;
	if (fra.getNum() < 0)
	{
		str << "-";
	}
	if (fra.isInt())
	{
		str << fra.getNum().toString();
	}
	else
	{
		str << fra.getNum().toString() << "/" << fra.getDen().toString();
	}
	return str.str();
}

int main()
{
	string a1, b1, c1;
	cout << "请按ax^2+bx+c=0的形式输入a,b,c" << std::endl
		<< "允许输入整数，小数，分数（a/b形式）" << std::endl;
	cin >> a1 >> b1 >> c1;
	fraction a(a1), b(b1), c(c1);
	fraction delta = b * b - 4 * a * c;
	cout << "Δ是" << toString(delta) << std::endl;
	fraction fomer = -((b / a) / 2);
	if (delta < 0)
	{
		cout << "Δ小于0，前方的区域以后再来探索吧。";
	}
	else if (delta > 0)
	{
		cout << "该方程有两个根" << std::endl;
		cout << "x1=" << toString(fomer) << "+" << toString((a * 2).getInverse()) << "倍的根下" << toString(delta) << std::endl
			<< "x2=" << toString(fomer) << "-" << toString((a * 2).getInverse()) << "倍的根下" << toString(delta);
	}
	else if (delta == 0)
	{
		cout << "该方程有一个重根x=" << toString(fomer);
	}
	cout << std::endl;
	system("pause");
	return 0;
}