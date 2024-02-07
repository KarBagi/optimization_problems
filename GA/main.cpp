#include <iostream>
#include "Graph.h"
#include "GeneticAlgorithm.h"
#include <ctime>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
    int choice = 0;
    int timeM = 0, population = 0, method = 0;
    float wspK = 0, wspM = 0;
    string filename = "";

    Graph graph;

    srand(time(NULL));


    while(true) {
        cout << "Wybrany plik: " << filename << " , czas[s]: " << timeM << " , populacja: " << population << " ,wsp. krzyzowania: " << wspK << ", wsp. mutacji: " << wspM << endl;

        cout << "1. Wczytaj plik,\n";
        cout << "2. Podaj czas[s],\n";
        cout << "3. Podaj populacje,\n";
        cout << "4. Podaj wsp. krzyzowania,\n";
        cout << "5. Podaj wsp.mutacji,\n";
        cout << "6. Wybierz typ krzyzowania,\n";
        cout << "7. Wyjscie\n";

        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Podaj nazwe pliku: ";
                cin >> filename;

                graph.readGraph(filename);
                cout << graph.toString();

                break;
            }
            case 2:{
                cout << "Podaj czas: ";
                cin >> timeM;

                break;
            }
            case 3:{
                cout << "Podaj populacje: ";
                cin >> population;

                break;
            }
            case 4:{
                cout << "Podaj wsp. krzyzowania: ";
                cin >> wspK;

                break;
            }
            case 5:{
                cout << "Podaj wsp.mutacji: ";
                cin >> wspM;

                break;
            }
            case 6:{
                cout << "Podaj typ krzyzowania: \n";
                cout << "1. OX   2. PMX\n";
                cin >> method;

                GeneticAlgorithm alg(&graph, timeM, population, wspK, wspM);

                if(method == 1){
                    std::cout<<"Rozwiazanie: "<< alg.apply(true)<<std::endl;
                }
                if (method == 2){
                    std::cout<<"Rozwiazanie: "<< alg.apply(false)<<std::endl;
                }

                break;
            }
            case 7:{
                exit(0);
            }
        }
    }

    return 0;
}
