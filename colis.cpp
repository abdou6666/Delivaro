#include "colis.h"
#include "partenaire.h"


Colis::Colis()
{

}

bool Colis::ajouter()
{ QSqlQuery query;



    query.prepare("INSERT INTO COLIS (NUM_COLIS,DATE_LIVRAISON,ID_PARTENAIRE,ID_CLIENT,ADRESSE) VALUES(:NUM_COLIS,:DATE_LIVRAISON,:ID_PARTENAIRE,:ID_CLIENT,:ADRESSE)");

    query.bindValue(":NUM_COLIS",NUM_COLIS );
    query.bindValue(":DATE_LIVRAISON",DATE_LIVRAISON );
    query.bindValue(":ADRESSE",ADRESSE );
    query.bindValue(":ID_PARTENAIRE",ID_PARTENAIRE );
    query.bindValue(":ID_CLIENT",ID_CLIENT);


    return query.exec();

}

QSqlQueryModel* Colis::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select* from COLIS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_COLIS"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_LIVRAISON"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID_PARTENAIRE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID_CLIENT"));

        return model;



}

bool Colis::supprimer(int NUM_COLIS)
{
    QSqlQuery qry;
    QString a = QString::number(NUM_COLIS);
    qry.prepare("Delete from COLIS where NUM_COLIS = :NUM_COLIS");
    qry.bindValue(":NUM_COLIS",a);
    return qry.exec();
}


QSqlQueryModel * Colis::chercher_colis(int NUM_COLIS){
QSqlQuery q;
q.prepare("select * from COLIS where NUM_COLIS=:NUM_COLIS");
q.bindValue(":NUM_COLIS", NUM_COLIS);
q.exec();
QSqlQueryModel * model = new QSqlQueryModel;
model->setQuery(q);
model->setQuery("select* from COLIS");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_COLIS"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_LIVRAISON"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESSE"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID_PARTENAIRE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID_CLIENT"));
QSqlRecord rec = model->record(0);
int num = rec.value("NUM_COLIS").toInt();
if( num == NUM_COLIS){
    return model;
  }
    return nullptr;
}

void Colis::exporter(QTableView *table)
{
    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                                    filters, &defaultFilter);
    QFile file(fileName);
    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
    }
}






/* QVector<double> Colis::getData()
{
     QVector<double>testData;

     QSqlQuery query("select AVG(NOMBRE_COMMANDES)from PARTENAIRES where TYPE_PRODUIT ='alimentaire' ");
     while(query.next()){
         int erreur=0;
         int errerE=query.value(0).toInt();
         QSqlQuery query2("select AVG(NOMBRE_COMMANDES)from PARTENAIRES where TYPE_PRODUIT ='divers' ");
     while(query2.next()){
         erreur=query2.value(0).toInt();
     break;}
     testData<< errerE << erreur ;
     break;}
             return testData;  }
*/


 QSqlQueryModel *Colis::trier(QString critere,QString AD)
 {
     QSqlQuery *qry=new QSqlQuery();
     QSqlQueryModel *model=new QSqlQueryModel();
     qry->prepare("select * from COLIS order by "+critere+" "+AD);
     qry->exec();
     model->setQuery(*qry);
     return model;
 }
QSqlQueryModel *Colis::recherche_avancee(QString critere)
{ QSqlQuery qry;
     qry.prepare("select * from COLIS where lower(adresse) like '"+critere+"%' OR lower(id_partenaire) like '"+critere+"%' OR lower(id_client) like '"+critere+"%'");
     qry.exec();
     QSqlQueryModel * model = new QSqlQueryModel;
     model->setQuery(qry);
     model->setQuery("select* from COLIS");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_COLIS"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_LIVRAISON"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESSE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID_PARTENAIRE"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID_CLIENT"));
     return model;
}
