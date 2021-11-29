#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <QColor>

struct Element
{
    std::pair<float, float> m_coords;
    std::pair<float, float> m_velocity;
    std::pair<float, float> m_acceleration;

    int m_radius;
    QColor m_color;

    Element(int radius, std::pair<float, float> coords, std::pair<float, float> velocity,
            std::pair<float, float> acceleration, QColor color = QColor(QString("#ff0000"))):
            m_coords(coords), m_velocity(velocity), m_acceleration(acceleration), m_radius(radius), m_color(color) {
    }
};

#endif // ELEMENT_H
