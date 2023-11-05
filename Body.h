#ifndef SHOWOFF_BODY_H
#define SHOWOFF_BODY_H

#include <iostream>
#include <Eigen/Eigen>
#include <SFML/Graphics/Color.hpp>
#include <cmath>

using namespace std;
using namespace Eigen;

class Body {

private:
    Vector2d lastPosition;
    double lastDt;
    bool firstStepDone = false;

public:
    double mass;
    double radius;
    Vector2d position;
    Vector2d velocity;
    sf::Color color;

    Body(double mass, double radius, Vector2d &pos, Vector2d &vel, sf::Color color = sf::Color::White) {
        this->mass = mass;
        this->radius = radius;
        position = pos;
        velocity = vel;
        this->color = color;
    };

    double kineticEnergy() {
        return 0.5 * mass * velocity.squaredNorm();
    };

    void verletNextStep(Vector2d acceleration, double dt) {

        if (dt == 0)
            return;

        if (!firstStepDone) {
            lastPosition = position;
            position = lastPosition
                       + velocity * dt
                       + 0.5 * acceleration * dt * dt;
            lastDt = dt;
            firstStepDone = true;
            return;
        }

        Vector2d nextPosition = position
                                + (position - lastPosition) * dt/lastDt
                                + acceleration * dt * (dt + lastDt)/2;
        lastDt = dt;

        lastPosition = position;
        position = nextPosition;

        velocity = (position - lastPosition)/dt;
    };

    double density() {
        return mass/(M_PI * radius * radius);
    }

    Vector2d vectorTo(Body &body) {
        return body.position - position;
    };
};

#endif