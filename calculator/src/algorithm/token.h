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

struct Token
{
	TokenType type;//字符类型 
	double value = 0.0;//如果是数字存值 
};
std::tuple<Token, std::string> tokenize(std::string input);
