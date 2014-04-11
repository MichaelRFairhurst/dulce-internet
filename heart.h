#ifndef HEADER_HEART
#define HEADER_HEART

void cairo_close_path_inverted(cairo_t*);
void drawHeart(cairo_t*, int, int, int, int, int);
void fadeOutSelection(cairo_t* cairo, int x, int y, int w, int h);
void centerSelection(int x, int y, int w, int h);
void drawHeartPercentage(cairo_t* cairo, int x, int y, int w, int h, double percentage);

#endif
