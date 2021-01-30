#include "analyzer.h"
#include <assert.h>
#include <stack>
#include <vector>

bool is_digit_char(const char c)
{
	if (c <= '9' && c >= '0')
		return true;
	return false;
}

bool is_operator_char(const char c)
{
	if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	return false;
}

bool delete_spaces(std::string &s)// 1 if digit space digit
{
	for (size_t i = 0; i < s.size(); i++)
	{
		if (i < s.size() - 1 && is_digit_char(s[i]) && s[i + 1] == ' ' && is_digit_char(s[i + 2]))
			return true;
		if (s[i] == ' ')
		{
			s.erase(s.begin() + i);
			i--;
		}
	}
	return false;
}

bool check_brackets(const std::string &s)//quantity?
{
	size_t left_quantity = 0;
	size_t right_quantity = 0;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == ')') right_quantity++;
		if (s[i] == '(') left_quantity++;
		if (right_quantity > left_quantity)
			return 1;
	}
	assert(left_quantity == right_quantity);
	return 0;
}

void check_symbols(const std::string &s)
{
	for (size_t i = 0; i < s.size(); i++)
		assert(is_digit_char(s[i]) || is_operator_char(s[i]));
}

bool check_string(const std::string &s)//if empty, only brackets wrong beginning or only operators
{
	assert(s.size() > 0);
	assert(s[0] != '*' && s[0] != '/' && s[0] != '+' && s[0] != '-' && s[0] != ')');
	if (s[s.size() - 1] == '*' || s[s.size() - 1] == '-' || s[s.size() - 1] == '(' || s[s.size() - 1] == '+' || s[s.size() - 1] == '/')
		return 1;
	
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '(' && s[i + 1] == ')')
			return 1;
		if (s[i] == ')' && s[i + 1] == '(')
			return 1;
		if (s[i] == '(' && (s[i + 1] == '*' || s[i + 1] == '/'))
			return 1;
		if (s[i] == '*' && (s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == ')'))
			return 1;
		if (s[i] == '/' && (s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == ')'))
			return 1;
		if (s[i] == '(' && (s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == ')'))
			return 1;
		if (s[i] == '+' && (s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == ')'))
			return 1;
		if (s[i] == '-' && (s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == ')'))
			return 1;
		if (s[i] == '(' && s[i + 1] == '-' && s[i + 2] == '(')
			return 1;
	}
	return 0;
}

bool is_num(const char c)// 1 - num, 0 - not num
{
	if (c <= '9' && c >= '0')
		return true;
	else
		return false;
}

bool is_operator(const char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
		return true;
	else
		return false;
}

bool is_unary(const std::string &s, const size_t i)// 1 - unary, 0 - no
{
	if (i > 1 && (s[i - 1] == '-' || s[i - 1] == '+') && s[i - 2] == '(')
		return true;
	else
		return false;
}

std::string make_num(const std::string &s, size_t& i)
{
	std::string number;
	if (is_unary(s, i) == 1)
		number += s[i - 1];

	while (i < s.size() && is_num(s[i]))
	{
		number += s[i];
		i++;
	}
	i--;

	return number;
}

void push_num(std::vector<tokens::token_t> &tokens, std::string &num)
{
	tokens::token_t number;
	number.token_value = num;
	number.token_type = tokens::type::operand;
	tokens.push_back(number);
}

tokens::type define_type(char c)
{
	if (c == '+')
		return tokens::addition;
	if (c == '*')
		return tokens::multiplication;
	if (c == '-')
		return tokens::substraction;
	if (c == '/')
		return tokens::division;
	if (c == ')')
		return tokens::right_bracket;
	if (c == '(')
		return tokens::left_bracket;
}

void push_operator(std::vector<tokens::token_t>& tokens, char symbol)
{
	tokens::token_t oper;
	oper.token_value = symbol;
	oper.token_type = define_type(symbol);
	tokens.push_back(oper);
}

std::vector <tokens::token_t> tokens::parse(const std::string &s)
{
	std::vector<tokens::token_t> parse_vec;

	for (size_t i = 0; i < s.size(); i++)
	{
		std::string number;
		if (is_num(s[i]))
		{
			number = make_num(s, i);
			push_num(parse_vec, number);
		}
		else if (is_unary(s, i + 2))
		{
			push_operator(parse_vec, s[i]);
			i += 2;
			number = make_num(s, i);
			push_num(parse_vec, number);
		}
		else if (is_operator(s[i]))
		{
			push_operator(parse_vec, s[i]);
		}
	}
	return parse_vec;
}

void exp_end(std::vector<tokens::token_t> &postfix_vec, std::stack<tokens::token_t> &operators)//change
{
	while (!operators.empty())
	{
		postfix_vec.push_back(operators.top());
		operators.pop();
	}
}

bool priority(const tokens::token_t &a, const tokens::token_t &b)// 0 - precedence is higher, 1 - precedence is lower or equal(or Associativity)
{//b - top
	if ((a.token_type == tokens::multiplication || a.token_type == tokens::division) && (b.token_type == tokens::addition || b.token_type == tokens::substraction))
		return false;
	else if ((a.token_type == tokens::multiplication || a.token_type == tokens::division) && (b.token_type == tokens::division || b.token_type == tokens::multiplication))
		return true;
	else if ((a.token_type == tokens::addition || a.token_type == tokens::substraction) && (b.token_type == tokens::division || b.token_type == tokens::multiplication || b.token_type == tokens::addition || b.token_type == tokens::substraction))
		return true;
}

bool  postfix_operator_case(const std::vector<tokens::token_t> &tokens, std::vector<tokens::token_t> &postfix_vec, size_t i, std::stack<tokens::token_t> &operators)
{
	if (operators.empty())
	{
		operators.push(tokens[i]);
		return false;
	}

	else if (tokens[i].token_type == tokens::type::left_bracket)
	{
		operators.push(tokens[i]);
		return false;
	}

	else if (tokens[i].token_type == tokens::right_bracket)
	{
		while (!operators.empty())
		{
			if (operators.top().token_type == tokens::left_bracket)
			{
				operators.pop();
				return false;
			}
			postfix_vec.push_back(operators.top());
			operators.pop();
		}
		return false;
	}

	else if (!operators.empty() && priority(tokens[i], operators.top()) == 0)
	{
		operators.push(tokens[i]);
		return false;
	}

	else
	{
		while (!operators.empty() && priority(tokens[i], operators.top()) != 0)
		{
			if (operators.top().token_type == tokens::left_bracket)
				break;
			
			postfix_vec.push_back(operators.top());
			operators.pop();
		}
		operators.push(tokens[i]);
	}	
	return false;

}

void postfix_num_case(const std::vector<tokens::token_t> &tokens, size_t i, std::vector<tokens::token_t> &postfix_vec)
{
	postfix_vec.push_back(tokens[i]);
}

std::vector<tokens::token_t> tokens::to_postfix(const std::vector<tokens::token_t> &tokens)
{
	std::vector<tokens::token_t> postfix_vec;
	std::stack<tokens::token_t> operators;
	
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].token_type == tokens::operand)
			postfix_num_case(tokens, i, postfix_vec);
		else
			postfix_operator_case(tokens, postfix_vec, i, operators);
	}
	exp_end(postfix_vec, operators);
	return postfix_vec;
}

bool is_operand_token(const tokens::token_t &token)
{
	if (token.token_type == tokens::operand)
		return true;
	return false;
}
std::stack<tokens::token_t> make_operand_stack(const std::vector<tokens::token_t> &postfix_vec)
{
	std::stack<tokens::token_t> operand;
	for (size_t i = 0; i < postfix_vec.size(); i++)
	{
		if (is_operand_token(postfix_vec[i]))
			operand.push(postfix_vec[i]);
	}
	return operand;
}

void push_to_stack(const int result, std::stack<tokens::token_t> &answer)
{
	tokens::token_t value;
	value.token_type = tokens::operand;
	value.token_value = std::to_string(result);
	answer.push(value);
}

void check_division(const tokens::token_t& a)
{
	assert(std::stoi(a.token_value) != 0);
}

void operation(const std::vector<tokens::token_t>& postfix_vec, const size_t i, std::stack<tokens::token_t> &answer)
{
	tokens::token_t a = answer.top();
	answer.pop();
	tokens::token_t b = answer.top();
	answer.pop();
	
	int result = 0;
	if (postfix_vec[i].token_type == tokens::addition)
		result = std::stoi(b.token_value) + std::stoi(a.token_value);

	else if (postfix_vec[i].token_type == tokens::division)
	{
		check_division(a);
		result = std::stoi(b.token_value) / stoi(a.token_value);
	}

	else if (postfix_vec[i].token_type == tokens::multiplication)
		result = std::stoi(b.token_value) * stoi(a.token_value);

	else if (postfix_vec[i].token_type == tokens::substraction)
		result = std::stoi(b.token_value) - stoi(a.token_value);

	push_to_stack(result, answer);
}

void check_int_value(const tokens::token_t num)
{
	assert(std::stoi(num.token_value) <= 2147483647);
	assert(std::stoi(num.token_value) >= -2147483648);
}

int tokens::calculate(const std::vector<tokens::token_t> &postfix_vec)
{
	std::stack<tokens::token_t> answer;// = make_operand_stack(postfix_vec);
	for (size_t i = 0; i < postfix_vec.size(); i++)
	{
		if (is_operand_token(postfix_vec[i]))
		{
			check_int_value(postfix_vec[i]);
			answer.push(postfix_vec[i]);
		}
		else
			operation(postfix_vec, i, answer);
	}
	int result = std::stoi(answer.top().token_value);
	return result;
}

int tokens::string_foo(std::string &s)
{
	assert(delete_spaces(s) == 0);
	check_symbols(s);
	assert(check_brackets(s) == 0);
	assert(check_string(s) == 0);

	std::vector<tokens::token_t> parse_vec = tokens::parse(s);
	std::vector<tokens::token_t> postfix_vec = tokens::to_postfix(parse_vec);
	int result = tokens::calculate(postfix_vec);
	return result;
}
