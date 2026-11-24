// QuanLiDonHang.h - Quản lí hàng đợi các đơn hàng đang chờ xử lí
// (file DonHang.txt).
#pragma once

#include <string>

#include "DonHang.h"
#include "HangDoi.h"

class QuanLiDonHang {
public:
    explicit QuanLiDonHang(const std::string& ten_file);

    // Số thứ tự cho đơn mới (bắt đầu từ 1, tăng dần).
    int SoThuTuTiepTheo() const { return so_thu_tu_tiep_; }
    void ThemDon(const DonHang& don);
    bool LayDonDau(DonHang* don) { return hang_doi_.LayRaKhoiHang(don); }
    bool Rong() const { return hang_doi_.Rong(); }
    int SoLuong() const { return hang_doi_.KichThuoc(); }
    bool LuuFile();

private:
    std::string ten_file_;
    int so_thu_tu_tiep_;
    HangDoi<DonHang> hang_doi_;
};
