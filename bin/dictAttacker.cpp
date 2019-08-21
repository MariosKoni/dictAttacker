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
  unsigned int results;

  if (argc >= 3) {
    auto start = std::chrono::high_resolution_clock::now();
    
    Attacker attack(argv[1], argv[2], (unsigned short) std::strtoul(argv[3], NULL, 0));
    attack.loadDictionary();
    results = attack.crack();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsedSeconds = end - start;
    std::cout << "Cracked " << results << "." << std::endl;
    std::cout << "\nTook: " << elapsedSeconds.count() << "s." << std::endl;
  } else
      std::cout << "Execution: ./dictAttacker <hashedPasswordsPath> <dictionaryPath> <mode>" << std::endl;

  return 0;
}
