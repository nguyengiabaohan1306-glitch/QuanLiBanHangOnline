// DonHang.h - Thực thể đơn hàng (mỗi đơn có thể có nhiều mã hàng).
#pragma once

#include <string>
#include <vector>

// Một dòng chi tiết trong đơn: mã hàng, số lượng, thành tiền.
struct ChiTietDon {
    std::string ma_hang;
    long long so_luong;
    long long thanh_tien;
};

class DonHang {
public:
    DonHang();

    int so_thu_tu() const { return so_thu_tu_; }
    const std::string& ten_khach() const { return ten_khach_; }
    const std::string& dia_chi() const { return dia_chi_; }
    const std::string& so_dien_thoai() const { return so_dien_thoai_; }
    const std::string& ngay_dat() const { return ngay_dat_; }
    long long tong_tien() const { return tong_tien_; }
    const std::vector<ChiTietDon>& chi_tiet() const { return chi_tiet_; }

    void DatThongTin(int so_thu_tu, const std::string& ten_khach,
        const std::string& dia_chi,
        const std::string& so_dien_thoai,
        const std::string& ngay_dat);
    void ThemChiTiet(const ChiTietDon& chi_tiet);
    bool CoMaHang(const std::string& ma) const;

    // Định dạng 1 dòng trong file:
    // so_thu_tu|ten_khach|dia_chi|so_dien_thoai|ngay_dat|tong_tien|ma:sl:tien;ma:sl:tien
    std::string ThanhDong() const;
    static bool TuDong(const std::string& dong, DonHang* don);

private:
    int so_thu_tu_;
    std::string ten_khach_, dia_chi_, so_dien_thoai_, ngay_dat_;
    long long tong_tien_;
    std::vector<ChiTietDon> chi_tiet_;
};

