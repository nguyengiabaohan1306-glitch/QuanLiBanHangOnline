// DonHang.cpp
#include "DonHang.h"

#include <sstream>

#include "TienIch.h"

DonHang::DonHang() : so_thu_tu_(0), tong_tien_(0) {}

void DonHang::DatThongTin(int so_thu_tu, const std::string& ten_khach,
    const std::string& dia_chi,
    const std::string& so_dien_thoai,
    const std::string& ngay_dat) {
    so_thu_tu_ = so_thu_tu;
    ten_khach_ = ten_khach;
    dia_chi_ = dia_chi;
    so_dien_thoai_ = so_dien_thoai;
    ngay_dat_ = ngay_dat;
}

void DonHang::ThemChiTiet(const ChiTietDon& chi_tiet) {
    chi_tiet_.push_back(chi_tiet);
    tong_tien_ += chi_tiet.thanh_tien;
}

bool DonHang::CoMaHang(const std::string& ma) const {
    for (size_t i = 0; i < chi_tiet_.size(); ++i)
        if (chi_tiet_[i].ma_hang == ma) return true;
    return false;
}

std::string DonHang::ThanhDong() const {
    std::ostringstream luong;
    luong << so_thu_tu_ << '|' << ten_khach_ << '|' << dia_chi_ << '|'
        << so_dien_thoai_ << '|' << ngay_dat_ << '|' << tong_tien_ << '|';
    for (size_t i = 0; i < chi_tiet_.size(); ++i) {
        if (i > 0) luong << ';';
        luong << chi_tiet_[i].ma_hang << ':' << chi_tiet_[i].so_luong << ':'
            << chi_tiet_[i].thanh_tien;
    }
    return luong.str();
}

bool DonHang::TuDong(const std::string& dong, DonHang* don) {
    std::vector<std::string> phan = tienich::TachChuoi(dong, '|');
    if (phan.size() != 7 || !tienich::ToanChuSo(phan[0]) ||
        !tienich::ToanChuSo(phan[5]))
        return false;
    DonHang don_moi;
    don_moi.DatThongTin(std::stoi(phan[0]), phan[1], phan[2], phan[3], phan[4]);
    std::vector<std::string> cac_muc = tienich::TachChuoi(phan[6], ';');
    for (size_t i = 0; i < cac_muc.size(); ++i) {
        std::vector<std::string> truong = tienich::TachChuoi(cac_muc[i], ':');
        if (truong.size() != 3 || !tienich::ToanChuSo(truong[1]) ||
            !tienich::ToanChuSo(truong[2]))
            return false;
        ChiTietDon chi_tiet = { truong[0], std::stoll(truong[1]),
                               std::stoll(truong[2]) };
        don_moi.ThemChiTiet(chi_tiet);
    }
    *don = don_moi;
    return true;
}
