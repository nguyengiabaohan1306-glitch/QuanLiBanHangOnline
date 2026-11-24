// QuanLiAdmin.cpp
#include "QuanLiAdmin.h"

#include <fstream>
#include <vector>

#include "TienIch.h"

QuanLiAdmin::QuanLiAdmin(const std::string& ten_file) {
    std::ifstream file(ten_file.c_str());
    std::string dong;
    while (std::getline(file, dong)) {
        std::vector<std::string> phan =
            tienich::TachChuoi(tienich::CatKhoangTrang(dong), '|');
        if (phan.size() == 2) {
            TaiKhoan tai_khoan;
            tai_khoan.user = phan[0];
            tai_khoan.password = phan[1];
            ds_tai_khoan_.ThemCuoi(tai_khoan);
        }
    }
    if (ds_tai_khoan_.Rong()) {  // Tạo tài khoản mặc định nếu chưa có file.
        TaiKhoan mac_dinh;
        mac_dinh.user = "admin";
        mac_dinh.password = "123456";
        ds_tai_khoan_.ThemCuoi(mac_dinh);
        std::ofstream ghi(ten_file.c_str());
        ghi << "admin|123456\n";
    }
}

bool QuanLiAdmin::KiemTra(const std::string& user,
    const std::string& password) const {
    // Duyệt danh sách liên kết từ đầu đến cuối.
    for (DanhSachLienKet<TaiKhoan>::Nut* p = ds_tai_khoan_.dau(); p != nullptr;
        p = p->tiep) {
        if (p->du_lieu.user == user && p->du_lieu.password == password)
            return true;
    }
    return false;
}
