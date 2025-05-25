#pragma once
#include <string>
#include <vector>
#include "QuanNhan.h"
#include "SiQuan.h"
#include "BinhSi.h"

class QuanLiQuanDoi {
private:
    std::vector<QuanNhan*> danhSach; // Danh sách con trỏ đến quân nhân

public:
    QuanLiQuanDoi(); // Hàm tạo
    ~QuanLiQuanDoi(); // Hàm hủy, giải phóng bộ nhớ

    void docDuLieuTuFile(); // Đọc dữ liệu từ file
    void capNhatDuLieu(); // Ghi dữ liệu vào file
    // Thêm quân nhân với đầy đủ thông tin
    void them(const std::string& maSo, const std::string& hoTen, const std::string& capBac,
              const std::string& donVi, const std::string& queQuan, const std::string& ngaySinh,
              const std::string& ngayNhapNgu, const std::string& trachNhiem_Hoac_ChucVu,
              const std::string& loai);
    void xoa(const std::string& maSo); // Xóa quân nhân
    // Sửa thông tin quân nhân
    void sua(const std::string& oldMaSo, const std::string& newMaSo, const std::string& hoTen,
             const std::string& capBac, const std::string& donVi, const std::string& queQuan,
             const std::string& ngaySinh, const std::string& ngayNhapNgu,
             const std::string& trachNhiem_Hoac_ChucVu);
    int timKiem(const std::string& maSo); // Tìm quân nhân theo mã số
    QuanNhan* getQuanNhanByIndex(int index); // Lấy quân nhân theo chỉ số
    int thongKeSiQuan(); // Đếm số sĩ quan
    int thongKeBinhSi(); // Đếm số binh sĩ
    long long NganSachToiThieu(); // Tính ngân sách tối thiểu

    size_t getSoLuong() const; // Lấy số lượng quân nhân
    const std::vector<QuanNhan*>& getDanhSach() const; // Lấy danh sách
};