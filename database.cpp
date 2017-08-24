#include "database.h"

face_database_api::face_database_api(void)
{
    face_database_init();
}

face_database_api::~face_database_api()
{
    face_database_shutdown();
}

void face_database_api::face_database_init(void)
{
    qDebug()<<"face_database_init()";
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(SQLITE_DB_NAME);
    if( !database.open() )  {
        qDebug()<<"open database failed --"<<database.lastError()<<"\n";
        return;
    }

    QSqlQuery query(database);
    QString ceate_sql = SQLITE_CREATE_TABLE_SQL;
    query.prepare(ceate_sql);
    if(!query.exec()) {
        qDebug()<<"create table failed!";
        qDebug()<<query.lastError()<<"\n";
        return;
    }
}

void face_database_api::face_database_insert_facetable(QString qstrDevnum,  QString qstrDate, QString qstrStoragePath, \
                                                       QString qstrDateTime,  QString qstrImageName)
{
    if(qstrDevnum.isEmpty() || qstrDate.isEmpty() ||qstrStoragePath.isEmpty() || qstrDateTime.isEmpty() || qstrImageName.isEmpty()) {
        qDebug()<<"qstrDevnum , qstrDate , qstrDateTime or qstrImageName can not be empty!";
        return;
    }

    QSqlQuery query(database);
    query.prepare(SQLITE_INSERT_TABLE_SQL);
    query.addBindValue(qstrDevnum);
    query.addBindValue(qstrDate);
    query.addBindValue(qstrStoragePath);
    query.addBindValue(qstrDateTime);
    query.addBindValue(qstrImageName);
    if(query.exec())
        qDebug()<<"insert table success!";
    else
        qDebug()<<"insert table failed!";
}

void face_database_api::face_database_select_singlegroup_facetable(QString qstrStartTime,\
                        QString qstrEndTime, QString qstrDevnum,  vector<SearchResult>& searchResultItems)
{
    if(qstrStartTime.isEmpty() || qstrEndTime.isEmpty() || qstrDevnum.isEmpty()) {
        qDebug()<<"qstrStartTime or qstrEndTime and qstrDevnum can not be empty!";
        return;
    }
    qDebug()<<qstrStartTime << qstrEndTime << qstrDevnum;
    QSqlQuery query(database);
    query.prepare(SQLITE_SELECT_SINGLEGROUP_TABLE_SQL);
    query.addBindValue(qstrStartTime);
    query.addBindValue(qstrEndTime);
    query.addBindValue(qstrDevnum);
    if(!query.exec()) {
        qDebug()<<"select table failed!";
        qDebug()<<query.lastError()<<"\n";
        return;
    }

    while(query.next())
    {
        SearchResult searchResult;
        searchResult.qstrFilePath= query.value("imagepath").toString();
        searchResult.qstrFileName = query.value("imagename").toString();
        searchResult.qstrDirName = query.value("imagedate").toString();
        searchResultItems.push_back(searchResult);
    }
}

void face_database_api::face_database_delete_all_facetable(QString qstrDetDate)
{
    if(qstrDetDate.isEmpty()) {
        qDebug()<<"qstrDetDate can not be empty!";
        return;
    }

    QSqlQuery query(database);
    query.prepare(SQLITE_DELETE_TABLE_SQL);
    query.addBindValue(qstrDetDate);
    if(!query.exec()){
        qDebug()<<"delete table failed!";
        qDebug()<<query.lastError()<<"\n";
        return;
    }

    while(query.next())
    {
        qDebug()<<"delete";
    }
}

void face_database_api::face_database_shutdown(void)
{
    database.close();
}
