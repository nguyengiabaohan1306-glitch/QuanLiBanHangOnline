// DanhSachLienKet.h - Danh sách liên kết đơn (template, cài đặt trong header).
#pragma once

template <class KieuDL>
class DanhSachLienKet {
public:
    // Một nút của danh sách. Để public để bên ngoài có thể duyệt danh sách:
    // for (Nut* p = ds.dau(); p != nullptr; p = p->tiep) ...
    struct Nut {
        explicit Nut(const KieuDL& gia_tri) : du_lieu(gia_tri), tiep(nullptr) {}
        KieuDL du_lieu;
        Nut* tiep;
    };

    DanhSachLienKet() : dau_(nullptr), cuoi_(nullptr), kich_thuoc_(0) {}
    ~DanhSachLienKet() { XoaTatCa(); }
    DanhSachLienKet(const DanhSachLienKet&) = delete;
    DanhSachLienKet& operator=(const DanhSachLienKet&) = delete;

    // Thêm vào cuối danh sách.
    void ThemCuoi(const KieuDL& gia_tri) {
        Nut* nut_moi = new Nut(gia_tri);
        if (cuoi_ == nullptr) {
            dau_ = nut_moi;
            cuoi_ = nut_moi;
        }
        else {
            cuoi_->tiep = nut_moi;
            cuoi_ = nut_moi;
        }
        ++kich_thuoc_;
    }

    // Lấy phần tử đầu ra khỏi danh sách và xóa nó. Trả về false nếu rỗng.
    bool LayDau(KieuDL* ra) {
        if (dau_ == nullptr) return false;
        Nut* nut = dau_;
        *ra = nut->du_lieu;
        dau_ = nut->tiep;
        if (dau_ == nullptr) cuoi_ = nullptr;
        delete nut;
        --kich_thuoc_;
        return true;
    }

    void XoaTatCa() {
        while (dau_ != nullptr) {
            Nut* nut = dau_;
            dau_ = dau_->tiep;
            delete nut;
        }
        cuoi_ = nullptr;
        kich_thuoc_ = 0;
    }

    Nut* dau() const { return dau_; }
    int KichThuoc() const { return kich_thuoc_; }
    bool Rong() const { return kich_thuoc_ == 0; }

private:
    Nut* dau_;
    Nut* cuoi_;
    int kich_thuoc_;
};
