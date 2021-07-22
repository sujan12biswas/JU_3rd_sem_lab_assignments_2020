/*Create an APPLICANT class with application id (auto generated as last id +1),
name and score. Support must be there to receive applicant data, show applicant
details and to find out number of applicants.*/
#include<iostream>
#include<iomanip>
#include<string>
#include<cstdio>
#define MAX 100
using namespace std;
//class to implement APPLICANT according to the conditions givenin question
class APPLICANT
{	int ap_id;
	string n;
	string name[MAX];
	int score[MAX];
	int tot;
	public:
		APPLICANT()//constructor initializing application id
		{	ap_id=0;	}
		void Insert()//function to insert new record
		{	ap_id++;
			cout<<"Application ID:001900"<<ap_id<<endl;
			cout<<"Enter name: ";
			cin>>n;
			name[ap_id]=n;
			cout<<"Enter score: ";
			cin>>score[ap_id];
			tot=ap_id;
		}
		void Display()//function to display record of given application id
		{	int i;
			cout<<"Enter last digit of application id:";
			cin>>i;
			cout<<"\nApplication ID:\t001900"<<i;
			cout<<"\nName:\t";
			cout<<name[i];
			cout<<"\nScore:\t"<<score[i];
		}
		void Dis_Tot()//function to display total number of applicants 
		{	cout<<"Total applicant : "<<tot<<endl;	}
};
int main()
{	APPLICANT A;
	int c;
	char ch;
	do
	{	cout<<"1.Enter Applicant Details\n2.Display Applicant Details\n3.Display Number of Applicants\n";//menu-driven
		cin>>c;
		if(c==1)
		{	A.Insert(); 	}
		else if(c==2)
		{	A.Display();	}
		else if(c==3)
		{	A.Dis_Tot();	}
		else
		{	cout<<"Wrong Choice";	}
		cout<<"Want to perform more operations?(Y/N):";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	return 0;
}