#include "file_io.h"

file_IO::file_IO()
{
}
map<string,int> file_IO::getDirectoryFiles(char* dir, unordered_multimap<string, string> &folders, string filetype, bool printout_){

    /*  NOTE: Must hand the function an empty unordered multimap
    Reads all subdirectories for files with the given filetype, counts the files and return an unordered
    multimap containing the folder as keys and the files as values. can use the print
    method to console print the values.

    */
    QDirIterator it(dir ,QDir::Files, QDirIterator::Subdirectories);
    string currentfolder="";
    string file;
    string folder1;
    vector<string> files;
//    bool printout=printout_;
    string path;
    int foldercount=0;
    int filecount=0;
    while (it.hasNext()) {
        path=(it.next()).toStdString();
        Splitfilename(path,folder1,file,false);
        int index=file.find(filetype);
        //if jpg image:
        if (! (index==-1)){
            if (!(currentfolder==folder1)){
                //add vector of files to map with old folder name
//                folders.insert(files);
//                files.clear();
                foldercount+=1;
                currentfolder=folder1;}
            filecount+=1;
            folders.insert({folder1, file});
            if (printout_){
                cout<<"folder: "<<folder1<<" file: "<<file<<endl;
            }
        }
}
    if (printout_){cout<<"no. of classes: "<<foldercount<<endl;
    cout<<"no. of files: "<<filecount<<endl;}
    //find image area
    string loc = path+file;
    Mat test=imread(path+"/"+file);
    int area=test.cols*test.rows;
    int channels=test.channels();
    map<string,int> info;
    info["folder_count"]=foldercount;
    info["file_count"]=filecount;
    info["classes"]=filecount;
    info["imagearea"]=area;
    info["channels"]=channels;
    return info;
}

void file_IO::Splitfilename ( std::string& path_,std::string& folder_,std::string& file_, bool printOutput)
{

    if (printOutput){std::cout << "Splitting: " << path_ << '\n';}
    unsigned found = path_.find_last_of("/\\");
    unsigned folder_1 = (path_.substr(0,found)).find_last_of("/\\");
    file_=path_.substr(found+1);
    path_=path_.substr(0,found);
    folder_=path_.substr(folder_1+1);

    if (printOutput){
        std::cout << " path_: " << path_.substr(0,found) << '\n';
        std::cout << " folder_: " << folder_ << '\n';
        std::cout << " file_: " << file_ << '\n';}

}

void file_IO::print(unordered_multimap<string, string> &folder,char* name)
{
    print_.umm_out(folder,name);
}
void file_IO::print(map<int, string> &folder, char* name)
{
    print_.umm_out(folder,name);
}

void file_IO::print_key(unordered_multimap<string, string> &folder, char *key)
{
    print_.umm_out_key(folder,key);
}

void file_IO::print_out_Mat(Mat &mat)
{
    for( it = mat.begin<float>(), end = mat.end<float>(); it != end; ++it)
    {
        cout<<(*it)<<endl;
    }
}


