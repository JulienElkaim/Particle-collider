#include "ball.h"
#include <cmath>
#include <string>
#include <iostream>
#include <stdlib.h>


/**
 * @brief myabs is used to provide an abs solution able to handle double type.
 * @param inputer is the number to transform
 * @return absolute value of the input value
 */
double myabs(double inputer){
    return (inputer>0)? inputer: -inputer;
}

/**
* @brief transpose_vectorX let us find only the X value of the vector 1 transposed by the plan
* @param vecToTransposeX xValue of vector to transpose
* @param vecToTransposeY yValue of vector to transpose
* @param xTransD1 xValue of transposing vector of the plan
* @param yTransD1 yValue of transposing vector of the plan
* @return  the X value of the vector after transposition
*/
double transpose_vectorX( double vecToTransposeX, double vecToTransposeY, double xTransD1, double yTransD1){

    return vecToTransposeX* xTransD1 + vecToTransposeY *yTransD1; // (x,y) dot (xD1, yD1)

}

/**
* @brief transpose_vectorY let us find only the Y value of the vector 1 transposed by the plan
* @param vecToTransposeX xValue of vector to transpose
* @param vecToTransposeY yValue of vector to transpose
* @param xTransD1 xValue of transposing vector of the plan
* @param yTransD1 yValue of transposing vector of the plan
* @return  the X value of the vector after transposition
*/
double transpose_vectorY( double vecToTransposeX, double vecToTransposeY, double xTransD1, double yTransD1){

    //Second vecteur de la surface pour creer le plan sur lequel transposer vecToTranspose
    double xTransD2= -yTransD1;
    double yTransD2= xTransD1;

    return vecToTransposeX* xTransD2 + vecToTransposeY *yTransD2;

}

Ball::Ball(double xaxe, double yaxe, int r, double acceleration, double dirx, double diry)
{
    rayon = (r < 100)? ( (r>1)? r : 1 ) : 100;
    x = xaxe;
    y = yaxe;
    acc = acceleration;
    velocity[0] = dirx;
    velocity[1] = diry;

    preview_Y = y;
    preview_X = x;
    this->unitirizedVelocity();

}

/**
 * @brief Ball::unitirizedVelocity find (x',y') for vector velocity (x,y) as max(x',y') =1 and x'/y' = x/y
 */
void Ball::unitirizedVelocity(){ //Reduit le vecteur a un vecteur unitaire

    if (myabs(this->velocity[0]) >= 1 || myabs(this->velocity[1]) >= 1){
        //Verifie le plus grand des deux pour appliquer la bonne fonction de reduction
        if(myabs(this->velocity[0]) > myabs(this->velocity[1])){
            this->velocity[0] = this->velocity[0]/myabs(this->velocity[0]) ;
            this->velocity[1] = this->velocity[1]/myabs(this->velocity[0]);
        }else{
            this->velocity[0] = this->velocity[0]/myabs(this->velocity[1]) ;
            this->velocity[1] = this->velocity[1]/myabs(this->velocity[1]);
        }

    }else{
        if(myabs(this->velocity[0]) > myabs(this->velocity[1])){
            this->velocity[0] = this->velocity[0]/myabs(this->velocity[0]) ;
            this->velocity[1] = this->velocity[1]/myabs(this->velocity[0]);
        }else{
            this->velocity[0] = this->velocity[0]/myabs(this->velocity[1]) ;
            this->velocity[1] = this->velocity[1]/myabs(this->velocity[1]);
        }
    }

}

/**
 * @brief Ball::ownAcceleration apply to this particule its own acceleration to predict future position
 */
void Ball::ownAcceleration(){
    //Apply its own acceleration on PREVIEW values
    this->preview_X += this->acc * this->velocity[0];
    this->preview_Y += this->acc * this->velocity[1];
}

/**
 * @brief Ball::gravityEffect apply gravity on trajectory and acceleration
 */
void Ball::gravityEffect(){

    //Apply on Vector
    double g = 0.025;
    this->velocity[1] += g; //apply gravity on velocity vector, ICI POURRA INTERVENIR UNE POSSIBLE MASSE POUR ACCENTUER L'EFFET


    this->unitirizedVelocity(); //Ca fera baisser les x, monter les y, petit a petit

    //Apply gravity on Acceleration
    if(this->acc <= 0){
        this->velocity[1] = myabs(this->velocity[1]);

    }

    //Si Y décroit, alors la boule monte, donc la gravity la fait décélérer
    if (this->velocity[1] < 0 && this->acc > 0 ){
        this->acc = (this->acc > 0.6)? this->acc - 0.3 : 0;
    }else{// Si Y croit, la boule tombe, la gravity la fait accélérer
        if(this->acc <=20){this->acc+= 0.3;}
    }
}

/**
 * @brief Ball::frictionEffect Apply friction on acceleration value
 */
void Ball::frictionEffect(){
    //Frein a l'acceleration en fonction du rayon
    //La friction reduit de 99,8% a 98,5%
    this->acc *= 0.998 - ( (0.998 - 0.985) * (this->rayon/100) );;
}

/**
 * @brief Ball::applyAllConstraint General function to resolve all constraints generated by the movement of the ball.
 * @return if any constraint had to be resolved, return 1. Return 0 otherwise.
 */
int Ball::applyAllConstraint(){
    //Appelle les autres fonctions de contraint
    int counter = 0;
    counter += this->applySurfaceConstraint(); //rencontre surface
    counter+= this->applyCollisionConstraint(); // rencontre boule
    counter+= this->applyFalseConstraint(); //Simuler un socle en attendant d'avoir des surfaces
    return (counter>=1)? 1:0;


}

/**
 * @brief applySurfaceConstraint
 * @return if any constraint had to be resolved, return 1. Return 0 otherwise.
 */
int Ball::applySurfaceConstraint(){
    //Appeler la fonction de la surface en parametre qui verifie si boule DANS surface

    //Si oui, passer une fonction de BALL pour corriger la position par le depassement
        //Ensuite, appliquer transposition sur le vecteur velocity
        //Changer acceleration

    // EXAMPLE d'essai d'implémentation dans le second projet du mail. Pb: Aucune connaissance des transformations de vecteurs / principes physique


    //Si non, return 0
    return 0;
}



/**
 * @brief Ball::applyFalseConstraint is to handle collision with the window's limits. Temp. function, waiting for surface implementation
 * @return if any constraint had to be resolved, return 1. Return 0 otherwise.
 *
 */
int Ball::applyFalseConstraint(){


    //Par rapport a limite BASSE
    if( this->preview_Y+this->rayon >460){

        //On simule un frame de contact, actualiser precisement X et Y pour faire apparaitre la boule au point de contact
        double depasse_Y = this->preview_Y + this->rayon -460;
        this->preview_Y -= depasse_Y;
        double depasse_X = depasse_Y * this->velocity[0] /this->velocity[1] ;
        this->preview_X -=  depasse_X;



        //Pena acceleration, absorbtion de force
        double reaction_Acc =0.70* this->acc;

        //transposer mon vecteur de deplacement avec la surface rencontrée (0,-1)
        this->velocity[0] = transpose_vectorX(this->acc*this->velocity[0],this->acc*this-> velocity[1],0,-1);
        this->velocity[1] = transpose_vectorY(this->acc*this->velocity[0],this->acc*this-> velocity[1],0,-1);
        this->velocity[0] = this->velocity[0]*1; // Deja sur le bon plan
        this->velocity[1] = this->velocity[1]*1; //Deja sur le bon plan
        this->unitirizedVelocity(); //rend le vecteur unitaire
        this->acc = reaction_Acc; //décélère la boule
        return 1;
    }

    //Par rapport a limite HAUTE
    if( this->preview_Y-this->rayon < -180){

        //On simule un frame de contact, actualiser precisement X et Y pour faire apparaitre la boule au point de contact
        double depasse_Y = this->preview_Y - rayon +180;
        this->preview_Y -= depasse_Y;
        double depasse_X = depasse_Y * this->velocity[0] /this->velocity[1] ;
        this->preview_X -=  depasse_X;



        //Pena acceleration, absorbtion de force
        double reaction_Acc =0.90* this->acc;

        //transposer mon vecteur de deplacement avec la surface rencontrée (0,-1)
        this->velocity[0] = transpose_vectorX(this->acc*this->velocity[0],this->acc*this-> velocity[1],0,1);
        this->velocity[1] = transpose_vectorY(this->acc*this->velocity[0],this->acc*this-> velocity[1],0,1);
        //this->velocity[0] = this->velocity[0]*-1; le remettre dans le plan ne marche pas
        //this->velocity[1] = this->velocity[1]*1; le remettre dans le plan ne marche pas
        this->unitirizedVelocity(); //rend le vecteur unitaire
        this->acc = reaction_Acc; //décélère la boule
        return 1;
    }


    //Par rapport a limite DROIT
    if( this->preview_X+this->rayon >460){
        //On simule un frame de contact, actualiser precisement X et Y pour faire apparaitre la boule au point de contact
        double depasse_X = this->preview_X + this->rayon -460;
        this->preview_X -= depasse_X;
        double depasse_Y = depasse_X * this->velocity[1] /this->velocity[0] ;
        this->preview_Y -=  depasse_Y;

        //Pena acceleration, absorbtion de force
        double reaction_Acc =0.90* this->acc;

        //transposer mon vecteur de deplacement avec la surface rencontrée (-1,0)
        this->velocity[0] = transpose_vectorX(this->acc*this->velocity[0],this->acc*this-> velocity[1],-1,0);
        this->velocity[1] = transpose_vectorY(this->acc*this->velocity[0],this->acc*this-> velocity[1],-1,0);
        //this->velocity[0] = this->velocity[1]*1; le remettre dans le plan ne marche pas
        //this->velocity[1] = this->velocity[0]*-1; le remettre dans le plan ne marche pas
        this->unitirizedVelocity(); //rend le vecteur unitaire
        this->acc = reaction_Acc; //décélère la boule
        return 1;
    }

    //Par rapport a limite GAUCHE
    if( this->preview_X-this->rayon < -100){
        //On simule un frame de contact, actualiser precisement X et Y pour faire apparaitre la boule au point de contact
        double depasse_X = this->preview_X - this->rayon +100;
        this->preview_X -= depasse_X;
        double depasse_Y = depasse_X * this->velocity[1] /this->velocity[0] ;
        this->preview_Y -=  depasse_Y;

        //Pena acceleration, absorbtion de force
        double reaction_Acc =0.90* this->acc;

        //transposer mon vecteur de deplacement avec la surface rencontrée (1,0)
        this->velocity[0] = transpose_vectorX(this->acc*this->velocity[0],this->acc*this-> velocity[1],-1,0);
        this->velocity[1] = transpose_vectorY(this->acc*this->velocity[0],this->acc*this-> velocity[1],1,0);
        //this->velocity[0] = this->velocity[1]*-1; le remettre dans le plan ne marche pas
        //this->velocity[1] = this->velocity[0]*1; le remettre dans le plan ne marche pas
        this->unitirizedVelocity(); //rend le vecteur unitaire
        this->acc = reaction_Acc; //décélère la boule
        return 1;
    }

    return 0;
}

/**
 * @brief Ball::applyCollisionConstraint handle collision with other particules
 * @return 1 if we had to handle a collision. 0 otherwise
 */
int Ball::applyCollisionConstraint(){
    //Apply collision constraint when facing a ball object

    //Utiliser en input un tableau de Ball et le parcourir
    // Voir les autres boules, si distance des centres deux a deux est plus petite que somme des rayons des deux particules, collision
    // Si collision, modifier sa propre trajectoire ET AUSSI la trajectoire de la boule en collision
    //Si pas collision, passer boule suivante. Si aucune collision

    //Si résolution d'une contrainte en amène une autre, le prochain tour de boucle dans helper va permettre de le resoudre, donc pas de reparcours du tableau de ball ici.

    return 0;

}

/**
 * @brief Ball::move Applied when strengths and constraints are applied and resolved. Actualize the particule position
 */
void Ball::move(){
    //Actualise les valeurs de  acc, et velocity
    this->x = this->preview_X;
    this->y = this->preview_Y;
}