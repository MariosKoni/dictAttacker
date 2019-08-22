#pragma once

#include <string>
#include <vector>

class Attacker {
private:
  std::string pathToHash;
  std::string pathToDict;
  const std::string pathToFound = "../found/found.txt";
  unsigned short int mode;

  std::vector<std::string> dictionary;

public:
  Attacker(std::string, std::string, unsigned short int = 1);
  void loadDictionary();
  unsigned int crack();
};
