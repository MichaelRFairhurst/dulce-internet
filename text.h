#ifndef HEADER_TEXT
#define HEADER_TEXT
#include <cairo/cairo-xlib.h>

typedef struct {
	char start_letter;
	char end_letter;
	int start_x;
	int start_y;
	int mid_x;
	int mid_y;
	int end_x;
	int end_y;
} letter_move;

letter_move* makeMove(char, char, int, int);
letter_move** rearrangeLetters(char*, char*);
void printLetterMovePercentage(cairo_t*, letter_move*, int);
void animateTexts(cairo_t*, char*, char*);

#endif
