#ifdef RUN_TESTS
#include <iostream>
#include <string>
#include <vector>
#include "analyzer.h"
#include "print.h"
#include <assert.h>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
/*
void test1()
{
	//string s = "2+3";
	string s = "3*(  4 +  (+5) -6)  / (-2)";  //
	vector<tokens::token_t> example = tokens::string_foo(s);
	//cout << "success 1" << endl;
	cout << s << endl;
	print_vector(example);
	cout << endl;

}

void test1a()
{
	string s = "3 + 4 + 5";//
	vector<tokens::token_t> example = tokens::parse(s);
	//cout << "success 1a" << endl;
	cout << s << endl;
	print_vector(example);
	cout << endl;
}

void test1b()
{
	string s = "3 *4 + 5*12";//
	vector<tokens::token_t> example = tokens::parse(s);
	//cout << "success 1b" << endl;
	cout << s << endl;
	print_vector(example);
	cout << endl;
}

void test1c()
{
	string s = "3*-4 + 5*12 + 24/ -12";//
	vector<tokens::token_t> example = tokens::parse(s);
	//cout << "success 1c" << endl;
	cout << s << endl;
	print_vector(example);
	cout << endl;
}

void test1d()
{
	string s = ")3*-4 + 5*12 + 24/ -12";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 1d" << endl;

}

void test1e()
{
	string s = "*3*-4 + 5*12 + 24/ -12";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 1e" << endl;

}

void test1f()
{
	string s = "/3*-4 + 5*12 + 24/ -12";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 1f" << endl;

}


void test1g()
{
	string s = "3 -4) + 5*12 + 24/ -12";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 1g" << endl;

}

void test1h()
{
	string s = "3 -4 + (5*12 + (24/ -12)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 1h" << endl;

}

void test1i()
{
	string s = "3 -4 + (5*12 + (24/ -12)))(";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 1i" << endl;

}


void test2()
{
	string s = "()";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 2" << endl;
}

void test2a()
{
	string s = "(-)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 2a" << endl;
}

void test2b()
{
	string s = "(+)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 2b" << endl;
}

void test2ba()
{
	string s = "(*)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 2ba" << endl;
}

void test2c()
{
	string s = "(/)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 2c" << endl;
}

void test2bc()
{
	string s = "(/*-+)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 2bc" << endl;
}

void test2bb()
{
	string s = "(/*(((-+)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 2bb" << endl;
}

void test3()
{
	string s = "(*2)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 3" << endl;
}

void test3a()
{
	string s = "(/2)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 3a" << endl;
}

void test3b()//fine
{
	string s = "(+2)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 3b" << endl;
}

void test3c()//fine
{
	string s = "(-2)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 3c" << endl;
}

void test3d()//
{
	string s = "(2+)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 3d" << endl;
}

void test3e()//
{
	string s = "(2-)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 3e" << endl;
}

void test4()
{
	string s = "(-2) - 99 + (15 * 5 / 3))";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 4" << endl;
}

void test4a()
{
	string s = "(-2) - 99 + 15 * 5 / 3 - 13)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 4a" << endl;
}

void test4b()
{
	string s = "(-2) - 99 + 15 * 5 / 3 - 13)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 4b" << endl;
}

void test4c()
{
	string s = "((-2) - 99 + 15) * (45 / 3) - 13)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 4c" << endl;
}

void test4d()
{
	string s = "((-2) - 99 + 15) *(6 - 2) / ( 4 * 1) * (45 / 3) - 13)";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 4d" << endl;
}

void test4e()
{
	string s = "((-4) / (-2) - 99 + 15) *(6 - 2) / ( 4 * 1) * (45 / 3) - 13) - -2 ++5";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 4e" << endl;
}

void test5()
{
	string s = "((-4) _/ (-2) ";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 5" << endl;
}

void test5a()
{
	string s = "((-4) !/ (-2) ";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 5a" << endl;
}

void test5b()
{
	string s = "((b-4) !a/ (-2) ";//
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 5b" << endl;
}

void test5c()
{
	string s = "((b-4) !a/ (-2) ";
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 5c" << endl;
}

void test5d()
{
	string s = "((@-4) !a/ (-2) ";
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 5d" << endl;
}

void test5e()
{
	string s = "  ";
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 5e" << endl;
}

void test5f()
{
	string s = "";
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 5f" << endl;
}

void test6()
{
	string s = "      ";
	vector<tokens::token_t> example = tokens::string_foo(s);
	cout << "success 6" << endl;
	//std::vector<tokens::token_t> postfix_example = to_postfix(example);
}
*/
void test_postfix()
{
	//string s = "56 + 3";
	//string s = "56 * 3";
	//string s = "56 / 3";
	//string s = "56 - 3";
	//string s = "56 + 3 * 4";
	//string s = "56 * 3 /2";
	//string s = "56 + 3 + 4";
	//string s = "5 * (-2)";
	//string s = "5 * (-2 + 3 * 4)";
	//kstring s = "5 * (-2 + 3 * ( 2 + 4) - 2)";
	//string s = "5 * (-2 + 3 * ( 2 + 4) - 2) * (3 + ( 2 * (-5)))";
	//string s = "5 * (-2 + 3 * ( 2 + 4) - 2) * (3 + ( 2 * ( +5 + 2 *(-5) / (- 3 * 5))))";
	//0string s = "5 * (-2 + 3 * ( 2 + 4) - 2) * (3 + ( 2 * ( +5 + 2 *(-5) / ( 3 * 5 / 2 - 5))))";
	//string s = "(1+2+2*3*3*3+4*(1+2)/(2*3)*(3-4)/(5+3))";
	//string s = "1 + 3 + 7 / 853 * (4 - (4 - (5 + 9) * 23) / 2)";
	//string s = "0 ";
	//string s = "2 * (4 / (1) * 4 / 4) + 5";
	//string s = "-1-(-1)-(1+(-1)+(-1))";
	//string s = "2*(4/(1)*4/4)";
	//string s = "(-(2+1) )";
	//string s = "500000000000/2";
	// m          2147483647
	//string s = "(-(-3 - 9)) - 91";
	//cout << sizeof(int) << endl;
	//string s = "2 * (4 / (1) * 4 / 4) + 5";
	//string s = "2 * ( 66 / 2 *3  ) + (2 * 3) - 55";
	//string s = "2 * ( 636 - 43 / 2 * (-1) /3  ) + (2 * 3) - 55 + 32 + (4 *33)";
	string s = "2/0";
	int answer = tokens::string_foo(s);
	cout << endl << s << endl;
	cout << answer;
}

int main()
{
	//test1(); //ok
	//test1a(); //ok 
	//test1b(); //ok
	//test1c(); //ok
	//test1d(); //er
	//test1e(); //er
	//test1f(); //er
	//test1g(); //er
	//test1h();
	//test1i();
	//test2();
	//test2a();
	//test2b();
	//test2c();
	//test2bb();
	//test2ba();
	//test2bc();
	//test3();
	//test3a();
	//test3b();
	//test3c();
	//test3d();
	//test3e();
	//test4();
	//test4a();
	//test4b();
	//test4c();
	//test4d();
	//test4e();
	//test4();
	//test5();
	//test5a();
	//test5b();
	//test5c();
	//test5d();
	//test5e();
	//test5f();//er
	//test6();//er

	test_postfix();
	return 0;
}

#endif
