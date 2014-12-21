#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QTimer>
#include "Triangle.h"

class Scene : public QOpenGLWidget
{
    Q_OBJECT

public:
    Scene( QWidget *parent = 0 );

private slots:
    void slotUpdate();

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void drawTriangle( const Triangle &triangle );

    void wheelEvent( QWheelEvent *event );
    void scalePlus();
    void scaleMinus();
    float m_scale;

    void mousePressEvent( QMouseEvent *event );
    QPoint m_lastPos;

    void mouseMoveEvent( QMouseEvent *event );
    float m_xRot;
    float m_zRot;

    QOpenGLShaderProgram m_program;

    int m_vertexAttr;
    int m_colorAttr;
    int m_matrixUniform;

    Triangle m_triangle;

    QTimer m_timer;
    float m_x0;
    float m_y0;
    float m_angle;
    float m_radius;
};

#endif // SCENE_H
