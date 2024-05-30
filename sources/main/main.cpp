#include <iostream>
#include <chrono>
#include "../../headers/graphs/graph.h"
#include "../../headers/algorithms/dijkstra.h"
#include "../../headers/algorithms/bellmanFord.h"
#include "../../headers/algorithms/kruskal.h"
#include "../../headers/algorithms/prim.h"

using namespace std;

void showMenu() {

    // ZMIENNE POMOCNICZE - DO POBIERANIA INPUTU OD UZYTKOWNIKA
    int problem = 0, choice = 0;
    bool quit = false;
    int vertices, density;
    int start, end;

    // ZMIENNE DO MIERZENIA CZASU DZIALANIA ALGORYTMOW
    chrono::high_resolution_clock::time_point startTime, endTime;
    chrono::duration<double, std::milli> time(0);

    // GRAF - ALOKOWANY DYNAMICZNIE
    Graph graph;
    Graph *pGraph;

    // OBIEKTY DO WYKONYWANIA ALGORYTMOW NA GRAFACH
    Prim prim;
    Kruskal kruskal;
    Dijkstra dijkstra;
    BellmanFord bellmanFord;


    // PIERWSZY POZIOM MENU - WYBOR PROBLEMU DO ROZWIAZANIA
    do {
        cout << endl << "Ktory problem grafowy chcesz rozwiacac?" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
        cout << "1) Wyznaczanie minimalnego drzewa rozpinajacego (MST) - algorytmy Prima i Kruskala" << endl;
        cout << "2) Wyznaczanie najkrotszej sciezki w grafie - algorytmy Dijkstry i Bellmana-Forda" << endl;
        cout << "3) Wyznaczanie maksymalnego przeplywu - algorytm Forda-Fulkersona" << endl;
        cout << "Wybor:";
        cin >> problem;

        if(problem < 1 || problem > 3) {
            cout << endl << "Nieprawidlowy numer wybranej opcji. Sprobuj ponownie." << endl;
            problem = 0;
        }

    } while (problem == 0);


    // DRUGI POZIOM MENU - TWORZENIE/WYSWIETLANIE GRAFU, WYBOR ALGORYTMU
    do {
        cout << endl << "Wybierz operacje: " << endl;
        cout << "-------------------------------------" << endl;
        cout << "1) Wczytaj graf z pliku .txt" << endl;
        cout << "2) Wygeneruj graf losowo" << endl;
        cout << "3) Wyswietl ostatnio utworzony graf w formie macierzy incydencji i listy sasiadow" << endl;

        switch (problem) { // Algorytmy do wyboru w zaleznosci od wybranego problemu grafowego
            case 1: // MST
                cout << "4) Wykonaj algorytm Prima na ostatnio utworzonym grafie " << endl;
                cout << "5) Wykonaj algorytm Kruskala na ostatnio utworzonym grafie " << endl;
                cout << "6) Zakoncz" << endl;
                break;
            case 2: // Najkrotsza sciezka w grafie
                cout << "4) Wykonaj algorytm Dijkstry na ostatnio utworzonym grafie " << endl;
                cout << "5) Wykonaj algorytm Bellmana-Forda na ostatnio utworzonym grafie " << endl;
                cout << "6) Zakoncz" << endl;
                break;
            case 3: // Wyznaczanie maksymalnego przeplywu
                cout << "4) Wykonaj algorytm Forda-Fulkersona na ostatnio utworzonym grafie " << endl;
                cout << "5) Zakoncz" << endl;
        }

        cout << "Wybor:";
        cin >> choice;

        switch(choice) {
            case 1: // Wczytanie grafu z pliku .txt

                // WCZYTANIE GRAFU Z PLIKU
                break;

            case 2: // Genrowanie losowego grafu

                cout << endl << "Podaj liczbe wierzcholkow grafu:";
                cin >> vertices;
                while(vertices < 1) {
                    cout << endl <<  "Nieprawidlowa wartosc.\nPodaj liczbe wierzcholkow grafu:";
                    cin >> vertices;
                }

                cout << "Podaj gestosc grafu w procentach:";
                cin >> density;
                while(density < 0 || density > 100) {
                    cout << endl <<  "Nieprawidlowa wartosc.\nPodaj gestosc grafu w procentach:";
                    cin >> density;
                }

                graph = Graph(vertices, density);

                if(problem == 1) graph.generateGraph(false);    // MST - graf nieskierowany
                else graph.generateGraph(true); // Najkrotsza droga i max przeplyw - graf skierowany

                break;

            case 3: // Wyswietlenie grafu

                if(graph.getAdjacencyList() != nullptr && graph.getIncidenceMatrix() != nullptr) {
                    graph.showAdjacencyList();
                    graph.showIncidenceMatrix();
                } else {
                    cout << endl << "Utworz graf, aby moc go wyswietlic." << endl;
                }

                break;

            case 4: // Pierwszy algorytm

                if(graph.getIncidenceMatrix() != nullptr && graph.getAdjacencyList() != nullptr) {

                    switch (problem) { // akcja w zaleznosci od wybranego problemu grafowego
                        case 1: // MST - algorytm Prima

                            // Ustawienie wierzcholka startowego
                            cout << "Podaj wierzcholek startowy:";
                            cin >> start;
                            while (start < 0 || start >= graph.getVertices()) {
                                cout << "Nieprawidlowy numer wierzcholka." << endl;
                                cout << "Podaj poprawny wierzcholek startowy:";
                                cin >> start;
                            }
                            prim.setStart(start);

                            pGraph = &graph;
                            prim.setGraph(pGraph);

                            // Algorytm Prima dla reprezentacji listowej grafu
                            startTime = chrono::high_resolution_clock::now();
                            prim.algorithmList();
                            endTime = chrono::high_resolution_clock::now();
                            time = chrono::duration<double, std::milli>(endTime - startTime);
                            prim.showMstList();    // wyswietlenie MST dla reprezentacji listowej
                            cout << "Czas dzialania algorytmu: " << time.count() << " ms\n" << endl;

                            // Algorytm Prima dla reprezentacji macierzowej grafu
                            startTime = chrono::high_resolution_clock::now();
                            prim.algorithmMatrix();
                            endTime = chrono::high_resolution_clock::now();
                            time = chrono::duration<double, std::milli>(endTime - startTime);
                            prim.showMstMatrix();    // wyswietlenie MST dla reprezemtacji macierzowej
                            cout << "Czas dzialania algorytmu: " << time.count() << " ms" << endl;

                            break;

                        case 2: {   // Najkrotsza sciezka - algorytm Dijkstry

                            // Ustawienie wierzcholka poczatkowego
                            cout << "Podaj wierzcholek poczatkowy:";
                            cin >> start;
                            while (start < 0 || start >= graph.getVertices()) {
                                cout << "Nieprawidlowy numer wierzcholka startowego." << endl;
                                cout << "Podaj poprawny wierzcholek poczatkowy:";
                                cin >> start;
                            }
                            dijkstra.setStart(start);

                            // Ustawienie wierzcholka koncowego
                            cout << "Podaj wierzcholek koncowy (rozny od wierzcholka poczatkowego):";
                            cin >> end;
                            while (end < 0 || end >= graph.getVertices() || end == start) {
                                cout << "Nieprawidlowy numer wierzcholka koncowego." << endl;
                                cout << "Podaj poprawny wierzcholek koncowy:";
                                cin >> end;
                            }
                            dijkstra.setEnd(end);

                            // Przypisanie grafu do obiektu klasy Dijkstra
                            pGraph = &graph;
                            dijkstra.setGraph(pGraph);

                            // Algorytm Dijkstry dla reprezentacji listowej grafu
                            startTime = chrono::high_resolution_clock::now();
                            dijkstra.algorithmList();
                            endTime = chrono::high_resolution_clock::now();
                            time = chrono::duration<double, std::milli>(endTime - startTime);
                            dijkstra.showPathList();    // wyswietlenie najkrotszej sciezki dla reprezemtacji listowej
                            cout << "Czas dzialania algorytmu: " << time.count() << " ms\n" << endl;

                            // Algorytm Dijkstry dla reprezentacji macierzowej grafu
                            startTime = chrono::high_resolution_clock::now();
                            dijkstra.algorithmMatrix();
                            endTime = chrono::high_resolution_clock::now();
                            time = chrono::duration<double, std::milli>(endTime - startTime);
                            dijkstra.showPathMatrix();    // wyswietlenie najkrotszej sciezki dla reprezemtacji macierzowej
                            cout << "Czas dzialania algorytmu: " << time.count() << " ms" << endl;

                            break;

                        }

                        case 3: // Maksymalny przeplyw - algorytm Forda-Fulkersona

                            // ALGORYTM FORDA-FULKERSONA
                            break;

                        default:

                            cout << endl << "Wystapil blad. Wybierz opcje ponownie." << endl;
                            break;
                    }

                } else {

                    cout << endl << "Utworz graf, aby wykonac algorytm." << endl;

                }

                break;

            case 5: // Drugi algorytm / Zakoncz

                switch(problem) { // akcja w zaleznosci od wybranego problemu grafowego
                    case 1: // MST - algorytm Kruskala

                        if(graph.getIncidenceMatrix() != nullptr && graph.getAdjacencyList() != nullptr) {

                            // ALGORYTM KRUSKALA

                        } else {

                            cout << endl << "Utworz graf, aby wykonac algorytm." << endl;

                        }

                        break;

                    case 2: // Najkrotsza sciezka - algorytm Bellmana-Forda

                        if(graph.getIncidenceMatrix() != nullptr && graph.getAdjacencyList() != nullptr) {

                            // Ustawienie wierzcholka poczatkowego
                            cout << endl << "Podaj wierzcholek poczatkowy:";
                            cin >> start;
                            while (start < 0 || start >= graph.getVertices()) {
                                cout << "Nieprawidlowy numer wierzcholka startowego." << endl;
                                cout << "Podaj poprawny wierzcholek poczatkowy:";
                                cin >> start;
                            }
                            bellmanFord.setStart(start);

                            // Ustawienie wierzcholka koncowego
                            cout << "Podaj wierzcholek koncowy (rozny od wierzcholka poczatkowego):";
                            cin >> end;
                            while (end < 0 || end >= graph.getVertices() || end == start) {
                                cout << "Nieprawidlowy numer wierzcholka koncowego." << endl;
                                cout << "Podaj poprawny wierzcholek koncowy:";
                                cin >> end;
                            }
                            bellmanFord.setEnd(end);

                            // Przypisanie grafu do obiektu klasy BellmanFord
                            pGraph = &graph;
                            bellmanFord.setGraph(pGraph);

                            // Algorytm Bellmana-Forda dla reprezentacji listowej grafu
                            startTime = chrono::high_resolution_clock::now();
                            bellmanFord.algorithmList();
                            endTime = chrono::high_resolution_clock::now();
                            time = chrono::duration<double, std::milli>(endTime - startTime);
                            bellmanFord.showPathList();    // wyswietlenie najkrotszej sciezki dla reprezemtacji listowej
                            cout << "Czas dzialania algorytmu: " << time.count() << " ms\n" << endl;

                            // Algorytm Bellmana-Forda dla reprezentacji macierzowej grafu
                            startTime = chrono::high_resolution_clock::now();
                            bellmanFord.algorithmMatrix();
                            endTime = chrono::high_resolution_clock::now();
                            time = chrono::duration<double, std::milli>(endTime - startTime);
                            bellmanFord.showPathMatrix();    // wyswietlenie najkrotszej sciezki dla reprezemtacji listowej
                            cout << "Czas dzialania algorytmu: " << time.count() << " ms" << endl;

                        } else {

                            cout << endl << "Utworz graf, aby wykonac algorytm." << endl;

                        }

                        break;


                    case 3: // Maksymalny przeplyw - Zakoncz

                        quit = true;
                        break;

                    default:

                        cout << endl << "Wystapil blad. Wybierz opcje ponownie." << endl;
                        break;
                }
                break;

            case 6: // Zakoncz / niepoprawny numer

                if(problem == 1 || problem == 2) // MST i Najkrotsza sciezka
                    quit = true;
                else // Maksymalny przeplyw
                    cout << endl << "Niepoprawny numer wybranej opcji. Wybierz ponownie." << endl;
                break;

            default:

                cout << endl << "Niepoprawny numer wybranej opcji. Wybierz ponownie." << endl;
                break;
        }

    } while(!quit);

}


int main() {
    showMenu();
    return 0;
}
