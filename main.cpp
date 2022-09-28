
#include "Transactionlist.h"
int main()
{

	TransactionList l1;

	l1.Reader("Tlist.csv");
	
	menu(l1);
	system("CLS");
	cout << "Program Terminated !\n";
	system("pause");
 
}