#ifndef CBN_CONSOLEOUTPUT_H
#define CBN_CONSOLEOUTPUT_H
#include <unordered_map>
#include <map>
#include <iostream>
using namespace std;
class cbn_consoleOutput
{
public:
    cbn_consoleOutput();
    // unordered multimaps
    void umm_out(unordered_multimap  <string,string>  & folder, char *name="Folder Given");
    void umm_out(map<int, string> &folder, char *name="Folder Given");
    void umm_out_key(unordered_multimap  <string,string>  & folder,char* key);
    void umm_buckets(unordered_multimap  <string,string>  & folder);
};

#endif // CBN_CONSOLEOUTPUT_H
