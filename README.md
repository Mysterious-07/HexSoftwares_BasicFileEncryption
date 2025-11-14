# HexSoftwares_BasicFileEncryption
This is a beginner friendly Basic File Encryption / Decryption Project in C++ !!

____________________________________________________________________________________________________________

🔐 File Encryption & Decryption (C++)

A simple and beginner-friendly C++ project that encrypts and decrypts text files using a Caesar-shift–based technique.
This project was built as part of Task-1 at HexSoftware.

____________________________________________________________________________________________________________

📌 Features

✔ Encrypt any text file

✔ Decrypt the encrypted file

✔ Display file content

✔ Uses simple character-shifting logic

✔ Demonstrates file handling using fstream

____________________________________________________________________________________________________________

🧠 How Encryption Works

Every character in the file is shifted by +100 ASCII values during encryption.
During decryption, each character is shifted back by –100 ASCII values, restoring the original file.

This makes the logic simple and easy to understand for beginners.

____________________________________________________________________________________________________________


📁 Project Structure

📦 File-Encryption-Project

│── main.cpp

│── sample.txt

│── README.md

____________________________________________________________________________________________________________

🚀 How to Run the Program

1️⃣ Clone the repository
git clone https://github.com/Mysterious-07/HexSoftwares_BasicFileEncryption.git

2️⃣ Navigate to the project folder
cd BasicFileEncryption-Project

3️⃣ Compile the program
g++ main.cpp -o encryption

4️⃣ Run the executable
./encryption

____________________________________________________________________________________________________________

🧾 Code Snippet (Encryption Logic)

while (fin >> noskipws >> ch){

    ch = ch + 100;   // Encryption shift
    fout << ch;
}

____________________________________________________________________________________________________________

📸 Sample Menu Output
WELCOME TO FILE ENCRYPTION PROJECT

Press 1 to encrypt file
Press 2 to decrypt file
Press 3 to show file
Press 4 to exit
Please choose any option:

____________________________________________________________________________________________________________

🛠️ Requirements

C++ compiler (GCC, Clang, MSVC, etc.)

____________________________________________________________________________________________________________

🌟 Future Improvements

Add password-based encryption

Let users choose file names dynamically

Use advanced encryption algorithms (AES, XOR, etc.)

Add GUI version

____________________________________________________________________________________________________________

🤝 Contributing

Feel free to open issues or submit pull requests if you’d like to contribute!

____________________________________________________________________________________________________________

📬 Contact

Harsh Kharwar
GitHub: your username
LinkedIn: your profile link
