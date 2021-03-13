//
// Created by MAXIME on 3/9/2021.
//
#include "bits/stdc++.h"

#ifndef TRN2_TRANSACTION_H
#define TRN2_TRANSACTION_H
using namespace std;

class Transaction { // klase Transakcijai.
    string type;
    string PAN;
    double amount;
    string time;
    string currency;
public:
    explicit Transaction(string s);

    string getType();

    string getTime();

    string getPAN();

    string getCurrency();

    double getAmount();

private:

    string parseType(string s);

    string parsePAN(string s);

    double parseAmount(string s);

    string parseTime(string s);

    string parseCurrency(string s);


};


#endif //TRN2_TRANSACTION_H
