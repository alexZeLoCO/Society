#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void printPopulation (int population, int cycle, int cycle_limit, int population_female, int mutated_population, int female_mutated_population, int carrying_capacity) {
	cout << "-----------------------------------------" << endl;
	cout << "Cycle: " << cycle << "/" << cycle_limit << endl;
	cout << "Total population and carrying capacity: " << population + mutated_population << "/" << carrying_capacity << endl;
	cout << "Non-mutated population: " << population << endl;
	cout << "\t Female population: " << population_female << endl;
	cout << "\t Male population: " << population - population_female << endl;
	cout << "Mutated population: " << mutated_population << endl;
	cout << "\t Female mutated population " << female_mutated_population << endl;
	cout << "\t Male mutated population " << mutated_population - female_mutated_population << endl;
}


void printPopulation(int population, int cycle, int population_female, int mutated_population, int female_mutated_population, int carrying_capacity) {
	cout << "-----------------------------------------" << endl;
	cout << "Cycle: " << cycle << endl;
	cout << "Total population and carrying capacity: " << population + mutated_population << "/" << carrying_capacity << endl;
	cout << "Non-mutated population: " << population << endl;
	cout << "\t Female population: " << population_female << endl;
	cout << "\t Male population: " << population - population_female << endl;
	cout << "Mutated population: " << mutated_population << endl;
	cout << "\t Female mutated population " << female_mutated_population << endl;
	cout << "\t Male mutated population " << mutated_population - female_mutated_population << endl;
}

double overload(int carrying_capacity, int population) {
	if (population  > carrying_capacity) {
		return population / (population-carrying_capacity);
	}
	else {
		return 1;
	}
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

	int carrying_capacity;
	cout << "Enter the carrying capacity the society will have (positive integer higher than 0 or 0 for unlimited): " << endl;
	cin >> carrying_capacity;

	int mutation_chance;
	cout << "Enter the initial mutation chance (positive integer between 0 and 100): " << endl;
	cin >> mutation_chance;
	cout << "Finally, enter the cycles this society will run for (0 to run forever): ";
	cin >> cycle_limit;

	int mutated_population = 0;
	int female_mutated_population = 0;

	printPopulation(population, 0, cycle_limit, population_female,mutated_population,female_mutated_population,carrying_capacity);

	srand(time(NULL));
	if (cycle_limit > 0) {
		for (int cycle = 1; cycle <= cycle_limit; cycle++) {
		
			for (int i = 0; i < population + mutated_population;i++) {			//DEATH
				if (rand() % 100 + 1 < mutated_population / (population + mutated_population) or population <=0) {
					if (rand() % 100 + 1 < death_chance * 0.80 * overload(carrying_capacity, population + mutated_population)) {

						if (rand() % 100 + 1 < female_mutated_population / mutated_population or mutated_population-female_mutated_population<=0) {
							female_mutated_population--;
						}
						mutated_population--;
					}
				}
				else {
					if (rand() % 100 + 1 < death_chance * overload(carrying_capacity, population + mutated_population)) {
						if (population - population_female < 0 or rand() % 100 + 1 < population_female / population) {
							population_female--;
						}
						population--;
					}
					
				}
			}
				
			for (int i = 0; i < population_female+female_mutated_population; i++) {			//BIRTH
				if (rand() % 100 + 1 < birth_chance) {
					if (rand() % 100 + 1 < mutation_chance) {
						if (rand() % 100 + 1 < 50) {
							female_mutated_population++;
						}
						mutated_population++;
					}
					else {
						if (rand() % 100 + 1 < 50) {
							population_female++;
						}
						population++;
					}
				}
			}

			printPopulation(population, cycle, cycle_limit, population_female,mutated_population,female_mutated_population,carrying_capacity);
		}
	}

	else {
		int cycle = 0;
		while ((population_female>0 or female_mutated_population>0) and (mutated_population-female_mutated_population>0 or population-population_female>0)) {
			cycle++;
		
			for (int i = 0; i < population+mutated_population; i++) {				//DEATH
					if (rand() % 100 + 1 < mutated_population / (population + mutated_population) or population <= 0) {
						if (rand() % 100 + 1 < death_chance * 0.80 * overload(carrying_capacity, population + mutated_population)) {

							if (rand() % 100 + 1 < female_mutated_population / mutated_population or mutated_population-female_mutated_population<=0) {
								female_mutated_population--;
							}
							mutated_population--;
						}
					}
					else {
						if (rand() % 100 + 1 < death_chance * overload(carrying_capacity, population + mutated_population)) {
							if (population-population_female<0 or rand() % 100 + 1 < population_female / population) {
								population_female--;
							}
							population--;
						}

					}
				
			}

			for (int i = 0; i < population_female+female_mutated_population; i++) {				//BIRTH
				if (rand() % 100 + 1 < birth_chance) {
					if (rand() % 100 + 1 < mutation_chance) {
						if (rand() % 100 + 1 < 50) {
							female_mutated_population++;
						}
						mutated_population++;
					}
					else {
						if (rand() % 100 + 1 < 50) {
							population_female++;
						}
						population++;
					}
				}
			}

			printPopulation(population, cycle, population_female,mutated_population,female_mutated_population,carrying_capacity);
		}
	}
	return 0;
}