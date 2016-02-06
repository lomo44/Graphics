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


// 											
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
int leg_animation_fram = 0;
// Joint parameters
const float JOINT_MIN = -45.0f;
const float JOINT_MAX =  45.0f;
float joint_rot = 0.0f;

const float HEAD_ROTATE_MIN = -10.0f;
const float HEAD_ROTATE_MAX =  10.0f;
float head_rotate = 0.0f;

const float BODY_MOVING_X_MIN = -100;
const float BODY_MOVING_X_MAX = 100;
float body_move_x = 0.0f;

const float BODY_MOVING_Y_MIN = -100;
const float BODY_MOVING_Y_MAX = 100;
float body_move_y = 0.0f;

const float WING_MOVING_MIN = -1;
const float WING_MOVING_MAX = 1;
float wing_move = 0.0f;

const float WING_ROTATE_MIN = -30;
const float WING_ROTATE_MAX = 0;
float wing_rotate = 0.0f;

const float MOUTH_MOVING_MIN = 0;
const float MOUTH_MOVING_MAX = 0.5;
float mouth_move = 0.0f;

const float LEFT_TORSO_ROTATE_MIN = -22.5;
const float LEFT_TORSO_ROTATE_MAX = 120;
float left_torso_rotate = 0.0f;

const float RIGHT_TORSO_ROTATE_MIN = -22.5;
const float RIGHT_TORSO_ROTATE_MAX = 120;
float right_torso_rotate = 0.0f;

const float LEFT_LEG_ROTATE_MIN = -100;
const float LEFT_LEG_ROTATE_MAX = 135;
float left_leg_rotate = 0.0f;

const float RIGHT_LEG_ROTATE_MIN = -100;
const float RIGHT_LEG_ROTATE_MAX = 135;
float right_leg_rotate = 0.0f;

bool isleft = true;
// Draw our hinged object
const float bodyscale = 50;
//////////////////////////////////////////////////////
// TODO: Add additional joint parameters here
//////////////////////////////////////////////////////
const float MOUTH_OPEN_DISTANCE = 0.1;

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
void drawLeg(float leg_start_angle, float leg_rot, float torso_start_angle, float torso_rot);
void drawCircle(float _radius, int segcount);
void drawCircleFilled(float _radius, int segcount);
void drawPolygon(vector2Df* _float, int _NumberofPoint);
void drawBody();
void drawWing();
void drawHead();
void drawMouth();
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
    GLUI_Spinner *bodymoving_spinnerX =
    		glui->add_spinner("Body X",GLUI_SPINNER_FLOAT,&body_move_x);
    bodymoving_spinnerX->set_speed(0.1);
    bodymoving_spinnerX->set_float_limits(BODY_MOVING_X_MIN,BODY_MOVING_X_MAX,GLUI_LIMIT_CLAMP);

    GLUI_Spinner *bodymoving_spinnerY =
    		glui->add_spinner("Body Y",GLUI_SPINNER_FLOAT,&body_move_y);
    bodymoving_spinnerY->set_speed(0.1);
    bodymoving_spinnerY->set_float_limits(BODY_MOVING_Y_MIN,BODY_MOVING_Y_MAX,GLUI_LIMIT_CLAMP);

    GLUI_Spinner *wing_spinner =
        		glui->add_spinner("Wing Move",GLUI_SPINNER_FLOAT,&wing_move);
        wing_spinner->set_speed(0.1);
        wing_spinner->set_float_limits(WING_MOVING_MIN,WING_MOVING_MAX,GLUI_LIMIT_CLAMP);

    GLUI_Spinner *head_spinner =
    		glui->add_spinner("Head",GLUI_SPINNER_FLOAT,&head_rotate);
    head_spinner->set_speed(0.1);
    head_spinner->set_float_limits(HEAD_ROTATE_MIN,HEAD_ROTATE_MAX,GLUI_LIMIT_CLAMP);

    GLUI_Spinner *mouth_spinner =
    		glui->add_spinner("Mouth",GLUI_SPINNER_FLOAT,&mouth_move);
    mouth_spinner->set_speed(0.1);
    mouth_spinner->set_float_limits(MOUTH_MOVING_MIN,MOUTH_MOVING_MAX,GLUI_LIMIT_CLAMP);

    GLUI_Spinner *wingrotate_spinner =
    		glui->add_spinner("Wing Rotate",GLUI_SPINNER_FLOAT,&wing_rotate);
    wingrotate_spinner->set_speed(0.1);
    wingrotate_spinner->set_float_limits(WING_ROTATE_MIN,WING_ROTATE_MAX,GLUI_LIMIT_CLAMP);

    GLUI_Spinner *lefttorso_spinner =
    		glui->add_spinner("L Torso Rotate",GLUI_SPINNER_FLOAT,&left_torso_rotate);
    lefttorso_spinner->set_speed(0.1);
    lefttorso_spinner->set_float_limits(LEFT_TORSO_ROTATE_MIN,LEFT_TORSO_ROTATE_MAX,GLUI_LIMIT_CLAMP);

    GLUI_Spinner *righttorso_spinner =
    		glui->add_spinner("R Torso Rotate",GLUI_SPINNER_FLOAT,&right_torso_rotate);
    righttorso_spinner->set_speed(0.1);
    righttorso_spinner->set_float_limits(RIGHT_TORSO_ROTATE_MIN,RIGHT_TORSO_ROTATE_MAX,GLUI_LIMIT_CLAMP);

    GLUI_Spinner *leftleg_spinner
        = glui->add_spinner("L Leg", GLUI_SPINNER_FLOAT, &left_leg_rotate);
    leftleg_spinner->set_speed(0.1);
    leftleg_spinner->set_float_limits(LEFT_LEG_ROTATE_MIN, LEFT_LEG_ROTATE_MAX, GLUI_LIMIT_CLAMP);

    GLUI_Spinner *rightleg_spinner
        = glui->add_spinner("R Leg", GLUI_SPINNER_FLOAT, &right_leg_rotate);
    rightleg_spinner->set_speed(0.1);
    rightleg_spinner->set_float_limits(LEFT_LEG_ROTATE_MIN, LEFT_LEG_ROTATE_MAX, GLUI_LIMIT_CLAMP);

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

    const double body_moving_speed_X = 0.01;
    double body_position_X = (sin(animation_frame*body_moving_speed_X) + 1)/2;
    body_move_x = body_position_X * BODY_MOVING_X_MIN + (1-body_position_X) * BODY_MOVING_X_MAX;

    const double body_moving_speed_Y = 0.01;
    double body_position_Y = (sin(animation_frame*body_moving_speed_Y) + 1)/2;
    body_move_y = body_position_Y * BODY_MOVING_Y_MIN + (1-body_position_Y) * BODY_MOVING_Y_MAX;

    const double wing_moving_speed = 1;
    double torso_rotition = (sin(animation_frame*wing_moving_speed) + 1)/2;
    wing_move = torso_rotition * WING_MOVING_MIN + (1-torso_rotition) * WING_MOVING_MAX;

    const double head_moving_speed = 1;
    double head_angle = (sin(animation_frame*head_moving_speed)+1)/2;
    head_rotate = head_angle * HEAD_ROTATE_MIN + (1-head_angle) * HEAD_ROTATE_MAX;

    const double mouth_moving_speed = 0.5;
    double mouth_pos = (sin(animation_frame*mouth_moving_speed)+1)/2;
    mouth_move = mouth_pos * MOUTH_MOVING_MIN + (1- mouth_pos) * MOUTH_MOVING_MAX;

    const double wing_rotate_speed = 0.5;
    double wing_rot = (sin(animation_frame*wing_rotate_speed)+1)/2;
    wing_rotate = wing_rot * WING_ROTATE_MIN + (1- wing_rot) * WING_ROTATE_MAX;

    const double torso_rotate_speed = 0.2;
    const double leg_rot_speed = torso_rotate_speed;
    //double torso_rot = sin(leg_animation_fram*torso_rotate_speed + 1)/2.0;
    double leg_rot = 45 * sin(animation_frame*leg_rot_speed) + 90;
    /*if((animation_frame % 20) >= 9){
    	leg_rot = 45 * sin(animation_frame*leg_rot_speed) + 90;
    }
    else
    {
    	leg_rot = 100;
    }*/
    double left_torso_rot = 70 * sin(animation_frame*torso_rotate_speed - 90) + 50;
    double right_torso_rot = 70 * sin(animation_frame*torso_rotate_speed) + 50;
    //left_torso_rotate = torso_rot * LEFT_TORSO_ROTATE_MIN + (1- torso_rot) * LEFT_TORSO_ROTATE_MAX;
    left_torso_rotate = left_torso_rot;
    left_leg_rotate = leg_rot;
    right_torso_rotate = right_torso_rot;
    right_leg_rotate = leg_rot;

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
    leg_animation_fram++;
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



    // Push the current transformation matrix on the stack
    glTranslatef(body_move_x,body_move_y,0);
    glScalef(bodyscale,bodyscale,1);
    glPushMatrix();
    	drawBody();        // Draw the 'body'
    	glPushMatrix();
    		glTranslatef(0,3.1,0);
    		drawHead();
    	glPopMatrix();
    	glPushMatrix();
    		glTranslatef(0.5,1.8,0.0);
    		drawWing();
    	glPopMatrix();
    	glPushMatrix();
        	glTranslatef(1,-2.5,0);
        	drawLeg(180, right_leg_rotate, 0, right_torso_rotate);
        	glTranslatef(-1.8,0.1,0);
        	drawLeg(180, left_leg_rotate, -75, left_torso_rotate);
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
void drawLeg(float leg_start_angle, float leg_rot, float torso_start_angle, float torso_rot){
	const float torso_length = 2.0f;
	const float torso_width = 0.5f;
	const float leg_length = 2.0f;
	const float leg_width = 0.3f;
	glPushMatrix();
		glRotatef(torso_start_angle+torso_rot,0,0,1);
		glPushMatrix();
			glColor3f(1.0f,1.0f,1.0f);
			glTranslatef(0.0f,-torso_length/2,0.0f);
			glScalef(torso_width,torso_length,1);
			drawSquare(1.0);
		glPopMatrix();
		glColor3f(0,0,0);
		drawCircle(0.1,30);
		glTranslatef(0.0f,-torso_length+leg_width,0.0f);
		glPushMatrix();
			glRotatef(leg_start_angle+leg_rot,0,0,1);
			glTranslatef(0.0f,-leg_length/2,1);
			glScalef(leg_width,leg_length,1);
			glColor3f(0.0f,0.0f,0.0f);
			drawSquare(1.0);
		glPopMatrix();
		glColor3f(0,0,0);
		drawCircle(0.1,30);
	glPopMatrix();
}

void drawLeg()
{
	const float torso_length = 2.0f;
	const float torso_width = 0.5f;
	const float torso_startangle = 0.0f;
	const float leg_length = 2.0f;
	const float leg_width = 0.3f;
	const float leg_startangle = 0.0f;
	glPushMatrix();
		glRotatef(torso_startangle+joint_rot,0,0,1);
		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glTranslatef(0.0f,-torso_length/2,0.0f);
			glScalef(torso_width,torso_length,1);
			drawSquare(1.0);
		glPopMatrix();
    	glColor3f(0,0,0);
    	drawCircle(0.1,30);
		glTranslatef(0.0f,-torso_length+leg_width,0.0f);
		glPushMatrix();
			glRotatef(leg_startangle+joint_rot,0,0,1);
			glTranslatef(0.0f,-leg_length/2,1);
			glScalef(leg_width,leg_length,1);
			glColor3f(0.0,0.0,0.0);
			drawSquare(1.0);
		glPopMatrix();
		glColor3f(0,0,0);
		drawCircle(0.1,30);
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
void drawCircleFilled(float _radius, int segcount){
	glBegin(GL_POLYGON);
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

void drawBody(){
	glPushMatrix();
		// Set the colour to green
		glColor3f(0.0, 1.0, 0.0);
		vector2Df* body = new vector2Df[6];
		body[0].x = 1;body[0].y = 3.5;
		body[1].x = -1;body[1].y = 3.5;
		body[2].x = -2;body[2].y = -2;
		body[3].x = -0.6;body[3].y = -3.8;
		body[4].x = 1;body[4].y = -4;
		body[5].x = 2.4;body[5].y = -2;
		glColor3f(0.5,0.5,0.5);
		drawPolygon(body,6);
		// Draw the square for the body
	glPopMatrix();
}

void drawHead(){
	const float head_anlge = 0;
	glPushMatrix();
		glRotatef(head_anlge + head_rotate, 0, 0, 1);
		glPushMatrix();
			vector2Df* head = new vector2Df[5];
			head[0].x = 1;head[0].y = 0.5;
			head[1].x = -0.1;head[1].y = 1;
			head[2].x = -1;head[2].y = 0.5;
			head[3].x = -1.2;head[3].y = -1.2;
			head[4].x = 1.2;head[4].y = -1.2;
			glTranslatef(0,1,0);
			glColor3f(0,0,0);
			drawPolygon(head,5);
			glTranslatef(-0.5,0.2,0);
			glColor3f(1.0,1.0,1.0);
			drawCircleFilled(0.2,10);
			glTranslatef(-0.1,0,0);
			glColor3f(0.0,0.0,0.0);
			drawCircleFilled(0.1,10);
			glTranslatef(-1.1,-0.2,0);
			drawMouth();
		glPopMatrix();
		glColor3f(1.0,1.0,1.0);
		drawCircle(0.1,30);
	glPopMatrix();
}

void drawPolygon(vector2Df* _float, int _NumberofPoint){
	glBegin(GL_POLYGON);
	for(int i = 0; i < _NumberofPoint; i++){
		glVertex2f(_float[i].x,_float[i].y);
	}
	glEnd();
}

void drawWing(){
	const float wing_startangle = 0;
	glPushMatrix();
		glRotatef(wing_startangle + wing_rotate,0,0,1);
		glPushMatrix();
			glTranslatef(0,-1,0);
			vector2Df* pset = new vector2Df[4];
			pset[0].x = 0.6;pset[0].y = 1.5;
			pset[1].x = -0.6;pset[1].y = 1.5;
			pset[2].x = -0.3;pset[2].y = -0.1 -wing_move;
			pset[3].x = 0.3;pset[3].y = -0.1 -wing_move;
			glColor3f(0,0,0);
			drawPolygon(pset,4);
		glPopMatrix();
		glColor3f(1,1,1);
		drawCircle(0.1,30);
		delete pset;
	glPopMatrix();
}

void drawMouth(){
	const float mouth_startposition = 0;
	glPushMatrix();
		vector2Df* pset = new vector2Df[4];
		pset[0].x = 1;pset[0].y = 0.5;
		pset[1].x = -1;pset[1].y = 0;
		pset[2].x = -1;pset[2].y = -0.5;
		pset[3].x = 1;pset[3].y = -0.5;
		glColor3f(1.0,0,0);
		drawPolygon(pset,4);
		glTranslatef(0,-0.5,0);
		glTranslatef(0,mouth_startposition-mouth_move,0);
		glScalef(1,0.1,1);
		drawSquare(2);
	glPopMatrix();
}



