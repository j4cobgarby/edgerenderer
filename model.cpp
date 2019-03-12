#include "model.hpp"

Model::Model(std::string obj_filename) {
    std::ifstream obj_file(obj_filename);
    std::string ln;

    while (!obj_file.eof()) {
        std::getline(obj_file, ln);

        if (ln.size() == 0) continue;

        if (ln.substr(0, 2) == "v ") {
            float x, y, z;
            Eigen::Vector3f newpoint;

            if (sscanf(ln.c_str(), "v %f %f %f", &x, &y, &z) != 3) {
                std::cout << "Invalid line: " << ln << std::endl;
                continue;
            }

            newpoint << x, y, z;
            points.push_back(newpoint);
        }
    }

    obj_file.clear();
    obj_file.seekg(0);

    while (!obj_file.eof()) {
        std::getline(obj_file, ln);

        if (ln.size() == 0) continue;

        if (ln.at(0) == 'f') {
            std::stringstream ss(ln);
            std::vector<int> vert_indices;

            ss.ignore(2); // Ignore f character and following space. TODO: Make this better

            while (ss) {
                std::string word;
                int val;

                ss >> word;

                if (sscanf(word.c_str(), "%d", &val) == 1) {
                    vert_indices.push_back(val);
                }
            }

            for (int i = 0; i < vert_indices.size() - 1; i++) { // Iterate all elements except the last, since I'm getting pairs
                edges.push_back(
                    Edge(points.at(vert_indices.at(i)-1), points.at(vert_indices.at(i+1)-1),
                    vert_indices.at(i)-1, vert_indices.at(i+1)-1)
                );
            }

            if (vert_indices.size() == 3) { // Only draw triangular faces
                faces.push_back(TriFace(
                    &points.at(vert_indices.at(0)-1),
                    &points.at(vert_indices.at(1)-1),
                    &points.at(vert_indices.at(2)-1),
                    vert_indices.at(0)-1,
                    vert_indices.at(1)-1,
                    vert_indices.at(2)-2
                ));
            }
        }
    }
}