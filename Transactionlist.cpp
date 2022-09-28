#include "Transactionlist.h"

using namespace std;
int TransactionList::MODIFY_ORDER_STATUS(string id, string Status)
{
	if (isEmpty())
	{
		cout << "\n[-]List is Empty\n!";
		return 0;
	}
	Transactions* temp=first;

	bool present = false;

	while (temp)
	{
		if (temp->returnOrder().returnOrderID() == id && temp->returnOrder().returnStatus() == Status)
		{
			cout << "\nOrder Already Present !\n";
			return 0;
		}
		temp = temp->returnNext();
	}
	temp = first;
	while (temp)
	{
		if (temp->returnOrder().returnOrderID() == id)
		{
			ADD_ORDER_CustomID(id, temp->returnOrder().returnItem(), Status, temp->returnOrder().returnPurchaser(), temp->returnOrder().returnSeller(), temp->returnOrder().returnPrice());
			cout << "\n[+]Status Modified!";
			return 0;
		}
		temp = temp->returnNext();
	}
}

void TransactionList::CHECK_STATUS(string ID)
{
	Transactions* temp = first;
	bool flag = false;
	while (temp)
	{
		if (temp->returnOrder().returnOrderID() != ID)
		{
			flag = true;
		}
		else
		{
			flag = false;
			break;
		}
		temp = temp->returnNext();
	}

	if (flag)
	{
		cout << "\n[-]Order Not Found !\n";
		return ;
	}
	else
	{
		cout << endl;
		temp = last;
		while (temp)
		{
			if (temp->returnOrder().returnOrderID() == ID)
			{
				temp->returnOrder().Display();
			}
			temp = temp->returnPrevious();
		}

	}
	
}

void TransactionList::EXPORT()
{
	if (remove("recieved.csv") != 0 || remove("report-order-placed.csv") != 0 || remove("payment-processed.csv") != 0 || remove("shipped.csv") != 0)
	{
		cout << "\n[+]Files Created !\n";
	}


	string *arr = new string[1];
	arr[0] = " ";
	int size = 1;
	Transactions *current = first;
	Transactions* temp1=new Transactions;
	int i = 0;
	string ID;
	bool flag = false;
     label:
	while (current)
	{
		Transactions* temp = first;
		cout << "hello !" << endl;
		
		flag = false;
		for (int k = 0; k < size; k++)
		{
			if (current->returnOrder().returnOrderID() == arr[k])
			{
				flag = true;
			}
		}
		if (flag)
		{
			current=current->returnNext();
			cout << current->returnOrder().returnOrderID();
			goto label;
		}
		
		while (temp)
		{
			if (temp->returnOrder().returnOrderID() == current->returnOrder().returnOrderID())
			{
				temp1 = temp;
			}
			temp = temp->returnNext();
		}
		ID = temp1->returnOrder().returnOrderID();
		string status = temp1->returnOrder().returnStatus();
		cout << status << " ";
		i++;
        if (!flag)
		{
			if (i > size)
			{
				string* temp = new string[size + 1];
				int j;
				for (j = 0; j < size; j++)
				{
					temp[j] = arr[j];
				}
				temp[j] = ID;
				size++;
				delete[] arr;
				arr = temp;
			}
			else
			{
				arr[i - 1] = ID;
			}
		}
		

		if (status == "ORDER_RECIEVED" && flag!=true)  
		{
			temp1->returnOrder().addNodeInFile("recieved.csv");
		}
		else if(status=="ORDER_PLACED" && flag!=true )
		{
			temp1->returnOrder().addNodeInFile("report-order-placed.csv");
		}
		else if (status == "SHIPPED" && flag != true)
		{
			temp1->returnOrder().addNodeInFile("shipped.csv");
		}
		else if (status == "PAYMENT_PROCESSED" && flag != true)
		{
			temp1->returnOrder().addNodeInFile("payment-processed.csv");
		}
		current=current->returnNext();

	}

}



TransactionList::TransactionList()
{
	first = NULL;
	last = NULL;
	prevLast = NULL;
}

bool TransactionList::Reader(string FileName)
{
	string data;
	string Tn, Order_ID, Ts, Status, Item, Purchaser, Seller, price;
	int pos = 0;

	ifstream read(FileName);
	if (read.fail())
	{
		cout << "\n[-] Failed to open the file!\n";
		return 0;
	}
	else
	{

		cout << "[+]Started Reading !\n";
		
		while (!read.eof())
		{

			
			read.seekg(pos);
			getline(read, Tn, ',');
			getline(read, Order_ID, ',');
			getline(read, Ts, ',');
			getline(read, Status, ',');
			getline(read, Item, ',');
			getline(read, Purchaser, ',');
			getline(read, Seller, ',');
			getline(read, price, '\n');

			//cout << Tn<<endl;

		//	cout<< Order_ID <<"\t" << Ts << "\t" << Status << "\t" << Purchaser << "\t" << Item << "\t" << Seller << "\t" << price <<endl;
			pos = read.tellg();
			read >> data;



			int Transaction_Number = stoi(Tn);
			unsigned int Timestamp = stoi(Ts);
			float Price = stoi(price);
			//bool flag = stoi(Flag);
			if (!first && !last)
			{
				first = new Transactions;
				first->input_OrderData(Transaction_Number, Timestamp, Order_ID, Status, Item, Purchaser, Seller, Price);
				last = first;
				prevLast = last;
				first->Create_Hash();


			}
			else
			{
				Transactions* temp = new Transactions;
				temp->input_OrderData(Transaction_Number, Timestamp, Order_ID, Status, Item, Purchaser, Seller, Price);

				last->modifyNext(temp);
				temp->modifyPrevious(last);
				last = temp;
				last->Create_Hash();
				prevLast = last;
				
			}


		}


		return 1;
	}
	Transactions* temp = first;
	while (temp->returnPrevious() && temp)
	{
		if (temp->returnOrder().returnOrderID() < temp->returnPrevious()->returnOrder().returnOrderID())
		{
			prevLast = temp->returnPrevious();
		}
		temp = temp = temp->returnNext();
	}
	read.close();

}

void TransactionList::dispplay_trans()
{
	Transactions* temp = first;

	while (temp)
	{
		temp->output();
		temp = temp->returnNext();
	}
}

void TransactionList::REPORT_PURCHASER(string name)
{
	Transactions* temp = first;
	bool flag = false;
	while (temp)
	{
		if (temp->returnOrder().returnPurchaser() != name)
		{
			flag = true;
		}
		else
		{
			flag = false;
			break;
		}
		temp = temp->returnNext();
	}

	if (flag)
	{
		cout << "\n[-]Order Not Found !\n";
		return;
	}
	else
	{
		temp = first;
		while (temp)
		{
			if (temp->returnOrder().returnPurchaser() == name)
			{
				temp->returnOrder().Display();
			}
			temp = temp->returnNext();
		}
	}

	
}
void TransactionList::REPORT_SELLER(string name)
{
	Transactions* temp = first;
	bool flag = false;
	while (temp)
	{
		if (temp->returnOrder().returnSeller() != name)
		{
			flag = true;
		}
		else
		{
			flag = false;
			break;
		}
		temp = temp->returnNext();
	}

	if (flag)
	{
		cout << "\n[-]Order Not Found !\n";
		return;
	}
	else
	{
		temp = first;
		while (temp)
		{
			if (temp->returnOrder().returnSeller() == name)
			{
				temp->returnOrder().Display();
			}
			temp = temp->returnNext();
		}
	}
}

string TransactionList::getUniqueID()
{
	string id;

	id = prevLast->returnOrder().returnOrderID();
	int length = id.length();
	string temp;
	for (int i = length - 3; i < length; i++)
	{
		temp += id[i];
	}

	if (temp[2] != '9')
	{
		temp[2]++;
	}
	else if (temp[2] == '9')
	{
		if (temp[1] != '9')
		{
			temp[1]++;
			temp[2] = '0';
		}
		else if (temp[0] != '9')
		{
			temp[0]++;
			temp[1] = '0';
			temp[2] = '0';
		}

	}
	int j = 0;
	for (int i = length - 3; i < length; i++)
	{
		id[i] = temp[j];
		j++;
	}

	return id;

}
void TransactionList::ADD_ORDER_CustomID(string id,string Item,string Status, string Purchaser, string Seller, float Price)
{
	Transactions* temp = new Transactions;
	time_t t = time(0);
	unsigned int Ts = t;
	temp->input_OrderData(last->returnOrder().returnTn()+1,Ts ,id,Status,Item, Purchaser, Seller, Price);

	cout << last->returnOrder().returnTn() << endl;
		last->modifyNext(temp);
		temp->modifyPrevious(last);
		temp->Create_Hash();
		last = temp;
		temp->returnOrder().addNodeInFile("Tlist.csv");
	
	if (last->returnOrder().returnOrderID() < prevLast->returnOrder().returnOrderID())
	{
		cout << "NIce GG";
	}
}



void TransactionList::ADD_NEW_ORDER(string Item, string Purchaser, string Seller, float Price)
{
	time_t t = time(0);
	unsigned int Ts = t;
	string status = "ORDER_PLACED";
	Transactions* temp = new Transactions;

	temp->input_OrderData(last->returnOrder().returnTn() + 1, Ts, getUniqueID(), status, Item, Purchaser, Seller, Price);

	last->modifyNext(temp);
	temp->modifyPrevious(last);
	last = temp;
	prevLast = last;
	last->Create_Hash();
	temp->returnOrder().addNodeInFile("Tlist.csv");

}



bool TransactionList::isEmpty()
{
	if (!first && !NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TransactionList::DELETE_TRANSACTION(int Tn)
{
	bool flag = false;

	if (isEmpty())
	{
		cout << "\n[-]List is Empty!\n";
		return;
	}
	Transactions* temp = new Transactions;
	temp = first;
	while (temp)
	{
		if (Tn == temp->returnOrder().returnTn())
		{
			if (!temp->returnPrevious() && !temp->returnNext())
			{
				first = NULL;
				last = NULL;
				delete temp;
				flag = true;
				break;
			}
			if (!temp->returnPrevious())
			{
				first = temp->returnNext();
				temp->returnNext()->modifyPrevious(first);
				delete temp;
				first->modifyPrevious(NULL);
				flag = true;
				break;
			}
			else if (!temp->returnNext())
			{
				bool last1 = false;
				if (last->returnOrder().returnOrderID() == prevLast->returnOrder().returnOrderID())
				{
					last1 = true;
				}
				last = temp->returnPrevious();
				temp->returnPrevious()->modifyNext(last);
				delete temp;
				last->modifyNext(NULL);
				if (last1)
				{
					prevLast = last;
				}
				flag = true;
				break;
			}
			else
			{
				temp->returnPrevious()->modifyNext(temp->returnNext());
				temp->returnNext()->modifyPrevious(temp->returnPrevious());
				flag = true;
				delete temp;
				flag = true;
				break;
			}


		}
		temp = temp->returnNext();
	}

	if (flag)
	{
		cout << "\n[+]Transaction Deleted!\n";
	}
	else
	{
		cout << "\n[-]Error While Deleting\n";
	}


}


bool TransactionList::Security_Check()
{
	Transactions* temp = first;

	if (isEmpty())
	{
		return true;
	}
	while (temp)
	{
		if (!temp->checkHash())
		{
			cout << "\n[-]Illegal Deletion Detected!\n";
			system("pause");
			return true;
		}
		temp = temp->returnNext();
	}

}
bool TransactionList::Recovery()
{
	cout << "[+]Recovering from BackUp File !\n";

	Transactions* temp = first; 
	Transactions* curr = NULL;

	while (temp)
	{
		curr = temp;
		temp = temp->returnNext();
		delete curr;
	}
	first = NULL;
	last = NULL;
	if (Reader("Tlist.csv"))
	{
		cout << "\n[+]Orders Recovered!\n";
		return 1;
	}
	else
	{
		cout << "\n[-]Issues While Recovering !\n";
		return 0;
	}
	

}

TransactionList::~TransactionList() {}





bool menu(TransactionList l1)
{
	int Menu = -2;

	while (Menu != 0)
	{
		cout << "Select from the menu: ";
		cout << "\n1--              Add New Order";
		cout << "\n2--              MODIFY_ORDER_STATUS ";
		cout << "\n3--              CHECK_STATUS  ";
		cout << "\n4--              REPORT PURCHASER  ";
		cout << "\n5--              REPORT SELLER  ";
		cout << "\n6--              EXPORT ";
		cout << "\n7--              DELETE TRANSACTION";
		cout << "\n8--              Security Check  ";
		cout << "\n9--              Display List";
        cout << "\n0--              Exit";

		cout << "\n\nEnter Menu: ";
		while (!(cin >> Menu))
		{
			cout << "\nEnter Again: ";
			cin.clear();
			cin.ignore(100, '\n');
		}

		if (Menu == 1)
		{
			system("CLS");
			string itemName;
			string Purchaser;
			string Seller;
			float price;
			cin.ignore();
			cout << "Enter Item Name: ";
			getline(cin, itemName);
			cout << "\nEnter Purchaser Name: ";
			getline(cin, Purchaser);
			cout << "\nEnter Seller Name: ";
			getline(cin, Seller);
			cout << "\nEnter Price: ";
			while (!(cin >> price))
			{
				cout << "\nEnter Again: ";
				cin.clear();
				cin.ignore(100, '\n');
			}
			l1.ADD_NEW_ORDER(itemName, Purchaser, Seller, price);
			cout << "\nNew Order Added !\n";
			system("pause");
			system("CLS");

		}
		else if (Menu == 2)
		{
			system("CLS");
			string id;
			string status;
			cin.ignore();
			cout << "Enter Order ID: ";
			getline(cin, id);
			system("CLS");
			cout << "\nChoose New Status: \n";
			cout << "\n1-        ORDER_PLACED\n";
			cout << "\n2-        PAYMENT_PROCESSED\n";
			cout << "\n3-        SHIPPED\n";
			cout << "\n4-        RECIEVED\n";
			cout << "\nChoose from Menu: ";
			while (!(cin >> Menu))
			{
				cout << "\nEnter Again: ";
				cin.clear();
				cin.ignore(100, '\n');
			}
			if (Menu == 1)
			{
				status = "ORDER_PLACED";
			}
			else if (Menu == 2)
			{
				status = "PAYMENT_PROCESSED";
			}
			else if (Menu == 3)
			{
				status = "SHIPPED";
			}
			else if (Menu == 4)
			{
				status = "RECIEVED";
			}
			system("CLS");
            l1.MODIFY_ORDER_STATUS(id, status);
			system("pause");
			system("CLS");

			
		}
		else if (Menu == 3)
		{
			system("CLS");
			cin.ignore();
			string id;
			cout << "Enter Order ID: ";
			getline(cin, id);
			l1.CHECK_STATUS(id);
			system("pause");
			system("CLS");
		}
		else if (Menu == 4)
		{
			system("CLS");
			cin.ignore();
			string purchaser;
			cout << "Enter Purchaser Name: ";
			getline(cin, purchaser);
			l1.REPORT_PURCHASER(purchaser);
			system("pause");
			system("CLS");
		}
		else if (Menu == 5)
		{
			system("CLS");
			cin.ignore();
			string seller;
			cout << "Enter Seller Name: ";
			getline(cin, seller);
			l1.REPORT_SELLER(seller);
			cout << endl;
			system("pause");
			system("CLS");
		}
		else if (Menu == 6)
		{
			system("CLS");
			l1.EXPORT();
			cout << "\nList Exported !\n";
			system("pause");
			system("CLS");
		}
		else if (Menu == 7)
		{
			system("CLS");
			int Tn=0;
			cout << "Enter Transaction Number: ";
			while (!(cin >> Tn))
			{
				cout << "\nEnter Again: ";
				cin.clear();
				cin.ignore(100, '\n');
			}
			l1.DELETE_TRANSACTION(Tn);
			cout << endl;
			system("pause");
			system("CLS");
		}
		else if (Menu == 8)
		{
			system("CLS");
			if (l1.Security_Check())
			{
				l1.Recovery();
			}
			else
			{
				cout << "\n[+]No need of Security Check !\n";
			}
			cout << endl;
			system("pause");
			system("CLS");
		}
		else if (Menu == 9)
		{
			system("CLS");
			cout << endl << endl;
			l1.dispplay_trans();
			system("pause");
			system("CLS");
		}
	}
	return 0;
}
