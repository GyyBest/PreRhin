/********************************************************************
         @filename:  prerhin.h
         @author:    ChenYang
         @date:      2014/11/18   19:43
         @brief:	  
 ********************************************************************/

#ifndef __PRERHIN_H__
#define __PRERHIN_H__
    
#define PI          3.14159
#define TWO_PI      PI*2.0
#define HALF_PI     PI/2.0
#define DEG_TO_RAD  0.017453

struct MPoint {
    int x;
    int y;
};

struct Camera {
    GLfloat xeye;
    GLfloat yeye;
    GLfloat zeye;
};

struct SphericalCoords {
    float r;
    float phi;
    float theta;
};

class Vector3;
class Point3;

class Rhin {
public:
    Rhin();
    virtual ~Rhin();

    bool init();
    bool close();

    // When window size changed, resize it to ensure the 
    // image won't be distorted.
    void reshape(int width, int height);
   
    // Used to render scene
    void render();

    void drawVoxel(Vector3 v);
    
    // Draws a colorful cube
    void drawCube();

    // When left button is clicked, get down the position
    void leftButtonDown(int x, int y);

    // When right button is clicked, draw a voxel at where mouse clicked
    void rightButtonDown(Vector3 v);

    // While mouse moving, retrieves the mouse position (x,y) and convert it to 
    // spherical coords, then use it to set camera position in 3d space.
    void mouseMove(int x, int y);

    // Set camera's position in spherical coords.
    void setCamera(GLfloat p, GLfloat t);

    // While mouse moving, retrieves the mouse position (x, y) and convert it
    // from screen coordinate to OpenGL coordinate, return as type Vector3,
    // later will be used to draw other voxels.
    Vector3 getScreenPos(int x, int y);

private:
    int windowWidth;
    int windowHeight;

};

#endif // __PRERHIN_H__