#include "camera.hpp"

Camera::Camera(Eigen::Vector3f origin, Eigen::Vector3f forwards, Eigen::Vector3f up, Eigen::Vector3f right, float fov) :
origin(origin), forwards(forwards), up(up), right(right), fov(fov) {}

float Camera::angle_between(Eigen::Vector3f v1, Eigen::Vector3f v2) {
    return acos(std::clamp(v1.normalized().dot(v2.normalized()), -1.f, 1.f));
}

void Camera::get_alpha_beta(Eigen::Vector3f vert, float* alpha, float* beta) {
    Eigen::Matrix3f cob; // Change-of-base matrix
    cob.col(0) = forwards;
    cob.col(1) = up;
    cob.col(2) = right;
    //cob = cob.inverse().eval();

    Eigen::Vector3f delta_a = vert - origin; // Vector from origin to vertex
    Eigen::Vector3f delta_a_std = cob * delta_a; // delta_a with respect to standard axes
    
    Eigen::Vector3f flat_delta_a; // A vector equal to `delta_a_std` except y component=0
    flat_delta_a(0) = delta_a_std(0);
    flat_delta_a(1) = 0;
    flat_delta_a(2) = delta_a_std(2);

    Eigen::Vector3f x_axis; // A vector representing the x-axis
    x_axis(0) = 1;
    x_axis(1) = 0;
    x_axis(2) = 0;

    *alpha = angle_between(delta_a, flat_delta_a);
    *beta  = angle_between(x_axis, flat_delta_a);
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
}

void Camera::translate(float x, float y, float z) {
    origin(0) += x;
    origin(1) += y;
    origin(2) += z;

    //std::cout << origin << std::endl;
}