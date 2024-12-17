#include <iostream>
using namespace std;

class CaesarCipher {
private:
    int shift; 
public:
    CaesarCipher(int s) : shift(s) {}

    string encrypt(const string& text) {
        string result = "";
        for (int i = 0; i < text.length(); i++) {
            char c = text[i];
            if (isupper(c)) {
                result += char(int(c + shift - 65) % 26 + 65);
            } else if (islower(c)) {
                result += char(int(c + shift - 97) % 26 + 97);
            } else {
                result += c;
            }
        }
        return result;
    }

    string decrypt(const string& text) {
        string result = "";
        for (int i = 0; i < text.length(); i++) {
            char c = text[i];
            if (isupper(c)) {
                result += char(int(c - shift - 65 + 26) % 26 + 65); 
            } else if (islower(c)) {
                result += char(int(c - shift - 97 + 26) % 26 + 97); 
            } else {
                result += c;
            }
        }
        return result;
    }
};

class RLE {
private:
    string input;

public:
    RLE(const string& str) : input(str) {}

    string encode() {
        string encoded = "";
        int n = input.length();
        for (int i = 0; i < n; i++) {
            int count = 1;
            while (i < n - 1 && input[i] == input[i + 1]) {
                count++;
                i++;
            }
            encoded += input[i];
            encoded += static_cast<char>(count + '0');
        }
        return encoded;
    }

    string decode(const string& encoded) {
        string decoded = "";
        int n = encoded.length();
        for (int i = 0; i < n; i++) {
            char currentChar = encoded[i];
            i++;
            int count = encoded[i] - '0';
            decoded.append(count, currentChar);
        }
        return decoded;
    }

    string getInput() const {
        return input;
    }
};

class Mix : public RLE, public CaesarCipher {
private:
    string str;

public:
    Mix(const string& str, int shift) : RLE(str), CaesarCipher(shift), str(str) {}

    string encodeMix() {
        string rleEncoded = encode();      
        return encrypt(rleEncoded);        
    }

    string decodeMix(const string& encodedText) {
        string decrypted = decrypt(encodedText); 
        return decode(decrypted);               
    }
};

int main() {
    string text = "AAABBBCCDAA";
    int shift = 3;

    Mix mix(text, shift);
    string encoded = mix.encodeMix();
    cout << "Encoded: " << encoded << endl;

    string decoded = mix.decodeMix(encoded);
    cout << "Decoded: " << decoded << endl;

    return 0;
}
