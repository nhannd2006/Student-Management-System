# Student Information Management System

A robust C++ command-line application designed to manage, search, and analyze student records efficiently.

## 📝 Description
This project is a comprehensive management system developed to handle student databases. It features data persistence using text files and provides advanced statistical tools for academic performance analysis.

## 🚀 Key Features
- **Student Management (CRUD):** Add, edit, and delete student records including ID, Name, Birth Date, Address, Email, and Phone Number.
- **Search Engine:** - Exact ID lookup.
  - Approximate name search (case-insensitive).
- **Statistics & Reporting:**
  - Sorting functions by ID, Name (A-Z), and GPA (Descending).
  - Automated reports: Highest/Lowest scores by subject, GPA-based classification (Excellent, Good, Fair, etc.).
- **Data Persistence:** Automatic data synchronization with `student_list.txt`.

## 📂 Project Structure
- `student_management_system.cpp`: The core logic and implementation in C++.
- `student_list.txt`: The database file storing student records.
- `*.json`: Configuration and metadata files (local environment).

## 🛠️ How to Run
1. Clone the repository to your local machine.
2. Ensure you have a C++ compiler installed (e.g., `g++`).
3. Compile the source code:
   ```bash
   g++ student_management_system.cpp -o StudentManager