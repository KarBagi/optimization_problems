#include "pch.h"
#include "SimulatedAnnealing.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <ctime>

void SimualtedAnnealing::apply()
{
	vector<int> best;
	vector<int> permutation = random_permutation(size);
	vector<int> next(permutation);
	clock_t start;
	int firstToSwap;
	int secondToSwap;
	double temperature = temperatureBuffer;
	int result = 1 << 30;
	double time = 0;
	double foundTime = 0;
    int T = 0;
    int steps =  3*size;

	start = clock();

    while(true)
	{
		//while (temperature >= 0.1)
		//{


			next = permutation;
	
			int nextCost = calculatePath(next);


			for (int i = steps; i > 0; i--)
			{				
				do
				{
					firstToSwap = rand() % size;
					secondToSwap = rand() % size;
				} while (firstToSwap == secondToSwap);

				swap(next[firstToSwap],next[secondToSwap]);
				
				nextCost = calculatePath(next);

				int difference = result - nextCost;

				if (difference > 0)
				{
					result = nextCost;
					best = next;
					foundTime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
				}

				if (difference > 0 || (difference < 0 && getProbability(difference,temperature) > ((double)rand() / RAND_MAX) + 1))
				{
					permutation = next;
					break;
				}
				else
				{
					swap(next[firstToSwap], next[secondToSwap]);
				}

				time = (std::clock() - start) / (double)CLOCKS_PER_SEC;

				if (time >= timeBound || temperature < 0.1)
				{
					cout << "Droga: ";
					for (int d = 0; d < size; d++)
					{
						cout << best[d] << " ";
					}

                    cout << best[0];

					cout << "\nKoszt: " << result << endl;
					cout << "Znaleziono po: " << foundTime << " s " << endl;
					cout << "Temperatura koncowa: "<< temperature << endl;
                    cout << "exp: " << exp(-1 / temperature);
					cout << endl;
					return;
				}
			}

            switch (tempe)
            {
                case 1:
                    temperature *= coolingRate;
                    break;
                case 2:
                    temperature -= coolingRate;
                    break;
                case 3:
                    T++;
                    temperature *= pow(coolingRate, T);
                    break;
            }
		//}

		//temperature = temperatureBuffer;
		//permutation = random_permutation(size);

	}

}


vector<int> SimualtedAnnealing::random_permutation(int _size)
{
	vector<int> temp;
	temp.reserve(_size);

	for (int i = 0; i < _size; i++)
	{
		temp.push_back(i);
	}
	
	random_shuffle(temp.begin(), temp.end());
	
	return temp;
}

double SimualtedAnnealing::calculateTemperature()
{
	vector<int> origin; 

	int firstToSwap;
	int secondToSwap;
	int originCost = 0;
	int neighbourCost = 0;
	int delta = 0;
	int buffer = 0;

	for (int i = 0; i < 10000; i++)
	{
		do
		{
			firstToSwap = rand() % size;
			secondToSwap = rand() % size;
		} while (firstToSwap == secondToSwap);

		origin = random_permutation(size);
		vector<int> neighbour(origin);

		swap(neighbour[firstToSwap], neighbour[secondToSwap]);

		delta = fabs(calculatePath(origin) - calculatePath(neighbour));
		buffer += delta;
		
	}
	
	buffer /= 10000;

	return (-1*buffer)/log(0.99);
}

int SimualtedAnnealing::calculatePath(vector<int> path)
{
	int cost = 0;

	for (int i = 0; i < path.size() - 1; ++i)
	{
		cost += matrix[path[i]][path[i + 1]];
	}
	cost += matrix[path[size - 1]][path[0]];

	return cost;
}

double SimualtedAnnealing::getProbability(int diff, double temperature)
{
	
	return exp(diff / temperature);
}

SimualtedAnnealing::SimualtedAnnealing(Graph graph, int time, double rate, int te)
{
	matrix = graph.getMatrix();
	size = graph.getCount();
	timeBound = time;
	coolingRate = rate;
	temperatureBuffer = calculateTemperature();
    tempe = te;
}


SimualtedAnnealing::~SimualtedAnnealing()
{
}
