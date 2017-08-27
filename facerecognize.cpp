#include "facerecognize.h"

vector<RealMatStream> realMatStreams;
static QLabel* g_playlable = NULL;
QString g_qtrCurDeviceNum;

faceRecognize::faceRecognize(int minFaceSize,QLabel* Playwindow)
{
    thread = new WorkerThread(minFaceSize);
    //thread->start(QThread::LowPriority); close this function
    realMatStreams.clear();
    g_playlable = Playwindow;
}

faceRecognize::~faceRecognize()
{
    if(mpNULL != thread)
    {
        thread->terminate();
        delete thread;
        thread = mpNULL;
    }
}

WorkerThread::WorkerThread(int minFaceSize)
{
    m_iMinFaceSize = minFaceSize;
    InitFaceModel();
}

WorkerThread::~WorkerThread()
{
    DeInitFaceModel();
    qDebug()<<"~WorkerThread";
}


///<summary> Initialize face model of the seeta  </summary>
void WorkerThread::InitFaceModel()
{
    cout<<"Initialize Face Detection Model!"<<endl;
    QString  qstrCurPath = QApplication::applicationDirPath();
    if(access((qstrCurPath + FACE_MODES_DIR).toStdString().c_str(), R_OK) == 0)
    {
        cout<<"starting Load face detection libs..."<<endl;
        // Initialize face Detection model
        m_pFaceDet = new FaceDetection((qstrCurPath + FACE_MODES_DIR + "face_fd.bin").toStdString().c_str());
        // Initialize face alignment model
        m_pFaceAli = new FaceAlignment((qstrCurPath + FACE_MODES_DIR + "face_fa.bin").toStdString().c_str());
        // Initialize face Identification model
        m_pFaceIde = new FaceIdentification((qstrCurPath + FACE_MODES_DIR + "face_fr.bin").toStdString().c_str());

        m_pFaceDet->SetMinFaceSize(m_iMinFaceSize);
        m_pFaceDet->SetScoreThresh(2.f);
        m_pFaceDet->SetImagePyramidScaleFactor(0.8f);
        m_pFaceDet->SetWindowStep(4, 4);
        cout<<"Load face detection libs finshed!"<<endl;
    }
    else
    {
        cout <<"please check your resource floder,make sure the seeta bin!"<<endl;
        return;
    }
}

 void WorkerThread::DeInitFaceModel()
 {
     //delete seeta pointer
     if(mpNULL != m_pFaceDet)
     {
         delete m_pFaceDet;
         m_pFaceDet = mpNULL;
     }

     if(mpNULL != m_pFaceAli)
     {
         delete m_pFaceAli;
         m_pFaceAli = mpNULL;
     }

     if(mpNULL != m_pFaceIde)
     {
         delete m_pFaceIde;
         m_pFaceIde = mpNULL;
     }
 }

 ///<summary> check and create folder</summary>
bool WorkerThread::CheckSaveImageFolder(QString qstrStorageImagePath, QString qstrDevNum)
{
    mpBOOL bRet = mpFALSE;
    if(access(qstrStorageImagePath.toStdString().c_str(), R_OK) != 0)
    {
        qDebug() <<"Can't found the image folder!Waiting to create...";
        QDir dir;
        mpBOOL ok = dir.mkdir(qstrStorageImagePath);
        if(!ok)  return bRet;
    }

    QString qstrDeviceNum = qstrDevNum + "/";
    if(access((qstrStorageImagePath + qstrDeviceNum).toStdString().c_str(), R_OK) != 0)
    {
        qDebug() <<"Can't found the device folder!Waiting to create...";
        QDir dir;
        mpBOOL ok = dir.mkdir(qstrStorageImagePath + qstrDeviceNum);
        if(!ok)  return bRet;
    }

    QDateTime datetime =  QDateTime::currentDateTime();
    QString qstrDate = datetime.toString("yyyy-MM-dd/");
    if(access((qstrStorageImagePath + qstrDeviceNum + qstrDate).toStdString().c_str(), R_OK) != 0)
    {
        qDebug() <<"Can't found the qstrDate folder!Waiting to create...";
        QDir dir;
        mpBOOL ok = dir.mkdir(qstrStorageImagePath + qstrDeviceNum + qstrDate);
        if(!ok)  return bRet;
    }
    return mpTRUE;
}

void WorkerThread::run()
{
    while(1)
    {
        //qDebug()<<"realMatStreams size:"<<realMatStreams.size();
        std::vector<RealMatStream>::iterator itor;
        for(itor = realMatStreams.begin(); itor != realMatStreams.end(); itor++)
        {
            if( (*itor).isErase ) {
                realMatStreams.erase(itor);
                break;
            }

            if( (*itor).isDetected ) {
                RealMatStream itemRealMatStream;
                itemRealMatStream.initialize();
                itemRealMatStream.recordTime = (*itor).recordTime;
                itemRealMatStream.qstrDevNum = (*itor).qstrDevNum;
                itemRealMatStream.qstrImagePath = (*itor).qstrImagePath;
                itemRealMatStream.dueTime =  (*itor).dueTime;
                (*itor).matImage.copyTo(itemRealMatStream.matImage);
                (*itor).isDetected = mpFALSE;
                detectFaceNumWithFrame(itemRealMatStream);
               (*itor).isDetected = mpFALSE;
               detectFaceNumWithFrame((*itor));

            }
        }
        usleep(USLEEP_DELAY_100MS);//wait Nms
    }
}

///<summary> detect face from the frame </summary>
mpINT WorkerThread::detectFaceNumWithFrame(RealMatStream &itemRealMatStream)
{
    if(itemRealMatStream.matImage.cols != HKVS_VIDEO_HEIGHT_640 ||
       itemRealMatStream.matImage.rows != HKVS_VIDEO_WIDTH_480)
    {
          qDebug()<<"detectFaceNumWithFrame"<< "cols:"<<itemRealMatStream.matImage.cols << "rows:" << itemRealMatStream.matImage.rows;
          return -1;
    }

    if(itemRealMatStream.matImage.empty()) return -1;
    cv::Mat gallery_img_gray(itemRealMatStream.matImage.cols,itemRealMatStream.matImage.rows,CV_8UC3);
    cv::cvtColor(itemRealMatStream.matImage, gallery_img_gray, CV_BGR2GRAY);
    seeta::ImageData img_data_gray(gallery_img_gray.cols, gallery_img_gray.rows, gallery_img_gray.channels());
    img_data_gray.data = gallery_img_gray.data;
    img_data_gray.width = gallery_img_gray.cols;
    img_data_gray.height = gallery_img_gray.rows;
    img_data_gray.num_channels = 1;

    std::vector<seeta::FaceInfo> faces = m_pFaceDet->Detect(img_data_gray);  // Detect faces
    int32_t num = static_cast<int32_t>(faces.size());
    if (num == 0) return 0;

    for(int inum = 0; inum < num; inum++)
    {
        //Drawing the face rect
        cv::Rect face_rect;
        face_rect.x = faces[inum].bbox.x;
        face_rect.y = faces[inum].bbox.y;
        face_rect.width = faces[inum].bbox.width;
        face_rect.height = faces[inum].bbox.height;

        Mat tempimage(HKVS_VIDEO_HEIGHT_640,HKVS_VIDEO_WIDTH_480,CV_8UC3);
        itemRealMatStream.matImage.copyTo(tempimage);
        cv::rectangle(itemRealMatStream.matImage, face_rect, CV_RGB(255, 0, 0), 4, 8, 0);
        SaveAllDeivceImages(inum, tempimage, face_rect, itemRealMatStream);
   }

   return num;
}

///<summary>check and save image,insert record into database</summary>
void WorkerThread::SaveAllDeivceImages(int inum, Mat matImage, cv::Rect face_rect, RealMatStream &itemRealMatStream)
{
    if(matImage.empty() || itemRealMatStream.qstrImagePath.isEmpty() || itemRealMatStream.qstrDevNum.isEmpty() ) return;

    QDateTime datetime =  QDateTime::currentDateTime(); //get the current date
    QString qstrDate = datetime.toString("yyyy-MM-dd");//set formal
    QString qstrStoragePath = itemRealMatStream.qstrImagePath + itemRealMatStream.qstrDevNum + "/" + qstrDate + "/";
    QString strDateTime = datetime.toString("yyyyMMddhhmmss_");
    QString qstrFileName = strDateTime + QString("%1.jpg").arg(inum);
    QString qstrImageName = qstrStoragePath + qstrFileName;

    mpBOOL bRet = CheckSaveImageFolder(itemRealMatStream.qstrImagePath, itemRealMatStream.qstrDevNum);
    if(!bRet) return;

    clock_t curTime = clock();
    double diffticks = curTime - itemRealMatStream.recordTime;
    double diffms = diffticks / (CLOCKS_PER_SEC / 1000);
    if( (diffms/1000) > itemRealMatStream.dueTime)
    {
#ifdef  SET_SCREENSHOT_IMAGE
        cv::Rect set_face_rect = face_rect;
        set_face_rect.x = set_face_rect.x - 20;
        set_face_rect.y = set_face_rect.y - 20;
        set_face_rect.width = set_face_rect.width + 40;
        set_face_rect.height = set_face_rect.height + 40;

        if(set_face_rect.x >= 20 && set_face_rect.y >= 20
         && (set_face_rect.x + set_face_rect.width) <= HKVS_VIDEO_HEIGHT_640
         && (set_face_rect.y + set_face_rect.height) <= HKVS_VIDEO_WIDTH_480)
        {
            qDebug()<<"write1:"<<qstrImageName;
            Mat tempImage(matImage,set_face_rect);

            cv::resize(tempImage, tempImage, cv::Size(HKVS_VIDEO_HEIGHT_640,HKVS_VIDEO_WIDTH_480),0,0);
            Mat dstImage(HKVS_VIDEO_HEIGHT_640,HKVS_VIDEO_WIDTH_480,CV_8UC3);
            cv::GaussianBlur(tempImage,dstImage,Size(7, 7),0,0);
            QString qstrPutDateTime = datetime.toString("yyyy/MM/dd hh:mm:ss");
            //put the date time into image
            putText(dstImage, qstrPutDateTime.toStdString(), Point(50, 50), FONT_HERSHEY_PLAIN, 1.5, CV_RGB(255,0,0), 2.0);
            cv::imwrite(qstrImageName.toStdString(), dstImage);
            itemRealMatStream.recordTime = clock();//update the record time
            QString qstrDBDateTime = datetime.toString("yyyy-MM-dd hh:mm:ss");
            face_database_api::GetInstance()->face_database_insert_facetable(itemRealMatStream.qstrDevNum, qstrDate, qstrStoragePath, qstrDBDateTime, qstrFileName);
        }
#else
        qDebug()<<"write2:"<<qstrImageName;
        QString qstrPutDateTime = datetime.toString("yyyy/MM/dd hh:mm:ss");
        //put the date time into image
        putText(itemRealMatStream.matImage, qstrPutDateTime.toStdString(), Point(50, 50), FONT_HERSHEY_PLAIN, 1.5, CV_RGB(255,0,0), 2.0);
        cv::imwrite(qstrImageName.toStdString(), itemRealMatStream.matImage);
        itemRealMatStream.recordTime = clock();//update the record time
        QString qstrDBDateTime = datetime.toString("yyyy-MM-dd hh:mm:ss");
        face_database_api::GetInstance()->face_database_insert_facetable(itemRealMatStream.qstrDevNum, qstrDate, qstrStoragePath, qstrDBDateTime, qstrFileName);
#endif
    }

}

///<summary> Get that number according to the input nPort</summary>
int Get_Number_By_Port(long nPort)
{
    int iRet = -1;
    int i = -1;
    std::vector<RealMatStream>::iterator itor;
    for(itor = realMatStreams.begin(),i=0; itor != realMatStreams.end(); itor++,i++)
    {
        if( nPort == (*itor).lport) {
            iRet = i;
            break;
        }
    }
    return iRet;
}

///<summary> Show the result video with UI show video area </summary>
void showImageWithUI(Mat matImage)
{
    if(matImage.empty()) return;
    QImage qImage=QImage((const uchar*)matImage.data,matImage.cols,matImage.rows,QImage::Format_RGB888).rgbSwapped();
    qImage = qImage.scaled(640, 480);
    g_playlable->setPixmap(QPixmap::fromImage(qImage));
}

///<summary> Get that image frame according to the input port</summary>
void CALLBACK DecCBFun(long nPort, char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nUser,long nReserved2)
{
    if(mpNULL == pBuf || mpNULL == pFrameInfo) {
        qDebug()<< "The pBuf and pFrameInfo can not be NULL.";
        return;
    }

    if(pFrameInfo->nType ==T_YV12)
    {
        //YUV TO BGR (YV12)
        int number = Get_Number_By_Port(nPort);
        if(number < 0 ) return;

        if( !realMatStreams[number].isRead && !realMatStreams[number].isErase)
        {
            if(pFrameInfo->nHeight < 0 || pFrameInfo->nWidth < 0 || nPort == -1) return;

            Mat matImage(pFrameInfo->nHeight,pFrameInfo->nWidth,CV_8UC3);
            Mat srcImage(pFrameInfo->nHeight + pFrameInfo->nHeight/2,pFrameInfo->nWidth,CV_8UC1,(uchar*)pBuf);
            if(matImage.empty()) return;
            cvtColor(srcImage,matImage,CV_YUV2BGR_YV12);
            cv::resize(matImage, matImage, cv::Size(640,480),0,0);
            matImage.copyTo(realMatStreams[number].matImage);

            if(0 == g_qtrCurDeviceNum.compare( realMatStreams[number].qstrDevNum) ) {
                //put the date time into image
                putText(matImage, realMatStreams[number].qstrDevNum.toStdString(), Point(500, 50), FONT_HERSHEY_PLAIN, 1.5, CV_RGB(255,0,0), 2.0);
                showImageWithUI(matImage);
            }
            realMatStreams[number].isRead = mpTRUE;
       }
    }
    usleep(USLEEP_DELAY_10MS);//wait Nms
}

///<summary> Get that number according to the input lRealHandle</summary>
int getRealDataTableNumber(long lRealHandle)
{
    int iRet = -1;
    int i = 0;

    std::vector<RealMatStream>::iterator itor;
    for(itor = realMatStreams.begin(),i=0; itor != realMatStreams.end(); itor++,i++)
    {
        if( lRealHandle == (*itor).llRealHandle) {
            iRet = i;
            break;
        }
    }
    return iRet;
}

///<summary> HK's callback control input port value accroding to the lRealHandle</summary>
void CALLBACK fRealDataCallBack(LONG lRealHandle,DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,void *pUser)
{
    DWORD dRet = 0;
    int number = getRealDataTableNumber(lRealHandle);

    if(number < 0 ) return;

    long port = -1;
    switch (dwDataType)
    {
        case NET_DVR_SYSHEAD:
            if (!PlayM4_GetPort(&port)) {
                return;
            }
            if(port < 0 ) return;
            realMatStreams[number].lport = port;

            if (!PlayM4_OpenStream(port,pBuffer,dwBufSize,1024*1024))
            {
                dRet=PlayM4_GetLastError(port);
                break;
            }

            if (!PlayM4_SetDecCallBackExMend(port,DecCBFun,NULL,NULL,NULL) )
            {
                dRet=PlayM4_GetLastError(port);
                break;
            }

            if (!PlayM4_Play(port,NULL))
            {
                dRet=PlayM4_GetLastError(port);
                break;
            }
            break;

        case NET_DVR_STREAMDATA:
        default:
            if(realMatStreams[number].lport == -1) return;
            BOOL inData=PlayM4_InputData(realMatStreams[number].lport,pBuffer,dwBufSize);
            while (!inData)
            {
                Sleep(10);

                inData=PlayM4_InputData(realMatStreams[number].lport,pBuffer,dwBufSize);
            }
            break;
    }
}

///<summary> Get capture image which is according to realhandle, if less than zero start init device</summary>
//bool faceRecognize::HKVS_CapturePic(HkvsHandle& hkvsHandle, QString qstrStorageImagePath, Mat& matImage)
bool faceRecognize::HKVS_CapturePic(HkvsHandle& hkvsHandle, QString qstrStorageImagePath, QString qtrCurDeviceNum)
{
    g_qtrCurDeviceNum = qtrCurDeviceNum;
    mpBOOL bRet = mpFALSE;
    if(hkvsHandle.lRealHandle < 0)
    {
        //HWND hPlayWnd=(HWND)Playwindow->winId();
        NET_DVR_CLIENTINFO ClientInfo;
        ClientInfo.lChannel = 1; //Channel number
        //ClientInfo.hPlayWnd = hPlayWnd;
        ClientInfo.hPlayWnd = NULL;
        ClientInfo.lLinkMode = 0;    //Main Stream
        ClientInfo.sMultiCastIP = NULL;
        if (hkvsHandle.deviceid < 0) {
            qDebug()<<"device id error";
            return bRet;
        }

        long llRealHandle = NET_DVR_RealPlay_V30(hkvsHandle.deviceid,&ClientInfo,fRealDataCallBack,NULL,false);
        if (llRealHandle < 0) {
            qDebug()<<"playback error";
            return bRet;
        }

        RealMatStream tempRealMatStream;
        tempRealMatStream.initialize();
        tempRealMatStream.lDeviceId = hkvsHandle.deviceid;
        tempRealMatStream.dueTime = hkvsHandle.dueTime;
        tempRealMatStream.qstrDevNum = hkvsHandle.qstrDevNum;
        tempRealMatStream.qstrImagePath = qstrStorageImagePath;
        tempRealMatStream.llRealHandle = llRealHandle;
        realMatStreams.push_back(tempRealMatStream);
        qDebug()<<"realMatStreams size:"<<realMatStreams.size();
        hkvsHandle.lRealHandle = llRealHandle;
    } else {
        int number = getRealDataTableNumber(hkvsHandle.lRealHandle);
        if(number <0 ) return bRet;

        if(realMatStreams[number].isRead && !realMatStreams[number].isErase)
        {
            //if(realMatStreams[number].matImage.empty()) return bRet;
            //realMatStreams[number].matImage.copyTo(matImage);
            realMatStreams[number].qstrImagePath = qstrStorageImagePath;
            realMatStreams[number].dueTime = hkvsHandle.dueTime;
            thread->detectFaceNumWithFrame(realMatStreams[number]);
            realMatStreams[number].isRead = mpFALSE;
        }
    }

    return mpTRUE;
}

///<summary> Init and open the hkvs camera device</summary>
int faceRecognize::InitHKVSCamera(char *deviceip,short port, char * UserName, char * PassWord)
{
    if( mpNULL == deviceip || mpNULL == UserName ||  mpNULL == PassWord) {
        qDebug()<<" usr info can not be NULL!";
        return -2;
    }

    NET_DVR_Init();
    NET_DVR_DEVICEINFO_V30 devInfo;
    int deviceid = NET_DVR_Login_V30(deviceip,port,UserName,PassWord,&devInfo);
    if(-1 != deviceid )
    {
        qDebug()<<"deviceid:"<<deviceid;
    } else {
        qDebug()<<"get id error!";
    }

    return deviceid;
}

///<summary> Clean operate, erase in work thread</summary>
void faceRecognize::CleanItemFromVector(long llRealHandle)
{
    std::vector<RealMatStream>::iterator itor;
    for(itor = realMatStreams.begin(); itor != realMatStreams.end(); itor++)
    {
        if( llRealHandle == (*itor).llRealHandle) {
            (*itor).isErase = mpTRUE;
            realMatStreams.erase(itor);
            qDebug()<<"success sign erase";
            break;
        }
    }
}

///<summary> Init and open the hkvs camera device</summary>
int faceRecognize::HKVS_PlayStop(long llRealHandle)
{
    if(llRealHandle < 0 ) return -1;
    int number = getRealDataTableNumber(llRealHandle);
    if(number < 0 ){
         qDebug()<<" number == -1";
        return -1;
     }

    if (realMatStreams[number].lDeviceId < 0) {
        qDebug()<<"device_id error";
        return -1;
    }
    NET_DVR_Logout_V30(realMatStreams[number].lDeviceId);

    BOOL lRet=NET_DVR_StopRealPlay(llRealHandle);
    while (!lRet)//if false repeat close
    {
        qDebug()<< "stop real play error "<<NET_DVR_GetLastError();
        usleep(1000*10);
        lRet = NET_DVR_StopRealPlay(llRealHandle);
    }

    qDebug()<<"HKVS_PlayStop port:"<<realMatStreams[number].lport;
    if(realMatStreams[number].lport < 0 ) {
        CleanItemFromVector(llRealHandle);
        return -1;
    }

     int iRet = -1;
     if (!PlayM4_StopSound()) {
            iRet = PlayM4_GetLastError(realMatStreams[number].lport);
     }
     if (!PlayM4_Stop(realMatStreams[number].lport)) {
            iRet = PlayM4_GetLastError(realMatStreams[number].lport);
     }
     if (!PlayM4_CloseStream(realMatStreams[number].lport)) {
            iRet = PlayM4_GetLastError(realMatStreams[number].lport);
     }
     if (!PlayM4_FreePort(realMatStreams[number].lport) ){
            iRet = PlayM4_GetLastError(realMatStreams[number].lport);
     }

    NET_DVR_Cleanup();
    CleanItemFromVector(llRealHandle);

    return iRet;
}
