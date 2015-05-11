#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

/* GLobal Variables */
unsigned char* pixels;
int width, height;
bool click = false;
//////////////////////////////////////////////////////////////////////////////////
// Draws to the OpenGL window
//////////////////////////////////////////////////////////////////////////////////
void display()
{
  //glClearColor(0,0,0,0);
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    
    
    /* Draws Picture in GLUT */
    glRasterPos2d(-1.0,1.0);
    glPixelZoom(1.0,-1.0);
    glDrawPixels(width,height,GL_RGB,GL_UNSIGNED_BYTE,pixels);
  glutSwapBuffers();
}

void writePPM(const char* filename, unsigned char*& pixels, int& width, int& height);
//////////////////////////////////////////////////////////////////////////////////
// Handles keyboard events
//////////////////////////////////////////////////////////////////////////////////
void keyboard(unsigned char k, int x, int y)
{
  switch (k)
  {
    // the escape key and 'q' quit the program
    case 27:
    case 'q':
      exit(0);
      break;
    case 'w':
          writePPM("output.ppm", pixels, width, height);
  }
  glutPostRedisplay();
}

//////////////////////////////////////////////////////////////////////////////////
// Called occasionally to see if anything's happening
//////////////////////////////////////////////////////////////////////////////////
void idle()
{
  glutPostRedisplay();
}

//////////////////////////////////////////////////////////////////////////////////
// Called if a mouse button is pressed
//////////////////////////////////////////////////////////////////////////////////
void mouseButton(int button, int state, int x, int y)
{
    /* checks to see if mouse button is pressed if yes it changes pixels and changes a boolean variable to true */
    switch (button) {
        case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN) {
        for (int i=-5; i<6; i++) {
            for (int j=-5; j<6; j++) {
                
                int xoff= (x+i)*3;
                int yoff= width*(y+j)*3;
                if ((x+i >= 0) && (y+j >= 0) && (x+i < width) && (y+j  < height)) {
                pixels[xoff+yoff] = 255;
                pixels[xoff+yoff+1] = 0;
                pixels[xoff+yoff+2] = 0;
                }
            }
        }
        click = true;

    }
    else   {
        click = false;
    }
            break;
    }
}

//////////////////////////////////////////////////////////////////////////////////
// Called if the mouse moves
//////////////////////////////////////////////////////////////////////////////////
void mouseMotion(int x, int y){
    /* if boolean variable is true it continues to change pixels at location */
        if (click == true) {
            for (int i=-5; i<6; i++) {
                for (int j=-5; j<6; j++) {
                    
                    int xoff= (x+i)*3;
                    int yoff= width*(y+j)*3;
                    if ((x+i >= 0) && (y+j >= 0) && (x+i < width) && (y+j  < height)) {
                        pixels[xoff+yoff] = 255;
                        pixels[xoff+yoff+1] = 0;
                        pixels[xoff+yoff+2] = 0;
                    }
                }
            }
        }
}

//////////////////////////////////////////////////////////////////////////////////
// Read in a raw PPM file of the "P6" style.
//
// Input: "filename" is the name of the file you want to read in
// Output: "pixels" will point to an array of pixel values
//         "width" will be the width of the image
//         "height" will be the height of the image
//
// The PPM file format is:
//
//   P6
//   <image width> <image height>
//   255
//   <raw, 8-bit binary stream of RGB values>
//
// Open one in a text editor to see for yourself.
//
//////////////////////////////////////////////////////////////////////////////////
void readPPM(const char* filename, unsigned char*& pixels, int& width, int& height)
{
  // try to open the file
  FILE* file;
  file = fopen(filename, "rb");
  if (file == NULL)
  {
    cout << " Couldn't open file " << filename << "! " << endl;
    exit(1);
  }

  // read in the image dimensions
  fscanf(file, "P6\n%d %d\n255\n", &width, &height);
  int totalPixels = width * height;

  // allocate three times as many pixels since there are R,G, and B channels
  pixels = new unsigned char[3 * totalPixels];
  fread(pixels, 1, 3 * totalPixels, file);
  fclose(file);
  
  // output some success information
  cout << " Successfully read in " << filename << " with dimensions: " 
       << width << " " << height << endl;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void writePPM(const char* filename, unsigned char*& pixels, int& width, int& height)
{
    // try to open the file
    FILE* file;
    file = fopen(filename, "w");
    if (file == NULL)
    {
        cout << " Couldn't open file " << filename << "! " << endl;
        exit(1);
    }
    
    // read in the image dimensions
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    int totalPixels = width * height;
    
    // allocate three times as many pixels since there are R,G, and B channels
    //pixels = new unsigned char[3 * totalPixels];
    fwrite(pixels, 1, 3 * totalPixels, file);
    fclose(file);
    
    // output some success information
    cout << " Successfully read in " << filename << " with dimensions: "
    << width << " " << height << endl;
}



int main(int argc, char** argv)
{

  // Example of reading in an image. Uncomment if you're already converted
  // the JPG file.
  //unsigned char* pixels;
  //int width, height;
  readPPM("input.ppm", pixels, width, height);
    //n=width;
    //m=height;
    //k=pixels;
    
  glutInit(&argc, argv);
  glutInitWindowSize(width,height);
  glutInitWindowPosition(width,height);
  glutCreateWindow("CMPSC 180, Homework 0");
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//glDrawPixels(width,height,GL_RGB,GL_UNSIGNED_INT,pixels);
  glutDisplayFunc(display);
  glutMotionFunc(mouseMotion);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);

  glutMainLoop();

  return 0;
}
