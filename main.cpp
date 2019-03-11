#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "camera.hpp"

#define SPEED 0.0001
#define KEYPRESSED(k) sf::Keyboard::isKeyPressed(sf::Keyboard:: k)

int main() {
    std::vector<Edge> edges;
    edges.push_back(Edge(0, 0, 0, 2, 0, 0));
    edges.push_back(Edge(0, 0, 0, 0, 2, 0));
    edges.push_back(Edge(0, 0, 0, 0, 0, 2));

    edges.push_back(Edge(0, 0, 2, 0, 2, 2));
    edges.push_back(Edge(0, 0, 2, 2, 0, 2));

    edges.push_back(Edge(2, 0, 0, 2, 2, 0));
    edges.push_back(Edge(2, 0, 0, 2, 0, 2));
    //edges.push_back(Edge(2, 0, 0, 2, 2, 2));

    Eigen::Vector3f test;
    test << 2, 0, 0;

    Eigen::Vector3f origin, forwards, up, right;
    origin <<       0, 0, 0;
    forwards <<     1, 0, 0;
    up <<           0, 1, 0;
    right <<        0, 0, 1;

    Camera cam(origin, forwards, up, right, 1.745329);

    sf::RenderWindow win(sf::VideoMode(640, 480), "Window");

    while (win.isOpen()) {
        sf::Event ev;
        while (win.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) win.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            cam.translate(SPEED, 0, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            cam.translate(-SPEED, 0, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            cam.translate(0, 0, -SPEED);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            cam.translate(0, 0, SPEED);

        cam.render(&win, edges);
        win.display();

        float a, b;
        cam.get_alpha_beta(test, &a, &b);
        std::cout << a << " " << b << std::endl;
    }

}
