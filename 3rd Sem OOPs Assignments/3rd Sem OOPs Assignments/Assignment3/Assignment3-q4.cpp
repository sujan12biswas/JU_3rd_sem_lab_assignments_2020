/*Write a function max (a, b) that will return the reference of larger value. Store the
returned information to x where x is a i) variable of type a or b, ii) variable
referring to type of a or b. In both the cases modify x. Check also the values of a
and b.*/
#include<iostream>
#include<iomanip>
using namespace std;
int m;
//Function to find max between two numbers
int& max(int &a, int &b)
{	if(a>b) m=a;
	else m=b;
	return m;
}	
int main()
{	int a,b,x1;
	cout<<"Enter a : ";
	cin>>a;
	cout<<"Enter b : ";
	cin>>b;
	x1=max(a,b);
	int& x2=max(a,b);
	cout<<x1<<"  "<<x2<<endl;
	return 0;
}