# Lab Projects Overview

This repository contains a collection of C and C++ programs developed for various lab assignments. Each program addresses specific computational and cryptographic tasks, ranging from basic algorithms to advanced encryption techniques.

---

## Table of Contents
1. [Euclidean Algorithm](#euclidean-algorithm)
2. [Modular Multiplicative Inverse](#modular-multiplicative-inverse)
3. [Merkle-Hellman Knapsack Cipher](#merkle-hellman-knapsack-cipher)
4. [Password-Protected File System](#password-protected-file-system)
5. [Code Obfuscator](#code-obfuscator)
6. [Steganography System](#steganography-system)
7. [Checksum and CRC Calculations](#checksum-and-crc-calculations)
8. [Hamming Code](#hamming-code)

---

### Euclidean Algorithm
**File:** `EuclidAlgorithm.c`  
**Description:**  
Implements the Euclidean algorithm to compute the Greatest Common Divisor (GCD) of two positive integers (1678 and 432). The algorithm uses iterative subtraction and division remainder methods to determine the GCD, which is then printed as output.

---

### Modular Multiplicative Inverse
**File:** `FindD.c`  
**Description:**  
Calculates the modular multiplicative inverse of a number `e` (11) modulo `f` (724500). The program finds the smallest positive integer `d` such that `(e * d) % f == 1` using a while loop and prints the result.

---

### Merkle-Hellman Knapsack Cipher
**File:** `Task9.c`  
**Description:**  
Implements a cryptographic system based on the Merkle-Hellman knapsack cipher. The program:  
- Encrypts and decrypts user-input strings (up to 100 characters).  
- Generates private and public key pairs using modular arithmetic.  
- Supports Cyrillic characters via Windows code page 1251.  
- Outputs intermediate values, ciphertext, and decrypted results.

---

### Password-Protected File System
**File:** `FilewithPassword.cpp`  
**Description:**  
A C++ program that provides password-protected access to files. Features include:  
- Password verification and change functionality.  
- Menu-driven interface with options to access files, change passwords, or exit.  
- Secure input handling and file operations.  
- Supports Russian text output.

---

### Code Obfuscator
**File:** `ObfuscatorCCode.cpp`  
**Description:**  
A C++ program designed to obfuscate C source code by:  
- Removing comments and unnecessary whitespace.  
- Renaming variables to obscure readability.  
- Adding random obfuscation code.  
- Preserving functionality while making the code harder to understand.

---

### Steganography System
**File:** `Stenography.c`  
**Description:**  
Implements a steganography system for hiding text within BMP images using LSB (Least Significant Bit) encoding. Features include:  
- Support for variable packing degrees (1, 2, 4, or 8 bits per byte).  
- Encoding and decoding of text from/to BMP files.  
- Error handling for file operations and size limitations.  
- Russian locale support for console output.

---

### Checksum and CRC Calculations
**Files:**  
- `Control_Sum.cpp`: Computes a simple checksum (modulo 256) for file contents.  
- `CRC.c`: Calculates CRC-16 checksum using polynomial division.  
- `CRC_SHIFT.cpp`: Computes CRC-32 checksum using shift operations.  
- `CRC8.c`: Implements CRC-8 checksum via shift-based and polynomial division methods.  

**Description:**  
These programs demonstrate various checksum and CRC algorithms for error detection in files. They support dynamic memory allocation, secure file operations, and output results in multiple formats (decimal, hexadecimal, binary, and ASCII).

---

### Hamming Code
**File:** `HammingCode.c`  
**Description:**  
Implements Hamming code for error detection and correction in text files. Features include:  
- Encoding text with added control bits.  
- Decoding to detect and correct single-bit errors.  
- Support for customizable block sizes (8, 12, 16, etc.).  
- Dynamic memory allocation and secure file handling.

---

## Usage
1. **Compilation:** Use a C/C++ compiler (e.g., GCC, Clang) to compile the programs.  
   Example: `gcc EuclidAlgorithm.c -o EuclidAlgorithm`  
2. **Execution:** Run the compiled executable.  
   Example: `./EuclidAlgorithm`  

## Notes
- Some programs require specific input files (e.g., `input.txt`, `password.txt`). Ensure these files exist in the working directory.  
- Programs with Russian text output may require Windows code page 1251 for proper display.  
