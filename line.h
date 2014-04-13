typedef struct {
	double x;
	double y;
} coord;

void cutLine(double startx, double starty, double endx, double endy, double ratio, coord* output);
void cutLineCoords(coord* start, coord* end, double ratio, coord* output);
void splitBezierCurve(coord** points, double ratio, coord** lastpoints);
void getFirstLineSplits(coord ** points, int pointslen, double ratio, coord** lastpoints);
