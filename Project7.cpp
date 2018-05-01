/* EE 312 Project 7 submission by
 * Name: Jared Campbell
 * EID: jsc3642
 * Project 7, CRM part 2
 * EE 312, Spring 2018
   Slip days used: <0>
   Spring 2018
*/

#include <stdio.h>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"
void mostItems(void);
void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the 
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	} else if (word == "Diapers") {
		return &num_diapers;
	} else if (word == "Rattles") {
		return &num_rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	} else if (word == "Diapers") {
		return &cust.diapers;
	} else if (word == "Rattles") {
		return &cust.rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 * 
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the 
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust); 
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}
	
	return result;
}

void processPurchase() {
	String name;
	readString(name);
	String item;
	readString(item);
	int num;
	readNum(num);
	if(num <= 0) return;
	if(*selectInventItem(item) - num < 0) {
		printf("Sorry %s, we only have %d %s\n", name.c_str(), *selectInventItem(item), item.c_str());
		return;
	}
	*selectInventItem(item, database.operator[](name)) += num;
	*selectInventItem(item) -= num;
}

void processSummarize() {
	printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", num_bottles, num_diapers, num_rattles);
	printf("we have had a total of %d different customers\n", database.size());
	mostItems();
}

void processInventory() {
	String item;
	readString(item);
	int num;
	readNum(num);
	*selectInventItem(item) += num;
}

void mostItems(){
	Customer *b_max = findMax("Bottles");
    Customer *d_max = findMax("Diapers");
    Customer *r_max = findMax("Rattles");
    if(b_max == nullptr){
		printf("no one has purchased any Bottles\n");
	}
	else {
		printf("%s has purchased the most Bottles (%d)\n", b_max->name.c_str(), b_max->bottles);
	}

	if(d_max == nullptr){
		printf("no one has purchased any Diapers\n\n");
	}
	else {
		printf("%s has purchased the most Diapers (%d)\n", d_max->name.c_str(), d_max->diapers);
	}

	if(r_max == nullptr){
		printf("no one has purchased any Rattles\n\n");
	}
	else {
		printf("%s has purchased the most Rattles (%d)\n", r_max->name.c_str(), r_max->rattles);
	}
}

