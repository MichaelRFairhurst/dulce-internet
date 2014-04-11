#ifndef HEADER_WINDOW

void saveState();
void restoreState();
void updateScreen();
cairo_surface_t* getSavedSurface();
int openWindow();
cairo_t* getCairo();
void shift(int x, int y);

#endif
