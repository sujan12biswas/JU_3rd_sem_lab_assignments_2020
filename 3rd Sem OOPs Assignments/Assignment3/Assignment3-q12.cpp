/*Design a STUDENT class to store roll, name, course, admission date and marks
in 5 subjects. Provide methods corresponding to admission (marks are not
available then), receiving marks and preparing mark sheet. Support must be
there to show the number of students who have taken admission.*/
#include <iostream>
using namespace std;
//structure to store date in dd-mm-yyyy format
struct DOA
{
    int dd;
    int mm;
    int yy;
};
//class implementing STUDENT with required data members and functions
class STUDENT
{
	private:
    		int roll;
    		char name[50];
    		char course[100];
    		int marks[5];
    		DOA d;
	public:
    		void get_data();
    		void get_marks();
    		void show_data();
};
//function to input data
void STUDENT :: get_data()
{
    cout<<"Enter the roll:"<<endl;
    cin>>roll;
    cout<<"Enter the name:"<<endl;
    cin.ignore();
    cin.getline(name,50);
    cout<<"Enter the course:"<<endl;
    cin.getline(course,100);
    cout<<"Enter admission date in dd mm yyyy format"<<endl;
    cin>>d.dd>>d.mm>>d.yy;
}
//function to take marks of 5 subjects
void STUDENT :: get_marks()
{
    cout<<"Enter the marks of the five subjects:"<<endl;
    for(int i=0;i<5;i++)cin>>marks[i];
}
//function to display all data
void STUDENT::show_data()
{
        cout("%d\t%s\t\t%s\t\t%d-%d-%d\t%d\t%d\t%d\t%d\t%d\n",roll, name, course,d.dd,d.mm,d.yy,
            marks[0],marks[1],marks[2],marks[3],marks[4] );
}

int main()
{
    STUDENT s[100];
     int i=0;
    int choice;
  do
    {
        cout<<endl<<"1.Create a student data\n"<<endl;
        cout<<"2.Get a student marks\n"<<endl;
        cout<<"3.Display the records"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<endl<<"Please select your choice (1-4): "<<endl;
        cin>>&choice;

        switch (choice)
        {
            case 1:
                {
                    i++;
                    s[i].get_data();

                }
                 break;
            case 2:
                    s[i].get_marks();
                 break;
            case 3:
                {
                     cout<<endl<<"ALL STUDENTS RESULT "<<endl;
    cout<<"============================================================================================="<<endl;
    cout<<"R.No.\tName\t\tCourse\t\tDOA\t\tSub1\tSub2\tSub3\tSub4\tSub5"<<endl;
    cout<<"============================================================================================="<<endl;
                    for(int p=i;p>0;p--){
                        s[p].show_data();
                }
                    break;
    }
}while (choice != 4);
}
