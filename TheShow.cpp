#include "Solver.h"

#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace Eigen;

void draw(Solver &solver, sf::RenderWindow &window);


int main() {

    //dt ~ 0.01 s

    double dt = 0.01;
    int T = 100;

    int steps = T/dt;

    Solver solver;

    // FOR VISUALS:
    /*

    sf::RenderWindow window(sf::VideoMode(800, 800), "NBPCPP");
    sf::View view;

    view.setCenter(0, 0);
    view.setRotation(180);
    view.setSize(view.getSize().x, -view.getSize().y);


    int scale = 30000000;

    view.setSize(scale, scale * view.getSize().y/view.getSize().x);

    window.setView(view);
    */


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int i = 0; i < steps; i++) {
        solver.passTime(dt);


        // FOR VISUALS:
        /*
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        draw(solver, window);
         */
        //FOR VISUALS ^

    }


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

    return 0;
}

// ALSO FOR VISUALS:
/*
void drawBody(Body &body, sf::RenderWindow &window) {

    sf::CircleShape shape(body.radius);

    shape.setFillColor(sf::Color::White);
    shape.setOrigin(body.radius, body.radius);
    shape.setPosition(body.position.x(), body.position.y());

    window.draw(shape);
}

void draw(Solver &solver, sf::RenderWindow &window) {

    window.clear();

    vector<Body> bodiesInfo = solver.getBodiesInfo();
    for (Body body: bodiesInfo)
        drawBody(body, window);


    window.display();

}

*/

