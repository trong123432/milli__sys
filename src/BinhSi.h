#pragma once
#include "QuanNhan.h"

class BinhSi : public QuanNhan {
private:
    string nhiemVu; // Nhiệm vụ của binh sĩ

public:
    BinhSi(); // Hàm tạo mặc định
    BinhSi(string ms, string ht, string cb, string dv, string qq, string ns, string nnn, string nv); // Hàm tạo đầy đủ
    BinhSi(const BinhSi&); // Hàm tạo sao chép
    ~BinhSi() override; // Hàm hủy

    void hienThiThongTin() const override; // Hiển thị thông tin binh sĩ
    void setNhiemVu(string nv); // Cập nhật nhiệm vụ

    long long troCapXuatNgu(); // Tính trợ cấp xuất ngũ
    string getLoai() const override; // Trả về loại "Binh Sĩ"
    string getTrachNhiem() const override; // Lấy nhiệm vụ
    long long getLuong() const override; // Lấy lương

    friend istream& operator>>(istream&, BinhSi&);
    friend ostream& operator<<(ostream&, const BinhSi&);
};