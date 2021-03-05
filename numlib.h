#ifndef NUMLIB_H
#define NUMLIB_H

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

namespace numlib
{
	class bigint
	{
	public:
		bigint();
		bigint(int num);
		bigint(size_t num);
		bigint(long long num);
		bigint(const std::string &num);

		size_t getDigits();
		bigint getInverse();
		std::string toString();

		static bigint pow(const bigint &opt, const bigint &index);

		bigint operator-();
		void operator=(const bigint &num);
		bigint operator++();
		bigint operator++(int num);
		bigint operator--();
		bigint operator--(int num);
		friend bigint operator+(const bigint &left_i, const bigint &right_i);
		friend bigint operator-(const bigint &left_i, const bigint &right_i);
		friend bigint operator*(const bigint &left_i, const bigint &right_i);
		friend bigint operator/(const bigint &left_i, const bigint &right_i);
		friend bigint operator%(const bigint &left_i, const bigint &right_i);
		friend bool operator==(const bigint &left, const bigint &right);
		friend bool operator!=(const bigint &left, const bigint &right);
		friend bool operator<(const bigint &left, const bigint &right);
		friend bool operator<=(const bigint &left, const bigint &right);
		friend bool operator>(const bigint &left, const bigint &right);
		friend bool operator>=(const bigint &left, const bigint &right);

	private:
		std::vector<int> number;
		int notation;

		static bigint _add(bigint &left, bigint &right);
		static bigint _subtract(bigint &left, bigint &right);
		static bigint _multiplie(bigint &left, bigint &right);
		static void _divide(bigint &left, bigint &right, bigint &quotient, bigint &remainder);

		static void _reserve(bigint &opt, size_t length);
		static void _sizeFix(bigint &left, bigint &right);
		static bigint _toComplement(bigint &num);
		bigint _regularize();
		bigint _leftShift(size_t &index);
	};

	class fraction
	{
	public:
		fraction();
		fraction(int up);
		fraction(bigint up);
		fraction(bigint up, bigint down);
		fraction(std::string num);

		fraction getInverse();
		bigint getNum();
		bigint getDen();
		bool isInt();

		static fraction pow(const fraction &opt, const bigint &index);

		fraction operator-();
		void operator=(const fraction &num);
		friend fraction operator+(const fraction &left_i, const fraction &right_i);
		friend fraction operator-(const fraction &left_i, const fraction &right_i);
		friend fraction operator*(const fraction &left_i, const fraction &right_i);
		friend fraction operator/(const fraction &left_i, const fraction &right_i);
		friend bool operator==(const fraction &left, const fraction &right);
		friend bool operator!=(const fraction &left, const fraction &right);
		friend bool operator<(const fraction &left, const fraction &right);
		friend bool operator<=(const fraction &left, const fraction &right);
		friend bool operator>(const fraction &left, const fraction &right);
		friend bool operator>=(const fraction &left, const fraction &right);

	private:
		bigint up;
		bigint down;
		static bigint _gcd(bigint m, bigint n);
		static bigint _toInt(std::string opt);
	};
}
#endif