#include "attacker.hh"
#include "sha512.hh"

#include <fstream>
#include <cctype>
#include <regex>

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
      std::cout << "[Mode 1] Every word in the dictionary is being hashed and compared to the passwords." << std::endl;

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
    case 2: {
      const std::regex ch("[0-9].*[0-9]");
      std::cout << "[Mode 2] Every word in the dictionary is being manipulated by first capitalizing the first and then the last character." << std::endl;

      if (input.is_open()) {
        while (!input.eof()) {
          std::getline(input, tmp);
          for (auto &word: dictionary) {
            if (std::regex_match(word, ch))
              continue;
            else {
              //First capitalize the first character of each word
              word.front() = toupper(word.front());
              if (!sw::sha512::calculate(word).compare(tmp)) {
                numOfCracked++;
                std::cout << tmp << " -> " << word << std::endl;
              }
              //Then capitalize the last character of each word
              word.front() = tolower(word.front());
              word.back() = toupper(word.back());
              if (!sw::sha512::calculate(word).compare(tmp)) {
                numOfCracked++;
                std::cout << tmp << " -> " << word << std::endl;
              }
              //Finally capitalize the first and last character of each word
              word.front() = toupper(word.front());
              word.back() = toupper(word.back());
              if (!sw::sha512::calculate(word).compare(tmp)) {
                numOfCracked++;
                std::cout << tmp << " -> " << word << std::endl;
              }
            }
          }
        }
      }

      break;
    }
  }

  input.close();

  return numOfCracked;
}
