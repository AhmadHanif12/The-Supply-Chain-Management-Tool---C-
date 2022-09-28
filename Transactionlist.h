#pragma once
#include"Transactions.h"

class Transactons;


class TransactionList
{
private:
	Transactions* first;
	Transactions* last;
	Transactions* prevLast;
public:
	TransactionList();
	bool isEmpty();
	void dispplay_trans();

	bool Reader(string FileName);
	string getUniqueID();
	void ADD_ORDER_CustomID(string id, string Item, string Status, string Purchaser, string Seller, float Price);

	void ADD_NEW_ORDER(string Item, string Purchaser, string Seller, float Price);
	void DELETE_TRANSACTION(int Tn);
	int MODIFY_ORDER_STATUS(string id, string Status);
	void CHECK_STATUS(string ID);
	void REPORT_PURCHASER(string name);
	void REPORT_SELLER(string name);
	bool Security_Check();
	bool Recovery();
	void EXPORT();
	~TransactionList();

};


bool menu(TransactionList l1);