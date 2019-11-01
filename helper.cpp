#include "helper.h"
#include "ball.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

Helper::Helper()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(36, 32, 64));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    this->ballsTabSize = 20;
    this -> particule = new Ball*[ballsTabSize];
    this->particule[0] = new Ball(3,100,20,2, -0.9,1);
    this->particule[1] = new Ball(100,3,30,2,-0.5,-1);
    this->particule[2] = new Ball(230,10,10,2,-12,0);
    this->particule[3] = new Ball(219,5,20,2,-12,0);
    this->particule[4] = new Ball(0,0,10,14,-24,0);
    this->particule[5] = new Ball(230,40,10,5,0,-1);
    this->particule[6] = new Ball(400,200,20,2,1,5);
    this->particule[7] = new Ball(230,80,30,20,-1,-1);
    this->particule[8] = new Ball(100,90,20,2,-1,1);
    this->particule[9] = new Ball(17,17,20,2,1,12);
    this->particule[10] = new Ball(180,200,20,2,1,-12);
    this->particule[11] = new Ball(12,0,20,2,1,-12);
    this->particule[12] = new Ball(50,17,20,4,7,-12);
    this->particule[13] = new Ball(17,80,100,5,1,-1);//rapide
    this->particule[14] = new Ball(30,0,20,3,17,-12);
    this->particule[15] = new Ball(40,40,20,2,21,-12); //rapide
    this->particule[16] = new Ball(150,150,20,2,10,-12);
    this->particule[17] = new Ball(150,40,20,3,4,-12);//rapide
    this->particule[18] = new Ball(178,20,20,1,5,-12);
    this->particule[19] = new Ball(29,20,50,1,15,-12);//rapide



}

void Helper::paint(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(), background);
    painter->translate(100, 100);

    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    int myBallsSize = this->ballsTabSize;

    // A toutes les boules, appliquer la boucle pour que les forces et contraintes s'appliquent
    for(int i=0; i <myBallsSize; i++){


        //Appliquer forces en présence + direction et velocité actuelle

        this->particule[i] -> gravityEffect(); // Influence vecteur unitaire et acceleration
        this->particule[i]->frictionEffect();
        this->particule[i] ->ownAcceleration(); // Actualise les FUTURE x y




        //Boucle pour resoudre les constraints
            for (int resolve = 1; resolve<10; resolve++){

                //Recuperer toutes boules et surfaces existantes pour faire en sorte que les boules y aient toutes acces pour les calculs de contrainte

               // Actualise les FUTURE x y
               if( this ->particule[i]->applyAllConstraint() ==0){
                   //si toutes les contraintes resolues, alors sortir boucle
                   break;
               }
            }

       // Actualiser les coordonnées
        this->particule[i] ->move();

        //Afficher toutes les boules a la position du résultat
        painter->drawEllipse(QRectF(this->particule[i]->x, particule[i]->y, particule[i]->rayon, particule[i]->rayon));

    }


    painter->restore();

}
