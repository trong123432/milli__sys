#include "SiQuan.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

// Hàm tạo mặc định
SiQuan::SiQuan() : QuanNhan(), chucVu(""), luong(0) {
    updateLuong(); // Khởi tạo lương
}

// Hàm tạo đầy đủ, gán _loai là "Sĩ Quan"
SiQuan::SiQuan(string ms, string ht, string cb, string dv, string qq, string ns, string nnn, string cv)
    : QuanNhan(ms, ht, cb, dv, qq, ns, nnn, "Sĩ Quan"), chucVu(cv) {
    updateLuong(); // Cập nhật lương
}

// Hàm tạo sao chép
SiQuan::SiQuan(const SiQuan& q) : QuanNhan(q), chucVu(q.chucVu), luong(q.luong) {}

// Hàm hủy
SiQuan::~SiQuan() {}

// Trả về loại "Sĩ Quan"
string SiQuan::getLoai() const {
    return "Sĩ Quan";
}

// Cập nhật chức vụ
void SiQuan::updateChucVu(string cv) {
    chucVu = cv;
}

// Cập nhật lương dựa trên cấp bậc
void SiQuan::updateLuong() {
    string normalizedCapBac = capBac;
    transform(normalizedCapBac.begin(), normalizedCapBac.end(), normalizedCapBac.begin(),
              [](unsigned char c) { return tolower(c); }); // Chuẩn hóa chữ thường
    // Hỗ trợ cả ASCII và Unicode
    if (normalizedCapBac == "thieu uy" || normalizedCapBac == "thiếu úy") luong = 8000000;
    else if (normalizedCapBac == "trung uy" || normalizedCapBac == "trung úy") luong = 9000000;
    else if (normalizedCapBac == "thuong uy" || normalizedCapBac == "thượng úy") luong = 10000000;
    else if (normalizedCapBac == "dai uy" || normalizedCapBac == "đại úy") luong = 12000000;
    else if (normalizedCapBac == "thieu ta" || normalizedCapBac == "thiếu tá") luong = 15000000;
    else if (normalizedCapBac == "trung ta" || normalizedCapBac == "trung tá") luong = 18000000;
    else if (normalizedCapBac == "thuong ta" || normalizedCapBac == "thượng tá") luong = 20000000;
    else if (normalizedCapBac == "dai ta" || normalizedCapBac == "đại tá") luong = 22000000;
    else if (normalizedCapBac == "thieu tuong" || normalizedCapBac == "thiếu tướng") luong = 24000000;
    else if (normalizedCapBac == "trung tuong" || normalizedCapBac == "trung tướng") luong = 26000000;
    else if (normalizedCapBac == "thuong tuong" || normalizedCapBac == "thượng tướng") luong = 28000000;
    else if (normalizedCapBac == "dai tuong" || normalizedCapBac == "đại tướng") luong = 30000000;
    else luong = 7000000; // Mặc định
}

// Lấy lương
long long SiQuan::getLuong() const {
    return luong;
}

// Lấy chức vụ làm trách nhiệm
string SiQuan::getTrachNhiem() const {
    return chucVu;
}

// Hiển thị thông tin sĩ quan
void SiQuan::hienThiThongTin() const {
    cout << "--------Sĩ Quan--------" << endl;
    QuanNhan::hienThiThongTin(); // Gọi hiển thị của lớp cơ sở
    cout << "Chuc vu: " << chucVu << endl;
    cout << "Luong: " << getLuong() << endl;
    cout << "-----------------------\n" << endl;
}

istream& operator>>(istream& is, SiQuan& s) {
    is >> dynamic_cast<SiQuan&>(s);
    return is;
}

ostream& operator<<(ostream& os, const SiQuan& s) {
    os << s.maSo << ", " << s.hoTen << ", " << s.capBac << ", " << s.donVi << ", " << s.queQuan << ", " << s.ngaySinh << ", " << s.ngayNhapNgu << ", " << s.chucVu << ", " << s.getLoai();
    return os;
}