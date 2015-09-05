#include "cbn_consoleoutput.h"

cbn_consoleOutput::cbn_consoleOutput()
{

}


void cbn_consoleOutput::umm_out(unordered_multimap<string, string> &folder,char *name)
{
    std::cout << name <<" contains:"<<endl;
    for ( auto it = folder.begin(); it != folder.end(); ++it ){
    std::cout << " " << it->first << ":" << it->second;
    std::cout << std::endl;}
}
void cbn_consoleOutput::umm_out(map<int, string> &folder,char *name)
{
    std::cout << name <<" contains:"<<endl;
    for ( auto it = folder.begin(); it != folder.end(); ++it ){
    std::cout << " " << it->first << ":" << it->second;
    std::cout << std::endl;}
}

void cbn_consoleOutput::umm_out_key(unordered_multimap<string, string> &folder, char *key)
{
    auto its = folder.equal_range(key);           ///iterator for a keys values
    cout << "Key "<<key<<" contains:"<<endl;
    for (auto it = its.first; it != its.second; ++it) {
        cout <<it->second << endl;
    }
}

void cbn_consoleOutput::umm_buckets(unordered_multimap<string, string> &folder)
{
    std::cout << "folder buckets contain:\n";
    for ( unsigned i = 0; i < folder.bucket_count(); ++i) {
      std::cout << "bucket #" << i << " contains:";
      for ( auto local_it = folder.begin(i); local_it!= folder.end(i); ++local_it )
        std::cout << " " << local_it->first << ":" << local_it->second;
      std::cout << std::endl;
    }
}
