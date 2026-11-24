// HangHoa.h - Thực thể hàng hóa.
#pragma once
#include <string>

class HangHoa {
public:
    HangHoa();
    HangHoa(const std::string& ma, const std::string& ten,
        const std::string& noi_san_xuat, const std::string& mau_sac,
        long long gia_ban, const std::string& ngay_nhap, long long so_luong);

    const std::string& ma() const { return ma_; }
    const std::string& ten() const { return ten_; }
    const std::string& noi_san_xuat() const { return noi_san_xuat_; }
    const std::string& mau_sac() const { return mau_sac_; }
    long long gia_ban() const { return gia_ban_; }
    const std::string& ngay_nhap() const { return ngay_nhap_; }
    long long so_luong() const { return so_luong_; }
    void set_so_luong(long long so_luong) { so_luong_ = so_luong; }

    // Định dạng 1 dòng trong file:
    // ma|ten|noi_san_xuat|mau_sac|gia_ban|ngay_nhap|so_luong
    std::string ThanhDong() const;
    static bool TuDong(const std::string& dong, HangHoa* hang_hoa);

private:
    std::string ma_, ten_, noi_san_xuat_, mau_sac_;
    long long gia_ban_;
    std::string ngay_nhap_;
    long long so_luong_;
};

