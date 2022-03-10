#ifndef TRAFFICSIMULATION2022_VOERTUIG_H
#define TRAFFICSIMULATION2022_VOERTUIG_H


class Vehicle {

    double speed;
    double position;
    double acceleration;

public:
    Vehicle(double speed, double position);

    double getSpeed() const;

    void setSpeed(double newSpeed);

    double getPosition() const;

    void setPosition(double newPosition);

    double calculateAcceleration();

    double calculateSpeed();

    virtual ~Vehicle();
};


#endif //TRAFFICSIMULATION2022_VOERTUIG_H
