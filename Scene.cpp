#include <QMatrix4x4>
#include <cmath>
#include "Scene.h"

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_scale( 1.0f ),
    m_xRot( 0.0f ),
    m_zRot( 0.0f ),
    m_x0( 0.0f ),
    m_y0( 0.0f ),
    m_angle( 0.0f ),
    m_radius( 1.0f )
{
    connect( &m_timer, SIGNAL( timeout() ),
             this, SLOT( slotUpdate() ) );
    m_timer.start( 10 );
}

void Scene::slotUpdate()
{
    m_x0 = m_radius * std::cos( m_angle / M_PI );
    m_y0 = m_radius * std::sin( m_angle / M_PI );

    m_angle += 0.1f;

    if ( m_angle >= 360 )
        m_angle = 0;

    update();
}

void Scene::initializeGL()
{
    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile( ":/Shaders/vShader.glsl" );

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile( ":/Shaders/fShader.glsl" );

    m_program.addShader( &vShader );
    m_program.addShader( &fShader );
    if ( !m_program.link() )
    {
        qWarning( "Error: unable to link a shader program" );
        return;
    }

    m_vertexAttr = m_program.attributeLocation( "vertexAttr" );
    m_colorAttr = m_program.attributeLocation( "colorAttr" );
    m_matrixUniform = m_program.uniformLocation( "matrix" );

    glEnable( GL_DEPTH_TEST );
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( !m_program.bind() )
        return;

    QMatrix4x4 modelView;
    modelView.perspective( 60.0f, 4.0f / 3.0f, 0.1f, 400.0f );
    modelView.translate( m_x0, m_y0, -3.0f );
    modelView.scale( m_scale );
    modelView.rotate( m_xRot, 1.0f, 0.0f, 0.0f );
    modelView.rotate( m_zRot, 0.0f, 0.0f, 1.0f );
    m_program.setUniformValue( m_matrixUniform, modelView );

    drawTriangle( m_triangle );

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );
}

void Scene::drawTriangle( const Triangle &triangle )
{
    m_program.setAttributeArray( m_vertexAttr, triangle.vertices.data(), 3 );
    m_program.setAttributeArray( m_colorAttr, triangle.colors.data(), 3 );

    m_program.enableAttributeArray( m_vertexAttr );
    m_program.enableAttributeArray( m_colorAttr );

    glDrawArrays( GL_TRIANGLES, 0, triangle.vertices.size() / 3 );

    m_program.disableAttributeArray( m_vertexAttr );
    m_program.disableAttributeArray( m_colorAttr );
}

void Scene::wheelEvent( QWheelEvent *event )
{
    if ( event->delta() > 0 )
        scalePlus();
    else if ( event->delta() < 0 )
        scaleMinus();

    update();
}

void Scene::scalePlus()
{
    m_scale *= 1.1f;
}

void Scene::scaleMinus()
{
    m_scale /= 1.1;
}

void Scene::mousePressEvent( QMouseEvent *event )
{
    m_lastPos = event->pos();
}

void Scene::mouseMoveEvent( QMouseEvent *event )
{
    m_xRot += 180 / m_scale * ( float ) ( event->y() - m_lastPos.y() ) / height();
    m_zRot += 180 / m_scale * ( float ) ( event->x() - m_lastPos.x() ) / width();

    if ( m_xRot >= 360 )
        m_xRot = 0;

    if ( m_zRot >= 360 )
        m_zRot = 0;

    m_lastPos = event->pos();
    update();
}
