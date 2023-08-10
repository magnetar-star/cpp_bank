#include <iostream>
#include "transaction.hpp"
#include "BankSys.hpp"
#include <vector>

int main (){
    BankSystem bankSystem = BankSystem(std::vector<BankAccount*>(), std::vector<Transaction*>());
    Bank bank = Bank(std::vector<BankBranch>(), &bankSystem, 10000);

    std::string address = "123 Main St";
    std::string address2 = "456 Elm St";

    BankBranch branch1 = bank.addBranch(address, 1000);
    BankBranch branch2 = bank.addBranch(address2, 1000);

    branch1.addTeller(BankTeller(1));
    branch1.addTeller(BankTeller(2));
    branch2.addTeller(BankTeller(3));
    branch2.addTeller(BankTeller(4));

    std::string name1 = "John Doe";
    std::string name2 = "Bob Smith";
    std::string name3 = "Jane Doe";

    int customerId1 = branch1.openAccount(name1);
    int customerId2 = branch1.openAccount(name2);
    int customerId3 = branch2.openAccount(name3);

    branch1.deposit(customerId1, 100);
    branch1.deposit(customerId2, 200);
    branch2.deposit(customerId3, 300);

    branch1.withdraw(customerId1, 50);

    bank.printTransactions();

    bank.collectCash(0.5);

    return 0;
}