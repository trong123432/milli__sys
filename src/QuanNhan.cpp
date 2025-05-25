#include "QuanNhan.h"
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

// Hàm tạo mặc định, khởi tạo các chuỗi rỗng
QuanNhan::QuanNhan() : maSo(""), hoTen(""), capBac(""), donVi(""), queQuan(""), ngaySinh(""), ngayNhapNgu(""), _loai("") {}

// Hàm tạo với tham số, bao gồm _loai để lưu loại từ file
QuanNhan::QuanNhan(string ms, string ht, string cb, string dv, string qq, string ns, string nnn, string loai)
    : maSo(ms), hoTen(ht), capBac(cb), donVi(dv), queQuan(qq), ngaySinh(ns), ngayNhapNgu(nnn), _loai(loai) {}

// Hàm tạo sao chép, sao chép tất cả thuộc tính, bao gồm _loai
QuanNhan::QuanNhan(const QuanNhan& qn)
    : maSo(qn.maSo), hoTen(qn.hoTen), capBac(qn.capBac), donVi(qn.donVi),
      queQuan(qn.queQuan), ngaySinh(qn.ngaySinh), ngayNhapNgu(qn.ngayNhapNgu), _loai(qn._loai) {}

// Hàm hủy ảo
QuanNhan::~QuanNhan() {}

// Hiển thị thông tin quân nhân, dùng cho console hoặc lấy dữ liệu cho GUI
void QuanNhan::hienThiThongTin() const {
    cout << "Ma so: " << maSo << ", Ho ten: " << hoTen << endl;
    cout << "Cap bac: " << capBac << ", Don vi: " << donVi << endl;
    cout << "Que quan: " << queQuan << ", ngay sinh: " << ngaySinh << endl;
    cout << "Ngay nhap ngu: " << ngayNhapNgu << endl;
    if (!_loai.empty()) cout << "Loai (data): " << _loai << endl; // Hiển thị _loai nếu có
}

// Getter
string QuanNhan::getMaSo() const { return maSo; }
string QuanNhan::getHoTen() const { return hoTen; }
string QuanNhan::getCapBac() const { return capBac; }
string QuanNhan::getDonVi() const { return donVi; }
string QuanNhan::getQueQuan() const { return queQuan; }
string QuanNhan::getNgaySinh() const { return ngaySinh; }
string QuanNhan::getNgayNhapNgu() const { return ngayNhapNgu; }
string QuanNhan::getLoaiData() const { return _loai; }

// Setter
void QuanNhan::setMaSo(string ms) { maSo = ms; }
void QuanNhan::setHoTen(string ht) { hoTen = ht; }
void QuanNhan::setCapBac(string cb) { capBac = cb; }
void QuanNhan::setDonVi(string dv) { donVi = dv; }
void QuanNhan::setQueQuan(string qq) { queQuan = qq; }
void QuanNhan::setNgaySinh(string ns) { ngaySinh = ns; }
void QuanNhan::setNgayNhapNgu(string nnn) { ngayNhapNgu = nnn; }
void QuanNhan::setLoaiData(string loai) { _loai = loai; }

// Mã hóa cấp bậc thành số (1-16) để so sánh/sắp xếp
int QuanNhan::maHoaCapBac() {
    string normalizedCapBac = capBac;
    transform(normalizedCapBac.begin(), normalizedCapBac.end(), normalizedCapBac.begin(),
              [](unsigned char c) { return tolower(c); }); // Chuẩn hóa chữ thường
    // Hỗ trợ cả ASCII và Unicode
    if (normalizedCapBac == "binh nhi" || normalizedCapBac == "binh nhì") return 1;
    if (normalizedCapBac == "binh nhat" || normalizedCapBac == "binh nhất") return 2;
    if (normalizedCapBac == "ha si" || normalizedCapBac == "hạ sĩ" || normalizedCapBac == "hạ sỹ") return 3;
    if (normalizedCapBac == "trung si" || normalizedCapBac == "trung sĩ" || normalizedCapBac == "trung sỹ") return 4;
    if (normalizedCapBac == "thuong si" || normalizedCapBac == "thượng sĩ" || normalizedCapBac == "thượng sỹ") return 5;
    if (normalizedCapBac == "thieu uy" || normalizedCapBac == "thiếu úy") return 6;
    if (normalizedCapBac == "trung uy" || normalizedCapBac == "trung úy") return 7;
    if (normalizedCapBac == "dai uy" || normalizedCapBac == "đại úy") return 8;
    if (normalizedCapBac == "thieu ta" || normalizedCapBac == "thiếu tá") return 9;
    if (normalizedCapBac == "trung ta" || normalizedCapBac == "trung tá") return 10;
    if (normalizedCapBac == "thuong ta" || normalizedCapBac == "thượng tá") return 11;
    if (normalizedCapBac == "dai ta" || normalizedCapBac == "đại tá") return 12;
    if (normalizedCapBac == "thieu tuong" || normalizedCapBac == "thiếu tướng") return 13;
    if (normalizedCapBac == "trung tuong" || normalizedCapBac == "trung tướng") return 14;
    if (normalizedCapBac == "thuong tuong" || normalizedCapBac == "thượng tướng") return 15;
    if (normalizedCapBac == "dai tuong" || normalizedCapBac == "đại tướng") return 16;
    return 0;
}

istream& operator>>(istream& is, QuanNhan& Qn) {
    is >> Qn.maSo >> Qn.hoTen >> Qn.capBac >> Qn.donVi >> Qn.queQuan >> Qn.ngaySinh >> Qn.ngayNhapNgu >> Qn._loai;
    return is;
}

ostream& operator<<(ostream& os, const QuanNhan& p) {
    os << p.maSo << ", " << p.hoTen << ", " << p.capBac << ", " << p.donVi << ", " << p.queQuan << ", " << p.ngaySinh << ", " << p.ngayNhapNgu;
    return os;
}