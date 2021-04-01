#include<stdio.h>
#include<cs50.h>


int calculate(int startPop, int endPop);

int main(void)
{
	int startPop = 0;
	int endPop = 0;
	int years;

	// promt user for start population size
	do
	{
		startPop = get_int("Start size: ");
	}
	while(startPop < 9);

	// prompt end population size
	do
	{
		endPop = get_int("End size: ");
	}
	while(endPop < startPop);

	// Calculate int nr years required for pop to reach at least end size
	years = calculate(startPop, endPop);
	// print nr years required 
	printf("Years: %i\n", years);
}

int calculate(int startPop, int endPop) 
{
	int newPop = startPop;
	int deaths = 0;
	int births = 0;
	int years = 0;

	do 
	{
		deaths = newPop / 4;
		births = newPop / 3;
		newPop = newPop + births - deaths;
		years++;
	}	
	while(newPop < endPop);
	return years;
}
