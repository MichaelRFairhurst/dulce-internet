#include "line.h"
#include "constants.h"

void cutLine(int startx, int starty, int endx, int endy, double ratio, coord* output) {
	coord start;
	coord end;

	start.x = startx;
	start.y = starty;
	end.x = endx;
	end.y = endy;

	cutLineCoords(&start, &end, ratio, output);
}

void cutLineCoords(coord* start, coord* end, double ratio, coord* output) {
	output->x = start->x + (end->x - start->x) * ratio;
	output->y = start->y + (end->y - start->y) * ratio;
}

