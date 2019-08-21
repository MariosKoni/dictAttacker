#pragma once

#include <string>
#include <vector>

class Attacker {
private:
  std::string pathToHash;
  std::string pathToDict;
  unsigned short int mode;

  std::vector<std::string> dictionary;

public:
  Attacker(std::string, std::string, unsigned short int);
  void loadDictionary();
  void crack();
};
