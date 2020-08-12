#ifndef __UTIL_H
#define __UTIL_H

#include <GL/freeglut.h>
#include "event.h"
#include "callbacks.h"
#include "classes/classGame.h"
#include "api.h"

void initOpenGL(int, char**, int, int, api * ap, int idle);
void utilityCentral(Event *);
#endif
