#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // For formatting output
#include <unordered_map>

using namespace std;

// Structure to represent a product
struct Product {
    string productCode;
    string name;
    string description;
    string location;
    string deliveryOption;
    int quantity;
    double price;
    double discount;
};

// Base class for users
class User {
protected:
    string name;
    string username;
    string password;
    string securityWord;

public:
    User(string name, string username, string password, string securityWord) : name(name), username(username), password(password), securityWord(securityWord) {}

    // Getter methods
    string getName() const { return name; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getSecurityWord() const { return securityWord; }
};

// Class for Product Owners
class ProductOwner : public User {
private:
    vector<Product> products;

public:
    ProductOwner(string name, string username, string password, string securityWord) : User(name, username, password, securityWord) {
        loadProductsFromFile();
    }

    void productOwnerMenu() {
        int choice;

        while (true) {
            cout << "\n\t\t\t Product Owner (Producer) Menu";
            cout << "\n\t\t\t________________________________________\n";
            cout << "\n\t\t\t|\t 1. Add The Product   \t\t|";
            cout << "\n\t\t\t|\t 2. Modify The Product\t\t|";
            cout << "\n\t\t\t|\t 3. Delete The Product\t\t|";
            cout << "\n\t\t\t|\t 4. List The Product  \t\t|";
            cout << "\n\t\t\t|\t 5. Back To Main Menu \t\t|";
            cout << "\n\t\t\t________________________________________";

            cout << "\n\n\t Please enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addProduct();
                    break;
                case 2: {
                    string productCode;
                    cout << "Enter product code to update: ";
                    cin >> productCode;
                    updateProduct(productCode);
                    break;
                }
                case 3: {
                    string productCode;
                    cout << "Enter product code to remove: ";
                    cin >> productCode;
                    removeProduct(productCode);
                    break;
                }
                case 4:
                    listProducts();
                    break;
                case 5:
                    return; // Return to the main menu
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

    // Product management methods
    void addProduct();
    void updateProduct(const string& productCode);
    void removeProduct(const string& productCode);
    void listProducts() const;

    // Load products from file
    void loadProductsFromFile();
    void saveProductsToFile();
};

// Class for Buyers
class Buyer : public User {
public:
    Buyer(string name, string username, string password, string securityWord) : User(name, username, password, securityWord) {}

    void buyerMenu() {
        int choice;

        while (true) {
            cout << "\n\t\t\t\tBuyer Menu";
            cout << "\n\t\t\t________________________________________\n";
            cout << "\n\t\t\t|\t 1. List Products  \t\t|";
            cout << "\n\t\t\t|\t 2. Buy Product   \t\t|";
            cout << "\n\t\t\t|\t 3. Back To Main Menu \t\t|";
            cout << "\n\t\t\t________________________________________";

            cout << "\n\n\t Please enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    listProducts();
                    break;
                case 2:
                    buyProduct();
                    break;
                case 3:
                    return; // Return to the main menu
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

    // Buyer-specific methods
    void listProducts() const;
    void listProducts(const string& productOwnerUsername) const;
    void buyProduct();
};

// Function definitions outside the class

void ProductOwner::addProduct() {
    Product newProduct;
    cout << "Enter product code: ";
    cin >> newProduct.productCode;
    cout << "Enter product name: ";
    cin.ignore(); // Consume newline character
    getline(cin, newProduct.name);
    cout << "Enter product description: ";
    getline(cin, newProduct.description);
    cout << "Enter product location: ";
    getline(cin, newProduct.location);
    cout << "Enter delivery option: ";
    getline(cin, newProduct.deliveryOption);
    cout<<"Enter The Product Quantity 1 packet as 1Kg: ";
    cin>>newProduct.quantity;
    cout << "Enter product price per 1Kg: ";
    cin >> newProduct.price;
    cout << "Enter discount (percentage): ";
    cin >> newProduct.discount;

    products.push_back(newProduct);
    saveProductsToFile();
    cout << "Product added successfully!" << endl;
}

void ProductOwner::updateProduct(const string& productCode) {
    for (size_t i = 0; i < products.size(); ++i) {
        if (products[i].productCode == productCode) {
            cout << "Enter new product name: ";
            cin.ignore();
            getline(cin, products[i].name);
            cout << "Enter new product description: ";
            getline(cin, products[i].description);
            cout << "Enter new product location: ";
            getline(cin, products[i].location);
            cout << "Enter new delivery option: ";
            getline(cin, products[i].deliveryOption);
            cout<<"Enter The Product Quantity 1 packet as 1Kg: ";
            cin>> products[i].quantity;
            cout << "Enter new product price per 1Kg: ";
            cin >> products[i].price;
            cout << "Enter new discount (percentage): ";
            cin >> products[i].discount;

            saveProductsToFile();
            cout << "Product updated successfully!" << endl;
            return;
        }
    }
    cout << "Sorry! The Product is not found." << endl;
}

void ProductOwner::removeProduct(const string& productCode) {
    for (size_t i = 0; i < products.size(); ++i) {
        if (products[i].productCode == productCode) {
            products.erase(products.begin() + i);
            saveProductsToFile();
            cout << "Product removed successfully!" << endl;
            return;
        }
    }
    cout << "Sorry! The Product is not found." << endl;
}

void ProductOwner::listProducts() const {
    if (products.empty()) {
        cout << "No products listed." << endl;
    } else {
        cout << "Products:" << endl;
        cout << left << setw(15) << "Product Code" << setw(10) << "Name" << setw(20) << "Description" << setw(15) << "Location" << setw(20) << "Delivery" << setw(10) <<"Quantity" << setw(5) << "Price" << setw(5) << "Discount" << endl;
        for (const Product& product : products) {
            cout << left << setw(15) << product.productCode << setw(10) << product.name << setw(20) << product.description << setw(15) << product.location << setw(20) << product.deliveryOption << setw(10) <<product.quantity<< setw(5) << product.price << setw(5) << product.discount << "%" << endl;
        }
    }
}

void ProductOwner::loadProductsFromFile() {
    ifstream infile(getUsername() + "_products.txt");

    if (infile.is_open()) {
        string productCode, name, description, location, deliveryOption;
        int quantity;
        double price, discount;
        while (getline(infile, productCode, ',') &&
               getline(infile, name, ',') &&
               getline(infile, description, ',') &&
               getline(infile, location, ',') &&
               getline(infile, deliveryOption, ',') &&
               (infile >> quantity) &&
               (infile >> price) &&
               (infile >> discount)) {
            infile.ignore(); // Ignore the newline character
            Product product = {productCode, name, description, location, deliveryOption, quantity, price, discount};
            products.push_back(product);
        }
        infile.close();
    } else {
        cout << "No products found for this user." << endl;
    }
}

void ProductOwner::saveProductsToFile() {
    ofstream outfile(getUsername() + "_products.txt");

    if (outfile.is_open()) {
        for (const Product& product : products) {
            outfile << product.productCode << ",\t" << product.name << ",\t" << product.description << ",\t"
                    << product.location << ",\t" << product.deliveryOption << ",\t" <<product.quantity << ",\t" << product.price << ",\t"
                    << product.discount << endl;
        }
        outfile.close();
    } else {
        cout << "Error opening file for writing." << endl;
    }
}

void Buyer::listProducts() const {
    string productOwnerUsername;
    cout << "Enter Product Owner's username: ";
    cin >> productOwnerUsername;
    listProducts(productOwnerUsername);
}

void Buyer::listProducts(const string& productOwnerUsername) const {
    ifstream infile;
    string filename = productOwnerUsername + "_products.txt";
    infile.open(filename);

    if (infile.is_open()) {
        string productCode, name, description, location, deliveryOption;
        int quantity;
        double price, discount;

        cout << "\tProducts from " << productOwnerUsername << ":" << endl;
        cout << left << setw(15) << "Product Code" << setw(10) << "Name" << setw(20) << "Description" << setw(15) << "Location" << setw(20) << "Delivery" << setw(10) <<"Quantity" << setw(5) << "Price" << setw(5) << "Discount" << endl;
        
        while (getline(infile, productCode, ',') &&
               getline(infile, name, ',') &&
               getline(infile, description, ',') &&
               getline(infile, location, ',') &&
               getline(infile, deliveryOption, ',') &&
               (infile >> quantity) &&
               (infile >> price) &&
               (infile >> discount)) {
            infile.ignore(); // Ignore the newline character
            cout << left << setw(15) << productCode << setw(10) << name << setw(20) << description << setw(15) << location << setw(20) << deliveryOption << setw(10) << quantity << setw(10) << price << setw(5) << discount << "%" << endl;
        }
        infile.close();
    } else {
        cout << "Sorry! No products found for " << productOwnerUsername << endl;
    }
}

void Buyer::buyProduct() {
    string productOwnerUsername, productCode;
    cout << "Enter Product Owner's username: ";
    cin >> productOwnerUsername;
    cout << "Enter product code to buy: ";
    cin >> productCode;
    
    ifstream infile;
    string filename = productOwnerUsername + "_products.txt";
    infile.open(filename);
    ofstream tempFile("temp.txt");

    bool productFound = false;
    bool insufficientStock = false;

    if (infile.is_open() && tempFile.is_open()) {
        string productCodeFromFile, name, description, location, deliveryOption;
        int quantity;
        double price, discount;

        while (getline(infile, productCodeFromFile, ',') &&
               getline(infile, name, ',') &&
               getline(infile, description, ',') &&
               getline(infile, location, ',') &&
               getline(infile, deliveryOption, ',') &&
               (infile >> quantity) &&
               (infile >> price) &&
               (infile >> discount)) {
            infile.ignore(); // Ignore the newline character

            if (productCodeFromFile == productCode) {
                productFound = true;
                int qtyToBuy;
                cout << "Enter quantity to buy: ";
                cin >> qtyToBuy;

                double amount = price * qtyToBuy;
                double totalAmount = amount - (amount * (discount / 100));

                if(qtyToBuy <= quantity){
                    cout << "\nPurchase Details:" << endl;
                    cout << "Product Code: " << productCode << endl;
                    cout << "Product Name: " << name << endl;
                    cout << "Description: " << description << endl;
                    cout << "Location: " << location << endl;
                    cout << "Delivery Option: " << deliveryOption << endl;
                    cout << "Product Quantity 1 packet per 1Kg: " <<quantity<<endl;
                    cout << "Price: $" << fixed << setprecision(2) << amount << endl;
                    cout << "Discount: " << discount << "%" << endl;
                    cout << "Total Amount Paid: $" << fixed << setprecision(2) << totalAmount << endl;
                    quantity -= qtyToBuy;
                    cout << "Product bought successfully!" << endl;
                    break;
                }else {
                    insufficientStock = true;
                    cout << "Insufficient stock. Available quantity: " << quantity << endl;
                    return;
                }
                tempFile << left << setw(15) << productCode << setw(10) << name << setw(20) 
                         << description << setw(15) << location << setw(20) << deliveryOption << setw(10) 
                         << quantity << setw(10) << price << setw(5) << discount << "%" << endl;
                      
            }
        }
        infile.close();
        tempFile.close();

        if (!productFound) {
            cout << "Sorry! The product with code " << productCode << " is not found." << endl;
        }else if (!insufficientStock) {
            remove((productOwnerUsername + "_products.txt").c_str());
            rename("temp.txt", (productOwnerUsername + "_products.txt").c_str());
        }
    } else {
        cout << "Error opening product file for " << productOwnerUsername << endl;
    }
}


// Function to save user data to a file
void saveUserToFile(const User& user, const string& userType) {
    ofstream outfile(userType + "s.txt", ios::app);
    if (outfile.is_open()) {
        outfile << user.getUsername() << ",\t" << user.getPassword() << ",\t" << user.getName() << ",\t"<<user.getSecurityWord() << endl;
        cout<<"\nRegistration is Successfull!";
        outfile.close();
    } else {
        cout << "Error opening file for writing." << endl;
    }
}

// Function to load user data from a file
unordered_map<string, pair<string, string>> loadUsersFromFile(const string& userType) {
    unordered_map<string, pair<string, string>> users;
    ifstream infile(userType + "s.txt");

    if (infile.is_open()) {
        string username, password, name;
        while (getline(infile, username, ',') &&
               getline(infile, password, ',') &&
               getline(infile, name)) {
            users[username] = make_pair(password, name);
        }
        infile.close();
    } else {
        cout << "No users found for this user type." << endl;
    }

    return users;
}

// Function to register a new user
void registerUser(const string& userType) {
    string name, username, password, confirmPassword, securityWord;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter your desired username: ";
    cin >> username;

    do {
        cout << "Enter a password: ";
        cin >> password;
        cout << "Confirm password: ";
        cin >> confirmPassword;

        if (password != confirmPassword) {
            cout << "Passwords do not match. Please try again." << endl;
        }
    } while (password != confirmPassword);

    cout<<"Enter Your Security Key Word: ";
    cin.ignore();
    getline(cin, securityWord);

    // Create the user object
    User* newUser = nullptr;

    if (userType == "ProductOwner") {
        newUser = new ProductOwner(name, username, password, securityWord);
    } else {
        newUser = new Buyer(name, username, password, securityWord);
    }

    saveUserToFile(*newUser, userType);
    delete newUser;
}

// Function to handle user login
void loginUser(const string& userType) {
    string username, password, securityWord;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // Load users from file
    unordered_map<string, pair<string, string>> users = loadUsersFromFile(userType);

    // Check if the user exists and verify password
    if (users.find(username) != users.end()) {
        string storedPassword = get<0>(users[username]);
        string name = get<1>(users[username]);
        if (password == storedPassword) {
            cout << "Login successful! Welcome, " << name << "!" << endl;
            // Proceed to the respective menu
            if (userType == "ProductOwner") {
                ProductOwner productOwner(name, username, storedPassword, users[username].second);
                productOwner.productOwnerMenu();
            } else {
                Buyer buyer(name, username, storedPassword, users[username].second);
                buyer.buyerMenu();
            }
        } else {
            cout << "Invalid password. Please try again." << endl;
        }
    } else {
        cout << "Invalid username. Please try again." << endl;
    }
}

void forgotPassword(const string& userType) {
    m:
    string username, security_word;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your Security Word: ";
    cin >> security_word;

    // Load users from file
    unordered_map<string, pair<string, string>> users = loadUsersFromFile(userType);

    if (users.find(username) != users.end()) {
        string storedSecurityWord = users[username].second; // Get the stored security word from the loaded users
        if (security_word == storedSecurityWord) {
            string storedPassword = users[username].first; // Get the stored password from the loaded users
            cout << "Your password is: " << storedPassword << endl;
            loginUser(userType); // After retrieving the password, prompt the user to login
        } else {
            cout << "Security word doesn't match. Please try again or Register." << endl;
            registerUser(userType);
        }
    } else {
        cout << "Invalid username. Please try again." << endl;
        goto m;
    }
}


void menu() {
    string userType;
    int choice;

    while (true) {
        cout << "\n\t\t    _______________________________________";
        cout << "\n\t\t    =                                      =";
        cout << "\n\t\t    =     Automated Food Supply System     =";
        cout << "\n\t\t    =                                      =";
        cout << "\n\t\t    =______________________________________=\n";
        cout << "\n\t\t\t| 1. Register as Producer       |";
        cout << "\n\t\t\t| 2. Register as Buyer          |";
        cout << "\n\t\t\t| 3. Login as Producer          |";
        cout << "\n\t\t\t| 4. Login as Buyer             |";
        cout << "\n\t\t\t| 5. forgot Password            |";
        cout << "\n\t\t\t| 6. Exit                       |";
        cout << "\n\t\t\t_________________________________";

        cout << "\n\t\tPlease enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                userType = "ProductOwner";
                registerUser(userType);
                break;
            case 2:
                userType = "Buyer";
                registerUser(userType);
                break;
            case 3:
                userType = "ProductOwner";
                loginUser(userType);
                break;
            case 4:
                userType = "Buyer";
                loginUser(userType);
                break;
            case 5:
                forgotPassword(userType);
                break;
            case 6:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void welcomePage(){
        cout << "\n====================================================================================|\n";
    cout << "|                WELCOME TO AASTU AUTOMATED FOOD SUPPLY MARKET CENETER              |\n";
    cout << "|-----------------------------------------------------------------------------------|\n";
    cout << "|-----------------------------------------------------------------------------------|\n";
    cout << "|               ADDIS ABABA SCIENSCES AND TECHNOLOGY UNIVERSITY                     |\n";
    cout << "|                            UNIVERSITY FOR INDUSTRY                                |\n";
    cout << "|                      DEPARTMENET OF SOFTWARE ENGINEERING                          |\n";
    cout << "|-----------------------------------------------------------------------------------|\n";
    cout << "|                  This project Designed by CODE WORRIES Team                       |\n";
    cout << "|___________________________________________________________________________________|\n";
    cout << "\n\t\t    AASTU AUTOMATED FOOD SUPPLY MARKET center Registration page\n\n";
    cout << "\t\t\t   ******** MENU ********\n";

}

int main(){
    welcomePage();
    menu();
    return 0;
}
