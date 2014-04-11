#ifndef HEADER_WINDOW

void saveState();
void restoreState();
void updateScreen();
int openWindow();
cairo_t* getCairo();
void shift(int x, int y);

#endif
