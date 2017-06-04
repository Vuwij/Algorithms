#include <fstream>
#include <sstream>
#include <string>

#define HASH_MULT 0.6180339885

#include "PasswordList.h"
#include "superfasthash.h"

PasswordList::PasswordList(string file, int size, bool collision) {
    list = new Password[size];
    list_size = size;
    check_collisions = collision;
    read(file);
}

PasswordList::~PasswordList() {
    delete[] list;
}

void PasswordList::read(string file) {
    file_name = file;
    
    ifstream data_file(file, std::ifstream::in);
    if (!data_file.is_open()) 
        cout << "Could not open file: " << file << endl;

    string line;
    
    while (getline(data_file, line)) {
        add_to_hash(line);
    }
    
    if(check_collisions)
        cout << collisions << endl;
    
    data_file.close();   
}

bool PasswordList::add_to_hash(string password) {
    // Checks if it is valid
    if(!is_valid(password)) return false;
    
    // Check if it already exists
    if(contains(password)) return false;
    
    // Invert the password and check if it exists
    string inverse = password;
    for(int i = 0; i < inverse.length() / 2; i++) {
        char c = inverse[i];
        inverse[i] = inverse[inverse.length() - i - 1];
        inverse[inverse.length() - i - 1] = c;
    }
    if(contains(inverse)) return false;
    
    // Get the hash value for the string
    int hash = string_to_hash(password);
    
    Password* p = &list[hash];
    if(p->password == "") {
        p->password = password;
        return true;
    }
    
    // Move to the end of the linked list
    while(p->next != NULL) p = p->next;
    p->next = new Password(password);
    collisions++;
    
    return true;
}

bool PasswordList::insert(string password) {
    if(add_to_hash(password) == false) return false;
    
    // Add to the file
    ofstream out;
    out.open(file_name, ios::app);
    out << endl;
    out << password;
    
    return true;
}

// Uses the Multiplication Method
int PasswordList::string_to_hash(string s) {
    if(USE_SUPER_FAST_HASH)
        return (int) (::hash(s.c_str(), s.length()) / 2) % list_size;
    else {
        unsigned long hash = 5381;
        int tmp;
        
        for(int i = 0; i < s.length() - 2; i++) {
            hash = ((hash << 5) + hash) + s[i];
        }
        return hash % list_size;
    }
}

bool PasswordList::is_valid(string password) {
    int length = password.length();
    
    // Too Short
    if(length < 6) return false;
    
    // Too Long
    if(length > 12) return false;
    
    // Contains invalid characters
    for(int i = 0; i < length; i++) {
        char c = password[i];
        if(c < 48) return false;
        if(c > 57 && c < 65) return false;
        if(c > 91 && c < 97) return false;
        if(c > 123) return false;
    }
    
    return true;
}

bool PasswordList::contains(string password) {
    int hash = string_to_hash(password);
    Password* p = &list[hash];
    if(p->password == "") return false;
    
    if(p->password == password) return true;
    while((p = p->next) != NULL) {
        if(p->password == password) return true;
    }
    
    return false;
}