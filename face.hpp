#ifndef FACE_HPP
#define FACE_HPP

#include <eigen3/Eigen/Dense>

class TriFace { // Triangle face
public:
    TriFace(Eigen::Vector3f* p1, Eigen::Vector3f* p2, Eigen::Vector3f* p3) : p1(p1), p2(p2), p3(p3) {}

    Eigen::Vector3f* p1, p2, p3;
};

#endif