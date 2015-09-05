#ifndef TRAINEROBJECT_H
#define TRAINEROBJECT_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <QDirIterator>
#include <QDebug>
#include "file_io.h"
#include <unordered_map>
#include <boost/serialization/serialization.hpp>
 #include <boost/archive/text_oarchive.hpp>
 #include <boost/archive/text_iarchive.hpp>
 #include <string>
 #include <fstream>

using namespace cv;
using namespace std;
#include <string>
typedef unordered_multimap<string,string> umm_dirs;

class trainerObject
{

    class Pair {
    public:
        int value;
        string name;
        Pair(int n1, string n2) { value=n1; name=n2;  }
    };

public:
    umm_dirs umm_dir;
    file_IO io;
    Mat training_Data,featureRowSize;
    Mat label_Matrix;
    std::vector< float > labelArray;
    int lar[];
    vector <Pair> labelnames;
    map <int ,string > labelnm;
    string currentFolder="defaultsFolder__";
    string folder;
    map <string,int> info;
    int imageSize;//area of the training images (rows * colums)
    int fileNumber=-1;

    trainerObject(char *dir_, bool printout_=false);
    trainerObject();
    Mat &getTrainingMat();
    Mat &getLabelMat();
    void process();
    void convertImageToRow(Mat &src_, int size);
    string getClass(int i, bool ShowAllClasses= false);
    void initialize(int image_channels, int classes);
    void get3DFeatureRow(string path, Mat &dest, int row_to_change);
    void get1DFeatureRow(string path, Mat &dest, int row_to_change);
    void save(string dir_);
    void makeFeatureRow(Mat &src_, Mat &dest_);
private:

    char* dir;
    int n;
    void readDirectory(const char *dir, Mat & training, Mat & labels);

};

#endif // TRAINEROBJECT_H