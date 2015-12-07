/*
	@ Kalkulator - algorytm E.Dijkstra
	@ Autor: Emil Stefaniuk <emste@emste.eu>
	@ [INPUT] Dzialanie matematyczne - elementy oddzielone spacjami
	@ Przyklad dobrego wejscia: ( 2 + ( 2 * 2 ) )
	@ [OUTPUT] Wynik dzia³ania
*/
 
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

stack <char> stosOperatorow;
stack <double> stosLiczb;

string str;
string word;

int iteracja = 0;
int nawiasy = 0;

bool error = false;

double wynik_koncowy= 0;
int main()
{
	cout << "Wpisz dzialanie: "<<endl;
	getline(cin,str);
	stringstream stream(str);
	while( getline(stream, word, ' ') ){
		bool good_syntax = false;
        
		if(iteracja == 0 && word != "(" || iteracja == 0 && word==" "){
            error = true;
            break;
        }
        
		stringstream ss(word);
		double i;
		ss >> i;
		
		if(i > 0){ stosLiczb.push(i); good_syntax = true;}       
        if(word == "("){ nawiasy++; good_syntax = true;}
       
		 if(word == ")"){
			good_syntax = true;
			if(stosLiczb.size() > 1){
                double jeden = stosLiczb.top();
                stosLiczb.pop();
                double dwa = stosLiczb.top();
                
				string operatore;
				operatore = stosOperatorow.top();
				stosOperatorow.pop();
                               
				double wynikdzialania = 0;
				if(operatore == "+"){ wynikdzialania = jeden + dwa;}
				if(operatore == "-"){ wynikdzialania = dwa - jeden;}
				if(operatore == "*"){ wynikdzialania = jeden * dwa;}
				if(operatore == "/"){
					if(jeden == 0){ error = true; }
					else{ wynikdzialania = dwa / jeden; }
                }
				
				stosLiczb.top() = wynikdzialania;
				nawiasy--;
				wynik_koncowy = wynikdzialania;
			}
		}
 
		if(word == "+" || word == "-" || word == "*" || word == "/"){
			good_syntax = true;
			const char * c = word.c_str();
			stosOperatorow.push(*c);
		}
       
        if(!good_syntax) error = true;
       
		iteracja++;
	}
	if(error || nawiasy) { cout << "Blad skladni"; }
	else cout << "Wynik wynosi:" << wynik_koncowy;
	
	return 0;
}
