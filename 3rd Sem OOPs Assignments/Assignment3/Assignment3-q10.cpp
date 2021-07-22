/*Create a STACK class with operation for initialization, push and pop. Support for
checking underflow and overflow condition are also to be provided.*/
#include<iostream>
#include<iomanip>
#define MAX 100
using namespace std;
//class to implement stack
class STACK
{	int top ;
	public :
		int data[MAX];
		STACK() { top = -1; }
		void push( ) ;
		void pop( ) ;
		void display()
		{	for(int i=top;i>=0;i--)
			cout<<data[i]<<"\n";
		}
};
//function to push element in stack
void STACK::push()
{	if(top==99)
	{ 	cout<<"Overflow";
		return;
	}
	int X;
	cout<<"Enter the data:";
	cin>>X;
	top++;
	data[top]=X;
}
//function to pop element from stack
void STACK::pop()
{	if(top==-1)
	{ 	cout<<"Uderflow";
		return;
	}
	int X;
	X=data[top];
	top--;
	cout<<X<<"Removed";
}
int main()
{	STACK S;
	int ch;
	char c;
	do
	{	cout<<"1. Push \n2. Pop \n3.Display\n";
		cin>>ch;
		if(ch==1)
			S.push();
		else if(ch==2)
			S.pop();
		else if(ch==3)
			S.display();
		else
			cout<<"Wrong Choice";
		cout<<"Want to perform more operations?(Y/N)";
		cin>>c;
	}while(c=='Y'||c=='y');
	return 0;
}