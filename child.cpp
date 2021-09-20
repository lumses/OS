#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;
int main(){
    double a;
    char c;
    double res = 0;
    int k = 0;
    while(scanf("%lf%c", &a, &c) != EOF) {
        if (k == 0){
            res = a;
            k=1;
        } else {
            if (a!=0){
                res/=a;
            } else {
              cout << "You can't divide it by zero" << endl;
              break;
            } 
        }
        if(c == '\n') {
            cout << res << endl;
            k=0;
            fflush(stdout);
            res = 0.;
            continue;
        }
    }
  //  cout << res << endl;
    close(STDOUT_FILENO);
    return 0;
}