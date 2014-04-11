typedef struct {
	int x;
	int y;
} coord;

void cutLine(int startx, int starty, int endx, int endy, double ratio, coord* output);
void cutLineCoords(coord* start, coord* end, double ratio, coord* output);
void splitBezierCurve(coord** points, double ratio, coord** lastpoints);
void getFirstLineSplits(coord ** points, int pointslen, double ratio, coord** lastpoints);
