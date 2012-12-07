/*
 ============================================================================
 Name        : JRollAddressBook.c
 Author      : Justin Roll
 Version     :
 Copyright   : Copyright Cool Programs for Attractive People inc
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "main.h"

int main(void) {
	AddressBook* pAddressBook = (AddressBook*) malloc(sizeof(AddressBook));
	char buffer[BUFSIZ + 1];
	setvbuf(stdout, NULL, _IONBF, 0);
	int true = 1;
	printf("Ready\n");
	while (true) {
		gets(buffer);
		executeMasterAddressBook(buffer, pAddressBook);
		if (strstr(buffer, "q") != NULL) {
			true = 0;
			freeContactsInList(pAddressBook); //clean up structs in memory
			free(pAddressBook);
			printf("Complete\n");
		}
	}

	return EXIT_SUCCESS;
}

void deleteContactMaster(AddressBook* addressBook) {
	/*
	 * # Code:  d
	 # First parameter:  0-based index of the contact to delete.
	 #  NOTE:  if the index is higher than the number of contacts - 1, do nothing.
	 # Example:
	 d
	 *
	 */
	Contact* contactToDelete;
	char buffer[BUFSIZ + 1];
	int contactNum = -1;
	contactNum = atoi(gets(buffer));
	contactToDelete = getContactAtIndex(contactNum, addressBook);
	//get contact to delete
	if (contactToDelete != NULL)
		deleteContact(contactToDelete, addressBook);
}

void sanitizeString(char* string) {
	//this function is just to get rid of the \r\n at the end of a string
	if (string != NULL) {
		int count = 0;
		int currentIndex = strlen(string) - 1; //end index
		char* end = string + currentIndex;
		while (end > string && count < 2) {
			if ((*end == '\r') || (*end == '\n')) { //if we have nasty chars
				*end = 0; //terminate the string w/ 0
			}
			end--;
			count++;
		}
	}
}

void addContactMaster(AddressBook* addressBook) {
	Contact* contactToInsert;
	Contact* contactToInsertAfter;
	char numBuffer[BUFSIZ + 1];
	char stringBuffer[BUFSIZ + 1];
	int contactNum = -1;
	contactNum = atoi(gets(numBuffer));
	gets(stringBuffer);
	contactToInsert = createContact(stringBuffer);
	//get contact to delete
	contactToInsertAfter = getContactToInsertAfter(contactNum - 1, addressBook);
	insertContact(contactToInsert, contactToInsertAfter, addressBook);
}

void getContactMaster(AddressBook* addressBook) {
	Contact* gottenContact;
	char buffer[BUFSIZ + 1];
	int contactNum = -1;
	contactNum = atoi(gets(buffer));
	gottenContact = getContactAtIndex(contactNum, addressBook);
	if (gottenContact != NULL) {
		printf("%s,%s,%s,%s\n", gottenContact->lastName,
				gottenContact->firstName, gottenContact->emailAddress,
				gottenContact->phoneNumber);
	}
}

char* begToEndStringZero(char* stringText, int currentIndex) {
	//basically just substring the string, then sanitize and return

	char* returnString = (char*) malloc(256);
	strncpy(returnString, stringText + currentIndex, strlen(stringText)
			- currentIndex);
	sanitizeString(returnString); //remove /r/n
	return returnString;
}

void getSpecificFieldMaster(AddressBook* addressBook) {
	/*
	 * # Code: f
	 # First parameter:  0-based index of the contact.
	 # Second parameter: Name of the field to get.  Valid values are firstName, lastName, email, phoneNumber.
	 # Example:
	 f
	 1
	 lastName
	 # Output to stdout: The value of the requested field, terminated with a \n.  E.g. "SMITH\n"
	 */
	char buffer[BUFSIZ + 1];
	char fieldName[13];
	char* result;
	int contactNum = -1;
	contactNum = atoi(gets(buffer));
	gets(fieldName);
	result = findContactField(contactNum, fieldName, addressBook);
	printf("%s\n", result);
}

void getNumberofContactsMaster(AddressBook* addressBook) {
	//count number of contacts in the linked list
	int numContacts = countContacts(addressBook);
	printf("%d\n", numContacts);

}

void executeMasterAddressBook(char* cmd, AddressBook* addressBook) {
	/*a add (p1, string)
	 d delete (p1)
	 g get (p1)
	 f fieldget (p1, firstName, lastName, email, phoneNumber)
	 n number (no other params) */
	if (strstr(cmd, "d") != NULL)
		deleteContactMaster(addressBook); // these methods will prompt the user for the appropriate
	else if (strstr(cmd, "a") != NULL) // add
		addContactMaster(addressBook);
	else if (strstr(cmd, "g") != NULL) // get
		getContactMaster(addressBook);
	else if (strstr(cmd, "f") != NULL) //field
		getSpecificFieldMaster(addressBook);
	else if (strstr(cmd, "n") != NULL) //count
		getNumberofContactsMaster(addressBook);
	else if (strstr(cmd, "l") != NULL) //load
		loadContactListFromFileMaster(addressBook);
	else if (strstr(cmd, "s") != NULL) //save
		writeContactListToFileMaster(addressBook);
	else if (strstr(cmd, "e") != NULL) //edit
		editContactMaster(addressBook);

}
/*Edit Stuff
 * (EXTRA CREDIT)  Edit a contact:

 1. Code:  e
 2. First parameter:  0-based index of the contact that is to be changed.
 3. Second parameter: Name of the field to edit.  Valid values are firstName, lastName, email, phoneNumber.
 4. Third parameter: new value of the field.
 5. Example:
 e
 3
 phoneNumber
 8002220001
 *
 *
 */

void editContactMaster(AddressBook* addressBook) {
	/*Example edit
	 * 	e
	 3
	 phoneNumber
	 8002220001
	 *
	 */
	char buffer[BUFSIZ + 1];
	char fieldName[256];
	char newValue[256];
	char* result;
	int contactNum = -1;
	contactNum = atoi(gets(buffer));
	gets(fieldName);
	gets(newValue);
	editContactField(contactNum, fieldName, newValue, addressBook);
}



void loadContactListFromFileMaster(AddressBook* addressBook) {
	int i = 0;
	char inputFile[BUFSIZ + 1];
	char buffer[BUFSIZ + 1];
	FILE* fpr;
	gets(inputFile);
	fpr = fopen(inputFile, "r");
	int contactCount = countContacts(addressBook) - 1; //last 0 based index
	while (fgets(buffer, BUFSIZ, fpr) != NULL) //grab line by line of file
	{
		if ((i > 0) && (buffer[0] != '\n')) //skip the header row
		{
			insertAtEnd(contactCount, addressBook, buffer);
			contactCount++;
		}
		i++;
	}
	fclose(fpr);
}

void insertAtEnd(int endIndex, AddressBook* addressBook, char* buffer) {

	Contact* contactToInsert = createContact(buffer);
	//get contact at very end of list
	Contact* contactToInsertAfter = getContactToInsertAfter(endIndex,
			addressBook);
	insertContact(contactToInsert, contactToInsertAfter, addressBook);
}

void writeContactListToFileMaster(AddressBook* addressBook) {
	/*write an integer count of the src tags to a file*/
	FILE * fpw;
	char outputFile[BUFSIZ + 1];
	char header[42] = "lastName,firstName,email,phoneNumber\n";
	char* pContactList;
	gets(outputFile);
	fpw = fopen(outputFile, "w");
	pContactList = returnContactStringFromList(addressBook);
	fprintf(fpw, header);
	fprintf(fpw, pContactList);
	fclose(fpw);
	free(pContactList);
}

char* returnContactStringFromList(AddressBook* addressBook) {
	//lastName,firstName,email,phoneNumber
	Contact* current;
	char* contactList = (char*) malloc(sizeof(Contact)*(countContacts(addressBook)+3)); //give us a little extra space
	//(char*) malloc((sizeof(Contact)+6)*countContacts(addressBook);
	current = addressBook->top;
	while (current != NULL) {
		strcat(contactList, current->lastName);
		strcat(contactList, ",");
		strcat(contactList, current->firstName);
		strcat(contactList, ",");
		strcat(contactList, current->emailAddress);
		strcat(contactList, ",");
		strcat(contactList, current->phoneNumber);
		strcat(contactList, "\n");
		current = current->next;
	}
	return contactList;
}



char* begToEndString(char* stringText, int currentIndex) {
	//from the beginning of this pointer, keep incrementing until we get to ",
	//then stop and return the string This is just a quotation mark
	//strncpy ( str3, str2, 5 );
	//want to subString the strings Returned

	char* returnString = (char*) malloc(256);
	char c = ',';
	int count = currentIndex;
	while (stringText[count] != c) {
		count++;
	}
	strncpy(returnString, stringText + currentIndex, count - currentIndex);
	return returnString; //go one char past the "
}

int charsFromStart(char* stringText, int startIndex) {
	int count = startIndex;
	char c = ',';
	while (stringText[count] != c) {
		count++;
	}
	return count;
}

void printContactsInList(AddressBook* addressBook) {
	Contact* current = addressBook->top;
	while (current != NULL) {
		puts(current->firstName);
		puts(current->lastName);
		puts(current->emailAddress);
		current = current->next;
	}
}

