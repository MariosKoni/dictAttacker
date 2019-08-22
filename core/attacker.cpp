#include "attacker.hh"
#include "sha512.hh"

#include <fstream>
#include <cctype>
#include <regex>
#include <ctime>
#include <cstdlib>
#include <algorithm>

//Constructor that assigns the arguments given by the user to the class object
Attacker::Attacker(std::string ph, std::string pd, unsigned short int m) {
  pathToHash = ph;
  pathToDict = pd;
  mode = m;
}

//Method that opens the dictionary file and loads everything into a vector of strings
//It doesn't take arguments and doesn't return anything
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

//Main method of the program that devides into three segments and trys to crack the passwords
//It takes no arguments and retunrs the number of cracked passwords. It also writes the passords
//that it has cracked into a file as well.
unsigned int Attacker::crack() {
  std::ifstream input(pathToHash);
  std::ofstream output(pathToFound);
  std::string tmp;
  unsigned int numOfCracked = 0;

  switch (mode) {
    default:
    case 1:
      std::cout << "[Mode 1] Every word in the dictionary is being compared to the passwords." << std::endl;

      if (input.is_open() && output.is_open()) {
        while (!input.eof()) {
          std::getline(input, tmp);
          for (auto &word: dictionary) {
            if (word.empty())
              continue;
            if (!sw::sha512::calculate(word).compare(tmp)) {
              numOfCracked++;
              std::cout << tmp << " -> " << word << std::endl;
              output << tmp << " -> " << word << std::endl;
            }
          }
        }
      }

      break;
    case 2: {
      const std::regex ch("[0-9].*[0-9]");
      std::cout << "[Mode 2] Every word in the dictionary is being manipulated by first capitalizing the first and then the last character and at last the two together." << std::endl;

      if (input.is_open() && output.is_open()) {
        while (!input.eof()) {
          std::getline(input, tmp);
          for (auto &word: dictionary) {

            if (word.empty())
              continue;

            if (std::regex_match(word, ch) && (!std::isalpha(word.front()) || !std::isalpha(word.back())))
              continue;
            else {
              //First capitalize the first character of each word
              word.front() = toupper(word.front());
              if (!sw::sha512::calculate(word).compare(tmp)) {
                numOfCracked++;
                std::cout << tmp << " -> " << word << std::endl;
                output << tmp << " -> " << word << std::endl;
                continue;
              }
              //Then capitalize the last character of each word
              word.front() = tolower(word.front());
              word.back() = toupper(word.back());
              if (!sw::sha512::calculate(word).compare(tmp)) {
                numOfCracked++;
                std::cout << tmp << " -> " << word << std::endl;
                output << tmp << " -> " << word << std::endl;
                continue;
              }
              //Finally capitalize the first and last character of each word
              word.front() = toupper(word.front());
              word.back() = toupper(word.back());
              if (!sw::sha512::calculate(word).compare(tmp)) {
                numOfCracked++;
                std::cout << tmp << " -> " << word << std::endl;
                output << tmp << " -> " << word << std::endl;
                continue;
              }
            }
          }
        }
      }

      break;
    }

    case 3: {
      unsigned short int offset1, offset2;
      std::string copy;

      std::cout << "[Mode 3] Random substrings will be appended randomly to the next word of the dictionary and then compared to the password." << std::endl;

      srand(time(NULL));
      if (input.is_open() && output.is_open()) {
        while (!input.eof()) {
          std::getline(input, tmp);
          for (std::size_t i = 0; i < dictionary.size(); ++i) {

            if (dictionary[i].empty())
              continue;

            do {
              offset1 = rand() % dictionary[i].size();
              offset2 = rand() % dictionary[i].size();
            } while (offset1 == offset2);

            if (!(offset1 < offset2))
              std::swap(offset1, offset2);

            std::string random = dictionary[i].substr(offset1, offset2);
            if (&dictionary[i] != &dictionary.back()) {
              copy = dictionary[i + 1];
              dictionary[i + 1] += random;
            } else
                break;
            if (!sw::sha512::calculate(dictionary[i + 1]).compare(tmp)) {
              numOfCracked++;
              std::cout << tmp << " -> " << dictionary[i + 1] << std::endl;
              output << tmp << " -> " << dictionary[i + 1] << std::endl;
            }
            dictionary[i + 1] = copy;
          }
        }
      }

      break;
    }
  }

  input.close();
  output.close();

  return numOfCracked;
}
