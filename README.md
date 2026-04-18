# Student Information Management System

## 📝 Description
This repository contains an advanced student management application developed as a major assignment for the **Advanced Programming** course. The system is designed to handle complex data operations, ensuring accuracy and efficiency in academic record management.



## 🚀 Key Features
- **Comprehensive CRUD Operations:** Add, modify, and delete student profiles (ID, Full Name, Birth Date, Address, Email, and Phone).
- **Advanced Search Engine:** Supports exact match for Student IDs and fuzzy search for names (case-insensitive).
- **Statistical Analysis:**
  - Dynamic sorting by ID, Name (A-Z), and GPA (Descending).
  - Academic performance classification (Excellent, Good, Fair, etc.).
  - Subject-specific analysis (Highest/Lowest scores).
- **Data Persistence:** Seamless integration with `student_list.txt` for long-term storage.

## 📂 Project Structure
- `student_management_system.cpp`: Main logic and data structure implementation.
- `student_list.txt`: The database containing student records.
- `.gitignore`: Configured to exclude build artifacts and local environment settings.

## 🛠️ Installation & Usage
1. **Compile the source code:**
   ```bash
   g++ student_management_system.cpp -o StudentManager