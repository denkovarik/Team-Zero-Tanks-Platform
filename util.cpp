#include "util.h"

void utilityCentral(Event *event)
{
  static Game game;

  event->doAction(game);
  delete event;
}

/***************************************************************************//**
 * Initialize glut callback functions, set the display mode, create a window
 ******************************************************************************/
void initOpenGL(int argc, char** argv, int wCols, int wRows, api *ap, int idle)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);

  glutInitWindowSize(wCols, wRows);

  glutInitWindowPosition(75, 10);

  glutCreateWindow("BattleTanks");

  glutDisplayFunc(display);

  glutKeyboardFunc(keyboard);

  glutMouseFunc(mouseClick);

  glutReshapeFunc(reshape);

  glutTimerFunc(idle, ticktock, idle);

  glutCloseFunc(onClose);

  glClearColor(0.0f, 0.5f, 0.0f, 0.0f);

  utilityCentral(new InitEvent(wCols, wRows, ap));
}
