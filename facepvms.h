#ifndef FACEPVMS_H
#define FACEPVMS_H

#include "DefDateTimeEdit.h"
#include "global.h"
#include "facerecognize.h"

namespace Ui {
class facePvms;
}
using namespace std;

class facePvms : public QWidget
{
    Q_OBJECT

public:
    explicit facePvms(QWidget *parent = 0);
    ~facePvms();

private:
    void InitFunctionSetting();
    void InitDeviceSelectedBox();

    void SetConfigFilePath();
    bool WriteConfigInfo(QString path, LoginInfo info);
    bool ReadConfigItemInfo(QString path, LoginInfo& info);
    bool ReadConfigLineInfo(QString path,QString key, QString& value);
    void CheckDeleteExpiredDirectory(QString qstrDirName,QString qstrDirPath);
    void GetSelectedQStringDateTime(DefDateTimeEdit* dateTimeEdit, QString& qstrSelectedDateTime);

    void FindTargetFaceImage(QString qstrFindPath,QString qstrFindImage);
    void closeAllDeviceid();
    bool  checkIPWhetherInVector(QString qstrIpAddr);
    bool closeDeviceWithNumber( QString qstrDevNum);
    bool WriteConfigLine(QString path, QString group, QString key, QString value);
    bool deleteAppointDir(const QString &dirPath);
    void DeleteExpiredRecordFromDataBase(QString qstrBeforeDate);
    void SetCalendarSelectDays();
    void GetDeviceNumberFromConifgFile(QString qstrDeviceName,  QString& qstrDeviceNumber);

private slots:
    void textChanged();
    void stateChanged();
    void setStartDateTime(const QDateTime &dateTime);
    void setEndDateTime(const QDateTime &dateTime);
    void readFrame();
    void ImageListItemClicked(QListWidgetItem * item);
    void on_pushButton_search_clicked();

    void on_pushButton_save_clicked();

    void on_pushbutton_device_config_clicked();

    void on_pushbutton_device_open_clicked();

    void on_pushButton_device_close_clicked();

    void on_pushButton_pathSelect_clicked();

    void on_pushButton_storageConfirm_clicked();

private:
    Ui::facePvms *ui;
    bool bSelected;
    QListWidget *pListWidget;
    QLineEdit *pLineEdit;
    QString strSelectedText;
    QTimer *m_pTimer;

    DefDateTimeEdit* m_defStartDTE;
    DefDateTimeEdit* m_defEndDTE;

    QWidget* startWidgetCalendar;
    QWidget* endWidgetCalendar;

    QCheckBox *m_pCheckBox;
    QString m_qstrCurPath;
    QString m_qstrCurConfigFilePath;
    faceRecognize* m_pFaceRec;
    QString m_qstrLastIp;
    vector<HkvsHandle> HkvsHandles;
    StorageInfo m_storageInfo;
    vector<QString> m_deviceStrIds;
    QString m_qstrDeviceNum;
    QListWidget *m_pListWidget;
    int m_iMaxDeviceNum;
};

#endif // FACEPVMS_H
