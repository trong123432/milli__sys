#include "BinhSi.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Hàm tạo mặc định
BinhSi::BinhSi() : QuanNhan(), nhiemVu("") {}

// Hàm tạo đầy đủ, gán _loai là "Binh Sĩ"
BinhSi::BinhSi(string ms, string ht, string cb, string dv, string qq, string ns, string nnn, string nv)
    : QuanNhan(ms, ht, cb, dv, qq, ns, nnn, "Binh Sĩ"), nhiemVu(nv) {
}

// Hàm tạo sao chép
BinhSi::BinhSi(const BinhSi& b) : QuanNhan(b), nhiemVu(b.nhiemVu) {}

// Hàm hủy
BinhSi::~BinhSi() {}

// Trả về loại "Binh Sĩ"
string BinhSi::getLoai() const {
    return "Binh Sĩ";
}

// Lấy nhiệm vụ làm trách nhiệm
string BinhSi::getTrachNhiem() const {
    return nhiemVu;
}

// Cập nhật nhiệm vụ
void BinhSi::setNhiemVu(string nv) {
    nhiemVu = nv;
}

// Tính lương dựa trên cấp bậc
long long BinhSi::getLuong() const {
    string normalizedCapBac = capBac;
    transform(normalizedCapBac.begin(), normalizedCapBac.end(), normalizedCapBac.begin(),
              [](unsigned char c) { return tolower(c); }); // Chuẩn hóa chữ thường
    if (normalizedCapBac == "binh nhi" || normalizedCapBac == "binh nhì") return 4000000;
    if (normalizedCapBac == "binh nhat" || normalizedCapBac == "binh nhất") return 4500000;
    if (normalizedCapBac == "ha si" || normalizedCapBac == "hạ sĩ" || normalizedCapBac == "hạ sỹ") return 5000000;
    if (normalizedCapBac == "trung si" || normalizedCapBac == "trung sĩ" || normalizedCapBac == "trung sỹ") return 5500000;
    return 4000000; // Mặc định
}

// Tính trợ cấp xuất ngũ dựa trên cấp bậc
long long BinhSi::troCapXuatNgu() {
    string normalizedCapBac = capBac;
    transform(normalizedCapBac.begin(), normalizedCapBac.end(), normalizedCapBac.begin(),
              [](unsigned char c) { return tolower(c); }); // Chuẩn hóa chữ thường
    if (normalizedCapBac == "binh nhi" || normalizedCapBac == "binh nhì") return 5000000;
    if (normalizedCapBac == "binh nhat" || normalizedCapBac == "binh nhất") return 7000000;
    if (normalizedCapBac == "ha si" || normalizedCapBac == "hạ sĩ" || normalizedCapBac == "hạ sỹ") return 8000000;
    if (normalizedCapBac == "trung si" || normalizedCapBac == "trung sĩ" || normalizedCapBac == "trung sỹ") return 9000000;
    return 1000000; // Mặc định
}

// Hiển thị thông tin binh sĩ
void BinhSi::hienThiThongTin() const {
    cout << "--------Binh Sĩ--------" << endl;
    QuanNhan::hienThiThongTin(); // Gọi hiển thị của lớp cơ sở
    cout << "Nhiem vu: " << nhiemVu << endl;
    cout << "Luong: " << getLuong() << endl;
    cout << "Tro cap xuat ngu: " << const_cast<BinhSi*>(this)->troCapXuatNgu() << endl;
    cout << "-----------------------\n" << endl;
}

istream& operator>>(istream& is, BinhSi& b) {
    is >> dynamic_cast<BinhSi&>(b);
    return is;
}

ostream& operator<<(ostream& os, const BinhSi& b) {
    os << b.maSo << ", " << b.hoTen << ", " << b.capBac << ", " << b.donVi << ", " << b.queQuan << ", " << b.ngaySinh << ", " << b.ngayNhapNgu << ", " << b.nhiemVu << ", " << b.getLoai();
    return os;
}

