// TienIch.cpp
#include "TienIch.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using std::cout;
using std::string;
using std::vector;

namespace tienich {

    void KhoiTao() {
#ifdef _WIN32
        SetConsoleOutputCP(65001);
#endif
    }

    void DatMau(Mau mau) {
#ifdef _WIN32
        static const int ma_mau[] = { 7, 10, 12, 14, 11 };
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ma_mau[mau]);
#else
        static const char* ma_mau[] = { "\033[0m", "\033[32m", "\033[31m", "\033[33m",
                                        "\033[36m" };
        cout << ma_mau[mau];
#endif
    }

    void ThongTin(const string& noi_dung) {
        DatMau(kXanhDuong);
        cout << noi_dung << "\n";
        DatMau(kMacDinh);
    }

    void ThanhCong(const string& noi_dung) {
        DatMau(kXanhLa);
        cout << noi_dung << "\n";
        DatMau(kMacDinh);
    }

    void BaoLoi(const string& noi_dung) {
        DatMau(kDo);
        cout << "[LOI] " << noi_dung << "\n";
        DatMau(kMacDinh);
    }

    void InChucNang(const string& noi_dung) {
        DatMau(kVang);
        cout << noi_dung << "\n";
        DatMau(kMacDinh);
    }

    void InThoat(const string& noi_dung) {
        DatMau(kDo);
        cout << noi_dung << "\n";
        DatMau(kMacDinh);
    }

    int LayPhim() {
#ifdef _WIN32
        return _getch();
#else
        termios cu, moi;
        tcgetattr(STDIN_FILENO, &cu);
        moi = cu;
        moi.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &moi);
        int phim = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &cu);
        return phim;
#endif
    }

    void TamDung() {
        DatMau(kVang);
        cout << "\nNhan Enter de tiep tuc...";
        DatMau(kMacDinh);
        string tam;
        if (!std::getline(std::cin, tam)) {  // Ctrl+Z / hết dữ liệu: bỏ qua
            std::cin.clear();
            clearerr(stdin);
        }
    }

    void GoiYHuy() {
        DatMau(kVang);
        cout << "(Nhan Ctrl+Z roi Enter bat cu luc nao de huy thao tac)\n";
        DatMau(kMacDinh);
    }

    void XoaManHinh() {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    string CatKhoangTrang(const string& chuoi) {
        size_t dau = chuoi.find_first_not_of(" \t\r\n");
        if (dau == string::npos) return "";
        size_t cuoi = chuoi.find_last_not_of(" \t\r\n");
        return chuoi.substr(dau, cuoi - dau + 1);
    }

    vector<string> TachChuoi(const string& chuoi, char ky_tu_tach) {
        vector<string> ket_qua;
        string phan;
        std::stringstream luong(chuoi);
        while (std::getline(luong, phan, ky_tu_tach)) ket_qua.push_back(phan);
        if (!chuoi.empty() && chuoi[chuoi.size() - 1] == ky_tu_tach)
            ket_qua.push_back("");
        return ket_qua;
    }

    string ChuThuong(string chuoi) {
        for (size_t i = 0; i < chuoi.size(); ++i)
            chuoi[i] = static_cast<char>(
                std::tolower(static_cast<unsigned char>(chuoi[i])));
        return chuoi;
    }

    // Đếm số kí tự UTF-8 (không đếm byte) để căn lề bảng cho đúng.
    size_t DoDaiUtf8(const string& chuoi) {
        size_t do_dai = 0;
        for (size_t i = 0; i < chuoi.size(); ++i)
            if ((static_cast<unsigned char>(chuoi[i]) & 0xC0) != 0x80) ++do_dai;
        return do_dai;
    }

    string CanLe(const string& chuoi, size_t do_rong) {
        size_t do_dai = DoDaiUtf8(chuoi);
        return do_dai >= do_rong ? chuoi : chuoi + string(do_rong - do_dai, ' ');
    }

    bool ToanChuSo(const string& chuoi) {
        if (chuoi.empty()) return false;
        for (size_t i = 0; i < chuoi.size(); ++i)
            if (!std::isdigit(static_cast<unsigned char>(chuoi[i]))) return false;
        return true;
    }

    bool NgayHopLe(const string& chuoi) {
        vector<string> phan = TachChuoi(chuoi, '/');
        if (phan.size() != 3 || !ToanChuSo(phan[0]) || !ToanChuSo(phan[1]) ||
            !ToanChuSo(phan[2]) || phan[2].size() != 4)
            return false;
        int ngay = std::stoi(phan[0]);
        int thang = std::stoi(phan[1]);
        int nam = std::stoi(phan[2]);
        if (thang < 1 || thang > 12 || ngay < 1 || nam < 1900) return false;
        int so_ngay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if ((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0) so_ngay[1] = 29;
        return ngay <= so_ngay[thang - 1];
    }

    // Đọc một dòng. Trả về false nếu người dùng nhấn Ctrl+Z (kí tự 26) hoặc hết dữ liệu.
    bool DocDong(string* dong) {
        bool bi_huy = !std::getline(std::cin, *dong) || std::cin.eof() ||
            dong->find('\x1a') != string::npos;
        if (bi_huy) {
            std::cin.clear();
            clearerr(stdin);
            cout << "\n";
            return false;
        }
        return true;
    }

    bool NhapBatBuoc(const string& loi_nhac, string* ket_qua) {
        while (true) {
            cout << loi_nhac;
            string dong;
            if (!DocDong(&dong)) return false;
            dong = CatKhoangTrang(dong);
            if (dong.empty()) {
                BaoLoi("Khong duoc de trong hoac nhap khoang trang.");
                continue;
            }
            if (dong.find('|') != string::npos) {
                BaoLoi("Khong duoc chua ki tu '|'.");
                continue;
            }
            *ket_qua = dong;
            return true;
        }
    }

    bool NhapSo(const string& loi_nhac, long long* ket_qua) {
        while (true) {
            string dong;
            if (!NhapBatBuoc(loi_nhac, &dong)) return false;
            if (ToanChuSo(dong) && dong.size() <= 12) {
                *ket_qua = std::stoll(dong);
                return true;
            }
            BaoLoi("Vui long nhap so nguyen khong am.");
        }
    }

    bool NhapNgay(const string& loi_nhac, string* ket_qua) {
        while (true) {
            string dong;
            if (!NhapBatBuoc(loi_nhac, &dong)) return false;
            if (NgayHopLe(dong)) {
                *ket_qua = dong;
                return true;
            }
            BaoLoi("Ngay khong hop le (dinh dang dd/mm/yyyy).");
        }
    }

    KetQuaNhap NhapAn(string* ket_qua, bool an_ky_tu) {
        ket_qua->clear();
        while (true) {
            int phim = LayPhim();
            if (phim == 27) return kNhanEsc;
            if (phim == 26 || phim == 4) {  // Ctrl+Z (Windows) hoặc Ctrl+D (Linux)
                cout << "\n";
                return kNhanCtrlZ;
            }
            if (phim == '\r' || phim == '\n') {
                cout << "\n";
                return kNhapXong;
            }
            if (phim == 8 || phim == 127) {  // Backspace
                if (!ket_qua->empty()) {
                    ket_qua->pop_back();
                    cout << "\b \b";
                }
            }
            else if (phim >= 32) {
                ket_qua->push_back(static_cast<char>(phim));
                cout << (an_ky_tu ? '*' : static_cast<char>(phim));
            }
            cout.flush();
        }
    }

}  // namespace tienich
