#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define ENTER 13
#define BKSP 8
#define TAB 9
#define SPACE 32

struct passengerNode
{
	int passportNum;
	char firstName[20];
	char surName[20];
	int yob;
	char email[20];
	char travelFrom[20];
	int travelFromNum;
	char travelClass[20];
	int travelClassNum;
	char tripsToIreland[40];
	int tripsToIrelandNum;
	char averageDuration[30];
	int averageDurationNum;

	struct passengerNode* next;
};

struct login
{
	char username[20];
	char password[20];
};

void addPassengerToStart(struct passengerNode** head);
void addPassengerToEnd(struct passengerNode* head);
void addPassengerAtPos(struct passengerNode* head, int pos);
void searchPassengerDetails(struct passengerNode* head);
void displayList(struct passengerNode* head);
int listLength(struct passengerNode* head);
int userLogin(FILE** logIn, struct login* user);
void updatePassengerStatistic(struct passengerNode* head);
void deletePassengerAtStart(struct passengerNode** head);
void deletePassengerAtEnd(struct passengerNode* head);
void deletePassengerAtPos(struct passengerNode* head, int pos);
void generatePassengerStats(struct passengerNode* head);
void get1980TravelStats(struct passengerNode* head);
void getTravelClassStats(struct passengerNode* head);

void printPassengerFile(FILE** database, struct passengerNode* head);


void main()
{
	FILE* logInFile;
	FILE* outFile;
	struct passengerNode* head = NULL;
	struct login* user;
	int choice, pos, validate;

	user = (struct login*)malloc(sizeof(struct login));

	validate = userLogin(&logInFile, user);

	if (validate == 1)
	{
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

		while (choice != -1)
		{
			switch (choice)
			{
			case 1:

				printf("\nPlease Enter position to add Passenger in List: ");
				scanf("%d", &pos);

				if (pos < 2)
				{
					printf("\nAdding to start of Database\n");

					addPassengerToStart(&head);
				}
				else if (pos > listLength(head))
				{
					printf("\nAdd to End of Database\n");
					addPassengerToEnd(head);
				}
				else
				{
					printf("\nAdd at position %d\n", pos);
					addPassengerAtPos(head, pos);
				}

				break;

			case 2:
				printf("Display all Passengers in Databases Details\n");
				displayList(head);
				break;

			case 3:
				printf("\nSearch Passenger Details\n");
				searchPassengerDetails(head);
				break;

			case 4:
				printf("\nUpdate Passenger Statistic\n");
				updatePassengerStatistic(head);
				break;

			case 5:

				printf("\nPlease Enter position to Delete Passenger in List: ");
				scanf("%d", &pos);

				if(head == NULL)
				{
					printf("\nSorry Database is Empty\n");
				}
				else
				{
					if (pos < 2)
					{
						printf("\nDeleting at start of Database\n");

						deletePassengerAtStart(&head);
					}
					else if (pos >= 2 && pos < listLength(head))
					{
						printf("\nDelete at position %d in Database\n", pos);
						deletePassengerAtPos(head, pos);
					}
					else
					{
						printf("\nDelete at end of Database\n");
						deletePassengerAtEnd(head);
					}//if

				}//if

				break;

			case 6:
				printf("\nGenerate Passenger Statistics\n");
				generatePassengerStats(head);
				break;

			case 7:
				printf("\nPrint Database to Report File\n");
				printPassengerFile(&outFile, head);
				break;

			case 8:
				printf("\nPrint UK Passengers in order of Birth year\n");
				break;

			default:
				printf("\nWrong input!!! Please Try Again...\n");

			}//switch

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



}//main


//method list

int userLogin(FILE** logIn, struct login* user)
{
	logIn = fopen("users.txt", "r");

	char userNames[3][20];
	char ch;
	char passWords[3][20];
	int pos, i = 0;

	if(logIn == NULL)
	{
		printf("\nFile could not be opened!!! Try Again...\n");
		return 0;
	}
	else
	{
		printf("\nFile opened!!!\n");

		printf("Enter username (Case Sensitive): ");
		scanf("%s", user->username);

		printf("\nEnter Password (6 Characters): ");
		//scanf("%d", &user->password);
		
		while(1)
		{
			ch = getch();

			//ASCII value for enter = 13
			if(ch == ENTER)
			{
				user->password[i] = '\0';
				break;
			}
			else if(ch == BKSP)//backspace 8
			{
				if(i > 0)
				{
					i--;
					printf("\b \b");
				}
			}
			else if(ch == TAB || ch == SPACE)//tab 9 & space 32
			{
				continue;
			}
			else
			{
				user->password[i] = ch;
				i++;
				printf("*");
			}//if

		}//while

		//printf("\nPassword: %s\n", user->password);
		
		pos = 0;

		while(!feof(logIn))
		{
			fscanf(logIn, "%s %s", userNames[pos], passWords[pos]);

			//printf("\nScanned: %s %d", userNames[pos], passWords[pos]);

			if (strcmp(userNames[pos], user->username) == 0 && strcmp(passWords[pos], user->password) == 0)
			{
				printf("\nUser Found\n");
				printf("\nUsername Found: %s, Password: ****** Accepted\n", user->username);
				return 1;
			}
			
			if(feof(logIn))
			{
				printf("\nNot Found!!! Try Again...\n");
				printf("\nUserName: %s, Password: ******  Not Found Try Again!!!\n", user->username);
				return 0;
			}

			pos++;

		}//while

		fclose(logIn);

	}//if
}

void addPassengerToStart(struct passengerNode** head)
{
	struct passengerNode* newPassenger;

	int travelArea, travelClass, tripsIreland, duration;

	newPassenger = (struct passengerNode*)malloc(sizeof(struct passengerNode));

	printf("\nPlease enter Passport number: ");
	scanf("%d", &newPassenger->passportNum);

	printf("\nPlease enter Passenger firstname: ");
	scanf("%s", newPassenger->firstName);

	printf("\nPlease enter Passenger lastname: ");
	scanf("%s", newPassenger->surName);

	printf("\nPlease enter Passenger Year of Birth: ");
	scanf("%d", &newPassenger->yob);

	printf("\nPlease enter Passenger E-mail: ");
	scanf("%s", newPassenger->email);

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

	switch(travelArea)
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

	newPassenger->next = *head;

	*head = newPassenger;
	
}//addAtStart

void addPassengerToEnd(struct passengerNode* head)
{
	struct passengerNode* curr;
	struct passengerNode* newPassenger;

	int travelArea, travelClass, tripsIreland, duration;

	newPassenger = (struct passengerNode*)malloc(sizeof(struct passengerNode));

	printf("\nPlease enter Passport number: ");
	scanf("%d", &newPassenger->passportNum);

	printf("\nPlease enter Passenger firstname: ");
	scanf("%s", newPassenger->firstName);

	printf("\nPlease enter Passenger lastname: ");
	scanf("%s", newPassenger->surName);

	printf("\nPlease enter Passenger Year of Birth: ");
	scanf("%d", &newPassenger->yob);

	printf("\nPlease enter Passenger E-mail: ");
	scanf("%s", newPassenger->email);

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

	while(curr->next != NULL)
	{
		curr = curr->next;
	}//while

	curr->next = newPassenger;

	newPassenger->next = NULL;

}//addToEnd

void addPassengerAtPos(struct passengerNode* head, int pos)
{
	struct passengerNode* temp;
	struct passengerNode* newPassenger;

	int travelArea, travelClass, tripsIreland, duration;

	newPassenger = (struct passengerNode*)malloc(sizeof(struct passengerNode));

	printf("\nPlease enter Passport number: ");
	scanf("%d", &newPassenger->passportNum);

	printf("\nPlease enter Passenger firstname: ");
	scanf("%s", newPassenger->firstName);

	printf("\nPlease enter Passenger lastname: ");
	scanf("%s", newPassenger->surName);

	printf("\nPlease enter Passenger Year of Birth: ");
	scanf("%d", &newPassenger->yob);

	printf("\nPlease enter Passenger E-mail: ");
	scanf("%s", newPassenger->email);

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

	for(int i = 0; i < pos - 2; i++)
	{
		temp = temp->next;
	}//for

	newPassenger->next = temp->next;
	temp->next = newPassenger;

}//addAtPos

void displayList(struct passengerNode* head)
{
	struct passengerNode* temp;
	
	int counter = 0;

	temp = head;

	while(temp != NULL)
	{
		counter++;
		printf("\nPassenger %d\n", counter);
		printf("\nPassport Number: %d\n", temp->passportNum);
		printf("\nPassenger Name: %s %s\n", temp->firstName, temp->surName);
		printf("\nPassport Number: %d\n", temp->passportNum);
		printf("\nPassenger Year of Birth: %d\n", temp->yob);
		printf("\nPassenger E-mail: %s\n", temp->email);
		printf("\nPassenger Area Travelled from: %d - %s\n", temp->travelFromNum, temp->travelFrom);
		printf("\nPassenger Travel Class: %d - %s\n", temp->travelClassNum, temp->travelClass);
		printf("\nTrips to Ireland per year: %d - %s\n", temp->tripsToIrelandNum, temp->tripsToIreland);
		printf("\nPassenger Average duration of stay: %d - %s\n\n", temp->averageDurationNum, temp->averageDuration);
		temp = temp->next;

	}//while

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

void searchPassengerDetails(struct passengerNode* head)
{
	int passportNum, option, counter = 1;
	char firstName[20], surName[20];

	struct passengerNode* temp;

	temp = head;

	do
	{
		printf("\nChoose from search options");
		printf("\n1. Search Passport number");
		printf("\n2. Search Passenger name");
		printf("\nEnter option: ");
		scanf("%d", &option);
	} while(option < 1 || option > 2);

	switch(option)
	{
	case 1:
		printf("\nPlease enter Passport number to search: ");
		scanf("%d", &passportNum);

		while(temp != NULL)
		{
			if(passportNum == temp->passportNum)
			{
				printf("\nPassenger Found at position %d in Database\n", counter);
				printf("\nPassport Number: %d\n", temp->passportNum);
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

		printf("\nPlease enter Passenger firstname to search: ");
		scanf("%s", firstName);
		
		printf("\nPlease enter Passenger lastname to search: ");
		scanf("%s", surName);

		while (temp != NULL)
		{
			if (strcmp(firstName, temp->firstName) == 0 && strcmp(surName, temp->surName) == 0)
			{
				printf("\nPassenger Found at position %d in Database\n", counter);
				printf("\nPassport Number: %d\n", temp->passportNum);
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

void updatePassengerStatistic(struct passengerNode* head)
{
	struct passengerNode* temp;

	int passportNum, option, counter = 1;

	int travelArea, travelClass, tripsIreland, duration;

	char firstName[20], surName[20];

	temp = head;

	do
	{
		printf("\nChoose from search options");
		printf("\n1. Search Passport number");
		printf("\n2. Search Passenger name");
		printf("\nEnter option: ");
		scanf("%d", &option);
	} while (option < 1 || option > 2);

	switch (option)
	{
	case 1:
		printf("\nPlease enter Passport number to search: ");
		scanf("%d", &passportNum);

		while (temp != NULL)
		{
			if (passportNum == temp->passportNum)
			{
				printf("\nPassenger passport number Found at position %d in Database\n", counter);

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
				printf("\nPassport Number: %d\n", temp->passportNum);
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

		printf("\nPlease enter Passenger firstname to search: ");
		scanf("%s", firstName);

		printf("\nPlease enter Passenger lastname to search: ");
		scanf("%s", surName);

		while (temp != NULL)
		{
			if (strcmp(firstName, temp->firstName) == 0 && strcmp(surName, temp->surName) == 0)
			{
				printf("\n%s %s Found in Database!!!\n", firstName, surName);

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
				printf("\nPassport Number: %d\n", temp->passportNum);
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
				temp = temp->next;
			}//if

		}//while

		printf("\nPassenger name %s %s not found in Database!!! Please try again...\n", firstName, surName);

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

void generatePassengerStats(struct passengerNode* head)
{
	int option;

	printf("\nPlease choose from options listed below to Generate Statistics base upon:");
	printf("\n1. Travel Class");
	printf("\n2. Born Before 1980");
	printf("\nEnter option: ");
	scanf("%d", &option);

	switch(option)
	{
	case 1:

		printf("\nTravel Class Statistics");
		printf("\n========================\n");

		getTravelClassStats(head);
		
		break;

	case 2:

		printf("\nTravel Class Statistics");
		printf("\n========================\n");

		get1980TravelStats(head);

		break;

	default:
		printf("\nInvalid option!!! Try Again...\n");
	}//switch



}//generateStats

void getTravelClassStats(struct passengerNode* head)
{
	struct passengerNode* temp;

	int listCounter = 0;

	int  fromUkCount = 0, fromRestOfEuropeCount = 0, fromAsiaCount = 0;

	int fromAmericasCount = 0, fromAustralasiaCount = 0;

	int oneDayIrelandCount = 0, lessThreeDayIrelandCount = 0, lessSevenDayIrelandCount = 0, moreSevenDayIrelandCount = 0;

	char option;

	float ukPerCent, roePerCent, asiaPerCent, americaPerCent, australasiaPerCent;

	float oneDayPerCent, lessThreePerCent, lessSevenPerCent, moreSevenPerCent;

	temp = head;

	while (temp != NULL)
	{
		listCounter++;
		temp = temp->next;

	}//while

	printf("\nNumber of Passengers in Database %d\n", listCounter);

	temp = head;

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
	//option = getchar();

	switch (option)
	{
	case 'a':
	case 'A':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "UK") == 0)
			{
				fromUkCount++;
			}//if

			temp = temp->next;

		}//while

		ukPerCent = ((float)fromUkCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from the UK is %.2f\n", ukPerCent);

		break;

	case 'b':
	case 'B':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "Rest of Europe") == 0)
			{
				fromRestOfEuropeCount++;
			}//if

			temp = temp->next;

		}//while

		roePerCent = ((float)fromRestOfEuropeCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from the Rest of Europe is %.2f %\n", roePerCent);

		break;

	case 'c':
	case 'C':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "Asia") == 0)
			{
				fromAsiaCount++;
			}//if

			temp = temp->next;

		}//while

		asiaPerCent = ((float)fromAsiaCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from Asia is %.2f %%\n", asiaPerCent);

		break;

	case 'd':
	case 'D':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "Americas") == 0)
			{
				fromAmericasCount++;
			}//if

			temp = temp->next;

		}//while

		americaPerCent = ((float)fromAmericasCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from the Americas is %.2f %\n", americaPerCent);

		break;

	case 'e':
	case 'E':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "Australasia") == 0)
			{
				fromAustralasiaCount++;
			}//if

			temp = temp->next;

		}//while

		australasiaPerCent = ((float)fromAustralasiaCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from the Australasia is %.2f %%\n", australasiaPerCent);

		break;

	case 'f':
	case 'F':

		while (temp != NULL)
		{
			if (strcmp(temp->averageDuration, "One Day") == 0)
			{
				oneDayIrelandCount++;
			}//if

			temp = temp->next;

		}//while

		oneDayPerCent = ((float)oneDayIrelandCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who spent on Average one day in Ireland is %.2f %%\n", oneDayPerCent);

		break;

	case 'g':
	case 'G':

		while (temp != NULL)
		{
			if (strcmp(temp->averageDuration, "Less than 3 Days") == 0)
			{
				lessThreeDayIrelandCount++;
			}//if

			temp = temp->next;

		}//while

		lessThreePerCent = ((float)lessThreeDayIrelandCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who spent on Average less than 3 days in Ireland is %.2f %%\n", lessThreePerCent);

		break;

	case 'h':
	case 'H':

		while (temp != NULL)
		{
			if (strcmp(temp->averageDuration, "Less than 7 Days") == 0)
			{
				lessSevenDayIrelandCount++;
			}//if

			temp = temp->next;

		}//while

		lessSevenPerCent = ((float)lessSevenDayIrelandCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who spent on Average less than 7 days in Ireland is %.2f %%\n", lessSevenPerCent);

		break;

	case 'i':
	case 'I':

		while (temp != NULL)
		{
			if (strcmp(temp->averageDuration, "More than 7 Days") == 0)
			{
				moreSevenDayIrelandCount++;
			}//if

			temp = temp->next;

		}//while

		moreSevenPerCent = ((float)moreSevenDayIrelandCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who spent on Average more than 7 days in Ireland is %.2f %%\n", moreSevenPerCent);

		break;

	default:
		printf("\nInvalid option!!! Try Again...\n");

	}//switch

}//GetTravelClassStats

void get1980TravelStats(struct passengerNode* head)
{
	int listCounter = 0;

	int  fromUkCount = 0, fromRestOfEuropeCount = 0, fromAsiaCount = 0;

	int fromAmericasCount = 0, fromAustralasiaCount = 0;

	int oneDayIrelandCount = 0, lessThreeDayIrelandCount = 0, lessSevenDayIrelandCount = 0, moreSevenDayIrelandCount = 0;

	int countryCount = 0, irelandCount = 0;

	float ukPerCent, roePerCent, asiaPerCent, americaPerCent, australasiaPerCent;

	float oneDayPerCent, lessThreePerCent, lessSevenPerCent, moreSevenPerCent;

	char option;

	struct passengerNode* temp;

	temp = head;

	while(temp != NULL)
	{
		listCounter++;
		temp = temp->next;

	}//while

	printf("\nNumber of Passengers in Database %d\n", listCounter);

	temp = head;

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
	//option = getchar();

	switch (option)
	{
	case 'a':
	case 'A':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "UK") == 0 && temp->yob < 1980)
			{
				fromUkCount++;
			}//if

			temp = temp->next;

		}//while

		ukPerCent = ((float)fromUkCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from the UK & are Born before 1980 is %.2f %%\n", ukPerCent);
		
		break;

	case 'b':
	case 'B':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "Rest of Europe") == 0 && temp->yob < 1980)
			{
				fromRestOfEuropeCount++;
			}//if

			temp = temp->next;

		}//while

		roePerCent = ((float)fromRestOfEuropeCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from the Rest of Europe & are Born before 1980 is %.2f %%\n", roePerCent);

		break;

	case 'c':
	case 'C':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "Asia") == 0 && temp->yob < 1980)
			{
				fromAsiaCount++;
			}//if

			temp = temp->next;

		}//while

		asiaPerCent = ((float)fromAsiaCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from Asia & are Born before 1980 is %.2f %%\n", asiaPerCent);

		break;

	case 'd':
	case 'D':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "Americas") == 0 && temp->yob < 1980)
			{
				fromAmericasCount++;
			}//if

			temp = temp->next;

		}//while

		americaPerCent = ((float)fromAmericasCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from the Americas & are Born before 1980 is %.2f %%\n", americaPerCent);

		break;

	case 'e':
	case 'E':

		while (temp != NULL)
		{
			if (strcmp(temp->travelFrom, "Australasia") == 0 && temp->yob < 1980)
			{
				fromAustralasiaCount++;
			}//if

			temp = temp->next;

		}//while

		australasiaPerCent = ((float)fromAustralasiaCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who travel from the Australasia & are Born before 1980 is %.2f %%\n", australasiaPerCent);

		break;

	case 'f':
	case 'F':

		while (temp != NULL)
		{
			if (strcmp(temp->averageDuration, "One Day") == 0 && temp->yob < 1980)
			{
				oneDayIrelandCount++;
			}//if

			temp = temp->next;

		}//while

		oneDayPerCent = ((float)oneDayIrelandCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who spent on Average one day in Ireland & are Born before 1980 is %.2f %%\n", oneDayPerCent);

		break;

	case 'g':
	case 'G':

		while (temp != NULL)
		{
			if (strcmp(temp->averageDuration, "Less than 3 Days") == 0 && temp->yob < 1980)
			{
				lessThreeDayIrelandCount++;
			}//if

			temp = temp->next;

		}//while

		lessThreePerCent = ((float)lessThreeDayIrelandCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who spent on Average less than 3 days in Ireland & are Born before 1980 is %.2f %%\n", lessThreePerCent);

		break;

	case 'h':
	case 'H':

		while (temp != NULL)
		{
			if (strcmp(temp->averageDuration, "Less than 7 Days") == 0 && temp->yob < 1980)
			{
				lessSevenDayIrelandCount++;
			}//if

			temp = temp->next;

		}//while

		lessSevenPerCent = ((float)lessSevenDayIrelandCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who spent on Average less than 7 days in Ireland & are Born before 1980 is %.2f %%\n", lessSevenPerCent);

		break;

	case 'i':
	case 'I':

		while (temp != NULL)
		{
			if (strcmp(temp->averageDuration, "More than 7 Days") == 0 && temp->yob < 1980)
			{
				moreSevenDayIrelandCount++;
			}//if

			temp = temp->next;

		}//while

		moreSevenPerCent = ((float)moreSevenDayIrelandCount / listCounter) * 100;

		printf("\n%% of Passengers in Database who spent on Average more than 7 days in Ireland & are Born before 1980 is %.2f %%\n", moreSevenPerCent);

		break;

	default:
		printf("\nInvalid option!!! Try Again...\n");

	}//switch

}//get1980TravelStats

void printPassengerFile(FILE** database, struct passengerNode* head)
{
	database = fopen("Database.txt", "w");

	struct passengerNode* temp;

	int counter = 0;

	temp = head;

	if(database == NULL)
	{
		printf("\nFile could not be opened!!! Try again...\n");
	}
	else
	{
		while (temp != NULL)
		{
			counter++;
			fprintf(database, "\nPassenger %d\n", counter);
			fprintf(database, "\nPassport Number: %d\n", temp->passportNum);
			fprintf(database, "\nPassenger Name: %s %s\n", temp->firstName, temp->surName);
			fprintf(database, "\nPassport Number: %d\n", temp->passportNum);
			fprintf(database, "\nPassenger Year of Birth: %d\n", temp->yob);
			fprintf(database, "\nPassenger E-mail: %s\n", temp->email);
			fprintf(database, "\nPassenger Area Travelled from: %d - %s\n", temp->travelFromNum, temp->travelFrom);
			fprintf(database, "\nPassenger Travel Class: %d - %s\n", temp->travelClassNum, temp->travelClass);
			fprintf(database, "\nTrips to Ireland per year: %d - %s\n", temp->tripsToIrelandNum, temp->tripsToIreland);
			fprintf(database, "\nPassenger Average duration of stay: %d - %s\n\n", temp->averageDurationNum, temp->averageDuration);
			temp = temp->next;

		}//while

		fclose(database);

		printf("\nDatabase written to Report File!!! Check Folder...\n");

	}//if

}//printPassengerFile