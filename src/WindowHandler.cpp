#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
// Định nghĩa các macro UNICODE và _UNICODE để hỗ trợ chuỗi ký tự Unicode (UTF-16) trong Windows API.

#include <windows.h>
#include <windowsx.h>
#include <Commctrl.h>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <algorithm>
#include "QuanLiQuanDoi.h"
// - windows.h, windowsx.h, Commctrl.h: Thư viện Windows API để tạo giao diện và điều khiển ListView.
// - stdexcept: Hỗ trợ ngoại lệ (exception).
// - cctype: Hỗ trợ xử lý ký tự (dùng trong trim).
// - codecvt, locale: Hỗ trợ chuyển đổi mã hóa Unicode (UTF-8/UTF-16).

#pragma comment(lib, "ComCtl32.lib")
// Liên kết tĩnh với thư viện ComCtl32.lib để sử dụng các điều khiển chung (như ListView).

QuanLiQuanDoi quanLiQuanDoi;
// Khởi tạo đối tượng toàn cục quanLiQuanDoi để quản lý danh sách quân nhân.

HWND hListView;
HWND hMaSoEdit, hHoTenEdit, hCapBacEdit, hDonViEdit, hQueQuanEdit, hNgaySinhEdit, hNgayNhapNguEdit;
HWND hChucVuEdit, hNhiemVuEdit, hLoaiQuanNhanEdit, hSearchEdit, hOutputStatic;
// Khai báo các biến toàn cục kiểu HWND để lưu trữ con trỏ tới các điều khiển giao diện (ListView, Edit, Static).

#define IDC_ADD_BUTTON          1001
#define IDC_DELETE_BUTTON       1002
#define IDC_EDIT_BUTTON         1003
#define IDC_SEARCH_BUTTON       1004
#define IDC_LOAD_BUTTON         1005
#define IDC_SAVE_BUTTON         1006
#define IDC_STAT_SQ_BUTTON      1007
#define IDC_STAT_BS_BUTTON      1008
#define IDC_STAT_NS_BUTTON      1009
#define IDC_LISTVIEW            2000
#define IDC_MASO_EDIT           2001
#define IDC_HOTEN_EDIT          2002
#define IDC_CAPBAC_EDIT         2003
#define IDC_DONVI_EDIT          2004
#define IDC_QUEQUAN_EDIT        2005
#define IDC_NGAYSINH_EDIT       2006
#define IDC_NGAYNHAPNGU_EDIT    2007
#define IDC_CHUCVU_EDIT         2008
#define IDC_NHIEMVU_EDIT        2009
#define IDC_LOAIQUANNHAN_EDIT   2012
#define IDC_SEARCH_EDIT         2013
#define IDC_OUTPUT_STATIC       2014
// Định nghĩa các ID duy nhất cho các điều khiển giao diện (nút, ô nhập liệu, ListView, v.v.).

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// Khai báo hàm xử lý thông điệp cho cửa sổ chính.

void AddColumnsToListView(HWND hListView);
// Hàm thêm các cột vào ListView để hiển thị thông tin quân nhân.

void PopulateListView(HWND hListView);
// Hàm cập nhật dữ liệu từ quanLiQuanDoi vào ListView.

void ClearInputFields();
// Hàm xóa nội dung các ô nhập liệu.

void DisplayMessage(const std::wstring& msg);
// Hàm hiển thị thông báo lên điều khiển Static (hOutputStatic).

bool IsValidDateFormat(const std::wstring& date);
// Hàm kiểm tra định dạng ngày hợp lệ (dd/mm/yyyy).

bool IsNumeric(const std::wstring& str);
// Hàm kiểm tra chuỗi có phải là số hay không.

std::string ws2s(const std::wstring& ws) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(ws);
}
// Hàm chuyển đổi chuỗi Unicode (wstring) sang chuỗi UTF-8 (string).

std::wstring s2ws(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(s);
}
// Hàm chuyển đổi chuỗi UTF-8 (string) sang chuỗi Unicode (wstring).

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SetConsoleOutputCP(CP_UTF8);
    // Đặt mã hóa đầu ra của console là UTF-8 để hỗ trợ ký tự Unicode.

    _wsetlocale(LC_ALL, L"vi_VN.UTF-8");
    // Thiết lập locale cho tiếng Việt với mã hóa UTF-8.

    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icc);
    // Khởi tạo các điều khiển chung, cụ thể là ListView.

    const WCHAR CLASS_NAME[] = L"QuanLyQuanDoiClass";
    // Định nghĩa tên lớp cửa sổ.

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    // Cấu hình lớp cửa sổ với hàm xử lý thông điệp, màu nền, và tên lớp.

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // Đăng ký lớp cửa sổ, nếu thất bại thì hiển thị thông báo lỗi và thoát.

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Quản Lý Quân Đội",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1500, 725,
        NULL, NULL, hInstance, NULL
    );
    // Tạo cửa sổ chính với kích thước 1500x725, tiêu đề "Quản Lý Quân Đội".

    if (hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // Kiểm tra nếu tạo cửa sổ thất bại thì hiển thị lỗi và thoát.

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    // Hiển thị và cập nhật cửa sổ.

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // Vòng lặp xử lý thông điệp chính của ứng dụng.

    return (int)msg.wParam;
    // Trả về mã thoát từ thông điệp cuối cùng.
}

void AddColumnsToListView(HWND hListView) {
    LVCOLUMN lvCol = {};
    lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    // Cấu hình cột ListView với thuộc tính: văn bản, độ rộng, và chỉ số cột.

    const wchar_t* columns[] = {
        L"Mã số", L"Họ tên", L"Cấp bậc", L"Đơn vị",
        L"Quê quán", L"Ngày sinh", L"Ngày nhập ngũ",
        L"Chức vụ/Nhiệm vụ", L"Loại"
    };
    int widths[] = {100, 150, 100, 150, 120, 100, 100, 150, 100};
    // Mảng chứa tiêu đề và độ rộng các cột.

    for (int i = 0; i < 9; i++) {
        lvCol.pszText = const_cast<LPWSTR>(columns[i]);
        lvCol.cx = widths[i];
        lvCol.iSubItem = i;
        ListView_InsertColumn(hListView, i, &lvCol);
    }
    // Thêm từng cột vào ListView.
}

void PopulateListView(HWND hListView) {
    ListView_DeleteAllItems(hListView);
    InvalidateRect(hListView, NULL, TRUE);
    UpdateWindow(hListView);
    // Xóa toàn bộ dữ liệu cũ trong ListView và cập nhật lại giao diện.

    LVITEM lvItem = {};
    lvItem.mask = LVIF_TEXT;
    // Cấu hình mục ListView với thuộc tính văn bản.

    for (size_t i = 0; i < quanLiQuanDoi.getSoLuong(); i++) {
        QuanNhan* qn = quanLiQuanDoi.getQuanNhanByIndex(i);
        if (!qn) continue;
        // Duyệt qua danh sách quân nhân, bỏ qua nếu con trỏ null.

        lvItem.iItem = i;
        lvItem.iSubItem = 0;
        std::wstring maSo = s2ws(qn->getMaSo());
        lvItem.pszText = const_cast<LPWSTR>(maSo.c_str());
        int itemIndex = ListView_InsertItem(hListView, &lvItem);
        // Thêm mã số quân nhân vào cột đầu tiên.

        std::wstring hoTen = s2ws(qn->getHoTen());
        ListView_SetItemText(hListView, itemIndex, 1, const_cast<LPWSTR>(hoTen.c_str()));
        std::wstring capBac = s2ws(qn->getCapBac());
        ListView_SetItemText(hListView, itemIndex, 2, const_cast<LPWSTR>(capBac.c_str()));
        std::wstring donVi = s2ws(qn->getDonVi());
        ListView_SetItemText(hListView, itemIndex, 3, const_cast<LPWSTR>(donVi.c_str()));
        std::wstring queQuan = s2ws(qn->getQueQuan());
        ListView_SetItemText(hListView, itemIndex, 4, const_cast<LPWSTR>(queQuan.c_str()));
        std::wstring ngaySinh = s2ws(qn->getNgaySinh());
        ListView_SetItemText(hListView, itemIndex, 5, const_cast<LPWSTR>(ngaySinh.c_str()));
        std::wstring ngayNhapNgu = s2ws(qn->getNgayNhapNgu());
        ListView_SetItemText(hListView, itemIndex, 6, const_cast<LPWSTR>(ngayNhapNgu.c_str()));
        std::wstring trachNhiem = s2ws(qn->getTrachNhiem());
        ListView_SetItemText(hListView, itemIndex, 7, const_cast<LPWSTR>(trachNhiem.c_str()));
        std::wstring loai = s2ws(qn->getLoai());
        ListView_SetItemText(hListView, itemIndex, 8, const_cast<LPWSTR>(loai.c_str()));
        // Điền các thông tin còn lại của quân nhân vào các cột tương ứng.
    }
}

void ClearInputFields() {
    SetWindowText(hMaSoEdit, L"");
    SetWindowText(hHoTenEdit, L"");
    SetWindowText(hCapBacEdit, L"");
    SetWindowText(hDonViEdit, L"");
    SetWindowText(hQueQuanEdit, L"");
    SetWindowText(hNgaySinhEdit, L"");
    SetWindowText(hNgayNhapNguEdit, L"");
    SetWindowText(hChucVuEdit, L"");
    SetWindowText(hNhiemVuEdit, L"");
    SetWindowText(hLoaiQuanNhanEdit, L"");
    SetWindowText(hSearchEdit, L"");
    // Xóa nội dung của tất cả các ô nhập liệu và ô tìm kiếm.
}

void DisplayMessage(const std::wstring& msg) {
    SetWindowText(hOutputStatic, msg.c_str());
    // Hiển thị thông báo lên điều khiển Static.
}

bool IsValidDateFormat(const std::wstring& date) {
    std::wregex datePattern(L"\\d{2}/\\d{2}/\\d{4}");
    return std::regex_match(date, datePattern);
    // Kiểm tra chuỗi ngày có khớp với định dạng dd/mm/yyyy hay không.
}

bool IsNumeric(const std::wstring& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), [](wchar_t c) { return iswdigit(c); });
    // Kiểm tra chuỗi có rỗng không và tất cả ký tự có phải là số hay không.
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HFONT hFont = CreateFont(
        20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        VIETNAMESE_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI"
    );
    // Tạo font Segoe UI kích thước 20, hỗ trợ bộ mã tiếng Việt.

    switch (uMsg) {
        case WM_CREATE: {
            INITCOMMONCONTROLSEX icc;
            icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
            icc.dwICC = ICC_LISTVIEW_CLASSES;
            InitCommonControlsEx(&icc);
            // Khởi tạo lại các điều khiển chung trong sự kiện tạo cửa sổ.

            int x = 10, y = 10;
            int width = 150, height = 40;
            int longLabelWidth = 270;
            // Thiết lập tọa độ và kích thước ban đầu cho các điều khiển.

            HWND hStatic = CreateWindow(L"STATIC", L"Mã số:", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hMaSoEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_MASO_EDIT, NULL, NULL);
            SendMessage(hMaSoEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Mã số, áp dụng font.

            hStatic = CreateWindow(L"STATIC", L"Họ tên:", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hHoTenEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_HOTEN_EDIT, NULL, NULL);
            SendMessage(hHoTenEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Họ tên.

            hStatic = CreateWindow(L"STATIC", L"Cấp bậc:", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hCapBacEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_CAPBAC_EDIT, NULL, NULL);
            SendMessage(hCapBacEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Cấp bậc.

            hStatic = CreateWindow(L"STATIC", L"Đơn vị:", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hDonViEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_DONVI_EDIT, NULL, NULL);
            SendMessage(hDonViEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Đơn vị.

            hStatic = CreateWindow(L"STATIC", L"Quê quán:", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hQueQuanEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_QUEQUAN_EDIT, NULL, NULL);
            SendMessage(hQueQuanEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Quê quán.

            hStatic = CreateWindow(L"STATIC", L"Ngày sinh (dd/mm/yyyy):", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hNgaySinhEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_NGAYSINH_EDIT, NULL, NULL);
            SendMessage(hNgaySinhEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Ngày sinh.

            hStatic = CreateWindow(L"STATIC", L"Ngày nhập ngũ (dd/mm/yyyy):", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hNgayNhapNguEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_NGAYNHAPNGU_EDIT, NULL, NULL);
            SendMessage(hNgayNhapNguEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Ngày nhập ngũ.

            hStatic = CreateWindow(L"STATIC", L"Loại quân nhân (Sĩ Quan/Binh Sĩ):", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hLoaiQuanNhanEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_LOAIQUANNHAN_EDIT, NULL, NULL);
            SendMessage(hLoaiQuanNhanEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Loại quân nhân.

            hStatic = CreateWindow(L"STATIC", L"Chức vụ (cho Sĩ Quan):", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hChucVuEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_CHUCVU_EDIT, NULL, NULL);
            SendMessage(hChucVuEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Chức vụ (dành cho Sĩ Quan).

            hStatic = CreateWindow(L"STATIC", L"Nhiệm vụ (cho Binh Sĩ):", WS_VISIBLE | WS_CHILD, x, y, longLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hNhiemVuEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, x + longLabelWidth + 5, y, width, height, hwnd, (HMENU)IDC_NHIEMVU_EDIT, NULL, NULL);
            SendMessage(hNhiemVuEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            y += height + 5;
            // Tạo nhãn và ô nhập liệu cho Nhiệm vụ (dành cho Binh Sĩ).

            width = 80;
            int btnX = 20, btnY = y;
            int btnHeight = 35;
            // Thiết lập kích thước và vị trí cho các nút.

            hStatic = CreateWindow(L"BUTTON", L"Thêm", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, btnX, btnY, width, btnHeight, hwnd, (HMENU)IDC_ADD_BUTTON, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            btnX += width + 5;
            // Tạo nút "Thêm" để thêm quân nhân.

            hStatic = CreateWindow(L"BUTTON", L"Xóa", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, btnX, btnY, width, btnHeight, hwnd, (HMENU)IDC_DELETE_BUTTON, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            btnX += width + 5;
            // Tạo nút "Xóa" để xóa quân nhân.

            hStatic = CreateWindow(L"BUTTON", L"Sửa", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, btnX, btnY, width, btnHeight, hwnd, (HMENU)IDC_EDIT_BUTTON, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            // Tạo nút "Sửa" để chỉnh sửa thông tin quân nhân.

            btnX = 10;
            btnY += btnHeight + 5;
            // Cập nhật vị trí cho các điều khiển tiếp theo.

            int searchLabelWidth = 140;
            hStatic = CreateWindow(L"STATIC", L"Tìm kiếm (Mã số):", WS_VISIBLE | WS_CHILD, btnX, btnY, searchLabelWidth, height, hwnd, NULL, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            hSearchEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, btnX + 135, btnY, 150, height, hwnd, (HMENU)IDC_SEARCH_EDIT, NULL, NULL);
            SendMessage(hSearchEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            hStatic = CreateWindow(L"BUTTON", L"Tìm", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, btnX + 130 + 160, btnY, 80, height, hwnd, (HMENU)IDC_SEARCH_BUTTON, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            // Tạo nhãn, ô nhập liệu, và nút "Tìm" cho chức năng tìm kiếm theo mã số.

            btnX = 10;
            btnY += btnHeight + 10;
            // Cập nhật vị trí.

            hStatic = CreateWindow(L"BUTTON", L"Tải dữ liệu", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, btnX, btnY, 100, btnHeight, hwnd, (HMENU)IDC_LOAD_BUTTON, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            btnX += 105;
            hStatic = CreateWindow(L"BUTTON", L"Lưu dữ liệu", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, btnX, btnY, 100, btnHeight, hwnd, (HMENU)IDC_SAVE_BUTTON, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            // Tạo các nút "Tải dữ liệu" và "Lưu dữ liệu" để đọc/ghi file.

            btnX = 10;
            btnY += btnHeight + 10;
            // Cập nhật vị trí.

            hStatic = CreateWindow(L"BUTTON", L"Thống kê Sĩ Quan", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, btnX, btnY, 145, btnHeight, hwnd, (HMENU)IDC_STAT_SQ_BUTTON, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            btnX += 150;
            hStatic = CreateWindow(L"BUTTON", L"Thống kê Binh Sĩ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, btnX, btnY, 130, btnHeight, hwnd, (HMENU)IDC_STAT_BS_BUTTON, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            btnX += 135;
            hStatic = CreateWindow(L"BUTTON", L"Ngân sách tối thiểu", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, btnX, btnY, 150, btnHeight, hwnd, (HMENU)IDC_STAT_NS_BUTTON, NULL, NULL);
            SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            // Tạo các nút thống kê số lượng Sĩ Quan, Binh Sĩ, và ngân sách tối thiểu.

            btnX = 10;
            btnY += btnHeight + 10;
            // Cập nhật vị trí.

            hOutputStatic = CreateWindow(L"STATIC", L"Thông báo: Sẵn sàng.", WS_VISIBLE | WS_CHILD, btnX, btnY, 600, height, hwnd, (HMENU)IDC_OUTPUT_STATIC, NULL, NULL);
            SendMessage(hOutputStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
            // Tạo điều khiển Static để hiển thị thông báo.

            hListView = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                WC_LISTVIEW,
                L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                x + longLabelWidth + width + 90, 10, 1000, 600,
                hwnd,
                (HMENU)IDC_LISTVIEW,
                GetModuleHandle(NULL),
                NULL
            );
            SendMessage(hListView, WM_SETFONT, (WPARAM)hFont, TRUE);
            // Tạo ListView để hiển thị danh sách quân nhân với chế độ báo cáo và chỉ chọn một mục.

            AddColumnsToListView(hListView);
            // Thêm các cột vào ListView.

            try {
                quanLiQuanDoi.docDuLieuTuFile();
                PopulateListView(hListView);
                DisplayMessage(L"Dữ liệu đã được tải.");
            } catch (const std::exception& e) {
                DisplayMessage(s2ws(std::string("Lỗi tải dữ liệu: ") + e.what()));
            }
            // Thử tải dữ liệu từ file và hiển thị lên ListView, xử lý ngoại lệ nếu có lỗi.
            return 0;
        }

        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case IDC_ADD_BUTTON: {
                    wchar_t buffer[256];
                    std::string maSo, hoTen, capBac, donVi, queQuan, ngaySinh, ngayNhapNgu, trachNhiem, loai;
                    // Lấy dữ liệu từ các ô nhập liệu.

                    GetWindowText(hMaSoEdit, buffer, 256);
                    maSo = ws2s(buffer);
                    GetWindowText(hHoTenEdit, buffer, 256);
                    hoTen = ws2s(buffer);
                    GetWindowText(hCapBacEdit, buffer, 256);
                    capBac = ws2s(buffer);
                    GetWindowText(hDonViEdit, buffer, 256);
                    donVi = ws2s(buffer);
                    GetWindowText(hQueQuanEdit, buffer, 256);
                    queQuan = ws2s(buffer);
                    GetWindowText(hNgaySinhEdit, buffer, 256);
                    ngaySinh = ws2s(buffer);
                    GetWindowText(hNgayNhapNguEdit, buffer, 256);
                    ngayNhapNgu = ws2s(buffer);
                    GetWindowText(hLoaiQuanNhanEdit, buffer, 256);
                    loai = ws2s(buffer);
                    // Lấy dữ liệu từ các ô nhập liệu tương ứng.

                    if (loai == "Sĩ Quan") {
                        GetWindowText(hChucVuEdit, buffer, 256);
                        trachNhiem = ws2s(buffer);
                    } else if (loai == "Binh Sĩ") {
                        GetWindowText(hNhiemVuEdit, buffer, 256);
                        trachNhiem = ws2s(buffer);
                    } else {
                        DisplayMessage(L"Lỗi: Loại quân nhân không hợp lệ!");
                        return 0;
                    }
                    // Lấy chức vụ (Sĩ Quan) hoặc nhiệm vụ (Binh Sĩ) tùy thuộc vào loại quân nhân.

                    if (maSo.empty() || hoTen.empty() || capBac.empty() || donVi.empty() || queQuan.empty() ||
                        ngaySinh.empty() || ngayNhapNgu.empty() || loai.empty()) {
                        DisplayMessage(L"Lỗi: Vui lòng điền đầy đủ thông tin bắt buộc!");
                        return 0;
                    }
                    // Kiểm tra nếu thiếu thông tin bắt buộc thì hiển thị lỗi.

                    if (!IsValidDateFormat(s2ws(ngaySinh)) || !IsValidDateFormat(s2ws(ngayNhapNgu))) {
                        DisplayMessage(L"Lỗi: Định dạng ngày không hợp lệ (dd/mm/yyyy)!");
                        return 0;
                    }
                    // Kiểm tra định dạng ngày hợp lệ.

                    try {
                        quanLiQuanDoi.them(maSo, hoTen, capBac, donVi, queQuan, ngaySinh, ngayNhapNgu, trachNhiem, loai);
                        PopulateListView(hListView);
                        ClearInputFields();
                        DisplayMessage(L"Đã thêm quân nhân thành công.");
                    } catch (const std::exception& e) {
                        DisplayMessage(s2ws(std::string("Lỗi thêm quân nhân: ") + e.what()));
                    }
                    // Thêm quân nhân, cập nhật ListView, xóa ô nhập liệu, và hiển thị thông báo.
                    break;
                }

                case IDC_DELETE_BUTTON: {
                    wchar_t buffer[256];
                    GetWindowText(hMaSoEdit, buffer, 256);
                    std::string maSo = ws2s(buffer);
                    // Lấy mã số từ ô nhập liệu.

                    if (maSo.empty()) {
                        DisplayMessage(L"Lỗi: Vui lòng nhập mã số để xóa!");
                        return 0;
                    }
                    // Kiểm tra nếu mã số rỗng thì hiển thị lỗi.

                    try {
                        quanLiQuanDoi.xoa(maSo);
                        PopulateListView(hListView);
                        ClearInputFields();
                        DisplayMessage(L"Đã xóa quân nhân thành công.");
                    } catch (const std::exception& e) {
                        DisplayMessage(s2ws(std::string("Lỗi xóa quân nhân: ") + e.what()));
                    }
                    // Xóa quân nhân, cập nhật ListView, xóa ô nhập liệu, và hiển thị thông báo.
                    break;
                }

                case IDC_EDIT_BUTTON: {
                    wchar_t buffer[256];
                    std::string oldMaSo, maSo, hoTen, capBac, donVi, queQuan, ngaySinh, ngayNhapNgu, trachNhiem;
                    // Lấy dữ liệu từ các ô nhập liệu.

                    GetWindowText(hMaSoEdit, buffer, 256);
                    oldMaSo = ws2s(buffer);
                    GetWindowText(hMaSoEdit, buffer, 256);
                    maSo = ws2s(buffer);
                    GetWindowText(hHoTenEdit, buffer, 256);
                    hoTen = ws2s(buffer);
                    GetWindowText(hCapBacEdit, buffer, 256);
                    capBac = ws2s(buffer);
                    GetWindowText(hDonViEdit, buffer, 256);
                    donVi = ws2s(buffer);
                    GetWindowText(hQueQuanEdit, buffer, 256);
                    queQuan = ws2s(buffer);
                    GetWindowText(hNgaySinhEdit, buffer, 256);
                    ngaySinh = ws2s(buffer);
                    GetWindowText(hNgayNhapNguEdit, buffer, 256);
                    ngayNhapNgu = ws2s(buffer);
                    // Lấy thông tin từ các ô nhập liệu.

                    std::string loai;
                    GetWindowText(hLoaiQuanNhanEdit, buffer, 256);
                    loai = ws2s(buffer);
                    // Lấy loại quân nhân.

                    if (loai == "Sĩ Quan") {
                        GetWindowText(hChucVuEdit, buffer, 256);
                        trachNhiem = ws2s(buffer);
                    } else if (loai == "Binh Sĩ") {
                        GetWindowText(hNhiemVuEdit, buffer, 256);
                        trachNhiem = ws2s(buffer);
                    } else {
                        DisplayMessage(L"Lỗi: Loại quân nhân không hợp lệ!");
                        return 0;
                    }
                    // Lấy chức vụ hoặc nhiệm vụ tùy thuộc vào loại.

                    if (oldMaSo.empty() || maSo.empty() || hoTen.empty() || capBac.empty() || donVi.empty() ||
                        queQuan.empty() || ngaySinh.empty() || ngayNhapNgu.empty()) {
                        DisplayMessage(L"Lỗi: Vui lòng điền đầy đủ thông tin bắt buộc!");
                        return 0;
                    }
                    // Kiểm tra thông tin bắt buộc.

                    if (!IsValidDateFormat(s2ws(ngaySinh)) || !IsValidDateFormat(s2ws(ngayNhapNgu))) {
                        DisplayMessage(L"Lỗi: Định dạng ngày không hợp lệ (dd/mm/yyyy)!");
                        return 0;
                    }
                    // Kiểm tra định dạng ngày.

                    try {
                        quanLiQuanDoi.sua(oldMaSo, maSo, hoTen, capBac, donVi, queQuan, ngaySinh, ngayNhapNgu, trachNhiem);
                        PopulateListView(hListView);
                        ClearInputFields();
                        DisplayMessage(L"Đã sửa thông tin quân nhân thành công.");
                    } catch (const std::exception& e) {
                        DisplayMessage(s2ws(std::string("Lỗi sửa thông tin: ") + e.what()));
                    }
                    // Sửa thông tin quân nhân, cập nhật ListView, xóa ô nhập liệu, và hiển thị thông báo.
                    break;
                }

                case IDC_SEARCH_BUTTON: {
                    wchar_t buffer[256];
                    GetWindowText(hSearchEdit, buffer, 256);
                    std::string maSo = ws2s(buffer);
                    // Lấy mã số từ ô tìm kiếm.

                    if (maSo.empty()) {
                        DisplayMessage(L"Lỗi: Vui lòng nhập mã số để tìm kiếm!");
                        return 0;
                    }
                    // Kiểm tra nếu mã số rỗng thì hiển thị lỗi.

                    int index = quanLiQuanDoi.timKiem(maSo);
                    if (index == -1) {
                        DisplayMessage(L"Không tìm thấy quân nhân với mã số: " + s2ws(maSo));
                        return 0;
                    }
                    // Tìm kiếm quân nhân theo mã số, nếu không tìm thấy thì hiển thị lỗi.

                    QuanNhan* qn = quanLiQuanDoi.getQuanNhanByIndex(index);
                    if (!qn) {
                        DisplayMessage(L"Lỗi: Không lấy được thông tin quân nhân!");
                        return 0;
                    }
                    // Lấy thông tin quân nhân theo chỉ số trả về.

                    SetWindowText(hMaSoEdit, s2ws(qn->getMaSo()).c_str());
                    SetWindowText(hHoTenEdit, s2ws(qn->getHoTen()).c_str());
                    SetWindowText(hCapBacEdit, s2ws(qn->getCapBac()).c_str());
                    SetWindowText(hDonViEdit, s2ws(qn->getDonVi()).c_str());
                    SetWindowText(hQueQuanEdit, s2ws(qn->getQueQuan()).c_str());
                    SetWindowText(hNgaySinhEdit, s2ws(qn->getNgaySinh()).c_str());
                    SetWindowText(hNgayNhapNguEdit, s2ws(qn->getNgayNhapNgu()).c_str());
                    SetWindowText(hLoaiQuanNhanEdit, s2ws(qn->getLoai()).c_str());
                    // Điền thông tin quân nhân vào các ô nhập liệu.

                    if (SiQuan* sq = dynamic_cast<SiQuan*>(qn)) {
                        SetWindowText(hChucVuEdit, s2ws(sq->getTrachNhiem()).c_str());
                        SetWindowText(hNhiemVuEdit, L"");
                    } else if (BinhSi* bs = dynamic_cast<BinhSi*>(qn)) {
                        SetWindowText(hNhiemVuEdit, s2ws(bs->getTrachNhiem()).c_str());
                        SetWindowText(hChucVuEdit, L"");
                    }
                    // Kiểm tra loại quân nhân (Sĩ Quan hoặc Binh Sĩ) và điền chức vụ/nhiệm vụ tương ứng.

                    DisplayMessage(L"Đã tìm thấy quân nhân với mã số: " + s2ws(maSo));
                    // Hiển thị thông báo tìm kiếm thành công.
                    break;
                }

                case IDC_LOAD_BUTTON: {
                    try {
                        quanLiQuanDoi.docDuLieuTuFile();
                        PopulateListView(hListView);
                        ClearInputFields();
                        DisplayMessage(L"Dữ liệu đã được tải lại thành công.");
                    } catch (const std::exception& e) {
                        DisplayMessage(s2ws(std::string("Lỗi tải dữ liệu: ") + e.what()));
                    }
                    // Tải dữ liệu từ file, cập nhật ListView, xóa ô nhập liệu, và hiển thị thông báo.
                    break;
                }

                case IDC_SAVE_BUTTON: {
                    try {
                        quanLiQuanDoi.capNhatDuLieu();
                        DisplayMessage(L"Dữ liệu đã được lưu thành công.");
                    } catch (const std::exception& e) {
                        DisplayMessage(s2ws(std::string("Lỗi lưu dữ liệu: ") + e.what()));
                    }
                    // Lưu dữ liệu vào file và hiển thị thông báo.
                    break;
                }

                case IDC_STAT_SQ_BUTTON: {
                    int soLuong = quanLiQuanDoi.thongKeSiQuan();
                    std::wstringstream ss;
                    ss << L"Số lượng Sĩ Quan: " << soLuong;
                    DisplayMessage(ss.str());
                    // Thống kê số lượng Sĩ Quan và hiển thị kết quả.
                    break;
                }

                case IDC_STAT_BS_BUTTON: {
                    int soLuong = quanLiQuanDoi.thongKeBinhSi();
                    std::wstringstream ss;
                    ss << L"Số lượng Binh Sĩ: " << soLuong;
                    DisplayMessage(ss.str());
                    // Thống kê số lượng Binh Sĩ và hiển thị kết quả.
                    break;
                }

                case IDC_STAT_NS_BUTTON: {
                    long long nganSach = quanLiQuanDoi.NganSachToiThieu();
                    std::wstringstream ss;
                    ss << L"Ngân sách tối thiểu: " << nganSach << L" VNĐ";
                    DisplayMessage(ss.str());
                    // Tính ngân sách tối thiểu và hiển thị kết quả.
                    break;
                }
            }
            return 0;
        }

        case WM_DESTROY: {
            DeleteObject(hFont);
            PostQuitMessage(0);
            return 0;
        }
        // Giải phóng font và thoát ứng dụng khi cửa sổ bị đóng.

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BTNFACE + 1));
            EndPaint(hwnd, &ps);
            return 0;
        }
        // Vẽ lại cửa sổ với màu nền mặc định.
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
    // Xử lý các thông điệp khác bằng hàm mặc định.
}