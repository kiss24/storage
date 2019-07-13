#ifndef SQLITEUTIL_H
#define SQLITEUTIL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <QVariant>
#include <QSqlQueryModel>
#include <QSqlRecord>


class SqliteUtil
{
public:
    explicit SqliteUtil(const QString& strDatabase = "smart.db");
    ~SqliteUtil();

    bool createConnection(const QString& strConn);

    QSqlRecord ExecuteRecord(const QString& strQuery);
    QSqlRecord ExecuteRecord(const QString& strQuery, QList<QVariant> lstParameter);
    QSqlRecord ExecuteRecord(const QString& strQuery, QVariant Parameter);

    QSqlQuery ExecuteSqlQuery(const QString& strQuery, QList<QVariant> lstParameter);
    QSqlQuery ExecuteSqlQuery(const QString& strQuery, QVariant Parameter);
    QSqlQuery ExecuteSqlQuery(const QString& strQuery);

    int ExecuteInt(const QString& strQuery);
    int ExecuteInt(const QString& strQuery, QList<QVariant> lstParameter);
    int ExecuteInt(const QString& strQuery, QVariant Parameter);

    bool Execute(const QString& strQuery, QVariant Parameter);
    bool Execute(const QString& strQuery, QList<QVariant> lstParameter);

    QString ExecuteString(const QString& strQuery);

    void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery);
    void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                           QList<QVariant> lstParameter);
    void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery, QVariant Parameter);


public:
    QSqlDatabase m_db;
    QString m_strDatabase;

};

#endif // SQLITEUTIL_H
