**GEBEY APP**

# Automated Food Supply System

This project is a C++-based Automated Food Supply System designed to manage product inventory, user registration, and order processing. It is intended for educational and collaborative development.

## Features
- User registration and login
- Product inventory management
- Order placement and tracking
- Data persistence using text files

## Project Structure
- `automated_food_supply.cpp` – Main test application logic
- `Gebeya.cpp` – Main application logic
- `loginData.txt` – Stores user login data
- `Products.txt` – Stores product information
- `README.md` – Project documentation

## Getting Started

### Prerequisites
- C++ compiler (e.g., g++, MinGW, MSVC)
- Git (for cloning and collaboration)

### Cloning the Repository
1. Open your terminal or PowerShell.
2. Run the following command:
   ```sh
   git clone <repository-url>
   ```
   Replace `<repository-url>` with the actual URL of this repository.
3. Navigate to the project directory:
   ```sh
   cd group_project/Automated_Food_Supply
   ```

### Building the Project
Compile the main source file using your preferred C++ compiler. For example, with g++:
```sh
g++ automated_food_supply.cpp -o automated_food_supply.exe
```
You can also compile other modules as needed:
```sh
g++ register.cpp -o register.exe
g++ check.cpp -o check.exe
g++ final_project.cpp -o final_project.exe
```

### Running the Application
After building, run the executable:
```sh
./automated_food_supply.exe
```
Or double-click the `.exe` file in Windows Explorer.

## Collaboration Guidelines

1. **Fork the repository** on GitHub.
2. **Clone your fork** to your local machine.
3. **Create a new branch** for your feature or bugfix:
   ```sh
   git checkout -b feature/your-feature-name
   ```
4. **Make your changes** and commit them with clear messages.
5. **Push your branch** to your fork:
   ```sh
   git push origin feature/your-feature-name
   ```
6. **Open a Pull Request** to the main repository.

### Code Style
- Use clear and descriptive variable/function names.
- Comment your code where necessary.
- Follow C++ best practices.

### Issues & Suggestions
- Use the GitHub Issues tab to report bugs or suggest features.

## License
This project is for educational purposes. Please check with the project owner for licensing details.

---

*Happy coding and collaborating!*
