#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

std::string get_binary_from_hex(const std::string& hex_str) {
    std::string binary = "";

    for (char c : hex_str) {
        switch(toupper(c)) {
            case '0': binary += "0000"; break;
            case '1': binary += "0001"; break;
            case '2': binary += "0010"; break;
            case '3': binary += "0011"; break;
            case '4': binary += "0100"; break;
            case '5': binary += "0101"; break;
            case '6': binary += "0110"; break;
            case '7': binary += "0111"; break;
            case '8': binary += "1000"; break;
            case '9': binary += "1001"; break;
            case 'A': binary += "1010"; break;
            case 'B': binary += "1011"; break;
            case 'C': binary += "1100"; break;
            case 'D': binary += "1101"; break;
            case 'E': binary += "1110"; break;
            case 'F': binary += "1111"; break;
        }
    }
    return binary;
}

int part_one(const std::string& hex_str) {
    int sum = 0;
    std::string bin_str = get_binary_from_hex(hex_str);

    int i = 0;

    while (i < bin_str.size() - 7) {
        // get the packet version (3 bits)
        int packet_version = std::stoi(bin_str.substr(i, 3), nullptr, 2);
        sum += packet_version;
        i += 3; // advance pointer
        // get the packer id (3 bits)
        int packet_id = std::stoi(bin_str.substr(i, 3), nullptr, 2);
        i += 3; // advance pointer
        // packet_id != 4 -> literal packet
        if (packet_id != 4) {
            // get the length type id (1 bit)
            char length_type_id = bin_str[i];
            i++; // advance pointer
            // lenght type id can be ither 0 or 1
            if (length_type_id == '0') {
                // get the sub-packet total lenght (15 bits)
                int sub_tot_length = std::stoi(bin_str.substr(i, 15), nullptr, 2);
                i += 15; // advance pointer
            } else if (length_type_id == '1') {
                // get the sub-packet count (11 bits)
                int sub_count = std::stoi(bin_str.substr(i, 11), nullptr, 2);
                i += 11; // advance pointer
            } else {
                continue;
            }
        } else {  // packet_id == 4 -> literal packet
            while (true) {
                char cont = bin_str[i];
                if (cont == '0') {
                    i += 5;
                    break;
                } else {
                    i += 5;
                }
            }
        }
    }

    return sum;
}

int part_two(const std::string& hex_str) {
    int sum = 0;

    return sum;
}

int main() {
    std::ifstream input_file("day_16.in");

    std::string hex_str;
    std::getline(input_file, hex_str);

    // std::string hex_str = "C0015000016115A2E0802F182340";

    int part_one_sol = part_one(hex_str);
    int part_two_sol = part_two(hex_str);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
