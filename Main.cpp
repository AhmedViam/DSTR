/**
*
* Name       : Order / Menue management
* File       : DSTR.cpp
* Author     : Viam
* Language   : C++ 11
* Size       : 27.1 KB
* Version    : 1.2.0(Base 1.0.0)
* Role       : Add / Save / delete Menue and Order details.
* Bugs/Issue : Sanitize code partitions.
*
**/



#include "D:/easendmailobj.tlh"
#include "D:/easendmailobj.tli"
#include <tchar.h> 
#include <algorithm> 
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
#include <windows.h>
#include <io.h> 
#include <ctime> 
#include <fstream> 
#include <time.h> 
#include <iostream> 
#include <sstream> 
#define max_records 50	// Should not exceed this limit
#define version 2.0.1
#pragma warning(disable: 4996)
#define _SCL_SECURE_NO_WARNINGS
using namespace std;
using namespace EASendMailObjLib;

/* Menue structure */

typedef struct Menue {

	char dishName[256];
	char MainCoure[256];
	float Price;
	char Dessert[200];
	char Drink[25];
	Menue * next;
	Menue * prev;


};



/* Order structure */

typedef struct Order {

	int OrderID;
	char clientName[256];
	char email[256];
	char menueName[256];
	char clientAddress[256];
	char clientNumber[256];
	int numGuest;
	long long int caterdatestamp;
	char caterLocation[256];
	int cost;
	int priority;
	Order * onext;
	Order * oprev;

};





char ans;
char input[20];
char NameInput[256];
int counter;
int c = 0;
bool found = false;

Menue * head;
Menue * tail;

Order * ohead;
Order * otail;

Menue * newnode;
Order * ordernode;
Order * ordercontainer[max_records];


/*
* Description:  These three function compare struct value recursively for sorting
* Return : Least value
*/


int comparePrice(const void * a, const void * b) {
	struct Menue * ia = (struct Menue *) a;
	struct Menue * ib = (struct Menue *) b;
	return (int)(100.f * ia->Price - 100.f * ib->Price);

}

int compareDate(const void * a,
	const void * b) {
	struct Order * ia = (struct Order *) a;
	struct Order * ib = (struct Order *) b;
	return (int)(100.f * ia->caterdatestamp - 100.f * ib->caterdatestamp);

}

int comparePriority(const void * a,
	const void * b) {
	struct Order * ia = (struct Order *) a;
	struct Order * ib = (struct Order *) b;
	return (int)(100.f * ia->priority - 100.f * ib->priority);

}


/*
* Description: Set the colour handle
* Return : 0
*/


int aesthetic() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	return 0;
}


/* Prototype declarations */

void addMenue(char * dishName, char * MainCoure, float Price, char * Dessert, char * Drink);
void addOrder(char * clientName, char * clientAddress, char * clientNumber, int numGuest, char * caterLocation, char * menueName, int priority, char * email);

void deleteOrder();
void deleteMenue();

void SendEmail(char * email, Order thisorder, string t);
void searchMenue();
void searchOrder();
void viewMenue();
void viewOrder();

int navigateMenue(Menue * head);
int navigateOrder(Order * head);

void printLinkedlist(Menue * head);


/*
* Description:  Check if file exists in the directory
* Return : True if exists
*/

bool is_file_exist(const char * fileName) {
	std::ifstream infile(fileName);
	return infile.good();
}


/*
* Description:  Add a new menue object to struct
* Return : Void
*/


void addMenue(char * dishName, char * MainCoure, float Price, char * Dessert, char * Drink) {
	int counts = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

	struct Menue people;
	strcpy(people.dishName, dishName);
	strcpy(people.MainCoure, MainCoure);
	people.Price = Price;
	strcpy(people.Dessert, Dessert);
	strcpy(people.Drink, Drink);



	FILE * strcont;

	struct Menue container[max_records];
	struct Menue input;

	strcont = fopen("MenueData.vf", "rb");

	while (fread(&input, sizeof(struct Menue), 1, strcont)) {
		container[counts] = input;
		counts++;
	}


	fclose(strcont);
	FILE * data;
	data = fopen("MenueData.vf", "wb");
	fwrite(container, sizeof(struct Menue), counts, data);
	fwrite(&people, sizeof(people), 1, data);

	fclose(strcont);
	fclose(data);

}

std::string time_t_to_string(time_t t) {
	std::stringstream sstr;
	sstr << t;
	return sstr.str();
}


/*
* Description:  Add a new Order object to struct
* Return : Void
*/


void addOrder(char * clientName, char * clientAddress, char * clientNumber, int numGuest, char * caterLocation, char * chosenMenue, int priority, char * email) {

	int counts = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

	std::time_t result = std::time(nullptr);

	string t;
	t = asctime(localtime(&result));
	cout << t;
	FILE * ReadHeader;
	ReadHeader = fopen("MenueData.vf", "rb");
	struct Menue people[max_records];
	struct Menue input;
	char menuename[256];
	struct Order client;
	int thiscost;
	/* Access the struct data with the correct offset with relation to section count */
	while (fread(&input, sizeof(struct Menue), 1, ReadHeader)) {
		if (strcmp(input.dishName, chosenMenue) == 0) {
			thiscost = numGuest * input.Price;
			found = true;
		}
	}

	if (found == false) {
		printf("No menue name of %s found \n", chosenMenue);
		printf("\n");
		system("pause");
		Sleep(600);
		return;
	}



	int randNum;
	time_t timer;
	struct tm y2k = {
		0
	};
	double seconds;

	y2k.tm_hour = 0;
	y2k.tm_min = 0;
	y2k.tm_sec = 0;
	y2k.tm_year = 100;
	y2k.tm_mon = 0;
	y2k.tm_mday = 1;

	time(&timer); /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(timer, mktime(&y2k));

	//int long long y = (int)round(seconds);

	randNum = rand() % (9000 - 2000 + 1) + 2000 * (thiscost * 0.1);
	strcpy(client.clientName, clientName);
	strcpy(client.clientAddress, clientAddress);
	strcpy(client.clientNumber, clientNumber);
	client.numGuest = numGuest;
	client.priority = priority;
	strcpy(client.caterLocation, caterLocation);
	client.cost = thiscost;
	client.OrderID = randNum;
	client.caterdatestamp = seconds;
	strcpy(client.menueName, chosenMenue);


	FILE * strcont;

	struct Order container[max_records];
	struct Order ink;

	strcont = fopen("OrderData.vf", "rb");

	while (fread(&ink, sizeof(struct Order), 1, strcont)) {
		container[counts] = ink;
		counts++;
	}


	fclose(strcont);
	FILE * data;
	data = fopen("OrderData.vf", "wb");
	fwrite(container, sizeof(struct Order), counts, data);
	fwrite(&client, sizeof(client), 1, data);

	fclose(strcont);
	fclose(data);
	printf("\nOrderID = %d\nClientName = %s\nclientAddress = %s\nclientNumber = %s\numGuest = %d\ncaterdatestamp =  %llu\ncaterLocation = %s\ncost = %d\nMenue = %s\nPriority = %d\n", client.OrderID, client.clientName, client.clientAddress, client.clientNumber, client.numGuest, client.caterdatestamp, client.caterLocation, client.cost, client.menueName, client.priority);

	printf("New record added\n");
	Sleep(2000);
	SendEmail(email, client,t);

}






/*
* Description:  Delete a menue object from struct, remember to shift struct accordingly
* Return : Void
*/

void deleteMenue() {
	found = false;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	int counts = 0;
	int j = 0;


	FILE * ReaderPointer;
	ReaderPointer = fopen("MenueData.vf", "rb");
	struct Menue input;
	struct Menue container[max_records];
	while (fread(&input, sizeof(struct Menue), 1, ReaderPointer)) {
		container[counts] = input;
		counts++;

	}
	fclose(ReaderPointer);

	printf("Type the dishName of the Menue you wish to delete.\n");
	scanf("%s", NameInput);

	FILE * Reader;
	Reader = fopen("MenueData.vf", "rb");
	char nullStr[20] = {
		"\0"
	};
	while (fread(&input, sizeof(struct Menue), 1, Reader)) {
		if (strcmp(input.dishName, NameInput) == 0) {
			fclose(ReaderPointer);
			printf("Below is the Menue found\n");
			printf("\n DishName = %s \nMainCourse = %s\nDrink = %s\nDessert = %s\nPrice = %f\n", input.dishName, input.MainCoure, input.Drink, input.Dessert, input.Price);
			found = true;
			printf("\nDeleting %s\n", input.dishName);
			Sleep(400);
			system("pause");

			for (c = j; c < counts; c++) {
				container[c] = container[c + 1];
			}
			FILE * output;
			output = fopen("MenueData.vf", "wb");
			fwrite(container, sizeof(struct Menue), (counts - 1), output);
			fclose(output);
			return;
		}

		j++;
	}

	if (found == false) {
		cout << "No Menue under that name found" << endl;
		Sleep(1000);
	}

}


/*
* Description:  Delete a Order object from struct, remember to shift struct accordingly
* Return : Void
*/


void deleteOrder() {


	int inputs;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	int counts = 0;
	int j = 0;

	FILE * ReaderPointer;
	ReaderPointer = fopen("OrderData.vf", "rb");

	struct Order input;
	struct Order container[max_records];
	while (fread(&input, sizeof(struct Order), 1, ReaderPointer)) {
		container[counts] = input;
		counts++;

	}
	fclose(ReaderPointer);

	printf("Type the ID of the Order you wish to delete.\n");

	FILE * Reader;
	Reader = fopen("OrderData.vf", "rb");
	char nullStr[20] = {
		"\0"
	};


	cin >> inputs;


	while (fread(&input, sizeof(struct Order), 1, Reader)) {
		if (input.OrderID == inputs) {
			fclose(ReaderPointer);
			printf("Below is the Order found\n");
			printf("\nOrderID = %d\nClientName = %s\nclientAddress = %s\nclientNumber = %s\numGuest = %d\ncaterdatestamp = %llu\ncaterLocation = %s\ncost = %d\nMenue = %s\nPriority = %d\n",
				input.OrderID, input.clientName, input.clientAddress, input.clientNumber, input.numGuest, input.caterdatestamp, input.caterLocation, input.cost, input.menueName), input.priority;
			found = true;
			printf("\nDeleting %d\n", input.OrderID);
			Sleep(400);
			system("pause");

			for (c = j; c < counts; c++) {
				container[c] = container[c + 1];
			}

			FILE * output;
			output = fopen("OrderData.vf", "wb");
			fwrite(container, sizeof(struct Order), (counts - 1), output);
			fclose(output);
			return;
		}

		j++;
	}

	if (found == false) {
		cout << "No Order under that name found" << endl;
		Sleep(1000);
	}
}




/*
* Description:  Search menue struct for a specific object
* Return : Void
*/



void searchMenue() {


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	FILE * ReadHeader;
	ReadHeader = fopen("MenueData.vf", "rb");
	FILE * ReaderPointer;
	ReaderPointer = fopen("MenueData.vf", "rb");
	struct Menue input;

	printf("Type the dishName of the Menue\n");
	scanf("%s", NameInput);


	/* Access the struct data with the correct offset with relation to section count */
	while (fread(&input, sizeof(struct Menue), 1, ReadHeader)) {
		if (strcmp(input.dishName, NameInput) == 0) {
			printf("\nDishName = %s \nMainCourse = %s\nDrink = %s\nDessert = %s\nPrice = %f\n",
				input.dishName, input.MainCoure, input.Drink, input.Dessert, input.Price);
			found = true;
			printf("\n");
			system("pause");
		}
	}
	if (found == false) {
		printf("No users found under the name %s found \n", NameInput);
		printf("\n");
		system("pause");
		Sleep(600);
	}

}


void searchOrder() {


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	int in;
	FILE * ReadHeader;
	ReadHeader = fopen("OrderData.vf", "rb");
	FILE * ReaderPointer;
	ReaderPointer = fopen("OrderData.vf", "rb");
	struct Order input;

	printf("Type the ID of the Order\n");
	cin >> in;
	while (!cin) {
		cout << "\n ERROR, enter a number ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> in;
	}

	/* Access the struct data with the correct offset with relation to section count */
	while (fread(&input, sizeof(struct Order), 1, ReadHeader)) {
		if (in == input.OrderID) {
			printf("\nOrderID = %d\nClientName = %s\nclientAddress = %s\nclientNumber = %s\numGuest = %d\ncaterdatestamp = %llu\ncaterLocation = %s\ncost = %d\nMenue = %s\nPriority = %d",
				input.OrderID, input.clientName, input.clientAddress, input.clientNumber, input.numGuest, input.caterdatestamp, input.caterLocation, input.cost, input.menueName, input.priority);
			found = true;
			printf("\n");
			system("pause");
		}
	}
	if (found == false) {
		printf("No Order under the ID %d found \n", in);
		printf("\n");
		system("pause");
		Sleep(600);
	}

}


/*
* Description:  Remove any repeated structs due to anomalies
* Return : Void
*/

void removeDuplicatesmenue(struct Menue * head) {
	
	struct Menue * current = head; // trailer
	struct Menue * next_next;

	if (current == NULL)
		return;


	while (current->next != NULL) {
		if (strcmp(current->dishName, current->next->dishName) == false) {
			next_next = current->next->next;
			free(current->next);
			current->next = next_next;
		}
		else{
			current = current->next;
		}
	}
}



void removeDuplicatesorder(struct Order * ohead) {
	struct Menue * current = head;
	struct Menue * next_next;

	if (current == NULL)
		return;

	while (current->next != NULL) {
		if (strcmp(current->dishName, current->next->dishName) == false) {


			next_next = current->next->next;
			free(current->next);
			current->next = next_next;
		}
		else{

			current = current->next;
		}
	}
}


/*
* Description:  Iterate through the Menue struct
* Return : Void
*/



void viewMenue() {


	int menue_count = 0;
	int g;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);


	FILE * ReaderPointer;
	ReaderPointer = fopen("MenueData.vf", "rb");
	struct Menue people[max_records];
	struct Menue input;

	printf("Retrieving Menue list ...\n");
	while (fread(&input, sizeof(struct Menue), 1, ReaderPointer)) {
		people[menue_count] = input;
		menue_count++;
		found = true;
	}

	if (found == false) {
		printf("\nNo records found");
		printf("\n");
		system("pause");
		return;
	}


	qsort(people, menue_count, sizeof(struct Menue), comparePrice);

	newnode = new Menue;
	strcpy(newnode->Dessert, people[0].Dessert);
	strcpy(newnode->dishName, people[0].dishName);
	strcpy(newnode->Drink, people[0].Drink);
	strcpy(newnode->MainCoure, people[0].MainCoure);
	newnode->Price = people[0].Price;
	newnode->prev = NULL;
	newnode->next = NULL;
	head = newnode;
	tail = newnode;

	for (g = 1; g < menue_count; g++) {

		if (g == menue_count) {
			newnode = new Menue;
			strcpy(newnode->Dessert, people[g].Dessert);
			strcpy(newnode->dishName, people[g].dishName);
			strcpy(newnode->Drink, people[g].Drink);
			strcpy(newnode->MainCoure, people[g].MainCoure);
			newnode->Price = people[g].Price;
			newnode->prev = tail;
			tail->next = newnode;
			tail = newnode;
			tail->next = NULL;
		}

		newnode = new Menue;
		strcpy(newnode->Dessert, people[g].Dessert);
		strcpy(newnode->dishName, people[g].dishName);
		strcpy(newnode->Drink, people[g].Drink);
		strcpy(newnode->MainCoure, people[g].MainCoure);
		newnode->Price = people[g].Price;
		newnode->next = NULL;
		newnode->prev = tail;
		tail->next = newnode;
		tail = newnode;
	}


	removeDuplicatesmenue(head);
	navigateMenue(head);

	Sleep(600);

}




/*
* Description:  Iterate through the Order struct
* Return : Void
*/



void viewOrder() {


	int order_count = 0;
	int g;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);


	FILE * ReaderPointer;
	ReaderPointer = fopen("OrderData.vf", "rb");
	struct Order thisorder[max_records];
	struct Order input;

	printf("Retrieving Order list ...\n");
	while (fread(&input, sizeof(struct Order), 1, ReaderPointer)) {
		thisorder[order_count] = input;
		order_count++;
		found = true;
	}

	if (found == false) {
		printf("\nNo records found");
		printf("\n");
		system("pause");
		return;
	}


	qsort(thisorder, order_count, sizeof(struct Order), compareDate);
	qsort(thisorder, order_count, sizeof(struct Order), comparePriority);

	ordernode = new Order;
	strcpy(ordernode->clientName, thisorder[0].clientName);
	strcpy(ordernode->clientAddress, thisorder[0].clientAddress);
	strcpy(ordernode->clientNumber, thisorder[0].clientNumber);
	strcpy(ordernode->caterLocation, thisorder[0].caterLocation);
	strcpy(ordernode->menueName, thisorder[0].menueName);
	ordernode->cost = thisorder[0].cost;
	ordernode->numGuest = thisorder[0].numGuest;
	ordernode->OrderID = thisorder[0].OrderID;
	ordernode->priority = thisorder[0].priority;
	ordernode->caterdatestamp = thisorder[0].caterdatestamp;
	ordernode->oprev = NULL;
	ordernode->onext = NULL;
	ohead = ordernode;
	otail = ordernode;

	for (g = 1; g < order_count; g++) {

		if (g == order_count) {
			ordernode = new Order;
			strcpy(ordernode->clientName, thisorder[g].clientName);
			strcpy(ordernode->clientAddress, thisorder[g].clientAddress);
			strcpy(ordernode->clientNumber, thisorder[g].clientNumber);
			strcpy(ordernode->caterLocation, thisorder[g].caterLocation);
			strcpy(ordernode->menueName, thisorder[g].menueName);
			ordernode->cost = thisorder[g].cost;
			ordernode->numGuest = thisorder[g].numGuest;
			ordernode->caterdatestamp = thisorder[g].caterdatestamp;
			ordernode->OrderID = thisorder[g].OrderID;
			ordernode->priority = thisorder[g].priority;
			ordernode->oprev = otail;
			otail->onext = ordernode;
			otail = ordernode;
			otail->onext = NULL;
		}

		ordernode = new Order;
		strcpy(ordernode->clientName, thisorder[g].clientName);
		strcpy(ordernode->clientAddress, thisorder[g].clientAddress);
		strcpy(ordernode->clientNumber, thisorder[g].clientNumber);
		strcpy(ordernode->caterLocation, thisorder[g].caterLocation);
		strcpy(ordernode->menueName, thisorder[g].menueName);
		ordernode->OrderID = thisorder[g].OrderID;
		ordernode->cost = thisorder[g].cost;
		ordernode->caterdatestamp = thisorder[g].caterdatestamp;
		ordernode->numGuest = thisorder[g].numGuest;
		ordernode->priority = thisorder[g].priority;
		ordernode->onext = NULL;
		ordernode->oprev = otail;
		otail->onext = ordernode;
		otail = ordernode;
	}


	removeDuplicatesorder(ohead);
	qsort(thisorder, order_count, sizeof(struct Order), compareDate);
	qsort(thisorder, order_count, sizeof(struct Order), comparePriority);

	navigateOrder(ohead);

	Sleep(600);

}


/*
* Description:  Send mail using EASendMail Class
* Return : Void
*/



void SendEmail(char * email, Order thisorder, string t) {


	Order mailOrder = thisorder; 
	::CoInitialize(NULL);
	IMailPtr oSmtp = NULL;
	oSmtp.CreateInstance(__uuidof(EASendMailObjLib::Mail));

	oSmtp->LicenseCode = _T("TryIt");

	oSmtp->ServerAddr = _T("smtp.gmail.com");
	oSmtp->SSL_init();
	oSmtp->ServerPort = 587;


	std::string OrderID = std::to_string(thisorder.OrderID);
	std::string Guest = std::to_string(thisorder.numGuest);
	std::string Cost = std::to_string(thisorder.cost);
	std::string body = std::string("The orderID is " + OrderID + "\nNumber of guests are " + Guest + "\nCost is " + Cost + "\nClient name is "+ thisorder.clientName + "\nOrder Date and time is " + t);


	const char * cstr = body.c_str();

	oSmtp->UserName = _T("viamtmp@gmail.com");
	oSmtp->Password = _T(""); // dont't use the password, use a restricted key access token

	oSmtp->FromAddr = ("viamtmp@gmail.com");
	oSmtp->AddRecipientEx((email), 0);

	oSmtp->Subject = _T("Burpee burger receipt");
	oSmtp->BodyText = (cstr);

	if (oSmtp->SendMail() == 0) {
		Sleep(1000);
	}

}




/* Entry point */

int main() {

	aesthetic();
	FILE * ReadPointer;

	if (!is_file_exist("MenueData.vf")) {

		ReadPointer = fopen("MenueData.vf", "wb");

		printf("MenueData file not found...\n");
		Sleep(3000);
		printf("Creating data repository\n");
		Sleep(2000);
		fclose(ReadPointer);

		fflush(stdin);
		fflush(stdout);
	}

	if (!is_file_exist("OrderData.vf")) {

		ReadPointer = fopen("OrderData.vf", "wb");

		printf("OrderData file not found...\n");
		Sleep(3000);
		printf("Creating data repository\n");
		Sleep(2000);
		fclose(ReadPointer);

		fflush(stdin);
		fflush(stdout);
	}



	do {
		system("cls");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		printf("For Menue related press M. For Order related press O, to exit press B\n");
		scanf("%s", &input);
		system("cls");

		int c = 0;
		bool found = false;;

		if (strcmp(input, "M") == 0) {
			printf("\nWelcome to Burpee burgers Menue Dashboard\n");
			printf("What would you like to do?\n\n1. To view all Menues press V\n2. To search for a Menue press S\n3. To delete a Menue press D\n4. To add a Menue press A\n5. To return press Q\n");
			scanf("%s", &ans);
			switch (ans) {

			case 'Q':
			{

				break;
			}

			case 'S':
			{
				searchMenue();
				break;
			}

			case 'V':
			{
				viewMenue();
				break;
			}
			case 'A':
			{
				int p;
				int  o = 0;
				system("cls");

				struct Menue people;

				printf("DishName: ");

				scanf("%s", people.dishName);

				printf("MainCourse: ");
				scanf("%s", people.MainCoure);

				printf("Price: ");
				cin >> p;
				while (!cin) {
					cout << "\n ERROR, enter a number ";
					cin.clear();
					cin.ignore(256, '\n');
					cin >> p;
				}
				while (p<0) {
					cout << "\n ERROR, less than 0";
					cin.clear();
					cin.ignore(256, '\n');
					cin >> p;
				}
				people.Price = p;

				printf("Dessert: ");
				scanf("%s", people.Dessert);

				printf("Drink ");
				scanf("%s", people.Drink);



				addMenue(people.dishName, people.MainCoure, people.Price, people.Dessert, people.Drink);
				printf("New record added\n");
				Sleep(1000);
			}
			break;

			case 'D':
			{
				deleteMenue();
				break;
			}

			default:
				printf("\nWrong input\n");
				Sleep(600);
				break;
			}

		}


		if (strcmp(input, "O") == 0) {
			printf("\nWelcome to Burpee burgers Order Dashboard\n");
			printf("What would you like to do?\n\n1. To view all Orders press V\n2. To search for an Order press S\n3. To delete an Order press D\n4. To add and Order press A\n5. To return press Q\n");
			scanf("%s", &ans);
			switch (ans) {

			case 'A':
			{
				int p = 0;
				system("cls");

				struct Order thisorder;
				char menuename[256];

				printf("clientName: ");

				scanf("%s", thisorder.clientName);

				printf("Menue name: ");

				scanf("%s", menuename);

				printf("Email: ");
				scanf("%s", thisorder.email);

				printf("clientAddress: ");
				scanf("%s", thisorder.clientAddress);

				printf("clientNumber: ");
				scanf("%s", thisorder.clientNumber);

				printf("numGuest: ");
				cin >> p;
				while (!cin) {
					cout << "\n ERROR, enter a number ";
					cin.clear();
					cin.ignore(256, '\n');
					cin >> p;
				}
				while (p<0) {
					cout << "\n ERROR, less than 0";
					cin.clear();
					cin.ignore(256, '\n');
					cin >> p;
				}
				thisorder.numGuest = p;

				printf("caterLocation ");
				scanf("%s", thisorder.caterLocation);

				printf("Priority 1 = High , 2 = Normal ");
				cin >> p;
				while (!cin) {
					cout << "\n ERROR, enter a number ";
					cin.clear();
					cin.ignore(256, '\n');
					cin >> p;
				}
				thisorder.priority = p;

				addOrder(thisorder.clientName, thisorder.clientAddress, thisorder.clientNumber, thisorder.numGuest, thisorder.caterLocation, menuename, thisorder.priority,thisorder.email);

				
				Sleep(1000);
				break;
			}
			case 'V':
			{
				viewOrder();
				break;

			}

			case 'D':
			{
				deleteOrder();

				break;
			}


			case 'S':
			{
				searchOrder();
				break;
			}

			default:
				printf("\nWrong input\n");
				Sleep(600);
				break;

			}


			if (strcmp(input, "B") == 0) {
				printf("Exiting..");
				Sleep(2000);
				return 0;

			}
		}



	} while (true);
	return 0;

}


void printLinkedlist(Menue * head) {
	Menue * temp = head;

	while (temp != NULL) {
		printf("\nDishName = %s \nMainCourse = %s\nDrink = %s\nDessert = %s\nPrice = %f\n",
			temp->dishName, temp->MainCoure, temp->Drink, temp->Dessert, temp->Price);
		temp = temp->next;
	}
}

int navigateMenue(Menue * head) {
	Menue * temp = head;

	do {

		printf("To view first press s, to view last press l, to go previous press p and to go forward press f \n");
		scanf("%s", &ans);

		switch (ans) {

		case 's':
		{
			system("cls");
			temp = head;
			printf("\nDishName = %s \nMainCourse = %s\nDrink = %s\nDessert = %s\nPrice = %f\n",
				temp->dishName, temp->MainCoure, temp->Drink, temp->Dessert, temp->Price);
			break;
		}

		case 'l':
		{
			system("cls");
			while (temp->next != NULL)
				temp = temp->next;
			printf("\nDishName = %s \nMainCourse = %s\nDrink = %s\nDessert = %s\nPrice = %f\n",
				temp->dishName, temp->MainCoure, temp->Drink, temp->Dessert, temp->Price);

			break;
		}

		case 'p':
		{
			system("cls");
			if (temp->prev != NULL) {
				temp = temp->prev;
				printf("\nDishName = %s \nMainCourse = %s\nDrink = %s\nDessert = %s\nPrice = %f\n",
					temp->dishName, temp->MainCoure, temp->Drink, temp->Dessert, temp->Price);
			}
			else {
				printf("This is the first record, cannot go any back\n");
				printf("\nDishName = %s \nMainCourse = %s\nDrink = %s\nDessert = %s\nPrice = %f\n",
					temp->dishName, temp->MainCoure, temp->Drink, temp->Dessert, temp->Price);
			}
			break;
		}

		case 'f':
		{
			system("cls");
			if (temp->next != NULL) {
				temp = temp->next;
				printf("\nDishName = %s \nMainCourse = %s\nDrink = %s\nDessert = %s\nPrice = %f\n",
					temp->dishName, temp->MainCoure, temp->Drink, temp->Dessert, temp->Price);
			}
			else {
				printf("This is the last record, cannot go any further\n");
				printf("\nDishName = %s \nMainCourse = %s\nDrink = %s\nDessert = %s\nPrice = %f\n",
					temp->dishName, temp->MainCoure, temp->Drink, temp->Dessert, temp->Price);
			}
			break;
		}

		case 'q':
		{
			return 0;
		}
		default:
			printf("\nWrong input\n");
			Sleep(600);
			break;
		}
	} while (true);
}


int navigateOrder(Order * ohead) {

	Order * temp = ohead;


	do {

		printf("\nTo view first press s, to view last press l, to go previous press p and to go forward press f \n");
		scanf("%s", &ans);

		switch (ans) {

		case 's':
		{
			system("cls");
			while (temp->oprev != NULL)
				temp = temp->oprev;


			printf("\nOrderID = %d\nClientName = %s\nclientAddress = %s\nclientNumber = %s\numGuest = %d\ncaterdatestamp = %llu\ncaterLocation = %s\ncost = %d\nMenue = %s\nPriority = %d",
				temp->OrderID, temp->clientName, temp->clientAddress, temp->clientNumber, temp->numGuest, temp->caterdatestamp, temp->caterLocation, temp->cost, temp->menueName, temp->priority);
			break;

		}

		case 'l':
		{
			system("cls");
			while (temp->onext != NULL)
				temp = temp->onext;
			printf("\nOrderID = %d\nClientName = %s\nclientAddress = %s\nclientNumber = %s\numGuest = %d\ncaterdatestamp = %llu\ncaterLocation = %s\ncost = %d\nMenue = %s\nPriority = %d",
				temp->OrderID, temp->clientName, temp->clientAddress, temp->clientNumber, temp->numGuest, temp->caterdatestamp, temp->caterLocation, temp->cost, temp->menueName, temp->priority);
			break;
		}

		case 'p':
		{
			system("cls");
			if (temp->oprev != NULL) {
				temp = temp->oprev;
				printf("\nOrderID = %d\nClientName = %s\nclientAddress = %s\nclientNumber = %s\numGuest = %d\ncaterdatestamp = %llu\ncaterLocation = %s\ncost = %d\nMenue = %s\nPriority = %d",
					temp->OrderID, temp->clientName, temp->clientAddress, temp->clientNumber, temp->numGuest, temp->caterdatestamp, temp->caterLocation, temp->cost, temp->menueName, temp->priority);

			}
			else {
				printf("This is the first record, cannot go any back\n");

				printf("\nOrderID = %d\nClientName = %s\nclientAddress = %s\nclientNumber = %s\numGuest = %d\ncaterdatestamp = %llu\ncaterLocation = %s\ncost = %d\nMenue = %s\nPriority = %d",
					temp->OrderID, temp->clientName, temp->clientAddress, temp->clientNumber, temp->numGuest, temp->caterdatestamp, temp->caterLocation, temp->cost, temp->menueName, temp->priority);
			}
			break;
		}

		case 'f':
		{
			system("cls");
			if (temp->onext != NULL) {
				temp = temp->onext;

				printf("\nOrderID = %d\nClientName = %s\nclientAddress = %s\nclientNumber = %s\numGuest = %d\ncaterdatestamp = %llu\ncaterLocation = %s\ncost = %d\nMenue = %s\nPriority = %d",
					temp->OrderID, temp->clientName, temp->clientAddress, temp->clientNumber, temp->numGuest, temp->caterdatestamp, temp->caterLocation, temp->cost, temp->menueName, temp->priority);
			}
			else {
				printf("This is the last record, cannot go any further\n");

				printf("\nOrderID = %d\nClientName = %s\nclientAddress = %s\nclientNumber = %s\numGuest = %d\ncaterdatestamp = %llu\ncaterLocation = %s\ncost = %d\nMenue = %s\nPriority = %d",
					temp->OrderID, temp->clientName, temp->clientAddress, temp->clientNumber, temp->numGuest, temp->caterdatestamp, temp->caterLocation, temp->cost, temp->menueName, temp->priority);
			}
			break;
		}

		case 'q':
		{
			return 0;
		}
		default:
			printf("\nWrong input\n");
			Sleep(600);
			break;
		}
	} while (true);
}
