#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include "json.hpp"

using json = nlohmann::json;

class Trem {
public:
  int pos = -1;
  json map;
  int nextpos = 1;
  std::string plat = "";

  Trem(json map) {
    this->map = map;
  };

  bool changePlat(std::string plataforma) {
    bool canChange = false;
    if (this->plat == "") {
      this->plat = plataforma;
      canChange = true;
    }else {
      auto platsHere = map.at("central").at(this->pos).at("plat");
      bool hasPlatAsked = false;
      bool hasMine = false;
      auto plats = map.at("central").at(this->pos).at("plat");
      for (auto it = plats.begin(); it != plats.end(); ++it) {
	if (*it == plataforma) {
	  hasPlatAsked = true;
	  continue;
	}
	if (*it == this->plat) {
	  hasMine = true;
	  continue;
	}
      }
      canChange = (hasPlatAsked && hasMine);
      if (canChange) this->plat = plataforma;
    }
    return canChange;
  }

  bool previous(std::string plataforma = "") {
    if (this->plat == "") this->plat = plataforma;
    auto central = map.at("central");
    if (this->pos - 1 <= -1) return false;
    bool shouldstop = false;
    bool found = false;
    if ((this->pos - 1)<(-1)) return false;
    while (!shouldstop) {
      this->pos -= 1;
      this->nextpos -= 1;
      auto plats = map.at("central").at(this->pos).at("plat");
      for (auto it = plats.begin(); it != plats.end(); ++it) {
	if(*it == this->plat) {
	  shouldstop = true;
	  found = true;
	  return found;
	} else {
	  continue;
	}
      }
    }
    return found;
  }
  
  bool next(std::string plataforma = "") {
    if (this->plat == "") this->plat = plataforma;
    bool shouldstop = false;
    bool found = false;
    while (!shouldstop) {
      auto central = map.at("central");
      if (this->pos + 1 >= central.size()) return false;
      this->pos += 1;
      this->nextpos += 1;
      auto plats = map.at("central").at(this->pos).at("plat");
      for (auto it = plats.begin(); it != plats.end(); ++it) {
	// std::cout << *it << std::endl;
	if(*it == this->plat) {
	  shouldstop = true;
	  found = true;
	  // std::cout << it.value() << std::endl;
	  // std::cout << this->map.at("central").at(this->pos).at("name") << std::endl;
	  return found;
	} else {
	  continue;
	}
      }
    }
    return found;
    // std::cout << map.at("central").at(this->pos).dump(4) << std::endl;
    // std::cout << map.at("central").at(this->pos).at("plat").dump(4) << std::endl;
    
  }
};

int main() {
  std::ifstream mapfile("map.json");
  json map = json::parse(mapfile);
  Trem trem(map);
  auto plats = map.at("central");

  // if (trem.next("p2")) printf("agora: %s \n", std::string(plats.at(trem.pos).at("name")).c_str());
  // if (trem.next("p2")) printf("agora: %s \n", std::string(plats.at(trem.pos).at("name")).c_str());
  // if (trem.previous("p2")) printf("agora: %s \n", std::string(plats.at(trem.pos).at("name")).c_str());

  while(true) {
    int command;
    std::string scommand;
    printf("\n1:Quit\n2:Próximo\n3:Anterior\n4:Mudar plataforma\n\n");
    std::cin >> command;
    if (command == 1) { exit(0); }
    if (command == 2) {
      if (trem.plat == "") {
	printf("Qual plataforma deseja seguir?\n");
	std::cin >> scommand;
	if (trem.next(scommand)) {
	  printf("você está em: %s\n", std::string(plats.at(trem.pos).at("name")).c_str());
	} else {
	  printf("Não é possível seguir em frente.\n");
	}
      } else {
	if (trem.next()) {
	  printf("você está em: %s\n", std::string(plats.at(trem.pos).at("name")).c_str());
	} else {
	  printf("Não é possível seguir em frente.\n");
	}
      }
    }
    if (command == 3) {
      if (trem.plat == "") {
	printf("Qual plataforma deseja seguir?\n");
	std::cin >> scommand;
	if (trem.previous(scommand)) {
	  printf("você está em: %s\n", std::string(plats.at(trem.pos).at("name")).c_str());
	} else {
	  printf("Não é possível voltar.\n");
	}
      } else {
	if (trem.previous()) {
	  printf("você está em: %s\n", std::string(plats.at(trem.pos).at("name")).c_str());
	} else {
	  printf("Não é possível voltar.\n");
	}
      }
    }
    if (command == 4) {
      std::cin >> scommand;
      if (trem.changePlat(scommand)) {
	printf("Agora seguindo plataforma %s\n", std::string(trem.plat).c_str());
      } else {
	printf("Não é possível trocar de plataforma. Ainda em %s\n", std::string(trem.plat).c_str());
      }
    }
  }
  
  // std::cout << trem.next("p6") << std::endl;
  // trem.next("p6");
  // std::cout << trem.changePlat("p8") << std::endl;
}
