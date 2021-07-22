/*Write a macro to find the maximum of two numbers. Call the macro with i) two
integers as the arguments and ii) two char * as the arguments. Observe the
outcomes.*/
#include<iostream>
#include<string>
#include<iomanip>
#define MAX(a,b) ((a>b)?a:b)
using namespace std;
int main()
{	int a,b;
	string c,d;
	a=10;   b=20;
	c="Sujan";   d="Biswas";
	cout<<MAX(a,b)<<endl;
	cout<<MAX(c,d);
	return(0);
}