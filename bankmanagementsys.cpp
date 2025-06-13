#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void printHeader(const string &title)
{
    cout << "\n========================================\n";
    cout << "        " << title << "\n";
    cout << "========================================\n";
}

class Account
{
private:
    string username, password;
    bool locked;

public:
    Account() { locked = false; }

    void registerUser()
    {
        printHeader("Register Account");
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        ofstream out("accounts.txt", ios::app);
        out << username << " " << password << " 0" << endl;
        out.close();
        ofstream bal("balances.txt", ios::app);
        bal << username << " 0" << endl;
        bal.close();
        cout << "\n✅ Account registered successfully!\n";
    }

    bool login()
    {
        string user, pass;
        int attempts = 3;
        printHeader("Login");
        cout << "Enter Username: ";
        cin >> user;

        while (attempts--)
        {
            cout << "Enter Password: ";
            cin >> pass;
            ifstream in("accounts.txt");
            string u, p;
            int lock;
            while (in >> u >> p >> lock)
            {
                if (u == user && p == pass)
                {
                    if (lock == 1)
                    {
                        cout << "\n❌ Account is locked. Contact support.\n";
                        return false;
                    }
                    username = u;
                    password = p;
                    return true;
                }
            }
            in.close();
            cout << "\n⚠️ Incorrect credentials. Attempts left: " << attempts << endl;
        }
        lockAccount(user);
        return false;
    }

    string getUsername() { return username; }

    void lockAccount(string user)
    {
        ifstream in("accounts.txt");
        ofstream out("temp.txt");
        string u, p;
        int lock;
        while (in >> u >> p >> lock)
        {
            if (u == user)
                out << u << " " << p << " 1" << endl;
            else
                out << u << " " << p << " " << lock << endl;
        }
        in.close();
        out.close();
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        cout << "\n🔒 Account locked due to failed attempts.\n";
    }
};

class FileManager
{
public:
    static float getBalance(string user)
    {
        ifstream in("balances.txt");
        string u;
        float bal;
        while (in >> u >> bal)
            if (u == user)
                return bal;
        return 0;
    }

    static void updateBalance(string user, float amount)
    {
        ifstream in("balances.txt");
        ofstream out("temp.txt");
        string u;
        float bal;
        while (in >> u >> bal)
        {
            if (u == user)
                out << u << " " << amount << endl;
            else
                out << u << " " << bal << endl;
        }
        in.close();
        out.close();
        remove("balances.txt");
        rename("temp.txt", "balances.txt");
    }

    static void recordTransaction(string user, string type, float amt)
    {
        ofstream out("transactions_" + user + ".txt", ios::app);
        out << type << " Rs." << amt << endl;
        out.close();
    }

    static void showMiniStatement(string user)
    {
        ifstream in("transactions_" + user + ".txt");
        vector<string> lines;
        string line;
        while (getline(in, line))
            lines.push_back(line);
        cout << "\n--- Mini Statement (Last 3 Transactions) ---\n";
        for (int i = max(0, (int)lines.size() - 3); i < lines.size(); i++)
            cout << lines[i] << endl;
        in.close();
    }
};

class Bank
{
private:
    string username;

public:
    Bank(string user) { username = user; }

    void deposit()
    {
        float amt;
        printHeader("Deposit Amount");
        cout << "Enter amount to deposit: ";
        cin >> amt;
        float bal = FileManager::getBalance(username);
        bal += amt;
        FileManager::updateBalance(username, bal);
        FileManager::recordTransaction(username, "Deposit", amt);
        cout << "\n💰 Deposited successfully!\n";
    }

    void withdraw()
    {
        float amt;
        printHeader("Withdraw Amount");
        cout << "Enter amount to withdraw: ";
        cin >> amt;
        float bal = FileManager::getBalance(username);
        if (amt > bal)
            cout << "\n❌ Insufficient balance!\n";
        else
        {
            bal -= amt;
            FileManager::updateBalance(username, bal);
            FileManager::recordTransaction(username, "Withdraw", amt);
            cout << "\n✅ Withdrawal successful!\n";
        }
    }

    void transfer()
    {
        string to;
        float amt;
        printHeader("Transfer Amount");
        cout << "Transfer to username: ";
        cin >> to;
        cout << "Amount: ";
        cin >> amt;
        float senderBal = FileManager::getBalance(username);
        float receiverBal = FileManager::getBalance(to);
        if (amt > senderBal)
            cout << "\n❌ Not enough balance.\n";
        else
        {
            senderBal -= amt;
            receiverBal += amt;
            FileManager::updateBalance(username, senderBal);
            FileManager::updateBalance(to, receiverBal);
            FileManager::recordTransaction(username, "Transfer to " + to, amt);
            FileManager::recordTransaction(to, "Received from " + username, amt);
            cout << "\n📤 Transfer successful.\n";
        }
    }

    void miniStatement()
    {
        printHeader("Mini Statement");
        FileManager::showMiniStatement(username);
    }
};

int main()
{
    int choice;
    string user;
    Account acc;

    while (true)
    {
        printHeader("Bank Management System");
        cout << "1. Register\n2. Login\n3. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
            acc.registerUser();
        else if (choice == 2)
        {
            if (acc.login())
            {
                user = acc.getUsername();
                Bank bank(user);
                while (true)
                {
                    printHeader("User Menu");
                    cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. Mini Statement\n5. Logout\nEnter choice: ";
                    cin >> choice;
                    if (choice == 1)
                        bank.deposit();
                    else if (choice == 2)
                        bank.withdraw();
                    else if (choice == 3)
                        bank.transfer();
                    else if (choice == 4)
                        bank.miniStatement();
                    else
                        break;
                }
            }
        }
        else
        {
            cout << "\n👋 Thank you for using our system.\n";
            break;
        }
    }
    return 0;
}
