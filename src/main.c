/***** Includes *****/

#include <X11/Xlib.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/***** Local Variables *****/

unsigned int _height;
unsigned int _width;

/***** Local Functions *****/


/***** Global Functions *****/

int
main(void)
{
  Display * dpy;
  Window wdw;
  XWindowAttributes attr;
  XButtonEvent start;
  XEvent ev;

  dpy = XOpenDisplay(NULL);
  if(NULL == dpy) {
    return 1;
  }

  wdw = XDefaultRootWindow(dpy);
  XGetWindowAttributes(dpy, wdw, &attr);
  _height = attr.height;
  _width = attr.width;

  XGrabKey(
    dpy,
    XKeysymToKeycode(dpy, XStringToKeysym("Tab")),
    Mod4Mask, // this defaults to the "super"/"windows" key
    DefaultRootWindow(dpy),
    True,
    GrabModeAsync, 
    GrabModeAsync);

  XGrabKey(
    dpy,
    XKeysymToKeycode(dpy, XStringToKeysym("Space")),
    Mod4Mask, // this defaults to the "super"/"windows" key
    DefaultRootWindow(dpy),
    True,
    GrabModeAsync, 
    GrabModeAsync);

  XGrabButton(
    dpy,
    1,
    Mod4Mask,
    DefaultRootWindow(dpy),
    True,
    ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
    GrabModeAsync,
    GrabModeAsync,
    None,
    None);

  XGrabButton(
    dpy,
    3,
    Mod4Mask,
    DefaultRootWindow(dpy),
    True,
    ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
    GrabModeAsync,
    GrabModeAsync,
    None,
    None);

  //int revert_to;

  //XGetInputFocus(dpy, &wdw, &revert_to);
  //if (None != wdw) {
    //XMoveResizeWindow(dpy, wdw, 0, 0, _width, _height);
  //}

  start.subwindow = None;
  while (1) {
    XNextEvent(dpy, &ev);
    if(ev.type == KeyPress && ev.xkey.subwindow != None) {
      if (
      XLowerWindow(dpy, ev.xkey.subwindow);
    
    }
    else if(ev.type == ButtonPress && ev.xbutton.subwindow != None) {
      XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
      start = ev.xbutton;
    }
    else if(ev.type == MotionNotify && start.subwindow != None) {
      int xdiff = ev.xbutton.x_root - start.x_root;
      int ydiff = ev.xbutton.y_root - start.y_root;
      XMoveResizeWindow(dpy, start.subwindow,
        attr.x + (start.button==1 ? xdiff : 0),
        attr.y + (start.button==1 ? ydiff : 0),
        MAX(1, attr.width + (start.button==3 ? xdiff : 0)),
        MAX(1, attr.height + (start.button==3 ? ydiff : 0)));
    }
    else if (NULL) {
      // center and maximize
      XMoveResizeWindow(dpy, start.subwindow,
        0,
        0,
        _width,
        _height);
    }
    else if(ev.type == ButtonRelease) {
      start.subwindow = None;
    }
  }
}
