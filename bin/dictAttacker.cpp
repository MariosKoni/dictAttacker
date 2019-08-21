#include "../core/attacker.hh"

#include <iostream>
#include <string>
#include <chrono>

/*
            ARGUMENTS
1. Path to the hashed passwords
2. Path to the dictionary that will be used
3. Mode that the program will use
*/

int main(int argc, char const *argv[]) {
  auto start = std::chrono::high_resolution_clock::now();

  if (argc >= 3) {
    Attacker attack(argv[1], argv[2], (unsigned short) std::strtoul(argv[3], NULL, 0));
    attack.loadDictionary();
    attack.crack();
  } else
      std::cout << "Execution: ./dictAttacker <hashedPasswordsPath> <dictionaryPath> <mode>" << std::endl;

  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsedSeconds = end - start;
  std::cout << "\nTook: " << elapsedSeconds.count() << "s." << std::endl;
  return 0;
}