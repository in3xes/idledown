/*
#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>
#include <X11/extensions/scrnsaver.h>
#include <stdio.h>
*/
#include "id.h"

//unsigned long workaroundCreepyXServer(Display *dpy, unsigned long _idleTime );
//int idletime();

/*
int main()
{
	while(1) {
		idletime();
	}

	return 1;
}
*/


int idletime()
{
  XScreenSaverInfo ssi;
  Display *dpy;
  int event_basep, error_basep;

  
  dpy = XOpenDisplay(NULL);
  if (dpy == NULL) {
    fprintf(stderr, "couldn't open display\n");
  }
  if (!XScreenSaverQueryExtension(dpy, &event_basep, &error_basep)) {
    fprintf(stderr, "screen saver extension not supported\n");
  }
  
  if (!XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), &ssi)) {
    fprintf(stderr, "couldn't query screen saver info\n");
  }
  
  int time = 0;
  time = (int ) workaroundCreepyXServer(dpy, ssi.idle);
  XCloseDisplay(dpy);

	return time;
}

unsigned long workaroundCreepyXServer(Display *dpy, unsigned long _idleTime ){
  int dummy;
  CARD16 standby, suspend, off;
  CARD16 state;
  BOOL onoff;

  if (DPMSQueryExtension(dpy, &dummy, &dummy)) {
    if (DPMSCapable(dpy)) {
      DPMSGetTimeouts(dpy, &standby, &suspend, &off);
      DPMSInfo(dpy, &state, &onoff);

      if (onoff) {
        switch (state) {
          case DPMSModeStandby:
            /* this check is a littlebit paranoid, but be sure */
            if (_idleTime < (unsigned) (standby * 1000))
              _idleTime += (standby * 1000);
            break;
          case DPMSModeSuspend:
            if (_idleTime < (unsigned) ((suspend + standby) * 1000))
              _idleTime += ((suspend + standby) * 1000);
            break;
          case DPMSModeOff:
            if (_idleTime < (unsigned) ((off + suspend + standby) * 1000))
              _idleTime += ((off + suspend + standby) * 1000);
            break;
          case DPMSModeOn:
          default:
            break;
        }
      }
    } 
  }

  return _idleTime;
}


