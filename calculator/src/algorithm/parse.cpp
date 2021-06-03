#include"parse.h"
#include"token.h"
#include<iostream>
#include<string.h>
//E->TR
//R->+T R | -T R |NULL

      



 static std::tuple<double, std::string> parseFactor(std::string input)
{
	//F->number|(E)
	double result;
	Token tk;
	//解析第一个token
	std::tie(tk, input) = tokenize(input);

	switch (tk.type) {
	case TokenType::Number://如果是数
		result = tk.value;
		break;
	case TokenType::Lp://如果遇到（E）的情况
		//解析里面的E
		std::tie(result, input) = parseExpression(input);
		//再解析右括号）
		std::tie(tk, input) = tokenize(input);
		//如果解析出来不是），则有语法错误，缺失）
		if (tk.type != TokenType::Rp)
		{
			std::cout << "输入错误，缺失“）”\n";
			break;
		}

		break;
	default:
		std::cout << "输入有误需要“数字”或者“（”\n";
		break;
	}
	return { result,input };
}



 static std::tuple<double, std::string> parseTerm(std::string input)
 {
	 double result;
	 //翻译T->FR中的F
	 std::tie(result, input) = parseFactor(input);

	 //翻译E->FR中的R
	 bool flag = true;
	 while (flag)
	 {
		 Token tk;
		 std::string res;
		 double term;
		 //第2.1步 翻译R—>*TR|/TR|NULL中的第一个token 那就是*或/或空
		 std::tie(tk, res) = tokenize(input);

		 switch (tk.type)
		 {
		 case TokenType::mul:
			 //第2.2步 解析*T R中的T
			 std::tie(term, input) = parseFactor(res);
			 result *= term;
			 break;
		 case TokenType::div:
			 //第2.2步 解析/T R中的T
			 std::tie(term, input) = parseFactor(res);
			 if (term == 0.0)
			 {
				 std::cout << "不可能除以0\n";
				 break;
			 }
			 result /= term;
			 break;
		 default:
			 flag = false;//退出while循环
			 break;
		 }

	 }
	 return{ result,input };
 }



 std::tuple<double, std::string> parseExpression(std::string input)    //解析表达式
 {
	 double result;
	 //翻译E->TR中的T
	 //////6月2日修改，发现无法处理以“-”开头的表达式
	 std:: string first;
	 first.assign(input, 0, 1); 
	 if (first == "-") { input.insert(0, "0"); };//如果表达式以“-”开头，则在表达式的首位补上0；
	 //////
	 std::tie(result, input) = parseTerm(input);

	 //翻译E->TR中的R
	 bool flag = true;
	 while (flag)
	 {
		 Token tk;
		 std::string res;
		 double term;
		 //第2.1步 翻译R—>+TR|-TR|NULL中的第一个token 那就是+或-或空
		 std::tie(tk, res) = tokenize(input);

		 switch (tk.type)
		 {
		 case TokenType::Plus:
			 //第2.2步 解析+T R中的T
			 std::tie(term, input) = parseTerm(res);
			 result += term;
			 break;
		 case TokenType::Minus:
			 //第2.2步 解析-T R中的T
			 std::tie(term, input) = parseTerm(res);
			 result -= term;
			 break;
		 default:
			 flag = false;//退出while循环
			 break;
		 }


	 }
	 return{ result,input };
 }
