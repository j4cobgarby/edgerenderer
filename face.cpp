#include "face.hpp"

TriFace::TriFace(Eigen::Vector3f* p1, Eigen::Vector3f* p2, Eigen::Vector3f* p3, int p1i, int p2i, int p3i) :
    p1(p1),
    p2(p2),
    p3(p3),
    p1i(p1i),
    p2i(p2i),
    p3i(p3i)
{}