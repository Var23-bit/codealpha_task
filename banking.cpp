#include <iostream>
#include <string>
#include <vector>

class Customer {
public:
    std::string name;
    int customerID;

    Customer(std::string name, int customerID) : name(name), customerID(customerID) {}

    void displayDetails() const {
        std::cout << "Customer Name: " << name << std::endl;
        std::cout << "Customer ID: " << customerID << std::endl;
    }
};

class Account {
public:
    int accountNumber;
    double balance;
    Customer* accountHolder;

    Account(int accountNumber, double balance, Customer* accountHolder) : accountNumber(accountNumber), balance(balance), accountHolder(accountHolder) {}

    void deposit(double amount) {
        balance += amount;
        std::cout << "Deposited " << amount << " into account " << accountNumber << std::endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrawn " << amount << " from account " << accountNumber << std::endl;
        } else {
            std::cout << "Insufficient balance in account " << accountNumber << std::endl;
        }
    }

    void displayBalance() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Current Balance: " << balance << std::endl;
    }
};

class Transaction {
public:
    int transactionID;
    int accountNumber;
    std::string transactionType;
    double amount;

    Transaction(int transactionID, int accountNumber, std::string transactionType, double amount)
        : transactionID(transactionID), accountNumber(accountNumber), transactionType(transactionType), amount(amount) {}

    void displayTransaction() const {
        std::cout << "Transaction ID: " << transactionID << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Transaction Type: " << transactionType << std::endl;
        std::cout << "Amount: " << amount << std::endl;
    }
};

class Bank {
public:
    std::vector<Customer> customers;
    std::vector<Account> accounts;
    std::vector<Transaction> transactions;
    int nextCustomerID = 1001;
    int nextAccountNumber = 2001;
    int nextTransactionID = 3001;

    void createCustomer(std::string name) {
        customers.emplace_back(name, nextCustomerID++);
        std::cout << "Customer created with ID: " << customers.back().customerID << std::endl;
    }

    void createAccount(int customerID, double initialBalance) {
        Customer* customer = findCustomer(customerID);
        if (customer) {
            accounts.emplace_back(nextAccountNumber++, initialBalance, customer);
            std::cout << "Account created with number: " << accounts.back().accountNumber << std::endl;
        } else {
            std::cout << "Customer not found." << std::endl;
        }
    }

    void deposit(int accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account) {
            account->deposit(amount);
            transactions.emplace_back(nextTransactionID++, accountNumber, "Deposit", amount);
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void withdraw(int accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account) {
            account->withdraw(amount);
            transactions.emplace_back(nextTransactionID++, accountNumber, "Withdrawal", amount);
        } else {
            std::cout << "Account not found" << std::endl;
        }
    }

    void displayBalance(int accountNumber) {
        Account* account = findAccount(accountNumber);
        if (account) {
            account->displayBalance();
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void displayTransactions(int accountNumber) {
         bool found = false;
        for (const auto& transaction : transactions) {
            if (transaction.accountNumber == accountNumber) {
                transaction.displayTransaction();
                found = true;
            }
        }
         if (!found) {
            std::cout << "No transactions found for account number: " << accountNumber << std::endl;
        }
    }

private:
    Customer* findCustomer(int customerID) {
        for (auto& customer : customers) {
            if (customer.customerID == customerID) {
                return &customer;
            }
        }
        return nullptr;
    }

    Account* findAccount(int accountNumber) {
        for (auto& account : accounts) {
            if (account.accountNumber == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }
};

int main() {
    Bank bank;

    bank.createCustomer("John Doe");
    bank.createCustomer("Jane Smith");

    bank.createAccount(1001, 1000);
    bank.createAccount(1002, 500);

    bank.deposit(2001, 500);
    bank.withdraw(2002, 200);

    bank.displayBalance(2001);
    bank.displayBalance(2002);

    bank.displayTransactions(2001);
    bank.displayTransactions(2002);
    return 0;
}