#include "camera.hpp"

Camera::Camera(Eigen::Vector3f origin, Eigen::Vector3f forwards, Eigen::Vector3f up, Eigen::Vector3f right, float fov) :
origin(origin), forwards(forwards), up(up), right(right), fov(fov) {
    update_cob();
}

void Camera::update_cob() {
    cob_cam_2_world.col(0) = forwards;
    cob_cam_2_world.col(1) = up;
    cob_cam_2_world.col(2) = right;

    cob_world_2_cam = cob_cam_2_world.inverse().eval();
}

float Camera::angle_between(Eigen::Vector3f v1, Eigen::Vector3f v2) {
    return acos(std::clamp(v1.normalized().dot(v2.normalized()), -1.f, 1.f));
}

bool Camera::get_alpha_beta(Eigen::Vector3f vert, float* alpha, float* beta) {
    Eigen::Vector3f delta_a = vert - origin; // Vector from origin to vertex
    Eigen::Vector3f delta_a_std = cob_world_2_cam * delta_a; // delta_a with respect to standard axes
    
    *alpha = atanf(delta_a_std(1)/delta_a_std(0));
    *beta = atanf(delta_a_std(2)/delta_a_std(0));

    return fabs(*alpha) > fov/2 || fabs(*beta) > fov/2 || delta_a_std(0) < 0;
}

void Camera::render(sf::RenderTarget* target, Model& model) {
    target->clear(sf::Color::Black); // Fill background
    sf::VertexArray lines(sf::Lines, model.get_edges().size() * 2);
    sf::VertexArray face_vertices(sf::Triangles, model.get_faces().size() * 3);

    sf::VertexArray point_pixels(sf::Points, model.get_points().size());
    std::vector<bool> visibilities;

    size_t p = 0;
    for (auto it = model.get_points().begin(); it != model.get_points().end(); it++, p++) {
        float alpha, beta;
        bool behind_cam;

        behind_cam = get_alpha_beta(*it, &alpha, &beta);
        visibilities.push_back(!behind_cam);
        
        sf::Vector2f px(
            (target->getSize().x / 2) * (beta / (fov/2)) + (target->getSize().x / 2),
            (target->getSize().y / 2) - ((target->getSize().x / 2) * (alpha / (fov/2)))
        );

        point_pixels[p].position = px;
        point_pixels[p].color = sf::Color::Blue;
    }

    size_t e = 0;
    for (auto it = model.get_edges().begin(); it != model.get_edges().end(); it++, e+=2) {
        if (!visibilities.at(it->ai) && !visibilities.at(it->bi)) continue; // Pass if both vertices aren't visible

        lines[e].position = point_pixels[it->ai].position;
        lines[e+1].position = point_pixels[it->bi].position;
        lines[e].color = lines[e+1].color = sf::Color::Red;
    }

    size_t f = 0;
    for (auto it = model.get_faces().begin(); it != model.get_faces().end(); it++, f+=3) {
        if (!visibilities.at(it->p1i) && !visibilities.at(it->p2i) && !visibilities.at(it->p3i)) continue;

        face_vertices[f].position = point_pixels[it->p1i].position;
        face_vertices[f+1].position = point_pixels[it->p2i].position;
        face_vertices[f+2].position = point_pixels[it->p3i].position;

        face_vertices[f].color = face_vertices[f+1].color = face_vertices[f+2].color = sf::Color(0xffffff44);
    }

    target->draw(lines);
    //target->draw(face_vertices);
}

void Camera::translate(Eigen::Vector3f delta) {
    origin += delta;
    update_cob();
}

void Camera::translate(float x, float y, float z) {
    origin(0) += x;
    origin(1) += y;
    origin(2) += z;
    update_cob();
}

void Camera::rotate(float x, float y, float z) {
    Eigen::Matrix3f R_x, R_y, R_z, R;

    R_x <<  1, 0, 0,
            0, cosf(x), -sinf(x),
            0, sinf(x), cosf(x);

    R_y <<  cosf(y), 0, sinf(y),
            0, 1, 0,
            -sinf(y), 0, cosf(y);

    R_z <<  cosf(z), -sinf(z), 0,
            sinf(z), cosf(z), 0,
            0, 0, 1;

    R = R_z * R_y * R_x;

    forwards = R * forwards;
    up = R * up;
    right = R * right;

    update_cob();
}

void Camera::translate_along_direction(float x, float y, float z) {
    translate(x*forwards + y*up + z*right);
}