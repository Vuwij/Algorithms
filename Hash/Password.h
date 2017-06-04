#ifndef PASSWORD_H
#define	PASSWORD_H

#include <iostream>

using namespace std;

class Password {
public:
    Password(string password);
    Password();
    ~Password();
    Password* next = NULL;
    string password = "";
private:
    
};

#endif	/* PASSWORD_H */

