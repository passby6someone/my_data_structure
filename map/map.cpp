#include<iostream>
#include<stdlib.h>
#define STACK_INIT_SIZE 100  //�洢�ռ��ʼ������ 
#define STACKINCREMENT 10  //�洢�ռ�����
using namespace std;
typedef  struct
{
	int *base;  //ջ��ָ�� ,����ǰ�����ٺ�ΪNULL
	int *top;  //ջ��ָ��
	int stacksize ; //��ǰ�Է���Ĵ洢�ռ� 
 } SqStack_OPND;
 
 
typedef  struct
{
	char *base;  //ջ��ָ�� ,����ǰ�����ٺ�ΪNULL
	char *top;  //ջ��ָ��
	int stacksize ; //��ǰ�Է���Ĵ洢�ռ� 
 } SqStack_OPTR;
 
 
bool   InitStack_OPND(SqStack_OPND &s)
{
	//����һ����ջ
	s.base = (int*) malloc(STACK_INIT_SIZE * sizeof(int) ) ;
	if(!s.base)  return false;
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return true;
} 

bool   InitStack_OPTR(SqStack_OPTR &s)
{
	//����һ����ջ
	s.base = (char*) malloc(STACK_INIT_SIZE * sizeof(char) ) ;
	if(!s.base)  return false;
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return true;
} 


char  GetTop_OPTR(SqStack_OPTR &s )
{
	//��ջ��Ϊ��,�����ַ�e ,���򷵻���ֵ0 
	char e;
	if(s.top == s.base)  return 0;
	e = *(s.top-1);
	return e;
}


char  GetTop_OPND(SqStack_OPND &s )
{
	//��ջ��Ϊ��,�����ַ�e ,���򷵻���ֵ0 
	int e;
	if(s.top == s.base)  return 0;
	e = *(s.top-1);
	return e;
}


bool  Push_OPTR(SqStack_OPTR &s  , char e)
{
	//����eΪ�µ�ջ��Ԫ��
	if(s.top - s.base > s.stacksize)	{   //ջ��,׷�Ӵ洢�ռ� 
		s.base = (char*) realloc(s.base  , (s.stacksize + STACKINCREMENT)  * sizeof(char) );
		if(!s.base) return false;
		s.top =  s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	 } //���ӿռ���� 
	 
	 *s.top++ = e;
	 return true;
}


bool  Push_OPND(SqStack_OPND &s  , int e)
{
	//����eΪ�µ�ջ��Ԫ��
	if(s.top - s.base > s.stacksize)	{   //ջ��,׷�Ӵ洢�ռ� 
		s.base = (int*) realloc(s.base  , (s.stacksize + STACKINCREMENT)  * sizeof(int) );
		if(!s.base) return false;
		s.top =  s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	 } //���ӿռ���� 
	 
	 *s.top++ = e;
	 return true;
}


bool Pop_OPTR(SqStack_OPTR &s , char &e)
{
	//��ջ��Ϊ��,ɾ��s��ջ��Ԫ��,��e������ֵ,������true , ���򷵻�false
	if(s.top == s.base)  return false;
	e = * --s.top;
	return  true; 
}


bool Pop_OPND(SqStack_OPND &s , int &e)
{
	//��ջ��Ϊ��,ɾ��s��ջ��Ԫ��,��e������ֵ,������true , ���򷵻�false
	if(s.top == s.base)  return false;
	e = * --s.top;
	return  true; 
}


//������������ջ
//�����Ĵ��������ջ   :  OPTR
//�����Ĵ����������������ջ   :  OPND
SqStack_OPTR OPTR ;
SqStack_OPND OPND ;

int e;  //����ջ��Ԫ�� GetTop() �� Pop()���õ�

char Precede(char  e , char c)  //����������ȹ�ϵ��,�����������ȹ�ϵ֮һ 
{
		//�涨, e Ϊ01 ,c Ϊ 02
		int convert_e , convert_c; //��e �� c ת��Ϊ�����ڽ��бȽ�,���������д�����
		
		//��e ����ת�� 
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
		
		
		//��c ����ת�� 
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
		if(convert_e == 5 && convert_c == 7)  return '0';  //�����﷨�����Ƿ����ַ�0  ��Ϊ (  �� # ��������̳��� 
		
		
		if(convert_e == 6 && convert_c == 1)  return '>';
		if(convert_e == 6 && convert_c == 2)  return '>';
		if(convert_e == 6 && convert_c == 3)  return '>';
		if(convert_e == 6 && convert_c == 4)  return '>';
		if(convert_e == 6 && convert_c == 5)  return '0';   // ��������� ) ( ����ʽ 
		if(convert_e == 6 && convert_c == 6)  return '>';
		if(convert_e == 6 && convert_c == 7)  return '>'; 
		
		
		if(convert_e == 7 && convert_c == 1)  return '<';
		if(convert_e == 7 && convert_c == 2)  return '<';
		if(convert_e == 7 && convert_c == 3)  return '<';
		if(convert_e == 7 && convert_c == 4)  return '<';
		if(convert_e == 7 && convert_c == 5)  return '<';
		if(convert_e == 7 && convert_c == 6)  return '0';  //# �� ( ������ͬʱ��̳��� 
		if(convert_e == 7 && convert_c == 7)  return '=';
} //Precede

char theta;  // ��Precede()�����г�> �������, ��Ŵ�OPTR�г�ջ�������

//����������  thetaΪ������  a �� b Ϊ�������ֵ �� ��ֵ 
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



int  EvaluateExpression()   //int �Ƿ��ر��ʽ���������ս�� 
{
	char c;
	InitStack_OPTR(OPTR);   Push_OPTR(OPTR , '#');
	InitStack_OPND(OPND);   c = getchar();
	
	while( c != '#' || GetTop_OPTR(OPTR) != '#')
	{
		if(!In(c)) 
		{
			
			Push_OPND(OPND , c-48); c =getchar();  //������������ջ 
		}
		else
		{
			switch( Precede(GetTop_OPTR(OPTR) , c) )
			{
				case '<':  //ջ��Ԫ������Ȩ��
				{
					Push_OPTR(OPTR , c) ; c = getchar(); break;
				} 
				
				case '=':  //�����Ų�������һ���ַ�
				{
					char x; //������ջ���ֵ 
					Pop_OPTR(OPTR , x) ;  c = getchar(); break;
				} 
				
				case '>':  //��ջ�����������ջ
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
	cout<<"������ʽ,�ó�������,������#����,��������밴�س�!"<<endl;
	int result = EvaluateExpression();
	cout<<"���ʽ���Ϊ:"<<endl;
	cout<<result<<endl;
    int a;
    cin>>a;
	return 0;
}