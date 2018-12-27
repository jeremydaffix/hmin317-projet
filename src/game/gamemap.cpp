#include "gamemap.h"



GameMap::GameMap(QString path) : GameObject ()
{
    qDebug() << "LOADING MAP " << path;


    QFile file;

    // lecture du fichier de la map
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    //qWarning() << val;

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8()); // on cree un document json

    QJsonObject json = doc.object(); // objet racine

    // a partir de là, chaque noeud =
    // soit un autre objet, soit un tableau, soit une valeur "de base"

    QString mapName = json["mapname"].toString();
    QString defaultSprite = json["defaultsprite"].toString();

    if (json.contains("sprites") && json["sprites"].isArray())
    {
            QJsonArray spritesArray = json["sprites"].toArray();

            //mNpcs.clear();
            //mNpcs.reserve(npcArray.size());

            for (int i = 0; i < spritesArray.size(); ++i)
            {
                QJsonObject obj = spritesArray[i].toObject();



                //Sprite *spr = new Sprite();

            }
        }


          /*QJsonValue value = sett2.value(QString("appName"));
          qWarning() << value;
          QJsonObject item = value.toObject();
          qWarning() << tr("QJsonObject of description: ") << item;

          // in case of string value get value and convert into string
          qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
          QJsonValue subobj = item["description"];
          qWarning() << subobj.toString();

          // in case of array get array and convert into string
          qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
          QJsonArray test = item["imp"].toArray();
          qWarning() << test[1].toString();*/
}
