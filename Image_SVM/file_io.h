#ifndef FILE_IO_H
#define FILE_IO_H
using namespace std;
#include <iostream>
#include <string>
#include <QDirIterator>
#include <unordered_map>
#include "cbn_consoleoutput.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
typedef std::vector<string>  vfiles;
class file_IO
{
public:
    file_IO();

    map<string, int> getDirectoryFiles(char *dir, unordered_multimap<string, string> &folders, string filetype = ".jpg", bool printout_=false);
    void Splitfilename(std::string &path_, std::string &folder_, std::string &file_, bool printOutput = false);
    void print(unordered_multimap<string, string> & folder, char *name="Folder given");
    void print(map<int, string> & folder, char *name="Folder given");
    void print_key(unordered_multimap<string, string> & folder,char* key);
    void print_out_Mat(Mat & mat);
private:
    cbn_consoleOutput print_=cbn_consoleOutput();
    MatIterator_<float> it, end;
private:
};

#endif // FILE_IO_H
