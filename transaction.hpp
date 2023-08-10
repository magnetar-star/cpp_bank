#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>

class Transaction {
    private:
        int _customerId;
        int _tellerId;

    public:
        Transaction(const int& customerId, const int& tellerId);
        int getCustomerId() const;
        int getTellerId() const;
        virtual std::string getTransactionDescription() const = 0;
};

class Deposit : public Transaction {
    private:
        double _amount;
    public:
        Deposit(const int& customerId, const int& tellerId, double amount);
        double getAmount() const;
        std::string getTransactionDescription() const override;
};

class Withdrawal: public Transaction {
    private:
        double _amount;
    public:
        Withdrawal(const int& customerId, const int& tellerId, double amount);
        double getAmount() const;
        std::string getTransactionDescription() const override;
};

class OpenAccount : public Transaction {
    public:
        OpenAccount(const int& customerId, const int& tellerId);
        std::string getTransactionDescription() const override;
};

#endif