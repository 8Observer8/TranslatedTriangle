#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

class Triangle
{
public:
    Triangle();

    void initVertices();
    void initColors();

    void setX0( float x );
    void setY0( float y );
    float x0() const;
    float y0() const;

    std::vector<float> vertices;
    std::vector<float> colors;

private:
    float m_x0;
    float m_y0;
    float m_size;
};

#endif // TRIANGLE_H
