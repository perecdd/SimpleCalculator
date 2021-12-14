#include "RPNGenerator.h"

RPNGenerator::RPNGenerator()
{
}

std::string RPNGenerator::generate(const std::string& line)
{
	result = "";
	size = line.size();
	line_ = line.data();
	pointer = 0;

	if (E() && pointer == size) {
		return result;
	}
	else {
		return "";
	}
}

bool RPNGenerator::E()
{
	if (pointer >= size) return false;
	if (!E3()) return false;
	return true;
}

bool RPNGenerator::E3()
{
	if (pointer >= size) return false;
	if (!E2()) return false;
	if (!E33()) return false;
	return true;
}

bool RPNGenerator::E33()
{
	if (pointer >= size) return true;
	if (line_[pointer] == '+') {
		pointer++;
		if (!E2()) return false;
		result.push_back('+');
		if (!E33()) return false;
	}
	else if (line_[pointer] == '-') {
		pointer++;
		if (!E2()) return false;
		result.push_back('-');
		if (!E33()) return false;
	}
	return true;
}

bool RPNGenerator::E2()
{
	if (pointer >= size) return false;
	if (!E1()) return false;
	if (!E22()) return false;
	return true;
}

bool RPNGenerator::E22()
{
	if (pointer >= size) return true;
	if (line_[pointer] == '*') {
		pointer++;
		if (!E1()) return false;
		result.push_back('*');
		if (!E22()) return false;
	}
	else if (line_[pointer] == '/') {
		pointer++;
		if (!E1()) return false;
		result.push_back('/');
		if (!E22()) return false;
	}
	return true;
}

bool RPNGenerator::E1()
{
	if (pointer >= size) return false;
	if (line_[pointer] >= '0' && line_[pointer] <= '9') {
		result.push_back(line_[pointer]);
		pointer++;
	}
	else {
		if (line_[pointer] == '(') {
			pointer++;
			if (!E()) return false;
			if (line_[pointer] == ')') {
				pointer++;
			}
			else return false;
		}
		else return false;
	}
	return true;
}
