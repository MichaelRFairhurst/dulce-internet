#include <cairo/cairo-xlib.h>
#include <unistd.h>
#include "window.h"
#include "heart.h"
#include "line.h"
#include "constants.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

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
	double percentage = 0;

	cairo_set_source_rgb(cairo, 0.9, 0.5, 0.5);
	cairo_new_path(cairo);
	cairo_set_line_width(cairo, 11);
	cairo_set_line_cap(cairo, CAIRO_LINE_CAP_ROUND);

	while(percentage < 1) {
		drawHeartPercentage(cairo, x, y, w, h, percentage);
		cairo_stroke(cairo);
		percentage += 0.2;
		updateScreen();
		usleep(speed);
	}
}

void drawHeartPercentage(cairo_t* cairo, int x, int y, int w, int h, double percentage) {
	cairo_rectangle(cairo, x, y, x+w, y+h);
	percentage *= 4;
	int centerx = x + w*0.5;
	y = y + h;
	int topy = y - h * 1.2;
	int cheeky = y - h * 0.7;
	int curvey = y - h * 0.35;
	int curveleft = x + w * 0.2;
	int curveright = x + w * 0.8;

	cairo_move_to(cairo, centerx, y);
	coord midpoint;
	cutLine(centerx, y, curveleft, curvey, MAX(percentage, 1), &midpoint);
	//cairo_line_to(cairo, midpoint.x, midpoint.y);
	cairo_line_to(cairo, curveleft, curvey);

	percentage -= 1;
	if(percentage <= 0) return;

	cutLine(centerx, y, curveleft, curvey, 2.6, &midpoint);
	cairo_curve_to(cairo, midpoint.x, midpoint.y, centerx, topy, centerx, cheeky);

	cutLine(centerx, y, curveright, curvey, 2.6, &midpoint);
	cairo_curve_to(cairo, centerx, topy, midpoint.x, midpoint.y, curveright, curvey);
	cairo_line_to(cairo, centerx, y);

	cairo_stroke_preserve(cairo);
}

void fadeOutSelection(cairo_t* cairo) {
	cairo_close_path_inverted(cairo);
	cairo_set_source_rgba(cairo, 1, 1, 1, 0.15);
	double fade;
	for(fade = 0; fade <= 1; fade += .02) {
		cairo_set_source_rgba(cairo, 1, 1, 1, fade);
		cairo_fill_preserve(cairo);
		updateScreen();
		drawHeart(cairo, 20,20,200,200,0);
		cairo_close_path_inverted(cairo);
		usleep(10000);
	}
}
