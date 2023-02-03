#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include "json.hpp"
#include <sstream>

using json = nlohmann::json;

int main() {
  std::ifstream mapfile("map.json");
  json map = json::parse(mapfile);
  Trem trem(map);
  auto plats = map.at("central");
  int command = 1;
  while (true) {
    printf("1: cabo\n2:nova plataforma");
    std::cin >> command;
    if (command = 1) {
      std::string nome, plats;
      printf("nome: \n");
      cin >> nome;
      printf("plats ('plat1 plat2'): \n");
      cin >> plats;
      string line = plats;
      string arr[];
      int i = 0;
      stringstream ssin(line);
      while (ssin.good() && i < 4){
        ssin >> arr[i];
        ++i;
      }
      plats[plats.size()] ;
    }
  }
}
