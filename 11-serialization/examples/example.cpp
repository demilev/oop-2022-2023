#include <fstream>
#include <string>
#include <iostream>

// Примерна програма за писане и четен във файл
int main()
{
    // std::ofstream outFile;
    std::ifstream inFile;

    // outFile.open("out.txt");
    inFile.open("out.txt");

    // outFile << "Hello World!";

    // int a;
    // inFile >> a;

    std::string input;
    std::getline(inFile, input);

    std::cout << input;

    std::getline(inFile, input);

    std::cout << input;

    // outFile.close();
    inFile.close();

    return 0;
}