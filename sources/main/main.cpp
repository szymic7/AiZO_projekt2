#include <iostream>
#include "../../headers/graphs/graph.h"

using namespace std;

void showMenu() {

    // ZMIENNE POMOCNICZE
    int problem = 0, choice = 0;
    bool quit = false;

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

                // WYGENEROWANIE GRAFU
                break;

            case 3: // Wyswietlenie grafu

                // WYSWIETLENIE GRAFU
                break;

            case 4: // Pierwszy algorytm

                switch(problem) { // akcja w zaleznosci od wybranego problemu grafowego
                    case 1: // MST - algorytm Prima

                        // ALGORYTM PRIMA
                        break;

                    case 2: // Najkrotsza sciezka - algorytm Dijkstry

                        // ALGORYTM DIJKSTRY
                        break;

                    case 3: // Maksymalny przeplyw - algorytm Forda-Fulkersona

                        // ALGORYTM FORDA-FULKERSONA
                        break;

                    default:

                        cout << endl << "Wystapil blad. Wybierz opcje ponownie." << endl;
                        break;
                }
                break;

            case 5: // Drugi algorytm / Zakoncz

                switch(problem) { // akcja w zaleznosci od wybranego problemu grafowego
                    case 1: // MST - algorytm Kruskala

                        // ALGORYTM KRUSKALA
                        break;

                    case 2: // Najkrotsza sciezka - algorytm Bellmana-Forda

                        // ALGORYTM BELLMANA-FORDA
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
    //showMenu();

    // TEST

    Graph graph(4, 50);
    int **matrix;

    // alokacja pamieci dla tablicy dwuwymiarowej
    matrix = new int*[4];
    for (int i = 0; i < 4; ++i) {
        matrix[i] = new int[5];
    }

    // przypisanie wartosci do elementow macierzy
    int number = -7;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            matrix[i][j] = number;
            number++;
        }
    }

    graph.setIncidenceMatrix(matrix);
    graph.setEdges(5);
    graph.showIncidenceMatrix();

    return 0;
}
