// QuanLiAdmin.h - Quản lí tài khoản nhân viên (file Admin.txt, dạng user|password).
#pragma once

#include <string>

#include "DanhSachLienKet.h"

struct TaiKhoan {
    std::string user;
    std::string password;
};

class QuanLiAdmin {
public:
    explicit QuanLiAdmin(const std::string& ten_file);
    bool KiemTra(const std::string& user, const std::string& password) const;

private:
    DanhSachLienKet<TaiKhoan> ds_tai_khoan_;
};
