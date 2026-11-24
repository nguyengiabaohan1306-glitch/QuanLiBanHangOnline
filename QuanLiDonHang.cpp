// QuanLiDonHang.cpp
#include "QuanLiDonHang.h"

#include <fstream>

#include "TienIch.h"

QuanLiDonHang::QuanLiDonHang(const std::string& ten_file)
    : ten_file_(ten_file), so_thu_tu_tiep_(1) {
    std::ifstream file(ten_file_.c_str());
    std::string dong;
    while (std::getline(file, dong)) {
        DonHang don;
        if (DonHang::TuDong(tienich::CatKhoangTrang(dong), &don)) {
            hang_doi_.ThemVaoHang(don);
            if (don.so_thu_tu() >= so_thu_tu_tiep_)
                so_thu_tu_tiep_ = don.so_thu_tu() + 1;
        }
    }
}

void QuanLiDonHang::ThemDon(const DonHang& don) {
    hang_doi_.ThemVaoHang(don);
    ++so_thu_tu_tiep_;
}

// Ghi các đơn trong hàng đợi ra file mà vẫn giữ nguyên thứ tự hàng đợi:
// lấy từng đơn ra, ghi file, rồi cho vào lại cuối hàng đợi (đúng n lần).
bool QuanLiDonHang::LuuFile() {
    std::ofstream file(ten_file_.c_str());
    if (!file) return false;
    int so_don = hang_doi_.KichThuoc();
    for (int i = 0; i < so_don; ++i) {
        DonHang don;
        hang_doi_.LayRaKhoiHang(&don);
        file << don.ThanhDong() << "\n";
        hang_doi_.ThemVaoHang(don);
    }
    return true;
}
