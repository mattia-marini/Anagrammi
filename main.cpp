#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<string> normali;
vector<string> scurrili;
vector<string> verbi;
int map[26];
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

#define BOLD "\033[1m"
#define ITALICS "\033[3m"
#define CLS "\033[2J\033[1;1H"

string frase = "desdromenzitediocan";
//string frase ="";

bool isContained(string s1, int map[]) {

  int tmpMap[26];
  memcpy(tmpMap, map, 26 * sizeof(int));

  for (int i = 0; i < s1.size(); i++) {
    if (tmpMap[s1[i] - 'a'] == 0)
      return false;
    else
      tmpMap[s1[i] - 'a']--;
  }
  return true;
}

void trimWhitespaces() {
  int i = 0;
  while (i < frase.size() && frase[i] == ' ')
    i++;
  frase.erase(0, i);

  i = frase.size() - 1;
  while (i >= 0 && frase[i] == ' ')
    i--;
  frase.erase(i + 1, string::npos);
}

void eraseLetters(string s) {
  for (int i = 0; i < s.size(); i++) {
    int j = 0;
    while (frase[j] != s[i])
      j++;
    frase.erase(j, 1);
  }

  trimWhitespaces();

  /*
  for (int i = 0; i < frase.size(); i++) {
    if (frase[i] == ' ') {
      int j = 0;
      while (s[i] == ' ') {
        j++;
      }
      if (j != 0)
        frase.erase(i, j - 1);
    }
  }
  */
}

string normalize(string s) {
  string tmp = "";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != ' ')
      tmp.push_back(s[i]);
  }

  return tmp;
}
/*
void normalizeString(string& s){
for(int i = 0; i<s.size(); i++){
if((s[i]>='a' && s[i]<='z')){
if(s[i]=='è' or s[i] == 'é')
  s[i]='e';
}
}
}
  */

void whatIsAvailable() {
  std::cout << GREEN << BOLD << "-----------PAROLE NORMALI-----------" << RESET
            << std::endl;

  for (int i = 0; i < normali.size(); i++) {
    if (isContained(normali[i], map))
      std::cout << normali[i] << "\n";
  }

  std::cout << RED << BOLD << "-----------PAROLE SCURRILI-----------" << RESET
            << std::endl;

  for (int i = 0; i < scurrili.size(); i++) {
    if (isContained(scurrili[i], map))
      std::cout << scurrili[i] << std::endl;
  }

  std::cout << BLUE << BOLD << "-----------VERBI-----------" << RESET
            << std::endl;

  for (int i = 0; i < verbi.size(); i++) {
    if (isContained(verbi[i], map))
      std::cout << verbi[i] << std::endl;
  }
}

int main(int argc, char *argv[]) {
  ifstream normaliIn("normali.txt");
  ifstream scurriliIn("scurrili.txt");
  ifstream verbiIn("verbi.txt");

  memset(map, 0, 26 * sizeof(int));
  trimWhitespaces();

  const string fraseNormalized = normalize(frase);
  std::cout << fraseNormalized << std::endl;

  for (int i = 0; i < fraseNormalized.size(); i++)
    map[fraseNormalized[i] - 'a']++;

  string tmp;
  while (normaliIn.good()) {
    normaliIn >> tmp;
    normali.push_back(tmp);
  }
  while (scurriliIn.good()) {
    scurriliIn >> tmp;
    scurrili.push_back(tmp);
  }
  while (verbiIn.good()) {
    verbiIn >> tmp;
    verbi.push_back(tmp);
  }

  /*
  string userIn = "";
  std::cout << CLS;
  while (true) {
    std::cout << ITALICS << "La tua frase:\n\n" << frase << std::endl;
    std::cout << RESET << BOLD << "\n"
              << GREEN << "A - Verifica parole contenute \n"
              << BLUE << "B - Verifica se è contenuta parola\n"
              << YELLOW << "C - Sottrai\n"
              << RED << "Q - Quit\n"
              << RESET << std::endl;
    cin >> userIn;

    cout << CLS;

    if (userIn.compare("Q") == 0 or userIn.compare("q") == 0)
      break;

    else if (userIn.compare("A") == 0 or userIn.compare("a") == 0)
      whatIsAvailable();

    else if (userIn.compare("B") == 0 or userIn.compare("b") == 0) {
      std::cout << ITALICS
                << "Dammi una parola per cui verificare se sia contenuta"
                << RESET << std::endl;
      string candidato;
      cin >> candidato;
      std::cout << CLS;
      if (isContained(candidato, map))
        std::cout << GREEN << "La parola è contenuta!" << std::endl;
      else
        std::cout << RED << "La parola NON è contenuta!" << std::endl;

      cout << RESET;
    }

    else if (userIn.compare("C") == 0 or userIn.compare("c") == 0) {
      std::cout << ITALICS << "Dammi una parola da sottrarre" << RESET
                << std::endl;
      string candidato;
      cin >> candidato;
      cout << CLS;
      if (!isContained(candidato, map))
        std::cout << RED << "Mona va che non è contenuta sta parola, dovmi eh"
                  << std::endl;
      else {
        for (int i = 0; i < candidato.size(); i++) {
          map[candidato[i] - 'a']--;
        }
        eraseLetters(candidato);
        std::cout << GREEN << "Sottratto con successo" << std::endl;
      }

      std::cout << RESET;
    }

    else {
      std::cout << "Hai fat-fingerato, sei stra gay" << std::endl;
    }
  }
  */
}
