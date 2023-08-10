#include <iostream>
#include <string>
#include "transaction.hpp"

Transaction::Transaction(const int& customerId, const int& tellerId)
    : _customerId(customerId), _tellerId(tellerId) {
    }
    
int Transaction::getCustomerId() const {
        return _customerId;
    };
    
int Transaction::getTellerId() const {
        return _tellerId;
    };
    
Deposit::Deposit(const int& customerId, const int& tellerId, double amount)
    : Transaction(customerId, tellerId), _amount(amount) {
}
std::string Deposit::getTransactionDescription() const {
    return "Teller " + std::to_string(getTellerId()) + " deposited $"
            + std::to_string(_amount) + " into account" 
            + std::to_string(getCustomerId());
};

Withdrawal::Withdrawal(const int& customerId, const int& tellerId, double amount)
    : Transaction(customerId, tellerId), _amount(amount) {
}
std::string Withdrawal::getTransactionDescription() const {
    return "Teller " + std::to_string(getTellerId()) + " withdrew $"
            + std::to_string(_amount) + " from account" 
            + std::to_string(getCustomerId());
};

OpenAccount::OpenAccount(const int& customerId, const int& tellerId)
    : Transaction(customerId, tellerId) {
}
std::string OpenAccount::getTransactionDescription() const {
    return "Teller " + std::to_string(getTellerId()) + " opened account" 
            + std::to_string(getCustomerId());
};