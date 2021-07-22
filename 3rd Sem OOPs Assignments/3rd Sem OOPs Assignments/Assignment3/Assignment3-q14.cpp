/*Design the class(es) for the following scenario:
1.An item list contains item code, name, rate, and quantity for several
items.
2.Whenever a new item is added in the list uniqueness of item code is to be
checked.
3.Time to time rate of the items may change.
4.Whenever an item is issued or received existence of the item is checked
and quantity is updated.
5.In case of issue, availability of quantity is also to be checked.
6.User may also like to know price/quantity available for an item.*/
#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;
#define MAX_SIZE 100
class ITEM
{
private:
    int item_code;
    char name[31];
    int quantity;
    double price;

public:
    void getData();
    void showData()
    {
        cout << item_code << "\t\t" << name << "\t\t"
             << quantity << "\t\t" << price << "\n";
    }
    int getCode() const
    {
         return item_code;
    }
    void updateQuan(int q) { quantity += q; }
    void updateRate(double p) { price = p; }
    int getQuan() const { return quantity; }
    double getPrice() const { return price; }
};
void ITEM ::getData()
{
    cout << "Enter item code : ";
    cin >> item_code;
    cout << "Enter name of item : ";
    cin >> name;
    cout << "Enter available quantity of item : ";
    cin >> quantity;
    cout << "Enter price of item : ";
    cin >> price;
}
class ITEM_LIST
{
    static int totNum;
    ITEM list[MAX_SIZE];
    int verifyCode(int);
    bool checkQuan(int, int);

public:
    static int getTotal() { return totNum; }
    void getItemData();
    void changeRate(int);
    void IssueReceive(int);
    int retQuan(int ic)
    {
        int index = verifyCode(ic);
        return index == -1 ? -1 : list[index].getQuan();
    }
    double retPrice(int ic)
    {
        int index = verifyCode(ic);
        return index == -1 ? -1.00 : list[index].getPrice();
    }
    void displayAll()
    {
        cout << "Item Code\tItem Name\tQuantity\tRate\n";
        for (int i = 0; i < totNum; ++i)
            list[i].showData();
    }
};
int ITEM_LIST ::totNum = 0;
int main()
{
    cout.setf(ios ::fixed);
    cout.setf(ios ::showpoint);
    cout << setprecision(2);
    ITEM_LIST Il;
    int ch;
    do
    {
        cout << "Enter \n1 to add item, \n2 to change rate(price) of an item,"
             << " \n3 to issue/recieve an item, \n4 to check quantity of an item,"
             << " \n5 to know price of an item, \n0 to exit : ";
        cin >> ch;
        switch (ch)
        {
            int x, ic;
        case 1:
            cout << "Enter item details.\n";
            Il.getItemData();
            Il.displayAll();
            break;
        case 2:
            cout << "Enter item code : ";
            cin >> ic;
            Il.changeRate(ic);
            Il.displayAll();
            break;
        case 3:
            cout << "Enter item code : ";
            cin >> ic;
            Il.IssueReceive(ic);
            Il.displayAll();
            break;
        case 4:
            cout << "Enter item code : ";
            cin >> ic;
            cout << "The available quantity of item = " << Il.retQuan(ic) << endl;
            break;
        case 5:
            cout << "Enter item code : ";
            cin >> ic;
            cout << "The current price of the item = " << Il.retPrice(ic) << endl;
            break;
        default:
            if (ch)
                cout << "Wrong input.\n";
        }
    } while (ch);
    return 0;
}
int ITEM_LIST ::verifyCode(int ic)
{
    for (int i = 0; i < totNum; ++i)
    {
        if ((list + i)->getCode() == ic)
            return i;
    }
    return -1;
}
void ITEM_LIST ::getItemData()
{
    ITEM item;
    item.getData();
    if (verifyCode(item.getCode()) == -1)
    {
        list[totNum] = item;
        ++totNum;
        return;
    }
    cout << "Item with code " << item.getCode() << " is already present.\n";
}
void ITEM_LIST ::changeRate(int ic)
{
    int index = verifyCode(ic);
    if (index == -1)
    {
        cout << "Item does not exist.\n";
        return;
    }
    double newRate;
    cout << "Enter new price : ";
    cin >> newRate;
    list[index].updateRate(newRate);
}
bool ITEM_LIST ::checkQuan(int index, int q)
{
    return (list + index)->getQuan() >= q;
}
void ITEM_LIST ::IssueReceive(int ic)
{
    int index = verifyCode(ic);
    if (index == -1)
    {
        cout << "Item does not exist.\n";
        return;
    }
    int q;
    char ch;
    cout << "To issue item enter 'i', to recieve enter 'r' : ";
    cin >> ch;
    if (ch == 'i')
    {
        cout << "Enter quantity required to be issued: ";
        cin >> q;
        if (!checkQuan(index, q))
        {
            cout << "Only " << list[index].getQuan() << " items available.\n";
            return;
        }
        else
            list[index].updateQuan(-q);
    }
    else
    {
        cout << "Enter quantity received : ";
        cin >> q;
        list[index].updateQuan(q);
    }
    cout << "Quantity updated to " << list[index].getQuan() << endl;
}