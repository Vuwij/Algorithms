#include "Password.h"

Password::Password() {}

Password::~Password() {
    delete next;
}

Password::Password(string password) {
    this->password = password;
}