#include "event.h"
#include "classes/classGame.h"
Event::~Event() {}

/*******************************************************************************
 * @brief Constructor
 *
 * @param[in] c - columns (in pixels) of the window
 * @param[in] r - rows (in pixels) of the window
 ******************************************************************************/
InitEvent::InitEvent(int c, int r, api* newAp) : columns(c), rows(r){
this->ap = newAp;
}

void InitEvent::doAction(Game &game)
{
  glClear(GL_COLOR_BUFFER_BIT);
  game.setNewApi(ap);
  //game.initGameState();
}

void DisplayEvent::doAction(Game &game)
{
  glClear (GL_COLOR_BUFFER_BIT);
  game.drawGrid();
  game.drawTanks();
  game.drawObjects();
  game.drawProjectiles();
  game.headerText();

  if(game.gameOver)
    game.gameOverScreen();
  glutSwapBuffers();
}

/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] w - width (in pixels) of the window
 * @param[in] h - height (in pixels) of the window
 ******************************************************************************/
ReshapeEvent::ReshapeEvent(int w, int h) : width(w), height(h) {}

void ReshapeEvent::doAction(Game &game)
{
  //std::cout << "Reshaping window to [" << width << ", " << height << "]\n";
}

/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] b - the button that was pressed
 * @param[in] s - the state of the button that was pressed (0-down, 1-up)
 * @param[in] x - the x-coordinate of where the button 'b' was pressed/released
 * @param[in] y - the y-coordinate of where the button 'b' was pressed/released
 ******************************************************************************/
MouseClickEvent::MouseClickEvent(int b, int s, int x, int y) :
  button(b), state(s), xLoc(x), yLoc(y) {}

void MouseClickEvent::doAction(Game &game)
{ }

/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] x - the x-coordinate of where the button 'b' was pressed/released
 * @param[in] y - the y-coordinate of where the button 'b' was pressed/released
 ******************************************************************************/
MouseDragEvent::MouseDragEvent(int x, int y) : xLoc(x), yLoc(y) {}

void MouseDragEvent::doAction(Game &game) { }

/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] x - the x-coordinate of where the button 'b' was pressed/released
 * @param[in] y - the y-coordinate of where the button 'b' was pressed/released
 ******************************************************************************/
MouseMoveEvent::MouseMoveEvent(int x, int y) : xLoc(x), yLoc(y) {}

void MouseMoveEvent::doAction(Game &game)
{
  stringstream ss;

  ss << "x = " << xLoc << " :: y = " << yLoc;
  glutSetWindowTitle(ss.str().c_str());
}

/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] k - the ascii value of the key that was pressed
 * @param[in] x - the x-coordinate of where the key 'k' was pressed
 * @param[in] y - the y-coordinate of where the key 'k' was pressed
 ******************************************************************************/
KeyboardEvent::KeyboardEvent(unsigned char k, int x, int y) : key(k), xLoc(x), yLoc(y) {}

void KeyboardEvent::doAction(Game &game)
{
  if(key == ESCAPE_KEY || key == 'Q' || key == 'q')
    glutLeaveMainLoop();
}

/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] tick - the number of milliseconds to wait before the next timer
 *    tick
 ******************************************************************************/
TimerEvent::TimerEvent(int value) : tick(value) {}

void TimerEvent::doAction(Game &game)
{
  if(!game.gameOver)
    game.executeTurn();
  glutPostRedisplay();

}

/***************************************************************************//**
 * @brief Constructor
 ******************************************************************************/
CloseEvent::CloseEvent() {}

void CloseEvent::doAction(Game &game)
{
  game.closeDown();
}
