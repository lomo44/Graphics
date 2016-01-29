/***********************************************************
             CSC418/2504, Fall 2011

                 robot.cpp

       Simple demo program using OpenGL and the glut/glui
       libraries


    Instructions:
        Please read the assignment page to determine
        exactly what needs to be implemented.  Then read
        over this file and become acquainted with its
        design.

        Add source code where it appears appropriate. In
        particular, see lines marked 'TODO'.

        You should not need to change the overall structure
        of the program. However it should be clear what
        your changes do, and you should use sufficient comments
        to explain your code.  While the point of the assignment
        is to draw and animate the character, you will
        also be marked based on your design.

		Some windows-specific code remains in the includes;
		we are not maintaining windows build files this term,
		but we're leaving that here in case you want to try building
		on windows on your own.

***********************************************************/

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef _WIN32
#include <unistd.h>
#else
void usleep(unsigned int nanosec)
{
    Sleep(nanosec / 1000);
}
#endif


// *************** GLOBAL VARIABLES *************************


const float PI = 3.14159;

// --------------- USER INTERFACE VARIABLES -----------------

// Window settings
int windowID;               // Glut window ID (for display)
GLUI *glui;                 // Glui window (for controls)
int Win[2];                 // window (x,y) size


// ---------------- ANIMATION VARIABLES ---------------------

// Animation settings
int animate_mode = 0;       // 0 = no anim, 1 = animate
int animation_frame = 0;      // Specify current frame of animation

// Joint parameters
const float JOINT_MIN = -45.0f;
const float JOINT_MAX =  45.0f;
float joint_rot = 0.0f;

//////////////////////////////////////////////////////
// TODO: Add additional joint parameters here
//////////////////////////////////////////////////////

// ---------------------------------------------------
template<class t> struct vector2D{
	t x;
	t y;
};

typedef vector2D<int> vector2Di;
typedef vector2D<float> vector2Df;
typedef vector2D<double> vector2Dd;

// ***********  FUNCTION HEADER DECLARATIONS ****************


// Initialization functions
void initGlut(char* winName);
void initGlui();
void initGl();


// Callbacks for handling events in glut
void myReshape(int w, int h);
void animate();
void display(void);

// Callback for handling events in glui
void GLUI_Control(int id);


// Functions to help draw the object
void drawSquare(float size);
void drawLeg();
void drawCircle(float _radius, int segcount);
void drawPolygon(vector2Df* _float, int _NumberofPoint);
// Return the current system clock (in seconds)
double getTime();


// ******************** FUNCTIONS ************************



// main() function
// Initializes the user interface (and any user variables)
// then hands over control to the event handler, which calls
// display() whenever the GL window needs to be redrawn.
int main(int argc, char** argv)
{

    // Process program arguments
    if(argc != 3) {
        printf("Usage: demo [width] [height]\n");
        printf("Using 300x200 window by default...\n");
        Win[0] = 300;
        Win[1] = 200;
    } else {
        Win[0] = atoi(argv[1]);
        Win[1] = atoi(argv[2]);
    }


    // Initialize glut, glui, and opengl
    glutInit(&argc, argv);
    initGlut(argv[0]);
    initGlui();
    initGl();

    // Invoke the standard GLUT main event loop
    glutMainLoop();

    return 0;         // never reached
}


// Initialize glut and create a window with the specified caption
void initGlut(char* winName)
{
    // Set video mode: double-buffered, color, depth-buffered
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutInitWindowPosition (0, 0);
    glutInitWindowSize(Win[0],Win[1]);
    windowID = glutCreateWindow(winName);

    // Setup callback functions to handle events
    glutReshapeFunc(myReshape); // Call myReshape whenever window resized
    glutDisplayFunc(display);   // Call display whenever new frame needed
}


// Quit button handler.  Called when the "quit" button is pressed.
void quitButton(int)
{
  exit(0);
}

// Animate button handler.  Called when the "animate" checkbox is pressed.
void animateButton(int)
{
  // synchronize variables that GLUT uses
  glui->sync_live();

  animation_frame = 0;
  if(animate_mode == 1) {
    // start animation
    GLUI_Master.set_glutIdleFunc(animate);
  } else {
    // stop animation
    GLUI_Master.set_glutIdleFunc(NULL);
  }
}

// Initialize GLUI and the user interface
void initGlui()
{
    GLUI_Master.set_glutIdleFunc(NULL);

    // Create GLUI window
    glui = GLUI_Master.create_glui("Glui Window", 0, Win[0]+10, 0);

    // Create a control to specify the rotation of the joint
    GLUI_Spinner *joint_spinner
        = glui->add_spinner("Joint", GLUI_SPINNER_FLOAT, &joint_rot);
    joint_spinner->set_speed(0.1);
    joint_spinner->set_float_limits(JOINT_MIN, JOINT_MAX, GLUI_LIMIT_CLAMP);

    ///////////////////////////////////////////////////////////
    // TODO:
    //   Add controls for additional joints here
    ///////////////////////////////////////////////////////////

    // Add button to specify animation mode
    glui->add_separator();
    glui->add_checkbox("Animate", &animate_mode, 0, animateButton);

    // Add "Quit" button
    glui->add_separator();
    glui->add_button("Quit", 0, quitButton);

    // Set the main window to be the "active" window
    glui->set_main_gfx_window(windowID);
}


// Performs most of the OpenGL intialization
void initGl(void)
{
    // glClearColor (red, green, blue, alpha)
    // Ignore the meaning of the 'alpha' value for now
    glClearColor(0.7f,0.7f,0.9f,1.0f);
}




// Callback idle function for animating the scene
void animate()
{
    // Update geometry
    const double joint_rot_speed = 0.1;
    double joint_rot_t = (sin(animation_frame*joint_rot_speed) + 1.0) / 2.0;
    joint_rot = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;

    ///////////////////////////////////////////////////////////
    // TODO:
    //   Modify this function animate the character's joints
    //   Note: Nothing should be drawn in this function!  OpenGL drawing
    //   should only happen in the display() callback.
    ///////////////////////////////////////////////////////////

    // Update user interface
    glui->sync_live();

    // Tell glut window to update itself.  This will cause the display()
    // callback to be called, which renders the object (once you've written
    // the callback).
    glutSetWindow(windowID);
    glutPostRedisplay();

    // increment the frame number.
    animation_frame++;

    // Wait 50 ms between frames (20 frames per second)
    usleep(50000);
}


// Handles the window being resized by updating the viewport
// and projection matrices
void myReshape(int w, int h)
{
    // Setup projection matrix for new window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w/2, w/2, -h/2, h/2);

    // Update OpenGL viewport and internal variables
    glViewport(0,0, w,h);
    Win[0] = w;
    Win[1] = h;
}



// display callback
//
// This gets called by the event handler to draw
// the scene, so this is where you need to build
// your scene -- make your changes and additions here.
// All rendering happens in this function.  For Assignment 1,
// updates to geometry should happen in the "animate" function.
void display(void)
{
    // glClearColor (red, green, blue, alpha)
    // Ignore the meaning of the 'alpha' value for now
    glClearColor(0.7f,0.7f,0.9f,1.0f);

    // OK, now clear the screen with the background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup the model-view transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    ///////////////////////////////////////////////////////////
    // TODO:
    //   Modify this function draw the scene
    //   This should include function calls to pieces that
    //   apply the appropriate transformation matrice and
    //   render the individual body parts.
    ///////////////////////////////////////////////////////////

    // Draw our hinged object
    const float BODY_WIDTH = 300.0f;
    const float BODY_LENGTH = 500.0f;

    // Push the current transformation matrix on the stack
    glPushMatrix();

        // Draw the 'body'
        glPushMatrix();
            // Scale square to size of body
            glScalef(BODY_WIDTH, BODY_LENGTH, 1.0);

            // Set the colour to green
            glColor3f(0.0, 1.0, 0.0);
            vector2Df* body = new vector2Df[6];
            body[0].x = -1;body[0].y = 10;
            body[1].x = 1;body[1].y = 10;
            body[2].x = 3;body[2].y = 0;
            body[3].x = 1;body[3].y = -3;
            body[4].x = -1;body[4].y = -3;
            body[5].x = -3;body[5].y = 0;
            // Draw the square for the body
            drawSquare(1.0);
        glPopMatrix();
        glPushMatrix();
        	glTranslatef(-10,0,0);
        	drawLeg();
        	glTranslatef(20,0,0);
        	drawLeg();
        glPopMatrix();
    // Retrieve the previous state of the transformation stack
    glPopMatrix();


    // Execute any GL functions that are in the queue just to be safe
    glFlush();

    // Now, show the frame buffer that we just drew into.
    // (this prevents flickering).
    glutSwapBuffers();
}


// Draw a square of the specified size, centered at the current location
void drawSquare(float width)
{
    // Draw the square
    glBegin(GL_POLYGON);
    glVertex2d(-width/2, -width/2);
    glVertex2d(width/2, -width/2);
    glVertex2d(width/2, width/2);
    glVertex2d(-width/2, width/2);
    glEnd();
}

void drawLeg()
{
	const float torso_length = 100.0f;
	const float torso_width = 10.0f;
	const float torso_startangle = 0.0f;
	const float leg_length = 100.0f;
	const float leg_width = 10.0f;
	const float leg_startangle = 0.0f;
	glPushMatrix();
		glTranslatef(0.0f,-10.0f,0);
		glRotatef(torso_startangle+joint_rot,0,0,1);
		glPushMatrix();
			glColor3f(1.0f,1.0f,0.0f);
			glTranslatef(0.0f,-torso_length/2,0.0f);
			glScalef(torso_width,torso_length,1);
			drawSquare(1.0);
		glPopMatrix();
    	glColor3f(0,0,0);
    	drawCircle(6,30);
		glTranslatef(0.0f,-torso_length+leg_width,0.0f);
		glPushMatrix();
			glRotatef(leg_startangle+joint_rot,0,0,1);
			glTranslatef(0.0f,-leg_length/2,1);
			glScalef(leg_width,leg_length,1);
			glColor3f(1.0f,0.0f,1.0f);
			drawSquare(1.0);
		glPopMatrix();
		glColor3f(0,0,0);
		drawCircle(6,30);
	glPopMatrix();
}

void drawCircle(float _radius, int segcount){
	glBegin(GL_LINE_LOOP);
	float theta = 0;
	float delta = 2 * PI/segcount;
	for(int i = 0; i <= segcount; i++){
		float x = _radius * cos(theta);
		float y = _radius * sin(theta);
		glVertex2d(x,y);
		theta += delta;
	}
	glEnd();
}

void drawPolygon(vector2Df* _float, int _NumberofPoint){
	glBegin(GL_POLYGON);
	for(int i = 0; i <= _NumberofPoint; i++){
		glVertex2d(_float[i].x,_float[i].y);
	}
	glEnd();
}



