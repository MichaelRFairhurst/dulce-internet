#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "text.h"
#include "window.h"
#include "constants.h"

letter_move* makeMove(char startletter, char endletter, int startx, int endx) {
	letter_move* currentmove = malloc(sizeof(letter_move));
	currentmove->start_letter = startletter;
	currentmove->end_letter = endletter;
	currentmove->start_x = startx;
	currentmove->start_y = TEXT_HEIGHT;
	currentmove->end_x = endx;
	currentmove->end_y = TEXT_HEIGHT;
	currentmove->mid_x = (startx + endx) / 2 + (rand() % (TEXT_DIST*2)) - TEXT_DIST;
	currentmove->mid_y = TEXT_HEIGHT + (rand() % (TEXT_DIST*2)) - TEXT_DIST;
	return currentmove;
}

letter_move** rearrangeLetters(char* text1, char* text2) {
	int i, c;
	letter_move** movements = malloc(sizeof(letter_move*));
	movements[0] = NULL;
	int movements_count = 0;
	int* text1_found = malloc(strlen(text1) * sizeof(int));
	int* text2_found = malloc(strlen(text2) * sizeof(int));
	int* text1_offsets = malloc(strlen(text1) * sizeof(int));
	int* text2_offsets = malloc(strlen(text2) * sizeof(int));
	int text1_leftoffset = 0;
	int text2_leftoffset = 0;
	memset(text1_found, 0, strlen(text1) * sizeof(int));
	memset(text2_found, 0, strlen(text2) * sizeof(int));

	cairo_text_extents_t textextents;
	textextents.x_bearing = 0;
    textextents.y_bearing = 0;
    textextents.width = 0;
    textextents.height = 0;
    textextents.x_advance = 0;
    textextents.y_advance = 0;
	for(i = strlen(text1) - 1; i >= 0; i--) {
		char* copy = strdup(text1);
		copy[i] = 0; // shorten string

		cairo_text_extents(getCairo(), copy, &textextents);

		text1_offsets[i] = textextents.x_advance + i * 1;

		if(i == strlen(text1) - 1) {
			text1_leftoffset = (WIDTH - text1_offsets[i]) / 2;
		}

		text1_offsets[i] += text1_leftoffset;

		free(copy);
	}
	for(i = strlen(text2) - 1; i >= 0; i--) {
		char* copy = strdup(text2);
		copy[i] = 0; // shorten string

		cairo_text_extents(getCairo(), copy, &textextents);

		text2_offsets[i] = textextents.x_advance + i * 1;

		if(i == strlen(text2) - 1) {
			text2_leftoffset = (WIDTH - text2_offsets[i]) / 2;
		}
		text2_offsets[i] += text2_leftoffset;
		free(copy);
	}

	for(i = 0; i < strlen(text1); i++) {
		for(c = 0; c < strlen(text2); c++) {
			if(text2_found[c]) continue;
			if(text1[i] == text2[c]) {
				text1_found[i] = 1;
				text2_found[c] = 1;
				letter_move* currentmove = makeMove(text1[i], text2[c], text1_offsets[i], text2_offsets[c]);
				movements = realloc(movements, sizeof(letter_move*) * (movements_count + 2));
				movements[movements_count] = currentmove;
				movements[++movements_count] = NULL;
				break;
			}
		}
	}

	for(i = 0; i < strlen(text1); i++) {
		if(text1_found[i]) continue;
		for(c = 0; c < strlen(text2); c++) {
			if(text2_found[c]) continue;
			text1_found[i] = 1;
			text2_found[c] = 1;
			letter_move* currentmove = makeMove(text1[i], text2[c], text1_offsets[i], text2_offsets[c]);
			movements = realloc(movements, sizeof(letter_move*) * (movements_count + 2));
			movements[movements_count] = currentmove;
			movements[++movements_count] = NULL;
			break;
		}
	}

	for(i = 0; i < strlen(text1); i++) {
		if(text1_found[i]) continue;
		letter_move* currentmove = makeMove(text1[i], 0, text1_offsets[i], text1_offsets[i]);
		movements = realloc(movements, sizeof(letter_move*) * (movements_count + 2));
		movements[movements_count] = currentmove;
		movements[++movements_count] = NULL;
	}

	for(i = 0; i < strlen(text2); i++) {
		if(text2_found[i]) continue;
		letter_move* currentmove = makeMove(0, text2[i], text2_offsets[i], text2_offsets[i]);
		movements = realloc(movements, sizeof(letter_move*) * (movements_count + 2));
		movements[movements_count] = currentmove;
		movements[++movements_count] = NULL;
	}

	free(text1_found); free(text2_found); free(text1_offsets); free(text2_offsets);
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
	cairo_set_source_rgba(cairo, 0, 0, 0, alpha);
	cairo_show_text(cairo, buf);
	free(buf);
}

void animateTexts(cairo_t* cairo, char* text1, char* text2) {
	int percentage;
	letter_move** movements = rearrangeLetters(text1, text2);
	//cairo_rectangle(cairo, 0, 0, WIDTH, HEIGHT);
	saveState();
	for(percentage = 0; percentage <= 100; percentage++) {
		int i = 0;
		restoreState();
		while(movements[i]) {
			printLetterMovePercentage(cairo, movements[i], percentage);
			i++;
		}
		updateScreen();
		usleep(percentage == 0 ? 1000000 : 20000);
	}

	int i = 0;
	while(movements[i]) {
		free(movements[i]);
		i++;
	}
	free(movements);
}
