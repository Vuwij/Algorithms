#ifndef PASSWORDLIST_H
#define	PASSWORDLIST_H

#define USE_SUPER_FAST_HASH false

#include <iostream>
#include "Password.h"

using namespace std;

class PasswordList {
public:
    PasswordList(string file) : PasswordList(file, 1000) {}
    PasswordList(string file, int size) : PasswordList(file, size, false) {}
    PasswordList(string file, int size, bool collision);
    
    ~PasswordList();
    
    // Parses the file for the password
    void read(string file);
    
    // Attempt to insert the password, if an entry exists or is not valid then return false.
    // Adds the password to the file
    bool insert(string password);
    
private:
    Password* list;
    int list_size;
    string file_name;
    bool check_collisions = false;
    int collisions = 0;
    
    // String To Hash
    int string_to_hash(string s);
    
    // Checks if a password is valid
    bool is_valid(string password);
    
    // Checks if a password already exists
    bool contains(string password);
    
    // Adds a new password to the list
    bool add_to_hash(string password);
};

#endif	/* PASSWORDLIST_H */

