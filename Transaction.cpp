//
// Created by MAXIME on 3/9/2021.
//

#include "Transaction.h"


string returnType(string s) { // viens parbaudes veids.
    if (s == "00") {
        return "Purchase";
    } else if (s == "01") {
        return "Withdrawal";
    } else {
        return "Unknown operation";
    }
}

map<string, string> VAL = { // otrs parbaudes veids, mapping.
        make_pair("840", "usd"),
        make_pair("978", "eur"),
        make_pair("826", "gbp"),
        make_pair("643", "rub"),
};

string
customTimeProcess(string s) { // jo nav smukas DateTime formata kaa Java; tresais parbaudes veids, range based queries.
    string time = "";
    time += s.substr(6, 2) + "."; // dd;
    time += s.substr(4, 2) + "."; // mm;
    time += s.substr(0, 4) + " "; // yyyy;
    time += s.substr(8, 2) + ":"; // HH
    time += s.substr(10, 2); // minutes
    return time;
}

string processPAN(string s, string type) { // cik sapratu, aizstat 6 pec 4, vai pec 6 ir atkarigs no maksajuma veida.
    string _toReplace = "******";
    if (type == "Withdrawal") {
        return s.replace(4, 6, _toReplace);
    } else if (type == "Purchase") {
        return s.replace(6, 6, _toReplace);
    } else {
        return s.replace(6, 6, _toReplace); // var ari nonemt, ja nekorekta operacija. un izvadit kludu
    }
}

Transaction::Transaction(string s) { // vnk konstruktors, kas parse doto stringu.
    this->type = parseType(s);
    this->PAN = parsePAN(s);
    this->amount = parseAmount(s);
    this->time = parseTime(s);
    this->currency = parseCurrency(s);
}

// Pricnipaa jau varetu uzrakstit ari regex, ja vajag.
string
Transaction::parseType(string s) { // visur rakstiju ''based on input data' tiesos skaitlus, sadalot stringu dalaas.
    return returnType(s.substr(0, 2));
}

string Transaction::parsePAN(string s) {
    return processPAN(s.substr(2, 16), this->type);
}

double Transaction::parseAmount(string s) {
    string tmp = s.substr(18, 12);
    return stod(tmp) / 100.0;
}

string Transaction::parseTime(string s) {
    return customTimeProcess(s.substr(30, 12));
}

string Transaction::parseCurrency(string s) {
    if (!VAL[s.substr(44, 3)].empty()) return VAL[s.substr(44, 3)]; else return "unknown currency";
}

string Transaction::getType() {
    return type;
}

string Transaction::getTime() {
    return time;
}

string Transaction::getPAN() {
    return PAN;
}

string Transaction::getCurrency() {
    return currency;
}

double Transaction::getAmount() {
    return amount;
}

