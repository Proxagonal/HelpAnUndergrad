#ifndef SHOWOFF_SOLVER_H
#define SHOWOFF_SOLVER_H

#include <iostream>
#include <Eigen/Eigen>
#include "Body.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include "Simulation.h"

using namespace std;
using namespace Eigen;


class Solver {

private:

    const double G = 6.674 * pow(10, -11);
    const int subSteps = 1;

    //***VISUAL
    //const sf::RenderWindow &window;
    //const Vector2d (*getMouse)(const sf::RenderWindow &);

    vector<Body> bodyList;

    double t = 0;
    double totalMass;

    double getRandom() {
        return ((double)rand()) / RAND_MAX;
    }

public:

    Solver() {

    //Solver(sf::RenderWindow &window, Vector2d (*getMouse)(const sf::RenderWindow &)):
    //window(window) {

        //this->getMouse = (const Vector2d (*)(const sf::RenderWindow &))getMouse;

        srand(time(0));

        this->bodyList = initialConditions();
        totalMass = calcTotalMass();

        for (Body &body : bodyList)
            body.color = sf::Color::White;
    }

    vector<Body> initialConditions() {

        vector<Body> list;

        for (int j = 1; j < 3; j++) {
            int n = 7*j; //20 BODIES
            for (int i = 0; i < n; i++) {

                Vector2d pos(j*500000 * cos(2*M_PI*i/n), j*500000 * sin(2*M_PI*i/n));
                Vector2d vel(-120000 * sin(2*M_PI*i/n) * j * 2, 120000 * cos(2*M_PI*i/n) * j * 2);
                sf::Color color((i%3 == 0)*255, ((i+1)%3 == 0)*255, ((i+2)%3 == 0)*255);

                list.emplace_back(200000000000000000000000000.0, 100000 * (getRandom()+0.3),
                                            pos,
                                            vel, color);
            }
        }

        list.erase(std::next(list.begin())); // was 21, now 20

        cout << list.size() << endl;

        return list;

    }

    void passTime(double dt) {

        t += dt;

        for (int i = 0; i < subSteps; i++) {
            doVerlet(dt/subSteps);
            fixCollisions();
        }

    }

    void doVerlet(double dt) {

        for (Body &body : bodyList) {
            body.verletNextStep(totalAccelerationOf(body), dt);
        }
    }

    void fixCollisions() {

        //NAIVE
        for (Body &body1 : bodyList)
            for (Body &body2 : bodyList)
                if (&body1 != &body2 && isCollide(body1, body2))
                    unCollide(body1, body2);
    }

    double calcTotalMass() {

        double mass = 0;

        for (Body &body : bodyList) {
            mass += body.mass;
        }

        return mass;

    }

    Vector2d totalGravitationalAccelerationOf(Body &body) {

        Vector2d acc(0, 0);

        for (Body &otherBody : bodyList)
            if (body.vectorTo(otherBody).norm() != 0)
                acc += gravitationalAccelerationOf(body, otherBody);

        //acc += -10*body.position.normalized() * G * body.mass/body.position.squaredNorm();

        return acc;
    };

    Vector2d totalAccelerationOf(Body &body) {

        Vector2d acc(0,0);

        acc += totalGravitationalAccelerationOf(body);

        return acc;

    }

    Vector2d gravitationalAccelerationOf(Body &body1, Body &body2) {

        Vector2d rHat = body1.vectorTo(body2).normalized();
        double rSquared = body1.vectorTo(body2).squaredNorm();

        return rHat * G * body2.mass/rSquared;
    };

    void unCollide(Body &body1, Body &body2) {

        Vector2d move = body1.vectorTo(body2).normalized()
                * (body1.radius + body2.radius - body1.vectorTo(body2).norm());

        body1.position -= move/2;
        body2.position += move/2;

    };

    bool isCollide(Body &body1, Body &body2) {
        return body1.radius + body2.radius > body1.vectorTo(body2).norm();
    }

    const vector<Body> &getBodiesInfo() {
        return bodyList;
    }

};


#endif //SHOWOFF_SOLVER_H
