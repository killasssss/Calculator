#include"UI.h"
#include"parse.h"
#include<QPushButton>
#include<QHBoxLayout>//水平布局
#include<QVBoxLayout>//垂直布局
#include<QGridLayout>//栅格布局（按照坐标布局）
#include<iostream>
#include<QFont>
#include<string>
#include"math.h"
//UI.cpp 分为 初始界面设置 与 按钮响应设置
//===================初始界面设置==================================================================
UI::UI(QWidget* parent):QDialog(parent) //构造函数
{
	
	pText = new QLineEdit("click \"CE\" to use", this);//文本框，引号里填初始显示的内容
	pText->setMinimumHeight(80);//设置文本框最小高度
	QFont font;
	font.setPointSize(17);//字体大小
	pText->setFont(font);//设置
	
	pText1 = new QLineEdit("input 1", this);//输入框1
	pText2 = new QLineEdit("input 2", this);//输入框2 
	pText3 = new QLineEdit("input 3", this);//输入框3 
	//三个输入框用于两个数比较  求公约数  求公倍数
	pText1->setMinimumHeight(50);//设置文本框最小高度
	pText2->setMinimumHeight(50);
	pText3->setMinimumHeight(50);

	QFont font1;
	font1.setPointSize(14);//字体大小
	pText1->setFont(font);//设置
	pText2->setFont(font);
	pText3->setFont(font);

	
	
	QWidget* pannel = new QWidget(this);//按键面板
	//按键面板栅格布局
	QGridLayout* pannelLayout = new QGridLayout(pannel);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			QPushButton* button = new QPushButton(buttons[i][j], pannel);
			
			button->setMinimumHeight(60);//设置按钮最小高度
			QFont font;
			font.setPointSize(12);//字体大小
			button->setFont(font);//设置
			pannelLayout->addWidget(button, i, j);
			
			//下面这行极其关键，将按钮的动作与自定义的按钮响应函数连接，使按钮坐标作为输入量传入函数按钮响应函数（ int row, int column）
			connect(button, &QPushButton::clicked, [=]() ->void{onKeyButtonClicked(i, j); });//connect函数连接按钮响应的函数 格式为: 按钮，动作，函数
		}                                           //用lambda语法来响应 [](输入的参数)->返回类型{函数}
	}												//此处变量捕获列表为[=]按值捕获变量i,j
	pannelLayout->setMargin(0);//设置控件与窗体的左右边距
	pannelLayout->setSpacing(5);//设置各个控件之间的上下间距
	pannel->setLayout(pannelLayout);
	
	//文本框和按键面板竖直布局组合
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(pText);//加文本框
	layout->addWidget(pText1);
	layout->addWidget(pText2);
	layout->addWidget(pText3);
	layout->addWidget(pannel);//加按键面板
	setLayout(layout);
	
}


//============================ 按钮响应设置===============================================================

int flag = 0;//用于判断按下等号时 ，执行函数计算、四则运算等不同运算

void UI::onKeyButtonClicked(int row, int column)//按钮响应的函数
{
	QString Text = pText->text();
	QString Text1 = pText1->text();
	QString Text2 = pText2->text();
	QString Text3 = pText3->text();
	
	if (buttons[row][column] == "CE")
	{
		Text = "";
		Text1 = "input 1";
		Text2 = "input 2";
		Text3 = "input 3";
		pText->setText(Text);//返回新的文本
		pText1->setText(Text1);
		pText2->setText(Text2);
		pText3->setText(Text3);
		flag = 0;
	}
	else if(buttons[row][column] == "<-")
	{
		if (Text != "")
		{
			Text.remove(Text.length() - 1, 1);
			pText->setText(Text);//返回新的文本
		}
	}
	else if (buttons[row][column] == "sin")//三角函数sin flag=1
	{	
		flag = 1;
		Text += buttons[2][0];
		Text += buttons[5][0];//输出  "sin（"
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "cos")//三角函数cos flag=2
	{
		flag = 2;
		Text += buttons[3][0];
		Text += buttons[5][0];//输出  "cos（"
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "ln")//对数函数ln flag=3
	{
		flag = 3;
		Text += buttons[1][0];
		Text += buttons[5][0];//输出  "ln（"
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "e^x")//幂函数e^x flag=4
	{
		flag = 4;
		Text = "e^(";//输出  "e^（"
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "a/x=b")// flag=5 反比例函数
	{
		flag = 5;
		Text = "a/x=b,please input A and B in input 1 and input 2  ";//输出提示
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "ax^2+bx+c=0")// flag=6 一元二次方程
	{
		flag = 6;
		Text = "ax^2+bx+c=0,please input A and B and Cin input 1,2,3  ";//输出
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "ax+b=0")// flag=7 一元一次方程
	{
		flag = 7;
		Text = "Ax+B=0,please input A and B in input 1 and input 2  ";//输出提示
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "Binary")// flag=8 输入二进制
	{
		flag = 8;
		Text = "please write a Binary number in input 1 ";
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "Octal")// flag=9 输入八进制
	{
		flag = 9;
		Text = "please write a Octal number in input 1   ";
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "Decimal")// flag=10 输入十进制
	{
		flag = 10;
		Text = "please write a Decimal number in input 1   ";
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "Hexadecimal")// flag=11 输入十六进制
	{
		flag = 11;
		Text = "please write a Hexadecimal number in input 1   ";
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "compare")// flag=12 比较两个数大小
	{
		flag = 12;
		Text = "please write the two number to compare  in input 1 and input 2,must write B or O or D or H before each number ";
		pText->setText(Text);//返回新的文本
	}
	else if (buttons[row][column] == "divisor")// 最大公约数 flag=13
	{
		flag = 13;
		Text = "the greatest common divisor,please input A and B in input 1 and input 2 ";
		pText->setText(Text);//返回新的文本

	}
	
	else if (buttons[row][column] == "multiple")// flag=14
	{
		flag = 14;
		Text = "least common multiple,please input A and B in input 1 and input 2";//输出  "least common multiple:   "
		pText->setText(Text);//返回新的文本
	}


	else if (buttons[row][column] == "a^b")// flag=15 a^b
	{
	flag = 15;
	Text = "a^b,please input A and B in input 1 and input 2";//输出
	pText->setText(Text);//返回新的文本
	}


	//===========================================================================================================

	//===================================判断，按下的按钮是不是"=",若是则执行计算================================
	else if (buttons[row][column] == "=") 
	{
		if(flag==0)//四则运算的情况
		{
			double result;
			std::string str;
			std::tie(result, str) = parseExpression(Text.toLatin1().data());
			Text = QString::number(result);//double变成QString
			pText->setText(Text);//返回新的文本
		}
		else if(flag==1)//sin()
		{ 
			QString E;
			E = Text.mid(3);//用QString的mid函数截取第3位 与 末尾 之间的信息，存储到E中
			double result;
			std::string str;
			std::tie(result, str) = parseExpression(E.toLatin1().data());//计算出sin（E）中的E的值
			result = sin(result);//计算sin（E）的值
			Text = QString::number(result);//double变成QString
			pText->setText(Text);//返回新的文本
			flag = 0;//flag归零;
		}
		else if (flag == 2)//cos()
		{
			QString E;
			E = Text.mid(3);//用QString的mid函数截取第3位 与 末尾 之间的信息，存储到E中
			double result;
			std::string str;
			std::tie(result, str) = parseExpression(E.toLatin1().data());//计算出cos（E）中的E的值
			result = cos(result);//计算cos（E）的值
			Text = QString::number(result);//double变成QString
			pText->setText(Text);//返回新的文本
			flag = 0;//flag归零;
		}
		else if (flag == 3)//ln()
		{
			QString E;
			E = Text.mid(2);//用QString的mid函数截取第2位 与 末尾 之间的信息，存储到E中
			double result;
			std::string str;
			std::tie(result, str) = parseExpression(E.toLatin1().data());//计算出ln（E）中的E的值
			result = log(result);//计算ln（E）的值
			Text = QString::number(result);//double变成QString
			pText->setText(Text);//返回新的文本
			flag = 0;//flag归零;
		}
		else if (flag == 4)//e^(x)
		{
			QString E;
			E = Text.mid(2);//用QString的mid函数截取第2位 与 末尾 之间的信息，存储到E中
			double result;
			std::string str;
			std::tie(result, str) = parseExpression(E.toLatin1().data());//计算出e^（E）中的E的值
			result = exp(result);//计算e^（E）的值
			Text = QString::number(result);//double变成QString
			pText->setText(Text);//返回新的文本
			flag = 0;//flag归零;
		}
		else if (flag == 5)//反比例函数
		{ 
			double a, b;
			double c;
			std::string str1, str2;
			std::tie(a, str1) = parseExpression(Text1.toLatin1().data());
			std::tie(b, str2) = parseExpression(Text2.toLatin1().data());
			if ((a == 0 && b != 0) || (b == 0 && a != 0))//无解的情况
			{
				Text = "error! no answer ";
			}
			else if (a == 0 && b == 0)//x！=0的情况
			{
				Text = " x can be any value,but x != 0 ";
			}
			else//正常情况
			{
				c = a / b;
				QString temp;
				Text = "x = ";
				temp = QString::number(c);//c的类型变成QString
				Text += temp;//在现有文本基础上添加刚才按的按钮的内容
			}
			pText->setText(Text);//返回新的文本

		}
		else if (flag == 6)//flag=6 一元二次方程
		{
			double a, b,c;
			double delta,answer1,answer2;
			std::string str1, str2,str3;
			std::tie(a, str1) = parseExpression(Text1.toLatin1().data());
			std::tie(b, str2) = parseExpression(Text2.toLatin1().data());
			std::tie(c, str3) = parseExpression(Text3.toLatin1().data());
			delta = b * b - 4 * a * c;
			if (delta < 0) //无实数解的情况
			{
				Text = "There are no real roots";
			}
			else//求根格式正常求
			{
				delta = sqrt(delta);
				answer1 = (-b + delta) / (2 * a);
				answer2 = (-b - delta) / (2 * a);
				Text = "x1 = ";
				QString temp;
				temp = QString::number(answer1);//double变成QString
				Text += temp;//在现有文本基础上添加刚才按的按钮的内容
				Text += "   x2 = ";
				temp = QString::number(answer2);//double变成QString
				Text += temp;//在现有文本基础上添加刚才按的按钮的内容
			}
		pText->setText(Text);//返回新的文本
		}
		
		else if (flag == 7)//flag=7 一元一次方程 
		{
			double a, b;
			double c;
			std::string str1, str2;
			std::tie(a, str1) = parseExpression(Text1.toLatin1().data());
			std::tie(b, str2) = parseExpression(Text2.toLatin1().data());
			if (a == 0 && b == 0)
			{
				Text = "x can be any value";
			}
			else if (a == 0 && b != 0)
			{
				Text = "error!!!  A can not be \"0\" ";
			}
			else
			{
				c = b / a * (-1);
				QString temp;
				Text = "x = ";
				temp = QString::number(c);//c的类型变成QString
				Text += temp;//在现有文本基础上添加刚才按的按钮的内容

			}
			pText->setText(Text);//返回新的文本
		}
		else if (flag == 8)  //二进制转其他
		{
			bool Y;
			int ten;

			Text = "B: ";
			QString temp = QString::number(ten, 2); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "O: ";
			temp = QString::number(ten, 8); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "D: ";
			temp = QString::number(ten, 10); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "H: ";
			temp = QString::number(ten, 16); //常整形转换为Qstring形
			Text += temp;
			pText->setText(Text);//返回新的文本
			
		}     
		else if (flag == 9)  //八进制转其他
		{
			bool Y;
			int ten = Text1.toInt(&Y, 8);

			Text = "B: ";
			QString temp = QString::number(ten, 2); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "O: ";
			temp = QString::number(ten, 8); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "D: ";
			temp = QString::number(ten, 10); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "H: ";
			temp = QString::number(ten, 16); //常整形转换为Qstring形
			Text += temp;
			pText->setText(Text);//返回新的文本
		}     
		else if (flag == 10)//十进制转其他
		{
			bool Y;
			int ten = Text1.toInt(&Y, 10);
			Text = "B: ";
			QString temp = QString::number(ten, 2); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "O: ";
			temp = QString::number(ten, 8); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "D: ";
			temp = QString::number(ten, 10); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "H: ";
			temp = QString::number(ten, 16); //常整形转换为Qstring形
			Text += temp;
			pText->setText(Text);//返回新的文本
		}     
		else if (flag == 11) //十六进制转其他 
		{
			
			bool Y;
			int ten = Text1.toInt(&Y, 16);
			
			Text = "B: ";
			QString temp = QString::number(ten, 2); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "O: ";
			temp = QString::number(ten, 8); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "D: ";
			temp = QString::number(ten, 10); //常整形转换为Qstring形
			Text += temp;
			Text += "    ";
			Text += "H: ";
			temp = QString::number(ten, 16); //常整形转换为Qstring形
			Text += temp;
			pText->setText(Text);//返回新的文本

		}    
		else if (flag == 12)//compare 
		{
			int a, b;
			std::string str;
			str = Text1.toStdString();
			std::string first(str,0, 1);

			std::string s(str, 1, str.length() - 1);
			Text1 = QString::fromStdString(s);
			//QString B = "B", O = "O", D = "D", H = "H";
			bool Y;
			if (first == "B")
			{
				a=Text1.toInt(&Y, 2);
			}
			else if (first == "O")
			{
				a=Text1.toInt(&Y, 8);
			}
			else if (first == "D")
			{
				a=Text1.toInt(&Y, 10);
			}
			else if (first == "H")
			{
				a=Text1.toInt(&Y, 16);
			}
		
			str = Text2.toStdString();
			std::string first2(str, 0,1);
			std::string s2(str, 1, str.length() - 1);
			Text2 = QString::fromStdString(s2);
			if (first2 == "B")
			{
				b=Text2.toInt(&Y, 2);
			}
			else if (first2 == "O")
			{
				b=Text2.toInt(&Y, 8);
			}
			else if (first2 == "D")
			{
				b=Text2.toInt(&Y, 10);
			}
			else if (first2 == "H")
			{
				b=Text2.toInt(&Y, 16);
			}
			if (a > b) 
			{
				Text = "input 1 > input 2";
			}
			else if (a == b)
			{
				Text = "input 1 = input 2";
			}
			else
			{
				Text = "input 1 < input 2";
			}
			pText->setText(Text);//返回新的文本
		}     


		else if (flag == 13)//求最大公约数
		{
			Text = "greatest common divisor:  ";//输出
			Text1 = pText1->text();//获得输入框1和2内的内容
			Text2 = pText2->text();

			int a, b;
			std::string str1, str2;
			std::tie(a, str1) = parseExpression(Text1.toLatin1().data());
			std::tie(b, str2) = parseExpression(Text2.toLatin1().data());
		////////////////////////////此处为求最大公约数的函数代码，因调用求最大公约数函数一直报错////////
		////////////////////////////将函数代码直接写在了按钮响应函数内部,实在是无可奈何之举，有待改进///
			int min, max,result;
			int r;
			max = a > b ? a : b;
			min = a < b ? a : b;
			if (max % min == 0)
				result = min;
			else
			{
				while (max % min != 0)
				{
					r = max % min;
					max = min;
					min = r;
				}
					result = min;
			}
			
			QString temp;
			temp = QString::number(result);//int变成QString
			Text += temp;//在现有文本基础上添加刚才按的按钮的内容
			pText->setText(Text);//返回新的文本
		}

		else if (flag == 14)//求最小公倍数
		{
			Text = "least common multiple:  ";//输出  "least common multiple:   "
			Text1 = pText1->text();//获得输入框1和2内的内容
			Text2 = pText2->text();

			int a, b;
			std::string str1, str2;
			std::tie(a, str1) = parseExpression(Text1.toLatin1().data());
			std::tie(b, str2) = parseExpression(Text2.toLatin1().data());
		////////////////////////////此处为求最小公倍数的函数代码，因调用求最小公倍数函数一直报错////////
		////////////////////////////将函数代码直接写在了按钮响应函数内部,实在是无可奈何之举，有待改进///
			int min, max, r, result;
			max = a > b ? a : b;
			min = a < b ? a : b;
			if (max % min == 0)
				result = max;
			else
			{
				while (max % min != 0)
				{
					r = max % min;
					max = min;
					min = r;
				}
				result = a * b / min;
			}
		
			QString temp;
			temp = QString::number(result);//int变成QString
			Text += temp;//在现有文本基础上添加刚才按的按钮的内容
			pText->setText(Text);//返回新的文本
		}


		else if (flag == 15)//a^b
		{
			double a, b;
			double answer;
			std::string str1, str2;
			std::tie(a, str1) = parseExpression(Text1.toLatin1().data());
			std::tie(b, str2) = parseExpression(Text2.toLatin1().data());
			answer = pow(a, b);
			Text = "";
			QString temp;
			temp = QString::number(a);//double变成QString
			Text += temp;//在现有文本基础上添加刚才按的按钮的内容
			Text += " ^ ";
			temp = QString::number(b);//double变成QString
			Text += temp;//在现有文本基础上添加刚才按的按钮的内容
			Text += "  =  ";
			temp = QString::number(answer);//double变成QString
			Text += temp;//在现有文本基础上添加刚才按的按钮的内容
			pText->setText(Text);//返回新的文本
		}
	}//等号的响应的定义到此结束

	else//输入四则运算表达式
	{
		Text += buttons[row][column];//在现有文本基础上添加刚才按的按钮的内容
		pText->setText(Text);//返回新的文本
	}
	
}

