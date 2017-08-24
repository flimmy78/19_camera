/********************************************************************************
** Form generated from reading UI file 'facepvms.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEPVMS_H
#define UI_FACEPVMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_facePvms
{
public:
    QLabel *company_label;
    QTabWidget *tabelWidget_operation;
    QWidget *operation;
    QLabel *label_devname;
    QSpinBox *spinBox_deviceNumber;
    QPushButton *pushbutton_device_config;
    QGroupBox *groupBox_configArea;
    QLabel *label_ipaddr;
    QTextEdit *textEdit_ipaddr;
    QLabel *label_interval;
    QLabel *label_sec;
    QLabel *label_usr;
    QTextEdit *textEdit_account;
    QLabel *label_password;
    QTextEdit *textEdit_port;
    QLabel *label_port;
    QTextEdit *textEdit_password;
    QSpinBox *spinBox_intervalSec;
    QPushButton *pushButton_save;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_deviceOpera;
    QPushButton *pushbutton_device_open;
    QPushButton *pushButton_device_close;
    QWidget *inquery;
    QComboBox *comboBox;
    QLabel *label_deviceName;
    QLabel *label_starttime;
    QLabel *label_endTime;
    QPushButton *pushButton_search;
    QWidget *widget_startCanlendar;
    QWidget *widget_endCanlendar;
    QWidget *tab;
    QLabel *label_imageName;
    QLineEdit *lineEdit_imagePath;
    QPushButton *pushButton_pathSelect;
    QLabel *label_storageDateName;
    QSpinBox *spinBox_storagedate;
    QLabel *label_day;
    QPushButton *pushButton_storageConfirm;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_leftLayout;
    QTabWidget *tabWidget_result;
    QWidget *tab_display;
    QLabel *label_DisplayCam;
    QWidget *tab_searchResult;
    QListWidget *listWidget_imagelist;

    void setupUi(QWidget *facePvms)
    {
        if (facePvms->objectName().isEmpty())
            facePvms->setObjectName(QStringLiteral("facePvms"));
        facePvms->resize(865, 605);
        company_label = new QLabel(facePvms);
        company_label->setObjectName(QStringLiteral("company_label"));
        company_label->setGeometry(QRect(210, 20, 441, 41));
        company_label->setStyleSheet(QString::fromUtf8("\344\272\272\350\204\270\350\257\206\345\210\253\345\210\206\346\236\220\350\275\257\344\273\266face-pvms\n"
"font: 9pt \"\346\245\267\344\275\223\";\n"
"font: 24pt \"Agency FB\";"));
        tabelWidget_operation = new QTabWidget(facePvms);
        tabelWidget_operation->setObjectName(QStringLiteral("tabelWidget_operation"));
        tabelWidget_operation->setGeometry(QRect(660, 90, 201, 481));
        tabelWidget_operation->setIconSize(QSize(16, 16));
        operation = new QWidget();
        operation->setObjectName(QStringLiteral("operation"));
        label_devname = new QLabel(operation);
        label_devname->setObjectName(QStringLiteral("label_devname"));
        label_devname->setGeometry(QRect(0, 20, 61, 21));
        spinBox_deviceNumber = new QSpinBox(operation);
        spinBox_deviceNumber->setObjectName(QStringLiteral("spinBox_deviceNumber"));
        spinBox_deviceNumber->setGeometry(QRect(70, 20, 41, 22));
        pushbutton_device_config = new QPushButton(operation);
        pushbutton_device_config->setObjectName(QStringLiteral("pushbutton_device_config"));
        pushbutton_device_config->setGeometry(QRect(120, 20, 61, 23));
        groupBox_configArea = new QGroupBox(operation);
        groupBox_configArea->setObjectName(QStringLiteral("groupBox_configArea"));
        groupBox_configArea->setGeometry(QRect(0, 110, 181, 341));
        label_ipaddr = new QLabel(groupBox_configArea);
        label_ipaddr->setObjectName(QStringLiteral("label_ipaddr"));
        label_ipaddr->setGeometry(QRect(10, 150, 41, 21));
        textEdit_ipaddr = new QTextEdit(groupBox_configArea);
        textEdit_ipaddr->setObjectName(QStringLiteral("textEdit_ipaddr"));
        textEdit_ipaddr->setGeometry(QRect(60, 150, 100, 30));
        label_interval = new QLabel(groupBox_configArea);
        label_interval->setObjectName(QStringLiteral("label_interval"));
        label_interval->setGeometry(QRect(10, 30, 54, 21));
        label_sec = new QLabel(groupBox_configArea);
        label_sec->setObjectName(QStringLiteral("label_sec"));
        label_sec->setGeometry(QRect(110, 30, 21, 20));
        label_usr = new QLabel(groupBox_configArea);
        label_usr->setObjectName(QStringLiteral("label_usr"));
        label_usr->setGeometry(QRect(10, 60, 41, 31));
        textEdit_account = new QTextEdit(groupBox_configArea);
        textEdit_account->setObjectName(QStringLiteral("textEdit_account"));
        textEdit_account->setGeometry(QRect(60, 60, 100, 30));
        label_password = new QLabel(groupBox_configArea);
        label_password->setObjectName(QStringLiteral("label_password"));
        label_password->setGeometry(QRect(10, 100, 41, 31));
        textEdit_port = new QTextEdit(groupBox_configArea);
        textEdit_port->setObjectName(QStringLiteral("textEdit_port"));
        textEdit_port->setGeometry(QRect(60, 190, 100, 30));
        label_port = new QLabel(groupBox_configArea);
        label_port->setObjectName(QStringLiteral("label_port"));
        label_port->setGeometry(QRect(10, 190, 41, 31));
        textEdit_password = new QTextEdit(groupBox_configArea);
        textEdit_password->setObjectName(QStringLiteral("textEdit_password"));
        textEdit_password->setGeometry(QRect(60, 100, 100, 30));
        textEdit_password->setLayoutDirection(Qt::LeftToRight);
        spinBox_intervalSec = new QSpinBox(groupBox_configArea);
        spinBox_intervalSec->setObjectName(QStringLiteral("spinBox_intervalSec"));
        spinBox_intervalSec->setGeometry(QRect(70, 30, 42, 22));
        pushButton_save = new QPushButton(groupBox_configArea);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(50, 250, 77, 23));
        layoutWidget = new QWidget(operation);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 70, 171, 31));
        horizontalLayout_deviceOpera = new QHBoxLayout(layoutWidget);
        horizontalLayout_deviceOpera->setSpacing(6);
        horizontalLayout_deviceOpera->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_deviceOpera->setObjectName(QStringLiteral("horizontalLayout_deviceOpera"));
        horizontalLayout_deviceOpera->setContentsMargins(0, 0, 0, 0);
        pushbutton_device_open = new QPushButton(layoutWidget);
        pushbutton_device_open->setObjectName(QStringLiteral("pushbutton_device_open"));

        horizontalLayout_deviceOpera->addWidget(pushbutton_device_open);

        pushButton_device_close = new QPushButton(layoutWidget);
        pushButton_device_close->setObjectName(QStringLiteral("pushButton_device_close"));

        horizontalLayout_deviceOpera->addWidget(pushButton_device_close);

        tabelWidget_operation->addTab(operation, QString());
        inquery = new QWidget();
        inquery->setObjectName(QStringLiteral("inquery"));
        comboBox = new QComboBox(inquery);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(70, 20, 91, 22));
        label_deviceName = new QLabel(inquery);
        label_deviceName->setObjectName(QStringLiteral("label_deviceName"));
        label_deviceName->setGeometry(QRect(20, 20, 41, 21));
        label_starttime = new QLabel(inquery);
        label_starttime->setObjectName(QStringLiteral("label_starttime"));
        label_starttime->setGeometry(QRect(10, 60, 54, 20));
        label_endTime = new QLabel(inquery);
        label_endTime->setObjectName(QStringLiteral("label_endTime"));
        label_endTime->setGeometry(QRect(10, 131, 54, 21));
        pushButton_search = new QPushButton(inquery);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));
        pushButton_search->setGeometry(QRect(50, 210, 75, 23));
        widget_startCanlendar = new QWidget(inquery);
        widget_startCanlendar->setObjectName(QStringLiteral("widget_startCanlendar"));
        widget_startCanlendar->setGeometry(QRect(10, 90, 181, 31));
        widget_endCanlendar = new QWidget(inquery);
        widget_endCanlendar->setObjectName(QStringLiteral("widget_endCanlendar"));
        widget_endCanlendar->setGeometry(QRect(10, 160, 181, 31));
        tabelWidget_operation->addTab(inquery, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_imageName = new QLabel(tab);
        label_imageName->setObjectName(QStringLiteral("label_imageName"));
        label_imageName->setGeometry(QRect(10, 50, 71, 31));
        lineEdit_imagePath = new QLineEdit(tab);
        lineEdit_imagePath->setObjectName(QStringLiteral("lineEdit_imagePath"));
        lineEdit_imagePath->setGeometry(QRect(10, 80, 161, 21));
        pushButton_pathSelect = new QPushButton(tab);
        pushButton_pathSelect->setObjectName(QStringLiteral("pushButton_pathSelect"));
        pushButton_pathSelect->setGeometry(QRect(40, 120, 75, 23));
        label_storageDateName = new QLabel(tab);
        label_storageDateName->setObjectName(QStringLiteral("label_storageDateName"));
        label_storageDateName->setGeometry(QRect(10, 180, 61, 41));
        spinBox_storagedate = new QSpinBox(tab);
        spinBox_storagedate->setObjectName(QStringLiteral("spinBox_storagedate"));
        spinBox_storagedate->setGeometry(QRect(70, 190, 42, 22));
        label_day = new QLabel(tab);
        label_day->setObjectName(QStringLiteral("label_day"));
        label_day->setGeometry(QRect(120, 190, 21, 21));
        pushButton_storageConfirm = new QPushButton(tab);
        pushButton_storageConfirm->setObjectName(QStringLiteral("pushButton_storageConfirm"));
        pushButton_storageConfirm->setGeometry(QRect(40, 240, 75, 23));
        tabelWidget_operation->addTab(tab, QString());
        gridLayoutWidget = new QWidget(facePvms);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 70, 651, 511));
        gridLayout_leftLayout = new QGridLayout(gridLayoutWidget);
        gridLayout_leftLayout->setSpacing(6);
        gridLayout_leftLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout_leftLayout->setObjectName(QStringLiteral("gridLayout_leftLayout"));
        gridLayout_leftLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget_result = new QTabWidget(gridLayoutWidget);
        tabWidget_result->setObjectName(QStringLiteral("tabWidget_result"));
        tab_display = new QWidget();
        tab_display->setObjectName(QStringLiteral("tab_display"));
        label_DisplayCam = new QLabel(tab_display);
        label_DisplayCam->setObjectName(QStringLiteral("label_DisplayCam"));
        label_DisplayCam->setGeometry(QRect(0, 0, 640, 480));
        tabWidget_result->addTab(tab_display, QString());
        tab_searchResult = new QWidget();
        tab_searchResult->setObjectName(QStringLiteral("tab_searchResult"));
        listWidget_imagelist = new QListWidget(tab_searchResult);
        listWidget_imagelist->setObjectName(QStringLiteral("listWidget_imagelist"));
        listWidget_imagelist->setGeometry(QRect(0, 0, 640, 480));
        tabWidget_result->addTab(tab_searchResult, QString());

        gridLayout_leftLayout->addWidget(tabWidget_result, 1, 0, 1, 1);

        QWidget::setTabOrder(spinBox_deviceNumber, pushbutton_device_config);
        QWidget::setTabOrder(pushbutton_device_config, pushbutton_device_open);
        QWidget::setTabOrder(pushbutton_device_open, pushButton_device_close);
        QWidget::setTabOrder(pushButton_device_close, spinBox_intervalSec);
        QWidget::setTabOrder(spinBox_intervalSec, textEdit_account);
        QWidget::setTabOrder(textEdit_account, textEdit_password);
        QWidget::setTabOrder(textEdit_password, textEdit_ipaddr);
        QWidget::setTabOrder(textEdit_ipaddr, textEdit_port);
        QWidget::setTabOrder(textEdit_port, pushButton_save);
        QWidget::setTabOrder(pushButton_save, tabelWidget_operation);
        QWidget::setTabOrder(tabelWidget_operation, comboBox);
        QWidget::setTabOrder(comboBox, pushButton_search);

        retranslateUi(facePvms);

        tabelWidget_operation->setCurrentIndex(0);
        tabWidget_result->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(facePvms);
    } // setupUi

    void retranslateUi(QWidget *facePvms)
    {
        facePvms->setWindowTitle(QApplication::translate("facePvms", "facePvms", 0));
        company_label->setText(QApplication::translate("facePvms", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">\344\272\272\350\204\270\350\257\206\345\210\253\345\210\206\346\236\220\350\275\257\344\273\266 face-pvms(\350\257\225\347\224\250\347\211\2100.01)</span></p></body></html>", 0));
        label_devname->setText(QApplication::translate("facePvms", " \350\256\276\345\244\207\345\272\217\345\217\267", 0));
        pushbutton_device_config->setText(QApplication::translate("facePvms", "\351\205\215\347\275\256", 0));
        groupBox_configArea->setTitle(QApplication::translate("facePvms", "\351\205\215\347\275\256\345\214\272\345\237\237", 0));
        label_ipaddr->setText(QApplication::translate("facePvms", "\350\256\276\347\275\256IP\357\274\232", 0));
        label_interval->setText(QApplication::translate("facePvms", "\346\217\220\345\217\226\351\227\264\351\232\224", 0));
        label_sec->setText(QApplication::translate("facePvms", " \347\247\222", 0));
        label_usr->setText(QApplication::translate("facePvms", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        label_password->setText(QApplication::translate("facePvms", "\345\257\206\347\240\201\357\274\232", 0));
        label_port->setText(QApplication::translate("facePvms", "\347\253\257\345\217\243\345\217\267\357\274\232", 0));
        pushButton_save->setText(QApplication::translate("facePvms", " \347\241\256\350\256\244", 0));
        pushbutton_device_open->setText(QApplication::translate("facePvms", "\346\211\223\345\274\200\350\256\276\345\244\207", 0));
        pushButton_device_close->setText(QApplication::translate("facePvms", "\345\205\263\351\227\255\350\256\276\345\244\207", 0));
        tabelWidget_operation->setTabText(tabelWidget_operation->indexOf(operation), QApplication::translate("facePvms", "\346\223\215\344\275\234", 0));
        label_deviceName->setText(QApplication::translate("facePvms", "\350\256\276\345\244\207\345\217\267", 0));
        label_starttime->setText(QApplication::translate("facePvms", "\345\274\200\345\247\213\346\227\266\351\227\264", 0));
        label_endTime->setText(QApplication::translate("facePvms", "\347\273\223\346\235\237\346\227\266\351\227\264", 0));
        pushButton_search->setText(QApplication::translate("facePvms", "\346\237\245\350\257\242", 0));
        tabelWidget_operation->setTabText(tabelWidget_operation->indexOf(inquery), QApplication::translate("facePvms", "\346\237\245\350\257\242", 0));
        label_imageName->setText(QApplication::translate("facePvms", "\345\255\230\345\202\250\350\267\257\345\276\204\357\274\232", 0));
        pushButton_pathSelect->setText(QApplication::translate("facePvms", "\351\200\211\346\213\251", 0));
        label_storageDateName->setText(QApplication::translate("facePvms", "\345\255\230\345\202\250\346\227\266\351\227\264:", 0));
        label_day->setText(QApplication::translate("facePvms", "\345\244\251", 0));
        pushButton_storageConfirm->setText(QApplication::translate("facePvms", "\347\241\256\350\256\244", 0));
        tabelWidget_operation->setTabText(tabelWidget_operation->indexOf(tab), QApplication::translate("facePvms", "\345\255\230\345\202\250", 0));
        label_DisplayCam->setText(QApplication::translate("facePvms", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600;\">\346\230\276\347\244\272\345\214\272\345\237\237</span></p></body></html>", 0));
        tabWidget_result->setTabText(tabWidget_result->indexOf(tab_display), QApplication::translate("facePvms", "\346\221\204\345\203\217\345\244\264\346\230\276\347\244\272", 0));
        tabWidget_result->setTabText(tabWidget_result->indexOf(tab_searchResult), QApplication::translate("facePvms", "\346\237\245\350\257\242\347\273\223\346\236\234", 0));
    } // retranslateUi

};

namespace Ui {
    class facePvms: public Ui_facePvms {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEPVMS_H
