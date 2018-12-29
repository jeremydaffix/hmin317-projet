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

    //QString defaultSprite = json["defaultsprite"].toString();
    QJsonArray defaultTiles = json["defaulttiles"].toArray();


    width = json["width"].toInt();
    height = json["height"].toInt();


    // on commence par afficher les tiles de fond
    for(int i = 0 ; i < width ; ++i)
    {
        for(int j = 0 ; j < height ; ++j)
        {
            int n = QRandomGenerator::global()->bounded(defaultTiles.size());
            //int rot = QRandomGenerator::global()->bounded(4) * 90;

            std::string spr = defaultTiles[n].toString().toStdString();

            addSprite(spr, i, j);
        }
    }


    // tiles de la carte
    if (json.contains("tiles") && json["tiles"].isObject())
    {
            QJsonObject tiles = json["tiles"].toObject();

            for (int i = 0; i < tiles.size(); ++i) // pour chaque tile
            {
                QString tileName = tiles.keys().at(i);
                QJsonArray listPos = tiles.value(tileName).toArray();

                for(int j = 0 ; j < listPos.size() ; ++j) // pour chaque case où mettre ce tile
                {
                    QJsonArray coords = listPos[j].toArray();

                    int x = coords[0].toInt();
                    int y = coords[1].toInt();

                    addSprite(tileName.toStdString(), x, y);
                }

            }
        }

}


Sprite *GameMap::addSprite(std::string name, int caseX, int caseY, int rot)
{
    Sprite *s = new Sprite(name, QVector3D((-width / 2.) + caseX, (-height / 2.) + caseY, 0), rot, QVector2D(0.094,0.094));

    addChild(s);

    return s;
}
