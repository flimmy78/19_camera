#ifndef DEFDATETIMEEDIT_H
#define DEFDATETIMEEDIT_H

#include <QDateTimeEdit>
#include "DefineCalendar.h"
#include "QDebug"

class DefDateTimeEdit : public QDateTimeEdit
{
	Q_OBJECT

public:
	DefDateTimeEdit(QWidget *parent);
	~DefDateTimeEdit();
    void getSectionTextDateTime(QString& year, QString&month, \
                                QString& day, QString& hour, QString& minute,QString& second);

signals:
    void setFinished(const QDateTime &dateTime);

public slots:
    void setStartDateTime(const QDateTime &dateTime);

protected slots:
	void getDateTime(const QDateTime &dateTime);

private:
    void setMyStytle();
	DefineCalendar *m_DefCalendar;
};

#endif // DEFDATETIMEEDIT_H
