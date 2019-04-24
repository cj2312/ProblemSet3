#include <iostream >
#include<string>
using namespace std;

const string vowels = " aeiou ";

string pigLatinify(const string s){
    if(s.size()==0){return s;}//cadena vacia oopaaa!!
    if (s.find("qu")==0){//iniciamos con "qu"
        return s.substr(2, s.size()-2) + "-" + s.substr(0,2) + "ay";//si empieza con qu entonces le quita los 2 primeros caracteres y los pone al final con un - y con ay
    }
    else if(vowels.find(s[0]) != string::npos){return s + "way";}//si empieza con vocales entonces le aumenta way
    else {return s.substr(1,s.size()-1) + "-" + s[0] + "ay";}//si no empieza con qu ni vocal le quita el priemr caracter y o pone al ifinal con - y ay

}

int main(){
    cout<<pigLatinify("hola que tal");

}
