#ifndef BANKSYS_HPP
#define BANKSYS_HPP
#include <string>
#include <vector>
#include "transaction.hpp"
class BankTeller{
    private:
        int _id;
    public:
        BankTeller(const int& id);
        int getId() const;
};

class BankAccount{
    private:
        int _customerId;
        std::string _name;
        int _balance;

    public:
        BankAccount(const int& customerId, std::string name, int balance);
        int getBalance() const;
        void deposit(const int& amount);
        void withdraw(const int& amount);
};

class BankSystem {
    private:
        std::vector<BankAccount*> _accounts;
        std::vector<Transaction*> _transactions;

    public:
        BankSystem(std::vector<BankAccount*> accounts,
                   std::vector<Transaction*> transactions);
        BankAccount* getAccount(const int& customerId) const;
        std::vector<BankAccount*> getAccounts() const;
        std::vector<Transaction*> getTransactions() const;
        int openAccount(const std::string& customerName, const int& tellerId);
        void deposit(const int& customerId, const int& tellerId, const int amount);
        void withdraw(const int& customerId, const int& tellerId, int amount);
};

class BankBranch {
    private:
        std::string _address;
        int _cashOnHand;
        BankSystem* _bankSystem;
        std::vector<BankTeller> _tellers;

    public:
        BankBranch(const std::string& address, int cashOnHand, BankSystem* bankSystem);
        void addTeller(BankTeller teller);
        BankTeller getAvailableTeller() const;
        int openAccount(const std::string& customerName);
        void deposit(const int& customerId, int amount);
        void withdraw(const int& customerId, int amount);
        int collectCash(double ratio);
        void provideCash(int amount);
};

class Bank {
    private:
        std::vector<BankBranch> _branches;
        BankSystem* _bankSystem;
        int _totalCash;
    public:
        Bank(std::vector<BankBranch> branches, BankSystem* bankSystem, int totalCash);
        BankBranch addBranch(std::string address, int initialFunds);
        void collectCash(double ratio);
        void printTransactions() const;
};

#endif