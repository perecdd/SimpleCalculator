#include <iostream>
#include "SyntaxAnalyzer.h"
#include "RPNGenerator.h"
#include "Calculator.h"
#include <string>

int main()
{
	std::string line;
	std::cin >> line;
	SyntaxAnalyzer analyzer;
	if (analyzer.Analyze(line)) {
		RPNGenerator generator;
		std::cout << "RPN: " << generator.generate(line) << std::endl;
		std::cout << calculate(generator.generate(line));
	}
	else {
		std::cout << "Error!";
	}
	return 0;
}