#include "Transactions.h"

void Transactions::output()
{
	value.Display();
}


bool Transactions::checkHash()
{
	if (Create_Hash() == hash)
	{
		return true;
	}
	else
	{
		return false;
	}
}
Transactions::Transactions()
{
	next = NULL;
	previous = NULL;
}
Transactions* Transactions::returnNext()
{
	return next;
}
Transactions* Transactions::returnPrevious()
{
	return previous;
}
void Transactions::modifyPrevious(Transactions* temp)
{
	previous = temp;
}
string Transactions::returnHash()
{
	return hash;
}

void Transactions::modifyNext(Transactions* temp)
{
	next = temp;
}

order Transactions::returnOrder()
{
	return value;
}


void Transactions::input_OrderData(int Tn, unsigned int Tstamp, string id, string status, string item, string purchaser, string seller, float price)
{
	order temp(Tn, Tstamp, id, status, item, purchaser, seller, price);
	value = temp;

}

string Transactions::Create_Hash()
{

	if (previous)
	{
		hash = md5(previous->returnHash() + value.returnOrderID());
	}
	else
	{
		hash = md5(value.returnOrderID());
	}
	return hash;
}
Transactions::~Transactions() {}

