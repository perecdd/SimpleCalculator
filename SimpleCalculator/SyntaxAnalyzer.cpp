#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer()
{
}

bool SyntaxAnalyzer::Analyze(const std::string& line)
{
	size = line.size();
	line_ = line.data();
	pointer = 0;
	return E() && size == pointer;
}

bool SyntaxAnalyzer::E()
{
	if (pointer >= size) return false;
	if (!E3()) return false;
	return true;
}

bool SyntaxAnalyzer::E3()
{
	if (pointer >= size) return false;
	if (!E2()) return false;
	if (!E33()) return false;
	return true;
}

bool SyntaxAnalyzer::E33()
{
	if (pointer >= size) return true;
	if (line_[pointer] == '+') {
		pointer++;
		if (!E2()) return false;
		if (!E33()) return false;
	}
	else if (line_[pointer] == '-') {
		pointer++;
		if (!E2()) return false;
		if (!E33()) return false;
	}
	return true;
}

bool SyntaxAnalyzer::E2()
{
	if (pointer >= size) return false;
	if (!E1()) return false;
	if (!E22()) return false;
	return true;
}

bool SyntaxAnalyzer::E22()
{
	if (pointer >= size) return true;
	if (line_[pointer] == '*') {
		pointer++;
		if (!E1()) return false;
		if (!E22()) return false;
	}
	else if (line_[pointer] == '/') {
		pointer++;
		if (!E1()) return false;
		if (!E22()) return false;
	}
	return true;
}

bool SyntaxAnalyzer::E1()
{
	if (pointer >= size) return false;
	if (line_[pointer] >= '0' && line_[pointer] <= '9') {
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
