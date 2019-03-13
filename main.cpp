#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "camera.hpp"
#include "model.hpp"

#define SPEED 7
#define ROT 2.5
#define KEYPRESSED(k) sf::Keyboard::isKeyPressed(sf::Keyboard::Key::k)

int main() {
    std::string objpath("objs/knot.obj");
    Model suz(objpath);

    Eigen::Vector3f origin, forwards, up, right;
    origin <<       -5, 0.5, 0;
    forwards <<     1, 0, 0;
    up <<           0, 1, 0;
    right <<        0, 0, 1;

    Camera cam(origin, forwards, up, right, 1.396263);

    sf::RenderWindow win(sf::VideoMode(800, 800), "Renderer");
    win.setVerticalSyncEnabled(true);
    sf::Clock delta;

    while (win.isOpen()) {
        float dt = delta.restart().asSeconds();

        win.setTitle(std::to_string(1/dt));

        sf::Event ev;
        while (win.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) win.close();
        }

        if (KEYPRESSED(W))
            cam.translate_along_direction(SPEED * dt, 0, 0);
        if (KEYPRESSED(S))
            cam.translate_along_direction(-SPEED * dt, 0, 0);
        if (KEYPRESSED(A))
            cam.translate_along_direction(0, 0, -SPEED * dt);
        if (KEYPRESSED(D)) {
            cam.translate_along_direction(0, 0, SPEED * dt);
        }

        if (KEYPRESSED(Left))
            cam.rotate(0, ROT * dt, 0);
        if(KEYPRESSED(Right))
            cam.rotate(0, -ROT * dt, 0);

        cam.render(&win, suz);
        win.display();
    }

}
