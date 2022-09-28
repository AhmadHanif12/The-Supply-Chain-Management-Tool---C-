#include "Order.h"

order::order(int Tn, unsigned int Tstamp, string id, string status, string item, string purchaser, string seller, float price)
{
	Transaction_Number = Tn;
	Timestamp = Tstamp;
	Order_ID = id;
	Status = status;
	Item = item;
	Purchaser = purchaser;
	Seller = seller;
	Price = price;
	recieved = 0; placed = 0; shipped = 0; processed = 0;
}

/*order()
{
	Transaction_Number = 0;
	Timestamp = 0;
	Order_ID = "";
	Status = "";
	Item = "";
	Purchaser = "";
	Seller = "";
	Price = 0;
}*/

order::order(const order& obj)
{
	Transaction_Number = obj.Transaction_Number ;
	Timestamp = obj.Timestamp;
	Order_ID = obj.Order_ID;
	Status = obj.Status;
	Item = obj.Item;
	Purchaser = obj.Purchaser;
	Seller = obj.Seller;
	Price = obj.Price;
	recieved = obj.recieved; placed = obj.placed; shipped = obj.shipped; processed = obj.processed;

}

string order::returnOrderID()
{
	return Order_ID;
}

int order::returnTn()
{
	return Transaction_Number;
}
unsigned int order::returnTs()
{
	return Timestamp;
}
string order::returnID()
{
	return Order_ID;
}
string order::returnStatus()
{
	return Status;
}
string order::returnItem()
{
	return Item;
}
string order::returnPurchaser()
{
	return Purchaser;
}
string order::returnSeller()
{
	return Seller;
}
float order::returnPrice()
{
	return Price;
}


void order::Display()
{
	cout << "Tn =" << Transaction_Number << "  Ts = " << Timestamp << "  ID = " << Order_ID << "  Status = " << Status << "  Item = " << Item << "  Purchaser =" << Purchaser << "  Seller = " << Seller << "  Price = " << Price << endl << endl;

}
void order::modifyStatus(string status)
{
	Status = status;
}

void order::addNodeInFile(string FileName)
{
	ofstream write(FileName, ios::out | ios::app);

	write << Transaction_Number << "," << Order_ID << "," << Timestamp << "," << Status << "," << Item << "," << Purchaser << "," << Seller << "," << Price << "\n";

	write.close();

}

order::~order() {}