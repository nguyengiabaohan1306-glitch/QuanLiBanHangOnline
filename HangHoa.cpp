// HangHoa.cpp
#include "HangHoa.h"

#include <sstream>
#include <vector>

#include "TienIch.h"

HangHoa::HangHoa() : gia_ban_(0), so_luong_(0) {}

HangHoa::HangHoa(const std::string& ma, const std::string& ten,
    const std::string& noi_san_xuat, const std::string& mau_sac,
    long long gia_ban, const std::string& ngay_nhap,
    long long so_luong)
    : ma_(ma), ten_(ten), noi_san_xuat_(noi_san_xuat), mau_sac_(mau_sac),
    gia_ban_(gia_ban), ngay_nhap_(ngay_nhap), so_luong_(so_luong) {}

std::string HangHoa::ThanhDong() const {
    std::ostringstream luong;
    luong << ma_ << '|' << ten_ << '|' << noi_san_xuat_ << '|' << mau_sac_ << '|'
        << gia_ban_ << '|' << ngay_nhap_ << '|' << so_luong_;
    return luong.str();
}

bool HangHoa::TuDong(const std::string& dong, HangHoa* hang_hoa) {
    std::vector<std::string> phan = tienich::TachChuoi(dong, '|');
    if (phan.size() != 7 || phan[0].size() != 4 ||
        !tienich::ToanChuSo(phan[4]) || !tienich::ToanChuSo(phan[6]))
        return false;
    *hang_hoa = HangHoa(phan[0], phan[1], phan[2], phan[3], std::stoll(phan[4]),
        phan[5], std::stoll(phan[6]));
    return true;
}
