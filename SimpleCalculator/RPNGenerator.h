#pragma once
#include <string>

// Grammar:
// E -> E3
// E3 -> E2 E33
// E33 -> + E2 E33 | - E2 E33 | e
// E2 -> E1 E22
// E22 -> * E1 E22 | / E1 E22 | e
// E1 -> num | (E)
class RPNGenerator // Reverse Polish notation
{
public:
	RPNGenerator();
	std::string generate(const std::string& line);

private:
	bool E();
	bool E3();
	bool E33();
	bool E2();
	bool E22();
	bool E1();

	std::string result;
	int size = 0;
	int pointer = 0;
	const char* line_ = nullptr;
};