#ifndef MODEL_HPP
#define MODEL_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "edge.hpp"

class Model {
protected:
    std::vector<Eigen::Vector3f> points;
    std::vector<Edge> edges;
    std::vector<std::vector<Eigen::Vector3f*>> faces; // A vector of ({vectors of vertex pointers} == faces)
public:
    Model(std::string obj_filename);

    std::vector<Edge>& get_edges() {return edges;}
};

#endif
