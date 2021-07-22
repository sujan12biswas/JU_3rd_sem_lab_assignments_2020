/*For each student roll, name and phone number are to be maintained. For each
subject store subject code, name. A student may choose number of subjects
from a list of subjects. A subject may be chosen by number of students. Given a
roll number system must able to display the subjects chosen by the student and

also be able to display the students corresponding to a subject code. Design the
classes and implement the system.*/
#include<iostream>
#define MAX_SIZE 100
using namespace std;
typedef long long ll; 

class SUBJECT;	//forward declaration of the class subject

class listOfStudents;


class listOfSubjects;
//designing the class student to hold the record of each stduent
class STUDENT {
	char name[31];
	int roll;
	ll phoneNumber;
	int numberOfSubjects;
	int subjectCodeList[MAX_SIZE];
public:
	STUDENT() { //default constructor to initialise the required
		numberOfSubjects = 0;
	}

	//function to get the student details
	void getStudentData() {
		cout << "Enter the roll number of the student --> ";
		cin >> roll;
		cout << "Enter the name of the stduent --> ";
		scanf(" %[^\n]s", name);
		cout << "Enter the phone number of the student --> ";
		cin >> phoneNumber;
	}

	//function to get the number of subjects seleted
	void selectSubject(listOfStudents&, listOfSubjects&); //will be defined later after knowing the attributes of the class SUBJECT

	//function to show the relevant student data
	void showStudentData() {
		cout << "Name of the student --> " << name << "\n";
		cout << "Roll Of the student --> " << roll << "\n";
		cout << "Phone Number of the student --> " << phoneNumber << "\n";
		cout << "Number Of Subjects Seelected --> " << numberOfSubjects << "\n";
	}

	//function to diplay the subject details
	void showSubjects(listOfSubjects&);
	//friend void listOfStudents::showByRoll(int r);
	friend class listOfStudents;
};

//designing the class list of students
class listOfStudents {
	int count;
	STUDENT arr[MAX_SIZE];
public:
	listOfStudents() { //default constructor used for initialising the count
		count = -1;
	}
	//function to check whether toll is present or no
	bool checkRoll(int r) {
		for (int i = 0; i <= count; i++)
			if (arr[i].roll == r)
				return true;
		return false;
	}
	//function to add student
	void addStudent(listOfSubjects&);

	//function to view students
	void showData(listOfSubjects&);

	//function to show students by roll
	void showByRoll(int , listOfSubjects&);
};

//designing the class subject to hold the subject details
class SUBJECT {
	int subCode;
	char subName[31];
	int nOfStudents;
	int studentRollList[MAX_SIZE];

public:
	SUBJECT() { //constructor to initialise the reuqired
		subCode = -1;
		nOfStudents = 0;
	}

	//function to return subject code
	int retSubjectCode() {
		return subCode;
	}

	//function to get the subject details
	void getSubjectData() {
		cout << "Enter the Subject Code --> ";
		cin >> subCode;
		cout << "Enter the Subject Name --> ";
		cin >> subName;
	}

	//function to show ths subject details
	void showSubjectData() {
		cout << "Subject Code --> " << subCode << "\n";
		cout << "Subject Name --> " << subName << "\n";
		cout << "Number of students enrolled for the subject --> " << nOfStudents << "\n";
	}

	//function to display the students assigned
	void showStudentAsgn(listOfStudents&, listOfSubjects&);

	//friend function declaration required to acess the private data members
	friend class listOfSubjects;
};

//designing the class list of students
class listOfSubjects {
	int count;
	SUBJECT arr[MAX_SIZE];

public:
	listOfSubjects() { //default constructor to initialise the count
		count = -1;
	}
	//function to add a subject
	void addSubject() {
		count++;
		arr[count].getSubjectData();
	}
	//function to check whether subject with the required code exists or not
	bool checkSubject(int scode) {
		for (int i = 0; i <= count; i++) {
			if (arr[i].subCode == scode)
				return true;
		}
		return false;
	}

	//function to show all the subjects
	void showAllSubjects(listOfStudents& obj) {
		cout << "Subjects Available --> \n";
		for (int i = 0; i <= count; i++) {
			arr[i].showSubjectData();
			arr[i].showStudentAsgn(obj, *this);
			cout << "-----------------------------------\n";
		}
	}

	//method to update the subject code
	void updateSubject(int scode, int roll) {
		for (int i = 0; i <= count; i++) {
			if (arr[i].subCode == scode) {
				arr[i].studentRollList[arr[i].nOfStudents] = roll;
				arr[i].nOfStudents++;
			}
		}
	}

	//function to display the data against a subject code
	SUBJECT showBysubCode(int scode) {
		SUBJECT s;
		for (int i = 0; i <= count; i++) {
			if (arr[i].subCode == scode) {
				arr[i].showSubjectData();
				return arr[i];
			}
		}
		return s;
	}

	//funtion to show all the subjects
	void displayAll() {
		for (int i = 0; i <= count; i++) {
			arr[i].showSubjectData();
			cout << "---------------------------------\n";
		}
	}
};

//-------------------------------------------------------------------------
void listOfStudents::addStudent(listOfSubjects& obj) {
	count++;
	arr[count].getStudentData();
	arr[count].selectSubject(*this, obj);
}

//function to view the students
void listOfStudents::showData(listOfSubjects& obj) {
	if (count == -1)	//no students enrolled so far
	{
		cout << "No Students Have Enrolled So Far !";
		return;
	}
	for (int i = 0; i <= count; i++) {
		arr[i].showStudentData();
		arr[i].showSubjects(obj);
	}
}

//function to return the student details by student roll number
void listOfStudents::showByRoll(int r, listOfSubjects& obj) {
	for (int i = 0; i <= count; i++) {
		if (arr[i].roll == r) { //if the given roll number matches then show the details
			arr[i].showStudentData();
			arr[i].showSubjects(obj);
		}
	}
}

//function to show students assigned under a subject
void SUBJECT::showStudentAsgn(listOfStudents& obj, listOfSubjects& obj1) {
	cout << "Students studying this subject --> \n";
	for (int i = 0; i < nOfStudents; i++) {
		obj.showByRoll(studentRollList[i], obj1);
	}
}


//--------------------------------------------------------------------------

//function to get the subjects selected for a student included with the subject code rechecking feature
void STUDENT::selectSubject(listOfStudents& obj1, listOfSubjects& obj) {
	//obj.showAllSubjects(obj1);
	obj.displayAll();
	cout << "Enter the number of subjects --> ";
	cin >> numberOfSubjects;
	for (int i = 0; i < numberOfSubjects;) {
		int scode;
		cout << "Enter the Subject Code of the " << i + 1 << "Subject --> ";
		cin >> scode;
		if (obj.checkSubject(scode) == false) { //invalid subject code entered
			cout << "Please Enter a Valid Subject Code !";
		}
		else { //update the subject list
			obj.updateSubject(scode, roll);
			subjectCodeList[i] = scode; //updating the subject code list
			i++;
		}
	}
}

//function to display the selected subject for a student
void STUDENT::showSubjects(listOfSubjects& obj) {
	cout << "Subjects Selected are --> ";
	for (int i = 0; i < numberOfSubjects; i++) {
		obj.showBysubCode(subjectCodeList[i]);
		cout << "------------------------------------\n";
	}
}
listOfSubjects l1;
listOfStudents l2;


int main() {
	SUBJECT s1;
	while (1) {
		cout << "1. add a subject\n2. add a student\n3. display subject details\n4. Display Student By Roll\n5. Display All Students\n6. Display All Subjects\n7. exit\n";
		int ch;
		cin >> ch;
		switch (ch) {
		case 1: l1.addSubject(); //function call to add a subject
			break;
		case 2: l2.addStudent(l1);	//function call to add a student in the list
			break;
		case 3:	int scode;	//to show the subject details and the stduents assigned under it
			cout << "Enter the subject Code --> ";
			cin >> scode;
			s1 = l1.showBysubCode(scode);
			if (s1.retSubjectCode() == -1) {	//subject to be searched not found
				cout << "Subject to be searched not found !";
			}
			else {	//subject to be searched found
				s1.showStudentAsgn(l2, l1);
			}
			break;
		case 4:	int roll; //to show the student by roll number
			cout << "Enter the Roll Number of the stdent to be searched -> ";
			cin >> roll;
			if (l2.checkRoll(roll) == false) {
				cout << "Roll fo the student to be searched not found !";
			}
			else
				l2.showByRoll(roll, l1);
			break;
		case 5:	//to show all the students of the class;
			l2.showData(l1);
			break;
		case 6:	 //to display all subjects
			l1.showAllSubjects(l2);
			break;
		case 7:	//to get out of the system
			exit(0);
		}
	}
	return 0;
}