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

void Camera::get_alpha_beta(Eigen::Vector3f vert, float* alpha, float* beta) {
    Eigen::Vector3f delta_a = vert - origin; // Vector from origin to vertex
    Eigen::Vector3f delta_a_std = cob_world_2_cam * delta_a; // delta_a with respect to standard axes
    
    *alpha = atanf(delta_a_std(1)/delta_a_std(0));
    *beta = atanf(delta_a_std(2)/delta_a_std(0));
}

void Camera::render(sf::RenderTarget* target, std::vector<Edge> edges) {
    target->clear(sf::Color::Black); // Fill background
    sf::VertexArray lines(sf::Lines, edges.size() * 2);

    size_t e = 0; // Edge number
    for (auto it = edges.begin(); it != edges.end(); it++, e+=2) {
        float alpha_a, beta_a, 
                alpha_b, beta_b;
        get_alpha_beta(it->a, &alpha_a, &beta_a);
        get_alpha_beta(it->b, &alpha_b, &beta_b);

        sf::Vector2f px_a, px_b;
        px_a.x = (target->getSize().x / 2) * (beta_a / (fov/2)) + (target->getSize().x / 2);
        px_a.y = (target->getSize().y / 2) - ((target->getSize().x / 2) * (alpha_a / (fov/2)));

        px_b.x = (target->getSize().x / 2) * (beta_b / (fov/2)) + (target->getSize().x / 2);
        px_b.y = (target->getSize().y / 2) - ((target->getSize().x / 2) * (alpha_b / (fov/2)));

        lines[e].position = px_a;
        lines[e+1].position = px_b;
        lines[e].color = lines[e+1].color = sf::Color::White;
    }

    target->draw(lines);
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