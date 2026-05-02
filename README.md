# Student-Management-System | Hệ thống Quản lý Sinh viên

## 📝 Mô tả
Đây là bài tập lớn môn **Kỹ thuật lập trình (Advanced Programming)**. Dự án tập trung xây dựng một ứng dụng C++ chạy trên nền tảng dòng lệnh để quản lý, tìm kiếm và phân tích hồ sơ sinh viên với hiệu suất cao.

---

## 🚀 Các tính năng chính
- **Quản lý**: Hỗ trợ đầy đủ Thêm, Xem, Sửa, Xóa hồ sơ sinh viên.
- **Tìm kiếm**: Tra cứu chính xác theo MSSV và tìm kiếm gần đúng theo tên (không phân biệt hoa thường).
- **Thống kê**: 
  - Sắp xếp theo MSSV, Tên (A-Z), và Điểm trung bình (Giảm dần).
  - Tìm kiếm điểm cao nhất/thấp nhất theo từng môn học.
- **Lưu trữ**: Tự động đồng bộ dữ liệu với tệp `student_list.txt`.

---

## 📑 Định dạng & Kiểm tra dữ liệu

Mỗi bản ghi trong tệp `student_list.txt` được cấu trúc như sau:

`ID | Fullname | Birth_Date | Address | Email | Phone_Number | Math_Score ; Literature_Score`

### ✅ Quy định kiểm tra
Chương trình áp dụng các bộ lọc dữ liệu nghiêm ngặt để đảm bảo tính toàn vẹn:
- **ID (MSSV)**: Phải là duy nhất, không được trùng lặp.
- **Fullname (Họ tên)**: Tự động chuẩn hóa (loại bỏ khoảng trắng thừa) và chuyển sang định dạng *IN HOA*.
- **Birth_Date (Ngày sinh)**: Phải nằm trong khoảng 1990 - 2024 và kiểm tra tính hợp lệ của ngày theo tháng/năm nhuận.
- **Address (Địa chỉ)**: Tự động định dạng theo kiểu *Viết Hoa Chữ Cái Đầu* mỗi từ.
- **Email**: Phải có định dạng hợp lệ (chứa `@` và `.`), không bắt đầu hoặc kết thúc bằng ký tự đặc biệt.
- **Phone_Number (Số điện thoại)**: Phải đủ 10 chữ số và bắt đầu bằng số `0`.
- **Scores (Điểm số)**: Phải nằm trong thang điểm từ `0` đến `10`.

---

## 📂 Cấu trúc dự án
- `student_management_system.cpp`: Mã nguồn chính của chương trình.
- `student_list.txt`: Tệp dữ liệu lưu trữ hồ sơ sinh viên *(đã được ẩn)*.
- `.gitignore`: Loại bỏ các tệp rác và cấu hình cục bộ.

---

## 🛠️ Hướng dẫn chạy
```bash
# Biên dịch
g++ student_management_system.cpp -o StudentManager

# Chạy chương trình
./StudentManager
