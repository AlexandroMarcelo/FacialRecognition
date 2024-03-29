#ifndef DATABASE_H
#define DATABASE_H
//Se incluyen las librerías necesarias.
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "opencv2/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/flann/flann_base.hpp"

using namespace cv::flann;

using std::string;
using cv::Mat;
using std::vector;

struct BiographicalData{
    string id,matricula,name,lastName,mail,img;
    int age;
    std::vector<cv::Point2f> points;
};

struct MatriculaId{
    int ID;
    string matricula;
};

class DataBase {
    private:
        Mat queries,ides,descriptores;    
        Index *flann_index;
        int n;
        string biographicalFile,biometricFile,nFile,id_matFile;
        std::fstream biographicalDB,biometricDB,N,Id_Mat;
        std::vector<MatriculaId> Id_MatriculaVector;
        std::vector<BiographicalData> biograData;
         
       

    public:
        DataBase();
        DataBase(string biographicalFile,string biometricFile,string nFile,string id_matFile);
        //https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
        inline bool existsFile (const std::string& name);//Return true if the file exists, false if not.
        bool load_N_File();
        bool load_BiometricFile();
        bool load_BiographicalFile();
        bool load_Id_MatriculaFile();
        Mat getMatrix();
        Mat getColumn(int num);
        Mat getRow(int num);
        std::pair <Mat, Mat> search(Mat elementoaBuscar,int K);
        Mat getBiometricByMatricula(string matricula);
        BiographicalData getUserInfoByID(int ID);
        BiographicalData getUserInfoByMatricula(string matricula);
        bool saveUserDataInAFile(BiographicalData bio,std::vector<cv::Point2f> points);
        bool saveId_Matricula(BiographicalData bio);
        bool saveUserBiometricDataInAFile(Mat biometric);
        void saveUserImage(Mat &image);
        bool getN();
        bool updateDataBase();
        std::vector<std::string> indexData(std::string dataLine);
        BiographicalData String_To_Structure(std::string Data_As_String);
        bool ValidName(std::string word);
        bool ValidateMail(std::string mail);
        int ValidateData(const BiographicalData* Data);
        bool ValidateMatricula(std::string matricula);
        bool DuplicatedMatricula(string mat);
        //~DataBase();
    
};
#endif
