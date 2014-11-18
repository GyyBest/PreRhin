#ifdef _WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "prerhin.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

struct SphericalCoords polar = {3.0f, 60.0f, 45.0f};
struct Camera          camera;
struct MPoint          oldPt = {-1, -1};
bool lBtnDn = false;

Rhin::Rhin()
{

}

Rhin::~Rhin()
{

}

bool Rhin::init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    return true;
}

bool Rhin::close()
{
    return true;
}


void Rhin::setupProjection(int width, int height)
{
    if (height == 0)    // don't want a divide by zero
        height = 1;
    glViewport(0, 0, width, height);    // reset the viewport to new
    glMatrixMode(GL_PROJECTION);    // set projection matrix 
    glLoadIdentity();   // reset projection matrix
    gluPerspective(52.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    windowWidth = width;
    windowHeight = height;
}

void Rhin::reshape(int width, int height)
{
    if (height == 0)    // don't want a divide by zero
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6.0, 6.0,-6.0, 6.0,-6.0, 6.0); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    windowWidth = width;
    windowHeight = height;
}


void Rhin::prepare(float dt)
{
}

void Rhin::render()
{
    /*
    // clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
    glLoadIdentity();

    // move back 5 units and rotate about all 3 axes
    glTranslatef(0.0, 0.0, -5.0f);
    glRotatef(m_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

    // lime greenish color
    glColor3f(0.7f, 1.0f, 0.3f);

    // draw the triangle such that the rotation point is in the center
    glBegin(GL_TRIANGLES);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
    */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.xeye,camera.yeye,camera.zeye, 0.0 , 0.0, 0.0, 0.0, 1.0, 0.0);
    */
    drawCube();
    //glDisable(GL_DEPTH_TEST);
}

void Rhin::drawCube()
{
    //glBegin(GL_QUADS);
    glBegin(GL_POLYGON);
    // front
    glColor3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    // left
    glColor3f( 1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    // back
    glColor3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    // right
    glColor3f( 1.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    // top
    glColor3f( 1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);
    // bottom
    glColor3f( 0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();
}


void Rhin::setCamera(GLfloat p, GLfloat t)
{
    GLfloat phi, theta;                  
    polar.phi += p;                  
    polar.theta += t;

    if (polar.phi > 360.0f) 
        polar.phi -= 360.0f;
    if (polar.phi < 0.0f) 
        polar.phi += 360.0f;
    if (polar.theta > 360.0f) 
        polar.theta -= 360.0f;
    if (polar.theta < 0.0f) 
        polar.theta += 360.0f;

    phi = polar.phi * DEG_TO_RAD;
    theta = polar.theta * DEG_TO_RAD;

    camera.xeye = polar.r * sin(theta) * cos(phi);      
    camera.zeye = polar.r * sin(theta) * sin(phi);
    camera.yeye = polar.r * cos(theta);                 
    render();  
}

void Rhin::mouseMove(int x, int y)
{
    if (lBtnDn) {
        setCamera(float(x-oldPt.x), float(oldPt.y - y));       
        oldPt.x = x;              
        oldPt.y = y;
    }
}

void Rhin::leftButtonDown(int x, int y)
{
    lBtnDn = true;
    oldPt.x = x;                      
    oldPt.y = y;
}
