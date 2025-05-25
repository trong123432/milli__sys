#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class QuanNhan {
protected:
    string maSo, hoTen, capBac, donVi, queQuan, ngaySinh, ngayNhapNgu, _loai;

public:
    // Hàm tạo mặc định
    QuanNhan();

    // Hàm tạo đầy đủ tham số, bao gồm _loai để khởi tạo từ file
    QuanNhan(string ms, string ht, string cb, string dv, string qq, string ns, string nnn, string loai = "");

    // Hàm tạo sao chép
    QuanNhan(const QuanNhan& qn);

    // Hàm hủy ảo để đảm bảo lớp con hủy đúng cách
    virtual ~QuanNhan();

    // Hiển thị thông tin quân nhân, dùng cho console hoặc lấy dữ liệu cho GUI
    virtual void hienThiThongTin() const;

    // Getter cho các thuộc tính
    string getMaSo() const;      // Lấy mã số
    string getHoTen() const;     // Lấy họ tên
    string getCapBac() const;    // Lấy cấp bậc
    string getDonVi() const;     // Lấy đơn vị
    string getQueQuan() const;   // Lấy quê quán
    string getNgaySinh() const;  // Lấy ngày sinh
    string getNgayNhapNgu() const; // Lấy ngày nhập ngũ
    string getLoaiData() const;  // Lấy _loai (dữ liệu từ file)

    // Setter cho các thuộc tính
    void setMaSo(string ms);      // Cập nhật mã số
    void setHoTen(string ht);     // Cập nhật họ tên
    void setCapBac(string cb);    // Cập nhật cấp bậc
    void setDonVi(string dv);     // Cập nhật đơn vị
    void setQueQuan(string qq);   // Cập nhật quê quán
    void setNgaySinh(string ns);  // Cập nhật ngày sinh
    void setNgayNhapNgu(string nnn); // Cập nhật ngày nhập ngũ
    void setLoaiData(string loai);   // Cập nhật _loai

    // Hàm ảo thuần túy để lớp con triển khai trách nhiệm (chức vụ/nhiệm vụ)
    virtual string getTrachNhiem() const = 0;
    // Hàm ảo thuần túy để lấy lương, buộc lớp con triển khai
    virtual long long getLuong() const = 0;

    // Hàm ảo thuần túy để lấy loại quân nhân (Sĩ Quan/Binh Sĩ)
    virtual string getLoai() const = 0;

    // Mã hóa cấp bậc thành số để so sánh hoặc sắp xếp
    int maHoaCapBac();

    friend istream& operator>>(istream&, QuanNhan&);
    friend ostream& operator<<(ostream&, const QuanNhan&);
};