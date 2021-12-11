#include <iostream>
#include "SyntaxAnalyzer.h"
#include "RPNGenerator.h"
#include <string>

int main()
{
	RPNGenerator generator;
	std::cout << generator.generate("5*5*5+(5*6+3)+7*3");
	return 0;
}