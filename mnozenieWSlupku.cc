#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

deque <int> suma(deque<int> a, deque<int> b){ // a, b - reversed
  deque <int> wynik;
  int i, j;      // indexy iterujące po deque
  int temp = 0;

  for(i=0, j=0;
      i<a.size() && j<b.size();
      i++, j++){
    wynik.push_back((a[i]+b[j]+temp)%10);
    temp = (a[i]+b[j]+temp)/10;
  }

  for(; i<a.size(); i++){
    wynik.push_back((a[i]+temp)%10);
    temp = (a[i]+temp)/10;
  }
  for(; j<b.size(); j++){
    wynik.push_back((b[j]+temp)%10);
    temp = (b[j]+temp)/10;
  }
  if(temp) wynik.push_back(temp);

  return wynik;
}


deque <int> iloczyn(string a, string b){
  vector <deque <int> > skladniki;

  for(int i=b.size()-1; i>=0; i--){
    int temp = 0;                               // reszta
    deque <int> polW;                           // 1/2 wynik
    for(int j=a.size()-1; j>=0; j--){
      int cwiercW = (b[i]-'0')*(a[j]-'0')+temp; //  1/4 wynik
      polW.push_back(cwiercW%10);
      temp = cwiercW/10;
    }
    if(temp) polW.push_back(temp);
    skladniki.push_back(polW);
  }

  deque <int> wynik;

  for(int i=0; i<skladniki.size(); i++){
    for(int j=0; j<i; j++) skladniki[i].push_front(0);
    wynik = suma(wynik, skladniki[i]);
  }

  return wynik;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long Z;
  cin >> Z;
  while(Z-- > 0){
    string a, b;
    cin >> a >> b;
    bool ujemna = false;

    if((a[0] == '-') != (b[0] == '-')) ujemna = true;
    if(a[0] == '-') a.erase(a.begin());
    if(b[0] == '-') b.erase(b.begin());


    if(a.size() == b.size() && a<b) swap(a, b);
    else if(a.size()<b.size()) swap(a, b);                       // a >= b

    deque <int> wynik = iloczyn(a, b);

    if((wynik.back() != 0) && (ujemna)) cout << '-';

    int i = wynik.size()-1;
    while(i > 0 && wynik[i]==0) i--;
    for(; i>=0; i--){
      cout << wynik[i];
    }
    cout << "\n";
  }
}