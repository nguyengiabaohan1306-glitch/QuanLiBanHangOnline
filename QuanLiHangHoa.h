// QuanLiHangHoa.h - Quản lí danh sách hàng hóa (file HangHoa.txt).
// Danh sách là một mảng LUÔN được giữ sắp xếp tăng dần theo mã hàng,
// nhờ đó tra cứu theo mã dùng được tìm kiếm nhị phân (O(log n)).
#pragma once

#include <string>
#include <vector>

#include "HangHoa.h"

class QuanLiHangHoa {
public:
    explicit QuanLiHangHoa(const std::string& ten_file);

    // Đọc / lưu file mặc định (HangHoa.txt).
    void DocFile();
    bool LuuFile() const;

    // Đọc từ file bất kì, thay thế danh sách hiện tại.
    // Trả về false nếu không mở được file (danh sách giữ nguyên).
    // so_hop_le: số hàng hóa đọc được; so_bo_qua: số dòng sai định dạng/trùng mã.
    bool DocTuFile(const std::string& ten_file, int* so_hop_le, int* so_bo_qua);
    // Lưu danh sách hiện tại ra file bất kì.
    bool LuuRaFile(const std::string& ten_file) const;

    HangHoa* TimTheoMa(const std::string& ma);  // tìm kiếm nhị phân
    bool Them(const HangHoa& hang_hoa);  // false nếu mã sai độ dài hoặc bị trùng
    bool Xoa(const std::string& ma);
    bool Rong() const { return ds_.empty(); }
    int SoLuong() const { return static_cast<int>(ds_.size()); }

    void HienThi() const;
    // Hiển thị có sắp xếp: 1 = tên A-Z (sắp xếp chèn), 2 = giá tăng dần (sắp xếp
    // chọn), 3 = giá giảm dần (sắp xếp nhanh), 4 = số lượng giảm dần (sắp xếp
    // nhanh), 5 = theo mã (mặc định).
    void HienThiSapXep(int cach) const;
    // Tìm theo tên (không phân biệt hoa thường, khớp một phần): tìm tuần tự.
    // Trả về số kết quả tìm được.
    int TimTheoTen(const std::string& ten) const;

private:
    // Tìm nhị phân theo mã. Trả về vị trí trong mảng, hoặc -1 nếu không có.
    int TimNhiPhan(const std::string& ma) const;
    static void InBang(const std::vector<HangHoa>& danh_sach);

    std::string ten_file_;
    std::vector<HangHoa> ds_;  // luôn sắp xếp tăng dần theo mã
};
