/*Design a BALANCE class with account number, balance and date of last update.
Consider a TRANSACTION class with account number, date of transaction,
amount and transaction type (W for withdrawal and D for deposit). If it is a
withdrawal check whether the amount is available or not. Transaction object will
make necessary update in the BALANCE class.*/
#include<iostream>
using namespace std;

class BALANCE;
//class implementing date
class Date
{
    int dd;
    int mm;
    int yyyy;
    public:
    	Date()
    	{
        	dd = 1;
        	mm = 1;
        	yyyy = 2000;
    	}
    	Date(int d, int m, int y)
    	{
        	dd = d;
        	mm = m;
        	yyyy = y;
    	}
    friend class BALANCE;
};
class TRANSACTION;
//class implementing balance
class BALANCE
{
    int acno;
    float balance;
    Date last_update;
    public:
    	BALANCE(int acn, float b, Date dt)
    	{
        	acno = acn;
        	balance = b;
        	last_update = dt;
    	}
    void print_balance()
    {
        cout<<"Account No.: "<<acno<<"\nBalance: "<<balance<<"\nDate of Last Update: "<<last_update.dd<<"."<<last_update.mm<<"."<<last_update.yyyy<<endl;
    }

    friend class TRANSACTION;
};
//class implementing transaction
class TRANSACTION
{
    int acno;
    Date transac_date;
    float amt;
    char type;

    public:
    TRANSACTION(int acn, Date dt, float amount, char typ, BALANCE &balance)
    {
        int f = 0;
        if (typ == 'W')
        {
            if (balance.balance - amount < 0)
            {
                printf("Insufficient Balance to make transaction!");
                f = 1;
            }
            else
            {
                acno = acn;
                transac_date = dt;
                amt = amount;
                type = typ;

                balance.balance -= amount;
                balance.last_update = dt;
            }
        }
        else
        {
            acno = acn;
            transac_date = dt;
            amt = amount;
            type = typ;

            balance.balance += amount;
            balance.last_update = dt;
        }
    }
};

int main()
{
    Date date = Date(12, 12, 2001);
    BALANCE balance = BALANCE(3000, 2500, date);
    date = Date(30, 11, 2002);
    TRANSACTION(1000, date, 1000, 'W', balance);
    balance.print_balance();
    date = Date(20, 8,2003);
    TRANSACTION(1000, date, 1000, 'D', balance);
    balance.print_balance();
}