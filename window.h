#ifndef HEADER_WINDOW

void saveState();
void restoreState();
void restoreStatePartial(int x, int y, int w, int h);
void updateScreen();
void consumeEvents();
cairo_surface_t* getSavedSurface();
int openWindow();
cairo_t* getCairo();
cairo_t* getDirectCairo();
void shift(int x, int y);

#endif
