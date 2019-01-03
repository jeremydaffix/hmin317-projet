#include "gamemap.h"



GameMap::GameMap(QString _path) : Model3D ()
{
    path = _path;

}

GameMap::~GameMap()
{
    if(walkableMap != NULL)
    {
        delete walkableMap;
    }
}

void GameMap::BuildMap()
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


   initWalkableMap();


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

    // obstacles (= tiles non marchables) de la carte
    if (json.contains("obstacles") && json["obstacles"].isObject())
    {
            QJsonObject obstacles = json["obstacles"].toObject();

            for (int i = 0; i < obstacles.size(); ++i) // pour chaque tile
            {
                QString tileName = obstacles.keys().at(i);
                QJsonArray listPos = obstacles.value(tileName).toArray();

                for(int j = 0 ; j < listPos.size() ; ++j) // pour chaque case où mettre ce tile
                {
                    QJsonArray coords = listPos[j].toArray();

                    int x = coords[0].toInt();
                    int y = coords[1].toInt();

                    addSprite(tileName.toStdString(), x, y, 0);

                    walkableMap[width * y + x] = 0;
                }

            }
    }
}

std::list<QVector2D> GameMap::calcPath(QVector2D start, QVector2D target)
{
    std::list<QVector2D> ret;

    int pOutBuffer[42];

    int size = AStarFindPathDiag((int)start.x(), (int)start.y(),
                    (int)target.x(), (int)target.y(),
                    walkableMap, width, height,
                    pOutBuffer, 42);

    //qDebug() << "size path " << size;

    for(int k = 0 ; k < size ; ++k)
    {
        //index = (width * row) + col

        int index = pOutBuffer[k];

        int x = index % width;
        int y = index / width;

        QVector2D pos = QVector2D(x, y);

        ret.push_back(pos);

        //qDebug() << pos;
    }

    //qDebug() << "path btw " << start << target;
    //qDebug() << ret;

    return ret;
}

QVector2D GameMap::posToCase(QVector2D pos)
{
    // repère en bas à gauche de l'écran
    float xorigin = pos.x() + width / 2.;
    float yorigin = pos.y() + height / 2.;

    return QVector2D((int)xorigin, (int)yorigin);
}

QVector2D GameMap::caseToPos(QVector2D cas)
{
    return QVector2D((-width / 2.) + cas.x() + 0.5, (-height / 2.) + cas.y() + 0.5);
}


Sprite *GameMap::getSprite(QVector2D pos)
{
    int index = (int)pos.x() * height + (int)pos.y();
    return (Sprite*)*std::next(getChildren().begin(), index);
    //return (Sprite*)*getChildren().begin();
}


Sprite *GameMap::addSprite(std::string name, int caseX, int caseY, int rot, float z)
{
    Sprite *s = new Sprite(name, QVector3D((-width / 2.) + caseX, (-height / 2.) + caseY, z), rot, QVector2D(0.094,0.094), getShader());

    addChild(s);

    return s;
}

int GameMap::getHeight() const
{
    return height;
}

int GameMap::getWidth() const
{
    return width;
}

void GameMap::initWalkableMap()
{
    walkableMap = new unsigned char[height*width];

    std::vector<int> traversable;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
          //char c;
          //cin >> c;

          //walkableMap[width * j + i] = (count(passable.begin(), passable.end(), c) > 0);

          //if (count(passable.begin(), passable.end(), c) > 0)
          //      traversable.push_back(width*j + i);


            walkableMap[width * j + i] = 1;
        }
    }
}
