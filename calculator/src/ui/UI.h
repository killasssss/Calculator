#include <QDialog>
#include <QLineEdit>

class UI : public QDialog
{
private:
	QLineEdit* pText;//文本框的指针
	QLineEdit* pText1;//文本框1的指针
	QLineEdit* pText2;//文本框2的指针
	QLineEdit* pText3;//文本框3的指针

	QString buttons[6][6] =
	{
		{"compare" ,  "divisor",  "multiple" ,  "Binary"     ,"Octal"   ,  "Decimal"             },
	    {"ln"      ,  "CE"     ,  "a^b"        ,  "<-"       ,"/"       ,  "Hexadecimal"         },
		{"sin"     ,  "7"      ,  "8"        ,  "9"          ,"*"       ,  "ax+b=0"              },
		{"cos"     ,  "4"      ,  "5"        ,  "6"          ,"-"       ,  "ax^2+bx+c=0"         },
		{" "       ,  "1"      ,  "2"        ,  "3"          ,"+"       ,  "a/x=b"               },
		{"("       ,  ")"      ,  "0"        ,  "."          ,"="       ,  "e^x"                 },
	};


	void onKeyButtonClicked(int row, int column);//按钮响应
	
	
public:
	UI(QWidget* parent = nullptr);//构造函数	
	
	int MaxDivisor(int a, int b);//求最大公约数
	
}; 



