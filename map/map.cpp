#include<iostream>
#include<stdlib.h>
#define STACK_INIT_SIZE 100  //存储空间初始分配量 
#define STACKINCREMENT 10  //存储空间增量
using namespace std;
typedef  struct
{
	int *base;  //栈底指针 ,构造前和销毁后都为NULL
	int *top;  //栈顶指针
	int stacksize ; //当前以分配的存储空间 
 } SqStack_OPND;
 
 
typedef  struct
{
	char *base;  //栈底指针 ,构造前和销毁后都为NULL
	char *top;  //栈顶指针
	int stacksize ; //当前以分配的存储空间 
 } SqStack_OPTR;
 
 
bool   InitStack_OPND(SqStack_OPND &s)
{
	//构造一个空栈
	s.base = (int*) malloc(STACK_INIT_SIZE * sizeof(int) ) ;
	if(!s.base)  return false;
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return true;
} 

bool   InitStack_OPTR(SqStack_OPTR &s)
{
	//构造一个空栈
	s.base = (char*) malloc(STACK_INIT_SIZE * sizeof(char) ) ;
	if(!s.base)  return false;
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return true;
} 


char  GetTop_OPTR(SqStack_OPTR &s )
{
	//若栈不为空,返回字符e ,否则返回数值0 
	char e;
	if(s.top == s.base)  return 0;
	e = *(s.top-1);
	return e;
}


char  GetTop_OPND(SqStack_OPND &s )
{
	//若栈不为空,返回字符e ,否则返回数值0 
	int e;
	if(s.top == s.base)  return 0;
	e = *(s.top-1);
	return e;
}


bool  Push_OPTR(SqStack_OPTR &s  , char e)
{
	//插入e为新的栈顶元素
	if(s.top - s.base > s.stacksize)	{   //栈满,追加存储空间 
		s.base = (char*) realloc(s.base  , (s.stacksize + STACKINCREMENT)  * sizeof(char) );
		if(!s.base) return false;
		s.top =  s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	 } //增加空间完毕 
	 
	 *s.top++ = e;
	 return true;
}


bool  Push_OPND(SqStack_OPND &s  , int e)
{
	//插入e为新的栈顶元素
	if(s.top - s.base > s.stacksize)	{   //栈满,追加存储空间 
		s.base = (int*) realloc(s.base  , (s.stacksize + STACKINCREMENT)  * sizeof(int) );
		if(!s.base) return false;
		s.top =  s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	 } //增加空间完毕 
	 
	 *s.top++ = e;
	 return true;
}


bool Pop_OPTR(SqStack_OPTR &s , char &e)
{
	//若栈不为空,删除s的栈顶元素,用e返回其值,并返回true , 否则返回false
	if(s.top == s.base)  return false;
	e = * --s.top;
	return  true; 
}


bool Pop_OPND(SqStack_OPND &s , int &e)
{
	//若栈不为空,删除s的栈顶元素,用e返回其值,并返回true , 否则返回false
	if(s.top == s.base)  return false;
	e = * --s.top;
	return  true; 
}


//定义两个工作栈
//用来寄存运算符的栈   :  OPTR
//用来寄存操作数或运算结果的栈   :  OPND
SqStack_OPTR OPTR ;
SqStack_OPND OPND ;

int e;  //接收栈顶元素 GetTop() 和 Pop()中用到

char Precede(char  e , char c)  //根据算符优先关系表,返回三个优先关系之一 
{
		//规定, e 为01 ,c 为 02
		int convert_e , convert_c; //将e 和 c 转换为数字在进行比较,方便代码书写和理解
		
		//对e 进行转换 
		switch(e)
		{
			case '+' : convert_e = 1 ;  break;
			case '-' : convert_e = 2 ;  break;	
			case '*' : convert_e = 3 ;  break;
			case '/' : convert_e = 4 ;  break;
			case '(' : convert_e = 5 ;  break;
			case ')' : convert_e = 6 ;  break;
			case '#' : convert_e = 7 ;  break;
		} 
		
		
		//对c 进行转换 
		switch(c)
		{
			case '+' : convert_c = 1 ;  break;
			case '-' : convert_c = 2 ;  break;	
			case '*' : convert_c = 3 ;  break;
			case '/' : convert_c = 4 ;  break;
			case '(' : convert_c = 5 ;  break;
			case ')' : convert_c = 6 ;  break;
			case '#' : convert_c = 7 ;  break;
		} 
		
		if(convert_e == 1 && convert_c == 1)  return '>';
		if(convert_e == 1 && convert_c == 2)  return '>';
		if(convert_e == 1 && convert_c == 3)  return '<';
		if(convert_e == 1 && convert_c == 4)  return '<';
		if(convert_e == 1 && convert_c == 5)  return '<';
		if(convert_e == 1 && convert_c == 6)  return '>';
		if(convert_e == 1 && convert_c == 7)  return '>';
		
		
		
		if(convert_e == 2 && convert_c == 1)  return '>';
		if(convert_e == 2 && convert_c == 2)  return '>';
		if(convert_e == 2 && convert_c == 3)  return '<';
		if(convert_e == 2 && convert_c == 4)  return '<';
		if(convert_e == 2 && convert_c == 5)  return '<';
		if(convert_e == 2 && convert_c == 6)  return '>';
		if(convert_e == 2 && convert_c == 7)  return '>';
		
		
		if(convert_e == 3 && convert_c == 1)  return '>';
		if(convert_e == 3 && convert_c == 2)  return '>';
		if(convert_e == 3 && convert_c == 3)  return '>';
		if(convert_e == 3 && convert_c == 4)  return '>';
		if(convert_e == 3 && convert_c == 5)  return '<';
		if(convert_e == 3 && convert_c == 6)  return '>';
		if(convert_e == 3 && convert_c == 7)  return '>';
		
		
		
		if(convert_e == 4 && convert_c == 1)  return '>';
		if(convert_e == 4 && convert_c == 2)  return '>';
		if(convert_e == 4 && convert_c == 3)  return '>';
		if(convert_e == 4 && convert_c == 4)  return '>';
		if(convert_e == 4 && convert_c == 5)  return '<';
		if(convert_e == 4 && convert_c == 6)  return '>';
		if(convert_e == 4 && convert_c == 7)  return '>';
		
		
		if(convert_e == 5 && convert_c == 1)  return '<';
		if(convert_e == 5 && convert_c == 2)  return '<';
		if(convert_e == 5 && convert_c == 3)  return '<';
		if(convert_e == 5 && convert_c == 4)  return '<';
		if(convert_e == 5 && convert_c == 5)  return '<';
		if(convert_e == 5 && convert_c == 6)  return '=';
		if(convert_e == 5 && convert_c == 7)  return '0';  //出现语法错误是返回字符0  因为 (  和 # 不允许相继出现 
		
		
		if(convert_e == 6 && convert_c == 1)  return '>';
		if(convert_e == 6 && convert_c == 2)  return '>';
		if(convert_e == 6 && convert_c == 3)  return '>';
		if(convert_e == 6 && convert_c == 4)  return '>';
		if(convert_e == 6 && convert_c == 5)  return '0';   // 不允许出现 ) ( 的形式 
		if(convert_e == 6 && convert_c == 6)  return '>';
		if(convert_e == 6 && convert_c == 7)  return '>'; 
		
		
		if(convert_e == 7 && convert_c == 1)  return '<';
		if(convert_e == 7 && convert_c == 2)  return '<';
		if(convert_e == 7 && convert_c == 3)  return '<';
		if(convert_e == 7 && convert_c == 4)  return '<';
		if(convert_e == 7 && convert_c == 5)  return '<';
		if(convert_e == 7 && convert_c == 6)  return '0';  //# 和 ( 不允许同时相继出现 
		if(convert_e == 7 && convert_c == 7)  return '=';
} //Precede

char theta;  // 在Precede()函数判出> 的情况下, 存放从OPTR中出栈的运算符

//返回运算结果  theta为操作数  a 和 b 为运算符左值 和 右值 
int  Operate(int a , char theta , int b)
{
	switch(theta)
	{
		case '+' : return a+b;
		case '-' : return a-b;
		case '*' : return a*b;
		case '/' : return a/b;
	}
} 

bool In(char c)
{
	switch(c)
	{
		case '+' :
		case '-' :
		case '*' :
		case '/' :
		case '(' :
		case ')' :
		case '#' : return true;
	}
	return false;
}



int  EvaluateExpression()   //int 是返回表达式运算后的最终结果 
{
	char c;
	InitStack_OPTR(OPTR);   Push_OPTR(OPTR , '#');
	InitStack_OPND(OPND);   c = getchar();
	
	while( c != '#' || GetTop_OPTR(OPTR) != '#')
	{
		if(!In(c)) 
		{
			
			Push_OPND(OPND , c-48); c =getchar();  //不是运算符则进栈 
		}
		else
		{
			switch( Precede(GetTop_OPTR(OPTR) , c) )
			{
				case '<':  //栈顶元素优先权低
				{
					Push_OPTR(OPTR , c) ; c = getchar(); break;
				} 
				
				case '=':  //脱括号并接收下一个字符
				{
					char x; //接收退栈后的值 
					Pop_OPTR(OPTR , x) ;  c = getchar(); break;
				} 
				
				case '>':  //退栈并将结果存入栈
				{
					int a ,b;
					Pop_OPTR(OPTR , theta);
					Pop_OPND(OPND , b); Pop_OPND(OPND ,a);
					Push_OPND(OPND , Operate(a ,theta ,b));
					break;
				} 
			}//switch
		}
	} //while
	return GetTop_OPND(OPND);
} 

int main()
{
	cout<<"输入表达式,得出运算结果,输入以#结束,输入完毕请按回车!"<<endl;
	int result = EvaluateExpression();
	cout<<"表达式结果为:"<<endl;
	cout<<result<<endl;
    int a;
    cin>>a;
	return 0;
}