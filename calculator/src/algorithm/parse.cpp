#include"parse.h"
#include"token.h"
#include<iostream>
#include<string.h>
//E为表达式，在加减层面      T为项，在乘除层面     F为元素，是数值或者（E）
//E->TR   R-> +T R | -T R | NULL  表达式E由n个项加减组成，将其分成 当前值 与 R(剩余若干个 加减T)
//T->FR   R-> *F R | /F R | NULL  表达式T由n个元素乘除组成，将其分成 当前值 与 R(剩余若干个 乘除F)

      



 static std::tuple<double, std::string> parseFactor(std::string input)//解析F， F为元素，是数值或者（E）
{
	//F->number|(E)
	double result;
	Token tk;
	
	std::tie(tk, input) = tokenize(input);//解析接下来的一个数 或者 一个（E）

	switch (tk.type) //判断当前的token是 数 还是 （E）
	{
	case TokenType::Number://如果是数
		result = tk.value;
		break;

	case TokenType::Lp://如果遇到（E）的情况
		
		std::tie(result, input) = parseExpression(input);//解析里面的E
		
		std::tie(tk, input) = tokenize(input);//再解析右括号）
		
		if (tk.type != TokenType::Rp)//如果解析出来不是），则有语法错误
		{
			std::cout << "输入错误，缺失“）”\n";
			break;
		}
		break;

	default:
		std::cout << "输入有误需要“数字”或者“（”\n"; //既不是数字 也不是(E)，报错
		break;
	}
	return { result,input };
}



 static std::tuple<double, std::string> parseTerm(std::string input)//解析T，T->FR   R-> *F R | /F R | NULL
 {
	 double result;
	 //第1步  翻译T->FR中的F
	 std::tie(result, input) = parseFactor(input);

	 //第2步  翻译T->FR中的R     （此时R为剩余的n个 *F 或 /F）
	 bool flag = true;
	 while (flag)// R— > *FR || /FR || NULL, *F 或 /F 直到表达式 为空
	 {
		 Token tk;
		 std::string res;
		 double term;
		 //第2.1步 翻译R—>  *FR || /FR || NULL 中 的 * 或 / 或空
		 std::tie(tk, res) = tokenize(input);

		 switch (tk.type)//根据是 * 或 / 或 空，进行 *FR 或 /FR 或 NULL
		 {
		 case TokenType::mul: //如果是*
			 //第2.2步 解析*F R中的F
			 std::tie(term, input) = parseFactor(res);
			 result *= term;
			 break;
		 case TokenType::div: //如果是 /
			 //第2.2步 解析/F R中的/F
			 std::tie(term, input) = parseFactor(res);
			 if (term == 0.0) //除以0时报错
			 {
				 std::cout << "不可能除以0  \n";
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



 std::tuple<double, std::string> parseExpression(std::string input)    //解析E，E->TR   R-> +T R | -T R | NULL
 {
	 double result;
	 
	 //////6月2日修改，发现无法处理以“-”开头的表达式
	 std:: string first;
	 first.assign(input, 0, 1); 
	 if (first == "-") { input.insert(0, "0"); };//如果表达式以“-”开头，则在表达式的首位补上0；
	 

	 std::tie(result, input) = parseTerm(input);//第1步  翻译E->TR中的T，即解析表达式的第一个数值，result存取数值，input存取剩余表达式

	 //第2步  翻译E->TR中的R    （此时 R为剩余的n个+T 或 -T）
	 bool flag = true;
	 while (flag)// R— > +TR || -TR || NULL, +T 或 -T 直到表达式 为空
	 {
		 Token tk;
		 std::string res;
		 double term;
		 
		 //第2.1步 翻译R—> +TR || -TR || NULL 中 的+或-或空
		 std::tie(tk, res) = tokenize(input);

		 switch (tk.type)//根据是 + 或 - 或 空，进行 +TR 或 -TR 或 NULL
		 {
		 case TokenType::Plus:       //+ 的情况
			 //第2.2步 解析R—>+T R中的T
			 std::tie(term, input) = parseTerm(res);
			 result += term;
			 break;
		 case TokenType::Minus:      //- 的情况
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
