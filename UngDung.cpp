// UngDung.cpp
#include "UngDung.h"

#include <cstdlib>
#include <iostream>
#include <vector>

#include "TienIch.h"

using std::cout;
using std::string;
using std::vector;

UngDung::UngDung()
    : hang_hoa_("HangHoa.txt"), don_hang_("DonHang.txt"), admin_("Admin.txt") {}

void UngDung::ChayChuongTrinh() {
    while (true) {
        tienich::XoaManHinh();
        tienich::ThongTin("===== QUAN LI BAN HANG ONLINE =====");
        tienich::InChucNang("1. Hien thi thong tin hang hoa");
        tienich::InChucNang("2. Tim kiem thong tin hang hoa");
        tienich::InChucNang("3. Dat hang");
        tienich::InChucNang("4. Quan li");
        tienich::InThoat("0. Thoat");
        int lua_chon;
        if (!NhapLuaChon(0, 4, &lua_chon)) return;  // Ctrl+Z ở menu chính: thoát
        switch (lua_chon) {
        case 1: HienThiHangHoa(); break;
        case 2: TimKiemHangHoa(); break;
        case 3: DatHang(); break;
        case 4: KhuVucQuanLi(); break;
        case 0: return;
        }
    }
}

bool UngDung::NhapLuaChon(int nho_nhat, int lon_nhat, int* lua_chon) {
    while (true) {
        cout << "Chon chuc nang: ";
        string dong;
        if (!tienich::DocDong(&dong)) return false;
        dong = tienich::CatKhoangTrang(dong);
        if (tienich::ToanChuSo(dong) && dong.size() < 4) {
            int gia_tri = std::stoi(dong);
            if (gia_tri >= nho_nhat && gia_tri <= lon_nhat) {
                *lua_chon = gia_tri;
                return true;
            }
        }
        tienich::BaoLoi("Lua chon khong hop le.");
    }
}

void UngDung::BaoLoiVaDung(const string& noi_dung) {
    tienich::BaoLoi(noi_dung);
    tienich::TamDung();
}

void UngDung::BaoHuy() {
    tienich::ThongTin("Da huy thao tac.");
    tienich::TamDung();
}

// ---------------------- Khách hàng ----------------------
void UngDung::HienThiHangHoa() {
    int cach = 5;  // mặc định hiển thị theo mã
    while (true) {
        tienich::XoaManHinh();
        tienich::ThongTin("--- DANH SACH HANG HOA ---");
        if (hang_hoa_.Rong()) return BaoLoiVaDung("Chua co hang hoa nao.");
        hang_hoa_.HienThiSapXep(cach);
        cout << "\nSap xep danh sach theo:\n";
        tienich::InChucNang("1. Ten A-Z          (Sap xep chen)");
        tienich::InChucNang("2. Gia tang dan     (Sap xep chon)");
        tienich::InChucNang("3. Gia giam dan     (Sap xep nhanh)");
        tienich::InChucNang("4. So luong giam dan (Sap xep nhanh)");
        tienich::InChucNang("5. Ma hang");
        tienich::InThoat("0. Quay lai");
        if (!NhapLuaChon(0, 5, &cach) || cach == 0) return;
    }
}

void UngDung::TimKiemHangHoa() {
    tienich::XoaManHinh();
    tienich::ThongTin("--- TIM KIEM HANG HOA ---");
    tienich::GoiYHuy();
    string ten;
    if (!tienich::NhapBatBuoc("Nhap ten hang: ", &ten)) return BaoHuy();
    if (hang_hoa_.TimTheoTen(ten) == 0)
        tienich::BaoLoi("Khong tim thay hang hoa.");
    tienich::TamDung();
}

void UngDung::DatHang() {
    tienich::XoaManHinh();
    tienich::ThongTin("--- DAT HANG ---");
    tienich::GoiYHuy();
    if (hang_hoa_.Rong()) return BaoLoiVaDung("Chua co hang hoa de dat.");
    hang_hoa_.HienThi();
    cout << "\n";

    string ten_khach, dia_chi, so_dien_thoai, ngay_dat;
    if (!tienich::NhapBatBuoc("Ten khach hang: ", &ten_khach) ||
        !tienich::NhapBatBuoc("Dia chi khach hang: ", &dia_chi)) {
        return BaoHuy();
    }
    while (true) {
        if (!tienich::NhapBatBuoc("So dien thoai: ", &so_dien_thoai))
            return BaoHuy();
        if (tienich::ToanChuSo(so_dien_thoai) && so_dien_thoai.size() >= 9 &&
            so_dien_thoai.size() <= 11)
            break;
        tienich::BaoLoi("So dien thoai phai gom 9-11 chu so.");
    }
    if (!tienich::NhapNgay("Ngay dat hang (dd/mm/yyyy): ", &ngay_dat))
        return BaoHuy();

    DonHang don;
    don.DatThongTin(don_hang_.SoThuTuTiepTheo(), ten_khach, dia_chi,
        so_dien_thoai, ngay_dat);

    while (true) {
        string ma;
        if (!tienich::NhapBatBuoc("Ma hang (4 ki tu): ", &ma)) return BaoHuy();
        HangHoa* hang = hang_hoa_.TimTheoMa(ma);  // tìm kiếm nhị phân
        if (hang == nullptr)
            return BaoLoiVaDung("Ma hang khong ton tai. Huy dat hang.");
        if (hang->so_luong() <= 0)
            return BaoLoiVaDung("Mat hang da het hang. Huy dat hang.");
        if (don.CoMaHang(ma))
            return BaoLoiVaDung("Ma hang bi trung trong don. Huy dat hang.");

        long long so_luong = 0;
        if (!tienich::NhapSo("So luong: ", &so_luong)) return BaoHuy();
        if (so_luong <= 0)
            return BaoLoiVaDung("So luong phai lon hon 0. Huy dat hang.");
        if (so_luong > hang->so_luong())
            return BaoLoiVaDung("So luong vuot qua so luong dang co. Huy dat hang.");

        ChiTietDon chi_tiet = { ma, so_luong, so_luong * hang->gia_ban() };
        don.ThemChiTiet(chi_tiet);

        string them_nua;
        if (!tienich::NhapBatBuoc("Them ma hang khac? (y/n): ", &them_nua))
            return BaoHuy();
        if (tienich::ChuThuong(them_nua) != "y") break;
    }

    don_hang_.ThemDon(don);
    if (!don_hang_.LuuFile()) return BaoLoiVaDung("Khong the ghi file DonHang.txt.");
    tienich::ThanhCong("Don hang dang cho xu li");
    cout << "So thu tu don: " << don.so_thu_tu()
        << " | Tong tien: " << don.tong_tien() << "\n";
    tienich::TamDung();
}

// ---------------------- Quản lí ----------------------
UngDung::KetQuaDangNhap UngDung::DangNhap() {
    for (int lan_thu = 1; lan_thu <= 3; ++lan_thu) {
        tienich::XoaManHinh();
        tienich::DatMau(tienich::kVang);
        cout << "* * * * * * * * * * * * * * * * *\n"
            << "*       DANG NHAP HE THONG      *\n"
            << "* * * * * * * * * * * * * * * * *\n"
            << "(ESC: thoat chuong trinh | Ctrl+Z: huy, quay lai menu)\n";
        tienich::DatMau(tienich::kMacDinh);
        string user, password;
        cout << "User: ";
        tienich::KetQuaNhap ket_qua = tienich::NhapAn(&user, false);
        if (ket_qua == tienich::kNhanEsc) return kDangNhapThoat;
        if (ket_qua == tienich::kNhanCtrlZ) return kDangNhapHuy;
        cout << "Password: ";
        ket_qua = tienich::NhapAn(&password, true);
        if (ket_qua == tienich::kNhanEsc) return kDangNhapThoat;
        if (ket_qua == tienich::kNhanCtrlZ) return kDangNhapHuy;
        if (admin_.KiemTra(user, password)) return kDangNhapThanhCong;
        tienich::BaoLoi("Sai user hoac password (lan " + std::to_string(lan_thu) +
            "/3).");
        tienich::TamDung();
    }
    tienich::BaoLoi("Nhap sai 3 lan.");
    return kDangNhapThoat;
}

void UngDung::KhuVucQuanLi() {
    KetQuaDangNhap ket_qua = DangNhap();
    if (ket_qua == kDangNhapHuy) return BaoHuy();  // Ctrl+Z: về menu chính
    if (ket_qua == kDangNhapThoat) {  // ESC hoặc sai 3 lần: thoát hệ thống
        tienich::ThongTin("Thoat khoi he thong.");
        std::exit(0);
    }
    while (true) {
        tienich::XoaManHinh();
        tienich::ThongTin("===== MENU QUAN LI =====");
        tienich::InChucNang("1. Xu li don hang (dang cho: " +
            std::to_string(don_hang_.SoLuong()) + ")");
        tienich::InChucNang("2. Quan li hang hoa");
        tienich::InThoat("0. Quay lai");
        int lua_chon;
        if (!NhapLuaChon(0, 2, &lua_chon) || lua_chon == 0) return;
        if (lua_chon == 1) XuLiDonHang();
        else MenuQuanLiHangHoa();
    }
}

// Xử lí đơn đầu hàng đợi: trừ số lượng hàng, xóa đơn khỏi danh sách.
void UngDung::XuLiDonHang() {
    tienich::XoaManHinh();
    tienich::ThongTin("--- XU LI DON HANG ---");
    if (don_hang_.Rong()) return BaoLoiVaDung("Khong co don hang nao dang cho.");

    DonHang don;
    don_hang_.LayDonDau(&don);  // lấy đơn đặt sớm nhất ra khỏi hàng đợi

    // Kiểm tra đủ hàng trước khi trừ kho.
    const vector<ChiTietDon>& danh_sach = don.chi_tiet();
    bool hop_le = true;
    for (size_t i = 0; i < danh_sach.size() && hop_le; ++i) {
        HangHoa* hang = hang_hoa_.TimTheoMa(danh_sach[i].ma_hang);
        if (hang == nullptr || hang->so_luong() < danh_sach[i].so_luong) {
            tienich::BaoLoi("Don " + std::to_string(don.so_thu_tu()) + ": hang '" +
                danh_sach[i].ma_hang + "' khong du/khong ton tai. Huy don.");
            hop_le = false;
        }
    }
    if (hop_le) {
        for (size_t i = 0; i < danh_sach.size(); ++i) {
            HangHoa* hang = hang_hoa_.TimTheoMa(danh_sach[i].ma_hang);
            hang->set_so_luong(hang->so_luong() - danh_sach[i].so_luong);
        }
        tienich::ThanhCong("Da xu li xong don so " + std::to_string(don.so_thu_tu()));
        cout << "Khach hang: " << don.ten_khach()
            << " | SDT: " << don.so_dien_thoai()
            << " | Dia chi: " << don.dia_chi()
            << "\nTong tien: " << don.tong_tien() << "\n";
    }
    if (!hang_hoa_.LuuFile() || !don_hang_.LuuFile())
        tienich::BaoLoi("Loi ghi file du lieu.");
    tienich::TamDung();
}

void UngDung::MenuQuanLiHangHoa() {
    while (true) {
        tienich::XoaManHinh();
        tienich::ThongTin("--- QUAN LI HANG HOA ---");
        tienich::InChucNang("1. Them hang hoa moi");
        tienich::InChucNang("2. Xoa hang hoa theo ma");
        tienich::InChucNang("3. Cap nhat so luong hang hoa");
        tienich::InChucNang("4. Doc du lieu hang hoa tu file");
        tienich::InChucNang("5. Luu du lieu hang hoa ra file");
        tienich::InThoat("0. Quay lai");
        int lua_chon;
        if (!NhapLuaChon(0, 5, &lua_chon) || lua_chon == 0) return;
        tienich::GoiYHuy();
        if (lua_chon == 1) ThemHangHoa();
        else if (lua_chon == 2) XoaHangHoa();
        else if (lua_chon == 3) CapNhatSoLuong();
        else if (lua_chon == 4) DocDuLieuTuFile();
        else LuuDuLieuRaFile();
    }
}

void UngDung::ThemHangHoa() {
    string ma;
    while (true) {
        if (!tienich::NhapBatBuoc("Ma hang (dung 4 ki tu): ", &ma)) return BaoHuy();
        if (ma.size() != 4) {
            tienich::BaoLoi("Ma hang phai du 4 ki tu.");
            continue;
        }
        if (hang_hoa_.TimTheoMa(ma) != nullptr) {
            tienich::BaoLoi("Ma hang da ton tai.");
            continue;
        }
        break;
    }
    string ten, noi_san_xuat, mau_sac, ngay_nhap;
    long long gia_ban = 0;
    long long so_luong = 0;
    if (!tienich::NhapBatBuoc("Ten hang: ", &ten) ||
        !tienich::NhapBatBuoc("Noi san xuat: ", &noi_san_xuat) ||
        !tienich::NhapBatBuoc("Mau sac: ", &mau_sac) ||
        !tienich::NhapSo("Gia ban: ", &gia_ban) ||
        !tienich::NhapNgay("Ngay nhap kho (dd/mm/yyyy): ", &ngay_nhap) ||
        !tienich::NhapSo("So luong: ", &so_luong)) {
        return BaoHuy();
    }
    hang_hoa_.Them(HangHoa(ma, ten, noi_san_xuat, mau_sac, gia_ban, ngay_nhap,
        so_luong));
    if (hang_hoa_.LuuFile()) tienich::ThanhCong("Da them hang hoa.");
    else tienich::BaoLoi("Khong the ghi file HangHoa.txt.");
    tienich::TamDung();
}

void UngDung::XoaHangHoa() {
    string ma;
    if (!tienich::NhapBatBuoc("Nhap ma hang can xoa: ", &ma)) return BaoHuy();
    if (!hang_hoa_.Xoa(ma)) return BaoLoiVaDung("Ma hang khong ton tai.");
    if (hang_hoa_.LuuFile()) tienich::ThanhCong("Da xoa hang hoa.");
    else tienich::BaoLoi("Khong the ghi file HangHoa.txt.");
    tienich::TamDung();
}

void UngDung::CapNhatSoLuong() {
    string ma;
    if (!tienich::NhapBatBuoc("Nhap ma hang can cap nhat: ", &ma)) return BaoHuy();
    HangHoa* hang = hang_hoa_.TimTheoMa(ma);
    if (hang == nullptr) return BaoLoiVaDung("Ma hang khong ton tai.");
    cout << "So luong hien tai: " << hang->so_luong() << "\n";
    long long so_luong_moi = 0;
    if (!tienich::NhapSo("So luong moi: ", &so_luong_moi)) return BaoHuy();
    hang->set_so_luong(so_luong_moi);
    if (hang_hoa_.LuuFile()) tienich::ThanhCong("Da cap nhat so luong.");
    else tienich::BaoLoi("Khong the ghi file HangHoa.txt.");
    tienich::TamDung();
}

// Đọc danh sách hàng hóa từ một file bất kì, thay thế danh sách hiện tại.
void UngDung::DocDuLieuTuFile() {
    string ten_file, xac_nhan;
    if (!tienich::NhapBatBuoc("Ten file can doc (vd: HangHoa.txt): ", &ten_file) ||
        !tienich::NhapBatBuoc(
            "Du lieu hang hoa hien tai se bi thay the. Tiep tuc? (y/n): ",
            &xac_nhan)) {
        return BaoHuy();
    }
    if (tienich::ChuThuong(xac_nhan) != "y") return BaoHuy();
    int so_hop_le = 0;
    int so_bo_qua = 0;
    if (!hang_hoa_.DocTuFile(ten_file, &so_hop_le, &so_bo_qua))
        return BaoLoiVaDung("Khong mo duoc file '" + ten_file + "'.");
    if (!hang_hoa_.LuuFile()) tienich::BaoLoi("Khong the ghi file HangHoa.txt.");
    tienich::ThanhCong("Da doc " + std::to_string(so_hop_le) +
        " hang hoa tu file '" + ten_file + "'.");
    if (so_bo_qua > 0)
        tienich::ThongTin("Bo qua " + std::to_string(so_bo_qua) +
            " dong sai dinh dang hoac trung ma.");
    tienich::TamDung();
}

// Lưu danh sách hàng hóa hiện tại ra một file bất kì.
void UngDung::LuuDuLieuRaFile() {
    string ten_file;
    if (!tienich::NhapBatBuoc("Ten file can luu (vd: HangHoa_SaoLuu.txt): ",
        &ten_file))
        return BaoHuy();
    if (!hang_hoa_.LuuRaFile(ten_file))
        return BaoLoiVaDung("Khong the ghi file '" + ten_file + "'.");
    tienich::ThanhCong("Da luu " + std::to_string(hang_hoa_.SoLuong()) +
        " hang hoa ra file '" + ten_file + "'.");
    tienich::TamDung();
}
