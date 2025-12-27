#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int main()
{
    std::ifstream file("../data/adventofcode1-26-12-2025-data.txt");
    std::string line;
    std::vector<std::string> str_array;
    std::regex pattern(R"((\d+)-(\d+))");
    std::smatch numbers;
    long long sum = 0;

    /* Read each line into a vector */
    if (file.is_open()) {
        while (std::getline(file, line, ',')) {
            str_array.push_back(line);
        }

        file.close();
    }
    else {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    /* Check for invalid IDs */
    for (int i = 0; i < str_array.size(); i++) {
        if (std::regex_search(str_array[i], numbers, pattern)) {
            long long lower = std::stoll(numbers[1]), higher = std::stoll(numbers[2]);
            
            // Lower and higher inclusive
            while (lower <= higher) {
                std::string str_lower = std::to_string(lower);

                // Possibility of groups of digits occuring exactly twice if the number of digits is even
                if (str_lower.length() % 2 == 0) {
                    std::string first_half = str_lower.substr(0, str_lower.length()/2);
                    std::string second_half = str_lower.substr(str_lower.length()/2);

                    if (first_half == second_half) {
                        sum += lower;
                    }
                }
                lower++;
            }
        }
    }
    
    /* Display the number of 0's */
    std::cout << "The sum of all invalid IDs is: " << sum << std::endl;
    return 0;
}
