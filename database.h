#ifndef DATABASE_H
#define DATABASE_H

#include "global.h"
#include "sqlite3.h"
#include "TSingleIns.h"

/*
** CAPI3REF: Result Codes
** KEYWORDS: SQLITE_OK {error code} {error codes}
** KEYWORDS: {result code} {result codes}
**
** Many SQLite functions return an integer result code from the set shown
** here in order to indicates success or failure.
**
** New error codes may be added in future versions of SQLite.
**
** See also: [SQLITE_IOERR_READ | extended result codes]
*/
#define SQLITE_OK           0   /* Successful result */
/* beginning-of-error-codes */
#define SQLITE_ERROR        1   /* SQL error or missing database */
#define SQLITE_INTERNAL     2   /* Internal logic error in SQLite */
#define SQLITE_PERM         3   /* Access permission denied */
#define SQLITE_ABORT        4   /* Callback routine requested an abort */
#define SQLITE_BUSY         5   /* The database file is locked */
#define SQLITE_LOCKED       6   /* A table in the database is locked */
#define SQLITE_NOMEM        7   /* A malloc() failed */
#define SQLITE_READONLY     8   /* Attempt to write a readonly database */
#define SQLITE_INTERRUPT    9   /* Operation terminated by sqlite3_interrupt()*/
#define SQLITE_IOERR       10   /* Some kind of disk I/O error occurred */
#define SQLITE_CORRUPT     11   /* The database disk image is malformed */
#define SQLITE_NOTFOUND    12   /* NOT USED. Table or record not found */
#define SQLITE_FULL        13   /* Insertion failed because database is full */
#define SQLITE_CANTOPEN    14   /* Unable to open the database file */
#define SQLITE_PROTOCOL    15   /* NOT USED. Database lock protocol error */
#define SQLITE_EMPTY       16   /* Database is empty */
#define SQLITE_SCHEMA      17   /* The database schema changed */
#define SQLITE_TOOBIG      18   /* String or BLOB exceeds size limit */
#define SQLITE_CONSTRAINT  19   /* Abort due to constraint violation */
#define SQLITE_MISMATCH    20   /* Data type mismatch */
#define SQLITE_MISUSE      21   /* Library used incorrectly */
#define SQLITE_NOLFS       22   /* Uses OS features not supported on host */
#define SQLITE_AUTH        23   /* Authorization denied */
#define SQLITE_FORMAT      24   /* Auxiliary database format error */
#define SQLITE_RANGE       25   /* 2nd parameter to sqlite3_bind out of range */
#define SQLITE_NOTADB      26   /* File opened that is not a database file */
#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */
#define SQLITE_DONE        101  /* sqlite3_step() has finished executing */

#define SQLITE_DB_NAME          "facePvms.db"
#define SQLITE_CREATE_TABLE_SQL "CREATE TABLE IF NOT EXISTS faceTable" \
                                "(devicenum varchar NOT NULL, "\
                                "imagedate DATE,"\
                                "imagepath varchar,"\
                                "datetime DATETIME,"\
                                "imagename varchar)"

#define SQLITE_INSERT_TABLE_SQL "INSERT INTO faceTable(devicenum,imagedate,imagepath,datetime,imagename)" \
                                "VALUES(?,?,?,?,?)"

#define SQLITE_SELECT_SINGLEGROUP_TABLE_SQL "SELECT imagepath,imagename,imagedate FROM faceTable "\
                                "WHERE datetime between datetime(?) AND datetime(?)" \
                                "AND devicenum = ?"

#define SQLITE_UPDATE_TABLE_SQL "UPDATE faceTable SET imagename=? WHERE datetime=?"

#define SQLITE_DELETE_TABLE_SQL "DELETE FROM faceTable WHERE imagedate = ?"

class face_database_api:public TSingleIns<face_database_api>
{
public:
    explicit face_database_api(void);
    ~face_database_api();

    /*sqlite3 init of database if facetable is not exist create it*/
    void face_database_init(void);

     /* sqlite3 insert row capture image info to facetable*/
    void face_database_insert_facetable(QString qstrDevnum, QString qstrDate, QString qstrStoragePath, QString qstrDateTime,QString qstrImageName);

    /* sqlite3 select all group result from facetable that need input the start datetime an end datetime*/
   // void face_database_select_allgroup_facetable(QString qstrStartTime,\
            QString qstrEndTime, QString& qstrDevnum, QString& qstrStoragePath, QString& qstrimgName);

    /* sqlite3 select single group result from facetable that need input the start datetime an end datetime*/
    void face_database_select_singlegroup_facetable(QString qstrStartTime,\
            QString qstrEndTime, QString qstrDevnum, vector<SearchResult>& searchResultItems);

    /*delete set date info from facetable*/
    void face_database_delete_all_facetable(QString qstrDetDate);

    /*sqlite3 shutdown database*/
    void face_database_shutdown(void);

private:
    QSqlDatabase database;
};

#endif // DATABASE_H
