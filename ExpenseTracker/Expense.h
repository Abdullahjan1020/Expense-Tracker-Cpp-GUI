#pragma once
using namespace System;
public ref class Expense {
public:
	String^ Category;
	double Amount;
	DateTime Date;
	Expense(String^ category, double amount, DateTime date) {
		Category = category;
		Amount = amount;
		Date = date;
	}
};