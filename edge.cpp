#include "edge.hpp"

Edge::Edge(float ax, float ay, float az, float bx, float by, float bz) {
    a << ax, ay, az;
    b << bx, by, bz;
}