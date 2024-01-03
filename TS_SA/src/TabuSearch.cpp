#include "pch.h"
#include "TabuSearch.h"
#include <iostream>
#include "Graph.h"
#include <algorithm>
#include <ctime>

void TabuSearch::apply()
{
    vector<vector<int>> tabuMatrix;
    vector<int> best;
    vector<int> permutation = randomPermutation(size);
    vector<int> next(permutation);
    int result = 1 << 30;
    int firstToSwap;
    int secondToSwap;
    int nextCost;
    int k = 0;
    int diver;
    clock_t start;
    double time;
    double foundTime;

    tabuMatrix.resize(size);

    for (int j = 0; j < size; ++j)
    {
        tabuMatrix[j].resize(size, 0);
    }

    start = clock();

    while (true)
    {
        for (int step = 0; step < 15 * size; ++step)
        {

            if (diver == result)
            {
                if(k == 5)
                {
                    break;
                }
                else k++;
            }
            else k = 0;

            firstToSwap = 0;
            secondToSwap = 0;
            nextCost = 1 << 30;

            for (int first = 0; first < size; ++first)
            {
                for (int second = first + 1; second < size; ++second)
                {
                    swap(permutation[first], permutation[second]);
                    int currentCost = calculatePath(permutation);

                    if (currentCost < result && tabuMatrix[first][second] == 0)
                    {
                        result = currentCost;
                        best = permutation;
                        foundTime = (clock() - start) / (double)CLOCKS_PER_SEC;
                        firstToSwap = second;
                        secondToSwap = first;
                    }

                    swap(permutation[first], permutation[second]);

                    time = (clock() - start) / (double)CLOCKS_PER_SEC;

                    if (time >= searchTime)
                    {
                        cout << "Droga: ";
                        for (int d = 0; d < size; d++)
                        {
                            cout << best[d] << " ";
                        }

                        cout << best[0] << endl;

                        cout << "\nKoszt: " << result << endl;
                        cout << "Znaleziono po: " << foundTime << " s " << endl;
                        return;
                    }
                }
            }

            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    if(tabuMatrix[i][j] != 0)
                    {
                        tabuMatrix[i][j] -= 1;
                    }
                }
            }

            diver = result;
            permutation = next;
            tabuMatrix[firstToSwap][secondToSwap] += size;
        }

        permutation.clear();

        permutation = randomPermutation(size);

        for (vector<vector<int>>::iterator it = tabuMatrix.begin(); it != tabuMatrix.end(); ++it)
        {
            it->clear();
        }
        tabuMatrix.clear();

        tabuMatrix.resize(size);

        for (vector<vector<int>>::iterator it = tabuMatrix.begin(); it != tabuMatrix.end(); ++it)
        {
            it->resize(size, 0);
        }
    }
}

vector<int> TabuSearch::randomPermutation(int _size)
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

int TabuSearch::calculatePath(vector<int> path)
{
    int cost = 0;

    for (int i = 0; i < path.size() - 1; ++i)
    {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path[size - 1]][path[0]];

    return cost;
}

TabuSearch::TabuSearch(Graph graph, int time)
{
    matrix = graph.getMatrix();
    size = graph.getCount();
    searchTime = time;
}

TabuSearch::~TabuSearch()
{
}





/*
#include "pch.h"
#include "TabuSearch.h"
#include <iostream>
#include "Graph.h"
#include <algorithm>
#include <ctime>

void TabuSearch::apply()
{
	vector<vector<int>> tabuMatrix;
	vector<int>best;
	vector<int>permutation = randomPermutation(size);
	vector<int>next(permutation);
	int result = 1 << 30;
	int firstToSwap;
	int secondToSwap;
	int nextCost;
	std::clock_t start;
	double time;
	double foundTime;

	tabuMatrix.resize(size);

	for (int j = 0; j < size; ++j)
	{
		tabuMatrix[j].resize(size,0);
	}

	start = std::clock();

	while(true)
	{
		for (int step = 0; step <  15*size; ++step)
		{
			firstToSwap = 0;
			secondToSwap = 0;
			nextCost = 1 << 30;

			for (int first = 0; first < size; ++first)
			{
				for (int second = first + 1; second < size; ++second)
				{
					std::swap(permutation[first], permutation[second]);
					int currentCost = calculatePath(permutation);

					if (currentCost < result)
					{
						result = currentCost;
						best = permutation;
						foundTime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
					}

					if (currentCost < nextCost)
					{
						if (tabuMatrix[second][first]<step)
						{
							nextCost = currentCost;
							next = permutation;

							firstToSwap = second;
							secondToSwap = first;
						}
					}

					std::swap(permutation[first], permutation[second]);

					time = (std::clock() - start) / (double)CLOCKS_PER_SEC;

					if (time >= searchTime)
					{
						cout << "Droga: ";
						for (int d = 0; d < size; d++)
						{
							cout << best[d] << " ";
						}

						cout << "\nKoszt: " << result << endl;
						cout << "Znaleziono po: " << foundTime << " s " << endl;
						return;
					}
								
				}
			}	
			permutation = next;
			tabuMatrix[firstToSwap][secondToSwap] += size;
		}

		permutation.clear();

		permutation = randomPermutation(size);

		for (std::vector<vector<int> >::iterator it = tabuMatrix.begin(); it != tabuMatrix.end(); ++it) 
		{
			it->clear();
		}
		tabuMatrix.clear();

		tabuMatrix.resize(size);

		for (std::vector<vector<int> >::iterator it = tabuMatrix.begin(); it != tabuMatrix.end(); ++it) 
		{
			it->resize(size, 0);
		}
	}
}


vector<int> TabuSearch::randomPermutation(int _size)
{
	std::vector<int> temp;
	temp.reserve(_size);

	for (int i = 0; i < _size; i++)
	{
		temp.push_back(i);
	}

	random_shuffle(temp.begin(), temp.end());

	return temp;
}

int TabuSearch::calculatePath(vector<int> path)
{
	int cost = 0;

	for (int i = 0; i < path.size() - 1; ++i)
	{
		cost += matrix[path[i]][path[i + 1]];
	}
	cost += matrix[path[size-1]][path[0]];

	return cost;
}

TabuSearch::TabuSearch(Graph graph,int time)
{
	matrix = graph.getMatrix();
	size = graph.getCount();
	searchTime = time;
}

TabuSearch::~TabuSearch()
{
}
*/
