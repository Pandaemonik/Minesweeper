#pragma once
#include "resource.h"
#define DEFAULT_X 10
#define DEFAULT_Y 10
#define SQURE_SIZE 20
//Arrays
int bombs[DEFAULT_Y][DEFAULT_X]={ 
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,0,0,
	0,1,0,0,0,0,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
};//Containes the bomb locations
int numbers[DEFAULT_Y][DEFAULT_X];//containes the numbers to be displayed on click
bool safe[DEFAULT_Y][DEFAULT_X]={false};//Containes the selection of which squres are labled as safe
bool been_here[DEFAULT_Y][DEFAULT_X]={false};//Helper array for the recursion

int x,y,Number_of_mines(0);//Helper variables for input/location of cursor
bool Game_over(false);//Keeps information ifthe game is over or not