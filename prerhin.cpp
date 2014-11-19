/********************************************************************
         @filename:  prerhin.cpp
         @author:    ChenYang
         @date:      2014/11/18   20:01
         @brief:     
 ********************************************************************/

#ifdef _WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "prerhin.h"
#include "vector3.h"
#include "point3.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

struct SphericalCoords polar = {3.0f, 60.0f, 45.0f};
struct Camera          camera;
struct MPoint          oldPt = {-1, -1};

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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
//    gluLookAt(camera.xeye,camera.yeye,camera.zeye, 0.0 , 0.0, 0.0, 0.0, 1.0, 0.0);
    return true;
}

bool Rhin::close()
{
    return true;
}


void Rhin::reshape(int width, int height)
{
    if (height == 0)    // don't want a divide by zero
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    windowWidth = width;
    windowHeight = height;
}


void Rhin::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.xeye, camera.yeye, camera.zeye,  // camera position
              0.0 , 0.0, 0.0, // center position
              0.0, 1.0, 0.0); // up vector
    
    drawCube();
}

void Rhin::drawCube()
{
    glBegin(GL_QUADS);
    //glBegin(GL_POLYGON);
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

void Rhin::drawVoxel(Vector3 v)
{
    glPushMatrix();
    //glTranslatef(v.x, v.y, v.z);
    drawCube();
    glPopMatrix();
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
        setCamera(float(x-oldPt.x), float(oldPt.y - y));       
        oldPt.x = x;              
        oldPt.y = y;
}

void Rhin::leftButtonDown(int x, int y)
{
    oldPt.x = x;                      
    oldPt.y = y;
}


void Rhin::rightButtonDown(Vector3 v)
{
    Vector3 rvec = Vector3(v.x-0, v.y-0, v.z-0);
    if (rvec.length() >= 1) {
        glTranslatef(v.x, v.y, v.z);
        drawCube();
    }
}


Vector3 Rhin::getScreenPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, modelview, projection, viewport,
        &posX, &posY, &posZ);
    return Vector3(posX, posY, posZ);
}
