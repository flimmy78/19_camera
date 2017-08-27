#ifndef GLOBAL_H
#define GLOBAL_H

//MP_BGN_C_DECLS

//qt header
#include <QApplication>
#include <QWidget>
#include <QCheckBox>
#include <QListWidget>
#include <QLineEdit>
#include <QDebug>
#include <QDate>
#include <QDateTimeEdit>
#include <QTimer>
#include <QMessageBox>
#include <QSettings>
#include <QList>
#include <QDir>
#include <QByteArray>
#include <QFileDialog>
#include <QProcessEnvironment>
#include <QLibrary>
#include <QDesktopWidget>
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QLabel>

//QT DATABASE HEADER
#include <QSqlDatabase>
#include <QDebug>
#include <qwindow.h>
#include <QSqlQuery>
#include <QSqlError>
#include<QtPlugin>
#include <QtSql/QSql>

//opencv header
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

//c header
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

#include <stdarg.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
//time
#include <time.h>
#include <sys/time.h>

//c++ header
#include <iostream>

//seeta face header
#include "face_identification.h"
#include "recognizer.h"
#include "face_detection.h"
#include "face_alignment.h"
#include "math_functions.h"
#include "common.h"
#include "face_rec.h"

//hkvs header
#include "HCNetSDK.h"
#include "plaympeg4.h"

using namespace  std;
using namespace cv;
using namespace seeta;

typedef void                    mpVOID;
typedef bool                    mpBOOL;
typedef char                    mpCHAR;
typedef unsigned char           mpBYTE;
typedef int                     mpINT;
typedef unsigned int            mpUINT;
typedef long                    mpLONG;
typedef unsigned long           mpULONG;
typedef unsigned short          mpWORD;
typedef unsigned int            mpDWORD;
typedef unsigned long long      mpQWORD;
typedef float                   mpFLOAT;
typedef double                  mpDOUBLE;

#define MP_MALLOC(s)            MP_Malloc(s)
#define MP_FREE(p)              MP_Free(p)
#define MP_NEW  				new
#define MP_DELETE       		delete

#define mpTRUE                  1
#define mpFALSE                 0
#define mpNULL                  0
#define CONFIG_DIR              "/config/"
#define FACE_CASCADE_DIR        "/cascade/"
#define FACE_MODES_DIR          "/models/"
#define FACE_IMAGE_SAVE_FOLDER_NAME  "/image/"
#define FACE_STORAGE_GROUP_NAME "Storage"
#define DEFAULT_REC_MIN_FACE_SIZE 40

#define USLEEP_DELAY_100MS 100*1000
#define USLEEP_DELAY_10MS 10*1000

#define QMESSAGEBOX_WARNING     "Warning"
#define QMESSAGEBOX_WARNING_CHINSE     "提示"
#define DEFAULT_MAXDEVICE_NUMBER    24
#define DEFAULT_MAXDEVICE_NAME  "maximum"

#define HKVS_HWDN_ST_MAX_LEN  50
#define HKVS_CHANNEL_DEFAULT_VALUE    1

#define HKVX_DEVICE_LOGOUT_STATE   0
#define HKVX_DEVICE_LOGIN_STATE    1

#define HKVS_VIDEO_HEIGHT   1080
#define HKVS_VIDEO_WIDTH    1920

#define HKVS_VIDEO_HEIGHT_640   640
#define HKVS_VIDEO_WIDTH_480    480

#define SET_RESOLUTION_480_640  480*640
#define SET_RESOLUTION_240_320  240*320
#define SET_RESOLUTION_384_288  384*288
#define RESOLUTION_480_640_ID   163
#define RESOLUTION_240_320_ID   164
  
#define W_ICONSIZE   140
#define H_ICONSIZE   110
#define H_ITEMSIZE   142

#define SET_SOFTWARE_DUE_DATE   "2017-09-25"
#define SET_SCREENSHOT_IMAGE    
#define SET_SYSTEM_LANGUAGE_CHINESE 

typedef struct
{
    struct tm logSec;
    mpINT logMSec;
} LogTime;

typedef struct
{
    QString strDeviceNum;
    QString strIntervalSec;
    QString strUsrName;
    QString strPassword;
    QString strIpaddr;
    QString strPort;
    QString strDeviceName;
    void initLoginInfo() {
        strDeviceNum.clear();
        strIntervalSec.clear();
        strUsrName.clear();
        strPassword.clear();
        strIpaddr.clear();
        strPort.clear();
        strDeviceName.clear();
    }
}LoginInfo;

typedef struct
{
    long deviceid;
    long lRealHandle;
    QString qstrIpAddr;
    QString qstrDevNum;//device number
    QString qstrDevName;
    mpBOOL bState;      //FALSE logout TRUE login
    int dueTime; //
    HWND hPlayWnd;
    void initialize(){
        deviceid = -1;
        lRealHandle = -1;
        qstrIpAddr.clear();
        qstrDevNum.clear();
        qstrDevName.clear();
        bState = mpFALSE;
        dueTime = 0;
        hPlayWnd = NULL;
    }
}HkvsHandle;

typedef struct
{
    QString qstrImagePath;
    QString qstrExpireDays;
    void initialize(){
        qstrImagePath.clear();
        qstrExpireDays.clear();
    }
}StorageInfo;

typedef struct {
    QString qstrFilePath;
    QString qstrFileName;
    QString qstrDirName;
}SearchResult;

typedef struct {
    long lport;
    long llRealHandle;
    long lDeviceId;
    Mat matImage;
    //Mat* pMatImage;
    bool isRead;
    bool isDetected;
    bool isErase;
    QString qstrDevNum;//
    QString qstrImagePath;
    int dueTime; //
    clock_t recordTime;
    initialize(){
        isRead = mpFALSE;
        isDetected = mpFALSE;
        isErase = mpFALSE;
        lport = -1;
        llRealHandle =-1;
        lDeviceId = -1;
        qstrImagePath.clear();
        qstrDevNum.clear();
        matImage.create(HKVS_VIDEO_HEIGHT,HKVS_VIDEO_WIDTH,CV_8UC3);
        //pMatImage = NULL;
        dueTime = 0;
        recordTime = clock();
    }
}RealMatStream;

#define PRT_INFO(fmt, ...) MP_Log(__FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
/**
 * @ingroup SUB_GROUP_LOG
 * @brief
 * @param   pszFile in which file
 * @param   iLine   in which line
 * @param   pFunction   in which function
 * @parma   format  output format
 */
mpVOID MP_Log(const mpCHAR * pszFile, mpINT iLine, const mpCHAR * pFunction,const mpCHAR * format, ...);

//MP_END_C_DECLS

#endif // GLOBALHEAD


