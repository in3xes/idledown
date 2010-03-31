/*A daemon to shutdown idle computer				*\
*								*
\*(C) 2010 Pradeepkumar Gayam<deepu.aprjc@gmail.com>		*/

/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License with
  the Debian GNU/Linux distribution in file /usr/doc/copyright/GPL;
  if not, write to the Free Software Foundation, Inc., 59 Temple Place,
  Suite 330, Boston, MA  02111-1307  USA
*/

#include "id.h"

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

//testing

/*testing

agian8
*/
/*branch test
*/
