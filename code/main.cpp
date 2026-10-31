#include <iostream>
#include <string>
#include <windows.h>

extern "C" void __cdecl MakePalindrome(
    const char* source, char* result, int length);

int main() {
    SetConsoleCP(866);
    SetConsoleOutputCP(866);

    const int MAX_LENGTH = 255;
    std::string source;
    char result[2 * MAX_LENGTH + 1];

    std::cout << "Enter a string (max 255 characters): ";
    if (!std::getline(std::cin, source)) {
        std::cerr << "Error: input failed.\n";
        return 1;
    }
    if (source.size() > MAX_LENGTH) {
        std::cerr << "Error: string is longer than 255 characters.\n";
        return 1;
    }

    MakePalindrome(source.c_str(), result, static_cast<int>(source.size()));
    std::cout << "Palindrome: " << result << '\n';
    return 0;
}
