// bank.h
#include <string>

class account{
	private:
		int acno;
		char name[50];
		float balance;
		char type;
	
	public:
		void create_account();
		void show_account() const;
		void modify();
		void depo(float);
		void withdraw(float);
		void report() const;
		float getAccount();
		float getBalance();
		char getType() const;
};
