#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct LZ77Token {
    int offset;     // hamynknel skselu kety
    int length;     // erkarutyun
    char nextChar;  // hajordox smvol
};

//sexmum
std::vector<LZ77Token> compressLZ77(const std::string& input, int windowSize) {
    std::vector<LZ77Token> tokens;

    int inputSize = input.size();
    for (int i = 0; i < inputSize; ) {
        int bestOffset = 0, bestLength = 0;
        char nextChar = '\0';

        // hamynknum
        int windowStart = std::max(0, i - windowSize);
        for (int j = windowStart; j < i; ++j) {
            int matchLength = 0;
            while (j + matchLength < i && i + matchLength < inputSize &&
                   input[j + matchLength] == input[i + matchLength]) {
                ++matchLength;
            }
            if (matchLength > bestLength) {
                bestLength = matchLength;
                bestOffset = i - j;
            }
        }

        nextChar = (i + bestLength < inputSize) ? input[i + bestLength] : '\0';
        tokens.push_back({ bestOffset, bestLength, nextChar });

        i += bestLength + 1;
    }
    return tokens;
}

// decode function
std::string decompressLZ77(const std::vector<LZ77Token>& tokens) {
    std::string output;
    for (const auto& token : tokens) {
        if (token.offset > 0) {
            int startPos = output.size() - token.offset;
            for (int i = 0; i < token.length; ++i) {
                output += output[startPos + i];
            }
        }
        if (token.nextChar != '\0') {
            output += token.nextChar;
        }
    }
    return output;
}

int main() {
    std::string input = "aacaacabcabaaac";
    int windowSize = 6;

    // sexmum
    std::vector<LZ77Token> tokens = compressLZ77(input, windowSize);
    std::cout << "Сжатие (offset, length, nextChar):\n";
    for (const auto& token : tokens) {
        std::cout << "(" << token.offset << ", " << token.length << ", " << token.nextChar << ")\n";
    }

    // decode
    std::string decompressed = decompressLZ77(tokens);
    std::cout << "\nString: " << decompressed << "\n";

    return 0;
}
