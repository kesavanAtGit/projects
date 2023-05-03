#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

class Register {
    protected:
        std::string m_username{};
        std::string m_password{};
        std::string m_copyUsername{};
        std::fstream file{};
        int m_isSignedUp{};

    public:
        bool isSignedUp() {
            if(m_username == m_copyUsername) {
                std::cout << "Username already exists! Try a different username :( \n";
                return true;
            }
            return false;
        }

        void signUp() {

            std::cout << "Enter your username: ";
            std::cin >> m_username;

            file.open(m_username + ".txt", std::ios::out);
            if(!file) {
                std::cerr << "Cannot open the file for signing up daddy. \n";
            }
            else {
                //std::cout << "Enter your username: ";
                //std::cin >> m_username;

                // return early if the same username is used again to register
                if(isSignedUp()) {
                    file.close();
                    signUp();
                }else {
                    m_copyUsername = m_username;
                    std::cout << "Enter your password: ";
                    std::cin >> m_password;

                    file << m_username << '\n' << m_password;
                    std::cout << "Sign up successful! \n";
                    std::cout << "Username: " << m_username << '\n' << "Password: " << m_password << '\n';

                    ++m_isSignedUp;
                    std::cout << '\n';
                }
            }
            file.close();
        }

        std::string* getUsername() {return &m_username;}
        int& getSignUps() {return m_isSignedUp;}
};

class Login : public Register {
    private:
        std::string m_readUsername{};
        std::string m_readPassword{};
        std::string m_username{};
        std::string m_password{};
        std::string* m_ptr{getUsername()};
        int m_preLogin{};

    public:

        // what if the user tries to login when he doesn't even have an account?
        bool canLogin() {
            file.open(m_username + ".txt", std::ios::in);
            std::getline(file, m_readUsername);
            std::getline(file, m_readPassword);
            file.close();

            if(m_username == m_readUsername) {
                return true;
            }
            return false;
        }

        void login() {
            std::cout << "Username: ";
            std::cin >> m_username;

            std::cout << "Password: ";
            std::cin >> m_password;

            // avoid the canLogin() function ever after preLogin becomes 1
            if(m_preLogin == 1 || getSignUps() > 0) {
                *m_ptr = m_username;
            }

            if(!canLogin()) {
                std::cout << "You don't have an account named " << m_username << ". Sign up first! \n";
                signUp();
            }else {
                file.open(m_username + ".txt", std::ios::in);
                if(!file) {
                    std::cerr << "Can't open the file goddamn it! \n";
                } else {
                    //std::getline(file, m_readUsername);
                    //std::getline(file, m_readPassword);

                    if(m_username == m_readUsername && m_password == m_readPassword) {
                        std::cout << "You logged in successfully! \n"; std::cout << '\n';
                    }else if(m_username == m_readUsername && m_password != m_readPassword) {
                        std::cerr << "Invalid password{:?} Check your password! \n";
                        std::cout << '\n';
                    }else if(m_username != m_readUsername && m_password == m_readPassword) {
                        std::cerr << "Invalid username{:?} Check your username! \n";
                        std::cout << '\n';
                    }else {
                        std::cerr << "Check your username and password and try again! \n";
                        std::cout << '\n';
                    }
                }
            }
            file.close();
        }
};

int main() {
    std::cout << "-------------------------------------------------Welcome to our system!----- \n";
    Register signUp{};
    Login login{};

    while(true) {
        std::cout << "Choose one option: \n";
        std::cout << "1. SignIn/Login (press 1 to select this) \n";
        std::cout << "2. SignUp/Register (press 2 to select this) \n";
        std::cout << "Press any key and enter to exit \n";
        int input{};
        std::cin >> input;

        if(input == 2)
            signUp.signUp();
        else if(input == 1)
            login.login();
        else {
            std::cout << "Sayonara :)! \n";
            break;
        }
    }

    return 0;
}
