#include "connection.h"

Connection::Connection()
{

}
bool Connection::create_connection()
{
    bool test=false;
    mydb= QSqlDatabase::addDatabase("QODBC");

    mydb.setDatabaseName("test");
    mydb.setUserName("yessine");
    mydb.setPassword("yessine");
    if (mydb.open())
    {
        qDebug()<<"Connection Reussite";
        test=true;
    }
    else
        qDebug()<<"Connection Echouee";
    return test;
}
void Connection::close_connection()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}