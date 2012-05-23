/*=================================================================================================
     Author: Renato Farias (renatomdf@gmail.com)
 Created on: April 20th, 2012
 Updated on: May 23rd, 2012
    Purpose: To be a simple, bare-bones starting point for 2D OpenGL applications using GLUT.
=================================================================================================*/

/*=================================================================================================
  INCLUDES
=================================================================================================*/

#include <GL/glut.h>

/*=================================================================================================
  DEFINES
=================================================================================================*/

// Initial window dimensions
#define INIT_WINDOW_WIDTH  800
#define INIT_WINDOW_HEIGHT 600

// Initial window position
#define INIT_WINDOW_POS_X 0
#define INIT_WINDOW_POS_Y 0

/*=================================================================================================
  GLOBALS
=================================================================================================*/

// Current window dimensions
int WindowWidth  = INIT_WINDOW_WIDTH;
int WindowHeight = INIT_WINDOW_HEIGHT;

// Last mouse cursor position
int LastMousePosX;
int LastMousePosY;

// Arrays that track what keys are currently pressed
bool KeyStates[256];
bool KeySpecialStates[256];
bool MouseKeyStates[8];

// Is the window currently fullscreen?
bool FullScreen = false;

// Pop-up menus
int MenuId, SubMenuId;
enum MenuEntries {
	ENTRY_QUIT = 0,
	ENTRY_FULLSCREEN_ENTER,
	ENTRY_FULLSCREEN_LEAVE
};

/*=================================================================================================
  FUNCTIONS
=================================================================================================*/

// Function that draws the next frame
void DisplayFunc( void ) {

	// Clear window
	glClear( GL_COLOR_BUFFER_BIT );

	/*
	    Draw code goes here
	                         */

	// Swap buffers, flushing to screen
	glutSwapBuffers();

}

// Called when there is nothing to do
void IdleFunc( void ) {

	// Uncomment the following to repeatedly update the window
	//glutPostRedisplay();

}

// Makes the necessary adjustments if the window is resized
void ReshapeFunc( int width, int height ) {

	// Adjust the viewport
	glViewport( 0, 0, (GLsizei)width, (GLsizei)height );

	// Update current window dimensions
	WindowWidth  = width;
	WindowHeight = height;

}

// Called when a (ASCII) keyboard key is pressed
void KeyboardFunc( unsigned char key, int x, int y ) {  

	switch( key ) {
		// ESC exits the program
		case 27:
			exit(0);

		// f enters and leaves fullscreen mode
		case 'f':
			FullScreen = !FullScreen;
			FullScreen ? glutFullScreen() : glutPositionWindow(0,0);
			break;
	}

	// Set the state of the current key to pressed
	KeyStates[key] = true;

}

// Called when a (ASCII) keyboard key is released
void KeyboardUpFunc( unsigned char key, int x, int y ) {  

	// Set the state of the current key to released
	KeyStates[key] = false;

}

// Called when a special keyboard key is pressed
void KeyboardSpecialFunc( int key, int x, int y ) {

	// Set the state of the current key to pressed
	KeySpecialStates[key] = true;

}

// Called when a special keyboard key is released
void KeyboardSpecialUpFunc( int key, int x, int y ) {

	// Set the state of the current key to released
	KeySpecialStates[key] = false;

}

// Called when a mouse button is pressed or released
void MouseFunc( int button, int state, int x, int y ) {

	// Key 0: left button
	// Key 1: middle button
	// Key 2: right button
	// Key 3: scroll up
	// Key 4: scroll down

	if( state == GLUT_DOWN ) {
		MouseKeyStates[ button ] = true;
	}
	else if( state == GLUT_UP ) {
		MouseKeyStates[ button ] = false;
	}

	// Update mouse cursor position
	LastMousePosX = x;
	LastMousePosY = y;

}

// Called when the mouse cursor is moved while a mouse button is pressed
void MotionFunc( int x, int y ) {

	// Update mouse cursor position
	LastMousePosX = x;
	LastMousePosY = y;

}

// Called when the mouse cursor is moved while no mouse buttons are pressed
void PassiveMotionFunc( int x, int y ) {

	// Update mouse cursor position
	LastMousePosX = x;
	LastMousePosY = y;

}

// Called when an item from a pop-up menu is selected
void MenuFunc( int value ) {

	switch( value ) {
		case ENTRY_QUIT:
			exit(0);

		case ENTRY_FULLSCREEN_ENTER:
			if( !FullScreen ) {
				glutFullScreen();
				FullScreen = true;
			}
			break;

		case ENTRY_FULLSCREEN_LEAVE:
			if( FullScreen ) {
				glutPositionWindow(0,0);
				FullScreen = false;
			}
			break;
	}

}

// Initializes variables and OpenGL settings
void Initialize( void ) {

	// Set the background color to white
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

	// Set up orthogonal projection with (0,0) at the top-left corner of the window
	glOrtho( 0, 1, 1, 0, -1 ,1 );

	// Create sub pop-up menu and add entries
	SubMenuId = glutCreateMenu( &MenuFunc );
	glutAddMenuEntry( "Enter FullScreen", ENTRY_FULLSCREEN_ENTER );
	glutAddMenuEntry( "Leave FullScreen", ENTRY_FULLSCREEN_LEAVE );

	// Create main pop-up menu and add entries
	MenuId = glutCreateMenu( &MenuFunc );
	glutAddSubMenu( "FullScreen", SubMenuId );
	glutAddMenuEntry( "Quit", ENTRY_QUIT );

	// Attach menu to right mouse button
	glutAttachMenu( GLUT_RIGHT_BUTTON );

}

// Where it all begins...
int main( int argc, char** argv ) {

	// Initialize GLUT and window properties
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize( INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT );
	glutInitWindowPosition( INIT_WINDOW_POS_X, INIT_WINDOW_POS_Y );

	// Create main OpenGL window
	glutCreateWindow( "OpenGL 2D" );

	// Initialize variables and settings
	Initialize();

	// Register callback functions
	glutDisplayFunc( DisplayFunc );
	glutIdleFunc( IdleFunc );
	glutReshapeFunc( ReshapeFunc );

	glutKeyboardFunc( KeyboardFunc );
	glutKeyboardUpFunc( KeyboardUpFunc );
	glutSpecialFunc( KeyboardSpecialFunc );
	glutSpecialUpFunc( KeyboardSpecialUpFunc );

	glutMouseFunc( MouseFunc );
	glutMotionFunc( MotionFunc );
	glutPassiveMotionFunc( PassiveMotionFunc );

	// Enter the main loop
	glutMainLoop();

	return 0;

}
