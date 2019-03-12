#ifndef EDGE_HPP
#define EDGE_HPP

#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>

class Edge {
public:
    Edge(Eigen::Vector3f a, Eigen::Vector3f b, int ai, int bi) : a(a), b(b), ai(ai), bi(bi) {}
    Edge(float ax, float ay, float az, float bx, float by, float bz);

    Eigen::Vector3f a, b; // The two points of the edge
    int ai, bi; // Vertex indices
};

#endif