#include <iostream>
#include <fstream>

void writeAndRead() {

    std::fstream file{};
    file.open("something.txt", std::ios::out);
    file << "something we need";
    file.close();

    std::string output;
    file.open("something.txt", std::ios::in);
    while(true) {
        file >> output;
        std::cout << output << " ";
        if(file.eof()) {
            break;
        }
    }
    file.close();
}

int main() {
    std::string m_username{};
    std::cin >> m_username;
    std::cout << m_username + ".txt";
    return 0;
}
