/***********************************************************
             CSC418, Winter 2016
 
                 penguin.cpp
                 author: Mike Pratscher
                 based on code by: Eron Steger, J. Radulovich

		Main source file for assignment 2
		Uses OpenGL, GLUT and GLUI libraries
  
    Instructions:
        Please read the assignment page to determine 
        exactly what needs to be implemented.  Then read 
        over this file and become acquainted with its 
        design. In particular, see lines marked 'README'.
		
		Be sure to also look over keyframe.h and vector.h.
		While no changes are necessary to these files, looking
		them over will allow you to better understand their
		functionality and capabilites.

        Add source code where it appears appropriate. In
        particular, see lines marked 'TODO'.

        You should not need to change the overall structure
        of the program. However it should be clear what
        your changes do, and you should use sufficient comments
        to explain your code.  While the point of the assignment
        is to draw and animate the character, you will
        also be marked based on your design.

***********************************************************/

#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "keyframe.h"
#include "timer.h"
#include "vector.h"
#include <vector>
#include <algorithm>
#include "Matrix.h"
#include "RenderController.h"
#include "Drawable.h"
typedef std::vector<GLfloat> vecGLfloat;
// *************** GLOBAL VARIABLES *************************


const float PI = 3.14159;
const float RAD = 0.0174532;
const float SPINNER_SPEED = 0.1;

// --------------- USER INTERFACE VARIABLES -----------------

// Window settings
int windowID;				// Glut window ID (for display)
int Win[2];					// window (x,y) size

GLUI* glui_joints;			// Glui window with joint controls
GLUI* glui_keyframe;		// Glui window with keyframe controls
GLUI* glui_render;			// Glui window for render style

char msg[256];				// String used for status message
GLUI_StaticText* status;	// Status message ("Status: <msg>")


// ---------------- ANIMATION VARIABLES ---------------------

// Camera settings
bool updateCamZPos = false;
bool updateCamXYPos = false;
int  lastX = 0;
int  lastY = 0;
int PanningX = 0;
int PanningY = 0;
const float ZOOM_SCALE = 0.01;
const float MOVEMENT_PACE = 0.1;

// Camera Rotation
bool g_iUpdateCamRotation = false;
int g_rotationX = 0;
int g_rotationY = 0;
float g_fCamRotateX = 0;
float g_fCamRotateY = 0;
const float ROTATION_SCALE = 10;

GLdouble camXPos =  0.0;
GLdouble camYPos =  0.0;
GLdouble camZPos = -7.5;

const GLdouble CAMERA_FOVY = 60.0;
const GLdouble NEAR_CLIP   = 0.1;
const GLdouble FAR_CLIP    = 1000.0;

// Render settings
enum { WIREFRAME , SOLID, OUTLINED };	// README: the different render styles
int renderStyle = WIREFRAME;			// README: the selected render style

// Animation settings
int animate_mode = 0;			// 0 = no anim, 1 = animate

// Keyframe settings
const char filenameKF[] = "keyframes.txt";	// file for loading / saving keyframes

Keyframe* keyframes;			// list of keyframes

int maxValidKeyframe   = 0;		// index of max VALID keyframe (in keyframe list)
const int KEYFRAME_MIN = 0;
const int KEYFRAME_MAX = 32;	// README: specifies the max number of keyframes

// Frame settings
char filenameF[128];			// storage for frame filename

int frameNumber = 0;			// current frame being dumped
int frameToFile = 0;			// flag for dumping frames to file

const float DUMP_FRAME_PER_SEC = 24.0;		// frame rate for dumped frames
const float DUMP_SEC_PER_FRAME = 1.0 / DUMP_FRAME_PER_SEC;

// Time settings
Timer* animationTimer;
Timer* frameRateTimer;

const float TIME_MIN = 0.0;
const float TIME_MAX = 10.0;	// README: specifies the max time of the animation
const float SEC_PER_FRAME = 1.0 / 60.0;

// Joint settings

// README: This is the key data structure for
// updating keyframes in the keyframe list and
// for driving the animation.
//   i) When updating a keyframe, use the values
//      in this data structure to update the
//      appropriate keyframe in the keyframe list.
//  ii) When calculating the interpolated pose,
//      the resulting pose vector is placed into
//      this data structure. (This code is already
//      in place - see the animate() function)
// iii) When drawing the scene, use the values in
//      this data structure (which are set in the
//      animate() function as described above) to
//      specify the appropriate transformations.
Keyframe* joint_ui_data;

// README: To change the range of a particular DOF,
// simply change the appropriate min/max values below
const float ROOT_TRANSLATE_X_MIN = -5.0;
const float ROOT_TRANSLATE_X_MAX =  5.0;
const float ROOT_TRANSLATE_Y_MIN = -5.0;
const float ROOT_TRANSLATE_Y_MAX =  5.0;
const float ROOT_TRANSLATE_Z_MIN = -5.0;
const float ROOT_TRANSLATE_Z_MAX =  5.0;
const float ROOT_ROTATE_X_MIN    = -180.0;
const float ROOT_ROTATE_X_MAX    =  180.0;
const float ROOT_ROTATE_Y_MIN    = -180.0;
const float ROOT_ROTATE_Y_MAX    =  180.0;
const float ROOT_ROTATE_Z_MIN    = -180.0;
const float ROOT_ROTATE_Z_MAX    =  180.0;
const float HEAD_MIN             = -180.0;
const float HEAD_MAX             =  180.0;
const float ARM_SCALE_MIN        =  0.5;
const float ARM_SCALE_MAX        =  2.0;
const float SHOULDER_PITCH_MIN   = -45.0;
const float SHOULDER_PITCH_MAX   =  45.0;
const float SHOULDER_YAW_MIN     = -45.0;
const float SHOULDER_YAW_MAX     =  45.0;
const float SHOULDER_ROLL_MIN    = -45.0;
const float SHOULDER_ROLL_MAX    =  45.0;
const float HIP_PITCH_MIN        = -45.0;
const float HIP_PITCH_MAX        =  45.0;
const float HIP_YAW_MIN          = -45.0;
const float HIP_YAW_MAX          =  45.0;
const float HIP_ROLL_MIN         = -45.0;
const float HIP_ROLL_MAX         =  45.0;
const float BEAK_MIN             =  0.0;
const float BEAK_MAX             =  1.0;
const float ELBOW_MIN            =  0.0;
const float ELBOW_MAX            = 75.0;
const float KNEE_MIN             =  0.0;
const float KNEE_MAX             = 75.0;


// ***********  FUNCTION HEADER DECLARATIONS ****************


// Initialization functions
void initDS();
void initGlut(int argc, char** argv);
void initGlui();
void initGl();


// Callbacks for handling events in glut
void reshape(int w, int h);
void animate();
void display(void);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char c, int x, int y);

// Functions to help draw the object
Vector getInterpolatedJointDOFS(float time);
void drawCube();


// Image functions
void writeFrame(char* filename, bool pgm, bool frontBuffer);


// ******************** FUNCTIONS ************************
// *** Class **** //

// Extra Classes For Eaiser Implementation

// TODO: Currentlly the object layer is mixed up with render layer,need to
// seperate the layer.

#define COLOR_PENGUINFEET 0x00ffff26
#define COLOR_PENGUINLEG  0x00191903
#define COLOR_PENGUINBODY 0x0066660f
#define COLOR_PENGUINBEAK 0x00ff4800
#define COLOR_PENGUINHEAD 0x00656638
#define COLOR_PENGUINWING 0x007a8b8b
#define COLOR_PENGUINARM  0x00bcc5c5

std::vector<Drawable*> primitive_list;

class Polygon : public Drawable{
public:
	Polygon(){nofv = 0; isDrawReverse = false;}
	virtual ~Polygon(){}
	void SetVertex(Vector* vertexlist, int d, bool _isDrawReverse){
		nofv = d;
		float a = 0;
		float b = 0;
		float c = 0;
		int start = 0;
		int end = nofv;
		int increment = 1;
		isDrawReverse = _isDrawReverse;
		if(isDrawReverse){
			start = nofv-1;
			end = -1;
			increment = -1;
		}
		for(int i = start; i != end; i += increment){
			//std::cout<<vertexlist[i][0]<<"|"<<vertexlist[i][1]<<"|"<<vertexlist[i][2]<<std::endl;
			_vertexlist.push_back(vertexlist[i][0]);
			_vertexlist.push_back(vertexlist[i][1]);
			_vertexlist.push_back(vertexlist[i][2]);
			a += vertexlist[i][0];
			b += vertexlist[i][1];
			c += vertexlist[i][2];
		}
		a = a/d;
		b = b/d;
		c = c/d;
		mid[0] = a;
		mid[1] = b;
		mid[2] = c;
	}
	void SetReverse(bool _b){
		if(_b != isDrawReverse)
		{
			isDrawReverse = _b;
			std::reverse(_vertexlist.begin(),_vertexlist.end());
			for(unsigned int i = 0; i < _vertexlist.size();i+=3){
				GLfloat a = _vertexlist[i];
				_vertexlist[i] = _vertexlist[i+2];
				_vertexlist[i+2] = a;
			}
		}
	}
	Polygon* clone(){
		Polygon* _clone = new Polygon();
		Vector* _newvec = new Vector[nofv];
		for(int i = 0 ; i < nofv; i++){
			_newvec[i] = _vertexlist[i];
		}
		_clone->SetVertex(_newvec,nofv,isDrawReverse);
		_clone->translate(this->getTranslation());
		_clone->rotate(this->getReferenceCoord());
		_clone->scale(this->getScale());
		return _clone;
	}
	vecGLfloat& GetVertexlist(){return _vertexlist;}
	int GetVertexCount(){return nofv;}
	Vector& GetMid(){return mid;}
	void SetMid(Vector _v){
		mid = _v;
	}
protected:
	void drawObject(){
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,0,&_vertexlist[0]);
		glDrawArrays(GL_POLYGON,0,nofv);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
private:
	vecGLfloat _vertexlist;
	Vector mid;
	int nofv;
	bool isDrawReverse;
};
class LoftedPolygon : public Drawable{
// Note: Lofted Polygon Must Have same number of vertex for each face;
public:
	LoftedPolygon(){
		_face1 = NULL;
		_face2 = NULL;
	}
	~LoftedPolygon(){
		delete _face1;
		delete _face2;
	}
	void Setfaces(Polygon* face1, Polygon* face2){
		if(face1->GetMid()[3] > face2->GetMid()[3]){
			_face1 = face1;
			_face2 = face2;
		}
		else{
			_face1 = face2;
			_face2 = face1;
		}
		vecGLfloat& _v1 = _face1->GetVertexlist();
		vecGLfloat& _v2 = _face2->GetVertexlist();
		int vc1 = _face1->GetVertexCount();
		int vc2 = _face2->GetVertexCount();
		assert(vc1 == vc2);
		for(int i = 0; i < (vc1-1)*3; i+=3){
			addVertex(_v1[i+3],_v1[i+4],_v1[i+5]);
			addVertex(_v1[i],_v1[i+1],_v1[i+2]);
			addVertex(_v2[i],_v2[i+1],_v2[i+2]);
			addVertex(_v2[i+3],_v2[i+4],_v2[i+5]);
		}
		addVertex(_v1[0],_v1[1],_v1[2]);
		addVertex(_v1[vc1*3-3],_v1[vc1*3-2],_v1[vc1*3-1]);
		addVertex(_v2[vc1*3-3],_v2[vc1*3-2],_v2[vc1*3-1]);
		addVertex(_v2[0],_v2[1],_v2[2]);
		_face1->SetReverse(false);
		_face2->SetReverse(true);
	}
protected:
	void drawObject(){
		_face1->setColor1i(_colori._c);
		_face1->draw();
		_face2->setColor1i(_colori._c);
		_face2->draw();
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,0,&_vertexlist[0]);
		glDrawArrays(GL_QUADS,0,(int)(_vertexlist.size()/3));
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	LoftedPolygon* clone(){
		LoftedPolygon* _new = new LoftedPolygon();
		_new->Setfaces(_face1->clone(),_face2->clone());
		return _new;
	}
private:
	void addVertex(GLfloat x, GLfloat y, GLfloat z){
		_vertexlist.push_back(x);
		_vertexlist.push_back(y);
		_vertexlist.push_back(z);
	}
	Polygon* _face1;
	Polygon* _face2;
	vecGLfloat _vertexlist;
};
class ExtrudedPolygon : public LoftedPolygon{
public:
	ExtrudedPolygon(){
	}
	~ExtrudedPolygon(){}
	void SetBase(Polygon* face){
		vecGLfloat& _vec = face->GetVertexlist();
		Polygon* newface = new Polygon();
		*(newface) = *(face);
		vecGLfloat& newvec = newface->GetVertexlist();
		Matrix* _new = new Matrix();
		//depth.print();
		_new->loadTranslational(depth[0],depth[1],depth[2]);
		//_new->print();
		Vector _temp;
		for(unsigned int i = 0 ; i <= (_vec.size()-3);i+=3){
			_temp[0] = _vec[i];
			_temp[1] = _vec[i+1];
			_temp[2] = _vec[i+2];
			_temp = *(_new)*=_temp;
			newvec[i] = (_temp[0]);
			newvec[i+1]=(_temp[1]);
			newvec[i+2] =(_temp[2]);
		}
		Vector& mid = newface->GetMid();
		mid = *(_new)*=mid;
		//vecGL
		//newface->translate(depth);
		//newface->SetReverse(true);
		this->Setfaces(face,newface);
	}
	void SetDepth(Vector _depth){
		//_depth.print();
		depth = _depth;
	}
	void drawObject(){
		LoftedPolygon::drawObject();
	}
private:
	Vector depth;
};
class ReferenceAxis : public Drawable{
private:
	void drawObject(){
		glColor3f(1,0,0);
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,0,1);
		glEnd();
		glColor3f(0,1,0);
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,1,0);
		glEnd();
		glColor3f(0,0,1);
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(1,0,0);
		glEnd();
	}
public:
	ReferenceAxis* clone(){
		return new ReferenceAxis();
	}
};

class PenguinFeet : public Drawable{
public:
	PenguinFeet(Keyframe* _keyframe, bool isLeft){
		m_fLegLength = 1;
		initializeLeg();
		initializePalm();
		m_keyframe = _keyframe;
		m_bIsLeft = isLeft;
		if(m_bIsLeft){
			m_angle = _keyframe->getDOFPtr(Keyframe::L_KNEE);
		}
		else{
			m_angle = _keyframe->getDOFPtr(Keyframe::R_KNEE);
		}
	}
	~PenguinFeet(){;}
	PenguinFeet* clone(){
		return new PenguinFeet(m_keyframe,m_bIsLeft);
	}
	void drawObject(){
		//m_palm.draw();
		m_palm.rotate(0,0,-(*m_angle));
		m_leg.draw();
		m_palm.draw();
	}
private:
	void initializePalm(){
		Polygon* newPoly1 = new Polygon();
		Vector* newver = new Vector[3];
		newver[0] = *(new Vector(0.0,0.0,0.0));
		newver[1] = *(new Vector(-1,0.0,-0.5));
		newver[2] = *(new Vector(-1,0.0,0.5));
		newPoly1->SetVertex(newver,3,false);
		Vector _newvec;
		_newvec[1] = 0.1;
		m_palm.SetDepth(_newvec);
		m_palm.SetBase(newPoly1);
		m_palm.setColor1i(COLOR_PENGUINFEET);
		m_palm.translate(0,-m_fLegLength,0);
	}
	void initializeLeg(){
		Polygon* newPoly1 = new Polygon();
		Vector* newver = new Vector[4];
		newver[0] = *(new Vector(-0.1,0.0,0.1));
		newver[1] = *(new Vector(0.1,0.0,0.1));
		newver[2] = *(new Vector(0.1,0.0,-0.1));
		newver[3] = *(new Vector(-0.1,0.0,-0.1));
		newPoly1->SetVertex(newver,4,false);
		Vector _newvec;
		_newvec[1] = m_fLegLength;
		m_leg.SetDepth(_newvec);
		m_leg.SetBase(newPoly1);
		m_leg.setColor1i(COLOR_PENGUINLEG);
		m_leg.translate(0,-m_fLegLength,0);
	}
private:
	float* m_angle;
	bool m_bIsLeft;
	Keyframe* m_keyframe;
	float m_fLegLength;
	ExtrudedPolygon m_palm;
	ExtrudedPolygon m_leg;
};
class PenguinUpperWing : public Drawable{
public:
	PenguinUpperWing(){
		Polygon* newPoly1 = new Polygon();
		Vector* newver = new Vector[4];
		newver[0] = *(new Vector(0.3,0.6,0.0));
		newver[1] = *(new Vector(-0.3,0.6,0.0));
		newver[2] = *(new Vector(-0.15,-0.6,0.0));
		newver[3] = *(new Vector(0.3,-0.6,0.0));
		newPoly1->SetVertex(newver,4,false);
		Vector _newvec;
		_newvec[2] = 0.1;
		m_upperwing.SetDepth(_newvec);
		m_upperwing.SetBase(newPoly1);
		m_upperwing.translate(-0.04,-0.3,0);
		m_upperwing.setColor1i(COLOR_PENGUINWING);
	}
	~PenguinUpperWing(){;}
	PenguinUpperWing* clone(){
		return new PenguinUpperWing();
	}
	void drawObject(){
		m_upperwing.draw();
	}
private:
	ExtrudedPolygon m_upperwing;
};
class PenguinLowerWing : public Drawable{
public:
	PenguinLowerWing(){
		Polygon* newPoly1 = new Polygon();
		Vector* newver = new Vector[4];
		newver[0] = *(new Vector(0.20,0.2,0.0));
		newver[1] = *(new Vector(-0.20,0.2,0.0));
		newver[2] = *(new Vector(-0.15,-0.2,0.0));
		newver[3] = *(new Vector(0.20,-0.2,0.0));
		newPoly1->SetVertex(newver,4,false);
		Vector _newvec;
		_newvec[2] = 0.1;
		m_lowerwing.SetDepth(_newvec);
		m_lowerwing.SetBase(newPoly1);
		m_lowerwing.translate(0,-0.2,0);
		m_lowerwing.setColor1i(COLOR_PENGUINARM);
	}
	~PenguinLowerWing(){;}
	PenguinLowerWing* clone(){
		return new PenguinLowerWing();
	}
	void drawObject(){
		m_lowerwing.draw();
	}
private:
	ExtrudedPolygon m_lowerwing;
};
class PenguinWing : public Drawable{
public:
	PenguinWing(Keyframe* _keyframe, bool isLeft){
		m_keyframe = _keyframe;
		m_isLeft = isLeft;
		m_lowerwing = new PenguinLowerWing();
		m_upperwing = new PenguinUpperWing();
		if(m_isLeft){
			m_scale = _keyframe->getDOFPtr(Keyframe::L_ARM_SCALE);
		}
		else{
			m_scale = _keyframe->getDOFPtr(Keyframe::R_ARM_SCALE);
		}
	}
	~PenguinWing(){;}
	PenguinWing* clone(){ return new PenguinWing(m_keyframe, m_isLeft);}
	void drawObject(){
		m_upperwing->draw();
		m_lowerwing->translate(0,-0.8,0);
		m_lowerwing->rotate(0,0,-5);
		m_lowerwing->scale(1,*(m_scale),1);
		m_lowerwing->draw();
	}
private:
	float* m_scale;
	Keyframe* m_keyframe;
	bool m_isLeft;
	PenguinLowerWing* m_lowerwing;
	PenguinUpperWing* m_upperwing;
};
class PenguinHip : public Drawable{
public:
	PenguinHip(Keyframe* _keyframe, bool left ){
		Polygon* newPoly1 = new Polygon();
		Vector* newver = new Vector[4];
		newver[0] = *(new Vector(-0.15,0.2,0.15));
		newver[1] = *(new Vector(0.15,0.2,0.15));
		newver[2] = *(new Vector(0.15,0.2,-0.15));
		newver[3] = *(new Vector(-0.15,0.2,-0.15));
		newPoly1->SetVertex(newver,4,false);

		Polygon* newPoly2 = new Polygon();
		Vector* newver1 = new Vector[4];
		newver1[0] = *(new Vector(-0.1,0.0,0.1));
		newver1[1] = *(new Vector(0.1,0.0,0.1));
		newver1[2] = *(new Vector(0.1,0.0,-0.1));
		newver1[3] = *(new Vector(-0.1,0.0,-0.1));
		newPoly2->SetVertex(newver1,4,false);

		m_keyframe = _keyframe;
		m_Hip.Setfaces(newPoly2,newPoly1);
		m_Hip.setColor1i(COLOR_PENGUINFEET);
		m_Hip.translate(0,-0.2,0);
		b_isLeft = left;
		m_feet = new PenguinFeet(_keyframe,left);
	}
	~PenguinHip(){;}
	PenguinHip* clone(){
		return new PenguinHip(m_keyframe,b_isLeft);
	}
	void drawObject(){
		m_Hip.draw();
		m_feet->draw();
	}
protected:
	bool b_isLeft;
	Keyframe* m_keyframe;
	LoftedPolygon m_Hip;
	PenguinFeet* m_feet;
};
class PenguinUpperBeak : public Drawable{
public:
	PenguinUpperBeak(){
		Polygon* newPoly1 = new Polygon();
		Vector* newver1 = new Vector[4];
		newver1[0] = *(new Vector(-0.5,0,0.1));
		newver1[1] = *(new Vector(0.0,0,0.1));
		newver1[2] = *(new Vector(0.0,0,-0.1));
		newver1[3] = *(new Vector(-0.5,0,-0.1));
		newPoly1->SetVertex(newver1,4,false);

		Polygon* newPoly2 = new Polygon();
		Vector* newver = new Vector[4];
		newver[0] = *(new Vector(-0.45,0.1,0.08));
		newver[1] = *(new Vector(0.0,0.1,0.08));
		newver[2] = *(new Vector(0.0,0.1,-0.08));
		newver[3] = *(new Vector(-0.45,0.1,-0.08));
		newPoly2->SetVertex(newver,4,false);
		m_UpperBeak.setColor1i(COLOR_PENGUINBEAK);
		m_UpperBeak.Setfaces(newPoly1,newPoly2);
	}
	~PenguinUpperBeak(){;}
	PenguinUpperBeak* clone(){ return new PenguinUpperBeak();}
	void drawObject(){
		m_UpperBeak.draw();
	}
private:
	ExtrudedPolygon m_UpperBeak;
};
class PenguinLowerBeak : public Drawable{
public:
	PenguinLowerBeak(){
		Polygon* newPoly1 = new Polygon();
		Vector* newver1 = new Vector[4];
		newver1[0] = *(new Vector(-0.5,0,0.1));
		newver1[1] = *(new Vector(0.0,0,0.1));
		newver1[2] = *(new Vector(0.0,0,-0.1));
		newver1[3] = *(new Vector(-0.5,0,-0.1));
		newPoly1->SetVertex(newver1,4,false);

		Polygon* newPoly2 = new Polygon();
		Vector* newver = new Vector[4];
		newver[0] = *(new Vector(-0.45,-0.1,0.08));
		newver[1] = *(new Vector(0.0,-0.1,0.08));
		newver[2] = *(new Vector(0.0,-0.1,-0.08));
		newver[3] = *(new Vector(-0.45,-0.1,-0.08));
		newPoly2->SetVertex(newver,4,false);
		m_LowerBeak.setColor1i(COLOR_PENGUINBEAK);
		m_LowerBeak.Setfaces(newPoly2,newPoly1);
	}
	~PenguinLowerBeak(){;}
	PenguinUpperBeak* clone(){ return new PenguinUpperBeak();}
	void drawObject(){
		m_LowerBeak.draw();
	}
private:
	ExtrudedPolygon m_LowerBeak;
};
class PenguinBeak : public Drawable{
public:
	PenguinBeak(Keyframe* _keyframe){
		m_AnimationKeyFrame = _keyframe;
		m_Displacement = _keyframe->getDOFPtr(Keyframe::BEAK);
	}
	~PenguinBeak(){;}
	PenguinBeak* clone(){return new PenguinBeak(m_AnimationKeyFrame);}
	void drawObject(){
		float _temp = *(m_Displacement)/2;
		//std::cout<<"temp"<<_temp << std::endl;

		m_UpperBeak.translate(0,_temp,0);
		m_LowerBeak.translate(0,-_temp,0);
		m_UpperBeak.draw();
		m_LowerBeak.draw();
	}
private:
	float* m_Displacement;
	Keyframe* m_AnimationKeyFrame;
	PenguinUpperBeak m_UpperBeak;
	PenguinLowerBeak m_LowerBeak;
};
class PenguinHead : public Drawable{
public:
	PenguinHead(Keyframe* _frame){
		Polygon* newPoly1 = new Polygon();
		Vector* newver1 = new Vector[4];
		newver1[0] = *(new Vector(-0.8,0,0.8));
		newver1[1] = *(new Vector(0.8,0,0.8));
		newver1[2] = *(new Vector(0.8,0,-0.8));
		newver1[3] = *(new Vector(-0.8,0,-0.8));
		newPoly1->SetVertex(newver1,4,false);
		Polygon* newPoly2 = new Polygon();
		Vector* newver = new Vector[4];
		newver[0] = *(new Vector(-0.6,1.0,0.6));
		newver[1] = *(new Vector(0.6,1.0,0.6));
		newver[2] = *(new Vector(0.6,1.0,-0.6));
		newver[3] = *(new Vector(-0.6,1.0,-0.6));
		newPoly2->SetVertex(newver,4,false);
		m_head.setColor1i(COLOR_PENGUINHEAD);
		m_head.Setfaces(newPoly1,newPoly2);
		m_keyframe = _frame;
		m_Beak = new PenguinBeak(_frame);
	}
	~PenguinHead(){;}
	PenguinHead* clone(){return new PenguinHead(m_keyframe);}
	void drawObject(){
		m_head.draw();
		m_Beak->translate(-0.65,0.65,0);
		m_Beak->draw();
	}
private:
	Keyframe* m_keyframe;
	LoftedPolygon m_head;
	PenguinBeak* m_Beak;
};
class PenguinBody : public Drawable{
public:
	PenguinBody(Keyframe* _keyframe){
		Polygon* newPoly1 = new Polygon();
		Vector* newver1 = new Vector[4];
		newver1[0] = *(new Vector(-1,-1,1));
		newver1[1] = *(new Vector(1,-1,1));
		newver1[2] = *(new Vector(1,-1,-1));
		newver1[3] = *(new Vector(-1,-1,-1));
		newPoly1->SetVertex(newver1,4,false);
		Polygon* newPoly2 = new Polygon();
		Vector* newver = new Vector[4];
		newver[0] = *(new Vector(-0.7,1,0.7));
		newver[1] = *(new Vector(0.7,1,0.7));
		newver[2] = *(new Vector(0.7,1,-0.7));
		newver[3] = *(new Vector(-0.7,1,-0.7));
		newPoly2->SetVertex(newver,4,false);
		m_body.Setfaces(newPoly1,newPoly2);
		m_body.setColor1i(COLOR_PENGUINBODY);
		m_keyframe = _keyframe;
		m_Lhip = new PenguinHip(m_keyframe,true);
		m_Rhip = new PenguinHip(m_keyframe,false);
		m_Lhip->translate(0,-1,0.5);
		m_Rhip->translate(0,-1,-0.5);

		float wing_distance = 1.6;
		m_RWing = new PenguinWing(m_keyframe,false);
		m_LWing = new PenguinWing(m_keyframe,true);
		m_LWing->translate(0,0.2,wing_distance/2);
		m_RWing->translate(0,0.2,-wing_distance/2-0.1);
		m_fWingTilt = -7;
	}
	~PenguinBody(){;}
	PenguinBody* clone(){
		return new PenguinBody(m_keyframe);
	}
	void drawObject(){

		m_body.draw();
		//m_hip.translate(0,-1,0);
		m_Lhip->rotate(m_keyframe->getDOF(Keyframe::L_HIP_ROLL),m_keyframe->getDOF(Keyframe::L_HIP_YAW),m_keyframe->getDOF(Keyframe::L_HIP_PITCH));
		m_Lhip->draw();
		m_Rhip->rotate(m_keyframe->getDOF(Keyframe::R_HIP_ROLL),m_keyframe->getDOF(Keyframe::R_HIP_YAW),m_keyframe->getDOF(Keyframe::R_HIP_PITCH));
		m_Rhip->draw();
		m_LWing->rotate(-(m_keyframe->getDOF(Keyframe::L_SHOULDER_ROLL))+m_fWingTilt,-(m_keyframe->getDOF(Keyframe::L_SHOULDER_YAW)),-(m_keyframe->getDOF(Keyframe::L_SHOULDER_PITCH)));
		m_RWing->rotate(m_keyframe->getDOF(Keyframe::R_SHOULDER_ROLL)-m_fWingTilt,m_keyframe->getDOF(Keyframe::R_SHOULDER_YAW),m_keyframe->getDOF(Keyframe::R_SHOULDER_PITCH));
		m_RWing->draw();
		m_LWing->draw();
	}
private:
	float m_fWingTilt;
	Keyframe* m_keyframe;
	LoftedPolygon m_body;
	PenguinHip* m_Lhip;
	PenguinHip* m_Rhip;
	PenguinWing* m_LWing;
	PenguinWing* m_RWing;
};
class Penguin : public Drawable{
public:
	Penguin(Keyframe* _frame){
		m_keyframe = _frame;
		m_head = new PenguinHead(_frame);
		m_body = new PenguinBody(_frame);
		m_fTranslateX = m_keyframe->getDOFPtr(Keyframe::ROOT_TRANSLATE_X);
		m_fTranslateY = m_keyframe->getDOFPtr(Keyframe::ROOT_TRANSLATE_Y);
		m_fTranslateZ = m_keyframe->getDOFPtr(Keyframe::ROOT_TRANSLATE_Z);
		m_fRotateX = m_keyframe->getDOFPtr(Keyframe::ROOT_ROTATE_X);
		m_fRotateY = m_keyframe->getDOFPtr(Keyframe::ROOT_ROTATE_Y);
		m_fRotateZ = m_keyframe->getDOFPtr(Keyframe::ROOT_ROTATE_Z);
	}
	~Penguin(){;}
	Penguin* clone(){return new Penguin(m_keyframe);}
	void drawObject(){
		this->rotate(*(m_fRotateX),*(m_fRotateY),*(m_fRotateZ));
		this->rotate(*(m_fTranslateX),*(m_fTranslateY),*(m_fTranslateZ));
		float rotate = (m_keyframe->getDOF(Keyframe::HEAD));
		m_head->rotate(0,rotate,0);
		m_head->translate(0,1,0);
		m_head->draw();
		m_body->draw();
	}
private:
	float* m_fTranslateX;
	float* m_fTranslateY;
	float* m_fTranslateZ;
	float* m_fRotateX;
	float* m_fRotateY;
	float* m_fRotateZ;

	Keyframe* m_keyframe;
	PenguinHead* m_head;
	PenguinBody* m_body;
};
// This controller is used for drawing all the object on the
// screen


// main() function
// Initializes the user interface (and any user variables)
// then hands over control to the event handler, which calls 
// display() whenever the GL window needs to be redrawn.
int main(int argc, char** argv)
{

    // Process program arguments
    if(argc != 3) {
        printf("Usage: demo [width] [height]\n");
        printf("Using 640x480 window by default...\n");
        Win[0] = 640;
        Win[1] = 480;
    } else {
        Win[0] = atoi(argv[1]);
        Win[1] = atoi(argv[2]);
    }


    // Initialize data structs, glut, glui, and opengl
	initDS();
    initGlut(argc, argv);
    initGlui();
    initGl();

    // Invoke the standard GLUT main event loop
    glutMainLoop();

    return 0;         // never reached
}


// Create / initialize global data structures
void initDS()
{
	keyframes = new Keyframe[KEYFRAME_MAX];
	for( int i = 0; i < KEYFRAME_MAX; i++ )
		keyframes[i].setID(i);

	animationTimer = new Timer();
	frameRateTimer = new Timer();
	joint_ui_data  = new Keyframe();
	Penguin* mypenguin = new Penguin(joint_ui_data);
	g_RenderController.add(mypenguin);
	g_RenderController.add(new ReferenceAxis());
}


// Initialize glut and create a window with the specified caption 
void initGlut(int argc, char** argv)
{
	// Init GLUT
	glutInit(&argc, argv);

    // Set video mode: double-buffered, color, depth-buffered
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutInitWindowPosition (0, 0);
    glutInitWindowSize(Win[0],Win[1]);
    windowID = glutCreateWindow(argv[0]);
    glutSwapBuffers();
    // Setup callback functions to handle events
    glutReshapeFunc(reshape);	// Call reshape whenever window resized
    glutDisplayFunc(display);	// Call display whenever new frame needed
	glutMouseFunc(mouse);		// Call mouse whenever mouse button pressed
	glutMotionFunc(motion);		// Call motion whenever mouse moves while button pressed
	glutKeyboardFunc(keyboard);
}


// Load Keyframe button handler. Called when the "load keyframe" button is pressed
void loadKeyframeButton(int)
{
	// Get the keyframe ID from the UI
	int keyframeID = joint_ui_data->getID();

	// Update the 'joint_ui_data' variable with the appropriate
	// entry from the 'keyframes' array (the list of keyframes)
	*joint_ui_data = keyframes[keyframeID];

	// Sync the UI with the 'joint_ui_data' values
	glui_joints->sync_live();
	glui_keyframe->sync_live();

	// Let the user know the values have been loaded
	sprintf(msg, "Status: Keyframe %d loaded successfully", keyframeID);
	status->set_text(msg);
}

// Update Keyframe button handler. Called when the "update keyframe" button is pressed
void updateKeyframeButton(int)
{
	///////////////////////////////////////////////////////////
	// TODO:
	//   Modify this function to save the UI joint values into
	//   the appropriate keyframe entry in the keyframe list
	//   when the user clicks on the 'Update Keyframe' button.
	//   Refer to the 'loadKeyframeButton' function for help.
	///////////////////////////////////////////////////////////

	// Get the keyframe ID from the UI

	int keyframeID = joint_ui_data->getID();
	//std::cout<<"Keyframe ID: "<<keyframeID << std::endl;
	if(keyframeID > maxValidKeyframe){
		maxValidKeyframe = keyframeID;
	}
	// Update the 'maxValidKeyframe' index variable
	// (it will be needed when doing the interpolation)
	keyframes[keyframeID] = *(joint_ui_data);
	// Update the appropriate entry in the 'keyframes' array
	// with the 'joint_ui_data' data

	// Let the user know the values have been updated
	sprintf(msg, "Status: Keyframe %d updated successfully", keyframeID);
	status->set_text(msg);
}

// Load Keyframes From File button handler. Called when the "load keyframes from file" button is pressed
//
// ASSUMES THAT THE FILE FORMAT IS CORRECT, ie, there is no error checking!
//
void loadKeyframesFromFileButton(int)
{
	// Open file for reading
	FILE* file = fopen(filenameKF, "r");
	if( file == NULL )
	{
		sprintf(msg, "Status: Failed to open file %s", filenameKF);
		status->set_text(msg);
		return;
	}

	// Read in maxValidKeyframe first
	fscanf(file, "%d", &maxValidKeyframe);

	// Now read in all keyframes in the format:
	//    id
	//    time
	//    DOFs
	//
	for( int i = 0; i <= maxValidKeyframe; i++ )
	{
		fscanf(file, "%d", keyframes[i].getIDPtr());
		fscanf(file, "%f", keyframes[i].getTimePtr());

		for( int j = 0; j < Keyframe::NUM_JOINT_ENUM; j++ )
			fscanf(file, "%f", keyframes[i].getDOFPtr(j));
	}

	// Close file
	fclose(file);

	// Let the user know the keyframes have been loaded
	sprintf(msg, "Status: Keyframes loaded successfully");
	status->set_text(msg);
}

// Save Keyframes To File button handler. Called when the "save keyframes to file" button is pressed
void saveKeyframesToFileButton(int)
{
	// Open file for writing
	FILE* file = fopen(filenameKF, "w");
	if( file == NULL )
	{
		sprintf(msg, "Status: Failed to open file %s", filenameKF);
		status->set_text(msg);
		return;
	}

	// Write out maxValidKeyframe first
	fprintf(file, "%d\n", maxValidKeyframe);
	fprintf(file, "\n");

	// Now write out all keyframes in the format:
	//    id
	//    time
	//    DOFs
	//
	for( int i = 0; i <= maxValidKeyframe; i++ )
	{
		fprintf(file, "%d\n", keyframes[i].getID());
		fprintf(file, "%f\n", keyframes[i].getTime());

		for( int j = 0; j < Keyframe::NUM_JOINT_ENUM; j++ )
			fprintf(file, "%f\n", keyframes[i].getDOF(j));

		fprintf(file, "\n");
	}

	// Close file
	fclose(file);

	// Let the user know the keyframes have been saved
	sprintf(msg, "Status: Keyframes saved successfully");
	status->set_text(msg);
}

// Animate button handler.  Called when the "animate" button is pressed.
void animateButton(int)
{
  // synchronize variables that GLUT uses
  glui_keyframe->sync_live();

  // toggle animation mode and set idle function appropriately
  if( animate_mode == 0 )
  {
	// start animation
	frameRateTimer->reset();
	animationTimer->reset();

	animate_mode = 1;
	GLUI_Master.set_glutIdleFunc(animate);

	// Let the user know the animation is running
	sprintf(msg, "Status: Animating...");
	status->set_text(msg);
  }
  else
  {
	// stop animation
	animate_mode = 0;
	GLUI_Master.set_glutIdleFunc(NULL);

	// Let the user know the animation has stopped
	sprintf(msg, "Status: Animation stopped");
	status->set_text(msg);
  }
}

// Render Frames To File button handler. Called when the "Render Frames To File" button is pressed.
void renderFramesToFileButton(int)
{
	// Calculate number of frames to generate based on dump frame rate
	int numFrames = int(keyframes[maxValidKeyframe].getTime() * DUMP_FRAME_PER_SEC) + 1;

	// Generate frames and save to file
	frameToFile = 1;
	for( frameNumber = 0; frameNumber < numFrames; frameNumber++ )
	{
		// Get the interpolated joint DOFs
		joint_ui_data->setDOFVector( getInterpolatedJointDOFS(frameNumber * DUMP_SEC_PER_FRAME) );

		// Let the user know which frame is being rendered
		sprintf(msg, "Status: Rendering frame %d...", frameNumber);
		status->set_text(msg);

		// Render the frame
		display();
	}
	frameToFile = 0;

	// Let the user know how many frames were generated
	sprintf(msg, "Status: %d frame(s) rendered to file", numFrames);
	status->set_text(msg);
}

// Quit button handler.  Called when the "quit" button is pressed.
void quitButton(int)
{
  exit(0);
}

// Initialize GLUI and the user interface
void initGlui()
{
	GLUI_Panel* glui_panel;
	GLUI_Spinner* glui_spinner;
	GLUI_RadioGroup* glui_radio_group;

    GLUI_Master.set_glutIdleFunc(NULL);


	// Create GLUI window (joint controls) ***************
	//
	glui_joints = GLUI_Master.create_glui("Joint Control", 0, Win[0]+12, 0);

    // Create controls to specify root position and orientation
	glui_panel = glui_joints->add_panel("Root");

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "translate x:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::ROOT_TRANSLATE_X));
	glui_spinner->set_float_limits(ROOT_TRANSLATE_X_MIN, ROOT_TRANSLATE_X_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "translate y:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::ROOT_TRANSLATE_Y));
	glui_spinner->set_float_limits(ROOT_TRANSLATE_Y_MIN, ROOT_TRANSLATE_Y_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "translate z:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::ROOT_TRANSLATE_Z));
	glui_spinner->set_float_limits(ROOT_TRANSLATE_Z_MIN, ROOT_TRANSLATE_Z_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "rotate x:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::ROOT_ROTATE_X));
	glui_spinner->set_float_limits(ROOT_ROTATE_X_MIN, ROOT_ROTATE_X_MAX, GLUI_LIMIT_WRAP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "rotate y:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::ROOT_ROTATE_Y));
	glui_spinner->set_float_limits(ROOT_ROTATE_Y_MIN, ROOT_ROTATE_Y_MAX, GLUI_LIMIT_WRAP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "rotate z:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::ROOT_ROTATE_Z));
	glui_spinner->set_float_limits(ROOT_ROTATE_Z_MIN, ROOT_ROTATE_Z_MAX, GLUI_LIMIT_WRAP);
	glui_spinner->set_speed(SPINNER_SPEED);

	// Create controls to specify head rotation
	glui_panel = glui_joints->add_panel("Head");

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "head:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::HEAD));
	glui_spinner->set_float_limits(HEAD_MIN, HEAD_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	// Create controls to specify beak
	glui_panel = glui_joints->add_panel("Beak");

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "beak:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::BEAK));
	glui_spinner->set_float_limits(BEAK_MIN, BEAK_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);


	glui_joints->add_column(false);


	// Create controls to specify right arm
	glui_panel = glui_joints->add_panel("Right arm");
	
	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "arm scale:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::R_ARM_SCALE));
	glui_spinner->set_float_limits(ARM_SCALE_MIN, ARM_SCALE_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);
	
	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "shoulder pitch:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::R_SHOULDER_PITCH));
	glui_spinner->set_float_limits(SHOULDER_PITCH_MIN, SHOULDER_PITCH_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "shoulder yaw:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::R_SHOULDER_YAW));
	glui_spinner->set_float_limits(SHOULDER_YAW_MIN, SHOULDER_YAW_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "shoulder roll:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::R_SHOULDER_ROLL));
	glui_spinner->set_float_limits(SHOULDER_ROLL_MIN, SHOULDER_ROLL_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "elbow:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::R_ELBOW));
	glui_spinner->set_float_limits(ELBOW_MIN, ELBOW_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	// Create controls to specify left arm
	glui_panel = glui_joints->add_panel("Left arm");
	
	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "arm scale:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::L_ARM_SCALE));
	glui_spinner->set_float_limits(ARM_SCALE_MIN, ARM_SCALE_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "shoulder pitch:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::L_SHOULDER_PITCH));
	glui_spinner->set_float_limits(SHOULDER_PITCH_MIN, SHOULDER_PITCH_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "shoulder yaw:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::L_SHOULDER_YAW));
	glui_spinner->set_float_limits(SHOULDER_YAW_MIN, SHOULDER_YAW_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "shoulder roll:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::L_SHOULDER_ROLL));
	glui_spinner->set_float_limits(SHOULDER_ROLL_MIN, SHOULDER_ROLL_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "elbow:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::L_ELBOW));
	glui_spinner->set_float_limits(ELBOW_MIN, ELBOW_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);


	glui_joints->add_column(false);


	// Create controls to specify right leg
	glui_panel = glui_joints->add_panel("Right leg");

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "hip pitch:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::R_HIP_PITCH));
	glui_spinner->set_float_limits(HIP_PITCH_MIN, HIP_PITCH_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "hip yaw:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::R_HIP_YAW));
	glui_spinner->set_float_limits(HIP_YAW_MIN, HIP_YAW_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "hip roll:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::R_HIP_ROLL));
	glui_spinner->set_float_limits(HIP_ROLL_MIN, HIP_ROLL_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "knee:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::R_KNEE));
	glui_spinner->set_float_limits(KNEE_MIN, KNEE_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	// Create controls to specify left leg
	glui_panel = glui_joints->add_panel("Left leg");

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "hip pitch:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::L_HIP_PITCH));
	glui_spinner->set_float_limits(HIP_PITCH_MIN, HIP_PITCH_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "hip yaw:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::L_HIP_YAW));
	glui_spinner->set_float_limits(HIP_YAW_MIN, HIP_YAW_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "hip roll:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::L_HIP_ROLL));
	glui_spinner->set_float_limits(HIP_ROLL_MIN, HIP_ROLL_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_spinner = glui_joints->add_spinner_to_panel(glui_panel, "knee:", GLUI_SPINNER_FLOAT, joint_ui_data->getDOFPtr(Keyframe::L_KNEE));
	glui_spinner->set_float_limits(KNEE_MIN, KNEE_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);


	///////////////////////////////////////////////////////////
	// TODO (for controlling light source position & additional
	//      rendering styles):
	//   Add more UI spinner elements here. Be sure to also
	//   add the appropriate min/max range values to this
	//   file, and to also add the appropriate enums to the
	//   enumeration in the Keyframe class (keyframe.h).
	///////////////////////////////////////////////////////////

	//
	// ***************************************************


	// Create GLUI window (keyframe controls) ************
	//
	glui_keyframe = GLUI_Master.create_glui("Keyframe Control", 0, 0, Win[1]+64);

	// Create a control to specify the time (for setting a keyframe)
	glui_panel = glui_keyframe->add_panel("", GLUI_PANEL_NONE);
	glui_spinner = glui_keyframe->add_spinner_to_panel(glui_panel, "Time:", GLUI_SPINNER_FLOAT, joint_ui_data->getTimePtr());
	glui_spinner->set_float_limits(TIME_MIN, TIME_MAX, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	// Create a control to specify a keyframe (for updating / loading a keyframe)
	glui_keyframe->add_column_to_panel(glui_panel, false);
	glui_spinner = glui_keyframe->add_spinner_to_panel(glui_panel, "Keyframe ID:", GLUI_SPINNER_INT, joint_ui_data->getIDPtr());
	glui_spinner->set_int_limits(KEYFRAME_MIN, KEYFRAME_MAX-1, GLUI_LIMIT_CLAMP);
	glui_spinner->set_speed(SPINNER_SPEED);

	glui_keyframe->add_separator();

	// Add buttons to load and update keyframes
	// Add buttons to load and save keyframes from a file
	// Add buttons to start / stop animation and to render frames to file
	glui_panel = glui_keyframe->add_panel("", GLUI_PANEL_NONE);
	glui_keyframe->add_button_to_panel(glui_panel, "Load Keyframe", 0, loadKeyframeButton);
	glui_keyframe->add_button_to_panel(glui_panel, "Load Keyframes From File", 0, loadKeyframesFromFileButton);
	glui_keyframe->add_button_to_panel(glui_panel, "Start / Stop Animation", 0, animateButton);
	glui_keyframe->add_column_to_panel(glui_panel, false);
	glui_keyframe->add_button_to_panel(glui_panel, "Update Keyframe", 0, updateKeyframeButton);
	glui_keyframe->add_button_to_panel(glui_panel, "Save Keyframes To File", 0, saveKeyframesToFileButton);
	glui_keyframe->add_button_to_panel(glui_panel, "Render Frames To File", 0, renderFramesToFileButton);

	glui_keyframe->add_separator();

	// Add status line
	glui_panel = glui_keyframe->add_panel("");
	status = glui_keyframe->add_statictext_to_panel(glui_panel, "Status: Ready");

	// Add button to quit
	glui_panel = glui_keyframe->add_panel("", GLUI_PANEL_NONE);
	glui_keyframe->add_button_to_panel(glui_panel, "Quit", 0, quitButton);
	//
	// ***************************************************


	// Create GLUI window (render controls) ************
	//
	glui_render = GLUI_Master.create_glui("Render Control", 0, 367, Win[1]+64);

	// Create control to specify the render style
	glui_panel = glui_render->add_panel("Render Style");
	glui_radio_group = glui_render->add_radiogroup_to_panel(glui_panel, &renderStyle);
	glui_render->add_radiobutton_to_group(glui_radio_group, "Wireframe");
	glui_render->add_radiobutton_to_group(glui_radio_group, "Solid");
	glui_render->add_radiobutton_to_group(glui_radio_group, "Solid w/ outlines");
	//
	// ***************************************************


	// Tell GLUI windows which window is main graphics window
	glui_joints->set_main_gfx_window(windowID);
	glui_keyframe->set_main_gfx_window(windowID);
	glui_render->set_main_gfx_window(windowID);
}


// Performs most of the OpenGL intialization
void initGl(void)
{
    // glClearColor (red, green, blue, alpha)
    // Ignore the meaning of the 'alpha' value for now
    glClearColor(0.7f,0.7f,0.9f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}


// Calculates the interpolated joint DOF vector
// using Catmull-Rom interpolation of the keyframes
Vector getInterpolatedJointDOFS(float time)
{
	// Need to find the keyframes bewteen which
	// the supplied time lies.
	// At the end of the loop we have:
	//    keyframes[i-1].getTime() < time <= keyframes[i].getTime()
	//
	int i = 0;
	while( i <= maxValidKeyframe && keyframes[i].getTime() < time )
		i++;

	// If time is before or at first defined keyframe, then
	// just use first keyframe pose
	if( i == 0 )
		return keyframes[0].getDOFVector();

	// If time is beyond last defined keyframe, then just
	// use last keyframe pose
	if( i > maxValidKeyframe )
		return keyframes[maxValidKeyframe].getDOFVector();

	// Need to normalize time to (0, 1]
	time = (time - keyframes[i-1].getTime()) / (keyframes[i].getTime() - keyframes[i-1].getTime());

	// Get appropriate data points and tangent vectors
	// for computing the interpolation
	Vector p0 = keyframes[i-1].getDOFVector();
	Vector p1 = keyframes[i].getDOFVector();
	
	// Linear interpolation.
	return p0 + (p1-p0)*time;
}


// Callback idle function for animating the scene
void animate()
{
	// Only update if enough time has passed
	// (This locks the display to a certain frame rate rather
	//  than updating as fast as possible. The effect is that
	//  the animation should run at about the same rate
	//  whether being run on a fast machine or slow machine)
	if( frameRateTimer->elapsed() > SEC_PER_FRAME )
	{
		// Tell glut window to update itself. This will cause the display()
		// callback to be called, which renders the object (once you've written
		// the callback).
		glutSetWindow(windowID);
		glutPostRedisplay();

		// Restart the frame rate timer
		// for the next frame
		frameRateTimer->reset();
	}
}


// Handles the window being resized by updating the viewport
// and projection matrices
void reshape(int w, int h)
{
	// Update internal variables and OpenGL viewport
	Win[0] = w;
	Win[1] = h;
	glViewport(0, 0, (GLsizei)Win[0], (GLsizei)Win[1]);

    // Setup projection matrix for new window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(CAMERA_FOVY, (GLdouble)Win[0]/(GLdouble)Win[1], NEAR_CLIP, FAR_CLIP);
}



// display callback
//
// README: This gets called by the event handler
// to draw the scene, so this is where you need
// to build your scene -- make your changes and
// additions here. All rendering happens in this
// function. For Assignment 2, updates to the
// joint DOFs (joint_ui_data) happen in the
// animate() function.
void display(void)
{
    // Clear the screen with the background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    // Setup the model-view transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// Specify camera transformation
    glTranslatef(camXPos, camYPos, camZPos);
    glRotatef(g_fCamRotateX,0,1,0);
    glRotatef(g_fCamRotateY,1,0,0);
	// Get the time for the current animation step, if necessary
	if( animate_mode )
	{
		float curTime = animationTimer->elapsed();

		if( curTime >= keyframes[maxValidKeyframe].getTime() )
		{
			// Restart the animation
			animationTimer->reset();
			curTime = animationTimer->elapsed();
		}

		///////////////////////////////////////////////////////////
		// README:
		//   This statement loads the interpolated joint DOF vector
		//   into the global 'joint_ui_data' variable. Use the
		//   'joint_ui_data' variable below in your model code to
		//   drive the model for animation.
		///////////////////////////////////////////////////////////
		// Get the interpolated joint DOFs
		joint_ui_data->setDOFVector( getInterpolatedJointDOFS(curTime) );

		// Update user interface
		joint_ui_data->setTime(curTime);
		glui_keyframe->sync_live();
	}


    ///////////////////////////////////////////////////////////
    // TODO:
	//   Modify this function to draw the scene.
	//   This should include function calls that apply
	//   the appropriate transformation matrices and render
	//   the individual body parts.
	//   Use the 'joint_ui_data' data structure to obtain
	//   the joint DOFs to specify your transformations.
	//   Sample code is provided below and demonstrates how
	//   to access the joint DOF values. This sample code
	//   should be replaced with your own.
	//   Use the 'renderStyle' variable and the associated
	//   enumeration to determine how the geometry should be
	//   rendered.
    ///////////////////////////////////////////////////////////

	// SAMPLE CODE **********
	//
	glPushMatrix();

		// setup transformation for body part
		glTranslatef(joint_ui_data->getDOF(Keyframe::ROOT_TRANSLATE_X),
					 joint_ui_data->getDOF(Keyframe::ROOT_TRANSLATE_Y),
					 joint_ui_data->getDOF(Keyframe::ROOT_TRANSLATE_Z));
		//glRotatef(30.0, 0.0, 1.0, 0.0);
		glRotatef(30.0, 1.0, 0.0, 0.0);

		// determine render style and set glPolygonMode appropriately

		// draw body part
		/*Polygon newPoly;
		Vector* newver = new Vector[4];
		newver[0] = *(new Vector(0.0,0.0,0.0));
		newver[1] = *(new Vector(1.0,0.0,0.0));
		newver[2] = *(new Vector(1.0,1.0,0.0));
		newver[3] = *(new Vector(0.0,1.0,0.0));
		newPoly.SetVertex(newver,4);
		//newPoly.draw();*/
		glColor3f(1.0, 1.0, 1.0);
		if(renderStyle == WIREFRAME){
			g_RenderController.SetMode(Wireframe);
		}
		else if(renderStyle == OUTLINED){
			g_RenderController.SetMode(Outlined);
		}
		else if(renderStyle == SOLID){
			g_RenderController.SetMode(Solid);
		}
		g_RenderController.Render();
		//drawCube();
	glPopMatrix();
	//
	// SAMPLE CODE **********

    // Execute any GL functions that are in the queue just to be safe
    glFlush();

	// Dump frame to file, if requested
	if( frameToFile )
	{
		sprintf(filenameF, "frame%03d.ppm", frameNumber);
		writeFrame(filenameF, false, false);
	}

    // Now, show the frame buffer that we just drew into.
    // (this prevents flickering).
    glutSwapBuffers();
}


// Handles mouse button pressed / released events
void mouse(int button, int state, int x, int y)
{
	// If the RMB is pressed and dragged then zoom in / out
	if( button == GLUT_MIDDLE_BUTTON )
	{
		if( state == GLUT_DOWN )
		{
			lastX = x;
			lastY = y;
			updateCamZPos = true;
		}
		else
		{
			updateCamZPos = false;
		}
	}
	else if(button == GLUT_RIGHT_BUTTON){
		if( state == GLUT_DOWN){
			g_rotationX = x;
			g_rotationY = y;
			g_iUpdateCamRotation =true;
		}
		else{
			g_iUpdateCamRotation = false;
		}
	}
	else if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			PanningX = x;
			PanningY = y;
			updateCamXYPos = true;
		}
		else{
			updateCamXYPos = false;
		}
	}
}


// Handles mouse motion events while a button is pressed
void motion(int x, int y)
{
	// If the RMB is pressed and dragged then zoom in / out
	if( updateCamZPos )
	{
		// Update camera z position
		camZPos += (x - lastX) * ZOOM_SCALE;
		lastX = x;

		// Redraw the scene from updated camera position
		glutSetWindow(windowID);
		glutPostRedisplay();
	}
	if(g_iUpdateCamRotation){
		g_fCamRotateX += (x-g_rotationX) * RAD * ROTATION_SCALE;
		g_fCamRotateY += (y-g_rotationY) * RAD * ROTATION_SCALE;
		g_rotationX = x;
		g_rotationY = y;
		glutSetWindow(windowID);
		glutPostRedisplay();
	}
	if(updateCamXYPos){
		camXPos += (x - PanningX) * ZOOM_SCALE;
		camYPos -= (y - PanningY) * ZOOM_SCALE;
		PanningX = x;
		PanningY = y;
		glutSetWindow(windowID);
		glutPostRedisplay();
	}
}

void keyboard(unsigned char c, int x, int y){
	switch(c){
	case 'w':
		camZPos += MOVEMENT_PACE;
		break;
	case 's':
		camZPos -= MOVEMENT_PACE;
		break;
	case 'a':
		camXPos -= MOVEMENT_PACE;
		break;
	case 'd':
		camXPos += MOVEMENT_PACE;
		break;
	default:
		std::cout<<"wow"<<std::endl;
		break;
	}
	//glutSetWindow(windowID);
	//glutPostRedisplay();
}

// Draw a unit cube, centered at the current location
// README: Helper code for drawing a cube
void drawCube()
{
	glColor3f(1,0,0);
	glBegin(GL_QUADS);
		// draw front face
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f( 1.0, -1.0, 1.0);
		glVertex3f( 1.0,  1.0, 1.0);
		glVertex3f(-1.0,  1.0, 1.0);
	glEnd();
	glColor3f(1,0,1);
	glBegin(GL_QUADS);
		// draw back face
		glVertex3f( 1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0,  1.0, -1.0);
		glVertex3f( 1.0,  1.0, -1.0);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_QUADS);
		// draw left face
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0,  1.0);
		glVertex3f(-1.0,  1.0,  1.0);
		glVertex3f(-1.0,  1.0, -1.0);
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_QUADS);
		// draw right face
		glVertex3f( 1.0, -1.0,  1.0);
		glVertex3f( 1.0, -1.0, -1.0);
		glVertex3f( 1.0,  1.0, -1.0);
		glVertex3f( 1.0,  1.0,  1.0);

		// draw top
		glVertex3f(-1.0,  1.0,  1.0);
		glVertex3f( 1.0,  1.0,  1.0);
		glVertex3f( 1.0,  1.0, -1.0);
		glVertex3f(-1.0,  1.0, -1.0);

		// draw bottom
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f( 1.0, -1.0, -1.0);
		glVertex3f( 1.0, -1.0,  1.0);
		glVertex3f(-1.0, -1.0,  1.0);
	glEnd();
}

///////////////////////////////////////////////////////////
//
// BELOW ARE FUNCTIONS FOR GENERATING IMAGE FILES (PPM/PGM)
//
///////////////////////////////////////////////////////////

void writePGM(char* filename, GLubyte* buffer, int width, int height, bool raw=true)
{
	FILE* fp = fopen(filename,"wt");

	if( fp == NULL )
	{
		printf("WARNING: Can't open output file %s\n",filename);
		return;
	}

	if( raw )
	{
		fprintf(fp,"P5\n%d %d\n%d\n",width,height,255);
		for(int y=height-1;y>=0;y--)
		{
			fwrite(&buffer[y*width],sizeof(GLubyte),width,fp);
			/*
			for(int x=0;x<width;x++)
			{
				fprintf(fp,"%c",int(buffer[x+y*width];
			}
			*/
		}
	}
	else
	{
		fprintf(fp,"P2\n%d %d\n%d\n",width,height,255);
		for(int y=height-1;y>=0;y--)
		{
			for(int x=0;x<width;x++)
			{
				fprintf(fp,"%d ",*((int *)(&buffer[x+y*width])));
			}
			fprintf(fp,"\n");
		}
	}

	fclose(fp);
}

#define RED_OFFSET   0
#define GREEN_OFFSET 1
#define BLUE_OFFSET  2

void writePPM(char* filename, GLubyte* buffer, int width, int height, bool raw=true)
{
	FILE* fp = fopen(filename,"wt");

	if( fp == NULL )
	{
		printf("WARNING: Can't open output file %s\n",filename);
		return;
	}

	if( raw )
	{
		fprintf(fp,"P6\n%d %d\n%d\n",width,height,255);
		for(int y=height-1;y>=0;y--)
		{
			for(int x=0;x<width;x++)
			{
				GLubyte* pix = &buffer[4*(x+y*width)];

				fprintf(fp,"%c%c%c",int(pix[RED_OFFSET]),
									int(pix[GREEN_OFFSET]),
									int(pix[BLUE_OFFSET]));
			}
		}
	}
	else
	{
		fprintf(fp,"P3\n%d %d\n%d\n",width,height,255);
		for(int y=height-1;y>=0;y--)
		{
			for(int x=0;x<width;x++)
			{
				GLubyte* pix = &buffer[4*(x+y*width)];

				fprintf(fp,"%d %d %d ",int(pix[RED_OFFSET]),
									   int(pix[GREEN_OFFSET]),
									   int(pix[BLUE_OFFSET]));
			}
			fprintf(fp,"\n");
		}
	}

	fclose(fp);
}

void writeFrame(char* filename, bool pgm, bool frontBuffer)
{
	static GLubyte* frameData = NULL;
	static int currentSize = -1;

	int size = (pgm ? 1 : 4);

	if( frameData == NULL || currentSize != size*Win[0]*Win[1] )
	{
		if (frameData != NULL)
			delete [] frameData;

		currentSize = size*Win[0]*Win[1];

		frameData = new GLubyte[currentSize];
	}

	glReadBuffer(frontBuffer ? GL_FRONT : GL_BACK);

	if( pgm )
	{
		glReadPixels(0, 0, Win[0], Win[1],
					 GL_LUMINANCE, GL_UNSIGNED_BYTE, frameData);
		writePGM(filename, frameData, Win[0], Win[1]);
	}
	else
	{
		glReadPixels(0, 0, Win[0], Win[1],
					 GL_RGBA, GL_UNSIGNED_BYTE, frameData);
		writePPM(filename, frameData, Win[0], Win[1]);
	}
}
