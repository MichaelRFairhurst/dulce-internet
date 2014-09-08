#include <cairo/cairo-xlib.h>
#include <unistd.h>
#include "window.h"
#include "heart.h"
#include "line.h"
#include "constants.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void cairo_close_path_inverted(cairo_t* cairo) {
	/**
	 *       4
	 *    _______
	 *   |       |
	 *   |       |
	 * 5 |   O   | 3
	 *   | 7 | 1 |
	 *   |___|___|
	 *     6   2
	 */
	cairo_rel_line_to(cairo, 0, 5000); // 1
	cairo_rel_line_to(cairo, 5000, 0); // 2
	cairo_rel_line_to(cairo, 0, -10000); // 3
	cairo_rel_line_to(cairo, -10000, 0); // 4
	cairo_rel_line_to(cairo, 0, 10000); // 5
	cairo_rel_line_to(cairo, 5000, 0); // 6
	cairo_rel_line_to(cairo, 0, -5000); // 7
	cairo_close_path(cairo);
}

void drawHeart(cairo_t* cairo, int x, int y, int w, int h, int speed) {
	double percentage = 0.005;

	cairo_set_source_rgb(cairo, 0.9, 0.5, 0.5);
	cairo_new_path(cairo);
	cairo_set_line_width(cairo, 11);
	cairo_set_line_cap(cairo, CAIRO_LINE_CAP_ROUND);

	while(percentage <= 1) {
		cairo_t* target = percentage == 1 ? cairo : getDirectCairo();
		cairo_set_source_rgb(target, 0.9, 0.5, 0.5);
		cairo_new_path(target);
		cairo_set_line_width(target, 5);
		cairo_set_line_cap(target, CAIRO_LINE_CAP_ROUND);

		drawHeartPercentage(target, x, y, w, h, percentage);
		cairo_stroke_preserve(target);

		if(percentage == 1) updateScreen();
		percentage += 0.005;
		usleep(speed);
	}
}

void drawHeartPercentage(cairo_t* cairo, int x, int y, int w, int h, double percentage) {
	percentage *= 3;
	int centerx = x + w*0.5;
	y = y + h;
	int topy = y - h * 1.2;
	int cheeky = y - h * 0.7;
	int curvey = y - h * 0.35;
	int curveleft = x + w * 0.2;
	int curveright = x + w * 0.8;

	cairo_move_to(cairo, centerx, y);
	coord midpoint;
	cutLine(centerx, y, curveleft, curvey, MIN(percentage*2, 1), &midpoint);
	cairo_line_to(cairo, midpoint.x, midpoint.y);

	percentage -= 0.5;
	if(percentage <= 0) return;

	coord allBezierCoords[8];
	coord* bezierCoords[4] = { &allBezierCoords[0], &allBezierCoords[1], &allBezierCoords[2], &allBezierCoords[3] };
	coord* bezierCutCoords[4] = { &allBezierCoords[4], &allBezierCoords[5], &allBezierCoords[6], &allBezierCoords[7] };

	cutLine(centerx, y, curveleft, curvey, 2.6, &midpoint);
	bezierCoords[0]->x = curveleft;
	bezierCoords[0]->y = curvey;
	bezierCoords[1]->x = midpoint.x;
	bezierCoords[1]->y = midpoint.y;
	bezierCoords[2]->x = centerx;
	bezierCoords[2]->y = topy;
	bezierCoords[3]->x = centerx;
	bezierCoords[3]->y = cheeky;
	splitBezierCurve(bezierCoords, MIN(percentage, 1), bezierCutCoords);
	cairo_curve_to(cairo, bezierCutCoords[1]->x, bezierCutCoords[1]->y, bezierCutCoords[2]->x, bezierCutCoords[2]->y, bezierCutCoords[3]->x, bezierCutCoords[3]->y);

	percentage -= 1;
	if(percentage <= 0) return;

	cutLine(centerx, y, curveright, curvey, 2.6, &midpoint);
	bezierCoords[0]->x = centerx;
	bezierCoords[0]->y = cheeky;
	bezierCoords[1]->x = centerx;
	bezierCoords[1]->y = topy;
	bezierCoords[2]->x = midpoint.x;
	bezierCoords[2]->y = midpoint.y;
	bezierCoords[3]->x = curveright;
	bezierCoords[3]->y = curvey;
	splitBezierCurve(bezierCoords, MIN(percentage, 1), bezierCutCoords);
	cairo_curve_to(cairo, bezierCutCoords[1]->x, bezierCutCoords[1]->y, bezierCutCoords[2]->x, bezierCutCoords[2]->y, bezierCutCoords[3]->x, bezierCutCoords[3]->y);

	percentage -= 1;
	percentage *= 2;
	if(percentage <= 0) return;

	cutLine(curveright, curvey, centerx, y, percentage, &midpoint);
	cairo_line_to(cairo, midpoint.x, midpoint.y);
}

void fadeOutSelection(cairo_t* cairo, int x, int y, int w, int h) {
	//saveState();
	double fade;

	cairo_t* target = getDirectCairo();
	for(fade = 0; fade <= 1.1; fade += .002) {
		if(fade > 1) target = cairo;

		cairo_new_path(target);
		drawHeartPercentage(target, x, y, w, h, 1);
		cairo_close_path_inverted(target);
		cairo_set_source_rgba(target, 1, 1, 1, fade);
		cairo_fill(target);

		cairo_set_source_rgb(target, 0.9, 0.5, 0.5);
		cairo_new_path(target);
		cairo_set_line_width(target, 5);
		cairo_set_line_cap(target, CAIRO_LINE_CAP_ROUND);
		drawHeartPercentage(target, x, y, w, h, 1);

		cairo_stroke_preserve(target);
		if(fade > 1) updateScreen();
		usleep(20000);
	}
}

void centerSelection(int x, int y, int w, int h) {

	int leftx = (WIDTH - w)/2;
	int topy = (TEXT_HEIGHT - h)/2;

	int lastx = x, lasty = y;
	double percentage;
	coord midpoint;

	for(percentage = 0; percentage <= 1; percentage += 0.01) {
		cutLine(x, y, leftx, topy, percentage, &midpoint);
		shift(((int) midpoint.x) - lastx, ((int) midpoint.y) - lasty);
		lastx = midpoint.x; lasty = midpoint.y;
		usleep(10000);
	}
}
