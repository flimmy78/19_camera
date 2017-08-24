#ifndef FACERECOGNIZE_H
#define FACERECOGNIZE_H

#include "TSingleIns.h"
#include "global.h"
#include "database.h"

class WorkerThread : public QThread
{
public:
    explicit WorkerThread(int minFaceSize);
     ~WorkerThread();
    void DeInitFaceModel();
    void InitFaceModel();
    mpINT detectFaceNumWithFrame(RealMatStream &itemRealMatStream);
    void SaveAllDeivceImages(int inum, Mat tempimage, cv::Rect face_rect, RealMatStream &itemRealMatStream);
    bool CheckSaveImageFolder(QString qstrStorageImagePath, QString qstrDeviceNum);

protected:
    virtual void run();
 private:
    seeta::FaceDetection *m_pFaceDet;
    seeta::FaceAlignment *m_pFaceAli;
    seeta::FaceIdentification *m_pFaceIde;
    int m_iMinFaceSize;
    CascadeClassifier m_cascFace;
};

class faceRecognize: public QWidget
{

public:
    explicit faceRecognize(int minFaceSize,QLabel* Playwindow);
    ~faceRecognize();

    int InitHKVSCamera(char *deviceIP,short port, char * UserName, char * PassWord);
    int HKVS_PlayStop(long llRealHandle);
    //bool HKVS_CapturePic(HkvsHandle& hkvsHandle, QString qstrImagePath, QWidget* Playwindow);
    //bool HKVS_CapturePic(HkvsHandle& hkvsHandle, QString qstrImagePath, Mat& matImage);
    bool HKVS_CapturePic(HkvsHandle& hkvsHandle, QString qstrImagePath, QString qtrCurDeviceNum);
    void CleanItemFromVector(long llRealHandle);
private:
    WorkerThread* thread;
};

#endif // FACERECOGNIZE_H
