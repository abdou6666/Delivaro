#include "connection.h"

connection::connection()
{

}
bool connection::createConnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("abdou");
db.setUserName("abdou");//inserer nom de l'utilisateur
db.setPassword("abdou");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void connection::closeConnection(){db.close(); }
