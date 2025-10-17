#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>
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

// oblicza nowy punkt "nowy", ktory wychodzi z obracania punktu p wokol (0,0)o kat a
point obracanie(point p, float a) {
    point nowy;
    nowy.x=p.x*cos(a)-p.y*sin(a);
    nowy.y=p.x*sin(a)+p.y*cos(a);
    return nowy;
}
//glowny program
int main() {
    int n;
    cout<<"Podaj liczbe punktow: ";
    cin>>n;
    vector<point> kropki(n);
    vector<point> kropki1(n);
    cout<<"Podaj wspolrzedne punktow (x y): ";
    for (int i=0; i<n; i++) {
        cin>>kropki[i].x>>kropki[i].y;
    }
    for (int i=0; i<n; i++) {
        kropki1[i].x=kropki[i].x;
        kropki1[i].y=kropki[i].y;
    }
    //przepisuje d na poczatek najwieksza wartosc
    float d=numeric_limits<float>::max();

    // przechodzimy przez wszystkie pary punktów
    for (int i=0; i<n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            float dx=kropki1[j].x-kropki1[i].x;
            float dy=kropki1[j].y-kropki1[i].y;
            //porownujemy roznice wspolrzednych dwoch punktow i szukamy roznych od siebie
            if (fabs(dx)<1e-6f && fabs(dy)<1e-6f)
                continue;
            //jak znachodzimy takie punkty, to liczymy kat nachylenia prostej miedzy nimi
            float a=atan2(dy, dx);
            float minY=numeric_limits<float>::max();
            float maxY=numeric_limits<float>::lowest();
            //obracamy wszystkie punkty, tak zeby prosta przechodzaca przez te punkty stala pozioma
            for (int i=0; i < kropki.size(); i++) {
                point p=kropki1[i];
                point nowy=obracanie(p, -a);
                if (nowy.y<minY)
                    minY=nowy.y;
                if (nowy.y>maxY)
                    maxY=nowy.y;
            }
            //i obliczamy szerokosc prostej
            float width=maxY-minY;
            if (width<d)
                d=width;
        }
    }
    otoczkaF(kropki);
    cout<<fixed<<setprecision(4)<<showpoint;
    cout<<endl<<"Proste: d="<<d;
    return 0;
}
