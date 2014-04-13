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

int main(int argc, char** argv) {
	if(!openWindow()) return 1;

	srand(time(NULL));
	cairo_surface_t* forest = cairo_image_surface_create_from_png("forest.png");
	cairo_surface_t* oneyr = cairo_image_surface_create_from_png("1yr.png");
	cairo_surface_t* twentyfirst = cairo_image_surface_create_from_png("21st.png");
	cairo_surface_t* beach = cairo_image_surface_create_from_png("beach.png");
	cairo_surface_t* kiss = cairo_image_surface_create_from_png("kiss.png");
	cairo_surface_t* multnoma = cairo_image_surface_create_from_png("multnoma.png");
	cairo_surface_t* oakspark = cairo_image_surface_create_from_png("oakspark.png");
	cairo_surface_t* saturdaymarket = cairo_image_surface_create_from_png("saturdaymarket.png");
	cairo_surface_t* submarine = cairo_image_surface_create_from_png("submarine.png");

	updateScreen();

	while(1) {
		fadeBetween(getCairo(), twentyfirst, forest, 10000);
		drawHeart(getCairo(), 60, 20, 190, 128, 10000);
		fadeOutSelection(getCairo(), 60, 20, 190, 128);
		centerSelection(60, 20, 190, 128);
		sleep(5);
		saveState();
		animateTexts(getCairo(), "Hello my love, Dulce!", "Its your love, mike!");
		restoreState();
		animateTexts(getCairo(), "Its your love, mike!", "My love for you is vaster than forests");
		restoreState();
		animateTexts(getCairo(), "My love for you is vaster than forests", "and so much greater than friendship");
		sleep(5);
		fadeBetween(getCairo(), kiss, getSavedSurface(), 10000);
		sleep(10);
		fadeBetween(getCairo(), beach, kiss, 10000);
		sleep(10);
		fadeBetween(getCairo(), multnoma, beach, 10000);
		sleep(10);
		fadeBetween(getCairo(), oakspark, multnoma, 10000);
		sleep(10);
		fadeBetween(getCairo(), saturdaymarket, oakspark, 10000);
		sleep(10);
		fadeBetween(getCairo(), submarine, saturdaymarket, 10000);
		sleep(10);
		fadeBetween(getCairo(), oneyr, submarine, 10000);
		sleep(10);
		fadeBetween(getCairo(), forest, oneyr, 10000);
		sleep(10);
	}
	return 0;
}

