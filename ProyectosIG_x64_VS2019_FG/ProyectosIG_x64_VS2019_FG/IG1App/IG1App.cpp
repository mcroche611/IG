#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()  
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();   

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mScene = new Scene;
	
	mCamera->set3D();
	mScene->init();
	mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL() 
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);
		
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   
	
	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 
	
	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutIdleFunc(s_update);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free() 
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mViewPort; mViewPort = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::display() const   
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (m2Vistas) 
	{
		display2V();
	}
	else 
		mScene->render(*mCamera); //1 vista
	
	glutSwapBuffers();	// swaps the front and back buffer
}

void IG1App::display2V() const
{ // se llama en display()
// para renderizar las vistas utilizamos una cámara auxiliar:
	Camera auxCam = *mCamera; // copiando mCamera
	// el puerto de vista queda compartido (se copia el puntero)
	Viewport auxVP = *mViewPort; // lo copiamos en una var. aux. para
	// el tamaño de los 4 puertos de vista es el mismo, lo configuramos

	mViewPort->setSize(mWinW / 2, mWinH);
	// igual que en resize, para que no cambie la escala,
	// tenemos que cambiar el tamaño de la ventana de vista de la cámara
	auxCam.setSize(mViewPort->width(), mViewPort->height());

	//vista 3D
	mViewPort->setPos(0, 0);
	// el tamaño de la ventana de vista es el mismo para las 4 vistas (ya configurado)
	// pero tenemos que cambiar la posición y orientación de la cámara
	auxCam.set3D();
	// renderizamos con la cámara y el puerto de vista configurados
	mScene->render(auxCam);

	//vista cenital
	mViewPort->setPos(mWinW / 2, 0);
	auxCam.setCenital();
	// renderizamos con la cámara y el puerto de vista configurados
	mScene->render(auxCam);	

	*mViewPort = auxVP; // restaurar el puerto de vista 
}

//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight) 
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height()); 
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y) 
{
	bool need_redisplay = true;
	
	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case 'r':
		//mCamera->orbit(glm::radians(1.0), glm::radians(1.0));
		//mCamera->orbit(glm::radians(0.0), glm::radians(1.0));
		mCamera->orbit(glm::radians(1.0), 500);
		break;
	//case 'R':
	//	//mCamera->orbit(glm::radians(1.0), glm::radians(1.0));
	//	mCamera->orbit(glm::radians(0.0), glm::radians(1.0));
	//	//mCamera->orbit(glm::radians(1.0), glm::radians(0.0));
	//	break;
	case '0':
		mScene->setState(0);
		break;
	case '1':
		mScene->setState(1);
		break;
	case '2':
		mScene->setState(2);
		break;
	case 'u':
		activeAnim = !activeAnim;
		break;
	case 'U':
		break;
	case 'p':
		mCamera->changePrj();
		break;
	case 'c':
		mCamera->setCenital();
		break;
	case 'k':
		setVistas();
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y) 
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)
	
	switch (key) {
	case GLUT_KEY_RIGHT:
			//mCamera->moveLR(1);
			mCamera->pitchReal(1);    // rotates 1 on the X axis
		break;
	case GLUT_KEY_LEFT:
			//mCamera->moveLR(-1);
			mCamera->pitchReal(-1);    // rotates 1 on the X axis
		break;
	case GLUT_KEY_UP:	
		if (mdf == GLUT_ACTIVE_CTRL)
			//mCamera->moveFB(1);
			mCamera->yawReal(1);     // rotate -1 on the Y axis 
		else
			//mCamera->moveUD(1);
			mCamera->rollReal(1);   // rotates -1 on the Z axis

		break;
	case GLUT_KEY_DOWN:
		if (mdf == GLUT_ACTIVE_CTRL)
			//mCamera->moveFB(-1);
			mCamera->yawReal(-1);     // rotate -1 on the Y axis 
		else
			//mCamera->moveUD(-1);
			mCamera->rollReal(-1);   // rotates -1 on the Z axis
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
void IG1App::update()
{
	if (activeAnim)
	{
		mScene->update();
		glutPostRedisplay();
	}
}

void IG1App::setVistas()
{
	m2Vistas = !m2Vistas;
}
//-------------------------------------------------------------------------

