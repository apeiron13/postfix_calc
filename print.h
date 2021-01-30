#pragma once
#include "analyzer.h"

using std::cout;
using std::endl;

void print_vector(const std::vector<tokens::token_t> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << vec[i].token_value <<" ";
	}
	cout << endl;
}

