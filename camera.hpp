#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "edge.hpp"

void get_alpha_beta(sf::Vector3f forwards, sf::Vector3f origin, sf::Vector3f vert, float* alpha, float* beta);

class Camera {
private:
    Eigen::Vector3f origin; // The origin position of the camera
    Eigen::Vector3f forwards, up, right; // Normalised direction vectors representing the
                                      // orientation of the camera
    float fov; // The field of view on the X-axis, in radians

    float angle_between(Eigen::Vector3f v1, Eigen::Vector3f v2); // Angle in radians between two vectors
    
public:
    Camera(Eigen::Vector3f origin, Eigen::Vector3f forwards, Eigen::Vector3f up, Eigen::Vector3f right, float fov);

    void render(sf::RenderTarget* target, std::vector<Edge> edges);
    void translate(Eigen::Vector3f delta);
    void translate(float x, float y, float z);

    void get_alpha_beta(Eigen::Vector3f vert, float* alpha, float* beta);
};

#endif