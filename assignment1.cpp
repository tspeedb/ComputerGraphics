/***
 assignment1.cpp
 Assignment-1: Cartoonify

 Name: Bennett, Tommy

 Project Summary: Homer Simpson's face created using Chaikin's algorithm used iteratively
 ***/

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <iostream>
using namespace std;

class Vertex {
    GLfloat x, y;
public:
    Vertex(GLfloat, GLfloat);
    GLfloat get_y() { return y; };
    GLfloat get_x() { return x; };
};

Vertex::Vertex(GLfloat X, GLfloat Y) {
    x = X;
    y = Y;
}

void setup() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

vector<Vertex> generate_points(vector<Vertex> control_points) {
    vector<Vertex> newPoints;
    newPoints.push_back(control_points.at(0));

    for(int i = 0; i < (control_points.size()-1); i++) {
        //Distance between two points by x and y
        float x1Distance = (control_points[i+1].get_x() - control_points[i].get_x())* 0.25;
        float y1Distance = (control_points[i+1].get_y() - control_points[i].get_y())* 0.25;
        float x2Distance = (control_points[i+1].get_x() - control_points[i].get_x())* 0.75;
        float y2Distance = (control_points[i+1].get_y() - control_points[i].get_y())* 0.75;

        //New points created @ 1/4 and 3/4
        Vertex p0 = Vertex(control_points[i].get_x() + x1Distance, control_points[i].get_y() + y1Distance);
        Vertex p1 = Vertex(control_points[i].get_x() + x2Distance, control_points[i].get_y() + y2Distance);

        newPoints.push_back(p0);
        newPoints.push_back(p1);
    }
    newPoints.push_back(control_points.back());
    return newPoints;

    //return points;
}

void draw_curve(vector<Vertex> control_points, int n_iter) {

    // TODO:
    // Draw a Chaikin or Bezier curve based on the given control points
    
    vector<Vertex> newPoints = control_points;
    vector<Vertex> generatedPoints;

    glBegin(GL_LINES);
    for(int i = 0; i < n_iter; i++) {
        generatedPoints = generate_points(newPoints);
        newPoints = generatedPoints;
    }

    for (int i = 0; i < newPoints.size() - 1; i++) {
        glVertex2f(newPoints[i].get_x(), newPoints[i].get_y());
        glVertex2f(newPoints[i + 1].get_x(), newPoints[i + 1].get_y());
    }
    glEnd();
    

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set our color to black (R, G, B)
    glColor3f(0.0f, 0.0f, 0.0f);

    // TODO:
    // Draw cartoon
    
    //THIS IS WHERE YOU DRAW THE CHARACTER
    
    vector < vector<Vertex> > originalPoints;
    vector<Vertex> headPoints;
    
    // Head
    headPoints.push_back(Vertex(0.226f, 0.22f));
    headPoints.push_back(Vertex(0.26f, 0.239f));
    headPoints.push_back(Vertex(0.206f, 0.302f));
    headPoints.push_back(Vertex(0.19f, 0.31f));
    headPoints.push_back(Vertex(0.159f, 0.4f));
    headPoints.push_back(Vertex(0.116f, 0.47f));
    headPoints.push_back(Vertex(0.1f, 0.49f));
    headPoints.push_back(Vertex(0.08f, 0.51f));
    headPoints.push_back(Vertex(0.042f, 0.535f));
    headPoints.push_back(Vertex(0.012f, 0.55f));
    headPoints.push_back(Vertex(-0.0125f, 0.56f));
    headPoints.push_back(Vertex(-0.09f, 0.57f));
    headPoints.push_back(Vertex(-0.16f, 0.562f));
    headPoints.push_back(Vertex(-0.2f, 0.554f));
    headPoints.push_back(Vertex(-0.26f, 0.53f));
    headPoints.push_back(Vertex(-0.3f, 0.51f));
    headPoints.push_back(Vertex(-0.35f, 0.472f));
    headPoints.push_back(Vertex(-0.41f, 0.4f));
    headPoints.push_back(Vertex(-0.43f, 0.364f));
    headPoints.push_back(Vertex(-0.44f, 0.33f));
    headPoints.push_back(Vertex(-0.45f, 0.3f));
    headPoints.push_back(Vertex(-0.45f, 0.27f));
    headPoints.push_back(Vertex(-0.45f, 0.24f));
    headPoints.push_back(Vertex(-0.435f, 0.182f));
    headPoints.push_back(Vertex(-0.42f, 0.136f));
    headPoints.push_back(Vertex(-0.4f, 0.09f));
    headPoints.push_back(Vertex(-0.3f, -0.14f));
    headPoints.push_back(Vertex(-0.333f, -0.2f));
    headPoints.push_back(Vertex(-0.258f, -0.275f));
    headPoints.push_back(Vertex(-0.23f, -0.4f));
    headPoints.push_back(Vertex(-0.222f, -0.54f));
    
    originalPoints.push_back(headPoints);
    
    //left eye
    vector<Vertex> leftEyePoints;
    leftEyePoints.push_back(Vertex(-0.24f, 0.07f));
    leftEyePoints.push_back(Vertex(-0.2f, 0.166f));
    leftEyePoints.push_back(Vertex(-0.15f, 0.202f));
    leftEyePoints.push_back(Vertex(-0.1f, 0.215f));
    leftEyePoints.push_back(Vertex(-0.02f, 0.198f));
    leftEyePoints.push_back(Vertex(.05f, 0.1f));
    leftEyePoints.push_back(Vertex(.05f, 0.05f));
    leftEyePoints.push_back(Vertex(0.0f, -0.026f));
    leftEyePoints.push_back(Vertex(-0.06f, -0.057f));
    leftEyePoints.push_back(Vertex(-0.18f, -0.034f));
    leftEyePoints.push_back(Vertex(-0.215f, 0.0f));
    leftEyePoints.push_back(Vertex(-0.23f, 0.025f));
    leftEyePoints.push_back(Vertex(-0.24f, 0.07f));
    
    originalPoints.push_back(leftEyePoints);
    
    //left pupil
    vector<Vertex> leftPupilPoints;
    leftPupilPoints.push_back(Vertex(-0.11f, 0.047f));
    leftPupilPoints.push_back(Vertex(-0.127f, 0.065f));
    leftPupilPoints.push_back(Vertex(-0.11f, 0.083f));
    leftPupilPoints.push_back(Vertex(-0.091f, 0.065f));
    leftPupilPoints.push_back(Vertex(-0.11f, 0.047f));
    originalPoints.push_back(leftPupilPoints);

    //right eye
    vector<Vertex> rightEyePoints;
    rightEyePoints.push_back(Vertex(0.02f, 0.17f));
    rightEyePoints.push_back(Vertex(0.08f, 0.228f));
    rightEyePoints.push_back(Vertex(0.15f, 0.246f));
    rightEyePoints.push_back(Vertex(0.21f, 0.23f));
    rightEyePoints.push_back(Vertex(0.25f, 0.2f));
    rightEyePoints.push_back(Vertex(0.278f, 0.14f));
    rightEyePoints.push_back(Vertex(0.273f, 0.08f));
    rightEyePoints.push_back(Vertex(0.251f, 0.04f));
    rightEyePoints.push_back(Vertex(0.228f, 0.023f));
    originalPoints.push_back(rightEyePoints);

    //right pupil
    vector<Vertex> rightPupilPoints;
    rightPupilPoints.push_back(Vertex(0.195f, 0.11f));
    rightPupilPoints.push_back(Vertex(0.177f, 0.128f));
    rightPupilPoints.push_back(Vertex(0.195f, 0.147f));
    rightPupilPoints.push_back(Vertex(0.214f, 0.128f));
    rightPupilPoints.push_back(Vertex(0.195f, 0.11f));
    originalPoints.push_back(rightPupilPoints);
    
    
        
    //upper lip
    vector<Vertex> upperLipPoints;
    upperLipPoints.push_back(Vertex(-0.14f, -0.327f));
    upperLipPoints.push_back(Vertex(-0.05f, -0.35f));
    upperLipPoints.push_back(Vertex(0.02f, -0.355f));
    upperLipPoints.push_back(Vertex(0.276f, -0.328f));
    upperLipPoints.push_back(Vertex(0.385f, -0.28f));
    upperLipPoints.push_back(Vertex(0.394f, -0.255f));
    upperLipPoints.push_back(Vertex(0.39f, -0.235f));
    upperLipPoints.push_back(Vertex(0.368f, -0.216f));
    upperLipPoints.push_back(Vertex(0.35f, -0.16f));
    upperLipPoints.push_back(Vertex(0.285f, -0.07f));
    upperLipPoints.push_back(Vertex(0.259f, -0.05f));
    upperLipPoints.push_back(Vertex(0.23f, -0.034));
    
    
    originalPoints.push_back(upperLipPoints);
    
    //bottom lip  + nose
    vector<Vertex> bottomLipPoints;
    bottomLipPoints.push_back(Vertex(0.276f, -0.328f));
    bottomLipPoints.push_back(Vertex(0.278f, -0.36f));
    bottomLipPoints.push_back(Vertex(0.245f, -0.4f));
    bottomLipPoints.push_back(Vertex(0.208f, -0.472f));
    bottomLipPoints.push_back(Vertex(0.15f, -0.512f));
    bottomLipPoints.push_back(Vertex(-0.06f, -0.505f));
    bottomLipPoints.push_back(Vertex(-0.18f, -0.39f));
    bottomLipPoints.push_back(Vertex(-0.2f, -0.315f));
    bottomLipPoints.push_back(Vertex(-0.15f, -0.173f));
    bottomLipPoints.push_back(Vertex(-0.04f, -0.11f));
    bottomLipPoints.push_back(Vertex(0.05f, -0.096f));
    bottomLipPoints.push_back(Vertex(0.2f, -0.065f));
    bottomLipPoints.push_back(Vertex(0.23f, -0.034));
    bottomLipPoints.push_back(Vertex(0.228f, 0.023f));
    bottomLipPoints.push_back(Vertex(0.2f, 0.05f));
    bottomLipPoints.push_back(Vertex(0.16f, 0.054f));
    bottomLipPoints.push_back(Vertex(0.1f, 0.04f));
    bottomLipPoints.push_back(Vertex(0.045f, 0.035f));
    
    originalPoints.push_back(bottomLipPoints);

    //cheek
    vector<Vertex> cheekPoints;
    cheekPoints.push_back(Vertex(0.251f, 0.04f));
    cheekPoints.push_back(Vertex(0.263f, 0.02f));
    cheekPoints.push_back(Vertex(0.27f, 0.0f));
    cheekPoints.push_back(Vertex(0.272f, -0.018f));
    cheekPoints.push_back(Vertex(0.269f, -0.035f));
    cheekPoints.push_back(Vertex(0.259f, -0.05f));
    
    originalPoints.push_back(cheekPoints);
    
    //neck
    vector<Vertex> neckPoints;
    neckPoints.push_back(Vertex(0.208f, -0.472f));
    neckPoints.push_back(Vertex(0.227f, -0.54f));
    neckPoints.push_back(Vertex(0.265f, -0.605f));
    
    originalPoints.push_back(neckPoints);
    
    //hair piece 1
    vector<Vertex> hairPoints;
    hairPoints.push_back(Vertex(-0.38f, 0.366f));
    hairPoints.push_back(Vertex(-0.405f, 0.405f));
    hairPoints.push_back(Vertex(-0.413f, 0.5f));
    hairPoints.push_back(Vertex(-0.38f, 0.556f));
    hairPoints.push_back(Vertex(-0.32f, 0.585f)); //BOTH
    hairPoints.push_back(Vertex(-0.25f, 0.574f));
    hairPoints.push_back(Vertex(-0.22f, 0.548f));
    originalPoints.push_back(hairPoints);
    
    //hair piece 2
    vector<Vertex> hairPoints2;
    hairPoints2.push_back(Vertex(-0.323f, 0.428f));
    hairPoints2.push_back(Vertex(-0.343f, 0.478f));
    hairPoints2.push_back(Vertex(-0.344f, 0.52f));
    hairPoints2.push_back(Vertex(-0.32f, 0.585f)); //B
    hairPoints2.push_back(Vertex(-0.22f, 0.636f));
    hairPoints2.push_back(Vertex(-0.155f, 0.62f));
    hairPoints2.push_back(Vertex(-0.112f, 0.568f));
    originalPoints.push_back(hairPoints2);
    
    //hair 3
    vector<Vertex> hairPoints3;
    hairPoints3.push_back(Vertex(-0.23f, -0.06f));
    hairPoints3.push_back(Vertex(-0.305f, 0.035f));
    hairPoints3.push_back(Vertex(-0.31f, -0.085f));
    hairPoints3.push_back(Vertex(-0.383f, -0.022f));
    hairPoints3.push_back(Vertex(-0.362f, -0.137f));
    originalPoints.push_back(hairPoints3);
    
    //ear top
    vector<Vertex> earPoints;
    earPoints.push_back(Vertex(-0.3f, -0.2f));
    earPoints.push_back(Vertex(-0.282f, -0.19f));
    earPoints.push_back(Vertex(-0.26f, -0.2f));
    originalPoints.push_back(earPoints);
    
    //ear bot
    vector<Vertex> earPoints2;
    earPoints2.push_back(Vertex(-0.282f, -0.19f));
    earPoints2.push_back(Vertex(-0.283f, -0.208f));
    earPoints2.push_back(Vertex(-0.275f, -0.23f));
    originalPoints.push_back(earPoints2);
    
    
    for (int i = 0; i < originalPoints.size(); i++) {
         vector<Vertex> points_i = originalPoints[i];
         vector<Vertex> points_to_draw = generate_points(points_i);
         draw_curve(points_to_draw, 10);
     }

    
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 600); // Set your own window size
    glutCreateWindow("Assignment 1");
    setup();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

