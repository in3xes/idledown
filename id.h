#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>
#include <X11/extensions/scrnsaver.h>

unsigned long workaroundCreepyXServer(Display *dpy, unsigned long _idleTime );
int idletime();

