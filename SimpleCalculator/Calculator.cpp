#include "Calculator.h"
#include <stack>
#include <stdexcept>

int calculate(std::string_view line)
{
	std::string log = std::string(line);

	std::stack<int> values;

	while (!line.empty()) {
		char sym = line.front();
		line.remove_prefix(1);

		if (sym >= '0' && sym <= '9') {
			values.push(sym - '0');
		}
		else if (values.size() >= 2) {
			int second = values.top();
			values.pop();
			int first = values.top();
			values.pop();

			int result = 0;

			switch (sym) {
			case '+':
				result = first + second;
				break;

			case '-':
				result = first - second;
				break;

			case '*':
				result = first * second;
				break;

			case '/':
				result = first / second;
				break;

			default:
				throw std::runtime_error(std::string("Unknown operation '") + sym + "'");
				break;
			}

			values.push(result);
		}
		else throw std::runtime_error("Incorrect expression: '" + log + "'");
	}

	if (values.size() == 1) {
		return values.top();
	}
	else {
		throw std::runtime_error("Not all digits are connected by operators OR the expression is empty");
	}
}