#include "stdio.h"
#include "line.h"
#include "constants.h"

void cutLine(double startx, double starty, double endx, double endy, double ratio, coord* output) {
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

void splitBezierCurve(coord** points, double ratio, coord** lastpoints) {
	getFirstLineSplits(points, 4, ratio, lastpoints);
}

void getFirstLineSplits(coord ** points, int pointslen, double ratio, coord** lastpoints) {
	int i;
	lastpoints[0]->x = points[0]->x;
	lastpoints[0]->y = points[0]->y;

	if(pointslen == 1) return;

	for(i = 0; i < pointslen - 1; i++) {
		// rewrite points[i] to the cut between [i] and [i+1]
		cutLineCoords(points[i], points[i+1], ratio, points[i]);
	}

	getFirstLineSplits(points, pointslen - 1, ratio, lastpoints + 1);
}
