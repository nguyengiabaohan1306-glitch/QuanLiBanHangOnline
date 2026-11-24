// UngDung.h - Lớp điều khiển chương trình: menu và các chức năng.
#pragma once

#include <string>

#include "QuanLiAdmin.h"
#include "QuanLiDonHang.h"
#include "QuanLiHangHoa.h"

class UngDung {
public:
    UngDung();
    void ChayChuongTrinh();

private:
    enum KetQuaDangNhap { kDangNhapThanhCong, kDangNhapThoat, kDangNhapHuy };

    // Trả về false nếu người dùng nhấn Ctrl+Z.
    static bool NhapLuaChon(int nho_nhat, int lon_nhat, int* lua_chon);
    static void BaoLoiVaDung(const std::string& noi_dung);
    static void BaoHuy();  // thông báo đã hủy thao tác (Ctrl+Z)

    // Chức năng dành cho khách hàng.
    void HienThiHangHoa();
    void TimKiemHangHoa();
    void DatHang();

    // Chức năng dành cho nhân viên quản lí.
    KetQuaDangNhap DangNhap();
    void KhuVucQuanLi();
    void XuLiDonHang();
    void MenuQuanLiHangHoa();
    void ThemHangHoa();
    void XoaHangHoa();
    void CapNhatSoLuong();
    void DocDuLieuTuFile();
    void LuuDuLieuRaFile();

    QuanLiHangHoa hang_hoa_;
    QuanLiDonHang don_hang_;
    QuanLiAdmin admin_;
};
