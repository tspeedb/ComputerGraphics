/***
 Assignment-2: Rotating a Cube in 3-Dimensional Space

 Name: Bennett, Tommy

 Collaborators: N/A

 Project Summary: Created a 3D cube to exhibit rotation in the x, y, and z degrees.
 ***/

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

//#pragma GCC diagnostic pop

#include <math.h>
#include <vector>
using namespace std;


float theta = 0.0;

// Converts degrees to radians for rotation
float deg2rad(float d) {
    return (d*M_PI)/180.0;
}

// Converts a vector to an array
GLfloat* vector2array(vector<GLfloat> vec) {
    GLfloat* arr = new GLfloat[vec.size()];
    for (int i = 0; i < vec.size(); i++) {
        arr[i] = vec[i];
    }
    return arr;
}

// Converts Cartesian coordinates to homogeneous coordinates
vector<GLfloat> to_homogenous_coord(vector<GLfloat> cartesian_coords) {
    
    vector<GLfloat> result;

    //Append the 1 in the 4th dimension to generate homoegenous coordinates
    for(int i = 0; i < cartesian_coords.size(); i+=3){
        result.push_back(cartesian_coords[i]);
        result.push_back(cartesian_coords[i+1]);
        result.push_back(cartesian_coords[i+2]);
        result.push_back(+1.0);
    }

    return result;
}

// Converts Cartesian coordinates to homogeneous coordinates
vector<GLfloat> to_cartesian_coord(vector<GLfloat> homogenous_coords) {
    vector<GLfloat> result;

    //Remove the 1 in the 4th dimension to generate Cartesian coordinates
    for(int i = 0; i < homogenous_coords.size(); i++){
        if((i + 1) % 4 != 0){
            result.push_back(homogenous_coords[i]);
        }
    }
    return result;
}

// Definition of a rotation matrix about the x-axis theta degrees
vector<GLfloat> rotation_matrix_x (float theta) {
    vector<GLfloat> rotate_mat_x = {
        +1.0, +0.0, +0.0, +0.0,
        +0.0, cos(theta), -sin(theta), +0.0,
        +0.0, sin(theta), cos(theta), +0.0,
        +0.0, +0.0, +0.0, +1.0
    };

    //Define the rotation matrix about the x-axis

    return rotate_mat_x;
}

// Definition of a rotation matrix along the y-axis by theta degrees
vector<GLfloat> rotation_matrix_y (float theta) {
    vector<GLfloat> rotate_mat_y = {
           cos(theta), +0.0, sin(theta), +0.0,
           +0.0, +1.0, +0.0, +0.0,
           -sin(theta), +0.0, cos(theta), +0.0,
           +0.0, +0.0, +0.0, +1.0
       };
    
    //Define the rotation matrix about the y-axis

    return rotate_mat_y;
}

// Definition of a rotation matrix along the z-axis by theta degrees
vector<GLfloat> rotation_matrix_z (float theta) {
    vector<GLfloat> rotate_mat_z= {
        cos(theta), -sin(theta), +0.0, +0.0,
        sin(theta), cos(theta), +0.0, +0.0,
        +0.0, +0.0, +1.0, +0.0,
        +0.0, +0.0, +0.0, +1.0
    };
    
    //Define the rotation matrix about the z-axis

    return rotate_mat_z;
}

// Perform matrix multiplication for A B
vector<GLfloat> mat_mult(vector<GLfloat> A, vector<GLfloat> B) {
    vector<GLfloat> result;
    
    //Compute matrix multiplication of A B (combnine???)

    for(int i = 0; i < B.size(); i += 4){
        result.push_back((A[0] * B[i]) + (A[1] * B[i+1]) + (A[2] * B[i+2]) + (A[3] * B[i+3]));
        result.push_back((A[4] * B[i]) + (A[5] * B[i+1]) + (A[6] * B[i+2]) + (A[7] * B[i+3]));
        result.push_back((A[8] * B[i]) + (A[9] * B[i+1]) + (A[10] * B[i+2]) + (A[11] * B[i+3]));
        result.push_back((A[12] * B[i]) + (A[13] * B[i+1]) + (A[14] * B[i+2]) + (A[15] * B[i+3]));
    }
    
    return result;
}

void setup() {
    // Enable the vertex array functionality
    glEnableClientState(GL_VERTEX_ARRAY);
    // Enable the color array functionality (so we can specify a color for each vertex)
    glEnableClientState(GL_COLOR_ARRAY);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Set up some default base color
    glColor3f(0.5, 0.5, 0.5);
    // Set up white background
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void init_camera() {
    // Camera parameters
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a 50 degree field of view, 1:1 aspect ratio, near and far planes at 3 and 7
    gluPerspective(50.0, 1.0, 2.0, 10.0);
    // Position camera at (2, 3, 5), attention at (0, 0, 0), up at (0, 1, 0)
    gluLookAt(2.0, 6.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display_func() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // World model parameters
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    vector<GLfloat> points = {
        // Front plane
        +1.0,   +1.0,   +1.0,
        -1.0,   +1.0,   +1.0,
        -1.0,   -1.0,   +1.0,
        +1.0,   -1.0,   +1.0,
        // Back plane
        +1.0,   +1.0,   -1.0,
        -1.0,   +1.0,   -1.0,
        -1.0,   -1.0,   -1.0,
        +1.0,   -1.0,   -1.0,
        // Right
        +1.0,   +1.0,   -1.0,
        +1.0,   +1.0,   +1.0,
        +1.0,   -1.0,   +1.0,
        +1.0,   -1.0,   -1.0,
        // Left
        -1.0,   +1.0,   -1.0,
        -1.0,   +1.0,   +1.0,
        -1.0,   -1.0,   +1.0,
        -1.0,   -1.0,   -1.0,
        // Top
        +1.0,   +1.0,   +1.0,
        -1.0,   +1.0,   +1.0,
        -1.0,   +1.0,   -1.0,
        +1.0,   +1.0,   -1.0,
        // Bottom
        +1.0,   -1.0,   +1.0,
        -1.0,   -1.0,   +1.0,
        -1.0,   -1.0,   -1.0,
        +1.0,   -1.0,   -1.0,
    };

    GLfloat colors[] = {
        // Front plane
        1.0,    0.0,    0.0,
        1.0,    0.0,    0.0,
        1.0,    0.0,    0.0,
        1.0,    0.0,    0.0,
        // Back plane
        0.0,    1.0,    0.0,
        0.0,    1.0,    0.0,
        0.0,    1.0,    0.0,
        0.0,    1.0,    0.0,
        // Right
        0.0,    0.0,    1.0,
        0.0,    0.0,    1.0,
        0.0,    0.0,    1.0,
        0.0,    0.0,    1.0,
        // Left
        1.0,    1.0,    0.0,
        1.0,    1.0,    0.0,
        1.0,    1.0,    0.0,
        1.0,    1.0,    0.0,
        // Top
        1.0,    0.0,    1.0,
        1.0,    0.0,    1.0,
        1.0,    0.0,    1.0,
        1.0,    0.0,    1.0,
        // Bottom
        0.0,    1.0,    1.0,
        0.0,    1.0,    1.0,
        0.0,    1.0,    1.0,
        0.0,    1.0,    1.0,
    };

    //Apply rotation(s) to the set of points
    vector<GLfloat> homogeneous_points = to_homogenous_coord(points);

    vector<GLfloat> x_rotated_points = mat_mult(rotation_matrix_x(deg2rad(theta)), homogeneous_points);
    vector<GLfloat> y_rotated_points = mat_mult(rotation_matrix_y(deg2rad(theta)), x_rotated_points);
    vector<GLfloat> z_rotated_points = mat_mult(rotation_matrix_z(deg2rad(theta)), y_rotated_points);
    points = to_cartesian_coord(z_rotated_points);

    GLfloat* vertices = vector2array(points);

    glVertexPointer(3,          // 3 components (x, y, z)
                    GL_FLOAT,   // Vertex type is GL_FLOAT
                    0,          // Start position in referenced memory
                    vertices);  // Pointer to memory location to read from

    //pass the color pointer
    glColorPointer(3,           // 3 components (r, g, b)
                   GL_FLOAT,    // Vertex type is GL_FLOAT
                   0,           // Start position in referenced memory
                   colors);     // Pointer to memory location to read from

    // Draw quad point planes: each 4 vertices
    glDrawArrays(GL_QUADS, 0, 4*6);

    glFlush();			//Finish rendering
    glutSwapBuffers();
}

void idle_func() {
    theta = theta+0.3;
    display_func();
}

int main (int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    // Create a window with rendering context and everything else we need
    glutCreateWindow("Assignment 2");

    setup();
    init_camera();

    // Set up our display function
    glutDisplayFunc(display_func);
    glutIdleFunc(idle_func);
    // Render our world
    glutMainLoop();
    return 0;
}

