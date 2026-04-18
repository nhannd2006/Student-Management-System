# Student-Management-System | Hệ thống Quản lý Sinh viên

## 📝 Description | Mô tả
- **English**: This is a major assignment for the **Advanced Programming** course. The project focuses on building a robust C++ command-line application for managing, searching, and analyzing student records with high efficiency.
- **Tiếng Việt**: Đây là bài tập lớn môn **Kỹ thuật lập trình (Advanced Programming)**. Dự án tập trung xây dựng một ứng dụng C++ chạy trên nền tảng dòng lệnh để quản lý, tìm kiếm và phân tích hồ sơ sinh viên với hiệu suất cao.

---

## 👤 Author Information | Thông tin Tác giả
- **Project | Đồ án**: Student Information Management System
- **Course | Học phần**: Advanced Programming (Kỹ thuật lập trình)
- **Author | Tác giả**: Nguyễn Đăng Nhân (ID: 24280038)
- **Class | Lớp**: 24KDL1
- **University | Trường**: VNU-HCM University of Science (Đại học Khoa học Tự nhiên, ĐHQG-HCM)
- **Completion Date | Ngày hoàn thành**: 21/06/2025

---

## 🚀 Key Features | Các tính năng chính
- **Management | Quản lý**: Full CRUD support (Create, Read, Update, Delete) | Hỗ trợ đầy đủ Thêm, Xem, Sửa, Xóa hồ sơ sinh viên.
- **Search | Tìm kiếm**: Exact ID lookup and case-insensitive approximate name search | Tra cứu chính xác theo MSSV và tìm kiếm gần đúng theo tên (không phân biệt hoa thường).
- **Statistics | Thống kê**: 
  - Sorting by ID, Name (A-Z), and GPA (Descending) | Sắp xếp theo MSSV, Tên (A-Z), và Điểm trung bình (Giảm dần).
  - Subject-specific analysis (Highest/Lowest scores) | Tìm kiếm điểm cao nhất/thấp nhất theo từng môn học.
- **Persistence | Lưu trữ**: Automatic data synchronization with `student_list.txt` | Tự động đồng bộ dữ liệu với tệp `student_list.txt`.

---

## 📑 Data Format & Validation | Định dạng & Kiểm tra dữ liệu

Each record in the `student_list.txt` file is structured as follows | Mỗi bản ghi trong tệp `student_list.txt` được cấu trúc như sau:
`ID | Fullname | Birth_Date | Address | Email | Phone_Number | Math_Score ; Literature_Score`

### ✅ Validation Rules | Quy định kiểm tra
The program applies strict data filters to ensure integrity | Chương trình áp dụng các bộ lọc dữ liệu nghiêm ngặt để đảm bảo tính toàn vẹn:
- **ID (MSSV)**: Must be unique; no duplicates are allowed | Phải là duy nhất, không được trùng lặp.
- **Fullname (Họ tên)**: Automatically normalized (removing redundant spaces) and converted to *UPPERCASE* | Tự động chuẩn hóa (loại bỏ khoảng trắng thừa) và chuyển sang định dạng *IN HOA*.
- **Birth_Date (Ngày sinh)**: Must be between 1990 and 2024, with full validation for days in months and leap years | Phải nằm trong khoảng 1990 - 2024 và kiểm tra tính hợp lệ của ngày theo tháng/năm nhuận.
- **Address (Địa chỉ)**: Automatically formatted to *Title Case* (capitalizing the first letter of each word) | Tự động định dạng theo kiểu *Viết Hoa Chữ Cái Đầu* mỗi từ.
- **Email**: Must follow a valid format (contains `@` and `.`) and cannot start or end with special characters | Phải có định dạng hợp lệ (chứa `@` và `.`), không bắt đầu hoặc kết thúc bằng ký tự đặc biệt.
- **Phone_Number (Số điện thoại)**: Must be exactly 10 digits and start with `0` | Phải đủ 10 chữ số và bắt đầu bằng số `0`.
- **Scores (Điểm số)**: Must be within the valid range of `0.0` to `10.0` | Phải nằm trong thang điểm từ `0` đến `10`.

---

## 📊 Classification Logic | Logic Xếp loại
- **Xuất sắc (Excellent)**: GPA ≥ 9.0
- **Giỏi (Good)**: GPA ≥ 8.0
- **Khá (Fair)**: GPA ≥ 6.5
- **Trung bình (Average)**: GPA ≥ 5.0
- **Yếu (Poor)**: GPA < 5.0

---

## 📂 Project Structure | Cấu trúc dự án
- `student_management_system.cpp`: The core source code containing system logic | Mã nguồn chính của chương trình.
- `student_list.txt`: Database file for student records *(hidden/untracked)* | Tệp dữ liệu lưu trữ hồ sơ sinh viên *(đã được ẩn)*.
- `.gitignore`: Excludes build artifacts (`.exe`, `.o`) and local configs | Loại bỏ các tệp rác và cấu hình cục bộ.

---

## 🛠️ How to Run | Hướng dẫn chạy
```bash
# Compile | Biên dịch
g++ student_management_system.cpp -o StudentManager

# Execute | Chạy chương trình
./StudentManager