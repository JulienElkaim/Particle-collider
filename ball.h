#ifndef BALL_H
#define BALL_H


class Ball
{
public:
    Ball(double xaxe, double yaxe, int r, double acceleration, double dirx, double diry);
    int applyAllConstraint();
    void gravityEffect();
    void frictionEffect();
    void move();
    void ownAcceleration();


public:

    double x;
    double y;
    double acc;
    int rayon;

    double preview_X;
    double preview_Y;
    double preview_Acc;

    double velocity[2];




private:
    void unitirizedVelocity(); //Reduit le vecteur a un vecteur unitaire
    int applySurfaceConstraint(); //rencontre surface
    int applyCollisionConstraint(); //rencontre boules
    int applyFalseConstraint();

};

#endif // BALL_H
