/*
 * AddressBook.h
 *
 *  Created on: Dec 5, 2012
 *      Author: jjroll
 */

#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

#endif /* ADDRESSBOOK_H_ */
typedef struct contact Contact;
struct contact {
	char firstName[256];
	char lastName[256];
	char emailAddress[256];
	char phoneNumber[256];
	Contact* prev;
	Contact* next;
};

typedef struct addressBook {
	Contact* top;
	Contact* current;
} AddressBook;

Contact* createContact(char* text);
void editContactField(int contactIndex, char* fieldName, char* newValue,
		AddressBook* addressBook);
int countContacts(AddressBook* addressBook);
char* findContactField(int contactIndex, char* fieldName,
		AddressBook* addressBook);
Contact* getContactToInsertAfter(int contactIndex, AddressBook* addressBook);
Contact* getContactAtIndex(int contactIndex, AddressBook* addressBook);
Contact* deleteContact(Contact* contactToDelete, AddressBook* addressBook);
Contact* insertContact(Contact* contactToInsert, Contact* contactToInsertAfter,
		AddressBook* addressBook);
void freeContactsInList(AddressBook* addressBook);
