/**
 * @file main.cpp
 * @author Rose Richards (rose.evelyn5550@gmail.com)
 * @brief A test system for registering an account & logging in.
 *
 * @version 0.1
 * @date 2026-10-26
 * 
 * @copyright Copyright (c) 2026
 * 
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sys/stat.h>

/**
 * @brief Allows the user to create an account
 * 
 */
void createAccount();

/**
 * @brief Allows the user to login
 * 
 */
void login();

/**
 * @brief Encrypts the data
 * 
 * @param seed Seed derived from password
 * @param timestamp Timestamp grabbed at time of creation
 * @return int Encrypted data
 */
int encrypt(std::string seed, time_t &timestamp);


int main(){
    int prompt;
    std::cout << "1.Login - 2.Create an Account \n> ";
    std::cin >> prompt;
    if (prompt == 1) login();
    else if (prompt == 2) createAccount();
    else std::cout << "Invalid command." << std::endl;
    return 0;
}

int encrypt(std::string seed, time_t &timestamp){
    int end = 0;
    int temp = 0;
    for (int i = 0; i < seed.length(); i++){
        temp = (seed[i] - '0')* timestamp;
        end = end + temp;
    }
    return end;
} 

void createAccount(){
    std::string tempName;
    std::string tempPass;
    time_t timestamp;
    time(&timestamp);

    std::cout << "Enter a username: ";
    std::cin >> tempName;
    std::cout << "Enter a password: ";
    std::cin >> tempPass;
    
    int pass = encrypt(tempPass, timestamp);

    std::string fileName = "/workspaces/login-registration-system/mockDB/" + tempName + ".txt";

    std::ofstream MyFile(fileName);
   //MyFile << std::fixed;
    MyFile << tempName << std::endl;
    MyFile << pass << std::endl;
    MyFile << timestamp << std::endl;

    pass = 0;
    tempName.clear();
    tempPass.clear();
    time(&timestamp);
    MyFile.close();
    return;
}

void login(){
    std::string tempUser, tempPass, fileUser= "";
    int filePass, fileEncrypt;

    std::cout << "Username: ";
    std::cin >> tempUser;
    std::cout << "Password: ";
    std::cin >> tempPass;

    std::string path = "/workspaces/login-registration-system/mockDB/" + tempUser + ".txt";
    std::ifstream file;
    file.open(path);
    
    if (!file.is_open()) {
        std::cout << "Username or Password are incorrect";
        path.clear();
        tempUser.clear();
        tempPass.clear();
    }
    getline(file, fileUser);
    

    file.close();
    path.clear();
    tempUser.clear();
    tempPass.clear();
    return;
}