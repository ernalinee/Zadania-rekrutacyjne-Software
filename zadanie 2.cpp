#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct point {
    int x, y;
};

int start( point q, point w, point e) {
    int vector=(w.x - q.x) * (e.y - q.y) - (w.y - q.y) * (e.x - q.x);
    if (vector == 0){
        return 0; 
         if (vector > 0){
            return 1; 
        }
        else {
            return 2;
        }
    }
}

int main()
{
    

    return 0;
}