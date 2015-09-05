#include "trainerobject.h"




trainerObject::trainerObject(char *dir_,bool printout_)
{

    dir=dir_;
    n=1;
    info=io.getDirectoryFiles(dir,umm_dir,".jpg",printout_);
    int classss=info["classes"];
    int channe=info["channels"];
    imageSize=info["imagearea"];
    training_Data=Mat(classss,imageSize*channe,CV_32FC1);
    featureRowSize=Mat(1,imageSize*channe,CV_32FC1);
    cout<<"feature Row Size is: Mat( "<< "1,"<<imageSize*channe<<",CV_32FC1)"<<endl;
    label_Matrix=Mat(classss,1,CV_32FC1);
    cout<<"image area is: "<<imageSize<<endl;
}

trainerObject::trainerObject()
{

}



Mat &trainerObject::getTrainingMat()
{
    return  training_Data;
}

Mat &trainerObject::getLabelMat()
{
//    io.print_out_Mat(label_Data);

    return label_Matrix;
}
void trainerObject::initialize( int image_channels,int classes){

//    training_Data=Mat(classes,imageSize*image_channels,CV_32FC1);

//    label_Data=Mat(classes,1,CV_32FC1);
    //first folder name is different and the folder number is auto incremented to zero (the correct index for the first folder)
}

void trainerObject::process( )
{
    fileNumber=-1;
    //setup variables for class counting
    string changedFolder=umm_dir.begin()->first;
    int klass=0;
    int row=0;
    //iterate through directory adding featureRows & adding class rows

    for (auto i = umm_dir.begin(); i != umm_dir.end();i++,row+=1){
        string path= (string)dir +"/"+ i->first+"/"+i->second;
        get3DFeatureRow(path,training_Data,row);
        if (i->first != changedFolder){
            changedFolder=i->first;
            klass+=1;
        }
        //add labels for the new feature row
        labelnames.push_back(Pair(klass,i->first));
        labelArray.push_back(klass);
        labelnm[klass]=i->first;
    }
    //create labels automatically
    //create a pointer to the start of the vector (the reference to its first element) This is an array
    float* array = &labelArray[0];
//    float labels[6] = {0,0, 0, 0, 1,1};
    Mat labelsMat(labelArray.size(), 1, CV_32FC1, array);
    labelsMat.col(0).copyTo(label_Matrix.col(0));

}
void trainerObject::get1DFeatureRow(string  path, Mat & dest, int row_to_change)
{
/*
    reads image
    creates feature row
    adds feature row to training data Mat
    adds a pair to labelnames
 * */

    int ii = 0; // Current column in training_mat
    Mat img_mat=imread(path);
    namedWindow("get",2);
    imshow("get",img_mat);
//    waitKey(0);
    Mat featureRow(1,img_mat.cols*img_mat.rows*img_mat.channels(),CV_32FC1);

    for (int i = 0; i<img_mat.rows; i++) {
        for (int j = 0; j < img_mat.cols; j++)
        {
            featureRow.at<float>(0,ii++) = (float)img_mat.at<Vec3b>(i,j)[0];
        }
    }

featureRow.row(0).copyTo(dest.row(row_to_change));
}

void trainerObject::get3DFeatureRow(string  path, Mat & dest, int row_to_change)
{
/*
    reads image
    creates feature row
    adds feature row to training data Mat
    adds a pair to labelnames
 * */

    int ii = 0; // Current column in training_mat
    Mat img_mat=imread(path);
    namedWindow("get",2);
    imshow("get",img_mat);
//    waitKey(0);
    Mat featureRow(1,img_mat.cols*img_mat.rows*img_mat.channels(),CV_32FC1);
    for (int i = 0; i<img_mat.rows; i++) {
        for (int j = 0; j < img_mat.cols; j++) {
            featureRow.at<float>(0,ii++) = (float)img_mat.at<Vec3b>(i,j)[0];
            featureRow.at<float>(0,ii++) = (float)img_mat.at<Vec3b>(i,j)[1];
            featureRow.at<float>(0,ii++) = (float)img_mat.at<Vec3b>(i,j)[2];
            if (i==j && i==2){
            cout<<"B1: "<<(float)img_mat.at<Vec3b>(i,j)[0]<<endl;
            cout<<"G1: "<<(float)img_mat.at<Vec3b>(i,j)[1]<<endl;
            cout<<"R1: "<<(float)img_mat.at<Vec3b>(i,j)[2]<<endl;
        }}
    }

featureRow.row(0).copyTo(dest.row(row_to_change));
}
void trainerObject::makeFeatureRow(Mat & src_, Mat &dest_){

    /*
        reads image
        creates feature row
        adds feature row to training data Mat
        adds a pair to labelnames
     * */
    Mat *poes= new Mat(src_.rows,src_.cols,CV_32FC1);
    *poes=src_.clone();
//    Mat src_0= imread("/home/craig/scripts/temp/0 fuck.jpg");
//    *poes=src_0.clone();
    namedWindow("make",2);
    imshow("make",src_);
//    waitKey(0);

    int ii = 0; // Current column in training_mat
    Mat featureRow2(1,src_.cols*src_.rows*src_.channels(),CV_32FC1);
    for (int i = 0; i<src_.rows; i++) {
        for (int j = 0; j < src_.cols; j++) {
            featureRow2.at<float>(0,ii++) =(float) (*poes).at<Vec3b>(i,j)[0];
            featureRow2.at<float>(0,ii++) =(float) (*poes).at<Vec3b>(i,j)[1];
            featureRow2.at<float>(0,ii++) =(float) (*poes).at<Vec3b>(i,j)[2];
            if (i==j && i==2){
            cout<<"B3: "<<(float)(*poes).at<Vec3b>(i,j)[0]<<endl;
            cout<<"G3: "<<(float)(*poes).at<Vec3b>(i,j)[1]<<endl;
            cout<<"R3: "<<(float)(*poes).at<Vec3b>(i,j)[2]<<endl;
        }}
    }
    delete poes;

    featureRow2.row(0).copyTo(dest_.row(0));
}

string trainerObject::getClass(int i,bool ShowAllClasses )
{
    if (ShowAllClasses){
        for (auto & i : labelnm){
            cout<<i.first<<" "<<i.second<<endl;
        }}
    return labelnm[i];
}