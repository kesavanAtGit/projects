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
    writeAndRead();
    return 0;
}
