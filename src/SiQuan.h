#pragma once
#include "QuanNhan.h"

class SiQuan : public QuanNhan {
private:
    string chucVu; // Chức vụ của sĩ quan
    long long luong; // Lương hàng tháng

public:
    SiQuan(); // Hàm tạo mặc định
    SiQuan(string ms, string ht, string cb, string dv, string qq, string ns, string nnn, string cv); // Hàm tạo đầy đủ
    SiQuan(const SiQuan&); // Hàm tạo sao chép
    ~SiQuan() override; // Hàm hủy

    void updateChucVu(string cv); // Cập nhật chức vụ
    void updateLuong(); // Cập nhật lương dựa trên cấp bậc

    void hienThiThongTin() const override; // Hiển thị thông tin sĩ quan
    long long getLuong() const override; // Lấy lương
    string getTrachNhiem() const override; // Lấy chức vụ làm trách nhiệm
    string getLoai() const override; // Trả về loại "Sĩ Quan"

    friend istream& operator>>(istream&, SiQuan&);
    friend ostream& operator<<(ostream&, const SiQuan&);
};