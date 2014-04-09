#include <cairo/cairo-xlib.h>
#include "window.h"
#include "heart.h"
#include "constants.h"

void cairo_close_path_inverted(cairo_t* cairo)  {
	/**
	 *     6   2
	 *    _______
	 *   |   |   |
	 *   | 7 | 1 |
	 * 5 |   O   | 3
	 *   |       |
	 *   |_______|
	 *       4
	 */
	cairo_rel_line_to(cairo, 0, -5000); // 1
	cairo_rel_line_to(cairo, 5000, 0); // 2
	cairo_rel_line_to(cairo, 0, 10000); // 3
	cairo_rel_line_to(cairo, -10000, 0); // 4
	cairo_rel_line_to(cairo, 0, -10000); // 5
	cairo_rel_line_to(cairo, 5000, 0); // 6
	cairo_rel_line_to(cairo, 0, 5000); // 7
	cairo_close_path(cairo);
}

void drawHeart(cairo_t* cairo, int x, int y, int w, int h, int speed) {
	x = 50; y = 50; w = 200; h = 200;
	double len = 0;
	cairo_set_source_rgb(cairo, 0.9, 0.5, 0.5);
	cairo_new_path(cairo);
	cairo_set_line_width(cairo, 11);
	cairo_set_line_cap(cairo, CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cairo, x, y);
	while(len < 1) {
		len += 0.1;
		cairo_line_to(cairo, x + w*len, y + h*len);
		cairo_stroke_preserve(cairo);
		updateScreen();
		usleep(speed);
	}
	len = 0;
	while(len < 1) {
		len += 0.1;
		cairo_line_to(cairo, x + w, y + h - h*len);
		cairo_stroke_preserve(cairo);
		updateScreen();
		usleep(speed);
	}
	cairo_line_to(cairo, x, y);
}

void fadeOutSelection(cairo_t* cairo) {
	cairo_close_path_inverted(cairo);
	cairo_set_source_rgba(cairo, 1, 1, 1, 0.15);
	double fade;
	for(fade = 0; fade <= 1; fade += .02) {
		cairo_set_source_rgba(cairo, 1, 1, 1, fade);
		cairo_fill_preserve(cairo);
		updateScreen();
		drawHeart(cairo, 0,0,0,0,0);
		cairo_close_path_inverted(cairo);
		usleep(10000);
	}
}
