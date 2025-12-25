#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int main()
{
    std::ifstream file("../data/adventofcode1-25-12-2025-data.txt");
    std::string line;
    std::vector<std::string> str_array;
    std::regex pattern(R"(\d+)");
    std::smatch number;
    int curr = 50, prev = 0, count = 0, mod = 100;

    /* Read each line into a vector */
    if (file.is_open()) {
        while (getline(file, line)) {
            str_array.push_back(line);
        }

        file.close();
    }
    else {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    
    /* Read the direction and number, then perform modular arithmetic */
    for (int i = 0; i < str_array.size(); i++) {    
        if (std::regex_search(str_array[i], number, pattern)) {
            prev = curr;

            if (str_array[i].substr(0, 1) == "L") {
                // Modular arithmetic: subtraction
                curr = ((curr % mod) - ((std::stoi(number[0]) % 100) % mod) + mod) % mod;
            }
            else if (str_array[i].substr(0, 1) == "R") {
                // Modular arithmetic: addition
                curr = ((curr % mod) + ((std::stoi(number[0]) % 100) % mod)) % mod;
            }

            // Count the number of wrap-arounds (0-crossing)
            count += (std::stoi(number[0]) / mod);

            // Count 0-crossing or 0-pointing after taking wrap-arounds into account
            if (prev != 0) {
                // Curr points at 0
                if (curr == 0) {
                    count++;
                }
                // Curr crosses 0 and points elsewhere (no-wrap around)
                else {
                    if (str_array[i].substr(0, 1) == "L" && !(curr >= 1 && curr <= prev)) {
                        count++;
                    }
                    if (str_array[i].substr(0, 1) == "R" && !(curr >= prev && curr <= mod-1)) {
                        count++;
                    }
                }
            }
        }
    }

    /* Display the number of 0's */
    std::cout << "The password is: " << count << std::endl;
    return 0;
}
