// HangDoi.h - Hàng đợi FIFO (template) dùng DanhSachLienKet:
// đơn đặt trước thì được xử lí trước.
#pragma once

#include "DanhSachLienKet.h"

template <class KieuDL>
class HangDoi {
public:
    void ThemVaoHang(const KieuDL& gia_tri) { ds_.ThemCuoi(gia_tri); }
    bool LayRaKhoiHang(KieuDL* ra) { return ds_.LayDau(ra); }
    bool Rong() const { return ds_.Rong(); }
    int KichThuoc() const { return ds_.KichThuoc(); }

private:
    DanhSachLienKet<KieuDL> ds_;
};
