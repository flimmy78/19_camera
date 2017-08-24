#include "facepvms.h"
#include "ui_facepvms.h"

facePvms::facePvms(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::facePvms)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Widget|Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
    m_pTimer = new QTimer(this);
    face_database_api::GetInstance();

    HkvsHandles.clear();
    m_deviceStrIds.clear();
    SetConfigFilePath();
    InitFunctionSetting();
    InitDeviceSelectedBox();
    SetCalendarSelectDays();
    connect(m_defStartDTE, SIGNAL(setFinished(QDateTime)), this, SLOT(setStartDateTime(QDateTime)));
    connect(m_defEndDTE, SIGNAL(setFinished(QDateTime)), this, SLOT(setEndDateTime(QDateTime)));
    connect(m_pListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(ImageListItemClicked(QListWidgetItem*)));
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(readFrame()));
}

facePvms::~facePvms()
{
    if(mpNULL != m_pTimer)
    {
        m_pTimer->stop();
        delete m_pTimer;
        m_pTimer = mpNULL;
    }
    if(mpNULL != m_pFaceRec)
    {
        delete m_pFaceRec;
        m_pFaceRec = mpNULL;
    }

    face_database_api::ReleaseInstance();
    closeAllDeviceid();
    delete ui;
    qDebug() <<"exit face pvms!";
}

void facePvms::ImageListItemClicked(QListWidgetItem * item)
{
    if(!item) return;

    qDebug()<<item->text();
    QString imagePath = item->text();
    if(imagePath.isEmpty()) return;

    cv::Mat matImage = cv::imread(imagePath.toStdString(), 1);
    if (matImage.empty()) {
        qDebug()<<"Read image error";
        return;
    }
    QImage qImage=QImage((const uchar*)matImage.data,matImage.cols,matImage.rows,QImage::Format_RGB888).rgbSwapped();
    QPixmap objPixmap=QPixmap::fromImage(qImage);

    QWidget* pWidget=new QWidget();
    pWidget->resize(QSize(640,480));
    pWidget->setWindowTitle(item->text());
    pWidget->setWindowFlags(Qt::Widget|Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);

    QLabel* pic=new QLabel(pWidget);
    pic->setPixmap(objPixmap.scaled(QSize(640,480)));
    pWidget->show();

    update();
}

///<summary> Init prepare params Setting</summary>
void facePvms::InitFunctionSetting()
{
    //init show listwidget view
    m_pListWidget = ui->listWidget_imagelist;
    m_pListWidget->setIconSize(QSize(W_ICONSIZE, H_ICONSIZE));
    m_pListWidget->setResizeMode(QListView::Adjust);
    m_pListWidget->setViewMode(QListView::IconMode);
    m_pListWidget->setMovement(QListView::Static);
    m_pListWidget->setSpacing(10);

    //init widget  calender
    startWidgetCalendar = ui->widget_startCanlendar;
    endWidgetCalendar = ui->widget_endCanlendar;
    m_defStartDTE = new DefDateTimeEdit(startWidgetCalendar);
    m_defEndDTE  = new DefDateTimeEdit(endWidgetCalendar);

    //init config funtion
    ui->groupBox_configArea->hide();
    ui->spinBox_deviceNumber->setMinimum(1);
    ui->spinBox_storagedate->setMinimum(1);

    m_storageInfo.initialize();
    ReadConfigLineInfo(m_qstrCurConfigFilePath.toStdString().c_str(),"Storage/imagePath", m_storageInfo.qstrImagePath);
    if(m_storageInfo.qstrImagePath.isEmpty() )
        m_storageInfo.qstrImagePath = m_qstrCurPath + FACE_IMAGE_SAVE_FOLDER_NAME;
    ui->lineEdit_imagePath->setText(m_storageInfo.qstrImagePath);

    mpBOOL bRes = ReadConfigLineInfo(m_qstrCurConfigFilePath.toStdString().c_str(),"Storage/expireDays", m_storageInfo.qstrExpireDays);
    bool ok = false;
    int storageValue = m_storageInfo.qstrExpireDays.toInt(&ok,10);
    if(bRes) ui->spinBox_storagedate->setValue(storageValue);

    QString qstrValue;
    bRes = ReadConfigLineInfo(m_qstrCurConfigFilePath.toStdString().c_str(),"FaceConfig/setRecMinFaceSize", qstrValue);
    if(bRes) {
       int faceValue = qstrValue.toInt(&ok,10);
        m_pFaceRec = MP_NEW faceRecognize(faceValue, ui->label_DisplayCam);
    }  else {
        m_pFaceRec = MP_NEW faceRecognize(DEFAULT_REC_MIN_FACE_SIZE,ui->label_DisplayCam);
        WriteConfigLine(m_qstrCurConfigFilePath, "FaceConfig", "setRecMinFaceSize",QString("%1").arg(DEFAULT_REC_MIN_FACE_SIZE));
    }
}

///<summary> Read the max device number,Init the selected box</summary>
 void facePvms:: InitDeviceSelectedBox()
 {
     pListWidget = new QListWidget(this);
     pLineEdit = new QLineEdit(this);

     m_iMaxDeviceNum = DEFAULT_MAXDEVICE_NUMBER;
     QString maxValue;
     mpBOOL bRes = ReadConfigLineInfo(m_qstrCurConfigFilePath.toStdString().c_str(),"maxdevice/maximum", maxValue);
     if(!bRes)  {
         WriteConfigLine(m_qstrCurConfigFilePath, "maxdevice", "maximum",QString("%1").arg(m_iMaxDeviceNum));
     } else {
         bool ok;
         m_iMaxDeviceNum = maxValue.toInt(&ok,10);
         qDebug() <<"maxNum:"<<m_iMaxDeviceNum;
     }

     for (int i = 1; i < m_iMaxDeviceNum + 1; i++)
     {
         QListWidgetItem *pListWidgetItem = new QListWidgetItem(pListWidget);
         pListWidget->addItem(pListWidgetItem);
         pListWidgetItem->setData(Qt::UserRole, i);
         pListWidget->addItem(pListWidgetItem);

         QCheckBox *pCheckBox = new QCheckBox(this);
         QString qstrDeviceNameIndex = QString("device%1/deviceName").arg(i);
         QString qstrDeviceNameValue;
         mpBOOL bReadRes = ReadConfigLineInfo(m_qstrCurConfigFilePath.toStdString().c_str(),qstrDeviceNameIndex, qstrDeviceNameValue);
         if(bReadRes)
             pCheckBox->setText(qstrDeviceNameValue);
         else
             pCheckBox->setText(QStringLiteral("device%1").arg(i));

         pListWidget->setItemWidget(pListWidgetItem, pCheckBox);
         connect(pCheckBox, SIGNAL(clicked(bool)), this, SLOT(stateChanged()));
     }
     ui->comboBox->setModel(pListWidget->model());
     ui->comboBox->setView(pListWidget);
     ui->comboBox->setLineEdit(pLineEdit);
     pLineEdit->setReadOnly(true);                                                                                                                    //ui.comboBox->setEditable(true);
     connect(pLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged()));
}

 void facePvms::GetDeviceNumberFromConifgFile(QString qstrDeviceName,  QString& qstrDeviceNumber)
 {
     if(qstrDeviceName.isEmpty() ) {
         qDebug()<< "Inquiry can not empty!";
         return;
     }
     for (int i = 1; i < m_iMaxDeviceNum + 1; i++)
     {
         QString qstrInquiryDeviceNameIndex = QString("device%1/deviceName").arg(i);
         QString qstrInquiryDeviceNameValue;
         mpBOOL bReadRes = ReadConfigLineInfo(m_qstrCurConfigFilePath.toStdString().c_str(),qstrInquiryDeviceNameIndex, qstrInquiryDeviceNameValue);
         if(bReadRes && 0 == qstrDeviceName.compare(qstrInquiryDeviceNameValue)) {
             qstrDeviceNumber = QString("device%1").arg(i);
             qDebug()<<"return: "<<qstrDeviceNumber;
             break;
         }
     }
     return;
 }

 void facePvms::stateChanged()
 {
    bSelected = true;
    QString strSelectedData("");
    strSelectedText.clear();
    m_deviceStrIds.clear();
    int nCount = pListWidget->count();
    for (int i = 0; i < nCount; ++i)
    {
         QListWidgetItem *pItem = pListWidget->item(i);
         QWidget *pWidget = pListWidget->itemWidget(pItem);
         QCheckBox *pCheckBox = (QCheckBox *)pWidget;
         if (pCheckBox->isChecked() )
         {
             QString strText = pCheckBox->text();
             qDebug()<<"strText:"<<strText;
             QString qstrDeviceNumber;
             GetDeviceNumberFromConifgFile(strText, qstrDeviceNumber); //search from config file
             if(qstrDeviceNumber.isEmpty())
                m_deviceStrIds.push_back(strText);
             else
                m_deviceStrIds.push_back(qstrDeviceNumber);
             strSelectedData.append(strText).append(";"); //add selected text into line
         }
     }
     if (strSelectedData.endsWith(";")) {
         strSelectedData.remove(strSelectedData.count() - 1, 1);
     }

     //set or clear line edit content
     if (!strSelectedData.isEmpty())
     {
         strSelectedText = strSelectedData;
         pLineEdit->setText(strSelectedData);
         pLineEdit->setToolTip(strSelectedData);
     }
     else
     {
         pLineEdit->clear();
     }
     bSelected = false;
 }

 void facePvms::textChanged()
 {
    if (!bSelected)
         pLineEdit->setText(strSelectedText);
 }

 void facePvms::SetCalendarSelectDays()
 {
     bool ok = false;
     QString storageDays= "-" + m_storageInfo.qstrExpireDays;
     int storageValue = storageDays.toInt(&ok,10);
     //set calendar date
     QDate  Curtoday = QDate::currentDate();//get current date
     m_defStartDTE->setDateRange(Curtoday.addDays(storageValue),Curtoday.addDays(0));
     m_defEndDTE->setDateRange(Curtoday.addDays(storageValue),Curtoday.addDays(0));
 }

void facePvms::readFrame()
{
    QString qstrCurDevNum = QString("%1").arg(HkvsHandles.size());
    ui->label_curdevice->setText(qstrCurDevNum);
    if( HkvsHandles.size() == 0 ) {
        ui->label_DisplayCam->clear();
        return ;
    }

    //restricted use days
    QDateTime datetime =  QDateTime::currentDateTime();
    QString qstrCurDate = datetime.toString("yyyy-MM-dd");
    QString qstrCurDateTime = datetime.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_systime_show->setText(qstrCurDateTime);
    if(qstrCurDate.compare(SET_SOFTWARE_DUE_DATE) >= 0)
    {
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("软件已经过期!") );
#else
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("The software is expired!"));
#endif
         return;
    }

    SetCalendarSelectDays();

    std::vector<HkvsHandle>::iterator itor;
    for(itor = HkvsHandles.begin(); itor != HkvsHandles.end(); itor++)
    {
        if(-1 == (*itor).deviceid || !((*itor).bState) )  break;
        // m_pFaceRec->HKVS_CapturePic(*itor, m_storageInfo.qstrImagePath, (QWidget*)ui->label_DisplayCam);
        // m_pFaceRec->HKVS_CapturePic(*itor, m_storageInfo.qstrImagePath, matImage);
         m_pFaceRec->HKVS_CapturePic(*itor, m_storageInfo.qstrImagePath, m_qstrDeviceNum);
    }
}

///<summary> Action startwidget that reviced set finished signal</summary>
void facePvms::setStartDateTime(const QDateTime &dateTime)
{
    //set start time less than end time
    m_defStartDTE->setMaximumDateTime(m_defEndDTE->dateTime());
    m_defStartDTE->setDateTime(dateTime);
}

///<summary> Action endwidget that reviced set finished signal</summary>
void facePvms::setEndDateTime(const QDateTime &dateTime)
{
    m_defEndDTE->setMaximumDateTime(dateTime.addSecs(0));
    m_defEndDTE->setDateTime(dateTime);
    qDebug()<<"setEndDateTime";
}

///<summary> Write item info into config file </summary>
bool facePvms::WriteConfigInfo(QString path, LoginInfo saveInfo)
{
    if(path.isEmpty() || saveInfo.strDeviceNum.isEmpty())
    {
        return false;
    }
    QSettings* config = new QSettings(path,QSettings::IniFormat);
    config->beginGroup(saveInfo.strDeviceNum);
    config->setValue("intervalSec",saveInfo.strIntervalSec);
    config->setValue("usrAccount",saveInfo.strUsrName);
    config->setValue("password",saveInfo.strPassword);
    config->setValue("deviceIpAddr",saveInfo.strIpaddr);
    config->setValue("devicePort",saveInfo.strPort);
    config->setValue("deviceName",saveInfo.strDeviceName);
    config->endArray();
    delete config;
    config = mpNULL;
    return true;
}

///<summary> Write line info into config file </summary>
bool facePvms::WriteConfigLine(QString path, QString group, QString key, QString value)
{
    if(key.isEmpty() || value.isEmpty())
    {
        return false;
    }
    QSettings* config = new QSettings(path,QSettings::IniFormat);
    config->beginGroup(group);
    config->setValue(key,value);
    config->endArray();
    delete config;
    config = mpNULL;
    return true;
}

///<summary> Read value with save in config file </summary>
bool facePvms::ReadConfigLineInfo(QString path,QString key, QString& value)
{
    if( path.isEmpty() || key.isEmpty())
    {
        return false;
    }
    QSettings* config = new QSettings(path,QSettings::IniFormat);
    value = config->value(key).toString();
    if(mpNULL != config) {
        delete config;
        config = mpNULL;
    }
    if(value.isEmpty())
        return false;
    else
        return true;
}

///<summary> Read ithem with save in config file </summary>
bool facePvms::ReadConfigItemInfo(QString path, LoginInfo& configInfo)
{
    if(path.isEmpty() || configInfo.strDeviceNum.isEmpty())
    {
        return false;
    }
    QSettings* config = new QSettings(path,QSettings::IniFormat);
    configInfo.strIntervalSec = config->value(configInfo.strDeviceNum + QString("/intervalSec")).toString();
    configInfo.strUsrName = config->value(configInfo.strDeviceNum + QString( "/usrAccount")).toString();
    configInfo.strPassword = config->value(configInfo.strDeviceNum + QString( "/password")).toString();
    configInfo.strIpaddr = config->value(configInfo.strDeviceNum + QString("/deviceIpAddr")).toString();
    configInfo.strPort = config->value(configInfo.strDeviceNum + QString("/devicePort")).toString();
    configInfo.strDeviceName = config->value(configInfo.strDeviceNum + QString("/deviceName")).toString();
    if(mpNULL != config) {
        delete config;
        config = mpNULL;
    }
    return true;
}

void facePvms::SetConfigFilePath()
{
    m_qstrCurPath = QApplication::applicationDirPath();
    if(m_qstrCurPath.isEmpty()) return;
    qDebug()<<"Current path:"<<m_qstrCurPath;

    if(access((m_qstrCurPath + CONFIG_DIR).toStdString().c_str(), R_OK) != 0)
    {
        qDebug() <<"Can't found the folder!Waiting to create...";
        const mpCHAR * configDir = (m_qstrCurPath + CONFIG_DIR).toStdString().c_str();
        mpINT ok= mkdir(configDir);
        if(ok != 0) return;
    }
    m_qstrCurConfigFilePath = (m_qstrCurPath + CONFIG_DIR + "config.ini").toStdString().c_str();
}

void facePvms::FindTargetFaceImage(QString qstrFindPath, QString qstrFindImageName)
{
    if(qstrFindPath.isEmpty() || qstrFindImageName.isEmpty() ) {
        qDebug() << "The current path or image name can not be empty!";
        return;
    }

    QDir targetDir(qstrFindPath);
    if(targetDir.exists() ) {
         QStringList filters;
         filters<<QString("*.jpg");
         targetDir.setFilter(QDir::Files | QDir::NoSymLinks); //set filter format
         targetDir.setNameFilters(filters);  //add filters（.jpg）
    } else{
        return;
    }

    QFileInfoList list = targetDir.entryInfoList();
    for(int nIndex = 0; nIndex<list.count(); nIndex++)
    {
        QFileInfo tempInfo = list.at(nIndex);
        if(tempInfo.isFile() == false) {
            qDebug()<<"It's not a file";
            continue;
        }

        if(qstrFindImageName.compare(tempInfo.fileName()) == 0)
        {
            QString imagePath= qstrFindPath + qstrFindImageName;
            cv::Mat matImage = cv::imread(imagePath.toStdString(), 1);
            if (matImage.empty()) {
                qDebug()<<"Read image error";
                return;
            }
            QImage qImage=QImage((const uchar*)matImage.data,matImage.cols,matImage.rows,QImage::Format_RGB888).rgbSwapped();
            QPixmap objPixmap=QPixmap::fromImage(qImage);
            QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(W_ICONSIZE,H_ICONSIZE))),imagePath);
            pItem->setSizeHint(QSize(W_ICONSIZE,H_ITEMSIZE));
            m_pListWidget->insertItem(nIndex, pItem);
        }
    }
}

bool facePvms::deleteAppointDir(const QString &dirPath)
{
    QDir directory(dirPath);
     if (!directory.exists())
     {
         return true;
     }

     QString srcPath = QDir::toNativeSeparators(dirPath);
     if (!srcPath.endsWith(QDir::separator()))
         srcPath += QDir::separator();

     QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
     bool error = false;
     for (QStringList::size_type i=0; i != fileNames.size(); ++i)
     {
         QString filePath = srcPath + fileNames.at(i);
         QFileInfo fileInfo(filePath);
         if (fileInfo.isFile() || fileInfo.isSymLink())
         {
             QFile::setPermissions(filePath, QFile::WriteOwner);
             if (!QFile::remove(filePath))
             {
                 qDebug() << "remove file" << filePath << " faild!";
                 error = true;
             }
         }
         else if (fileInfo.isDir())
         {
             if (!deleteAppointDir(filePath))
             {
                 error = true;
             }
         }
    }

    if( !directory.rmdir(directory.path()) )
    {
         qDebug() << "remove dir" << directory.absolutePath() << " faild!";
         error = true;
    }

    return !error;
}


bool facePvms::checkIPWhetherInVector(QString qstrDeviceIp)
{
    mpBOOL bRet = mpFALSE;
    if(HkvsHandles.empty()) return bRet;
    std::vector<HkvsHandle>::iterator itor;
    for(itor = HkvsHandles.begin(); itor != HkvsHandles.end(); itor++)
    {
        if( 0 == qstrDeviceIp.compare((*itor).qstrIpAddr) ) {
            bRet = mpTRUE;
            break;
        }
    }
    return bRet;
}

void facePvms::closeAllDeviceid()
{
    std::vector<HkvsHandle>::iterator itor;
    for(itor = HkvsHandles.begin(); itor != HkvsHandles.end(); itor++)
    {
         if( (*itor).bState ) {
             m_pFaceRec->HKVS_PlayStop((*itor).lRealHandle);
             (*itor).initialize();
         }
    }
}

bool facePvms::closeDeviceWithNumber( QString qstrDevNum)
{
   mpBOOL bRet = mpFALSE;
   if(qstrDevNum.isEmpty()) return bRet;
   std::vector<HkvsHandle>::iterator itor;
   for(itor = HkvsHandles.begin(); itor != HkvsHandles.end(); itor++)
   {
       if( 0 == qstrDevNum.compare((*itor).qstrDevNum) )
       {
            m_qstrDeviceNum = (*HkvsHandles.begin()).qstrDevNum;
            m_pFaceRec->HKVS_PlayStop((*itor).lRealHandle);
            (*itor).initialize();//set state false
            HkvsHandles.erase(itor);
            bRet = mpTRUE;
            break;
       }
   }

   return bRet;
}

void facePvms::GetSelectedQStringDateTime(DefDateTimeEdit* dateTimeEdit, QString& qstrSelectedDateTime)
{
    QString strYear, strMonth, strDay, strHour, strMinute, strSecond;

    dateTimeEdit->getSectionTextDateTime(strYear,strMonth,strDay,strHour,strMinute,strSecond);
    QString qstrSelectedDate = strYear +"-" + strMonth + "-" + strDay;
    qstrSelectedDateTime = qstrSelectedDate + " " +strHour + ":" + strMinute + ":" + strSecond;
}

void facePvms::on_pushButton_search_clicked()
{
    QString selecteStartdDateTime, selectedEndDateTime;
    GetSelectedQStringDateTime(m_defStartDTE, selecteStartdDateTime);
    GetSelectedQStringDateTime(m_defEndDTE, selectedEndDateTime);
    if(selecteStartdDateTime.isEmpty() || selectedEndDateTime.isEmpty())
    {
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("开始或结束时间不能为空!") );
#else
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("start time or end time can not be empty!"));
#endif
        return;
    }
    m_pListWidget->clear();
    vector<SearchResult> searchResultItems;
    qDebug()<<"m_deviceStrIds size:"<< m_deviceStrIds.size();//search items
    for(int i=0; i< m_deviceStrIds.size(); i++)
    {
        searchResultItems.clear();
        face_database_api::GetInstance()->face_database_select_singlegroup_facetable(selecteStartdDateTime, selectedEndDateTime, m_deviceStrIds[i], searchResultItems);
        qDebug() <<m_deviceStrIds[i]<<" item number: "<<searchResultItems.size();
        for(int i=0; i<searchResultItems.size(); i++)
        {
            CheckDeleteExpiredDirectory(searchResultItems[i].qstrDirName,searchResultItems[i].qstrFilePath);
            FindTargetFaceImage(searchResultItems[i].qstrFilePath, searchResultItems[i].qstrFileName);
        }
    }
    return;
}

void facePvms::DeleteExpiredRecordFromDataBase(QString qstrBeforeDate)
{
    //delete record from data base
    face_database_api::GetInstance()->face_database_delete_all_facetable(qstrBeforeDate);
}

void facePvms::CheckDeleteExpiredDirectory(QString qstrDirName,QString qstrDirPath)
{
    if(qstrDirName.isEmpty() || qstrDirPath.isEmpty()){
        qDebug()<<"qstrDirName or qstrDirPath can not be empty!";
        return;
    }
    bool ok = false;
    QString storageDays= "-" + m_storageInfo.qstrExpireDays;
    int storageValue = storageDays.toInt(&ok,10);
    QDateTime currentDatetime =  QDateTime::currentDateTime();
    QString qstrBeforeDate = currentDatetime.addDays(storageValue).toString("yyyy-MM-dd");
    //qDebug()<<"qstrBeforeDate: "<<qstrBeforeDate <<"qstrDirName: "<<qstrDirName;
    //QDateTime datetime =  QDateTime::currentDateTime();
    //QString qstrCurDate = datetime.toString("yyyy-MM-dd");
    //if(qstrCurDate.compare(qstrBeforeDate) < 0) return;
    if(qstrDirName.compare(qstrBeforeDate) <= 0) {
        if(deleteAppointDir(qstrDirPath) ) {
            DeleteExpiredRecordFromDataBase(qstrDirName);//delete record from db
        }
    }
}

void facePvms::on_pushButton_save_clicked()
{
    LoginInfo loginInfo;
    loginInfo.initLoginInfo();
    loginInfo.strDeviceNum.append("device");
    loginInfo.strDeviceNum += ui->spinBox_deviceNumber->text();
    loginInfo.strIntervalSec = ui->spinBox_intervalSec->text();
    loginInfo.strUsrName = ui->lineEdit_account->text();
    loginInfo.strPassword = ui->lineEdit_password->text();
    loginInfo.strIpaddr = ui->lineEdit_ipaddr->text();
    loginInfo.strPort = ui->lineEdit_port->text();
    loginInfo.strDeviceName = ui->lineEdit_devicename->text();
    qDebug()<<loginInfo.strDeviceNum;

    if( m_qstrCurPath.isEmpty() ) return;
    mpBOOL bRet = WriteConfigInfo(m_qstrCurConfigFilePath, loginInfo);
    if(mpTRUE != bRet) {
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("保存失败!") );
#else
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("Save fault!"));
#endif
    } else {
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("保存成功!") );
#else
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("Save success!"));
#endif
        InitDeviceSelectedBox();
    }
    ui->groupBox_configArea->hide();
}

void facePvms::on_pushbutton_device_config_clicked()
{
    if( m_qstrCurConfigFilePath.isEmpty() ) return;
    LoginInfo configInfo;
    configInfo.initLoginInfo();
    configInfo.strDeviceNum.append("device");
    configInfo.strDeviceNum += ui->spinBox_deviceNumber->text();
    mpBOOL bRet = ReadConfigItemInfo(m_qstrCurConfigFilePath, configInfo);
    if(mpTRUE == bRet)
    {
        mpBOOL ok = mpFALSE;
        ui->spinBox_intervalSec->setValue(configInfo.strIntervalSec.toInt(&ok,10));
        ui->lineEdit_account->setText(configInfo.strUsrName);
        ui->lineEdit_password->setText(configInfo.strPassword);
        ui->lineEdit_ipaddr->setText(configInfo.strIpaddr);
        ui->lineEdit_port->setText(configInfo.strPort);
        ui->lineEdit_devicename->setText(configInfo.strDeviceName);
    }
    ui->groupBox_configArea->show();
}

void facePvms::on_pushbutton_device_open_clicked()
{
    m_pTimer->stop();
    do{
        ui->label_DisplayCam->clear();
        qDebug() <<"open button has been clicked!";
        if( m_qstrCurConfigFilePath.isEmpty() ) break;
        LoginInfo configInfo;
        configInfo.initLoginInfo();
        configInfo.strDeviceNum.append("device");
        configInfo.strDeviceNum += ui->spinBox_deviceNumber->text();
        m_qstrDeviceNum = configInfo.strDeviceNum;
        mpBOOL bReadRet = ReadConfigItemInfo(m_qstrCurConfigFilePath, configInfo);
        if(!bReadRet) break;

        if(configInfo.strIpaddr.isEmpty() || configInfo.strPort.isEmpty())
        {
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("设备IP或端口不能为空!") );
#else
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("device ip or port can not be empty!"));
#endif
            break;
        }
        if(configInfo.strUsrName.isEmpty() || configInfo.strPassword.isEmpty())
        {
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("用户名或密码不能为空!") );
#else
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("usr name or password can not be empty!"));
#endif

            break;
        }
        mpBOOL bCheckRet = checkIPWhetherInVector(configInfo.strIpaddr);
        if(bCheckRet) {
            //QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("Already opened the device!"));
            break;
        }

        qDebug()<<configInfo.strIpaddr<<configInfo.strPort<<configInfo.strUsrName<<configInfo.strPassword;
        //convert type from QString to char*
        bool ok = false;
        short port = configInfo.strPort.toShort(&ok,10);
        int iDeplyTime = configInfo.strIntervalSec.toInt(&ok,10);
        QByteArray qbIpAddr = configInfo.strIpaddr.toLatin1();
        QByteArray qbUsrName = configInfo.strUsrName.toLatin1();
        QByteArray qbPassword = configInfo.strPassword.toLatin1();

        char* pIpAddr =  qbIpAddr.data();
        char* pUsrName = qbUsrName.data();
        char* pPassword = qbPassword.data();

        //init camera
        long deviceid = m_pFaceRec->InitHKVSCamera(pIpAddr,port,pUsrName,pPassword);
        if( -1 == deviceid )
        {
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("初始化失败，请检查你的网络或配置参数!") );
#else
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("Init fault,please check your network or configured param!"));
#endif
         break;
        }

        HkvsHandle handleInfo;
        handleInfo.initialize();
        handleInfo.dueTime = iDeplyTime;
        handleInfo.deviceid = deviceid;
        handleInfo.qstrDevNum = configInfo.strDeviceNum;
        handleInfo.qstrIpAddr = configInfo.strIpaddr;
        handleInfo.bState = mpTRUE;
        HkvsHandles.push_back(handleInfo);
        qDebug()<<"push the date";
    }while(mpFALSE);
    m_pTimer->start(10);
}

void facePvms::on_pushButton_device_close_clicked()
{
    qDebug() <<"close button has been clicked!";
    QString qstrDevNum = "device" + ui->spinBox_deviceNumber->text();

    mpBOOL bRet = closeDeviceWithNumber(qstrDevNum);
    if(bRet)
    {
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("关闭成功!") );
#else
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("Device close sucessful!"));
#endif
    } else{
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("设备已关闭或未打开!") );
#else
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("Device Already closed or Not opened!"));
#endif
    }
    qDebug() << qstrDevNum;
    ui->groupBox_configArea->hide();
}

void facePvms::on_pushButton_pathSelect_clicked()
{
    m_pTimer->stop();
    QString qstrFilePath = QFileDialog::getExistingDirectory(this,tr("Open Directory"),"/home", QFileDialog::ShowDirsOnly |QFileDialog::DontResolveSymlinks);
    ui->lineEdit_imagePath->setText(qstrFilePath);
    m_pTimer->start(10);
}

///write into config file
void facePvms::on_pushButton_storageConfirm_clicked()
{
    QString imagePath = ui->lineEdit_imagePath->text();
    if( imagePath.isEmpty() )
    {
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("路径不能为空!") );
#else
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("Path Can not be empty!") );
#endif
        return;
    }

    //check last character whether '/'
    if(imagePath[imagePath.size()-1] != '/')
    {
        imagePath = imagePath + "/";
    }

    WriteConfigLine(m_qstrCurConfigFilePath, FACE_STORAGE_GROUP_NAME, "imagePath", imagePath );
    m_storageInfo.qstrImagePath = imagePath;
    qDebug()<< m_storageInfo.qstrImagePath;

    QString qstrExpireDays = ui->spinBox_storagedate->text();
    m_storageInfo.qstrExpireDays = qstrExpireDays;
    WriteConfigLine(m_qstrCurConfigFilePath, FACE_STORAGE_GROUP_NAME, "expireDays",qstrExpireDays);
#ifdef  SET_SYSTEM_LANGUAGE_CHINESE
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING_CHINSE),tr("保存成功!") );
#else
      QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("Save successful!") );
#endif
}
