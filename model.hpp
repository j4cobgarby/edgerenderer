#ifndef MODEL_HPP
#define MODEL_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "edge.hpp"
#include "face.hpp"

class Model {
protected:
    std::vector<Eigen::Vector3f> points;
    std::vector<Edge> edges;
    std::vector<TriFace> faces;
public:
    Model(std::string obj_filename);

    std::vector<Eigen::Vector3f>& get_points() {return points;}
    std::vector<Edge>& get_edges() {return edges;}
    std::vector<TriFace>& get_faces() {return faces;}
};

#endif
