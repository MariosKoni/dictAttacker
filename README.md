# DictAttaker

Terminal based password attacker (SHA-512) written in C++.

The program is called with three arguments (though two can do the job). The first is the path to the file of the hashed passwords that you have found. The second is the path to the dictionary file you have and the last one is the mode in which the program will operate.

Mode 1 -> The program tests every hash with every word from the dictionary hashed.
Mode 2 -> The program tests every hash with every word but it varies the word by first capitalizing the first letter, secondly by capitalizing the last letter and lastly by capitalizing the first and the last as well.
Mode 3 -> The program tests every hash with every word but it first takes a random substring from the word and append it to the next word of the dictionary. Then tests this word with the hash.

Whenever it finds something, it outputs it to the screen and in a file as well.

Currently the program runs in a single thread. It will eventually run in more than one to optimize performance.

To run this program in Linux all you have to do is run the `make` command from the bin folder. For windows users things are a bit more complicated. You will need the `cl` command to compile the program, though, you will need the latest visual studio (any edition). Open the start menu and navigate to the visual studio folder and open the "Developer Command Prompt for VS". After that type `cl /W4 /EHsc dictAttacker.cpp ../core/attacker.cpp /link /out:dictAttacker.exe`. WARNING. I HAVE NOT TESTED IT IN WINDOWS OS.
