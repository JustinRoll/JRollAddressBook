/*
 * AddressBook.c
 *
 *  Created on: Dec 4, 2012
 *      Author: jjroll
 */

#include "AddressBook.h"
#include <stdio.h>

Contact* createContact(char* text) {
	int charIncrement;
	//parse test like this
	//"JOHNSON,ROSALIA,rjohnson@pricegrabber.com,8001110002"
	//into a valid contact
	Contact* ptrNewContact = (Contact*) malloc(sizeof(Contact));
	strcpy(ptrNewContact->lastName, begToEndString(text, 0));
	charIncrement = charsFromStart(text, 0);
	strcpy(ptrNewContact->firstName, begToEndString(text, charIncrement + 1));
	charIncrement = charsFromStart(text, charIncrement + 1);
	strcpy(ptrNewContact->emailAddress, begToEndString(text, charIncrement + 1));
	charIncrement = charsFromStart(text, charIncrement + 1);
	strcpy(ptrNewContact->phoneNumber, begToEndStringZero(text, charIncrement
			+ 1));
	ptrNewContact->next = NULL; //just in case these are originally some
	ptrNewContact->prev = NULL; //gobbledegook
	return ptrNewContact;
}

void editContactField(int contactIndex, char* fieldName, char* newValue,
		AddressBook* addressBook) {

	//char * strcpy ( char * destination, const char * source );
	char FIRST_NAME[256] = "firstName";
	char LAST_NAME[256] = "lastName";
	char EMAIL_ADDRESS[256] = "email";
	char PHONE_NUMBER[256] = "phoneNumber"; //for matching to the user input
	Contact* current = getContactAtIndex(contactIndex, addressBook);
	if (current != NULL) {
		if (strstr(fieldName, FIRST_NAME)!=NULL)
			strcpy(current->firstName, newValue);
		else if (strstr(fieldName, LAST_NAME) != NULL)
			strcpy(current->lastName, newValue);
		else if (strstr(fieldName, EMAIL_ADDRESS)!= NULL)
			strcpy(current->emailAddress, newValue);
		else if (strstr(fieldName, PHONE_NUMBER)!= NULL) {
			strcpy(current->phoneNumber, newValue);
		}
	}
}

int countContacts(AddressBook* addressBook) {
//iterate through the list and count!
	Contact* current = addressBook->top;
	int i = 0;
	while (current != NULL) {
		i++;
		current = current->next;
	}
	return i;
}

Contact* getContactToInsertAfter(int contactIndex, AddressBook* addressBook) {
	if (contactIndex == -1)
		return NULL;
	int i = 0;
	Contact* current = addressBook->top;
	if (current) {
		while (i < contactIndex) {
			i++;
			if (current->next != NULL) {
				current = current->next;
			}
		}
	}
	return current;
}

Contact* getContactAtIndex(int contactIndex, AddressBook* addressBook) {
	Contact* current = NULL;
	if (contactIndex >= countContacts(addressBook))
		return NULL;
	int i = 0;
	current = addressBook->top;
	if (current) {
		while (i < contactIndex) {
			i++;
			if (current->next != NULL) {
				current = current->next;
			}
		}
	}
	return current;
}

Contact* insertContact(Contact* contactToInsert, Contact* contactToInsertAfter,
		AddressBook* addressBook) {

	if (contactToInsertAfter != NULL) { //not inserting to empty
		contactToInsert->prev = contactToInsertAfter;
		contactToInsert->next = contactToInsertAfter->next;
		contactToInsertAfter->next = contactToInsert;

		if (contactToInsert->next != NULL) //make sure there is a next
			contactToInsert->next->prev = contactToInsert;
	} else { //insert node at top of list
		contactToInsert->prev = NULL;
		contactToInsert->next = addressBook->top;
		if (addressBook->top != NULL)
			addressBook->top->prev = contactToInsert;
		addressBook->top = contactToInsert;
	}
	return contactToInsert;
}

void freeContactsInList(AddressBook* addressBook) { //clean up memory!
	Contact* current = addressBook->top;
	while (current != NULL) {
		Contact* nextNode = current->next;
		free(current);
		current = nextNode;
	}
}

Contact* deleteContact(Contact* contactToDelete, AddressBook* addressBook) {
	/*                    |--------|
	 * 					  |    x    | account for deleting top node
	 * 					  |--------|
	 */
	Contact* contactToReturn;

	if (contactToDelete == addressBook->top) {
		if (contactToDelete->next != NULL) {
			contactToReturn = contactToDelete->next;
			addressBook->top = contactToReturn;
			contactToReturn->prev = NULL;
		} else {
			contactToReturn = NULL;
			addressBook->top = NULL;
		}
	} else {

		if (contactToDelete->next != NULL) //not the last node
		{
			contactToReturn = contactToDelete->next;
			contactToReturn->prev = contactToDelete->prev;
			contactToDelete->prev->next = contactToReturn;
		} else //delete last node
		{
			contactToReturn = contactToDelete->prev;
			contactToReturn->next = NULL;
		}
	}

	free(contactToDelete); //cleaning

	return (contactToReturn);
}

char* findContactField(int contactIndex, char* fieldName,
		AddressBook* addressBook) {
	//firstName, lastName, email, phoneNumber.
	char FIRST_NAME[256] = "firstName";
	char LAST_NAME[256] = "lastName";
	char EMAIL_ADDRESS[256] = "email";
	char PHONE_NUMBER[256] = "phoneNumber";
	char* ERROR = "E from find";
	Contact* current = getContactAtIndex(contactIndex, addressBook);
	if (current != NULL) {
		if (strstr(fieldName, FIRST_NAME)!=NULL)
			return current->firstName;
		else if (strstr(fieldName, LAST_NAME)!=NULL)
			return current->lastName;
		else if (strstr(fieldName, EMAIL_ADDRESS)!=NULL)
			return current->emailAddress;
		else if (strstr(fieldName, PHONE_NUMBER)!=NULL) {
			return current->phoneNumber;
		} else
			return ERROR;
	}
}

