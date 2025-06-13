# 💼 VaultX – A Secure File-Based Bank System in C++

**VaultX** is a modern console-based **Bank Management System** built with **C++** using **Object-Oriented Programming (OOP)** and **file handling**.  
It simulates core banking operations like login, registration, deposits, withdrawals, transfers, and mini statements — with all data stored securely in local files.

---

## 🔑 Key Features

- 👤 **User Registration & Login**  
  Create new accounts, securely log in, and prevent unauthorized access.

- 🔒 **Account Locking**  
  Automatically locks account after 3 failed login attempts.

- 💰 **Deposit & Withdraw**  
  Users can deposit or withdraw amounts, with updated balances.

- 🔁 **Money Transfer**  
  Easily transfer funds between registered users.

- 🧾 **Mini Statement**  
  Displays the last 3 transactions using per-user transaction history.

- 📂 **File-Based Storage**  
  All account data, balances, and transactions are stored in `.txt` files — no databases used.

- 🎨 **Stylish Console UI**  
  Enhanced user experience using emoji feedback and ASCII formatting.

---

## 🛠 Tech Stack

- **Language**: C++  
- **Concepts**: Classes, Inheritance, File I/O, Loops  
- **Libraries**: `<iostream>`, `<fstream>`, `<vector>`  
- ❌ No `<ctime>` or `<iomanip>` used

---

## 📁 Project Structure

main.cpp // Full source code
├── accounts.txt // Stores usernames, passwords, lock status
├── balances.txt // Tracks user balances
├── transactions_<user>.txt // Stores individual transaction logs
# ⚙️ How to Run

1. **Clone this repository**  
   ```bash
   git clone https://github.com/your-username/VaultX.git
   cd VaultX
   g++ main.cpp -o vaultx
./vaultx
