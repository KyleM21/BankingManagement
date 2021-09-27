#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include "bank.h"

using namespace std;

//This function gets the account information from the user and stores it
void account::create_account(){
	cout<<"\nEnter account number: ";
	while (true){
	    cin >> acno;
	    if (!cin){
			cout << "\nPlease only enter integers: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
	    }
	    else break;
  	}
	cout<<"\nPlease enter your full name: ";
	cin.ignore();
	cin.getline(name,50);
	
	cout<<"\nEnter C for a checking account, or S for a savings account (C/S)\nPlease note that Checking accounts have a 5$ minimum, Savings are 100$ minimum: ";
	while(true){
		cin >> type;
		type=toupper(type);
		if(type != 'C' && type != 'S'){
			cout << "\nPlease enter C or S for the account type, capitalization does not matter: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else break;
	}
	
	cout<<("\nEnter the initial ammount of money to be in the account: ");
	while (true){
	    cin >> balance;
	    if (!cin)
	    {
			cout << "\nPlease only enter integers: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
	    }
	    
	    if(balance<5 && type=='C'){
			cout << "\nPlease enter a number above $5: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else if(balance<1000 && type=='S'){
			cout << "\nPlease enter a number above $1,000: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else break;
  	}
  	
	cout<<"\nAccount Created successfully!";
}

//This function prints out the info of the account
void account::show_account() const{
	cout<<"\nAccount Noumber: "<<acno;
	cout<<"\nAccount Holder: "<<name;
	cout<<"\nAccount Type: "<<type;
	cout<<"\nAccount Balance:  "<<balance;
	
}

//This function lets the user modify account information
void account::modify(){
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>balance;
}

//This function handles depositing money into the account
void account::depo(float x){
	balance+=x;
}

//This function handles withdrawing money from the account
void account::withdraw(float x){
	balance-=x;
}

//This function prints out a report of the account
void account::report() const{
	cout<<"\nAccount Number: "<<acno;
	cout<<"\nAccount Holder: "<<name;
	cout<<"\nAccount Type: "<<type;
	cout<<"\nAccount Balance: "<<balance;
}

//This function gets the account number
float account::getAccount(){
	return acno;
}

//This function gets the account balance
float account::getBalance(){
	return balance;
}

////This function gets the account type
//char account::getType() const{
//	return type;
//}

void write_account();				//This function writes the account to the binary file
void display_ac(int);				//This function displays the account that corresponds to the given account number
void modify_account(int);			//This function modifies the account and writes it to the binary file
void delete_account(int);			//This function deletes the selected account
void display_all();					//This function displays every account
void deposit_withdraw(float, int); 	//This function will handle depositing/withdrawing money
void intro();						//This function displays the intro
float getNum();

//The main function displays the main menu and allows the user to select what they would like to do 
int main(){
	char ch;	
	int num = 0;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT";
		cout<<"\n\n\t03. WITHDRAW";
		cout<<"\n\n\t04. BALANCE";
		cout<<"\n\n\t05. LIST ALL ACCOUNTS";
		cout<<"\n\n\t06. CLOSE ACCOUNT";
		cout<<"\n\n\t07. MODIFY ACCOUNT INFO";
		cout<<"\n\n\t08. EXIT PROGRAM";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : ";
			num = getNum();
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : ";
			num = getNum();
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : ";
			num = getNum();
			display_ac(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : ";
			num = getNum();
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : ";
			num = getNum();
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using the bank management system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

//This function validates that all numbers given to the program are infact numbers.
float getNum(){
	float x;
	while (true){
	    cin >> x;
	    if (!cin)
	    {
			cout << "\nPlease only enter integers: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
	    }
	    else break;
  	}
  	return x;
}

//This function writes the account to the binary file
void write_account(){
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//This function handles depositing and withdrawing money
void deposit_withdraw(float n, int option){
	float amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File){
		cout<<"Account file not found!";
		return;
	}
	while(!File.eof() && found==false){
		
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.getAccount()==n)	{
			ac.show_account();
			if(option==1){
				cout<<"\n\n\t****Depositing money****";
				cout<<"\n\nEnter The amount to be deposited: ";
				cin>>amt;
				ac.depo(amt);
			}
			if(option==2){
				
				cout<<"\n\n\t****Withdrawing money****";
				cout<<"\n\nEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.getBalance()-amt;
				if((bal<5))
					cout<<"Insufficience balance";
				else
					ac.withdraw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Your Account has been Updated";
			found=true;
	       }
         }
         
	File.close();
	if(found==false)
		cout<<"\n\nAccount Not Found!";
}

//This function displays the account that corresponds to the given account number
void display_ac(int n){
	account ac;
	bool found=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	
	if(!inFile){
		cout<<"Account file not found!";
		return;
	}
	
	cout<<"\nAccount Details\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))){
		if(ac.getAccount()==n){
			ac.show_account();
			found=true;
		}
	}
	
	inFile.close();
	if(!found)
		cout<<"\n\nNo account exists with that number";
}

//This function displays every account
void display_all(){
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile){
		cout<<"Account file not found!";
		return;
	}
	cout<<"\n\n\t\t*****ACCOUNT HOLDER LIST*****\n\n";
	
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))){
		
		ac.report();
		cout<<"\n";
	}
	inFile.close();
}

//This function lets the user modify their account
void modify_account(int n){
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File){
		cout<<"Account file not found!";
		return;
	}
	while(!File.eof() && found==false){
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.getAccount()==n){
			ac.show_account();
			cout<<"\n\nPlease enter the new details of the account!"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Your Account has been Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\nAccount Not Found!";
}

//This function deletes the selected account
void delete_account(int n){
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"account.dat not found!";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.getAccount()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tYour account has been deleted";
}

//This function displays the intro text and gives credit where it is due!
void intro(){
	cout<<"\nWelcome to my banking program!";
	cout<<"\nWritten by Kyle Marcoux";
	cout<<"\nBased on a project found on cppforschool.com, \nI used their code to write/read the account file";
	cin.get();
}
