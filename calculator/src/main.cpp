#include"parse.h"
#include"UI.h"
#include<stdio.h>
#include<QApplication>

int main(int argc, char* argv[])
{
	//double result;
	//std::string input = "1+2/2";
	

	
		//std::tie(result, input) = parseExpression(input);
		//printf("%.3lf", result);//显示double类型，长度不足三个时在左边补空格
	
	QApplication app(argc, argv);//格式头

	UI w;
	w.show();
	
	app.exec();//格式尾

	return 0;
}

