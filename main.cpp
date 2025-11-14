// file_encryptor.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

class FileEncryptor {
private:
    std::string filename;
    bool isEncrypted = false;

    bool readAll(std::vector<unsigned char>& buf, std::string& err) const {
        std::ifstream fin(filename, std::ios::binary);
        if (!fin) {
            err = "Cannot open file for reading: " + filename;
            return false;
        }
        fin.seekg(0, std::ios::end);
        std::streamsize size = fin.tellg();
        fin.seekg(0, std::ios::beg);

        buf.resize(static_cast<size_t>(size));
        if (size > 0 && !fin.read(reinterpret_cast<char*>(buf.data()), size)) {
            err = "Error while reading file: " + filename;
            return false;
        }
        return true;
    }

    bool writeAll(const std::vector<unsigned char>& buf, std::string& err) const {
        std::ofstream fout(filename, std::ios::binary | std::ios::trunc);
        if (!fout) {
            err = "Cannot open file for writing: " + filename;
            return false;
        }
        if (!buf.empty() && !fout.write(reinterpret_cast<const char*>(buf.data()), buf.size())) {
            err = "Error while writing file: " + filename;
            return false;
        }
        return true;
    }

public:
    FileEncryptor() = default;
    explicit FileEncryptor(const std::string& fname) : filename(fname) {}

    void setFileName(const std::string& fname) { filename = fname; }

    bool encrypt(int shift, std::string& err) {
        if (filename.empty()) { err = "Filename not set."; return false; }

        std::vector<unsigned char> buf;
        if (!readAll(buf, err)) return false;

        for (auto &b : buf) {
            int val = static_cast<int>(b);
            val = (val + shift) & 0xFF;
            b = static_cast<unsigned char>(val);
        }

        if (!writeAll(buf, err)) return false;

        isEncrypted = true;
        return true;
    }

    bool decrypt(int shift, std::string& err) {
        if (filename.empty()) { err = "Filename not set."; return false; }

        std::vector<unsigned char> buf;
        if (!readAll(buf, err)) return false;

        for (auto &b : buf) {
            int val = static_cast<int>(b);
            val = (val - shift) & 0xFF;
            b = static_cast<unsigned char>(val);
        }

        if (!writeAll(buf, err)) return false;

        isEncrypted = false;
        return true;
    }

    bool show(std::string& err) const {
        if (filename.empty()) { err = "Filename not set."; return false; }

        std::ifstream fin(filename, std::ios::binary);
        if (!fin) {
            err = "Cannot open file for reading: " + filename;
            return false;
        }

        char ch;
        std::cout << "\n--- File Contents ---\n\n";
        while (fin.get(ch)) {
            std::cout << ch;
        }
        std::cout << "\n\n----------------------\n\n";
        return true;
    }

    bool getEncryptedFlag() const { return isEncrypted; }
};

int readIntFromCin() {
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a number: ";
    }
    return x;
}

int main() {
    FileEncryptor fe;
    std::string err;
    std::string fname;
    int choice = 0;

    std::cout << "\n=========================================\n";
    std::cout << "   WELCOME TO FILE ENCRYPTION PROJECT\n";
    std::cout << "=========================================\n\n";

    std::cout << "Enter file name to operate on (default: sample.txt).\n";
    std::cout << "Press ENTER to use default: ";
    std::getline(std::cin, fname);

    if (fname.empty()) fname = "sample.txt";
    fe.setFileName(fname);

    const int defaultShift = 100;

    do {
        std::cout << "-----------------------------------------\n";
        std::cout << "                 MENU                    \n";
        std::cout << "-----------------------------------------\n";
        std::cout << "1. Encrypt file\n";
        std::cout << "2. Decrypt file\n";
        std::cout << "3. Show file contents\n";
        std::cout << "4. Change filename (current: " << fname << ")\n";
        std::cout << "5. Exit\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Choose an option: ";
        
        choice = readIntFromCin();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n";

        switch (choice) {
            case 1: {
                std::cout << "Enter shift value (0-255) or press ENTER for default (" 
                          << defaultShift << "): ";
                std::string line;
                std::getline(std::cin, line);
                int shift = defaultShift;

                if (!line.empty()) {
                    try { shift = std::stoi(line) & 0xFF; }
                    catch (...) { shift = defaultShift; }
                }

                if (fe.encrypt(shift, err)) {
                    std::cout << "✔ File successfully encrypted (shift = " << shift << ").\n\n";
                } else {
                    std::cout << "✘ Encryption failed: " << err << "\n\n";
                }
                break;
            }
            case 2: {
                std::cout << "Enter shift used during encryption (0-255) or press ENTER for default (" 
                          << defaultShift << "): ";
                std::string line;
                std::getline(std::cin, line);
                int shift = defaultShift;

                if (!line.empty()) {
                    try { shift = std::stoi(line) & 0xFF; }
                    catch (...) { shift = defaultShift; }
                }

                if (fe.decrypt(shift, err)) {
                    std::cout << "✔ File successfully decrypted (shift = " << shift << ").\n\n";
                } else {
                    std::cout << "✘ Decryption failed: " << err << "\n\n";
                }
                break;
            }
            case 3: {
                if (!fe.show(err)) {
                    std::cout << "✘ Show failed: " << err << "\n\n";
                }
                break;
            }
            case 4: {
                std::cout << "Enter new filename: ";
                std::getline(std::cin, fname);

                if (!fname.empty()) {
                    fe.setFileName(fname);
                    std::cout << "✔ Filename updated to: " << fname << "\n\n";
                } else {
                    std::cout << "No change made.\n\n";
                }
                break;
            }
            case 5:
                std::cout << "Exiting program...\n\n";
                break;

            default:
                std::cout << "Invalid option. Please try again.\n\n";
        }

    } while (choice != 5);

    return 0;
}
