/* compile with:
 *  * gcc $(pkg-config xext x11 cairo-xlib-xrender --cflags --libs) cairo-xshape-example.c
 *   */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "constants.h"
#include <cairo/cairo-xlib.h>
#include "window.h"
#include "line.h"
#include "fade.h"
#include "heart.h"
#include "text.h"

void updateScreen();

cairo_surface_t* backgroundA;
cairo_surface_t* backgroundB;

int main(int argc, char** argv) {
	if(!openWindow()) return 1;

	srand(time(NULL));
	backgroundA = cairo_image_surface_create_from_png("pic2.png");
	backgroundB = cairo_image_surface_create_from_png("pic.png");

	updateScreen();
	fadeBetween(getCairo(), backgroundA, backgroundB, 10000);
	drawHeart(getCairo(), 20, 20, 250, 250, 10000);
	drawHeart(getCairo(), 300, 300, 450, 250, 10000);
	//fadeOutSelection(getCairo());
	sleep(2);
	animateTexts(getCairo(), "fat rumple cat", "rumple cat fat");
	restoreState();
	animateTexts(getCairo(), "rumple cat fat", "hello my love, Dulce!");
	restoreState();
	animateTexts(getCairo(), "hello my love, Dulce!", "Its your love, mike!");
	restoreState();
	animateTexts(getCairo(), "Its your love, mike!", "How many people does it take to monitor a cat?");
	restoreState();
	animateTexts(getCairo(), "How many people does it take to monitor a cat?", "It depends on whether or not you consider the cat to be a person monitoring itself!");
	sleep(2);
	return 0;
}

