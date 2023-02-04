#include <iostream>
#include <string>
#include <fstream>
#include "./json/single_include/nlohmann/json.hpp"

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

  std::string choosePlataform() {
    int plataform = 2;
    printf("Escolha uma plataforma digitando apenas o número. (2, 6, 8, 11, 12)\n");
    std::cin >> plataform;
    while (true) {
      if (plataform == 2 || plataform == 6 || plataform == 8 || plataform == 11 || plataform == 12) {
	this->plat = std::string("p") + std::to_string(plataform);
	return this->plat;
      } else {
	printf("plataforma inválida.\n");
	continue;
      }
    }
  }
  
  bool changePlat(std::string plataforma) {
    bool canChange = false;
    if (this->plat == "") this->plat = plataforma;
    if (this->plat == "" && plataforma == "") this->plat = this->choosePlataform();
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
    return canChange;
    
    return canChange;
  }

  bool previous(std::string plataforma = "") {
    if (this->plat == "") this->plat = plataforma;
    if (this->plat == "" && plataforma == "") this->plat = this->choosePlataform();
    if ((this->pos - 1) <= -1) return false;
    auto central = map.at("central");
    bool found = false;
    int headpos = this->pos;
    int headnext = this->nextpos;
    while (!found) {
      headpos -= 1;
      headnext -= 1;
      auto plats = map.at("central").at(headpos).at("plat");
      for (auto it = plats.begin(); it != plats.end(); ++it) {
	if(*it == this->plat) {
	  found = true;
	  this->pos = headpos;
	  this->nextpos = headnext;
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
    if (this->plat == "" && plataforma == "") this->plat = this->choosePlataform();
    bool found = false;
    int headpos = this->pos;
    while (!found) {
      auto central = map.at("central");
      if ((headpos + 1) >= central.size()) return false;
      headpos += 1;
      // this->nextpos += 1;
      auto plats = map.at("central").at(headpos).at("plat");
      auto nextplats = map.at("central").at(headpos).at("plat");
      for (auto it = plats.begin(); it != plats.end(); ++it) {
	if(*it == this->plat) {
	  found = true;
	  this->pos = headpos;
	  return found;
	} else {
	  continue;
	}
      }
    }
    return found;  
  }
};

int main() {
  std::ifstream mapfile("map.json");
  json map = json::parse(mapfile);
  Trem trem(map);
  auto plats = map.at("central");
  bool showIdPos = true;
  // std::cout << plats.size() << std::endl;
  
  while(true) {
    if (showIdPos) printf("posição atual: %d", trem.pos);
    int command;
    std::string scommand;
    printf("\n1:Quit\n2:Próximo\n3:Anterior\n4:Mudar plataforma\n5:On/Off Mostrar posição atual.\n\n");
    std::cin >> command;
    if (command == 1) { exit(0); }
    if (command == 2) {
      if (trem.plat == "") {
	trem.choosePlataform();
	if (trem.next(trem.plat)) {
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
	trem.choosePlataform();
	if (trem.previous(trem.plat)) {
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
      int plataform = 0;
      std::string plataforms = "";
      printf("Escolha uma plataforma digitando apenas o número. (2, 6, 8, 11, 12)\n");
      std::cin >> plataform;
      bool valid = false;
      while (!valid) {
	if (plataform == 2 || plataform == 6 || plataform == 8 || plataform == 11 || plataform == 12) {
	  valid = true;
	} else {
	  printf("plataforma inválida.\n");
	}
      }
      plataforms = std::string("p") + std::to_string(plataform);
      if (trem.changePlat(plataforms)) {
	printf("Agora seguindo plataforma %s\n", std::string(trem.plat).c_str());
      } else {
	printf("Não é possível trocar de plataforma. Ainda em %s\n", std::string(trem.plat).c_str());
      }
    }
    if (command == 5) {
      showIdPos = (!showIdPos);
      if (showIdPos) printf("Mostrando posição.\n");
      if (!showIdPos) printf("Escondendo posição.\n");
    }
  }
  
  // std::cout << trem.next("p6") << std::endl;
  // trem.next("p6");
  // std::cout << trem.changePlat("p8") << std::endl;
}
