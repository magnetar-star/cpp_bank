#include <string>
#include <vector>
#include <cmath>
#include "transaction.hpp"
#include "Banksys.hpp"

BankTeller::BankTeller(const int& id) : _id(id) {}

int BankTeller::getId() const {
    return _id;
};

BankAccount::BankAccount(const int& customerId, 
                        std::string name,
                        int balance)
    : _customerId(customerId), _name(name), _balance(balance) {}

int BankAccount::getBalance() const {
    return _balance;
};

void BankAccount::deposit(const int& amount) {
    _balance += amount;
};

void BankAccount::withdraw(const int& amount) {
    _balance -= amount;
};


BankSystem::BankSystem(std::vector<BankAccount*> accounts,
                   std::vector<Transaction*> transactions)
    : _accounts(accounts), _transactions(transactions) {}

BankAccount* BankSystem::getAccount(const int& customerId) const {
    return _accounts[customerId];
};

std::vector<BankAccount*> BankSystem::getAccounts() const {
        return _accounts;
};

std::vector<Transaction*> BankSystem::getTransactions() const {
    return _transactions;
};

int BankSystem::openAccount(const std::string& customerName, const int& tellerId)
{   
    // Create an account
    int customerId = _accounts.size();
    BankAccount* account = new BankAccount(customerId, customerName, 0);
    _accounts.push_back(account);
    // Log transaction
    OpenAccount* transaction = new OpenAccount(customerId, tellerId);
    _transactions.push_back(transaction);
    return customerId;
};

void BankSystem::deposit(const int& customerId, const int& tellerId, const int amount)
{
    BankAccount* account = this -> getAccount(customerId);
    account->deposit(amount);

    Deposit* transaction = new Deposit(customerId, tellerId, amount);
    _transactions.push_back(transaction);
};

void BankSystem::withdraw(const int& customerId, const int& tellerId, int amount)
{
    if (amount > this -> getAccount(customerId) -> getBalance()) {
        throw "Insufficient funds";
    }
    BankAccount* account = this -> getAccount(customerId);
    account -> withdraw(amount);

    Withdrawal* transaction = new Withdrawal(customerId, tellerId, amount);
    _transactions.push_back(transaction);
};

BankBranch::BankBranch(const std::string& address, int cashOnHand, BankSystem* bankSystem)
: _address(address), _cashOnHand(cashOnHand), _bankSystem(bankSystem) {}

void BankBranch::addTeller(BankTeller teller) {
    _tellers.push_back(teller);
}

BankTeller BankBranch::getAvailableTeller() const {
    if (_tellers.size() <= 0) {  
        throw "Invalid tellers length"; 
    }
    int index = (int) std::round((double) rand()) /RAND_MAX * _tellers.size();
    return _tellers[index];
}

int BankBranch::openAccount(const std::string& customerName) {
    if(_tellers.size() == 0) {
        throw "Branch does not have any tellers";
    }
    BankTeller teller = this->getAvailableTeller();
    return _bankSystem -> openAccount(customerName, teller.getId());
}

void BankBranch::deposit(const int& customerId, int amount) {
    if (_tellers.size() == 0){
         throw "Branch does not have any tellers";
    }
    BankTeller teller = this -> getAvailableTeller();
    _bankSystem -> deposit(customerId, teller.getId(), amount);
}

void BankBranch::withdraw(const int& customerId, int amount) {
    if (amount > _cashOnHand) {
        throw "Branch does not have enough cash";
    }
    if (_tellers.size() == 0) {
        throw "Branch does not have any tellers";
    }
    _cashOnHand -= amount;
    BankTeller teller = this -> getAvailableTeller();
    _bankSystem -> withdraw(customerId, teller.getId(), amount);
}

int BankBranch::collectCash(double ratio) {
    int cashtoCollect = (int) std::round(this->_cashOnHand * ratio);
    _cashOnHand -= cashtoCollect;
    return cashtoCollect;
}

void BankBranch::provideCash(int amount) {
    _cashOnHand += amount;
}

Bank::Bank(std::vector<BankBranch> branches, BankSystem* bankSystem, int totalCash)
: _branches(branches), _bankSystem(bankSystem), _totalCash(totalCash) {}

BankBranch Bank::addBranch(std::string address, int initialFunds) {
    BankBranch branch(address, initialFunds, _bankSystem);
    _branches.push_back(branch);
    return branch;
}

void Bank::collectCash(double ratio) {
    for (BankBranch branch: _branches) {
        int cashCollected = branch.collectCash(ratio);
        _totalCash += cashCollected;
    }
}

void Bank::printTransactions() const {
    for(Transaction* transaction: _bankSystem -> getTransactions()) {
        std::cout << transaction -> getTransactionDescription() << std::endl;
    }
}