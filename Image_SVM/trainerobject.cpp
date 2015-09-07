#include "trainerobject.h"




trainerObject::trainerObject(char *dir_,bool printout_)
{
//# all files in directory must be of same size and type 
    dir=dir_;
    n=1;
    info=io.getDirectoryFiles(dir,umm_dir,".png",printout_);
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
void trainerObject::process1C()
{
    // process one channel images into feature vector

    fileNumber=-1;
    //setup variables for class counting
    string changedFolder=umm_dir.begin()->first;

    int klass=0;
    int row=0;
    //iterate through directory adding featureRows & adding class rows

    for (auto i = umm_dir.begin(); i != umm_dir.end();i++,row+=1){
        string path= ((string)dir +"/"+ i->first+"/"+i->second);
        get1DFeatureRow(path,training_Data,row);
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

void trainerObject::process3C( )
{
    // process three channel images into feature vector

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
    const char * c = path.c_str();
    Mat img_mat=imread(c,CV_LOAD_IMAGE_GRAYSCALE);

//    namedWindow("get",2);
//    imshow("get",img_mat);
//    waitKey(0);

    Mat featureRow(1,img_mat.cols*img_mat.rows*img_mat.channels(),CV_32FC1);
    if (img_mat.channels()>1){cout<<"this is a 3 channel image, please use the 3C function instead"<<endl;return ;}

//    for (int i = 0; i<img_mat.rows; i++) {
//        for (int j = 0; j < img_mat.cols; j++)
//        {
//            featureRow.at<float>(0,ii++) = (float)img_mat.at<Vec3b>(i,j)[0];
//        }
//    }
    uchar p;
    uchar* opixel = featureRow.ptr<uchar>(0);
    for (int i=0; i<img_mat.rows ; i+=1)
    {
        uchar* pixel = img_mat.ptr<uchar>(i);


        for (int j=0 ; j<img_mat.cols ; j+=1)
        {
            (*opixel++)= pixel[j];
//            cout<<(float)pixel[j]<<endl;

        }
    }
    uchar* ypixel = featureRow.ptr<uchar>(0);
//    for (int j=0 ; j<featureRow.cols ; j+=1)
//    {
//        cout<<(float)ypixel[j]<<endl;

//    }

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
//______________________________________________________________________________TRAINING

void trainerObject::multiclassTrain()
{
    // Our data will be 2-dimensional data. So declare an appropriate type to contain these points.

    typedef dlib::matrix<double,tImageCols,1> sample_type; //tImagecols is set in header,,no of columns in the training image..ie the individual training image area


    // ----------------------------------------------------------------------------------------


    void generate_data (
        std::vector<sample_type>& samples,
        std::vector<double>& labels
    );
    try
    {
        std::vector<sample_type> samples;
        std::vector<double> labels;

        // First, get our labeled set of training data

//        generate_data(samples, labels); function from original example

        convertMat2Dlib(training_Data,samples,labels);

        cout << "samples.size() is: "<< samples.size() << endl;

        // The main object in this example program is the one_vs_one_trainer.  It is essentially
        // a container class for regular binary classifier trainer objects.  In particular, it
        // uses the any_trainer object to store any kind of trainer object that implements a
        // .train(samples,labels) function which returns some kind of learned decision function.
        // It uses these binary classifiers to construct a voting multiclass classifier.  If
        // there are N classes then it trains N*(N-1)/2 binary classifiers, one for each pair of
        // labels, which then vote on the label of a sample.
        //
        // In this example program we will work with a one_vs_one_trainer object which stores any
        // kind of trainer that uses our sample_type samples.
        typedef dlib::one_vs_one_trainer<dlib::any_trainer<sample_type> > ovo_trainer;


        // Finally, make the one_vs_one_trainer.
        ovo_trainer trainer;


        // Next, we will make two different binary classification trainer objects.  One
        // which uses kernel ridge regression and RBF kernels and another which uses a
        // support vector machine and polynomial kernels.  The particular details don't matter.
        // The point of this part of the example is that you can use any kind of trainer object
        // with the one_vs_one_trainer.
        typedef dlib::polynomial_kernel<sample_type> poly_kernel;
        typedef dlib::radial_basis_kernel<sample_type> rbf_kernel;

        // make the binary trainers and set some parameters
        dlib::krr_trainer<rbf_kernel> rbf_trainer;
        dlib::svm_nu_trainer<poly_kernel> poly_trainer;
        poly_trainer.set_kernel(poly_kernel(0.1, 1, 2));
        rbf_trainer.set_kernel(rbf_kernel(0.1));


        // Now tell the one_vs_one_trainer that, by default, it should use the rbf_trainer
        // to solve the individual binary classification subproblems.
        trainer.set_trainer(rbf_trainer);
        // We can also get more specific.  Here we tell the one_vs_one_trainer to use the
        // poly_trainer to solve the class 1 vs class 2 subproblem.  All the others will
        // still be solved with the rbf_trainer.
        trainer.set_trainer(poly_trainer, 1, 2);

        // Now let's do 5-fold cross-validation using the one_vs_one_trainer we just setup.
        // As an aside, always shuffle the order of the samples before doing cross validation.
        // For a discussion of why this is a good idea see the svm_ex.cpp example.
        dlib::randomize_samples(samples, labels);
        cout << "cross validation: \n" << dlib::cross_validate_multiclass_trainer(trainer, samples, labels, 5) << endl;
        // The output is shown below.  It is the confusion matrix which describes the results.  Each row
        // corresponds to a class of data and each column to a prediction.  Reading from top to bottom,
        // the rows correspond to the class labels if the labels have been listed in sorted order.  So the
        // top row corresponds to class 1, the middle row to class 2, and the bottom row to class 3.  The
        // columns are organized similarly, with the left most column showing how many samples were predicted
        // as members of class 1.
        //
        // So in the results below we can see that, for the class 1 samples, 60 of them were correctly predicted
        // to be members of class 1 and 0 were incorrectly classified.  Similarly, the other two classes of data
        // are perfectly classified.
        /*
            cross validation:
            60  0  0
            0 70  0
            0  0 80
        */

        // Next, if you wanted to obtain the decision rule learned by a one_vs_one_trainer you
        // would store it into a one_vs_one_decision_function.
        dlib::one_vs_one_decision_function<ovo_trainer> df = trainer.train(samples, labels);
        sample_type m;

        cout << "predicted label: "<< df(m)  << ", true label: "<< 1 << endl;
        cout << "predicted label: "<< df(samples[90]) << ", true label: "<< labels[90] << endl;
        // The output is:
        /*
            predicted label: 2, true label: 2
            predicted label: 1, true label: 1
        */


        // If you want to save a one_vs_one_decision_function to disk, you can do
        // so.  However, you must declare what kind of decision functions it contains.
        dlib::one_vs_one_decision_function<ovo_trainer,
        dlib::decision_function<poly_kernel>,  // This is the output of the poly_trainer
        dlib::decision_function<rbf_kernel>    // This is the output of the rbf_trainer
        > df2, df3;


        // Put df into df2 and then save df2 to disk.  Note that we could have also said
        // df2 = trainer.train(samples, labels);  But doing it this way avoids retraining.
        df2 = df;
        dlib::serialize("df.dat") << df2;

        // load the function back in from disk and store it in df3.
        dlib::deserialize("df.dat") >> df3;


        // Test df3 to see that this worked.
        cout << endl;
        cout << "predicted label: "<< df3(samples[0])  << ", true label: "<< labels[0] << endl;
        cout << "predicted label: "<< df3(samples[90]) << ", true label: "<< labels[90] << endl;
        // Test df3 on the samples and labels and print the confusion matrix.
        cout << "test deserialized function: \n" << dlib::test_multiclass_decision_function(df3, samples, labels) << endl;





        // Finally, if you want to get the binary classifiers from inside a multiclass decision
        // function you can do it by calling get_binary_decision_functions() like so:
        dlib::one_vs_one_decision_function<ovo_trainer>::binary_function_table functs;
        functs = df.get_binary_decision_functions();
        cout << "number of binary decision functions in df: " << functs.size() << endl;
        // The functs object is a std::map which maps pairs of labels to binary decision
        // functions.  So we can access the individual decision functions like so:
        dlib::decision_function<poly_kernel> df_1_2 = dlib::any_cast<dlib::decision_function<poly_kernel> >(functs[dlib::make_unordered_pair(1,2)]);
        dlib::decision_function<rbf_kernel>  df_1_3 = dlib::any_cast<dlib::decision_function<rbf_kernel>  >(functs[dlib::make_unordered_pair(1,3)]);
        // df_1_2 contains the binary decision function that votes for class 1 vs. 2.
        // Similarly, df_1_3 contains the classifier that votes for 1 vs. 3.

        // Note that the multiclass decision function doesn't know what kind of binary
        // decision functions it contains.  So we have to use any_cast to explicitly cast
        // them back into the concrete type.  If you make a mistake and try to any_cast a
        // binary decision function into the wrong type of function any_cast will throw a
        // bad_any_cast exception.
    }
    catch (std::exception& e)
    {
        cout << "exception thrown!" << endl;
        cout << e.what() << endl;
    }
}

void trainerObject::printoutMatrix(Mat &in_)
{
    if (in_.channels()==3)
    {
        for (int i=0; i<in_.rows ; i+=1)
        {

            Vec3b* pixel = in_.ptr<Vec3b>(i);

            for (int j=0 ; j<in_.cols ; j+=1)
            {
                float r= (float)pixel[j][2];
                float g= (float)pixel[j][1];
                float b= (float)pixel[j][0];
                cout<<"r: "<<r<<" g: "<< g<< " b: "<< b << endl;
            }
        }
    }
    else if (in_.channels()==1)
    {
        for (int i=0; i<in_.rows ; i+=1)
        {

            uchar* pixel = in_.ptr<uchar>(i);

            for (int j=0 ; j<in_.cols ; j+=1)
            {
                float r= (float)pixel[j];

                cout<<"uchar: "<<r<<endl;
            }
        }
    }
}


void trainerObject::convertMat2Dlib(Mat &src_, std::vector<dlib::matrix<double, tImageCols, 1> > &dst, std::vector<double>& labels )
{
    //create a m type to pass to the matrix
    dlib::matrix<double,tImageCols,1> m;

    //iterate through the matrix
    for (int i=0; i<src_.rows;i++)
    {
        //create pointer to each row in matrix
        uchar * pixel = src_.ptr<uchar>(i);
        for (int j= 0 ; j<src_.cols;j++)
        {
            float p=(float)pixel[j];
            m(j)=p;
        }
//        for (int k =0 ; k< tImageCols;k++)
//        {
//            cout<< "mk: "<<m(k) << "labels is: "<<labelArray[i] <<endl;

//        }
        dst.push_back(m);
        labels.push_back(labelArray[i] + 1);


    }
    // each row is copied into the dlib vector

}

