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
		fadeBetween(getCairo(), twentyfirst, getSavedSurface(), 10000);
		drawHeart(getCairo(), 60, 2, 190, 150, 10000);
		fadeOutSelection(getCairo(), 60, 2, 190, 150);
		centerSelection(60, 2, 190, 150);
		sleep(5);
		saveState();
		animateTexts(getCairo(), "Hello my love, Dulce!", "Its your love, Mike!");
		restoreState();
		animateTexts(getCairo(), "Its your love, Mike!", "Alone or with friends, I always need you by my side");
		restoreState();
		animateTexts(getCairo(), "Alone or with friends, I always need you by my side", "You're my everything and I love you so much <3");
		sleep(5);
		//fadeBetween(getCairo(), kiss, getSavedSurface(), 10000);
		//drawHeart(getCairo(), 145, 120, 60, 50, 10000);
		//saveState();
		//sleep(10);
		fadeBetween(getCairo(), beach, getSavedSurface(), 10000);
		drawHeart(getCairo(), 20, 4, 130, 128, 10000);
		fadeOutSelection(getCairo(), 20, 4, 130, 128);
		centerSelection(20, 4, 130, 128);
		sleep(5);
		saveState();
		animateTexts(getCairo(), "The realization on my face here is so priceless :)", "You are so funny and make me so so happy");
		restoreState();
		animateTexts(getCairo(), "You are so funny and make me so so happy", "You teach me so much, about myself, you, life...");
		restoreState();
		animateTexts(getCairo(), "You teach me so much, about myself, you, life...", "From sea anemones to surprising photo stories :)");
		sleep(5);
		fadeBetween(getCairo(), beach, getSavedSurface(), 10000);
		drawHeart(getCairo(), 150, 40, 175, 198, 10000);
		fadeOutSelection(getCairo(), 150, 40, 175, 198);
		centerSelection(150, 40, 175, 198);
		sleep(5);
		saveState();
		animateTexts(getCairo(), "You make all the best moments in my life better", "I only hope that I can do the same back for you");
		restoreState();
		animateTexts(getCairo(), "I only hope that I can do the same back for you", "You are the brightest part of my brightest stories");
		restoreState();
		animateTexts(getCairo(), "You are the brightest part of my brightest stories", "And I love you from highest to lowest days <3");
		sleep(5);
		fadeBetween(getCairo(), multnoma, getSavedSurface(), 10000);
		drawHeart(getCairo(), 56, 70, 250, 165, 10000);
		fadeOutSelection(getCairo(), 56, 70, 250, 165);
		centerSelection(56, 70, 250, 165);
		sleep(5);
		saveState();
		animateTexts(getCairo(), "When I'm with you I feel on top of the world", "When I'm with you I can do anything");
		restoreState();
		animateTexts(getCairo(), "When I'm with you I can do anything", "I dunno, say, climb multnoma falls :)");
		restoreState();
		animateTexts(getCairo(), "I dunno, say, climb multnoma falls :)", "Which was a piece of cake; you were by my side");
		restoreState();
		animateTexts(getCairo(), "Which was a piece of cake; you were by my side", "And all the tiny cars watched us kiss at the top :)");
		sleep(10);
		fadeBetween(getCairo(), oakspark, getSavedSurface(), 10000);
		drawHeart(getCairo(), 156, 60, 205, 225, 10000);
		fadeOutSelection(getCairo(), 156, 60, 205, 225);
		sleep(5);
		saveState();
		fadeBetween(getCairo(), oakspark, getSavedSurface(), 10000);
		drawHeart(getCairo(), 50, -24, 210, 175, 10000);
		fadeOutSelection(getCairo(), 50, -24, 210, 175);
		sleep(5);
		animateTexts(getCairo(), "With each kiss I love you more and more", "And I'm alllll about kissing your hair :)");
		restoreState();
		animateTexts(getCairo(), "And I'm alllll about kissing your hair :)", "And kissing your cheeks and nose too...");
		sleep(5);
		restoreState();
		fadeBetween(getCairo(), saturdaymarket, getSavedSurface(), 10000);
		drawHeart(getCairo(), 116, 40, 250, 205, 10000);
		fadeOutSelection(getCairo(), 116, 40, 250, 205);
		sleep(5);
		saveState();
		fadeBetween(getCairo(), saturdaymarket, getSavedSurface(), 10000);
		drawHeart(getCairo(), -25, 4, 210, 175, 10000);
		fadeOutSelection(getCairo(), -25, 4, 210, 175);
		sleep(5);
		animateTexts(getCairo(), "I love it when we act immature together", "Especially to mess with friends or strangers");
		restoreState();
		animateTexts(getCairo(), "Especially to mess with friends or strangers", "Who should we prank next?");
		sleep(5);
		fadeBetween(getCairo(), submarine, getSavedSurface(), 10000);
		drawHeart(getCairo(), 6, 35, 280, 180, 10000);
		fadeOutSelection(getCairo(), 6, 35, 280, 180);
		centerSelection(6, 35, 280, 180);
		sleep(5);
		saveState();
		animateTexts(getCairo(), "One day we can buy and live in a submarine", "If that's what you want we'll do it");
		restoreState();
		animateTexts(getCairo(), "If that's what you want we'll do it", "With 10 kittens and constant playtime");
		restoreState();
		animateTexts(getCairo(), "With 10 kittens and constant playtime", "Moored in portland for the beer :)");
		sleep(5);
		fadeBetween(getCairo(), oneyr, getSavedSurface(), 10000);
		drawHeart(getCairo(), 150, 35, 120, 140, 10000);
		fadeOutSelection(getCairo(), 150, 35, 120, 140);
		centerSelection(150, 35, 120, 140);
		sleep(5);
		saveState();
		animateTexts(getCairo(), "We're past a perfect year together", "And on to a perfect new one");
		restoreState();
		animateTexts(getCairo(), "And on to a perfect new one", "I'd say I plan to make the most of it");
		restoreState();
		animateTexts(getCairo(), "I'd say I plan to make the most of it", "But with us together, its not just a plan");
		restoreState();
		animateTexts(getCairo(), "But with us together, its not just a plan", "Its just the most natural course of events");
		restoreState();
		animateTexts(getCairo(), "Its just the most natural course of events", "Because of how much I love you <3");
		sleep(5);
		fadeBetween(getCairo(), forest, getSavedSurface(), 10000);
		drawHeart(getCairo(), -20, 24, 210, 235, 10000);
		fadeOutSelection(getCairo(), -20, 24, 210, 235);
		sleep(5);
		saveState();
		fadeBetween(getCairo(), forest, getSavedSurface(), 10000);
		drawHeart(getCairo(), 90, -40, 270, 245, 10000);
		fadeOutSelection(getCairo(), 90, -40, 270, 245);
		sleep(5);
		saveState();
	}
	return 0;
}

