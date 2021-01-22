#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void printPopulation (int population, int cycle, int cycle_limit, int population_female) {
	cout << "-----------------------------------------" << endl;
	cout << "Cycle: " << cycle << "/" << cycle_limit << endl;
	cout << "Total population: " << population << endl;
	cout << "\t female population: " << population_female << endl;
	cout << "\t male population: " << population - population_female << endl;
}


void printPopulation(int population, int cycle, int population_female) {
	cout << "-----------------------------------------" << endl;
	cout << "Cycle: " << cycle << endl;
	cout << "Total population: " << population << endl;
	cout << "\t female population: " << population_female << endl;
	cout << "\t male population: " << population - population_female << endl;
}

int main () {

	cout << "This program will run a society simulation." << endl;
	cout << "People may live, people may be born, and people may die." << endl;
	cout << endl;
	cout << "First we will define parameters for the population: " << endl;

	int death_chance;
	int birth_chance;
	cout << "Enter death chance (positive integer between 0 and 100): " << endl;
	cin >> death_chance;
	cout << "Enter birth chance (positive integer between 0 and 100): " << endl;
	cin >> birth_chance;

	int population;
	int cycle_limit;
	cout << "At first, half of the population will be male, the other half female." << endl;
	cout << "Enter the starting population size: ";
	cin >> population;
	int population_female = population / 2;
	cout << "Enter the cycles this society will run for (0 to run forever): ";
	cin >> cycle_limit;

	printPopulation(population, 0, cycle_limit, population_female);

	srand(time(NULL));
	if (cycle_limit > 0) {
		for (int cycle = 1; cycle <= cycle_limit; cycle++) {
		
			for (int i = 0; i < population; i++) {			//DEATH
				if (rand() % 100 + 1 < death_chance) {
					if (rand() % 100 + 1 < 50) {
						population_female--;
					}
					population--;
				}
			}
				
			for (int i = 0; i < population_female; i++) {			//BIRTH
				if (rand() % 100 + 1 < birth_chance) {
					if (rand() % 100 + 1 < 50) {
						population_female++;
					}
					population++;
				}
			}

			printPopulation(population, cycle, cycle_limit, population_female);
		}
	}

	else {
		int cycle = 0;
		while (population_female>0 and population-population_female>0) {
			cycle++;
		
			for (int i = 0; i < population; i++) {				//BIRTH
				if (rand() % 100 + 1 < death_chance) {
					if (rand() % 100 + 1 < 50) {
						population_female--;
					}
					population--;
				}
			}

			for (int i = 0; i < population_female; i++) {				//DEATH
				if (rand() % 100 + 1 < birth_chance) {
					if (rand() % 100 + 1 < 50) {
						population_female++;
					}
					population++;
				}
			}

			printPopulation(population, cycle, population_female);
		}
	}
	return 0;
}