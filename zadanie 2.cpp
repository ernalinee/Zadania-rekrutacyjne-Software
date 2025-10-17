#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

//budujemy strukturę dla przechowywania współrzędnych punkt
struct point {
    float x, y;
};

//funkcja start bierze trzy punktu na plaszyznie i patrzy lokalnie na trzy punkty i mowi,
//w ktora strone jest nastepny punkt w otoczce: po lewej stronie, po prawej,
//czy prosto z punktu widzenia poprzedniego punktu w otoczce
int start( point q, point w, point e) {
    float vector=(w.x-q.x)*(e.y-q.y)-(w.y-q.y)*(e.x-q.x);
    float zero=1e-6;
    if (vector>zero)
        return 1; // znajduje sie po lewej stronie, wiec nie staje nowym punktem otoczki
    else if (vector<-zero)
        return 2; // znajduje sie po prawej stronie, wiec staje nowym punktem otoczki
    //(bo budujemy otoczke w kierunku wskazowek zegara)
    else
        return 0; //punkty leżą w jednej linii
}

//funkcja otoczkaF znachodzi otoczkę wypuklą, na poczatku znajdujac punkt najbardziej po prawej stronie
//i od niego zaczyna szukac i obierac nastepny punkt dla otoczki uzuwajac funkcji start,
//az dopoki naszym nastepnym punktem otoczki nie bedzie nasz najpierwszy punkt
void otoczkaF(vector<point> kropki) {
    int n=kropki.size();
    if (n<3) {
        cout<<"Trzeba minimum 3 punkty dla otoczki";
        return;
    }
    vector<point>otoczkaK;
    int prawa=0;
    //znajdujemy najbardziej prawy punkt
    for (int i=1; i<n; i++) {
        if (kropki[i].x>kropki[prawa].x)
            prawa=i;
    }
    int pierwsza=prawa, w;
    do {
        //dodajemy ten punkt do otoczki
        otoczkaK.push_back(kropki[pierwsza]);
        //szukamy nastepny punkt po prawej stronie, porownywajac inne punkty
        w=(pierwsza+1)%n;
        for (int i=0; i<n; i++) {
            if (start(kropki[pierwsza], kropki[i], kropki[w])==2)
                w=i;
    }
        //teraz q nasz najbardziej prawy punkt i zaczynamy szukac nowy punkt
    pierwsza=w;
    } while (pierwsza!=prawa);
    //wypisujemy punkty otoczki
    cout<<"Otoczka: ";
    cout<<fixed<<setprecision(1)<<showpoint;
    for (int i=0; i<otoczkaK.size(); i++) {
        cout<<"("<<otoczkaK[i].x<<", "<<otoczkaK[i].y<<")";
    }
}

//glowny program
int main() {
    int n;
    cout<<"Podaj liczbe punktow: ";
    cin>>n;
    vector<point> kropki(n);
    cout<<"Podaj wspolrzedne punktow (x y): ";
    for (int i=0; i<n; i++) {
        cin>>kropki[i].x>>kropki[i].y;
    }
    otoczkaF(kropki);

    return 0;
}
