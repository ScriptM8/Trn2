/**
 *
 * C++ Programming Test
 * Task is to write a program named trn2msg.exe in C/C++ which reads transaction file and writes notification file.
 * Made by Maksims Čižikovs 3.10.2021
 */
#include <bits/stdc++.h>
#include "tinyxml/tinyxml.h"
#include "Transaction.h"
#include "log.h"

using namespace std;
#define REP(i, n) for(auto i=0;i<(n);i++)
#define fastIO std::ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define DEBUG(x) {cout << #x << "=" << x <<endl;}
#define decimalpoints(x) cout<<setprecision(x)<<fixed;
#define decimalpoints2(x) out<<setprecision(x)<<fixed;
typedef string basicString;
vector<Transaction> T;
TiXmlDocument doc;


void printConsole(string s) {
    cout << s << '\n';
}

string getDate(string format) { //C-style;
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[256];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    //strftime(buffer, sizeof(buffer), "%Y.%m.%d %H:%M:%S", timeinfo);
    strftime(buffer, sizeof(buffer), format.c_str(), timeinfo);
    std::string str(buffer);
    return str;
}

int main(int argc, char *args[]) {
    //fastIO;
    ifstream in;
    ofstream out;
    decimalpoints(2);
    decimalpoints2(2);

    /**Logger**/
    FILELog::ReportingLevel() = linfo;
    string _logger = "trn2msg.exe_" + getDate("%Y%m%d") + ".log";
    FILE *log_fd = fopen(_logger.c_str(), "w");
    Output2FILE::Stream() = log_fd;
    /****/

    /**Failu Parbaude **/
    L_(linfo) << "Programm started";
    if (argc >= 2) {
        in.open(args[1]);
        if (in.good()) L_(linfo) << "redzu failu";
        L_(linfo) << "Tika atrasts faila nosaukums argumentos";
    }
    if (in.fail() or !in.is_open()) {
        printConsole("nav no kurienes lasit info.. beidzam darbu");
        L_(lerror) << "nav no kurienes lasit failu, beigt darbu";
        exit(0);
    }
    string line;
    while (getline(in, line)) {
        auto t = Transaction(line);
        if (!line.empty()) T.emplace_back(t); // 47 for no out_of_range exception.
    }

    L_(linfo) << "Fails veiksmigi nolasits";
    if (argc >= 3) {
        out.open(args[2], ofstream::out);
        L_(linfo) << "Atrasts izvades faila nosaukums argumentos";
    }
    /****/

    /**XML izveide**/
    auto *root = new TiXmlElement("root");
    auto *msg_list = new TiXmlElement("msg-list");

    for (auto x : T) {
        auto *msg = new TiXmlElement("msg");
        string tmp = x.getType() + " with card " + x.getPAN() + " on " + x.getTime() + ", amount " +
                     to_string(x.getAmount()).replace(5, 4, "") + " " +
                     x.getCurrency() + ".";
        auto *text = new TiXmlText(tmp.c_str());
        msg->LinkEndChild(text);
        msg_list->LinkEndChild(msg);
    }
    root->LinkEndChild(msg_list);
    auto *totals = new TiXmlElement("totals");
    totals->SetAttribute("cnt", T.size());
    double cnt = 0.0;
    for (auto x : T) {
        cnt += (double) x.getAmount();
    }
    totals->SetAttribute("sum", to_string(cnt).replace(5, 4, "").c_str());
    totals->SetAttribute("date", getDate("%Y.%m.%d %H:%M:%S").c_str());
    root->LinkEndChild(totals);
    doc.LinkEndChild(root);
    L_(linfo) << "Veiksmigi saveidoti xml faili";
    /****/

    /**Drukasana**/
    try {
        if (out.fail() or !out.is_open()) {
            string name = "tmp";
            doc.SaveFile(name.c_str());
            ifstream in2(name);
            while (in2) {
                string tmp;
                getline(in2, tmp);
                if (!tmp.empty()) printConsole(tmp);
            }
            in2.close();
            remove(name.c_str());
        } else {
            doc.SaveFile(args[2]);
        }
        L_(linfo) << "Veiksmigi notika izvade";
    } catch (...) {
        L_(lerror) << "Izvade nenotika veiskmigi";
    }

    /** P.S.
     * Risinajuma izmantoju pieejamo open-source XML parseri, bet vareju ari uzrakstit savejo.
     * Risinajuma izmantoju pieejamo open-source loggeri, simple un efektivs.
     * Vareju visu iznest atseviskas funkcijas labakai skatamibai, nav problema.
     * Izejot no ievaddatiem, (kas ir 47 gara rinda) ja taa ir vienmer, kods nostrada vienmer. Ir dazas parbaudes par neatbilstibu, bet pilnu iespejamo kludu aspektam vajag nelielu testesanu.
     *
     */
    return 0;
}


