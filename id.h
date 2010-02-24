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

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>
#include <X11/extensions/scrnsaver.h>

unsigned long workaroundCreepyXServer(Display *dpy, unsigned long _idleTime );
int idletime();

