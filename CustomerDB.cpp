/* EE 312 Project 7 submission by
 * Name: Jared Campbell
 * EID: jsc3642
 * Project 7, CRM part 2
 * EE 312, Spring 2018
   Slip days used: <0>
   Spring 2018
*/
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name) { // not done, your effort goes here
	int i = 0;
	while(i < this->length) {
		if(this->data[i].name == name) return this->data[i];
		i++;
	}
	if(this->length < this->capacity){
		this->data[this->length] = Customer(name);
		this->length++;
		return this->data[this->length-1];
	}
	else {
		auto *cust_copy = new Customer[this->capacity*2];
		int j = 0;
		while(j < this->length) {
			cust_copy[j].name = this->data[j].name;
			cust_copy[j].bottles = this->data[j].bottles;
			cust_copy[j].diapers = this->data[j].diapers;
			cust_copy[j].rattles = this->data[j].rattles;
			j++;
		}
		delete[] this->data;
		this->data = cust_copy;
		this->data[this->length] = Customer(name);
		this->length++;
		this->capacity*=2;
		return this->data[this->length-1];
	}
}

bool CustomerDB::isMember(String name) { // not done, your effort goes here
	int i = 0;
	while(i < this->length) {
		if(this->data[i].name == name) return true;
		i++;
	}
	return false;
}
