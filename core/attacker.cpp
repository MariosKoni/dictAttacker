#include "attacker.hh"
#include "sha512.hh"

#include <fstream>

Attacker::Attacker(std::string ph, std::string pd, unsigned short int m) {
  pathToHash = ph;
  pathToDict = pd;
  mode = m;
}

void Attacker::loadDictionary() {
  std::ifstream input(pathToDict);
  std::string tmp;
  unsigned int i = 1;

  if (input.is_open()) {
    while (!input.eof()) {
      std::cout << "Loading word " << i << "." << std::endl;

      std::getline(input, tmp);
      dictionary.emplace_back(tmp);

      i++;
    }
  }

  getchar();
  for (auto &word: dictionary)
    std::cout << word << std::endl;

  input.close();
}

void Attacker::crack() {
  switch (mode) {
    default:
    case 1:
      std::cout << "Executing by checking with every word in the dictionary." << std::endl;

      break;
    case 2:
      std::cout << "Executed case 2." << std::endl;
      break;
  }
}
