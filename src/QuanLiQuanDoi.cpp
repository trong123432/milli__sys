#include "QuanLiQuanDoi.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <codecvt>
#include <locale>
#include <iostream>
// - stdexcept: Hỗ trợ ngoại lệ (exception).
// - cctype: Hỗ trợ xử lý ký tự (dùng trong trim).
// - codecvt, locale: Hỗ trợ chuyển đổi mã hóa Unicode (UTF-8/UTF-16).

#pragma warning(disable : 4996)

// Cắt bỏ khoảng trắng trong wstring
std::wstring trim_wstring(const std::wstring& wstr) {
    const std::wstring whitespace = L" \t\n\r\f\v";
    const size_t strBegin = wstr.find_first_not_of(whitespace);
    if (strBegin == std::wstring::npos) return L"";
    const size_t strEnd = wstr.find_last_not_of(whitespace);
    const size_t strRange = strEnd - strBegin + 1;
    return wstr.substr(strBegin, strRange);
}

// Cắt bỏ khoảng trắng trong string
std::string trim_string(const std::string& str) {
    const std::string whitespace = " \t\n\r\f\v";
    const size_t strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) return "";
    const size_t strEnd = str.find_last_not_of(whitespace);
    const size_t strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

// Hàm tạo
QuanLiQuanDoi::QuanLiQuanDoi() {}

// Hàm hủy, giải phóng bộ nhớ
QuanLiQuanDoi::~QuanLiQuanDoi() {
    for (auto qn : danhSach) {
        delete qn; // Giải phóng từng quân nhân
    }
    danhSach.clear();
}

// Lấy số lượng quân nhân
size_t QuanLiQuanDoi::getSoLuong() const {
    return danhSach.size();
}

// Lấy danh sách quân nhân
const std::vector<QuanNhan*>& QuanLiQuanDoi::getDanhSach() const {
    return danhSach;
}

// Đọc dữ liệu từ file Unicode
void QuanLiQuanDoi::docDuLieuTuFile() {
    std::wifstream file("data/solider_list.txt");
    if (!file.is_open()) {
        std::wcerr << L"Lỗi nghiêm trọng: Không thể mở file data/solider_list.txt!" << std::endl;
        throw std::runtime_error("Khong the mo file du lieu data/solider_list.txt!");
    }
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>)); // Hỗ trợ UTF-8

    for (auto qn : danhSach) {
        delete qn; // Giải phóng danh sách cũ
    }
    danhSach.clear();

    std::wstring line;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        line = trim_wstring(line);
        if (line.empty()) {
            continue; // Bỏ qua dòng rỗng
        }

        std::wstringstream ss(line);
        std::wstring maSo, hoTen, capBac, donVi, queQuan, ngaySinh, ngayNhapNgu, trachNhiem_ChucVu_NhiemVu, loaiFromFile;

        // Đọc từng trường, phân cách bằng |
        if (!std::getline(ss, maSo, L'|')) { std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu mã số." << std::endl; continue; }
        maSo = trim_wstring(maSo);
        if (!std::getline(ss, hoTen, L'|')) { std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu họ tên." << std::endl; continue; }
        hoTen = trim_wstring(hoTen);
        if (!std::getline(ss, capBac, L'|')) { std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu cấp bậc." << std::endl; continue; }
        capBac = trim_wstring(capBac);
        if (!std::getline(ss, donVi, L'|')) { std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu đơn vị." << std::endl; continue; }
        donVi = trim_wstring(donVi);
        if (!std::getline(ss, queQuan, L'|')) { std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu quê quán." << std::endl; continue; }
        queQuan = trim_wstring(queQuan);
        if (!std::getline(ss, ngaySinh, L'|')) { std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu ngày sinh." << std::endl; continue; }
        ngaySinh = trim_wstring(ngaySinh);
        if (!std::getline(ss, ngayNhapNgu, L'|')) { std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu ngày nhập ngũ." << std::endl; continue; }
        ngayNhapNgu = trim_wstring(ngayNhapNgu);
        if (!std::getline(ss, trachNhiem_ChucVu_NhiemVu, L'|')) { std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu trách nhiệm/chức vụ." << std::endl; continue; }
        trachNhiem_ChucVu_NhiemVu = trim_wstring(trachNhiem_ChucVu_NhiemVu);
        if (!std::getline(ss, loaiFromFile, L'|')) { std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu loại." << std::endl; continue; }
        loaiFromFile = trim_wstring(loaiFromFile);

        // Chuyển đổi sang string
        std::string sMaSo = converter.to_bytes(maSo);
        std::string sHoTen = converter.to_bytes(hoTen);
        std::string sCapBac = converter.to_bytes(capBac);
        std::string sDonVi = converter.to_bytes(donVi);
        std::string sQueQuan = converter.to_bytes(queQuan);
        std::string sNgaySinh = converter.to_bytes(ngaySinh);
        std::string sNgayNhapNgu = converter.to_bytes(ngayNhapNgu);
        std::string sTrachNhiem_ChucVu_NhiemVu = converter.to_bytes(trachNhiem_ChucVu_NhiemVu);
        std::string sLoaiFromFile = converter.to_bytes(loaiFromFile);

        if (sMaSo.empty() || sHoTen.empty() || sLoaiFromFile.empty() || sCapBac.empty()) {
            std::wcerr << L"Lỗi dòng " << lineNumber << L": Thiếu thông tin bắt buộc." << std::endl;
            continue;
        }

        try {
            if (sLoaiFromFile == "Sĩ Quan") {
                SiQuan* sq = new SiQuan(sMaSo, sHoTen, sCapBac, sDonVi, sQueQuan, sNgaySinh, sNgayNhapNgu, sTrachNhiem_ChucVu_NhiemVu);
                danhSach.push_back(sq);
            } else if (sLoaiFromFile == "Binh Sĩ") {
                BinhSi* bs = new BinhSi(sMaSo, sHoTen, sCapBac, sDonVi, sQueQuan, sNgaySinh, sNgayNhapNgu, sTrachNhiem_ChucVu_NhiemVu);
                danhSach.push_back(bs);
            } else {
                std::wcerr << L"Lỗi dòng " << lineNumber << L": Loại không hợp lệ '" << loaiFromFile << L"'." << std::endl;
            }
        } catch (const std::exception& e) {
            std::wcerr << L"Lỗi tạo đối tượng dòng " << lineNumber << L": " << converter.from_bytes(e.what()) << std::endl;
        }
    }
    file.close();
}

// Ghi dữ liệu vào file Unicode
void QuanLiQuanDoi::capNhatDuLieu() {
    std::wofstream file("data/solider_list.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Khong the mo file de luu du lieu!");
    }
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>)); // Hỗ trợ UTF-8

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    for (const auto& qn : danhSach) {
        file << converter.from_bytes(qn->getMaSo()) << L"|"
             << converter.from_bytes(qn->getHoTen()) << L"|"
             << converter.from_bytes(qn->getCapBac()) << L"|"
             << converter.from_bytes(qn->getDonVi()) << L"|"
             << converter.from_bytes(qn->getQueQuan()) << L"|"
             << converter.from_bytes(qn->getNgaySinh()) << L"|"
             << converter.from_bytes(qn->getNgayNhapNgu()) << L"|"
             << converter.from_bytes(qn->getTrachNhiem()) << L"|"
             << converter.from_bytes(qn->getLoai()) << L"\n";
    }
    file.close();
}

// Thêm quân nhân
void QuanLiQuanDoi::them(const std::string& maSo, const std::string& hoTen, const std::string& capBac,
                         const std::string& donVi, const std::string& queQuan, const std::string& ngaySinh,
                         const std::string& ngayNhapNgu, const std::string& trachNhiem_Hoac_ChucVu,
                         const std::string& loai) {
    if (timKiem(maSo) != -1) {
        throw std::runtime_error("Ma so da ton tai!");
    }
    if (loai == "Sĩ Quan") {
        SiQuan* sq = new SiQuan(maSo, hoTen, capBac, donVi, queQuan, ngaySinh, ngayNhapNgu, trachNhiem_Hoac_ChucVu);
        danhSach.push_back(sq);
    } else if (loai == "Binh Sĩ") {
        BinhSi* bs = new BinhSi(maSo, hoTen, capBac, donVi, queQuan, ngaySinh, ngayNhapNgu, trachNhiem_Hoac_ChucVu);
        danhSach.push_back(bs);
    } else {
        throw std::runtime_error("Loai quan nhan khong hop le!");
    }
}

// Xóa quân nhân
void QuanLiQuanDoi::xoa(const std::string& maSo) {
    int index = timKiem(maSo);
    if (index == -1) {
        throw std::runtime_error("Khong tim thay quan nhan voi ma so!");
    }
    delete danhSach[index];
    danhSach.erase(danhSach.begin() + index);
}

// Sửa thông tin quân nhân
void QuanLiQuanDoi::sua(const string& oldMaSo, const string& newMaSo, const string& hoTen,
                        const string& capBac, const string& donVi, const string& queQuan,
                        const string& ngaySinh, const string& ngayNhapNgu,
                        const string& trachNhiem_Hoac_ChucVu) {
    int index = timKiem(oldMaSo);
    if (index == -1) {
        throw std::runtime_error("Khong tim thay quan nhan voi ma so cu!");
    }
    if (oldMaSo != newMaSo && timKiem(newMaSo) != -1) {
        throw std::runtime_error("Ma so moi da ton tai!");
    }

    QuanNhan* qn = danhSach[index];
    qn->setMaSo(newMaSo);
    qn->setHoTen(hoTen);
    qn->setCapBac(capBac);
    qn->setDonVi(donVi);
    qn->setQueQuan(queQuan);
    qn->setNgaySinh(ngaySinh);
    qn->setNgayNhapNgu(ngayNhapNgu);

    if (SiQuan* sq = dynamic_cast<SiQuan*>(qn)) {
        sq->updateChucVu(trachNhiem_Hoac_ChucVu);
        sq->updateLuong();
    } else if (BinhSi* bs = dynamic_cast<BinhSi*>(qn)) {
        bs->setNhiemVu(trachNhiem_Hoac_ChucVu);
    }
}

// Tìm quân nhân theo mã số
int QuanLiQuanDoi::timKiem(const std::string& maSo) {
    for (size_t i = 0; i < danhSach.size(); i++) {
        if (danhSach[i]->getMaSo() == maSo) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Lấy quân nhân theo chỉ số
QuanNhan* QuanLiQuanDoi::getQuanNhanByIndex(int index) {
    if (index < 0 || index >= static_cast<int>(danhSach.size())) {
        return nullptr;
    }
    return danhSach[index];
}

// Đếm số sĩ quan
int QuanLiQuanDoi::thongKeSiQuan() {
    int count = 0;
    for (const auto& qn : danhSach) {
        if (dynamic_cast<SiQuan*>(qn)) {
            count++;
        }
    }
    return count;
}

// Đếm số binh sĩ
int QuanLiQuanDoi::thongKeBinhSi() {
    int count = 0;
    for (const auto& qn : danhSach) {
        if (dynamic_cast<BinhSi*>(qn)) {
            count++;
        }
    }
    return count;
}

// Tính ngân sách tối thiểu
long long QuanLiQuanDoi::NganSachToiThieu() {
    long long total = 0;
    for (const auto& qn : danhSach) {
        total += qn->getLuong(); // Dùng getLuong() đa hình
    }
    return total;
}