#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include "window.h"
#include "constants.h"

static cairo_surface_t *xsurface;
static cairo_surface_t *surface;
static cairo_surface_t *surface_copy;
static cairo_t *cairo;
static cairo_t *cairo_copy;
static cairo_t *xcairo;
static Display *dpy;
Window w;

void saveState() {
	cairo_set_source_surface(cairo_copy, surface, 0, 0);
	cairo_rectangle(cairo_copy, 0, 0, WIDTH, HEIGHT);
	cairo_fill(cairo_copy);
}

void restoreState() {
	cairo_rectangle(cairo, 0, 0, WIDTH, HEIGHT);
	cairo_set_source_surface(cairo, surface_copy, 0, 0);
	cairo_fill(cairo);
	updateScreen();
}

void restoreStatePartial(int x, int y, int w, int h) {
	cairo_rectangle(cairo, x, y, w, h);
	cairo_set_source_surface(cairo, surface_copy, 0, 0);
	cairo_fill(cairo);
	updateScreen();
}

void shift(int x, int y) {
	saveState();
	cairo_set_source_rgb(cairo, 1,1,1);
	cairo_rectangle(cairo, 0, 0, WIDTH, HEIGHT);
	cairo_fill(cairo);
	cairo_rectangle(cairo, 0, 0, WIDTH, HEIGHT);
	cairo_set_source_surface(cairo, surface_copy, x, y);
	cairo_fill(cairo);
	updateScreen();
}

void updateScreen() {
	cairo_set_source_surface(xcairo, surface, 0, 0);
	cairo_rectangle(xcairo, 0, 0, WIDTH, HEIGHT);
	cairo_fill(xcairo);
	consumeEvents();
}

void consumeEvents() {
	while (XPending(dpy)) {
		XEvent e;
		XNextEvent(dpy, &e);
		printf("Got event: %d\n", e.type);

		switch (e.type) {
			case Expose:
				//paint(cairo, backgroundA, backgroundB, fade);
				break;
		}
	}
}

cairo_surface_t* getSavedSurface() {
	return surface_copy;
}

int openWindow() {
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		fprintf(stderr, "Error: Can't open display. Is DISPLAY set?\n");
		return 0;
	}

	w = XCreateSimpleWindow(dpy, RootWindow(dpy, 0),
	                        0, 0, WIDTH, HEIGHT, 0, 0, BlackPixel(dpy, 0));

	XMapWindow(dpy, w);
	XEvent e;

	xsurface = cairo_xlib_surface_create(dpy, w, DefaultVisual(dpy, 0), WIDTH, HEIGHT);
	xcairo = cairo_create(xsurface);
	surface = cairo_surface_create_similar(xsurface, CAIRO_CONTENT_COLOR_ALPHA, WIDTH, HEIGHT);
	surface_copy = cairo_surface_create_similar(xsurface, CAIRO_CONTENT_COLOR_ALPHA, WIDTH, HEIGHT);
	cairo_copy = cairo_create(surface_copy);
	cairo = cairo_create(surface);
	cairo_set_source_surface(xcairo, surface, 0, 0);
	return 1;
}

cairo_t* getCairo() {
	return cairo;
}

cairo_t* getDirectCairo() {
	return xcairo;
}
