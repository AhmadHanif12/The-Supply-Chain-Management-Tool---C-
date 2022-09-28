#pragma once
#include"Order.h"


class Transactions
{
private:
	string hash;
	order value;
	Transactions* next;
	Transactions* previous;


public:
	Transactions();
	Transactions* returnNext();
	Transactions* returnPrevious();
	void modifyPrevious(Transactions* temp);
	void modifyNext(Transactions* temp);

	order returnOrder();
	bool checkHash();
	void input_OrderData(int Tn, unsigned int Tstamp, string id, string status, string item, string purchaser, string seller, float price);


	//	string isPresent_AllFiles();

	string Create_Hash();

	string returnHash();
	void output();
	~Transactions();

};
