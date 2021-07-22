/*Create a class for linked list. Consider a separate class NODE for basic node
activities and use it in class for linked list.*/
#include <iostream>
using namespace std;
class Node
{
	private:
    		int data;
    		Node *next;
	public:
    		Node(int num)//creates new node
    		{
    			data = num;
    			next = nullptr;
		}
    		int getData()//returns the data of the node
    		{	return data;   }
    		Node *getNext()//returns reference of next node
    		{	return next;	}
    		void setNext(Node *ptr)//sets next node
    		{	next = ptr;	}
};
class LinkedList
{
	private:
    		Node *head;
	public:
    		LinkedList()
		{	head = nullptr;	}
    		~LinkedList()//destructor to free memory
    		{
    			while (!isEmpty())
    			{
        			Node *temp = head->getNext();
        			delete head;
        			head = temp;
    			}
    		}
    		void pushFront(int n)//function to push element in list
    		{
    			Node *temp = new Node(n);
    			temp->setNext(head);
    			head = temp;
    		}
    		void display()//function to display list
    		{
    			if (isEmpty())
        			cout << "List is Empty";
			Node *temp = head;
    			while (temp != nullptr)
    			{
        			cout << temp->getData() << " ";
        			temp = temp->getNext();
    			}
    			cout << endl;
    		}
    		bool isEmpty()//to check if list is empty
    		{	return head == nullptr;	}
};

int main()
{
    LinkedList list;
    cout<<"Add in list:";
    for(int i=0;i<10;i++)
    {	int num;
    	cin>>num;
    	list.pushFront(num);
    }
    list.display();
}