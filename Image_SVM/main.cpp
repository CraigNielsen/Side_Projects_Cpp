#include <QCoreApplication>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/ml/ml.hpp>
#include "trainerobject.h"
#include "file_io.h"
#include <unordered_map>
#include "cbn_consoleoutput.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <boost/serialization/map.hpp>



using namespace cv;
//typedef vector<string> vstrings;
//typedef  folders;


int main()
{

    /*
     * create a trainer object, giving it a directory will classes in seperate folders and all images the same size
     * Then process.(can seperate that as well, still deciding
     * now getTrainingmat and getLabelMat return the matrices for training
     * create a svm, train it using matrices,
     * now can use trainer objects method getFeatureRow to convert a test image to a row for testing against the svm
     *
    */

    ///SETUP
    trainerObject t=trainerObject("/home/craig/Pictures/training_images/BW_ROIsmall/",true);
    t.process1C();
    t.multiclassTrain();
    t.multiclassTest();


//    uchar* ypixel = training_Data.ptr<uchar>(0);
//    for (int j=0 ; j<training_Data.cols ; j+=1)
//    {
//        uchar* ypixel = training_Data.ptr<uchar>(0);
//        cout<<(float)ypixel[j]<<endl;
//        waitKey(10);
//    }

//    t.io.print(t.labelnm);
//    Mat proc=imread("/home/craig/QT/scripts/training/50/1.jpg");


////    trainerObject t=trainerObject();

////    //http://stackoverflow.com/questions/14694810/using-opencv-and-svm-with-images




//    CvSVMParams params=CvSVMParams();
////    params.svm_type = CvSVM::NU_SVC;
////    params.kernel_type = CvSVM::RBF;
////    params.gamma = 3;
//    params.svm_type = CvSVM::C_SVC;
////    params.kernel_type = CvSVM::RBF; //CvSVM::RBF, CvSVM::LINEAR ...
////    params.degree = 0; // for poly
////    params.gamma = 20; // for poly/rbf/sigmoid
////    params.coef0 = 0; // for poly/sigmoid

////    params.C = 7; // for CV_SVM_C_SVC, CV_SVM_EPS_SVR and CV_SVM_NU_SVR
////    params.nu = 0.0; // for CV_SVM_NU_SVC, CV_SVM_ONE_CLASS, and CV_SVM_NU_SVR
////    params.p = 0.0; // for CV_SVM_EPS_SVR

////    params.class_weights = NULL; // for CV_SVM_C_SVC
////    params.term_crit.type = CV_TERMCRIT_ITER +CV_TERMCRIT_EPS;
////    params.term_crit.max_iter = 1000;
////    params.term_crit.epsilon = 1e-6;
//    CvSVM svm;
//    ///TRAIN
//    cout<<"start training"<<endl;

//    Mat train=t.getTrainingMat().clone();
//    Mat labels_=t.getLabelMat().clone();
//    svm.train(train, labels_, Mat(), Mat(), params);

//    svm.save("/home/craig/scripts/road1.xml"); // saving

//    cout<<"finished"<<endl;


//    ///TEST
//    svm.load("/home/craig/scripts/road1.xml"); // loading

//    Mat img_mat3 = Mat(1,2700,CV_32FC1); // I used 0 for greyscale
//    t.getFeatureRow("/home/craig/scripts/training/50/2688.jpg",img_mat3,0);

//    float answer= svm.predict(img_mat3);

//    cout<<"class is: "<<answer<<endl;





    return 0;
}
