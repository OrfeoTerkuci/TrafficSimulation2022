#ifndef TRAFFICSIMULATION2022_VOERTUIG_H
#define TRAFFICSIMULATION2022_VOERTUIG_H

class Vehicle {

    double speed;
    double position;

public:
    Vehicle(double speed, double position);

    double getSpeed() const;

    void setSpeed(double speed);

    double getPosition() const;

    void setPosition(double position);

    virtual ~Vehicle();
};


#endif //TRAFFICSIMULATION2022_VOERTUIG_H
