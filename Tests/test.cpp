#include "pch.h"
#include "../SimpleCalculator/SyntaxAnalyzer.cpp"
#include "../SimpleCalculator/RPNGenerator.cpp"
#include "../SimpleCalculator/Calculator.cpp"
TEST(SyntaxAnalyzer, GoodData) {
	SyntaxAnalyzer analyzer;
	for (int i = 0; i < 10; i++) {
		EXPECT_TRUE(analyzer.Analyze(std::to_string(i)));
	}
	EXPECT_TRUE(analyzer.Analyze("1-1"));
	EXPECT_TRUE(analyzer.Analyze("1+1"));
	EXPECT_TRUE(analyzer.Analyze("1*1"));
	EXPECT_TRUE(analyzer.Analyze("1/1"));
	EXPECT_TRUE(analyzer.Analyze("1/1"));
	EXPECT_TRUE(analyzer.Analyze("(1)"));
	EXPECT_TRUE(analyzer.Analyze("(1)+(1)"));
	EXPECT_TRUE(analyzer.Analyze("(1)*(1)"));
	EXPECT_TRUE(analyzer.Analyze("(1)/(1)"));
	EXPECT_TRUE(analyzer.Analyze("(1/1)"));
	EXPECT_TRUE(analyzer.Analyze("1+1*1/1-1+(1)*(1/(2))"));
	EXPECT_TRUE(analyzer.Analyze("(5*6+3)+7*3"));
}

TEST(SyntaxAnalyzer, BadData) {
	SyntaxAnalyzer analyzer;
	EXPECT_TRUE(!analyzer.Analyze(""));
	EXPECT_TRUE(!analyzer.Analyze("("));
	EXPECT_TRUE(!analyzer.Analyze(")"));
	EXPECT_TRUE(!analyzer.Analyze("()"));
	EXPECT_TRUE(!analyzer.Analyze("+"));
	EXPECT_TRUE(!analyzer.Analyze("-"));
	EXPECT_TRUE(!analyzer.Analyze("*"));
	EXPECT_TRUE(!analyzer.Analyze("/"));

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			EXPECT_TRUE(!analyzer.Analyze(std::to_string(i) + std::to_string(j)));
		}
	}
	EXPECT_TRUE(!analyzer.Analyze("100"));

	EXPECT_TRUE(!analyzer.Analyze("1+1*1/1-1+(1)*(1/(2)))"));
	EXPECT_TRUE(!analyzer.Analyze("(1+1*1/1-1+(1)*(1/(2))"));
	EXPECT_TRUE(!analyzer.Analyze("1++1"));
	EXPECT_TRUE(!analyzer.Analyze("1**1"));
	EXPECT_TRUE(!analyzer.Analyze("1//1"));
	EXPECT_TRUE(!analyzer.Analyze("1()1"));
	EXPECT_TRUE(!analyzer.Analyze("1--1"));
}

TEST(RPNGenerator, GoodData) {
	RPNGenerator generator;
	for (int i = 0; i < 10; i++) {
		EXPECT_EQ(std::to_string(i), generator.generate(std::to_string(i)));
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			EXPECT_EQ(std::to_string(i) + std::to_string(j) + "+", generator.generate(std::to_string(i) + "+" + std::to_string(j)));
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			EXPECT_EQ(std::to_string(i) + std::to_string(j) + "-", generator.generate(std::to_string(i) + "-" + std::to_string(j)));
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			EXPECT_EQ(std::to_string(i) + std::to_string(j) + "/", generator.generate(std::to_string(i) + "/" + std::to_string(j)));
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			EXPECT_EQ(std::to_string(i) + std::to_string(j) + "*", generator.generate(std::to_string(i) + "*" + std::to_string(j)));
		}
	}
	EXPECT_EQ("1", generator.generate("(((((1)))))"));
	EXPECT_EQ("11+", generator.generate("(1)+(1)"));
	EXPECT_EQ("11*", generator.generate("(1)*(1)"));
	EXPECT_EQ("11/", generator.generate("(1)/(1)"));
	EXPECT_EQ("11/", generator.generate("(1/1)"));
	EXPECT_EQ("564*+", generator.generate("5+6*4"));
	EXPECT_EQ("56*3+73*+", generator.generate("(5*6+3)+7*3"));
	EXPECT_EQ("555**56*3+73*++", generator.generate("5*5*5+(5*6+3)+7*3"));
}

TEST(RPNGenerator, BadData) {
	RPNGenerator generator;
	EXPECT_EQ("", generator.generate(""));
	EXPECT_EQ("", generator.generate("()"));
	EXPECT_EQ("", generator.generate(")("));
	EXPECT_EQ("", generator.generate("("));
	EXPECT_EQ("", generator.generate(")"));
	EXPECT_EQ("", generator.generate("(1"));
	EXPECT_EQ("", generator.generate("1--"));
	EXPECT_EQ("", generator.generate("2++"));
	EXPECT_EQ("", generator.generate("3--1"));
	EXPECT_EQ("", generator.generate("1++5"));
	EXPECT_EQ("", generator.generate("3**1"));
	EXPECT_EQ("", generator.generate("1//5"));

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			EXPECT_EQ("", generator.generate(std::to_string(i) + std::to_string(j)));
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			EXPECT_EQ("", generator.generate(std::to_string(i) + std::to_string(j) + "+"));
		}
	}
}

TEST(Calculator, GoodData) {
	for (int i = 0; i < 10; i++) {
		EXPECT_EQ(i, calculate(std::to_string(i)));
	}

	EXPECT_EQ(2, calculate("11+"));
	EXPECT_EQ(1, calculate("11*"));
	EXPECT_EQ(1, calculate("11/"));
	EXPECT_EQ(29, calculate("564*+"));
	EXPECT_EQ(54, calculate("56*3+73*+"));
	EXPECT_EQ(179, calculate("555**56*3+73*++"));
}

TEST(Calculator, BadData) {
	{
		bool error = false;
		try {
			calculate("1+1");
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
	{
		bool error = false;
		try {
			calculate("5*(1+1)");
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
	{
		bool error = false;
		try {
			calculate("11");
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
	{
		bool error = false;
		try {
			calculate("11+1++");
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
	{
		bool error = false;
		try {
			calculate("1111+1++");
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
	{
		bool error = false;
		try {
			calculate("11$");
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
	{
		bool error = false;
		try {
			calculate("11%");
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
	{
		bool error = false;
		try {
			calculate("");
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
	{
		bool error = false;
		try {
			calculate("kp+");
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
}