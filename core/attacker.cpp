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

  if (input.is_open()) {
    std::cout << "Dictionary is being loaded. This may take a while...";
    while (!input.eof()) {

      std::getline(input, tmp);
      dictionary.emplace_back(tmp);
    }
  }
  std::cout << "OK" << std::endl;

  input.close();
}

unsigned int Attacker::crack() {
  std::ifstream input(pathToHash);
  std::string tmp;
  unsigned int numOfCracked = 0;

  switch (mode) {
    default:
    case 1:
      std::cout << "Executing by checking with every word in the dictionary." << std::endl;

      if (input.is_open()) {
        while (!input.eof()) {
          std::getline(input, tmp);
          for (auto &word: dictionary) {
            if (!sw::sha512::calculate(word).compare(tmp)) {
              numOfCracked++;
              std::cout << tmp << " -> " << word << std::endl;
            }
          }
        }
      }
      break;
    case 2:
      std::cout << "Executed case 2." << std::endl;
      break;
  }

  input.close();

  return numOfCracked;
}
