#include "sqliteutil.h"
#include <QDebug>



/****************************************************************************
**
** Copyright (C) 2014 scutemos-huabo
** All rights reserved.
** Contact: wiessharling@qq.com
** Please keep the author contact information.
** 2014-07-16
**
****************************************************************************/




SqliteUtil::SqliteUtil(const QString &strDatabase) :
    m_strDatabase(strDatabase)
{
    createConnection(m_strDatabase);
}

SqliteUtil::~SqliteUtil()
{
    m_db.close();
}

bool SqliteUtil::createConnection(const QString &database)
{
    //与数据库建立连接
    if (QSqlDatabase::contains("my_conn"))
    {
        m_db = QSqlDatabase::database("my_conn");
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "my_conn");
    }
    //设置数据库名
    m_db.setDatabaseName(database);
    //打开数据库
    if (!m_db.open())
    {
        qDebug() << "Open database failed!";
        return false;
    }
    else
    {
        return true;
    }
}



QSqlRecord SqliteUtil::ExecuteRecord(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.exec();
    return query.record();
}

QSqlRecord SqliteUtil::ExecuteRecord(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    query.exec();
    return query.record();
}

QSqlRecord SqliteUtil::ExecuteRecord(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    query.exec();
    return query.record();
}

QSqlQuery SqliteUtil::ExecuteSqlQuery(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.setForwardOnly(true);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    query.exec();
    return query;
}

QSqlQuery SqliteUtil::ExecuteSqlQuery(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.setForwardOnly(true);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    query.exec();
    return query;
}

QSqlQuery SqliteUtil::ExecuteSqlQuery(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.setForwardOnly(true);
    query.prepare(strQuery);
    query.exec();
    return query;
}

int SqliteUtil::ExecuteInt(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.exec();
    int ID = 0;
    while(query.next())
    {
        ID = query.value(0).toInt();
    }
    return ID;
}

int SqliteUtil::ExecuteInt(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    query.exec();
    int ID = 0;
    while(query.next())
    {
        ID = query.value(0).toInt();
    }
    return ID;
}

int SqliteUtil::ExecuteInt(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    query.exec();
    int ID = 0;
    while(query.next())
    {
        ID = query.value(0).toInt();
    }
    return ID;
}

bool SqliteUtil::Execute(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    return query.exec();
}

bool SqliteUtil::Execute(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    return query.exec();
}

QString SqliteUtil::ExecuteString(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.exec();
    QString temp;
    while(query.next())
    {
        temp = query.value(0).toString();
    }
    return temp;
}

void SqliteUtil::ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    p_queryModel->setQuery(strQuery, m_db);
}

void SqliteUtil::ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                       QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    p_queryModel->setQuery(query);
}

void SqliteUtil::ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                                   QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    p_queryModel->setQuery(query);
 }
