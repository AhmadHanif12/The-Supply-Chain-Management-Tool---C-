#pragma once

#include<stdio.h>
#include<ctime>
#include"md5.h"
#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
using namespace std;
class order
{
private:
	int Transaction_Number;
	unsigned int Timestamp;
	string Order_ID, Status, Item, Purchaser, Seller;
	float Price;
	bool recieved, placed, shipped, processed;

public:
	order(int Tn = 0, unsigned int Tstamp = 0, string id = "", string status = "", string item = "", string purchaser = "", string seller = "", float price = 0);

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


	int returnTn();
	unsigned int returnTs();
	string returnID();
	string returnStatus();
	string returnItem();
	string returnPurchaser();
	string returnSeller();
	float returnPrice();

	void modifyStatus(string status);

	order(const order& obj);

	void addNodeInFile(string FileName);
	//void Refresh(string FieName);
	string returnOrderID();
	void Display();
	~order();
};