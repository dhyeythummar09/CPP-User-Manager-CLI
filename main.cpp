#include<iostream>
#include<vector>
#include<string>
#include <limits> 
using namespace std;

// Abstract User Class
class User{
protected:
    string name;
    string username;
    string password;

public:
    // User Constructor
    User(string name ,string uname,string pwd){
        this->name=name;    this->username=uname;    this->password=pwd;
    }

    // Virtual destructor for polymorphism
    virtual ~User() {} 
    // This ensures that when you call delete userPtr , the correct destructor chain is called, starting from the derived class and up to the base.

    // Getters & Setters
    string getUsername() const {
        return username;
    }

    bool checkPassword(string enteredPassword) const{
        return (password == enteredPassword);
    }

    virtual string getRole() const = 0; // pure virtual which makes User Class abstract

    string getUserInfo() const {          
        return ("Name: " + name + ", Username: " + username + ", Role: [" + getRole() + "]\n"); 
    }
};


//  Derived Class : RegularUser
class RegularUser : public User{
public:
    // RegularUser Constructor
    RegularUser(string name ,string uname,string pwd) : User(name , uname , pwd){
        cout << " Regular User Account with User Name :" << uname << " created!\n";
    }

    string getRole() const override{
        return "Regular";
    }
};


//  Derived Class : AdminUser
class AdminUser : public User{
public:
    // AdminUser Constructor
    AdminUser(string name ,string uname,string pwd) : User(name , uname , pwd){
        cout << " Admin User Account with User Name :" << uname << " created!\n";
    }

    string getRole() const override{
        return "Admin";
    }
};


class UserManager{
private:
    vector<User*> users;    // vector containing list of pointers of all users
    User* loggedInUser = nullptr;   // current Logged in user's pointer

public:
    // destructor to free memory allocated for each user
    ~UserManager() {
        for(auto u : users){
            delete u;
        }
    }

    // method to register a user
    void registerUser(bool isAdmin = false){
        string name,uname,pwd;
        cout << "Enter the Below Details --->\n";
        cout << "Name :";
        getline(cin, name);
        cout << "Username and Password must NOT contain any SPACES\n";
        cout << "Username :";
        cin >> uname;
        cout << "Password :";
        cin >> pwd;
        
        // Checking if the entered Username already exists
        for(auto u : users){
            if(u->getUsername() == uname){
                cout << "\t\tUsername already exists. Please try again using a different Username!\n\n";
                return;
            }
        }

        // Creating a new acount
        User* newUser;
        if(isAdmin)     newUser = static_cast<User*>(new AdminUser(name , uname , pwd));
        else            newUser = static_cast<User*>(new RegularUser(name , uname , pwd));
        users.push_back(newUser);

        cout << "\t\tUser registered successfully!\n\n";
    }

    // method for user login
    bool userLogin(string uname, string pwd){
        for(auto u : users){
            if((u->getUsername() == uname) && (u->checkPassword(pwd))){
                loggedInUser = u;
                cout << "\t\tWelcome, " << uname << " [" << u->getRole() << "]\n";
                return true;
            }
        }

        cout << "\t\tInvalid username or password! Please try again...\n\n";
        return false;
    }

    // method to show all users ==> accessible only by ADMINS
    void showAllUsers(){        
        if((loggedInUser == nullptr) || (loggedInUser->getRole() != "Admin")){
            cout << "\t\tAccess Denied. Admins only.\n\n";
            return;
        }

        cout << "\t\t------- All Users --------\n";
        for (auto u : users) {
            cout << "\t\t" << u->getUsername() << " [" << u->getRole() << "]\n";
        }
        cout << "\t------------------------------\n\n";
    }

    // method to delete user ==> accessible only by ADMINS
    void deleteUser(string uname){
        if((loggedInUser == nullptr) || (loggedInUser->getRole() != "Admin")){
            cout << "\t\tAccess Denied. Admins only.\n\n";
            return;
        }

        for (auto it = users.begin(); it != users.end(); ++it) {
            if ((*it)->getUsername() == uname) {
                delete *it;
                users.erase(it);
                cout << "\t\tUser deleted successfully.\n\n";
                return;
            }
        }

        cout << "\t\tUser not found!\n";
    }

    void userLogout(){
        if(loggedInUser == nullptr){
            cout << "Error! No user currently logged in....\n\n ";
            return;
        }

        cout << "Successfully logged out from Account : " << loggedInUser->getUsername() << "!!\n\n";
        loggedInUser = nullptr;
    }

    void getLoggedInUser() const{
        if(loggedInUser == nullptr){
            cout << "Error! No user currently logged in....\n\n ";
            return;
        }

        cout << "\t\tLogged in User : \n";
        cout << loggedInUser->getUserInfo();
        cout << "\n\n";
    }
};


int main()
{
    UserManager manager;
    char choice = 'Y';
    while(choice == 'y' || choice == 'Y'){
        system("cls");
        int op;
        cout << "\n========== USER MANAGER ==========\n";
        cout  << "Choose an option: \n";
        cout << "1. Register Regular User\n";
        cout << "2. Register Admin User\n";
        cout << "3. Login\n";
        cout << "4. Show All Users (Admin only)\n";
        cout << "5. Delete User (Admin only)\n";
        cout << "6. Current Logged-in User\n";
        cout << "7. Logout\n";
        cout << "0. Exit\n";
        cout << "====================================\n";
        cin >> op;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(op){
            case 0: {
                return 0;
            }    

            case 1:   // register regular
                manager.registerUser(false);
                break;

            case 2:   // register admin
                manager.registerUser(true);
                break;

            case 3: { // login
                string uname, pwd;
                cout << "Username: ";
                cin >> uname;
                cout << "Password: ";
                cin >> pwd;
                manager.userLogin(uname, pwd);
                break;
            }

            case 4: {   // show all users 
                manager.showAllUsers();
                break;
            }    

            case 5: { // delete user
                string uname;
                cout << "Username to delete: ";
                cin >> uname;
                manager.deleteUser(uname);
                break;
            }
            case 6:
                manager.getLoggedInUser();
                break;

            case 7:
                manager.userLogout();
                break;

            default:
                cout << "Invalid option. Try again.\n\n";
        }
        cout << "Do You Want to Continue [Y/N]? : ";
        cin>>choice;
    }
    return 0;
}