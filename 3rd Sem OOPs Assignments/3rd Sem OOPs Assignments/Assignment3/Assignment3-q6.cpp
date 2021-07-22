/*Write a function void f(int) that prints “inside f(int)”. Call the function with actual
argument of type: i) int, ii) char, iii) float and iv) double. Add one more function
f(float) that prints “inside f(float)”. Repeat the calls again and observe the
outcomes.*/
#include<iostream>
#include<iomanip>
using namespace std;
//Two functions with same name showing overloading
void f(int x)
{	cout<<"Inside f(int)"<<endl;		}
void f(float x)
{	cout<<"Inside f(float)"<<endl;	}
int main()
{	int a;
	float b;
	char c;
	double d;
	cout<<"Enter int:";
	cin>>a;
	cout<<"Enter float:";
	cin>>b;
	cout<<"Enter char:";
	cin>>c;
	cout<<"Enter double:";
	cin>>d;
	f(a);f(b);f(c);f(d);
	return 0;
} 


