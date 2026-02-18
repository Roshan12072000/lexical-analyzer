# 🧠 Lexical Analyzer in C

## 📌 About the Project

This project implements a **Lexical Analyzer** developed in the C programming language.
A lexical analyzer is the first phase of a compiler that scans source code and converts it into meaningful tokens.

The program reads input source code and identifies different lexical elements such as keywords, identifiers, operators, literals, and special symbols.

This project demonstrates fundamental compiler design concepts along with file handling and string processing in C.

---

## ⚙️ How It Works

The lexical analyzer processes the input file character by character and groups them into valid tokens.

### Working Flow:

1. Source code file is opened.
2. Characters are read sequentially.
3. Lexemes are identified.
4. Tokens are classified based on type.
5. Output is displayed or stored.

---

## 🔍 Tokens Identified

The analyzer can recognize:

* Keywords (int, char, if, while, etc.)
* Identifiers
* Operators
* Numeric constants
* String literals
* Special symbols

---

## 🚀 Features

* Tokenizes C source code
* Identifies keywords and identifiers
* Detects operators and symbols
* Recognizes numeric constants
* Handles whitespace and delimiters
* File-based input processing

---
## ❗ Error Detection Features

In addition to tokenization, this lexical analyzer also performs basic error detection.

### Detected Errors

* Invalid octal constants (digits greater than 7)
* Mismatched parentheses and braces
* Unrecognized symbols
* Invalid token formats

### Example

```
Input  : int x = 089;
Output : Error → Invalid octal constant
```

```
Input  : if (a > b {
Output : Error → Missing closing parenthesis
```

These validations improve source code analysis and demonstrate enhanced lexical processing capability.


## 🛠️ Technologies Used

* C Programming
* File Handling
* String Manipulation
* Token Parsing Logic
* Compiler Design Basics

---

## 📂 Project Structure

```
Lexical_Analyzer/
│
├── main.c
├── lexer.c
├── lexer.h
├── input.c
├── README.md
```

---

## ▶️ How to Compile & Run

### Compile

```
gcc main.c -o lexer
```

### Run

```
./lexer input.c
```

---

## 🖥️ Sample Output

```
Keyword      : int
Identifier   : main
Operator     : (
Operator     : )
Special Char : {
Keyword      : return
Number       : 0
Special Char : ;
Special Char : }
```

---

## 🎯 Applications

* Compiler design learning
* Programming language processing
* Code analysis tools
* Syntax highlighting systems
* Static code analyzers

---

## 📚 Learning Outcomes

* Compiler phases understanding
* Tokenization concepts
* Lexeme recognition
* File parsing techniques
* String processing in C

---

## 👨‍💻 Author

**Roshan Jameer**
GitHub: https://github.com/Roshan12072000

---

## 📜 Note

This project was developed for educational purposes to understand lexical analysis and basic compiler design principles.
