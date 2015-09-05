
#include "file_io.h"

void cbn_consoleOutput(unordered_multimap<string, string> &folder)
{
    std::cout << "Folder contains:"<<endl;
    for ( auto it = folder.begin(); it != folder.end(); ++it ){
    std::cout << " " << it->first << ":" << it->second;
    std::cout << std::endl;}
}
void umm_out(unordered_multimap<string, string> &folder)
{
    std::cout << "Folder contains:"<<endl;
    for ( auto it = folder.begin(); it != folder.end(); ++it ){
    std::cout << " " << it->first << ":" << it->second;
    std::cout << std::endl;}
}

void umm_out_key(unordered_multimap<string, string> &folder, char *key)
{
    auto its = folder.equal_range(key);           ///iterator for a keys values
    for (auto it = its.first; it != its.second; ++it) {
        cout << it->first << '\t' << it->second << endl;
    }
}

void umm_buckets(unordered_multimap<string, string> &folder)
{
    std::cout << "folder buckets contain:\n";
    for ( unsigned i = 0; i < folder.bucket_count(); ++i) {
      std::cout << "bucket #" << i << " contains:";
      for ( auto local_it = folder.begin(i); local_it!= folder.end(i); ++local_it )
        std::cout << " " << local_it->first << ":" << local_it->second;
      std::cout << std::endl;
    }
}
