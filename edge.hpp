#ifndef EDGE_HPP
#define EDGE_HPP

#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>

class Edge {
public:
    Edge(Eigen::Vector3f a, Eigen::Vector3f b) : a(a), b(b) {}
    Edge(float ax, float ay, float az, float bx, float by, float bz);

    Eigen::Vector3f a, b; // The two points of the edge
};

#endif