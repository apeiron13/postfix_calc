#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace tokens
{
	enum type {
		operand,//numbers
		addition,
		substraction,
		multiplication,
		division,
		left_bracket,
		right_bracket
	};
	
	struct token_t 
	{
		type token_type;
		std::string token_value;
	};
	
	std::vector<tokens::token_t> to_postfix(const std::vector<tokens::token_t>& tokens);
	std::vector <tokens::token_t> parse(const std::string &s);
	//std::vector <tokens::token_t> string_foo(std::string &s);
	int string_foo(std::string& s);
	int calculate(const std::vector<tokens::token_t>& v);
	
}


