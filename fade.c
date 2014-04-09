#include <cairo/cairo-xlib.h>
#include "window.h"
#include "constants.h"
#include "fade.h"

double fade = 1;

void showFade(cairo_t* cairo, cairo_surface_t* backgroundA, cairo_surface_t* backgroundB, double fade) {
	cairo_set_source_rgb(cairo, 0,0,0);
	cairo_rectangle(cairo, 0, 0, WIDTH, HEIGHT);
	cairo_fill(cairo);
	cairo_set_source_surface(cairo, backgroundA, 0,0);
	cairo_paint_with_alpha(cairo, fade);
	cairo_set_source_surface(cairo, backgroundB, 0,0);
	cairo_paint_with_alpha(cairo, 1-fade);
}

void fadeBetween(cairo_t* cairo, cairo_surface_t* backgroundA, cairo_surface_t* backgroundB, int interval) {
	double fade = 0;
	while(fade < 1) {
		fade += 0.01;
		showFade(cairo, backgroundA, backgroundB, fade);
		updateScreen();
		usleep(interval);
	}
}
