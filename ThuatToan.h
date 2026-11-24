// ThuatToan.h - Các thuật toán sắp xếp dạng template, áp dụng cho mảng.
// dung_truoc(a, b) trả về true nếu phần tử a phải đứng TRƯỚC phần tử b.
#pragma once

#include <utility>  // std::swap

// Sắp xếp chèn (Insertion Sort): độ phức tạp O(n^2), ổn định.
template <class KieuDL>
void SapXepChen(KieuDL mang[], int n,
    bool (*dung_truoc)(const KieuDL&, const KieuDL&)) {
    for (int i = 1; i < n; ++i) {
        KieuDL can_chen = mang[i];
        int j = i - 1;
        while (j >= 0 && dung_truoc(can_chen, mang[j])) {
            mang[j + 1] = mang[j];  // dời phần tử sang phải
            --j;
        }
        mang[j + 1] = can_chen;
    }
}

// Sắp xếp chọn (Selection Sort): độ phức tạp O(n^2).
template <class KieuDL>
void SapXepChon(KieuDL mang[], int n,
    bool (*dung_truoc)(const KieuDL&, const KieuDL&)) {
    for (int i = 0; i < n - 1; ++i) {
        int vi_tri_tot_nhat = i;
        for (int j = i + 1; j < n; ++j) {
            if (dung_truoc(mang[j], mang[vi_tri_tot_nhat])) vi_tri_tot_nhat = j;
        }
        if (vi_tri_tot_nhat != i) std::swap(mang[i], mang[vi_tri_tot_nhat]);
    }
}

// Sắp xếp nhanh (Quick Sort): trung bình O(n log n). Gọi: (mang, 0, n - 1, ...).
template <class KieuDL>
void SapXepNhanh(KieuDL mang[], int trai, int phai,
    bool (*dung_truoc)(const KieuDL&, const KieuDL&)) {
    if (trai >= phai) return;
    KieuDL chot = mang[(trai + phai) / 2];
    int i = trai;
    int j = phai;
    while (i <= j) {
        while (dung_truoc(mang[i], chot)) ++i;
        while (dung_truoc(chot, mang[j])) --j;
        if (i <= j) {
            std::swap(mang[i], mang[j]);
            ++i;
            --j;
        }
    }
    SapXepNhanh(mang, trai, j, dung_truoc);
    SapXepNhanh(mang, i, phai, dung_truoc);
}
