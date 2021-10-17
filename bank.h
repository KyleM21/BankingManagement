// bank.h
#ifndef BANK_H // include guard
#define BANK_H

#include <string>
#include <vector>

class account{
	private:
		int acno;
		char name[50];
		float balance;
		char type;
	
	public:
		void createAccount(std::vector<int>&);
		void showAccount() const;
		void modify();
		void depo(float);
		void withdraw(float);
		void report() const;
		int getAccount();
		float getBalance();
};

#endif
