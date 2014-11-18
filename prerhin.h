/*
 * @file:   perrhin.h
 * @author: ChenYang
 * @date:   2014/11/18
 * @brief:
 */

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

class Rhin {
public:
    Rhin();
    virtual ~Rhin();

    bool init();
    bool close();
    
    void setupProjection(int width, int height);
    void reshape(int width, int height);
   
    void prepare(float dt);
    void render();

    void drawCube();
    void leftButtonDown(int x, int y);

    void mouseMove(int x, int y);

    void setCamera(GLfloat p, GLfloat t);

private:
    int windowWidth;
    int windowHeight;

};

#endif // prerhin.h