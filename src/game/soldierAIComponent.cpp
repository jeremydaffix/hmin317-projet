
#include "game/soldierAIComponent.h"

#include <game/soldier.h>
#include <game/imaginawars.h>


SoldierAIComponent::SoldierAIComponent(Soldier *s)
{
    soldier = s;
    iw = (ImaginaWars*)ImaginaWars::getInstance();

    qse.setLoopCount(1);
    qse.setVolume(0.25);
}

void SoldierAIComponent::update()
{

}

void SoldierAIComponent::fixedUpdate()
{
    if(getContainer() == NULL) return;

    if(cptFrames % 5 == 0) {

        std::list<Soldier*> soldiers = iw->getSoldiers();

        std::list<Soldier*>::iterator it;

        float nearestDist = 999999.;
        Soldier *nearestSoldier = NULL;

        for (it = soldiers.begin( ); it != soldiers.end(); ++it)
        {
            if((*it)->getPlayer()->getNumPlayer() != soldier->getPlayer()->getNumPlayer()) // ennemi !!!
            {


                float dist = (*it)->getLocalPosition().distanceToPoint(soldier->getLocalPosition());


                if(dist <= 0.5) { // on est suffisamment prets pour se fighter

                    if(dist < nearestDist) { // plus prets que les autres ennemis

                        nearestDist = dist;
                        nearestSoldier = (*it);
                    }
                }
            }

        }


        if(nearestSoldier != NULL) // BASTOOOON
        {
            //qDebug() << "PAR ICI MA MIGNONNE";

            QVector2D mypos2d = QVector2D(soldier->getLocalPosition().x(), soldier->getLocalPosition().y());
            QVector2D ennemypos2d = QVector2D(nearestSoldier->getLocalPosition().x(), nearestSoldier->getLocalPosition().y());

            QVector2D dir = (ennemypos2d - mypos2d).normalized(); // direction vers le fieffé coquin

            soldier->getPathfinding()->setEnabled(false);
            soldier->selectStateAttack(dir);


            // degats

            if(cptFrames % 20 == 0)
            {
                int deg = 4;

                if(soldier->getType() == Soldier::TYPE_KNIGHT && nearestSoldier->getType() == Soldier::TYPE_ARCHER) deg *= 4; // fantassins forts contre archers
                else if(soldier->getType() == Soldier::TYPE_ARCHER && nearestSoldier->getType() == Soldier::TYPE_FAIRY) deg *= 4; // archers forts contre volants
                else if(soldier->getType() == Soldier::TYPE_FAIRY && nearestSoldier->getType() == Soldier::TYPE_KNIGHT) deg *= 4; // volants forts contre fantassins

                nearestSoldier->setLife(nearestSoldier->getLife() - deg);

            }


            // SONS DE LA BATAILLE QUI TUE

            if(soldier->getType() == Soldier::TYPE_ARCHER)
            {
                qse.setVolume(0.70);

                if(cptFrames % 50 == 0)
                {
                    qse.stop();
                    qse.setSource(QUrl(QString("qrc:/resources/sounds/battle_sound_effects_0/battle_sound_effects/Bow.wav")));
                    qse.play();
                }
            }

            else if(soldier->getType() == Soldier::TYPE_KNIGHT)
            {
                if(cptFrames % 75 == 0)
                {
                    qse.stop();
                    qse.setSource(QUrl(QString("qrc:/resources/sounds/qubodupImpactMetal.wav")));
                    qse.play();
                }

                else if(cptFrames % 50 == 0)
                {
                    qse.stop();
                    qse.setSource(QUrl(QString("qrc:/resources/sounds/battle_sound_effects_0/battle_sound_effects/swish_4.wav")));
                    qse.play();
                }

                else if(cptFrames % 25 == 0)
                {
                    qse.stop();
                    qse.setSource(QUrl(QString("qrc:/resources/sounds/rpg_sound_pack/RPG Sound Pack/battle/sword-unsheathe2_44.wav")));
                    qse.play();
                }
            }

            else if(soldier->getType() == Soldier::TYPE_FAIRY)
            {
                qse.setVolume(0.55);

                if(cptFrames % 120 == 0)
                {
                    qse.stop();
                    qse.setSource(QUrl(QString("qrc:/resources/sounds/rpg_sound_pack/RPG Sound Pack/battle/spell.wav")));
                    qse.play();
                }
            }
        }

        else // on reprend notre route si plus d'ennemis à proximité
        {
            soldier->getPathfinding()->setEnabled(true);
        }
    }



    ++cptFrames;
}
