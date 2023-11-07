#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

class BankAccount {
    int cellphone, AccNo, deposit;
    string name, surname, AccType, gender;
    char initials;

    public :
        void NewAccount();
        void AccDetails() const;
        void ModifyAccDetails();
        void DepositAmount(int);
        void WithdrawAmount(int);
        void DataReport() const;
        int ViewAccountNo() const;
        int ViewBalance() const;
        string ViewAccType() const;
};

//function declaration
void forNewAccount(); // write record in binary file
void forAccDetails(int); // display account details
void forModifyAccDetails(int); // modify record of file
void forDeleteAccount(int); // delete record of file
void forDataReport(int); // display all account details
void forDep_Withdraw(int, int); //deposit/withdraw amount

//creating account
void BankAccount::NewAccount() {
    cout << "==========================================\n" << "CREATE NEW ACCOUNT\n" << "==========================================\n";
    cout << "Enter your name : ";
    cin >> name;
    cout << "Enter your Surname : ";
    cin >> surname;
    cout << "Enter your Initials : ";
    cin >> initials;
    initials = toupper(initials);
    cout << "Enter your Gender(Male/Female) : ";
    getline(cin, gender);
    cin >> gender;
    for(int i = 0; (gender != "Male" && gender != "Female" && gender != "male" && gender != "female"); i++) {
        cout << "Invalid Gender\nEnter Your Gender(Male/Female) : ";
        cin >> gender;
    }

    cout << "Enter your Cellphone number(10 digits) : ";
    cin >> cellphone;
    for(int i = 0; (cellphone < 0600000000 || cellphone > 7999999999); i++) {
        cout << "Invalid cellphone\nEnter your Cellphone number(10 digists) : ";
        cin >> cellphone;
    }

    cout << "Account Type(Savings/Credit) : ";
    cin >> AccType;
    for(int i = 0; (AccType != "Savings" &&  AccType != "Credit" && AccType != "savings" && AccType != "credit"); i++) {
        cout << "Invalid Account Type\nEnter An Account Type(Savings or Credit) : ";
        cin >> AccType;
    }

    cout << "Enter an Account Number(10 digits), do not start with 0 : ";
    cin >> AccNo;
    for(int i = 0;(AccNo < 1 || AccNo > 999999999); i++) {
        cout << "Invalid Account Number\nEnter an Account Number(10 digits), do not start with 0 : ";
        cin >> AccNo;
    }
    system("cls"); system("clear");
    cout << "==========================================\n" << "Activating Account\n" << "==========================================\n";
    cout << "Activate your account by depositing R50+\nEnter your amount : ";
    cin >> deposit;

    for(int i = 0; deposit < 50; i++) {
        system("cls"); system("clear");
        cout << "==========================================\n" << "Activating Account\n" << "==========================================\n";
        cout << "Your account will only be activated by R50+\nTry again : ";
        cin >> deposit;
    }
    system("cls"); system("clear");
    cout << "==========================================\n" << "\tAccount Successfully Created\n" << "==========================================\n";
    cout << "\tpress enter to continue" << endl;
    cin.ignore();
    cin.get();
    //converting user input into caps.
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    transform(surname.begin(), surname.end(), surname.begin(), ::toupper);
    transform(gender.begin(), gender.end(), gender.begin(), ::toupper);
    transform(AccType.begin(), AccType.end(), AccType.begin(), ::toupper);
} //checked

void forNewAccount() {
    BankAccount acc;
    ofstream outFile;
    outFile.open("BankAccount.dat", ios::binary | ios::app);
    acc.NewAccount();
    outFile.write(reinterpret_cast<char*> (&acc), sizeof(BankAccount));
    outFile.close();
}

//Account details
void BankAccount::AccDetails() const{
    cout << "==========================================\n" << "Account Holder\n" << "==========================================\n";
    cout << "Full Names : " << surname << " " << name << endl;
    cout << "Gender : " << gender << endl;
    cout << "CellPhone no. : +27" << cellphone << endl;
    cout << "Account no. : " << AccNo << endl;
    cout << "Account Type : " << AccType << endl;
    cout << "Account Balance : R" << deposit << endl;
}

void forAccDetails(int num) {
    BankAccount acc;
    bool flag = false;
    ifstream inFile;
    inFile.open("BankAccount.dat", ios::binary);
    if(!inFile) {
        cout << "File could not be open || press any key..";
        return;
    }
    cout << "\nBalance Details\n";
    while(inFile.read(reinterpret_cast<char*> (&acc), sizeof(BankAccount))) {
        if(acc.ViewAccountNo() == num) {
            acc.AccDetails();
            flag = true;
        }
    }
    inFile.close();
    if(flag == false) {
        cout << "\nAccount Number Does Not Exist";
    }
}

void BankAccount::ModifyAccDetails() {
    cout << "==========================================\n" << "UPDATE YOUR ACCOUNT\n" << "==========================================\n";
    cout << "\nAccount no. : " << AccNo;
    cout << "Enter your New Name : ";
    cin >> name;
    cout << "Enter your New Surname : ";
    cin >> surname;
    cout << "Enter your Initials : ";
    cin >> initials;
    initials = toupper(initials);
    cout << "Enter your New Cellphone number(10 digits) : ";
    cin >> cellphone;
    for(int i = 0; (cellphone < 0600000000 || cellphone > 7999999999); i++) {
        cout << "Invalid cellphone\nEnter your Cellphone number(10 digists) : ";
        cin >> cellphone;
    }

    cout << "Account Type(Savings/Credit) : ";
    cin >> AccType;
    for(int i = 0; (AccType != "Savings" &&  AccType != "Credit" && AccType != "savings" && AccType != "credit"); i++) {
        cout << "Invalid Account Type\nEnter An Account Type(Savings or Credit) : ";
        cin >> AccType;
    }
    system("cls"); system("clear");
    cout << "==========================================\n" << "Activating New Account\n" << "==========================================\n";
    cout << "Activate your New account by depositing R50+\nEnter your amount : ";
    cin >> deposit;

    for(int i = 0; deposit < 50; i++) {
        system("cls"); system("clear");
        cout << "==========================================\n" << "Activating Account\n" << "==========================================\n";
        cout << "Your account will only be activated by R50+\nTry again : ";
        cin >> deposit;
    }/*
    system("cls"); system("clear");
    cout << "==========================================\n" << "\tNew Account Successfully Created\n" << "==========================================\n";
    cout << "\tpress enter to continue" << endl;*/
}

void forModifyAccDetails(int num) {
    bool available = false;
    BankAccount acc;
    fstream File;
    File.open("BankAccount.dat", ios::binary | ios::in | ios::out);
    if(!File) {
        cout << "File could not be open || Press any key..";
        return;
    }
    while(!File.eof() && available == false) {
        File.read(reinterpret_cast<char*> (&acc), sizeof(BankAccount));
        if(acc.ViewAccountNo() == num) {
            acc.AccDetails();
            cout << "\nEnter the new details of account" << endl;
            acc.ModifyAccDetails();
            int pos = (-1) * static_cast<int>(sizeof(BankAccount));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&acc), sizeof(BankAccount));
            system("cls"); system("clear");
            cout << "==========================================\n" << "\tNew Account Successfully Created\n" << "==========================================\n";
            cout << "\tpress enter to continue" << endl;
            available = true;
        }
    }
    File.close();
    if(available==false) {
        cout << "\nRecord Not Found";
    }
}

void forDeleteAccount(int num) {
    BankAccount acc;
    ifstream inFile;
    ofstream outFile;
    inFile.open("BankAccount.dat", ios::binary);
    if(!inFile) {
        cout << "File could not be open || Press Any Key";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while(inFile.read(reinterpret_cast<char*> (&acc), sizeof(BankAccount))) {
        if(acc.ViewAccountNo() != num) {
            outFile.write(reinterpret_cast<char*> (&acc), sizeof(BankAccount));
        }
    }
    inFile.close();
    outFile.close();
    remove("BankAccount");
    rename("Temp.dat", "BankAccount.dat");
    cout << "\nAccount Deleted..";
}

void BankAccount::DataReport() const {
    cout << AccNo << setw(10) << " " << surname << setw(10) << " " << name << setw(10) << AccType << setw(10) << deposit << endl;
}

void forDataReport(int) {
    BankAccount acc;
    ifstream inFile;
    inFile.open("BankAccount.dat", ios::binary);
    if(!inFile) {
        cout << "File could not be open || Press Any Key..";
        return;
    }
    cout << "====================================================\n" << "\tARRITHNIUS BANK ACCOUNT HOLDERS\n" << "====================================================\n";
    cout << "A/C no           Name              Type           Balance\n";
    cout << "====================================================\n";
    while(inFile.read(reinterpret_cast<char*> (&acc), sizeof(BankAccount))) {
        acc.DataReport();
    }
    inFile.close();
}

int BankAccount::ViewAccountNo() const {
    return AccNo;
}

void BankAccount::DepositAmount(int money) {
    deposit = deposit + money;
}

void BankAccount::WithdrawAmount(int money) {
    deposit = deposit - money;
}

void forDep_Withdraw(int num, int opt) {
    int amount;
    bool available = false;
    BankAccount acc;
    fstream File;
    File.open("BankAccount.dat", ios::binary | ios::in | ios::out);
    if(!File) {
        cout << "File could no be open || Press any key..";
        return;
    }
    while(!File.eof() && available == false) {
        File.read(reinterpret_cast<char*> (&acc), sizeof(BankAccount));
        if(acc.ViewAccountNo() == num) {
            acc.AccDetails();
            if(opt == 1) {
                cout << "\nDEPOSIT AMOUNT";
                cout << "\nEnter Amount To Deposit";
                cin >> amount;
                acc.DepositAmount(amount);
            }
            if(opt == 2) {
                cout << "\nTo WithDrawAmount";
                cout << "\nEnter Amount To WithDraw";
                cin >> amount;
                int balance = acc.ViewBalance() - amount;
                if((balance < 50) || (balance < 100)) {
                    cout << "Insufficient Balance";
                }
                else {
                    acc.WithdrawAmount(amount);
                }
            }
            int pos = (-1) * static_cast<int>(sizeof(acc));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&acc), sizeof(BankAccount));
            cout << "\nRecord Updated!";
            available = true;
        }
    }
    File.close();
    if(available == false) {
        cout << "\nRecord Not Found!";
    }
}

int BankAccount::ViewBalance() const {
    return deposit;
}

string BankAccount::ViewAccType() const {
    return AccType;
}

int main() {
    cout << "==========================================\n" << "\tWELCOME TO ARRITHNIUS BANK\n" << "==========================================\n";
    cout << "\tpress enter to continue" << endl;
    cin.get();
    system("cls"); system("clear");

    int var, menuopt;
    do {
        system("cls"); system("clear");
        cout << "==========================================\n" << "MAIN MENU\n" << "==========================================\n";
        cout << "1. New Account\n" << "2. Deposit Amount\n" << "3. Withdraw Amount\n" << "4. Balance\n" << "5. All Account Holder List\n" << "6. Close An Account\n" << "7. Modify An Account\n" << "8. Exit" << endl;
        cin >> menuopt;

        switch(menuopt) {
            case 1 :
                system("CLS");system("clear");
                forNewAccount();
                break;
            case 2 :
                system("CLS");system("clear");
                cout << "Enter Account Number : ";
                cin >> var;
                forDep_Withdraw(var, 1);
                break;
            case 3 :
                system("CLS");system("clear");
                cout << "Enter Account Number : ";
                cin >> var;
                forDep_Withdraw(var, 2);
                break;
            case 4 :
                system("CLS");system("clear");
                cout << "Enter Account Number : ";
                cin >> var;
                forAccDetails(var);
                break;
            case 5 :
                system("CLS");system("clear");
                forDataReport(var);
                break;
            case 6 :
                system("CLS");system("clear");
                cout << "\nEnter Account Number : ";
                cin >> var;
                forDeleteAccount(var);
                break;
            case 7 :
                system("CLS");system("clear");
                cout << "\nEnter Account Number : ";
                cin >> var;
                forModifyAccDetails(var);
                break;
            case 8 :
                system("CLS");system("clear");
                cout << "Thank You For Using Our Service.\n";
                exit(0);
                break;
            default :
                system("CLS");system("clear");
                cout << "You have chosen an incorrect option\n";
        }
    } while(menuopt != 8);

    return 0;
}
