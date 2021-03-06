#include"token.h"
#include<iostream>




std::tuple<double, std::string> parseNumber(std::string input) //用来tokenize小数、整数的函数
{
	std::string tempStr;
	char ch;
	while (1)//遇到 若干个数字字符以及小数点 可以组合成一个值
	{
		if (input.empty())//刚好是表达式最后的数字时，存完后结束
		{
			break;
		}

		ch = input.front();
		if ((ch >= '0' && ch <= '9') || (ch == '.'))
		{
			tempStr.push_back(ch);//把数字部分放进字符串tempStr，每个ch放在字符串尾
			input.erase(input.begin());//删除input中该数字部分 
		}
		else //该number存完，接下来是其他符号时 结束
		{
			break;
		}
	}//循环结束时，数字部分保留在tempStr中，剩余字符串在input中 

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
			ch = input.front();        //取出首字符
			input.erase(input.begin());//去除首字符 
		}
	} 	 while (ch == ' ');//只要还有空格就继续循环
	
	//修改5/25   !!!!!注意最后一次时，表达式的第一个字符在ch里，在input中已经被删除!!! 

	switch (ch) //判断符号类型
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
		tk.type = TokenType(ch);//是运算符号
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
		tk.type = TokenType::Number;//是数字
		input.insert(input.begin(), ch);//将ch添加回input开头 
		std::tie(tk.value, input) = parseNumber(input);
		break;

	default:
		std::cout<<("输入错误\n");
		break;
	}
	return{ tk,input };
}