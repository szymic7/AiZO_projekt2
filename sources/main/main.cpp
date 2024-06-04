#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
#include "../../headers/graphs/graph.h"
#include "../../headers/algorithms/dijkstra.h"
#include "../../headers/algorithms/bellmanFord.h"
#include "../../headers/algorithms/kruskal.h"
#include "../../headers/algorithms/prim.h"

using namespace std;

void showMenu() {

    // INICJALIZACJA GENERATORA LICZB LOSOWYCH
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

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
        cout << "Wybor:";
        cin >> problem;

        if(problem < 1 || problem > 2) {
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
                break;
            case 2: // Najkrotsza sciezka w grafie
                cout << "4) Wykonaj algorytm Dijkstry na ostatnio utworzonym grafie " << endl;
                cout << "5) Wykonaj algorytm Bellmana-Forda na ostatnio utworzonym grafie " << endl;
                break;
            default:
                cout << endl << "Wystapil blad." << endl;
                break;
        }

        cout << "6) Zakoncz" << endl;
        cout << "Wybor:";
        cin >> choice;

        switch(choice) {

            case 1: { // Wczytanie grafu z pliku .txt

                string filename;
                cout << "Podaj nazwe pliku: ";
                cin >> filename;

                // Sprawdzenie istnienia pliku
                ifstream file(filename);
                if (!file.is_open()) {
                    cout << endl << "Plik o nazwie " << filename << " nie istnieje." << endl;
                    cout << "Nie udalo sie wygenerowac grafu." << endl;
                    break;
                }
                file.close();

                // Wczytanie grafu z pliku
                graph.loadGraph(filename, problem != 1);    // problem == 1 - graf nieskierowany

                break;

            }

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

                if(problem == 1) graph.generateGraph(false, rng);    // MST - graf nieskierowany
                else graph.generateGraph(true, rng); // Najkrotsza droga - graf skierowany

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
                            cout << endl << "Podaj wierzcholek startowy:";
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

                        case 2:   // Najkrotsza sciezka - algorytm Dijkstry

                            // Ustawienie wierzcholka poczatkowego
                            cout << endl << "Podaj wierzcholek poczatkowy:";
                            cin >> start;
                            while (start < 0 || start >= graph.getVertices()) {
                                cout << endl << "Nieprawidlowy numer wierzcholka startowego." << endl;
                                cout << "Podaj poprawny wierzcholek poczatkowy:";
                                cin >> start;
                            }
                            dijkstra.setStart(start);

                            // Ustawienie wierzcholka koncowego
                            cout << "Podaj wierzcholek koncowy (rozny od wierzcholka poczatkowego):";
                            cin >> end;
                            while (end < 0 || end >= graph.getVertices() || end == start) {
                                cout << endl << "Nieprawidlowy numer wierzcholka koncowego." << endl;
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

                        default:

                            cout << endl << "Wystapil blad. Wybierz opcje ponownie." << endl;
                            break;
                    }

                } else {

                    cout << endl << "Utworz graf, aby wykonac algorytm." << endl;

                }

                break;

            case 5: // Drugi algorytm

                if(graph.getIncidenceMatrix() != nullptr && graph.getAdjacencyList() != nullptr) {

                    switch (problem) { // akcja w zaleznosci od wybranego problemu grafowego

                        case 1: // MST - algorytm Kruskala

                            pGraph = &graph;
                            kruskal.setGraph(pGraph);

                            // Algorytm Kruskala dla reprezentacji listowej grafu
                            startTime = chrono::high_resolution_clock::now();
                            kruskal.algorithmList();
                            endTime = chrono::high_resolution_clock::now();
                            time = chrono::duration<double, std::milli>(endTime - startTime);
                            kruskal.showMstList();    // wyswietlenie MST dla reprezentacji listowej
                            cout << "Czas dzialania algorytmu: " << time.count() << " ms\n" << endl;

                            // Algorytm Kruskala dla reprezentacji macierzowej grafu
                            startTime = chrono::high_resolution_clock::now();
                            kruskal.algorithmMatrix();
                            endTime = chrono::high_resolution_clock::now();
                            time = chrono::duration<double, std::milli>(endTime - startTime);
                            kruskal.showMstMatrix();    // wyswietlenie MST dla reprezemtacji macierzowej
                            cout << "Czas dzialania algorytmu: " << time.count() << " ms" << endl;

                            break;

                        case 2: // Najkrotsza sciezka - algorytm Bellmana-Forda

                            // Ustawienie wierzcholka poczatkowego
                            cout << endl << "Podaj wierzcholek poczatkowy:";
                            cin >> start;
                            while (start < 0 || start >= graph.getVertices()) {
                                cout << endl << "Nieprawidlowy numer wierzcholka startowego." << endl;
                                cout << "Podaj poprawny wierzcholek poczatkowy:";
                                cin >> start;
                            }
                            bellmanFord.setStart(start);

                            // Ustawienie wierzcholka koncowego
                            cout << "Podaj wierzcholek koncowy (rozny od wierzcholka poczatkowego):";
                            cin >> end;
                            while (end < 0 || end >= graph.getVertices() || end == start) {
                                cout << endl << "Nieprawidlowy numer wierzcholka koncowego." << endl;
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

                            break;

                        default:

                            cout << endl << "Wystapil blad. Wybierz opcje ponownie." << endl;
                            break;
                    }

                } else {

                    cout << endl << "Utworz graf, aby wykonac algorytm." << endl;

                }

                break;

            case 6: // Zakoncz

                quit = true;
                break;

            default:

                cout << endl << "Niepoprawny numer wybranej opcji. Wybierz ponownie." << endl;
                break;

        }

    } while(!quit);

}


// FUNKCJE DO POMIAROW SREDNIEGO CZASU WYKONYWANIA ALGORYTMOW

void pomiaryDijkstra() {

    // Inicjalizacja generatora liczb losowych
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // GRAF - ALOKOWANY DYNAMICZNIE
    int vertices, density;
    Graph graph;
    Graph *pGraph;

    // Algorytm Dijkstry
    Dijkstra dijkstra;

    // pomiar czasu
    chrono::high_resolution_clock::time_point startTime, endTime;
    double time = 0.0;

    // Poczatkowa liczba wierzcholkow - 20; kazda kolejna wieksza o 20
    vertices = 20;

    // Gestosc 50%
    density = 25;
    //graph.setDensity(density);

    int startVertice, endVertice;

    // Pomiary dla 7 reprezentatywnych wartosci liczby wierzcholkow
    for(int i = 0; i < 7; i++) {

        // Ustawienie liczby krawedzi dla grafu przed pomiarami (po zwiekszeniu liczby krawedzi)
        //graph.setVertices(vertices);
        graph = Graph(vertices, density);

        // Wyzerowanie zmiennej time przed kolejnymi 50 pomiarami
        time = 0.0;

        // 50 pomiarow
        for (int j = 0; j < 100; j++) {

            // Wygenerowanie grafu
            graph.generateGraph(true, rng);

            // Przypisanie grafu do obiektu klasy Dijkstra
            pGraph = &graph;
            dijkstra.setGraph(pGraph);

            // Wygenerowanie losowego wierzcholka startowego algorytmu
            startVertice = rng() % vertices;

            // Wygenerowanie losowego wierzcholka koncowego algorytmu (inny niz startowy)
            do {
                endVertice = rng() % vertices;
            } while (endVertice == startVertice);

            dijkstra.setStart(startVertice);
            dijkstra.setEnd(endVertice);

            // Algorytm dla reprezentacji listowej
            startTime = chrono::high_resolution_clock::now();
            dijkstra.algorithmMatrix();
            endTime = chrono::high_resolution_clock::now();
            //time += chrono::duration<double, std::milli>(endTime - startTime).count();
            time += chrono::duration<double, std::micro>(endTime - startTime).count();

        }

        // Obliczenie sredniego czasu z 50 pomiarow
        cout << endl << "Algorytm Dijkstry, lista sasiadow, gestosc " << density << "%, " << vertices << " wierzcholkow: " << time / 100.0 << " us." << endl;

        // Nastepna liczba wierzcholkow wieksza o 20 od poprzedniej
        vertices += 20;

    }


}

void pomiaryBellmanFord() {

    // Inicjalizacja generatora liczb losowych
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // GRAF - ALOKOWANY DYNAMICZNIE
    int vertices, density;
    Graph graph;
    Graph *pGraph;

    // Algorytm Bellmana Forda
    BellmanFord bellmanFord;

    // pomiar czasu
    chrono::high_resolution_clock::time_point startTime, endTime;
    double time = 0.0;

    // Poczatkowa liczba wierzcholkow - 20; kazda kolejna wieksza o 20
    vertices = 20;

    // Gestosc: 25, 50, 99%
    density = 99;
    //graph.setDensity(density);

    int startVertice, endVertice;

    // Pomiary dla 7 reprezentatywnych wartosci liczby wierzcholkow
    for(int i = 0; i < 7; i++) {

        // Ustawienie liczby krawedzi dla grafu przed pomiarami (po zwiekszeniu liczby krawedzi)
        //graph.setVertices(vertices);
        graph = Graph(vertices, density);

        // Wyzerowanie zmiennej time przed kolejnymi 50 pomiarami
        time = 0.0;

        // 50 pomiarow
        for (int j = 0; j < 100; j++) {

            // Wygenerowanie grafu
            graph.generateGraph(true, rng); // najkrotsza sciezka - graf skierowany

            // Przypisanie grafu do obiektu klasy Dijkstra
            pGraph = &graph;
            bellmanFord.setGraph(pGraph);

            // Wygenerowanie losowego wierzcholka startowego algorytmu
            startVertice = rng() % vertices;

            // Wygenerowanie losowego wierzcholka koncowego algorytmu (inny niz startowy)
            do {
                endVertice = rng() % vertices;
            } while (endVertice == startVertice);

            bellmanFord.setStart(startVertice);
            bellmanFord.setEnd(endVertice);

            // Algorytm dla reprezentacji listowej
            startTime = chrono::high_resolution_clock::now();
            bellmanFord.algorithmList();
            endTime = chrono::high_resolution_clock::now();
            //time += chrono::duration<double, std::milli>(endTime - startTime).count();
            time += chrono::duration<double, std::micro>(endTime - startTime).count();

        }

        // Obliczenie sredniego czasu z 50 pomiarow
        cout << endl << "Algorytm Bellmana-Forda, lista sasiadow, gestosc " << density << "%, " << vertices << " wierzcholkow: " << time / 100.0 << " us." << endl;

        // Nastepna liczba wierzcholkow wieksza o 20 od poprzedniej
        vertices += 20;

    }

}

void pomiaryPrim() {

    // Inicjalizacja generatora liczb losowych
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // GRAF - ALOKOWANY DYNAMICZNIE
    int vertices, density;
    Graph graph;
    Graph *pGraph;

    // Algorytm Kruskala
    Prim prim;

    // pomiar czasu
    chrono::high_resolution_clock::time_point startTime, endTime;
    double time = 0.0;

    // Poczatkowa liczba wierzcholkow - 20; kazda kolejna wieksza o 20
    vertices = 20;

    // Gestosc: 25, 50, 99%
    density = 25;

    // Pomiary dla 7 reprezentatywnych wartosci liczby wierzcholkow
    for(int i = 0; i < 7; i++) {

        // Ustawienie liczby krawedzi dla grafu przed pomiarami (po zwiekszeniu liczby krawedzi)
        graph = Graph(vertices, density);

        // Wyzerowanie zmiennej time przed kolejnymi 50 pomiarami
        time = 0.0;

        // 50 pomiarow
        for (int j = 0; j < 100; j++) {

            // Wygenerowanie grafu
            graph.generateGraph(false, rng); // algorytm MST - graf nieskierowany

            // Przypisanie grafu do obiektu klasy Dijkstra
            pGraph = &graph;
            prim.setGraph(pGraph);

            prim.setStart(rng() % vertices);

            // Algorytm dla reprezentacji listowej
            startTime = chrono::high_resolution_clock::now();
            prim.algorithmMatrix();
            endTime = chrono::high_resolution_clock::now();
            //time += chrono::duration<double, std::milli>(endTime - startTime).count();
            time += chrono::duration<double, std::micro>(endTime - startTime).count();

        }

        // Obliczenie sredniego czasu z 50 pomiarow
        cout << endl << "Algorytm Prima, macierz incydencji, gestosc " << density << "%, " << vertices << " wierzcholkow: " << time / 100.0 << " us." << endl;

        // Nastepna liczba wierzcholkow wieksza o 20 od poprzedniej
        vertices += 20;

    }

}

void pomiaryKruskal() {

    // Inicjalizacja generatora liczb losowych
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // GRAF - ALOKOWANY DYNAMICZNIE
    int vertices, density;
    Graph graph;
    Graph *pGraph;

    // Algorytm Kruskala
    Kruskal kruskal;

    // pomiar czasu
    chrono::high_resolution_clock::time_point startTime, endTime;
    double time = 0.0;

    // Poczatkowa liczba wierzcholkow - 20; kazda kolejna wieksza o 20
    vertices = 20;

    // Gestosc: 25, 50, 99%
    density = 50;

    // Pomiary dla 7 reprezentatywnych wartosci liczby wierzcholkow
    for(int i = 0; i < 7; i++) {

        // Ustawienie liczby krawedzi dla grafu przed pomiarami (po zwiekszeniu liczby krawedzi)
        graph = Graph(vertices, density);

        // Wyzerowanie zmiennej time przed kolejnymi 50 pomiarami
        time = 0.0;

        // 50 pomiarow
        for (int j = 0; j < 100; j++) {

            // Wygenerowanie grafu
            graph.generateGraph(false, rng);    // algorytm MST - graf nieskierowany

            // Przypisanie grafu do obiektu klasy Dijkstra
            pGraph = &graph;
            kruskal.setGraph(pGraph);

            // Algorytm dla reprezentacji listowej
            startTime = chrono::high_resolution_clock::now();
            kruskal.algorithmList();
            endTime = chrono::high_resolution_clock::now();
            //time += chrono::duration<double, std::milli>(endTime - startTime).count();
            time += chrono::duration<double, std::micro>(endTime - startTime).count();

        }

        // Obliczenie sredniego czasu z 50 pomiarow
        cout << endl << "Algorytm Kruskala, lista, gestosc " << density << "%, " << vertices << " wierzcholkow: " << time / 100.0 << " us." << endl;

        // Nastepna liczba wierzcholkow wieksza o 20 od poprzedniej
        vertices += 20;

    }

}



int main() {
    showMenu();
    return 0;
}
