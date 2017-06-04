#include <iostream>
#include <fstream>
#include <time.h>
#include "PasswordList.h"

using namespace std;

void check_password(string password, int hashsize = 1000) {
    // Parses the files
    PasswordList list("passwords.txt", hashsize);
    
    // Gets argument and inserts and prints validity
    bool valid = list.insert(password);
    if(valid) cout << "VALID" << endl;
    else cout << "INVALID" << endl;
}

void test_collision(string filename, int hashsize) {
    PasswordList list(filename, hashsize, true);
}

string generate_random_password() {
    int len = rand() % 8 + 8;
    string password = "";
    
    for(int i = 0; i < len; i++) {

        int r = rand() % 62;

        if(r < 26) r = r + 97;
        else if(r >= 26 && r < 52) r = r + 65 - 26;
        else r = r + 48 - 52;
        
        password += (char) r;
    }
    return password;
}

void generate_password_file(string filename, int count, int seed) {
    srand (seed);
    
    if(count > 100000) {
        cerr << "The number of passwords is too many" << endl;
        exit(1);
    }
    
    ofstream fs(filename);
    
    if(!fs) {
        cerr << "Cannot open the file " << filename << endl;
        exit(1);
    }
    
    for(int i = 0; i < count; i++) {
        string pswd = generate_random_password();
        fs << pswd << endl;
    }
    
    fs.close();
}

void usage() {
    cout << "Test Password: checkpass <password>" << endl;
    cout << "Generate Test Files checkpass -g password.txt <count> <seed>" << endl;
    cout << "Test Password with hash size: checkpass -h <count> <password>" << endl;
    cout << "Test Collisions with hash size: checkpass -t 1000 password.txt" << endl;
    exit(1);
}

int main(int argc, char** argv) {
    // Checks Command Line usage
    if(argc < 2 || argc > 5) {
        usage();
    }
    
    string s = argv[1];
    if(s == "-g") {
        if(argc != 5) usage();
        generate_password_file(argv[2], atoi(argv[3]), atoi(argv[4]));
    }
    else if (s == "-h") {
        if(argc != 4) usage();
        check_password(argv[3], atoi(argv[2]));
    }
    else if (s == "-t") {
        if(argc != 4) usage();
        test_collision(argv[3], atoi(argv[2]));
    }
    else {
        if(argc != 2) usage();
        check_password(argv[1], 1000);
    }
    
    return 0;
}

