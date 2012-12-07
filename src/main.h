/*
 * main.h
 *
 *  Created on: Dec 5, 2012
 *      Author: jjroll
 */

#include "AddressBook.h"
#ifndef MAIN_H_
#define MAIN_H_


#endif /* MAIN_H_ */


void executeMasterAddressBook(char* cmd, AddressBook* addressBook);
void writeFile(char* fileName, char* outputString);
void deleteContactMaster(AddressBook* addressBook); //prepares the params to delete a contact
void getContactMaster(AddressBook* addressBook);
void addContactMaster(AddressBook* addressBook);
void getNumberofContactsMaster(AddressBook* addressBook);
void writeContactListToFileMaster(AddressBook* addressBook);
void loadContactListFromFileMaster(AddressBook* addressBook);
char* begToEndString(char* stringText, int startIndex);
char* begToEndStringZero(char* stringText, int currentIndex);
char* restOfString(char* stringText, int currentIndex);
int charsFromStart(char* stringText, int startIndex);
char* returnContactStringFromList(AddressBook* addressBook);
void insertAtEnd(int endIndex, AddressBook* addressBook, char* buffer);
