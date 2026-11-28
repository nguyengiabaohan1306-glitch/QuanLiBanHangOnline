// TienIch.h - Các hàm tiện ích: màu console, nhập liệu, kiểm tra hợp lệ.
#pragma once

#include <string>
#include <vector>

namespace tienich {

	enum Mau { kMacDinh = 0, kXanhLa, kDo, kVang, kXanhDuong };

	// Kết quả của hàm NhapAn (nhập user/password).
	enum KetQuaNhap { kNhapXong = 0, kNhanEsc, kNhanCtrlZ };

	void KhoiTao();
	void DatMau(Mau mau);
	void ThongTin(const std::string& noi_dung);
	void ThanhCong(const std::string& noi_dung);
	void BaoLoi(const std::string& noi_dung);
	void InChucNang(const std::string& noi_dung);  // dòng chức năng: màu vàng
	void InThoat(const std::string& noi_dung);     // dòng thoát/quay lại: màu đỏ
	void TamDung();
	void GoiYHuy();  // in dòng nhắc "Ctrl+Z để hủy"
	void XoaManHinh();
	int LayPhim();

	std::string CatKhoangTrang(const std::string& chuoi);
	std::vector<std::string> TachChuoi(const std::string& chuoi, char ky_tu_tach);
	std::string ChuThuong(std::string chuoi);
	size_t DoDaiUtf8(const std::string& chuoi);  // số kí tự (không phải số byte)
	std::string CanLe(const std::string& chuoi, size_t do_rong);
	bool ToanChuSo(const std::string& chuoi);
	bool NgayHopLe(const std::string& chuoi);  // định dạng dd/mm/yyyy

	// Các hàm nhập liệu: trả về false nếu người dùng nhấn Ctrl+Z (rồi Enter) để hủy.
	bool DocDong(std::string* dong);
	// Không cho để trống / chỉ có khoảng trắng / chứa kí tự '|'.
	bool NhapBatBuoc(const std::string& loi_nhac, std::string* ket_qua);
	bool NhapSo(const std::string& loi_nhac, long long* ket_qua);
	bool NhapNgay(const std::string& loi_nhac, std::string* ket_qua);
	// Nhập một dòng, có thể ẩn kí tự (hiện '*'). Nhấn ESC hoặc Ctrl+Z để dừng.
	KetQuaNhap NhapAn(std::string* ket_qua, bool an_ky_tu);

}  // namespace tienich
