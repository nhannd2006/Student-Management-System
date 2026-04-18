# Student-Management-System

## 📝 Description | Mô tả
- **English**: A major assignment for the **Advanced Programming** course, building a robust program for student record management and analysis.
- **Tiếng Việt**: Bài tập lớn môn **Kỹ thuật lập trình**, xây dựng chương trình quản lý và phân tích hồ sơ sinh viên nâng cao.

## 👤 Author Information | Thông tin Tác giả
- **Project | Đồ án**: Student Information Management System 
- **Course | Học phần**: Advanced Programming (Kỹ thuật lập trình) 
- **Author | Tác giả**: Nguyễn Đăng Nhân (ID: 24280038)
- **Class | Lớp**: 24KDL1
- **University | Trường**: VNU-HCM University of Science (Đại học Khoa học Tự nhiên, ĐHQG-HCM)
- **Completion Date | Ngày hoàn thành**: 21/06/2025

## 🚀 Key Features | Các tính năng chính
- **Management | Quản lý**: Full CRUD support for student profiles (ID, Name, Birth Date, etc.) | Hỗ trợ đầy đủ các thao tác Thêm, Sửa, Xóa hồ sơ sinh viên.
- **Search | Tìm kiếm**: Exact ID lookup and approximate name search | Tra cứu chính xác theo MSSV và tìm kiếm gần đúng theo tên.
- **Statistics | Thống kê**: Sorting by multiple criteria and performance classification | Sắp xếp đa tiêu chí và xếp loại học lực.
- **Persistence | Lưu trữ**: Automatic data synchronization with `student_list.txt` | Tự động đồng bộ dữ liệu với tệp `student_list.txt`.

## 📂 Project Structure | Cấu trúc dự án
- `student_management_system.cpp`: Main source code | Mã nguồn chính của chương trình.
- `student_list.txt`: Database file storing student data | Tệp cơ sở dữ liệu lưu trữ hồ sơ sinh viên.
- `.gitignore`: Excludes build artifacts and local configs | Loại bỏ các tệp rác và cấu hình cục bộ.

## 🛠️ How to Run | Hướng dẫn chạy
```bash
# Compile | Biên dịch
g++ student_management_system.cpp -o StudentManager

# Execute | Chạy chương trình
./StudentManager