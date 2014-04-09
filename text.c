#include "text.h"
#include "constants.h"

letter_move* makeMove(char startletter, char endletter, int startx, int starty, int endx, int endy) {
	startx += 100; endx += 100;
	letter_move* currentmove = malloc(sizeof(letter_move));
	currentmove->start_letter = startletter;
	currentmove->end_letter = endletter;
	currentmove->start_x = startx;
	currentmove->start_y = starty;
	currentmove->end_x = endx;
	currentmove->end_y = endy;
	currentmove->mid_x = (startx + endx) / 2 + (rand() % 120) - 60;
	currentmove->mid_y = (starty + endy) / 2 + (rand() % 120) - 60;
	return currentmove;
}

letter_move** rearrangeLetters(char* text1, char* text2) {
	int i, c;
	letter_move** movements = malloc(sizeof(letter_move*));
	movements[0] = NULL;
	int movements_count = 0;
	int* text1_found = malloc(strlen(text1) * sizeof(int));
	int* text2_found = malloc(strlen(text2) * sizeof(int));
	memset(text1_found, 0, strlen(text1) * sizeof(int));
	memset(text2_found, 0, strlen(text2) * sizeof(int));

	for(i = 0; i < strlen(text1); i++) {
		for(c = 0; c < strlen(text1); c++) {
			if(text2_found[c]) continue;
			if(text1[i] == text2[c]) {
				text1_found[i] = 1;
				text2_found[c] = 1;
				letter_move* currentmove = makeMove(text1[i], text2[c], i * 15, 50, c * 15, 50);
				movements = realloc(movements, sizeof(letter_move*) * (movements_count + 2));
				movements[movements_count] = currentmove;
				movements[++movements_count] = NULL;
				break;
			}
		}
	}

	for(i = 0; i < strlen(text1); i++) {
		if(text1_found[i]) continue;
		for(c = 0; c < strlen(text1); c++) {
			if(text2_found[c]) continue;
			text1_found[i] = 1;
			text2_found[c] = 1;
			letter_move* currentmove = makeMove(text1[i], text2[c], i * 15, 50, c * 15, 50);
			movements = realloc(movements, sizeof(letter_move*) * (movements_count + 2));
			movements[movements_count] = currentmove;
			movements[++movements_count] = NULL;
			break;
		}
	}

	for(i = 0; i < strlen(text1); i++) {
		if(text1_found[i]) continue;
		letter_move* currentmove = makeMove(text1[i], 0, i * 15, 50, i * 15, 50);
		movements = realloc(movements, sizeof(letter_move*) * (movements_count + 2));
		movements[movements_count] = currentmove;
		movements[++movements_count] = NULL;
	}

	for(i = 0; i < strlen(text2); i++) {
		if(text2_found[i]) continue;
		letter_move* currentmove = makeMove(0, text2[i], i * 15, 50, i * 15, 50);
		movements = realloc(movements, sizeof(letter_move*) * (movements_count + 2));
		movements[movements_count] = currentmove;
		movements[++movements_count] = NULL;
	}

	return movements;
}

void printLetterMovePercentage(cairo_t* cairo, letter_move* which, int percentage) {
	int delta_x;
	int delta_y;
	int start_x;
	int start_y;
	double alpha = 1;
	char current_letter;
	if(percentage < 50) {
		if(!which->end_letter) alpha = 1 - percentage / 50.0;
		percentage *= 2;
		start_x = which->start_x;
		start_y = which->start_y;
		delta_x = which->mid_x - start_x;
		delta_y = which->mid_y - start_y;
		current_letter = which->start_letter;
	} else {
		percentage -= 50;
		if(!which->start_letter) alpha = percentage / 50.0;
		percentage *= 2;
		start_x = which->mid_x;
		start_y = which->mid_y;
		delta_x = which->end_x - start_x;
		delta_y = which->end_y - start_y;
		current_letter = which->end_letter;
	}

	alpha *= 0.4;

	cairo_move_to(cairo, start_x + delta_x / 100.0 * percentage, start_y + delta_y / 100.0 * percentage);
	char* buf = malloc(2); buf[0] = current_letter; buf[1] = 0;
	cairo_set_source_rgba(cairo, 1, 1, 1, alpha);
	cairo_show_text(cairo, buf);
	free(buf);
}

void animateTexts(cairo_t* cairo, char* text1, char* text2) {
	int i = 0, percentage;
	letter_move** movements = rearrangeLetters(text1, text2);
	//cairo_rectangle(cairo, 0, 0, WIDTH, HEIGHT);
	saveState();
	for(percentage = 0; percentage <= 100; percentage++) {
		int i = 0;
		restoreState();
		while(movements[i]) {
			printLetterMovePercentage(cairo, movements[i], percentage);
			updateScreen();
			i++;
		}
		usleep(percentage == 0 ? 1000000 : 20000);
	}
}
