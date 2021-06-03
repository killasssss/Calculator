#include"token.h"
#include<iostream>




std::tuple<double, std::string> parseNumber(std::string input)
{
	std::string tempStr;
	char ch;
	while (1)//遇到 若干个数字字符以及小数点 可以组合成一个值
	{
		if (input.empty())
		{
			break;
		}

		ch = input.front();
		if ((ch >= '0' && ch <= '9') || (ch == '.'))
		{
			tempStr.push_back(ch);//把数字部分放进字符串 
			input.erase(input.begin());//删除该数字部分 
		}
		else
		{
			break;
		}
	}//循环结束，数字部分保留在tempStr中，剩余字符串在input中 

	return{std::stod(tempStr),input};//stod=string to double 将保留在tempStr中数字部分保持double
}



std::tuple<Token, std::string> tokenize(std::string input)
{
	char ch;
	Token tk;


	do//去掉开头空格 
	{
		if (input.empty())//如果input是空串
		{
			tk.type = TokenType::End;
			return{ tk,"" };
		}
		else
		{
			ch = input.front();
			input.erase(input.begin());//去除首字符 
		}
	} 	 while (ch == ' ');
	//!!!!!注意最后一次时，表达式的第一个字符还在ch里，在input中已经被删除!!! 

	switch (ch)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
		tk.type = TokenType(ch);
		break;
	
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		tk.type = TokenType::Number;
		input.insert(input.begin(), ch);//将ch添加回input开头 
		std::tie(tk.value, input) = parseNumber(input);
		break;

	default:
		std::cout<<("输入错误\n");
		break;
	}
	return{ tk,input };
}