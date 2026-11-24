// QuanLiHangHoa.cpp
#include "QuanLiHangHoa.h"

#include <fstream>
#include <iostream>

#include "ThuatToan.h"
#include "TienIch.h"

using std::cout;
using std::string;
using std::vector;

// ---------------------- Các hàm so sánh dùng cho sắp xếp ----------------------
static bool TenAZ(const HangHoa& a, const HangHoa& b) {
    return tienich::ChuThuong(a.ten()) < tienich::ChuThuong(b.ten());
}
static bool GiaTangDan(const HangHoa& a, const HangHoa& b) {
    return a.gia_ban() < b.gia_ban();
}
static bool GiaGiamDan(const HangHoa& a, const HangHoa& b) {
    return a.gia_ban() > b.gia_ban();
}
static bool SoLuongGiamDan(const HangHoa& a, const HangHoa& b) {
    return a.so_luong() > b.so_luong();
}

// ---------------------- In bảng có kẻ khung ----------------------
static const int kSoCot = 7;
static const int kDoRong[kSoCot] = { 6, 26, 16, 10, 12, 12, 9 };
static const string kTieuDe[kSoCot] = { "Ma",      "Ten hang",  "Noi san xuat",
                                        "Mau sac", "Gia ban",   "Ngay nhap",
                                        "So luong" };

static void InDuongKe() {
    cout << "+";
    for (int i = 0; i < kSoCot; ++i) cout << string(kDoRong[i] + 2, '-') << "+";
    cout << "\n";
}

static void InDong(const string cac_o[]) {
    cout << "|";
    for (int i = 0; i < kSoCot; ++i)
        cout << " " << tienich::CanLe(cac_o[i], kDoRong[i]) << " |";
    cout << "\n";
}

void QuanLiHangHoa::InBang(const vector<HangHoa>& danh_sach) {
    InDuongKe();
    InDong(kTieuDe);
    InDuongKe();
    for (size_t i = 0; i < danh_sach.size(); ++i) {
        const HangHoa& h = danh_sach[i];
        string cac_o[kSoCot] = { h.ma(), h.ten(), h.noi_san_xuat(), h.mau_sac(),
                                 std::to_string(h.gia_ban()), h.ngay_nhap(),
                                 std::to_string(h.so_luong()) };
        InDong(cac_o);
    }
    InDuongKe();
    cout << "Tong so: " << danh_sach.size() << " mat hang\n";
}

// ---------------------- Đọc / ghi file ----------------------
QuanLiHangHoa::QuanLiHangHoa(const string& ten_file) : ten_file_(ten_file) {
    DocFile();
}

void QuanLiHangHoa::DocFile() {
    int so_hop_le = 0;
    int so_bo_qua = 0;
    DocTuFile(ten_file_, &so_hop_le, &so_bo_qua);
}

bool QuanLiHangHoa::LuuFile() const { return LuuRaFile(ten_file_); }

bool QuanLiHangHoa::DocTuFile(const string& ten_file, int* so_hop_le,
    int* so_bo_qua) {
    *so_hop_le = 0;
    *so_bo_qua = 0;
    std::ifstream file(ten_file.c_str());
    if (!file) return false;
    ds_.clear();
    string dong;
    while (std::getline(file, dong)) {
        dong = tienich::CatKhoangTrang(dong);
        if (dong.empty()) continue;
        HangHoa hang_hoa;
        // Them() chèn đúng vị trí nên mảng luôn được sắp xếp theo mã.
        if (HangHoa::TuDong(dong, &hang_hoa) && Them(hang_hoa)) {
            ++(*so_hop_le);
        }
        else {
            ++(*so_bo_qua);
        }
    }
    return true;
}

bool QuanLiHangHoa::LuuRaFile(const string& ten_file) const {
    std::ofstream file(ten_file.c_str());
    if (!file) return false;
    for (size_t i = 0; i < ds_.size(); ++i) file << ds_[i].ThanhDong() << "\n";
    return true;
}

// ---------------------- Tìm kiếm / thêm / xóa ----------------------
int QuanLiHangHoa::TimNhiPhan(const string& ma) const {
    int trai = 0;
    int phai = SoLuong() - 1;
    while (trai <= phai) {
        int giua = (trai + phai) / 2;
        if (ds_[giua].ma() == ma) return giua;
        if (ds_[giua].ma() < ma) trai = giua + 1;
        else phai = giua - 1;
    }
    return -1;
}

HangHoa* QuanLiHangHoa::TimTheoMa(const string& ma) {
    int vi_tri = TimNhiPhan(ma);
    if (vi_tri == -1) return nullptr;
    return &ds_[vi_tri];
}

// Chèn vào đúng vị trí để mảng vẫn tăng dần theo mã (giống 1 bước sắp xếp chèn).
bool QuanLiHangHoa::Them(const HangHoa& hang_hoa) {
    if (hang_hoa.ma().size() != 4 || TimNhiPhan(hang_hoa.ma()) != -1) return false;
    ds_.push_back(hang_hoa);
    int i = SoLuong() - 1;
    while (i > 0 && ds_[i - 1].ma() > hang_hoa.ma()) {
        ds_[i] = ds_[i - 1];  // dời phần tử sang phải
        --i;
    }
    ds_[i] = hang_hoa;
    return true;
}

bool QuanLiHangHoa::Xoa(const string& ma) {
    int vi_tri = TimNhiPhan(ma);
    if (vi_tri == -1) return false;
    for (int i = vi_tri; i + 1 < SoLuong(); ++i) {
        ds_[i] = ds_[i + 1];  // dời phần tử sang trái để lấp chỗ trống
    }
    ds_.pop_back();
    return true;
}

int QuanLiHangHoa::TimTheoTen(const string& ten) const {
    string tu_khoa = tienich::ChuThuong(ten);
    vector<HangHoa> ket_qua;
    for (size_t i = 0; i < ds_.size(); ++i) {
        if (tienich::ChuThuong(ds_[i].ten()).find(tu_khoa) != string::npos)
            ket_qua.push_back(ds_[i]);
    }
    if (!ket_qua.empty()) InBang(ket_qua);
    return static_cast<int>(ket_qua.size());
}

// ---------------------- Hiển thị ----------------------
void QuanLiHangHoa::HienThi() const { InBang(ds_); }

void QuanLiHangHoa::HienThiSapXep(int cach) const {
    if (ds_.empty()) return;
    vector<HangHoa> ban_sao = ds_;  // sắp xếp trên bản sao, không đổi thứ tự gốc
    int n = SoLuong();
    switch (cach) {
    case 1:
        tienich::ThongTin("Sap xep theo ten A-Z (Sap xep chen - Insertion Sort)");
        SapXepChen(&ban_sao[0], n, TenAZ);
        break;
    case 2:
        tienich::ThongTin("Sap xep theo gia tang dan (Sap xep chon - Selection Sort)");
        SapXepChon(&ban_sao[0], n, GiaTangDan);
        break;
    case 3:
        tienich::ThongTin("Sap xep theo gia giam dan (Sap xep nhanh - Quick Sort)");
        SapXepNhanh(&ban_sao[0], 0, n - 1, GiaGiamDan);
        break;
    case 4:
        tienich::ThongTin("Sap xep theo so luong giam dan (Sap xep nhanh - Quick Sort)");
        SapXepNhanh(&ban_sao[0], 0, n - 1, SoLuongGiamDan);
        break;
    default:
        tienich::ThongTin("Sap xep theo ma hang tang dan");
        break;
    }
    InBang(ban_sao);
}
