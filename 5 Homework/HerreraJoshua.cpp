/* Joshua Herrera
   Homework 4 */

#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;

string timestamp() {
	time_t result = time(nullptr);
	return asctime(localtime(&result));
}


class transaction {
	enum Type {credit = -1, debit = 1};
	string TimeStamp;

	
public:

	float Amount;
	transaction *next;
	
	transaction() {Amount = 0; next = 0;}

	float get_transaction() {return Amount;}
	string classify() {
		switch ((int)(Amount/fabs(Amount))) {
			case debit: return "debit   ";
			case credit: return "credit  "; }
	}
	

}; //End transaction


class account {
	
	int ID;
	string Name;
	string DateOpened;
	transaction *n = new transaction;
	transaction *init = n;
	transaction *temp = n;

//By default, the first transaction in all accounts will be a 0 placeholder transaction
	
public: 
	
	account() {}
	account(string name, string date, int id) {Name = name; ID = id; DateOpened = date;}
	
	//retrieve functions
	string account_name() {return Name;}
	float account_balance() {
		float balance = 0;
		transaction *i = init;
		while (i->next != 0) {
			i = i->next;
			balance+= i->Amount;
		}
		return balance;
	}
	
	void transactions_all() {
		transaction *i = init;
		while (i->next != 0) {
			i = i->next;
			cout << i->classify() << " " << fabs(i->Amount) << endl;
		}
	}
	
	//edit functions
	void trans(float amount) {
		n = new transaction;
		n->Amount = amount;
		n->next = 0;
		temp->next = n;
		temp = n;
	}
	
}; //End account


class customer {
	
	int ID;
	string Name;
	string Address;
	account Accounts[10];
	int nAccounts = 0;
	
public:
	
	customer() {cout << "MUST SPECIFY ID AND NAME" << endl;}
	customer(int id, string name) {ID = id; Name = name;}
	
	//retrieve functions
	int get_id() {return ID;}
	string get_name() {return Name;}
	string get_address() {return Address;}
	string get_account_name(int id) {return Accounts[id].account_name();}
	float get_account_balance(int id) {return Accounts[id].account_balance();}
	float get_balance() {
		float balance = 0;
		for (int i=0; i<=nAccounts; i++)
			balance+= Accounts[i].account_balance();
		return balance;
	}
	void list_transactions(int id) {Accounts[id].transactions_all();}
	
	
	//edit functions
	void transact(int accountid, float amount) {Accounts[accountid].trans(amount);}
	
	void new_account(string name, string date) {
		Accounts[nAccounts] = account(name, date, nAccounts);
		nAccounts++;
	}
	void new_account(string name, string date, float initial) {
		Accounts[nAccounts] = account(name, date, nAccounts);
		transact(nAccounts, initial);
		nAccounts++;
	}

}; //End customer


int main() {
	
	customer me(014227, "Joshua Herrera");
	me.new_account("Checking 1", timestamp(), 100);
	me.new_account("Savings 1", timestamp(), 100);
	
	cout << endl << "Checking 1 balance: ";
	cout << me.get_account_balance(0) << endl;

	me.transact(0, 10);
	me.transact(1, 10);
	
	me.transact(0, -50);
	
	cout << endl;
	me.list_transactions(0);
	
	cout << "Total balance: " << me.get_balance() << endl;
	
	return 0;
}