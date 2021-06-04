#include<tuple>
#include<string>

enum class TokenType //枚举类型 
{
	Number,
	End,
	Error,
	Plus = '+',
	Minus = '-',
	mul = '*',
	div = '/',
	Lp = '(',  // left parentheses 左括号 
	Rp = ')',

};

struct Token //定义一个Token的数据类型来统一 装符号（包括数值），
{
	TokenType type;//字符类型 
	double value;  //如果是数字，存值 
};

std::tuple<Token, std::string> tokenize(std::string input);
