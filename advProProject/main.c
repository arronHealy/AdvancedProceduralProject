#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Arron Healy - Advanced Procedural Project
//defined values for password entry to print * char
#define ENTER 13
#define BKSP 8
#define TAB 9
#define SPACE 32

//passenger node to store passenger details for linked list
struct passengerNode
{
	int passportNum;
	char firstName[20];
	char surName[20];
	int yob;
	char email[20];
	char travelFrom[20];
	int travelFromNum;
	char travelClass[30];
	int travelClassNum;
	char tripsToIreland[40];
	int tripsToIrelandNum;
	char averageDuration[30];
	int averageDurationNum;

	struct passengerNode* next;
};

//user login structure for validation
struct login
{
	char username[20];
	char password[20];
};

//function declarations for linked list processing
struct passengerNode* loadFile(FILE** loadFile, struct passengerNode* head);

int searchPassportNum(struct passengerNode* head, int passport);

char *checkEmailAddress(char *email);

void addPassengerToStart(struct passengerNode** head);

void addPassengerToEnd(struct passengerNode* head);

void addPassengerAtPos(struct passengerNode* head, int pos);

void searchPassengerDetails(struct passengerNode* head);

void displayList(struct passengerNode* head, int size);

int listLength(struct passengerNode* head);

int userLogin(FILE** logIn, struct login* user);

void updatePassengerStatistic(struct passengerNode* head);

void deletePassengerAtStart(struct passengerNode** head);

void deletePassengerAtEnd(struct passengerNode* head);

void deletePassengerAtPos(struct passengerNode* head, int pos);

void generatePassengerStats(struct passengerNode* head);

void get1980TravelStats(struct passengerNode* head);

void getTravelClassStats(struct passengerNode* head);

void updatePassengerByName(struct passengerNode* head, char first[20], char last[20]);

void updatePassengerByNumber(struct passengerNode* head, int passport);

void printPassengerFile(FILE** database, FILE** details, struct passengerNode* head, int size);

void listUkByBirthYear(struct passengerNode* head, int size);

//start main
void main()
{
	FILE* logInFile;
	FILE* passengerFile;
	FILE* outFile;
	//files for login, read, write database

	//head of list and user structures
	struct passengerNode* head = NULL;
	struct login* user;
	
	//ints for validation, option choices and position of linked list
	int choice, pos, validate, option;

	//allocate memory for user
	user = (struct login*)malloc(sizeof(struct login));

	//do-while loop to ensure right option entered
	do
	{
		printf("\nWelcome to XYZ Passport Database");
		printf("\nEnter option to Load Database or Create New Database");
		printf("\n1. Load Passenger Details From File");
		printf("\n2. Enter New Passenger Details");
		printf("\nEnter option: ");
		scanf("%d", &option);

	} while (option < 1 || option > 2);

	//switch case option for load file or enter new list
	switch(option)
	{
	case 1:
		//login
		validate = userLogin(&logInFile, user);

		//break if login failed
		if(validate != 1)
		{
			printf("\nInvalid Login\n");
			break;
		}

		//assign head to load file function to return list has bug to fix but works
		head = loadFile(&passengerFile, head);
		break;

	case 2:
		//login
		validate = userLogin(&logInFile, user);
		
		break;

	}//switch

	//check validate returns 1 user login entered
	if (validate == 1)
	{
		//initial prompt user
		printf("\nLogin Accepted\n");

		printf("\nWelcome to XYZ Passport Database\n");
		printf("\nPlease Select from listed options below");
		printf("\n1. Add Passenger Details to Database");
		printf("\n2. Display all Passengers in Database");
		printf("\n3. Search & Display Passenger Details");
		printf("\n4. Search & Update Passenger Details");
		printf("\n5. Delete Passenger from Database");
		printf("\n6. Generate Statistics");
		printf("\n7. Print All Passenger Details to Report File");
		printf("\n8. List UK Passenger in order of Year of Birth");
		printf("\n-1. Exit Application");
		printf("\nEnter option: ");
		scanf("%d", &choice);

		//loop application until -1 entered
		while (choice != -1)
		{
			//switch case menu option
			switch (choice)
			{
			case 1:
				//case 1 create linked list based on position user enters
				//scan option
				printf("\nPlease Enter position to add Passenger in List: ");
				scanf("%d", &pos);

				//check position call 1 of add to list functions based on user entry  
				if (pos < 2)
				{
					printf("\nAdding to start of Database\n");
					//add to start
					addPassengerToStart(&head);
				}
				else if (pos > listLength(head))
				{
					printf("\nAdd to End of Database\n");
					//add to end
					addPassengerToEnd(head);
				}
				else
				{
					printf("\nAdd at position %d\n", pos);
					//add at position
					addPassengerAtPos(head, pos);
				}

				break;

			case 2:
				//case 2 check list is not empty - else display passenger details
				if (head == NULL)
				{
					printf("\nSorry Database is Empty Cannot perform operation!!!\n");
				}
				else
				{
					printf("Display all Passengers in Databases Details\n");
					displayList(head, listLength(head));
				}//if
				
				break;

			case 3:
				//case 3 check list is not empty - else search for passenger details
				if (head == NULL)
				{
					printf("\nSorry Database is Empty Cannot perform operation!!!\n");
				}
				else
				{
					printf("\nSearch Passenger Details\n");
					searchPassengerDetails(head);
				}//if
				
				break;

			case 4:
				//case 4 check list is not empty - update statistics of passenger
				if (head == NULL)
				{
					printf("\nSorry Database is Empty Cannot perform operation!!!\n");
				}
				else
				{
					printf("\nUpdate Passenger Statistic\n");
					updatePassengerStatistic(head);
				}//if
				break;

			case 5:
				//case 5 delete passenger from list scan for position at list
				printf("\nPlease Enter position to Delete Passenger in List: ");
				scanf("%d", &pos);
				
				//check list not empty
				if(head == NULL)
				{
					printf("\nSorry Database is Empty\n");
				}
				else
				{
					if (pos < 2)
					{
						printf("\nDeleting at start of Database\n");
						//check if less tha 2 delete at start
						deletePassengerAtStart(&head);
					}
					else if (pos >= 2 && pos < listLength(head))
					{
						printf("\nDelete at position %d in Database\n", pos);
						//check position greater than 2 and less than list length delete at position
						deletePassengerAtPos(head, pos);
					}
					else
					{
						printf("\nDelete at end of Database\n");
						//delete at end
						deletePassengerAtEnd(head);
					}//if

				}//if

				break;

			case 6:
				//case 6 check list not empty - else function call to generate statistics
				if(head == NULL)
				{
					printf("\nSorry Database is Empty Cannot perform operation!!!\n");
				}
				else
				{
					printf("\nGenerate Passenger Statistics\n");
					generatePassengerStats(head);
				}//if
				
				break;

			case 7:
				//check list not empty - else print passenger details list to file
				if (head == NULL)
				{
					printf("\nSorry Database is Empty Cannot perform operation!!!\n");
				}
				else
				{
					printf("\nPrint Database to Report File\n");
					printPassengerFile(&outFile, &loadFile, head, listLength(head));
				}//if
				
				break;

			case 8:
				//case 8 check list not empty - function call to list all uk passengers in order of birth year
				if (head == NULL)
				{
					printf("\nSorry Database is Empty Cannot perform operation!!!\n");
				}
				else
				{
					printf("\nPrint UK Passengers in order of Birth year\n");
					listUkByBirthYear(head, listLength(head));
				}//if
				
				break;
				//default case for invalid entry
			default:
				printf("\nWrong input!!! Please Try Again...\n");

			}//switch
			//subsequent read for menu option while not -1
			printf("\nList Length %d\n", listLength(head));

			printf("\nPlease Select from listed options below");
			printf("\n1. Add Passenger Details to Database");
			printf("\n2. Display all Passengers in Database");
			printf("\n3. Search & Display Passenger Details");
			printf("\n4. Search & Update Passenger Details");
			printf("\n5. Delete Passenger from Database");
			printf("\n6. Generate Statistics");
			printf("\n7. Print All Passenger Details to Report File");
			printf("\n8. List UK Passenger in order of Year of Birth");
			printf("\n-1. Exit Application");
			printf("\nEnter option: ");
			scanf("%d", &choice);

		}//while



	}
	else
	{
		printf("\nLogin Not Accepted!!! Try Again...\n");
	}//if
	
	 //else if login not accepted print error

	 //check list not empty - else print final version of list to file
	if (head == NULL)
	{
		printf("\nSorry Database is Empty Cannot Update File!!!\n");
	}
	else
	{
		printf("\nPrinting Updated Database to Report File\n");
		printPassengerFile(&outFile, &loadFile, head, listLength(head));
		printf("\nContents written to File!!! Check Folder...\n");
	}//if


}//main


//function list

//load file function - has error to be fixed prints null passenger after list loaded and display function called
//I know this is due to head not being dereferenced twice when passed to function but can't figure it out at the minute so 
//i will have to go with this for now but still works and doesn't cause crash of code
struct passengerNode* loadFile(FILE** loadFile, struct passengerNode* head)
{
	//open file for processing
	loadFile = fopen("passengerDetails.txt", "r");

	//check file opened otherwise error message
	if (loadFile == NULL)
	{
		printf("\nFile could not be opened Try Again!!!\n");
		return;
	}
	else
	{
		//printf("\nFile opened!!!\n");
		//loop file while not end of file
		while (!feof(loadFile))
		{
			//check for head = null, add to start of list 
			if (head == NULL)
			{
				//alllocate memory for node
				head = (struct passengerNode*)malloc(sizeof(struct passengerNode));

				//begin scan of list variables
				fscanf(loadFile, "%d", &head->passportNum);
				fscanf(loadFile, "%20s", head->firstName);
				fscanf(loadFile, "%20s", head->surName);
				fscanf(loadFile, "%d", &head->yob);
				fscanf(loadFile, "%20s", head->email);
				fscanf(loadFile, "%d", &head->travelFromNum);

				//switch scanned integer for string allocation in list 
				switch (head->travelFromNum)
				{
				case 1:
					strcpy(head->travelFrom, "UK");
					break;

				case 2:
					strcpy(head->travelFrom, "Rest of Europe");
					break;

				case 3:
					strcpy(head->travelFrom, "Asia");
					break;

				case 4:
					strcpy(head->travelFrom, "Americas");
					break;

				case 5:
					strcpy(head->travelFrom, "Australasia");
					break;

				}//switch

				//scan next integer in file
				fscanf(loadFile, "%d", &head->travelClassNum);

				//switch scanned integer for string allocation in list
				switch (head->travelClassNum)
				{
				case 1:
					strcpy(head->travelClass, "Economy");
					break;

				case 2:
					strcpy(head->travelClass, "Premium Economy");
					break;

				case 3:
					strcpy(head->travelClass, "Business Class");
					break;

				case 4:
					strcpy(head->travelClass, "First Class");
					break;

				}//switch

				 //scan next integer in file
				fscanf(loadFile, "%d", &head->tripsToIrelandNum);

				//switch scanned integer for string allocation in list
				switch (head->tripsToIrelandNum)
				{
				case 1:
					strcpy(head->tripsToIreland, "Less than three times per year");
					break;

				case 2:
					strcpy(head->tripsToIreland, "Less than three times per year");
					break;

				case 3:
					strcpy(head->tripsToIreland, "More than five times per year");
					break;

				}//switch

				 //scan next integer in file
				fscanf(loadFile, "%d", &head->averageDurationNum);

				//switch scanned integer for string allocation in list
				switch (head->averageDurationNum)
				{
				case 1:
					strcpy(head->averageDuration, "One day");
					break;

				case 2:
					strcpy(head->averageDuration, "Less than 3 days");
					break;

				case 3:
					strcpy(head->averageDuration, "Less than 7 days");
					break;

				case 4:
					strcpy(head->averageDuration, "More than 7 days");
					break;

				}//switch

				//point node to null
				head->next = NULL;

				//print used for testing list scanned correctly
				printf("\nPassenger Name: %s %s\n", head->firstName, head->surName);
				printf("\nPassport Number: %d\n", head->passportNum);
				printf("\nPassenger Year of Birth: %d\n", head->yob);
				printf("\nPassenger E-mail: %s\n", head->email);
				printf("\nPassenger Area Travelled from: %d - %s\n", head->travelFromNum, head->travelFrom);
				printf("\nPassenger Travel Class: %d - %s\n", head->travelClassNum, head->travelClass);
				printf("\nTrips to Ireland per year: %d - %s\n", head->tripsToIrelandNum, head->tripsToIreland);
				printf("\nPassenger Average duration of stay: %d - %s\n\n", head->averageDurationNum, head->averageDuration);

			}
			else
			{
				//assign a temp variable to head to loop from start through to end of list
				struct passengerNode* temp = head;

				//allocate memory for new node to end of list
				struct passengerNode* curr = (struct passengerNode*)malloc(sizeof(struct passengerNode));

				//scan variables for new node
				fscanf(loadFile, "%d", &curr->passportNum);
				fscanf(loadFile, "%20s", curr->firstName);
				fscanf(loadFile, "%20s", curr->surName);
				fscanf(loadFile, "%d", &curr->yob);
				fscanf(loadFile, "%20s", curr->email);
				fscanf(loadFile, "%d", &curr->travelFromNum);

				//switch scanned integer for string allocation
				switch (curr->travelFromNum)
				{
				case 1:
					strcpy(curr->travelFrom, "UK");
					break;

				case 2:
					strcpy(curr->travelFrom, "Rest of Europe");
					break;

				case 3:
					strcpy(curr->travelFrom, "Asia");
					break;

				case 4:
					strcpy(curr->travelFrom, "Americas");
					break;

				case 5:
					strcpy(curr->travelFrom, "Australasia");
					break;

				}//switch

				//scan next int from file
				fscanf(loadFile, "%d", &curr->travelClassNum);

				//switch scanned integer for string allocation
				switch (curr->travelClassNum)
				{
				case 1:
					strcpy(curr->travelClass, "Economy");
					break;

				case 2:
					strcpy(curr->travelClass, "Premium Economy");
					break;

				case 3:
					strcpy(curr->travelClass, "Business Class");
					break;

				case 4:
					strcpy(curr->travelClass, "First Class");
					break;

				}//switch

				 //scan next int from file
				fscanf(loadFile, "%d", &curr->tripsToIrelandNum);

				//switch scanned integer for string allocation
				switch (curr->tripsToIrelandNum)
				{
				case 1:
					strcpy(curr->tripsToIreland, "Less than three times per year");
					break;

				case 2:
					strcpy(curr->tripsToIreland, "Less than three times per year");
					break;

				case 3:
					strcpy(curr->tripsToIreland, "More than five times per year");
					break;

				}//switch

				 //scan next int from file
				fscanf(loadFile, "%d", &curr->averageDurationNum);

				//switch scanned integer for string allocation
				switch (curr->averageDurationNum)
				{
				case 1:
					strcpy(curr->averageDuration, "One day");
					break;

				case 2:
					strcpy(curr->averageDuration, "Less than 3 days");
					break;

				case 3:
					strcpy(curr->averageDuration, "Less than 7 days");
					break;

				case 4:
					strcpy(curr->averageDuration, "More than 7 days");
					break;

				}//switch

				//loop temp until temp->next is not null 
				while (temp->next != NULL)
				{
					temp = temp->next;
				}//while

				//assign new node to next position in list
				temp->next = curr;
				//point new node next to null
				curr->next = NULL;

				//print used for testing list scanned correctly
				printf("\nPassenger Name: %s %s\n", curr->firstName, curr->surName);
				printf("\nPassport Number: %d\n", curr->passportNum);
				printf("\nPassenger Year of Birth: %d\n", curr->yob);
				printf("\nPassenger E-mail: %s\n", curr->email);
				printf("\nPassenger Area Travelled from: %d - %s\n", curr->travelFromNum, curr->travelFrom);
				printf("\nPassenger Travel Class: %d - %s\n", curr->travelClassNum, curr->travelClass);
				printf("\nTrips to Ireland per year: %d - %s\n", curr->tripsToIrelandNum, curr->tripsToIreland);
				printf("\nPassenger Average duration of stay: %d - %s\n\n", curr->averageDurationNum, curr->averageDuration);

			}//if

		}//while


		printf("\nFile read into linked list\n");

		fclose(loadFile);

	}//if

	return head;

}//end loadFile


//user login function takes file and user struct
int userLogin(FILE** logIn, struct login* user)
{
	//open log in file
	logIn = fopen("users.txt", "r");

	//variables for manipulation
	char userNames[3][20];
	char ch;
	char passWords[3][20];
	int pos, i = 0;

	//check login file not null
	if(logIn == NULL)
	{
		printf("\nFile could not be opened!!! Try Again...\n");
		return 0;
	}
	else
	{
		//printf("\nFile opened!!!\n");

		//prompt user for username & password
		printf("Enter username (Case Sensitive): ");
		scanf("%s", user->username);

		printf("\nEnter Password (6 Characters): ");
		//scanf("%d", &user->password);
		
		//while loop is true 
		while(1)
		{
			//ch var gets character
			ch = getch();

			//ASCII value for enter = 13
			if(ch == ENTER)
			{
				//add null character to end of password after enter key hit
				user->password[i] = '\0';
				break;
			}
			else if(ch == BKSP)//backspace 8
			{
				//conditional delete * characters
				if(i > 0)
				{
					i--;
					printf("\b \b");
				}
			}
			else if(ch == TAB || ch == SPACE)//tab 9 & space 32
			{
				//handling for space and tab buttons
				continue;
			}
			else
			{
				//add ch to password & print * to screen while user enters password
				user->password[i] = ch;
				i++;
				printf("*");
			}//if

		}//while

		//assign pos to 0 for char array position
		pos = 0;

		//while loop not end of file
		while(!feof(logIn))
		{
			//scan user in file at pos
			fscanf(logIn, "%s %s", userNames[pos], passWords[pos]);

			//compare username & password entered to username & password at pos in file
			if (strcmp(userNames[pos], user->username) == 0 && strcmp(passWords[pos], user->password) == 0)
			{
				//user found return 1
				printf("\nUser Found\n");
				printf("\nUsername Found: %s, Password: ****** Accepted\n", user->username);
				return 1;
			}//if
			
			//check if end of file
			if(feof(logIn))
			{
				//return 0 no match
				printf("\nNot Found!!! Try Again...\n");
				printf("\nUserName: %s, Password: ******  Not Found Try Again!!!\n", user->username);
				return 0;
			}//if
			//increment pos for for next element in array
			pos++;

		}//while

		//close file
		fclose(logIn);
	}//if

}//userLogin

//seacrh passport number function
int searchPassportNum(struct passengerNode* head, int passport)
{
	//temp struct variable
	struct passengerNode* temp;

	//asign head to temp
	temp = head;

	//char option 
	char option;

	//loop while temp not null
	while(temp != NULL)
	{
		//check if temp number equal to passport number entered
		if(temp->passportNum == passport)
		{
			//print error message number already exists
			printf("\nPassport Number already exists in Database!!! Passport Number must be Unique...");
			printf("\nPlease Try Again...\n");
			
			//offer option to update user with this number
			printf("\nWould you like to Update Passenger Id - %d Statistics?", passport);
			printf("\nEnter (y/Y) Yes or (n/N) No\n");
			printf("Enter option: ");
			scanf(" %c", &option);

			//switch option
			switch(option)
			{
			case 'y':
			case 'Y':
				//update this passenger number details
				printf("\nUpdate Passenger Id - %d", passport);
				updatePassengerByNumber(head, passport);
				return 0;
				break;

			case 'n':
			case 'N':
				//return if no entered to update passenger
				return 0;
				break;

			default:
				printf("\nInvalid option entered!!! Enter valid option next time...\n");
				return 0;
			}//switch

		}//if
		
		//assign temp to next in list
		temp = temp->next;

	}//while

	return passport;

}//searchPassportNum

//check email address format function
char *checkEmailAddress(char *email)
{
	//declare needed symbols and string
	char atSymbol = '@', dotSymbol = '.', dotCom[10] = ".com";

	//temp string
	char temp[30];

	//int vars
	int size, foundAt = 0, atCounter = 0, dotCounter = 0;

	//assign size to length of string email
	size = strlen(email);

	//copy email to temp
	strcpy(temp, email);

	for(int i = 0; i < size; i++)
	{
		//loop through temp check for 1 occurence of @ and . symbol
		if(temp[i] == atSymbol)
		{
			atCounter++;
		}//if

		if(temp[i] == dotSymbol)
		{
			dotCounter++;
		}//if

	}//for
	
	//check for occurence of @ symbol and check string has .com
	if(strchr(email, atSymbol) && strstr(email, dotCom))
	{
		foundAt = 1;
	}//if

	//if all conditions met return valid email
	if(foundAt == 1 && atCounter == 1 && dotCounter == 1)
	{
		printf("\n%s Accepted", email);
		printf("\nEmail format valid continue with Passenger Detail Submission\n");
		return email;
	}
	else
	{
		//email not valid return null
		printf("\n%s Address not Valid!!! Please Try again...\n", email);
		return NULL;
	}//if

}//checkEmail

//add passenger to start of list function
void addPassengerToStart(struct passengerNode** head)
{
	//declare new node
	struct passengerNode* newPassenger;

	//helper vars for number and string manipulation
	int passportNum, travelArea, travelClass, tripsIreland, duration;

	//allocate memory for new node
	newPassenger = (struct passengerNode*)malloc(sizeof(struct passengerNode));

	//helper string for email manipulation
	char *tempEmail;
	//aloocate memory for temp email address
	tempEmail = (char*)malloc(30 * sizeof(char));

	//prompt user for passport number
	printf("\nPlease enter Passport number: ");
	scanf("%d", &passportNum);

	//check if head is not null
	if(head != NULL)
	{
		//assign passport number to search passport number if head not null
		newPassenger->passportNum = searchPassportNum(head, passportNum);
	}
	else
	{
		//list is empty assign passport number
		newPassenger->passportNum = passportNum;
	}//if

	//check passport number valid continue with passenger entry
	if(newPassenger->passportNum != 0)
	{
		//enter passenger name & birth year
		printf("\nPlease enter Passenger firstname: ");
		scanf("%s", newPassenger->firstName);

		printf("\nPlease enter Passenger lastname: ");
		scanf("%s", newPassenger->surName);

		printf("\nPlease enter Passenger Year of Birth: ");
		scanf("%d", &newPassenger->yob);

		//do-while handles email address calls function while null value returned
		do
		{
			printf("\nPlease enter Valid Passenger E-mail (myName@mail.com): ");
			scanf("%s", tempEmail);

		} while(checkEmailAddress(tempEmail) == NULL);
		
		//handle case where email may be null
		if(tempEmail == NULL)
		{
			printf("\nEmail Address %s Not Valid format!!! Please Try Again...\n", tempEmail);
			exit(0);
		}
		else
		{
			//assign email address if valid
			strcpy(newPassenger->email, tempEmail);
			//free memory for temp email
			free(tempEmail);
		}//if

		//do-while area travelled from
		do
		{
			printf("\nPlease enter Area Traveled from: ");
			printf("\n1. UK");
			printf("\n2. Rest of Europe");
			printf("\n3. Asia");
			printf("\n4. Americas");
			printf("\n5. Australasia");
			printf("\nEnter Area Travelled: ");
			scanf("%d", &travelArea);

		} while (travelArea < 1 || travelArea > 5);
		//do-while

		//switch travel area for string assignment
		switch (travelArea)
		{
		case 1:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "UK");
			break;

		case 2:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Rest of Europe");
			break;

		case 3:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Asia");
			break;

		case 4:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Americas");
			break;

		case 5:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Australasia");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		 //do-while travel class
		do
		{
			printf("\nPlease enter Travel Class to Ireland: ");
			printf("\n1. Economy");
			printf("\n2. Premium Economy");
			printf("\n3. Business Class");
			printf("\n4. First Class");
			printf("\nEnter Travel Class: ");
			scanf("%d", &travelClass);

		} while (travelClass < 1 || travelClass > 4);
		//do-while

		//switch travel class for string assignment
		switch (travelClass)
		{
		case 1:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "Economy");
			break;

		case 2:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "Premium Economy");
			break;

		case 3:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "Business Class");
			break;

		case 4:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "First Class");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		 //do-while trips to ireland
		do
		{
			printf("\nPlease enter number of Trips to Ireland per year: ");
			printf("\n1. Less than three times per year");
			printf("\n2. Less than five times per year");
			printf("\n3. More than five times per year");
			printf("\nEnter option: ");
			scanf("%d", &tripsIreland);

		} while (tripsIreland < 1 || tripsIreland > 3);
		//do-while

		//switch trips ireland for string assignment
		switch (tripsIreland)
		{
		case 1:
			newPassenger->tripsToIrelandNum = tripsIreland;
			strcpy(newPassenger->tripsToIreland, "Less than three times per year");
			break;

		case 2:
			newPassenger->tripsToIrelandNum = tripsIreland;
			strcpy(newPassenger->tripsToIreland, "Less than five times per year");
			break;

		case 3:
			newPassenger->tripsToIrelandNum = tripsIreland;
			strcpy(newPassenger->tripsToIreland, "More than five times per year");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		 //do-while trips to ireland
		do
		{
			printf("\nPlease enter Average Duration of Stay: ");
			printf("\n1. One day");
			printf("\n2. Less than 3 days");
			printf("\n3. Less than 7 days");
			printf("\n4. More than 7 days");
			printf("\nEnter Travel Class: ");
			scanf("%d", &duration);

		} while (duration < 1 || duration > 4);
		//do-while

		//switch average duration for string assignment
		switch (duration)
		{
		case 1:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "One day");
			break;

		case 2:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "Less than 3 days");
			break;

		case 3:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "Less than 7 days");
			break;

		case 4:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "More than 7 days");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		//assign new node next to null
		newPassenger->next = *head;

		//assign new nide to heads position
		*head = newPassenger;

	}
	else
	{
		printf("\nInvalid Passport Number Entered!!!\n");
		return;
	}//if

}//addAtStart

void addPassengerToEnd(struct passengerNode* head)
{
	struct passengerNode* curr;
	struct passengerNode* newPassenger;

	char *tempEmail;

	int travelArea, travelClass, tripsIreland, duration, passportNum;

	newPassenger = (struct passengerNode*)malloc(sizeof(struct passengerNode));

	tempEmail = (char*)malloc(30 * sizeof(char));

	printf("\nPlease enter Passport number: ");
	scanf("%d", &passportNum);

	newPassenger->passportNum = searchPassportNum(head, passportNum);

	if(newPassenger->passportNum != 0)
	{
		printf("\nPlease enter Passenger firstname: ");
		scanf("%s", newPassenger->firstName);

		printf("\nPlease enter Passenger lastname: ");
		scanf("%s", newPassenger->surName);

		printf("\nPlease enter Passenger Year of Birth: ");
		scanf("%d", &newPassenger->yob);

		do
		{
			printf("\nPlease enter Valid Passenger E-mail (myName@mail.com): ");
			scanf("%s", tempEmail);

			printf("\n%s email before method\n", tempEmail);

		} while (checkEmailAddress(tempEmail) == NULL);
		//do-while


		if (tempEmail == NULL)
		{
			printf("\nEmail Address %s Not Valid format!!! Please Try Again...\n", tempEmail);
			exit(0);
		}
		else
		{
			strcpy(newPassenger->email, tempEmail);
			//printf("\n%s Address after method\n", newPassenger->email);
			free(tempEmail);
		}//if

		do
		{
			printf("\nPlease enter Area Traveled from: ");
			printf("\n1. UK");
			printf("\n2. Rest of Europe");
			printf("\n3. Asia");
			printf("\n4. Americas");
			printf("\n5. Australasia");
			printf("\nEnter Area Travelled: ");
			scanf("%d", &travelArea);

		} while (travelArea < 1 || travelArea > 5);
		//do-while

		switch (travelArea)
		{
		case 1:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "UK");
			break;

		case 2:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Rest of Europe");
			break;

		case 3:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Asia");
			break;

		case 4:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Americas");
			break;

		case 5:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Australasia");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch


		do
		{
			printf("\nPlease enter Travel Class to Ireland: ");
			printf("\n1. Economy");
			printf("\n2. Premium Economy");
			printf("\n3. Business Class");
			printf("\n4. First Class");
			printf("\nEnter Travel Class: ");
			scanf("%d", &travelClass);

		} while (travelClass < 1 || travelClass > 4);
		//do-while


		switch (travelClass)
		{
		case 1:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "Economy");
			break;

		case 2:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "Premium Economy");
			break;

		case 3:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "Business Class");
			break;

		case 4:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "First Class");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		do
		{
			printf("\nPlease enter number of Trips to Ireland per year: ");
			printf("\n1. Less than three times per year");
			printf("\n2. Less than five times per year");
			printf("\n3. More than five times per year");
			printf("\nEnter option: ");
			scanf("%d", &tripsIreland);

		} while (tripsIreland < 1 || tripsIreland > 3);
		//do-while


		switch (tripsIreland)
		{
		case 1:
			newPassenger->tripsToIrelandNum = tripsIreland;
			strcpy(newPassenger->tripsToIreland, "Less than three times per year");
			break;

		case 2:
			newPassenger->tripsToIrelandNum = tripsIreland;
			strcpy(newPassenger->tripsToIreland, "Less than five times per year");
			break;

		case 3:
			newPassenger->tripsToIrelandNum = tripsIreland;
			strcpy(newPassenger->tripsToIreland, "More than five times per year");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		do
		{
			printf("\nPlease enter Average Duration of Stay: ");
			printf("\n1. One day");
			printf("\n2. Less than 3 days");
			printf("\n3. Less than 7 days");
			printf("\n4. More than 7 days");
			printf("\nEnter Travel Class: ");
			scanf("%d", &duration);

		} while (duration < 1 || duration > 4);
		//do-while


		switch (duration)
		{
		case 1:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "One day");
			break;

		case 2:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "Less than 3 days");
			break;

		case 3:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "Less than 7 days");
			break;

		case 4:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "More than 7 days");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		curr = head;

		while (curr->next != NULL)
		{
			curr = curr->next;
		}//while

		curr->next = newPassenger;

		newPassenger->next = NULL;

	}
	else
	{
		printf("\nInvalid Passport Number Entered!!!\n");
	}//if

}//addToEnd

void addPassengerAtPos(struct passengerNode* head, int pos)
{
	struct passengerNode* temp;
	struct passengerNode* newPassenger;

	char *tempEmail;

	int travelArea, travelClass, tripsIreland, duration, passportNum;

	newPassenger = (struct passengerNode*)malloc(sizeof(struct passengerNode));

	tempEmail = (char*)malloc(30 * sizeof(char));

	printf("\nPlease enter Passport number: ");
	scanf("%d", &passportNum);

	newPassenger->passportNum = searchPassportNum(head, passportNum);

	if(newPassenger->passportNum != 0)
	{
		printf("\nPlease enter Passenger firstname: ");
		scanf("%s", newPassenger->firstName);

		printf("\nPlease enter Passenger lastname: ");
		scanf("%s", newPassenger->surName);

		printf("\nPlease enter Passenger Year of Birth: ");
		scanf("%d", &newPassenger->yob);

		do
		{
			printf("\nPlease enter Valid Passenger E-mail (myName@mail.com): ");
			scanf("%s", tempEmail);

			printf("\n%s email before method\n", tempEmail);

		} while (checkEmailAddress(tempEmail) == NULL);



		if (tempEmail == NULL)
		{
			printf("\nEmail Address %s Not Valid format!!! Please Try Again...\n", tempEmail);
			exit(0);
		}
		else
		{
			strcpy(newPassenger->email, tempEmail);
			free(tempEmail);
		}//if


		do
		{
			printf("\nPlease enter Area Traveled from: ");
			printf("\n1. UK");
			printf("\n2. Rest of Europe");
			printf("\n3. Asia");
			printf("\n4. Americas");
			printf("\n5. Australasia");
			printf("\nEnter Area Travelled: ");
			scanf("%d", &travelArea);

		} while (travelArea < 1 || travelArea > 5);
		//do-while

		switch (travelArea)
		{
		case 1:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "UK");
			break;

		case 2:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Rest of Europe");
			break;

		case 3:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Asia");
			break;

		case 4:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Americas");
			break;

		case 5:
			newPassenger->travelFromNum = travelArea;
			strcpy(newPassenger->travelFrom, "Australasia");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch


		do
		{
			printf("\nPlease enter Travel Class to Ireland: ");
			printf("\n1. Economy");
			printf("\n2. Premium Economy");
			printf("\n3. Business Class");
			printf("\n4. First Class");
			printf("\nEnter Travel Class: ");
			scanf("%d", &travelClass);

		} while (travelClass < 1 || travelClass > 4);
		//do-while


		switch (travelClass)
		{
		case 1:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "Economy");
			break;

		case 2:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "Premium Economy");
			break;

		case 3:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "Business Class");
			break;

		case 4:
			newPassenger->travelClassNum = travelClass;
			strcpy(newPassenger->travelClass, "First Class");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		do
		{
			printf("\nPlease enter number of Trips to Ireland per year: ");
			printf("\n1. Less than three times per year");
			printf("\n2. Less than five times per year");
			printf("\n3. More than five times per year");
			printf("\nEnter option: ");
			scanf("%d", &tripsIreland);

		} while (tripsIreland < 1 || tripsIreland > 3);
		//do-while


		switch (tripsIreland)
		{
		case 1:
			newPassenger->tripsToIrelandNum = tripsIreland;
			strcpy(newPassenger->tripsToIreland, "Less than three times per year");
			break;

		case 2:
			newPassenger->tripsToIrelandNum = tripsIreland;
			strcpy(newPassenger->tripsToIreland, "Less than five times per year");
			break;

		case 3:
			newPassenger->tripsToIrelandNum = tripsIreland;
			strcpy(newPassenger->tripsToIreland, "More than five times per year");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		do
		{
			printf("\nPlease enter Average Duration of Stay: ");
			printf("\n1. One day");
			printf("\n2. Less than 3 days");
			printf("\n3. Less than 7 days");
			printf("\n4. More than 7 days");
			printf("\nEnter Duration of stay: ");
			scanf("%d", &duration);

		} while (duration < 1 || duration > 4);
		//do-while


		switch (duration)
		{
		case 1:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "One day");
			break;

		case 2:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "Less than 3 days");
			break;

		case 3:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "Less than 7 days");
			break;

		case 4:
			newPassenger->averageDurationNum = duration;
			strcpy(newPassenger->averageDuration, "More than 7 days");
			break;

		default:
			printf("\nInvalid option!!! Try Again...\n");

		}//switch

		temp = head;

		for (int i = 0; i < pos - 2; i++)
		{
			temp = temp->next;
		}//for

		newPassenger->next = temp->next;
		temp->next = newPassenger;

	}
	else
	{
		printf("\nInvalid Passport Number Entered!!!\n");
		return;
	}//if

}//addAtPos

//display list sorted function
void displayList(struct passengerNode* head, int size)
{
	//temp struct
	struct passengerNode* temp;
	
	//helper vars & int pointer declared
	int counter = 0, tempInt, *ptr;

	//assign head totemp
	temp = head;

	//malloc ptr for ints
	ptr = (int*)malloc(size * sizeof(int));

	//loop through list
	while (temp != NULL)
	{
		//assign passport number to address in memory
		*(ptr + counter) = temp->passportNum;
		//increment counter for next address
		counter++;
		//next item in list
		temp = temp->next;
	}//while

	//bubble sort memory addresses from lowest to highest size var from list length function
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (*(ptr + i) > *(ptr + j))
			{
				tempInt = *(ptr + i);
				*(ptr + i) = *(ptr + j);
				*(ptr + j) = tempInt;
			}//if
		}

	}//for

	//assign temp to head again after first loop
	temp = head;

	//assign counter to 0 again after loop
	counter = 0;

	//loop less than list length size
	for (int i = 0; i < size; i++)
	{
		//while loop through list
		while (temp != NULL)
		{
			//check if pointer address = to list passport number and print passenger
			if (*(ptr + i) == temp->passportNum)
			{
				counter++;
				printf("\nPassenger %d\n", counter);
				printf("\nPassenger Name: %s %s\n", temp->firstName, temp->surName);
				printf("\nPassport Number: %d\n", temp->passportNum);
				printf("\nPassenger Year of Birth: %d\n", temp->yob);
				printf("\nPassenger E-mail: %s\n", temp->email);
				printf("\nPassenger Area Travelled from: %d - %s\n", temp->travelFromNum, temp->travelFrom);
				printf("\nPassenger Travel Class: %d - %s\n", temp->travelClassNum, temp->travelClass);
				printf("\nTrips to Ireland per year: %d - %s\n", temp->tripsToIrelandNum, temp->tripsToIreland);
				printf("\nPassenger Average duration of stay: %d - %s\n\n", temp->averageDurationNum, temp->averageDuration);
			}//if

			//move temp to next in list
			temp = temp->next;

		}//while

		//assign temp to start of list for next iteration in for loop
		temp = head;

	}//for

}//displayList

int listLength(struct passengerNode* head)
{
	struct passengerNode* temp;

	int counter = 1;

	temp = head;

	while(temp->next != NULL)
	{
		counter++;
		temp = temp->next;
	}

	return counter;

}//listLength

//search passenger details
void searchPassengerDetails(struct passengerNode* head)
{
	//vars for options and search functions
	int passportNum, option, counter = 1;
	char firstName[20], surName[20];

	//temp structure
	struct passengerNode* temp;

	//assign head to temp
	temp = head;

	//do-while option for search
	do
	{
		printf("\nChoose from search options");
		printf("\n1. Search Passport number");
		printf("\n2. Search Passenger name");
		printf("\nEnter option: ");
		scanf("%d", &option);
	} while(option < 1 || option > 2);

	//switch option for search passport number or first and last name
	switch(option)
	{
	case 1:
		//case 1 - prompt for passport number to search and loop through list and compare passport number
		//return if passport number found
		printf("\nPlease enter Passport number to search: ");
		scanf("%d", &passportNum);

		while(temp != NULL)
		{
			if(passportNum == temp->passportNum)
			{
				printf("\nPassenger Found at position %d in Database\n", counter);
				printf("\nPassenger Name: %s %s\n", temp->firstName, temp->surName);
				printf("\nPassport Number: %d\n", temp->passportNum);
				printf("\nPassenger Year of Birth: %d\n", temp->yob);
				printf("\nPassenger E-mail: %s\n", temp->email);
				printf("\nPassenger Area Travelled from: %d - %s\n", temp->travelFromNum, temp->travelFrom);
				printf("\nPassenger Travel Class: %d - %s\n", temp->travelClassNum, temp->travelClass);
				printf("\nTrips to Ireland per year: %d - %s\n", temp->tripsToIrelandNum, temp->tripsToIreland);
				printf("\nPassenger Average duration of stay: %d - %s\n\n", temp->averageDurationNum, temp->averageDuration);
				return;
			}
			else
			{
				counter++;
				temp = temp->next;
			}//if

		}//while

		printf("\nPassport number %d not found in Database!!! Please try again...\n", passportNum);

		break;

	case 2:
		//case 2 - prompt for first and last name search list and compare names to names in list
		//return if found 
		printf("\nPlease enter Passenger firstname to search: ");
		scanf("%s", firstName);
		
		printf("\nPlease enter Passenger lastname to search: ");
		scanf("%s", surName);

		while (temp != NULL)
		{
			if (strcmp(firstName, temp->firstName) == 0 && strcmp(surName, temp->surName) == 0)
			{
				printf("\nPassenger Found at position %d in Database\n", counter);
				printf("\nPassenger Name: %s %s\n", temp->firstName, temp->surName);
				printf("\nPassport Number: %d\n", temp->passportNum);
				printf("\nPassenger Year of Birth: %d\n", temp->yob);
				printf("\nPassenger E-mail: %s\n", temp->email);
				printf("\nPassenger Area Travelled from: %d - %s\n", temp->travelFromNum, temp->travelFrom);
				printf("\nPassenger Travel Class: %d - %s\n", temp->travelClassNum, temp->travelClass);
				printf("\nTrips to Ireland per year: %d - %s\n", temp->tripsToIrelandNum, temp->tripsToIreland);
				printf("\nPassenger Average duration of stay: %d - %s\n\n", temp->averageDurationNum, temp->averageDuration);
				return;
			}
			else
			{
				counter++;
				temp = temp->next;
			}//if

		}//while

		printf("\nPassenger name %s %s not found in Database!!! Please try again...\n", firstName, surName);

		break;

	default:
		printf("\nInvalid option!!! Try Again...\n");
	
	}//switch

}//searchPassengerDetails

//update passenger by passport number
void updatePassengerByNumber(struct passengerNode* head, int passport)
{
	//temp structure for list
	struct passengerNode* temp;

	//vars for string manipulation & counter
	int travelClass, travelArea, tripsIreland, duration, counter = 1;

	//assign head to temp
	temp = head;

	//loop through list
	while (temp != NULL)
	{
		//if passport number matches start update of passenger details
		if (passport == temp->passportNum)
		{
			printf("\nPassenger passport number Found at position %d in Database\n", counter);

			//do-while to update passenger travel area
			do
			{
				printf("\nPlease enter Area Traveled from: ");
				printf("\n1. UK");
				printf("\n2. Rest of Europe");
				printf("\n3. Asia");
				printf("\n4. Americas");
				printf("\n5. Australasia");
				printf("\nEnter Area Travelled: ");
				scanf("%d", &travelArea);

			} while (travelArea < 1 || travelArea > 5);
			//do-while

			//switch otion for string assignment
			switch (travelArea)
			{
			case 1:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "UK");
				break;

			case 2:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "Rest of Europe");
				break;

			case 3:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "Asia");
				break;

			case 4:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "Americas");
				break;

			case 5:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "Australasia");
				break;

			default:
				printf("\nInvalid option!!! Try Again...\n");

			}//switch

			 //do-while to update passenger travel class
			do
			{
				printf("\nPlease enter Travel Class to Ireland: ");
				printf("\n1. Economy");
				printf("\n2. Premium Economy");
				printf("\n3. Business Class");
				printf("\n4. First Class");
				printf("\nEnter Travel Class: ");
				scanf("%d", &travelClass);

			} while (travelClass < 1 || travelClass > 4);
			//do-while

			//switch otion for string assignment
			switch (travelClass)
			{
			case 1:
				temp->travelClassNum = travelClass;
				strcpy(temp->travelClass, "Economy");
				break;

			case 2:
				temp->travelClassNum = travelClass;
				strcpy(temp->travelClass, "Premium Economy");
				break;

			case 3:
				temp->travelClassNum = travelClass;
				strcpy(temp->travelClass, "Business Class");
				break;

			case 4:
				temp->travelClassNum = travelClass;
				strcpy(temp->travelClass, "First Class");
				break;

			default:
				printf("\nInvalid option!!! Try Again...\n");

			}//switch

			do
			{
				printf("\nPlease enter number of Trips to Ireland per year: ");
				printf("\n1. Less than three times per year");
				printf("\n2. Less than five times per year");
				printf("\n3. More than five times per year");
				printf("\nEnter option: ");
				scanf("%d", &tripsIreland);

			} while (tripsIreland < 1 || tripsIreland > 3);
			//do-while


			switch (tripsIreland)
			{
			case 1:
				temp->tripsToIrelandNum = tripsIreland;
				strcpy(temp->tripsToIreland, "Less than three times per year");
				break;

			case 2:
				temp->tripsToIrelandNum = tripsIreland;
				strcpy(temp->tripsToIreland, "Less than five times per year");
				break;

			case 3:
				temp->tripsToIrelandNum = tripsIreland;
				strcpy(temp->tripsToIreland, "More than five times per year");
				break;

			default:
				printf("\nInvalid option!!! Try Again...\n");

			}//switch

			do
			{
				printf("\nPlease enter Average Duration of Stay: ");
				printf("\n1. One day");
				printf("\n2. Less than 3 days");
				printf("\n3. Less than 7 days");
				printf("\n4. More than 7 days");
				printf("\nEnter Travel Class: ");
				scanf("%d", &duration);

			} while (duration < 1 || duration > 4);
			//do-while


			switch (duration)
			{
			case 1:
				temp->averageDurationNum = duration;
				strcpy(temp->averageDuration, "One day");
				break;

			case 2:
				temp->averageDurationNum = duration;
				strcpy(temp->averageDuration, "Less than 3 days");
				break;

			case 3:
				temp->averageDurationNum = duration;
				strcpy(temp->averageDuration, "Less than 7 days");
				break;

			case 4:
				temp->averageDurationNum = duration;
				strcpy(temp->averageDuration, "More than 7 days");
				break;

			default:
				printf("\nInvalid option!!! Try Again...\n");

			}//switch

			printf("\nPassenger Statistics after user update\n");
			printf("\nPassenger Name: %s %s\n", temp->firstName, temp->surName);
			printf("\nPassport Number: %d\n", temp->passportNum);
			printf("\nPassenger Year of Birth: %d\n", temp->yob);
			printf("\nPassenger E-mail: %s\n", temp->email);
			printf("\nPassenger Area Travelled from: %d - %s\n", temp->travelFromNum, temp->travelFrom);
			printf("\nPassenger Travel Class: %d - %s\n", temp->travelClassNum, temp->travelClass);
			printf("\nTrips to Ireland per year: %d - %s\n", temp->tripsToIrelandNum, temp->tripsToIreland);
			printf("\nPassenger Average duration of stay: %d - %s\n\n", temp->averageDurationNum, temp->averageDuration);

			return;

		}
		else
		{
			counter++;
			temp = temp->next;
		}//if

	}//while

	printf("\nPassport number %d not found in Database!!! Please try again...\n", passport);


}//updateByPassportNumber

//update passenger by name
void updatePassengerByName(struct passengerNode* head, char first[20], char last[20])
{
	//temp node
	struct passengerNode* temp;

	//counter
	int counter = 1;

	//ints for string assignment
	int travelArea, travelClass, tripsIreland, duration;

	//assign head to temp
	temp = head;

	//loop through list
	while (temp != NULL)
	{
		//compare first name and last name to passed in strings update details if found
		if (strcmp(first, temp->firstName) == 0 && strcmp(last, temp->surName) == 0)
		{
			printf("\n%s %s Found in Database!!!\n", first, last);

			//if found update passenger details
			//do-while travel area
			do
			{
				printf("\nPlease enter Area Traveled from: ");
				printf("\n1. UK");
				printf("\n2. Rest of Europe");
				printf("\n3. Asia");
				printf("\n4. Americas");
				printf("\n5. Australasia");
				printf("\nEnter Area Travelled: ");
				scanf("%d", &travelArea);

			} while (travelArea < 1 || travelArea > 5);
			//do-while

			//switch option for string manipulation
			switch (travelArea)
			{
			case 1:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "UK");
				break;

			case 2:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "Rest of Europe");
				break;

			case 3:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "Asia");
				break;

			case 4:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "Americas");
				break;

			case 5:
				temp->travelFromNum = travelArea;
				strcpy(temp->travelFrom, "Australasia");
				break;

			default:
				printf("\nInvalid option!!! Try Again...\n");

			}//switch

			//do-while travel class
			do
			{
				printf("\nPlease enter Travel Class to Ireland: ");
				printf("\n1. Economy");
				printf("\n2. Premium Economy");
				printf("\n3. Business Class");
				printf("\n4. First Class");
				printf("\nEnter Travel Class: ");
				scanf("%d", &travelClass);

			} while (travelClass < 1 || travelClass > 4);
			//do-while

			//switch travel class for string assignment 
			switch (travelClass)
			{
			case 1:
				temp->travelClassNum = travelClass;
				strcpy(temp->travelClass, "Economy");
				break;

			case 2:
				temp->travelClassNum = travelClass;
				strcpy(temp->travelClass, "Premium Economy");
				break;

			case 3:
				temp->travelClassNum = travelClass;
				strcpy(temp->travelClass, "Business Class");
				break;

			case 4:
				temp->travelClassNum = travelClass;
				strcpy(temp->travelClass, "First Class");
				break;

			default:
				printf("\nInvalid option!!! Try Again...\n");

			}//switch

			//do-while trips to ireland
			do
			{
				printf("\nPlease enter number of Trips to Ireland per year: ");
				printf("\n1. Less than three times per year");
				printf("\n2. Less than five times per year");
				printf("\n3. More than five times per year");
				printf("\nEnter option: ");
				scanf("%d", &tripsIreland);

			} while (tripsIreland < 1 || tripsIreland > 3);
			//do-while

			//switch trips ireland for string assignment
			switch (tripsIreland)
			{
			case 1:
				temp->tripsToIrelandNum = tripsIreland;
				strcpy(temp->tripsToIreland, "Less than three times per year");
				break;

			case 2:
				temp->tripsToIrelandNum = tripsIreland;
				strcpy(temp->tripsToIreland, "Less than five times per year");
				break;

			case 3:
				temp->tripsToIrelandNum = tripsIreland;
				strcpy(temp->tripsToIreland, "More than five times per year");
				break;

			default:
				printf("\nInvalid option!!! Try Again...\n");

			}//switch

			//do-while average stay
			do
			{
				printf("\nPlease enter Average Duration of Stay: ");
				printf("\n1. One day");
				printf("\n2. Less than 3 days");
				printf("\n3. Less than 7 days");
				printf("\n4. More than 7 days");
				printf("\nEnter Travel Class: ");
				scanf("%d", &duration);

			} while (duration < 1 || duration > 4);
			//do-while

			//switch average stay for string assignment 
			switch (duration)
			{
			case 1:
				temp->averageDurationNum = duration;
				strcpy(temp->averageDuration, "One Day");
				break;

			case 2:
				temp->averageDurationNum = duration;
				strcpy(temp->averageDuration, "Less than 3 Days");
				break;

			case 3:
				temp->averageDurationNum = duration;
				strcpy(temp->averageDuration, "Less than 7 Days");
				break;

			case 4:
				temp->averageDurationNum = duration;
				strcpy(temp->averageDuration, "More than 7 Days");
				break;
			default:
				printf("\nInvalid option!!! Try Again...\n");

			}//switch

			printf("\nPassenger Statistics after user update\n");
			printf("\nPassenger at position %d in List", counter);
			printf("\nPassport Number: %d\n", temp->passportNum);
			printf("\nPassenger Name: %s %s\n", temp->firstName, temp->surName);
			printf("\nPassenger Year of Birth: %d\n", temp->yob);
			printf("\nPassenger E-mail: %s\n", temp->email);
			printf("\nPassenger Area Travelled from: %d - %s\n", temp->travelFromNum, temp->travelFrom);
			printf("\nPassenger Travel Class: %d - %s\n", temp->travelClassNum, temp->travelClass);
			printf("\nTrips to Ireland per year: %d - %s\n", temp->tripsToIrelandNum, temp->tripsToIreland);
			printf("\nPassenger Average duration of stay: %d - %s\n\n", temp->averageDurationNum, temp->averageDuration);
			//return once updated
			return;
		}
		else
		{
			//increment counter & move temp to nexr
			counter++;
			temp = temp->next;
		}//if

	}//while

	//if not found
	printf("\nPassenger name %s %s not found in Database!!! Please try again...\n", first, last);

}//updateByName

//update passenger stats
void updatePassengerStatistic(struct passengerNode* head)
{
	//int vars for passport number and option
	int passportNum, option;

	//strings for passenger name
	char firstName[20], surName[20];

	//do-while option validation
	do
	{
		printf("\nChoose from search options");
		printf("\n1. Search Passport number");
		printf("\n2. Search Passenger name");
		printf("\nEnter option: ");
		scanf("%d", &option);
	} while (option < 1 || option > 2);

	//switch option entered
	switch (option)
	{
	case 1:
		//case 1 enter passport number and call update by passport num function
		printf("\nPlease enter Passport number to search: ");
		scanf("%d", &passportNum);

		updatePassengerByNumber(head, passportNum);
		break;

	case 2:
		//case 2 - enter names and call update by name function
		printf("\nPlease enter Passenger firstname to search: ");
		scanf("%s", firstName);

		printf("\nPlease enter Passenger lastname to search: ");
		scanf("%s", surName);

		updatePassengerByName(head, firstName, surName);
		
		break;

	default:
		printf("\nInvalid option!!! Try Again...\n");

	}//switch


}//updatePassengerDetails

void deletePassengerAtStart(struct passengerNode** head)
{
	struct passengerNode* temp;

	temp = *head;

	*head = temp->next;

	free(temp);

}//deleteAtStart

void deletePassengerAtEnd(struct passengerNode* head)
{
	struct passengerNode* temp;
	struct passengerNode* prev;

	temp = head;

	while(temp->next != NULL)
	{
		prev = temp;
		temp = temp->next;
	}//while

	prev->next = NULL;
	
	free(temp);

}//deleteAtEnd

void deletePassengerAtPos(struct passengerNode* head, int pos)
{
	struct passengerNode* temp;
	struct passengerNode* prev;

	temp = head;

	for(int i = 0; i < pos - 1; i++)
	{
		prev = temp;
		temp = temp->next;
	}//for

	prev->next = temp->next;

	free(temp);

}//deleteAtPos

//generate passenger stats function
void generatePassengerStats(struct passengerNode* head)
{
	int option;

	//do-while validation
	do
	{
		printf("\nPlease choose from options listed below to Generate Statistics base upon:");
		printf("\n1. Travel Class");
		printf("\n2. Born Before 1980");
		printf("\nEnter option: ");
		scanf("%d", &option);

	} while (option < 1 || option > 2);
	
	//switch option entered
	switch(option)
	{
	case 1:
		//case 1 call get travel class stats
		printf("\nTravel Class Statistics");
		printf("\n========================\n");

		getTravelClassStats(head);
		
		break;

	case 2:
		//case 2 call get 1980 travel stats
		printf("\nTravel Class Statistics");
		printf("\n========================\n");

		get1980TravelStats(head);

		break;

	default:
		printf("\nInvalid option!!! Try Again...\n");
	}//switch



}//generateStats

//generate stats based on travel class function
void getTravelClassStats(struct passengerNode* head)
{
	//temp struct
	struct passengerNode* temp;

	//counter & option vars
	int statCounter = 0, classOption;

	//option & travel class string
	char option, travelClass[20];

	//per cent var
	float perCent;

	//assign head to temp
	temp = head;

	//do-while validate travel class option
	do
	{
		printf("\nSelect Travel Class to Generate Statistics");
		printf("\n1. Economy");
		printf("\n2. Premium Economy");
		printf("\n3. Business Class");
		printf("\n4. First Class");
		printf("\nEnter option: ");
		scanf("%d", &classOption);

	} while(classOption < 1 || classOption > 4);
	//do-while

	//switch option for string assignment
	switch(classOption)
	{
	case 1:
		strcpy(travelClass, "Economy");
		break;

	case 2:
		strcpy(travelClass, "Premium Economy");
		break;

	case 3:
		strcpy(travelClass, "Business Class");
		break;

	case 4:
		strcpy(travelClass, "First Class");
		break;

	default:
		printf("\nInvalid option!!! Try Again...\n");

	}//switch

	//print menu to prompt user for stat generation
	printf("\nTravel Class Statistic list");
	printf("\nPlease Enter Character from list below to Generate Statistics");
	printf("\nA. %% of Passengers who travel from the UK");
	printf("\nB. %% of Passengers who travel from Rest of Europe");
	printf("\nC. %% of Passengers who travel from Asia");
	printf("\nD. %% of Passengers who travel from the Americas");
	printf("\nE. %% of Passengers who travel from Australasia");
	printf("\nF. %% of Passengers who spent on average one day in Ireland");
	printf("\nG. %% of Passengers who spent on average less than 3 days in Ireland");
	printf("\nH. %% of Passengers who spent on average less than 7 days in Ireland");
	printf("\nI. %% of Passengers who spent on average more than 7 days in Ireland\n");
	printf("Enter option: ");
	scanf(" %c", &option);
	
	//switch menu option entered
	switch (option)
	{
	case 'a':
	case 'A':
		//case A generate stats for UK & travel class
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "UK") == 0 && strcmp(temp->travelClass, travelClass) == 0)
			{
				statCounter++;
			}//if

			temp = temp->next;
		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from the UK & in Travel class %s is %.2f %%\n", travelClass, perCent);

		break;

	case 'b':
	case 'B':
		//case B generate stats for Rest of Europe & travel class
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "Rest of Europe") == 0 && strcmp(temp->travelClass, travelClass) == 0)
			{
				statCounter++;
			}//if

			temp = temp->next;
		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from the Rest of Europe & in Travel class %s is %.2f %%\n", travelClass, perCent);

		break;

	case 'c':
	case 'C':
		//case C generate stats for Asia & travel class
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "Asia") == 0 && strcmp(temp->travelClass, travelClass) == 0)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from Asia & in Travel class %s is %.2f %%\n", travelClass, perCent);

		break;

	case 'd':
	case 'D':
		//case D generate stats for Americas & travel class
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "Americas") == 0 && strcmp(temp->travelClass, travelClass) == 0)
			{
				statCounter++;
			}//if

			temp = temp->next;
		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from the Americas & in Travel class %s is %.2f %%\n", travelClass, perCent);

		break;

	case 'e':
	case 'E':
		//case E generate stats for Austarlasia & travel class
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "Australasia") == 0 && strcmp(temp->travelClass, travelClass) == 0)
			{
				statCounter++;
			}//if

			temp = temp->next;
		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from the Australasia & in Travel class %s is %.2f %%\n", travelClass, perCent);

		break;

	case 'f':
	case 'F':
		//case F generate stats for 1 day stay & travel class
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->averageDuration, "One Day") == 0 && strcmp(temp->travelClass, travelClass) == 0)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;

		printf("\n%% of Passengers in Database who spent on Average one day in Ireland & in Travel class %s is %.2f %%\n", travelClass, perCent);

		break;

	case 'g':
	case 'G':
		//case G generate stats for less than 3 day stay & travel class
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->averageDuration, "Less than 3 Days") == 0 && strcmp(temp->travelClass, travelClass) == 0)
			{
				statCounter++;
			}//if

			temp = temp->next;
		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;

		printf("\n%% of Passengers in Database who spent on Average less than 3 days in Ireland & in Travel class %s is %.2f %%\n", travelClass, perCent);

		break;

	case 'h':
	case 'H':
		//case H generate stats for less than 7 day stay & travel class
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->averageDuration, "Less than 7 Days") == 0 && strcmp(temp->travelClass, travelClass) == 0)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;

		printf("\n%% of Passengers in Database who spent on Average less than 7 days in Ireland & in Travel class %s & in Travel Class %s is %.2f %%\n", travelClass, perCent);

		break;

	case 'i':
	case 'I':
		//case I generate stats for more than 7 day stay & travel class

		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->averageDuration, "More than 7 Days") == 0 && strcmp(temp->travelClass, travelClass) == 0)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		//per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;

		printf("\n%% of Passengers in Database who spent on Average more than 7 days in Ireland & in Travel class %s is %.2f %%\n", travelClass, perCent);

		break;

		//invalid option case
	default:
		printf("\nInvalid option!!! Try Again...\n");

	}//switch

}//GetTravelClassStats

//generate stats on passengers born before 1980 function
void get1980TravelStats(struct passengerNode* head)
{
	//counter
	int statCounter = 0;

	//var for per cent
	float perCent;

	//option char var
	char option;

	//temp structure
	struct passengerNode* temp;

	//assign head to temp
	temp = head;

	//print menu to prompt user for stat generation
	printf("\nPassenger Born before 1980 Statistic list");
	printf("\nPlease Enter Character from list below to Generate Statistics");
	printf("\nA. %% of Passengers who travel from the UK");
	printf("\nB. %% of Passengers who travel from Rest of Europe");
	printf("\nC. %% of Passengers who travel from Asia");
	printf("\nD. %% of Passengers who travel from the Americas");
	printf("\nE. %% of Passengers who travel from Australasia");
	printf("\nF. %% of Passengers who spent on average one day in Ireland");
	printf("\nG. %% of Passengers who spent on average less than 3 days in Ireland");
	printf("\nH. %% of Passengers who spent on average less than 7 days in Ireland");
	printf("\nI. %% of Passengers who spent on average more than 7 days in Ireland\n");
	printf("Enter option: ");
	scanf(" %c", &option);

	//switch menu option entered
	switch (option)
	{
	case 'a':
	case 'A':
		//case A generate stats for UK & yob before 1980
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "UK") == 0 && temp->yob < 1980)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from the UK & are Born before 1980 is %.2f %%\n", perCent);
		
		break;

	case 'b':
	case 'B':
		//case B generate stats for Rest of Europe & yob before 1980
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "Rest of Europe") == 0 && temp->yob < 1980)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from the Rest of Europe & are Born before 1980 is %.2f %%\n", perCent);

		break;

	case 'c':
	case 'C':
		//case C generate stats for Asia & yob before 1980
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "Asia") == 0 && temp->yob < 1980)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from Asia & are Born before 1980 is %.2f %%\n", perCent);

		break;

	case 'd':
	case 'D':
		//case D generate stats for Americas & yob before 1980
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "Americas") == 0 && temp->yob < 1980)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from the Americas & are Born before 1980 is %.2f %%\n", perCent);

		break;

	case 'e':
	case 'E':
		//case E generate stats for Australasia & yob before 1980
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->travelFrom, "Australasia") == 0 && temp->yob < 1980)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who travel from the Australasia & are Born before 1980 is %.2f %%\n", perCent);

		break;

	case 'f':
	case 'F':
		//case F generate stats for 1 day stay & yob before 1980
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->averageDuration, "One Day") == 0 && temp->yob < 1980)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who spent on Average one day in Ireland & are Born before 1980 is %.2f %%\n", perCent);

		break;

	case 'g':
	case 'G':
		//case G generate stats for less than 3 day stay & yob before 1980
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->averageDuration, "Less than 3 Days") == 0 && temp->yob < 1980)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who spent on Average less than 3 days in Ireland & are Born before 1980 is %.2f %%\n", perCent);

		break;

	case 'h':
	case 'H':
		//case H generate stats for less than 7 day stay & yob before 1980
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->averageDuration, "Less than 7 Days") == 0 && temp->yob < 1980)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who spent on Average less than 7 days in Ireland & are Born before 1980 is %.2f %%\n", perCent);

		break;

	case 'i':
	case 'I':
		//case I generate stats for more than 7 day stay & yob before 1980
		while (temp != NULL)
		{
			//loop list & compare values for stat count
			if (strcmp(temp->averageDuration, "More than 7 Days") == 0 && temp->yob < 1980)
			{
				statCounter++;
			}//if

			temp = temp->next;

		}//while

		 //per cent formula
		perCent = ((float)statCounter / listLength(head)) * 100;
		printf("\n%% of Passengers in Database who spent on Average more than 7 days in Ireland & are Born before 1980 is %.2f %%\n", perCent);

		break;

		//invalid option entered
	default:
		printf("\nInvalid option!!! Try Again...\n");

	}//switch

}//get1980TravelStats

//print passenger database to file
void printPassengerFile(FILE** database, FILE** details, struct passengerNode* head, int size)
{
	//open file for formatted database
	database = fopen("Database.txt", "w");

	//open file for load file details
	details = fopen("PassengerDetails.txt", "w");

	//declare temp struct
	struct passengerNode* temp;

	//int counter var, temp int for sorting & int pointer
	int counter = 0, tempInt, *ptr;

	//allocate space in memory for ints
	ptr = (int*)malloc(size * sizeof(int));

	//assign temp to head
	temp = head;

	//check for files opened
	if(database == NULL && details == NULL)
	{
		printf("\nFile could not be opened!!! Try again...\n");
	}
	else
	{
		//loop list and store passport numbers in memory
		while(temp != NULL)
		{
			*(ptr + counter) = temp->passportNum;
			counter++;
			temp = temp->next;
		}//while

		//sort those numbers in memory
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (*(ptr + i) > *(ptr + j))
				{
					tempInt = *(ptr + i);
					*(ptr + i) = *(ptr + j);
					*(ptr + j) = tempInt;
				}//if
			}

		}//for

		//reassign temp to head for next loop
		temp = head;

		//reassign counter to 0
		counter = 0;

		//loop for list length
		for(int i = 0; i < size; i++)
		{
			//loop through list
			while (temp != NULL)
			{
				//if list passport number matches sorted memory address print to file
				if(*(ptr + i) == temp->passportNum)
				{
					//increment counter
					counter++;

					//print formatted list to file
					fprintf(database, "\nPassenger %d\n", counter);
					fprintf(database, "\nPassenger Name: %s %s\n", temp->firstName, temp->surName);
					fprintf(database, "\nPassport Number: %d\n", temp->passportNum);
					fprintf(database, "\nPassenger Year of Birth: %d\n", temp->yob);
					fprintf(database, "\nPassenger E-mail: %s\n", temp->email);
					fprintf(database, "\nPassenger Area Travelled from: %d - %s\n", temp->travelFromNum, temp->travelFrom);
					fprintf(database, "\nPassenger Travel Class: %d - %s\n", temp->travelClassNum, temp->travelClass);
					fprintf(database, "\nTrips to Ireland per year: %d - %s\n", temp->tripsToIrelandNum, temp->tripsToIreland);
					fprintf(database, "\nPassenger Average duration of stay: %d - %s\n\n", temp->averageDurationNum, temp->averageDuration);

					//print to file for load file processing
					fprintf(details, "%d %s %s %d %s %d %d %d %d\n", temp->passportNum, temp->firstName, temp->surName, temp->yob, temp->email, temp->travelFromNum, temp->travelClassNum, temp->tripsToIrelandNum, temp->averageDurationNum);
					
				}//if

				//move temp to next in list
				temp = temp->next;

			}//while

			//reassign temp for next for loop iteration
			temp = head;

		}//for

		//close both files
		fclose(database);

		fclose(details);

		free(ptr);

		printf("\nDatabase written to Report File!!! Check Folder...\n");

	}//if

}//printPassengerFile

//list uk passengers by birth year function 
void listUkByBirthYear(struct passengerNode* head, int size)
{
	//temp structure
	struct passengerNode* temp;

	//ints pointer, counters & temp int for list processing
	int *ptr, ukCounter = 0, tempInt, countUk = 0;

	//assign temp to head
	temp = head;

	//allocate memory for ints
	ptr = (int*)malloc(size * sizeof(int));

	//loop through list and check for UK passengers
	while(temp != NULL)
	{
		if(strcmp(temp->travelFrom, "UK") == 0)
		{
			//if uk passenger found assign yob to memory pointer space 
			*(ptr + ukCounter) = temp->yob;
			//increment counter for next space in memory 
			ukCounter++;
		}//if

		temp = temp->next;

	}//while

	printf("\nNumber of UK Passengers %d\n", ukCounter);

	//reassign temp to head
	temp = head;

	//sort birth year memory addresses
	for(int i = 0; i < ukCounter; i++)
	{
		for(int j = i + 1; j < ukCounter; j++)
		{
			if(*(ptr + i) > *(ptr + j))
			{
				tempInt = *(ptr + i);
				*(ptr + i) = *(ptr + j);
				*(ptr + j) = tempInt;
			}//if
		}

	}//for

	//loop for uk counter var
	for(int i = 0; i < ukCounter; i++)
	{
		//loop to end of list
		while(temp != NULL)
		{
			//compare for uk passengers and birth year matches
			if(strcmp(temp->travelFrom, "UK") == 0 && *(ptr + i) == temp->yob)
			{
				//print sorted uk passenger list
				countUk++;
				printf("\nUK Passenger %d Birth Year %d\n", countUk, *(ptr + i));
				printf("\n=================================\n");
				printf("\nPassenger Name: %s %s\n", temp->firstName, temp->surName);
				printf("\nPassport Number: %d\n", temp->passportNum);
				printf("\nPassenger Year of Birth: %d\n", temp->yob);
				printf("\nPassenger E-mail: %s\n", temp->email);
				printf("\nPassenger Area Travelled from: %d - %s\n", temp->travelFromNum, temp->travelFrom);
				printf("\nPassenger Travel Class: %d - %s\n", temp->travelClassNum, temp->travelClass);
				printf("\nTrips to Ireland per year: %d - %s\n", temp->tripsToIrelandNum, temp->tripsToIreland);
				printf("\nPassenger Average duration of stay: %d - %s\n\n", temp->averageDurationNum, temp->averageDuration);
			}//if

			temp = temp->next;

		}//while

		//reassign temp to head for next for loop iteration
		temp = head;

	}//for

	//free memory for ptr
	free(ptr);

}//listUkByBirthYear


