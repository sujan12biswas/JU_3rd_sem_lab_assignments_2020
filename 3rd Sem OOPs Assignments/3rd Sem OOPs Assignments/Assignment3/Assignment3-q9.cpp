/*Design a class TIME which stores hour, minute and second. The class should
have the methods to support the following:
1. User may give the time value in 24-hour format.
2. User may give the time value in AM/PM format
3. Display the time in 24-hour format.
4. Display the time in AM/PM format.
5. User may like to add minute with a time value.*/
#include <iostream>
#include <iomanip>
using namespace std;
 
#define MAX 100
//class to store time in hours,mins,secs
class TIME
{	private:
		int hour, min, sec;
        	char ampm;
    	public:
        	void getTime();
        	void putTime();
};
//function to take time as input from user
void TIME::getTime()
{	int ch;	
	cout<<"Enter format(1 for 24-hr format or 2 for AM/PM format): " ;//option of format
	cin>>ch;
	if(ch==1)
	{	cout<<"Enter hours: ";
		cin>>hour;
		cout<<"Enter minutes: ";
		cin>>min;
		cout<<"Enter seconds: ";
		cin>>sec;
		ampm='h';
			}
	else if(ch==2)
	{	cout<<"Enter hours: ";
		cin>>hour;
		cout<<"Enter minutes: ";
		cin>>min;
		cout<<"Enter seconds: ";
		cin>>sec;
		cout<<"Enter AM/PM(a for AM/p for PM): ";
		cin>>ampm;	}
	else
		cout<<"Wrong format!!";
}
//function to display time
void TIME::putTime()
{	int ch;	
	cout<<"Display format(1 for 24-hr format or 2 for AM/PM format):";//option of format
	cin>>ch;
	if(ch==1)
	{	if(ampm=='a')
		{	cout << "Time: ";
    			cout <<hour<<":"<<min<<":"<<sec<<" ";	
    		}
    		else if(ampm=='p')
		{	cout << "Time: ";
    			cout <<(hour+12)<<":"<<min<<":"<<sec<<" ";	
    		}
    		else
    		{	cout << "Time: ";
    			cout <<hour<<":"<<min<<":"<<sec<<" ";
    		}	
    	}
	else if(ch==2)
	{	if(ampm=='a')
		{	cout << "Time: ";
    			cout <<hour<<":"<<min<<":"<<sec<<" "<<"AM";	
    		}
    		else if(ampm=='p')
		{	cout << "Time: ";
    			cout <<hour<<":"<<min<<":"<<sec<<" "<<"PM";	
    		}
    		else
    		{	if(hour<=12)
    			{	cout << "Time: ";
    				cout <<hour<<":"<<min<<":"<<sec<<" ";
    			}
    			else
    			{	cout << "Time: ";
    				cout <<(hour-12)<<":"<<min<<":"<<sec<<" ";
    			}
    		}	
    	}
	else
		cout<<"Wrong format!!";
}
 
int main()
{	TIME t[MAX];
	int i;
	char ch;
	i=0;
    	do
    	{	t[i].getTime();
    		cout<<"Want to enter more?(Y/N)";
    		cin>>ch;
    		i++;
    		if(ch=='Y'||ch=='y') continue;
    		else break;
    	} while(1);
     	cout<<endl;
        int n;
        n=i;
        i=0;
    	do
    	{	cout <<endl<< "Details of student " << (i+1) << ":\n";
		t[i].putTime();
		i++;
    	}while(i<n);
     
    return 0;
}