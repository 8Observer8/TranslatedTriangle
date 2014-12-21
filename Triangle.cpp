#include "Triangle.h"

Triangle::Triangle() :
    m_x0( -0.5f ),
    m_y0( -0.5f ),
    m_size( 1.0f )
{
    initVertices();
    initColors();
}

void Triangle::initVertices()
{
    vertices.clear();
    vertices.resize( 9 );

    // 0
    vertices[0] = m_x0;
    vertices[1] = m_y0;
    vertices[2] = 0.0f;

    // 1
    vertices[3] = m_x0 + m_size;
    vertices[4] = m_y0;
    vertices[5] = 0.0f;

    // 2
    vertices[6] = m_x0;
    vertices[7] = m_y0 + m_size;
    vertices[8] = 0.0f;
}

void Triangle::initColors()
{
    colors.clear();
    colors.resize( 9 );

    // 0
    colors[0] = 1.0f;
    colors[1] = 0.0f;
    colors[2] = 0.0f;

    // 1
    colors[3] = 0.0f;
    colors[4] = 1.0f;
    colors[5] = 0.0f;

    // 2
    colors[6] = 0.0f;
    colors[7] = 0.0f;
    colors[8] = 1.0f;
}

void Triangle::setX0( float x )
{
    m_x0 = x;
    initVertices();
}

void Triangle::setY0( float y )
{
    m_y0 = y;
    initVertices();
}

float Triangle::x0() const
{
    return m_x0;
}

float Triangle::y0() const
{
    return m_y0;
}
