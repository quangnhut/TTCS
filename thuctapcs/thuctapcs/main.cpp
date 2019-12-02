#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct date
{
	int ngay, thang, nam;
};
typedef struct date DATE;
//ham doc du lieu ngay sinh tu file txt
void DocNgaySinh(ifstream &filein, DATE &date)
{
	filein >> date.ngay;
	filein.seekg(1, 1);
	filein >> date.thang;
	filein.seekg(1, 1);
	filein >> date.nam;
}




//new change
struct nhanvien
{
	string hoten, chucvu, nguyenquan;
	DATE ngaysinh;
	float hesoluong;
	int cmnd;
};
typedef struct nhanvien NHANVIEN;
//khai bao cau truc 1 node nhan vien
struct node
{
	NHANVIEN data;
	struct node *pNext;
};
typedef struct node NODE;
//======KHAI BAO LINKED LIST CAC NHAN VIEN=====
struct list
{
	NODE *pHead;
	NODE *pTail;
};
typedef struct list LIST;
//ham khoi tao ds lien ket
void KhoiTaoDanhSach(LIST & l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}
//ham khoi tao 1 node them vao ds
NODE *KhoiTaoNode(NHANVIEN x)
{
	NODE *p = new NODE;
	if (p == NULL)
	{
		cout << "\nCap phat that bai";
		return NULL;
	}
	p->data = x;//dua du lieu cua nhan vien x vao data
	p->pNext = NULL;
	return p;
}
//ham them 1 node vao dau ds
void ThemDau(LIST &l, NODE *p)
{
	if (l.pHead==NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		p->pNext = l.pHead;//cho con tro p tro den head
		l.pHead = p;//cap nhat lai phead la node p
	}
}
//ham them 1 node vao cuoi ds
void ThemCuoi(LIST &l, NODE *p)
{
	if (l.pHead==NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;//cho con tro ptail tro den p
		l.pTail = p;//cap nhat lai ptail la node p
	}
}
//ham kiem tra
int ktra_giatri(int low, int high)
{
	int input;
	while (true)
	{
		while (!(cin >> input)) {
			cin.clear();
			cin.ignore(80, '\n');
			cout << "\nKhong hop le! Moi nhap lai: ";
		}
		if (input < low || input > high)
			cout << "Gia tri khong hop le, vui long nhap lai!\n";
		else
			break;
	}
	return input;
}
//ham doc du lieu 1 nhan vien tu file
void Doc_Thong_Tin_1_Nhan_Vien(ifstream &filein, NHANVIEN &nv)
{
		getline(filein, nv.hoten, ',');
		filein.seekg(1, 1);
		getline(filein, nv.chucvu, ',');
		filein.seekg(1, 1);
		DocNgaySinh(filein, nv.ngaysinh);
		filein.seekg(2, 1);
		filein >> nv.hesoluong;
		filein.seekg(2, 1);
		getline(filein, nv.nguyenquan, ',');
		filein.seekg(1, 1);
		filein >> nv.cmnd;
		//tao bien tam doc ky tu xuong dong
		string temp;
		getline(filein, temp);
}
//ham doc ds nhan vien tu file
void Doc_ds_Nhan_Vien(ifstream &filein, LIST &l)
{
	//doc den cuoi file thi dung
	while (!filein.eof())
	{
		//doc thong tin nhan vien
		NHANVIEN nv;
		Doc_Thong_Tin_1_Nhan_Vien(filein, nv);
		// khoi tao 1 node nhan vien
		NODE *p = KhoiTaoNode(nv);
		//them nhan vien vao linked list
		ThemCuoi(l, p);
	}
}
//ham giai phong vung nho
void Giai_Phong_Vung_Nho(LIST &l)
{ 
	NODE *p = NULL;
	while (l.pHead != NULL)
	{
		p = l.pHead;
		l.pHead = l.pHead->pNext;
		delete p;
	}
}
//ham hoan vi
void Hoan_Vi(NHANVIEN &x, NHANVIEN &y)
{
	NHANVIEN tam = x;
	x = y;
	y = tam;
}
//tach ten trong chuoi ho ten
string Tach_ten(string tennv)
{
	int lenght = tennv.length();
	int i;
	for (i = lenght-1; i >=0; i--)
	{
		if (tennv[i]==' ')
		{
			break;
		}
	}
	return tennv.substr(i + 1);
}
//sap xep theo he so luong
void Sap_Xep_Heso(LIST &l)
{
	for (NODE *k = l.pHead; k != NULL;k = k->pNext)
	{
		for (NODE *h = k->pNext; h != NULL;h = h->pNext)
		{
			if (k->data.hesoluong > h->data.hesoluong)
			{
				Hoan_Vi(k->data, h->data);
			}
		}
	}
}
//sap xep theo ngay sinh
void Sap_xep_ngay_sinh(LIST &l)
{
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		for (NODE *h = k->pNext; h != NULL; h = h->pNext)
		{
			if (k->data.ngaysinh.nam > h->data.ngaysinh.nam)
			{
				Hoan_Vi(k->data, h->data);
			}
			if (k->data.ngaysinh.nam == h->data.ngaysinh.nam)
			{
				if (k->data.ngaysinh.thang > h->data.ngaysinh.thang)
				{
					Hoan_Vi(k->data, h->data);
				}
				if (k->data.ngaysinh.thang == h->data.ngaysinh.thang)
				{
					if (k->data.ngaysinh.ngay > h->data.ngaysinh.ngay)
					{
						Hoan_Vi(k->data, h->data);
					}
				}
			}
		}
	}
}
//sap xep theo ten
void Sap_xep_ten(LIST &l)
{
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		for (NODE *h = k->pNext; h != NULL; h = h->pNext)
		{
			if (Tach_ten(k->data.hoten) > Tach_ten(h->data.hoten))
			{
				Hoan_Vi(k->data, h->data);
			}
		}
	}
}
//convert chuc vu
int Convert_chucvu(string cv)
{
	if (cv == "Tong giam doc" || cv=="tong giam doc")
	{
		return 1;
	}
	if (cv == "truong phong" || cv == "Truong phong")
	{
		return 2;
	}
	if (cv == "Thu ky vien" || cv == "thu ky vien")
	{
		return 3;
	}
	if (cv == "Nhan vien" || cv == "nhan vien")
	{
		return 4;
	}
}
//sap xep chuc vu
void Sap_xep_chucvu(LIST &l)
{
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		for (NODE *h = k->pNext; h != NULL; h = h->pNext)
		{
			if (Convert_chucvu(k->data.chucvu) > Convert_chucvu(h->data.chucvu))
			{
				Hoan_Vi(k->data, h->data);
			}
		}
	}
}
//chen nhan vien
void Chen_nhan_vien(LIST &l, NHANVIEN &nv)
{
	rewind(stdin);
	cout << "\nNhap ten nhan vien: ";
	getline(cin, nv.hoten);
	rewind(stdin);
	cout << "\nNhap chuc vu: ";
	getline(cin, nv.chucvu);
	cout << "\nNhap he so luong: ";
	while (!(cin >> nv.hesoluong)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai he so luong: ";
	}
	cout << "\nNhap ngay sinh: ";
	while (!(cin >> nv.ngaysinh.ngay)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai ngay sinh: ";
	}
	cout << "\nNhap thang sinh: ";
	while (!(cin >> nv.ngaysinh.thang)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai thang sinh: ";
	}
	cout << "\nNhap nam sinh: ";
	while (!(cin >> nv.ngaysinh.nam)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai nam sinh: ";
	}
	rewind(stdin);
	cout << "\nNhap nguyen quan: ";
	getline(cin, nv.nguyenquan);
	cout << "\nNhap so cmnd: ";
	while (!(cin >> nv.cmnd)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai so cmnd: ";
	}
	NODE *p = KhoiTaoNode(nv);
	ThemCuoi(l, p);
}
//xoa node dau
void Xoa_dau(LIST &l)
{
	if (l.pHead == NULL)
	{
		return;
	}
	NODE *p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;
}
//xoa node cuoi
void Xoa_cuoi(LIST &l)
{
	if (l.pHead == NULL)
	{
		return;
	}
	if (l.pHead->pNext==NULL)
	{
		Xoa_dau(l);
		return;
	}
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (k->pNext==l.pTail)
		{
			delete l.pTail;
			k->pNext = NULL;
			l.pTail = k;
			return;
		}
	}
}
//xoa theo he so
void Xoa_theo_he_so(LIST &l)
{
	int dem = 0;
	float heso;
	cout << "\nNhap vao he so: ";
	while (!(cin >> heso)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai he so: ";
	}
		if (l.pHead == NULL)
		{
			return;
		}
		if (l.pHead->data.hesoluong == heso)
		{
			dem = 1;
			Xoa_dau(l);
		}
		if (l.pTail->data.hesoluong == heso)
		{
			dem = 1;
			Xoa_cuoi(l);
		}
		NODE *g = new NODE;//node g tro den node truoc node can xoa
		for (NODE *k = l.pHead; k != NULL; k = k->pNext)
		{
			if (k->data.hesoluong == heso)
			{
				dem = 1;
				NODE *sau;
				sau = k->pNext;
				g->pNext = sau;
				delete k;
				k = g;
			}
			g = k;
		}
		if (dem == 0)
		{
			cout << "\n====Khong co nhan vien phu hop! Moi nhap lai=====";
		}
		if (dem == 1)
		{
			cout << "\n=====Xoa thanh cong=====";
		}
}
//xoa theo nam sinh
void Xoa_theo_namsinh(LIST &l)
{
	int dem = 0;
	int namsinh, ngaysinh, thangsinh;
	cout << "\nNhap vao ngay sinh: ";
	while (!(cin >> ngaysinh)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai ngay sinh: ";
	}
	cout << "\nNhap vao thang sinh: ";
	while (!(cin >> thangsinh)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai thang sinh: ";
	}
	cout << "\nNhap vao nam sinh: ";
	while (!(cin >> namsinh)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai nam sinh: ";
	}
	if (l.pHead == NULL)
	{
		return;
	}
	if (l.pHead->data.ngaysinh.nam == namsinh && l.pHead->data.ngaysinh.ngay == ngaysinh && l.pHead->data.ngaysinh.thang == thangsinh)
	{
		dem = 1;
		Xoa_dau(l);
	}
	if (l.pTail->data.ngaysinh.nam == namsinh && l.pTail->data.ngaysinh.ngay == ngaysinh && l.pTail->data.ngaysinh.thang == thangsinh)
	{
		dem = 1;
		Xoa_cuoi(l);
	}
	NODE *g = new NODE;//node g tro den node truoc node can xoa
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.ngaysinh.nam == namsinh && k->data.ngaysinh.ngay == ngaysinh && k->data.ngaysinh.thang == thangsinh)
		{
			dem = 1;
			NODE *sau;
			sau = k->pNext;
			g->pNext = sau;
			delete k;
			k = g;
		}
		g = k;
	}
	if (dem == 0)
	{
		cout << "\n====Khong co nhan vien phu hop! Moi nhap lai=====";
	}
	if (dem == 1)
	{
		cout << "\n=====Xoa thanh cong=====";
	}
}
//xoa theo ten
void Xoa_theo_ten(LIST &l)
{
	int dem = 0;
	string ten;
	rewind(stdin);
	cout << "\nNhap vao ten: ";
	getline(cin, ten);
	if (l.pHead == NULL)
	{
		return;
	}
	if (_stricmp((char *)ten.c_str(), (char *)Tach_ten(l.pHead->data.hoten).c_str()) == 0)
	{
		dem = 1;
		Xoa_dau(l);
	}
	if (_stricmp((char *)ten.c_str(), (char *)Tach_ten(l.pTail->data.hoten).c_str()) == 0)
	{
		dem = 1;
		Xoa_cuoi(l);
	}
	NODE *g = new NODE;//node g tro den node truoc node can xoa
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char *)ten.c_str(), (char *)Tach_ten(k->data.hoten).c_str()) == 0)
		{
			dem = 1;
			NODE *sau;
			sau = k->pNext;
			g->pNext = sau;
			delete k;
			k = g;
		}
		g = k;
	}
	if (dem == 0)
	{
		cout << "\n====Khong co nhan vien phu hop! Moi nhap lai=====";
	}
	if (dem == 1)
	{
		cout << "\n=====Xoa thanh cong=====";
	}
}
//xoa theo chuc vu
void Xoa_theo_chucvu(LIST &l)
{
	int dem = 0;
	string chucvu;
	rewind(stdin);
	cout << "\nNhap vao chuc vu: ";
	getline(cin, chucvu);
	if (l.pHead == NULL)
	{
		return;
	}
	if (_stricmp((char *)chucvu.c_str(), (char *)l.pHead->data.chucvu.c_str()) == 0)
	{
		dem = 1;
		Xoa_dau(l);
	}
	if (_stricmp((char *)chucvu.c_str(), (char *)l.pTail->data.chucvu.c_str()) == 0)
	{
		dem = 1;
		Xoa_cuoi(l);
	}
	NODE *g = new NODE;//node g tro den node truoc node can xoa
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char *)chucvu.c_str(), (char *)k->data.chucvu.c_str()) == 0)
		{
			dem = 1;
			NODE *sau;
			sau = k->pNext;
			g->pNext = sau;
			delete k;
			k = g;
		}
		g = k;
	}
	if (dem == 0)
	{
		cout << "\n====Khong co nhan vien phu hop! Moi nhaplai=====";
	}
	if (dem == 1)
	{
		cout << "\n=====Xoa thanh cong=====";
	}
}
//xoa theo nguyen quan
void Xoa_theo_nguyenquan(LIST &l)
{
	int dem = 0;
	string nguyenquan;
	rewind(stdin);
	cout << "\nNhap vao nguyen quan: ";
	getline(cin, nguyenquan);
	if (l.pHead == NULL)
	{
		return;
	}
	if (_stricmp((char *)nguyenquan.c_str(), (char *)l.pHead->data.nguyenquan.c_str()) == 0)
	{
		dem = 1;
		Xoa_dau(l);
	}
	if (_stricmp((char *)nguyenquan.c_str(), (char *)l.pTail->data.nguyenquan.c_str()) == 0)
	{
		dem = 1;
		Xoa_cuoi(l);
	}
	NODE *g = new NODE;//node g tro den node truoc node can xoa
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char *)nguyenquan.c_str(), (char *)k->data.nguyenquan.c_str()) == 0)
		{
			dem = 1;
			NODE *sau;
			sau = k->pNext;
			g->pNext = sau;
			delete k;
			k = g;
		}
		g = k;
	}
	if (dem == 0)
	{
		cout << "\n====Khong co nhan vien phu hop! Moi nhaplai=====";
	}
	if (dem == 1)
	{
		cout << "\n=====Xoa thanh cong=====";
	}
}
//xoa theo cmnd
void Xoa_theo_cmnd(LIST &l)
{
	int dem = 0;
	float cmnd;
	cout << "\nNhap vao cmnd: ";
	while (!(cin >> cmnd)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai cmnd: ";
	}
	if (l.pHead == NULL)
	{
		return;
	}
	if (l.pHead->data.cmnd == cmnd)
	{
		dem = 1;
		Xoa_dau(l);
	}
	if (l.pTail->data.cmnd == cmnd)
	{
		dem = 1;
		Xoa_cuoi(l);
	}
	NODE *g = new NODE;//node g tro den node truoc node can xoa
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.cmnd == cmnd)
		{
			dem = 1;
			NODE *sau;
			sau = k->pNext;
			g->pNext = sau;
			delete k;
			k = g;
		}
		g = k;
	}
	if (dem == 0)
	{
		cout << "\n====Khong co nhan vien phu hop! Moi nhap lai=====";
	}
	if (dem == 1)
	{
		cout << "\n=====Xoa thanh cong=====";
	}
}
//ham xuat du lieu
void Xuat(NHANVIEN nv)
{
	cout << nv.hoten <<"\t"<< nv.chucvu << "\t" << nv.ngaysinh.ngay << "/" << nv.ngaysinh.thang << "/" << nv.ngaysinh.nam << "\t   " << nv.hesoluong<<"\t           "<<nv.nguyenquan<<"\t\t"<<nv.cmnd;
}
//ham xuat ds nhan vien
void Xuat_ds_Nhan_Vien(LIST l)
{
	int dem = 1;
	cout << "\n\n\t      Ho va ten\t          " << "Chuc vu\t" << "Ngay sinh\t" << "He so luong\t   " << "Nguyen quan\t\t" << "So CMND" << endl;
	cout << "\t---------------------------------------------------------------------------------------------------------";
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		cout << "\n\n\t" << dem++ <<" : ";
		Xuat(k->data);
	}
}
//tim kiem
void Tim_kiem_theo_heso(LIST &l)
{
	float data;
	int dem = 0;
	int vitri = 1;
	cout << "\nNhap vao he so can tim: ";
	while (!(cin >> data)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai he so: ";
	}
	cout << "\n\t      Ho va ten\t          " << "Chuc vu\t" << "Ngay sinh\t" << "He so luong\t   " << "Nguyen quan\t\t" << "So CMND" << endl;
	cout << "\t---------------------------------------------------------------------------------------------------------";
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (data==k->data.hesoluong)
		{
			dem++;
			cout << "\n\t" << vitri << " : " << k->data.hoten << "\t" << k->data.chucvu << "\t" << k->data.ngaysinh.ngay << "/" << k->data.ngaysinh.thang << "/" << k->data.ngaysinh.nam << "\t   " << k->data.hesoluong << "\t           " << k->data.nguyenquan << "\t\t" << k->data.cmnd << endl;
		}
		++vitri;
		
	}
	if (dem==0)
	{
		cout << "\n===Khong tim thay nhan vien nao!===";
	}
}
//tim kiem theo chuc vu
void Tim_kiem_theo_chucvu(LIST &l)
{
	int dem = 0;
	int vitri = 1;
	string data;
	cout << "\nNhap vao chuc vu can tim: ";
	rewind(stdin);
	getline(cin, data);
	cout << "\n\t      Ho va ten\t          " << "Chuc vu\t" << "Ngay sinh\t" << "He so luong\t   " << "Nguyen quan\t\t" << "So CMND" << endl;
	cout << "\t---------------------------------------------------------------------------------------------------------";
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char *)data.c_str(), (char *)k->data.chucvu.c_str()) == 0)
		{
			dem++;
			cout << "\n\t" << vitri << " : " << k->data.hoten << "\t" << k->data.chucvu << "\t" << k->data.ngaysinh.ngay << "/" << k->data.ngaysinh.thang << "/" << k->data.ngaysinh.nam << "\t   " << k->data.hesoluong << "\t           " << k->data.nguyenquan << "\t\t" << k->data.cmnd << endl;
		}
		++vitri;
	}
	if (dem == 0)
	{
		cout << "\n===Khong tim thay nhan vien nao!===";
	}
}
//tim kiem theo ten
void Tim_kiem_theo_ten(LIST &l)
{
	int dem = 0;
	int vitri = 1;
	string data;
	cout << "\nNhap vao ten can tim: ";
	rewind(stdin);
	getline(cin, data);
	cout << "\n\t      Ho va ten\t          " << "Chuc vu\t" << "Ngay sinh\t" << "He so luong\t   " << "Nguyen quan\t\t" << "So CMND" << endl;
	cout << "\t---------------------------------------------------------------------------------------------------------";
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char *)data.c_str(), (char *)Tach_ten(k->data.hoten).c_str()) == 0)
		{
			dem++;
			cout << "\n\t" << vitri << " : " << k->data.hoten << "\t" << k->data.chucvu << "\t" << k->data.ngaysinh.ngay << "/" << k->data.ngaysinh.thang << "/" << k->data.ngaysinh.nam << "\t   " << k->data.hesoluong << "\t           " << k->data.nguyenquan << "\t\t" << k->data.cmnd << endl;
		}
		++vitri;
	}
	if (dem == 0)
	{
		cout << "\n===Khong tim thay nhan vien nao!===";
	}
}
//tim kiem theo nam sinh
void Tim_kiem_namsinh(LIST &l)
{
	int dem = 0;
	int vitri = 1;
	int nam, thang, ngay;
	cout << "\nNhap vao ngay sinh: ";
	while (!(cin >> ngay)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai ngay sinh: ";
	}
	cout << "\nNhap vao thang sinh: ";
	while (!(cin >> thang)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai thang sinh: ";
	}
	cout << "\nNhap vao nam sinh: ";
	while (!(cin >> nam)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Nhap lai nam sinh: ";
	}
	cout << "\n\t      Ho va ten\t          " << "Chuc vu\t" << "Ngay sinh\t" << "He so luong\t   " << "Nguyen quan\t\t" << "So CMND" << endl;
	cout << "\t---------------------------------------------------------------------------------------------------------";
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (nam == k->data.ngaysinh.nam && thang == k->data.ngaysinh.thang && ngay == k->data.ngaysinh.ngay)
		{
			dem++;
			cout << "\n\t" << vitri << " : " << k->data.hoten << "\t" << k->data.chucvu << "\t" << k->data.ngaysinh.ngay << "/" << k->data.ngaysinh.thang << "/" << k->data.ngaysinh.nam << "\t   " << k->data.hesoluong << "\t           " << k->data.nguyenquan << "\t\t" << k->data.cmnd << endl;
		}
		++vitri;
	}
	if (dem == 0)
	{
		cout << "\n===Khong tim thay nhan vien nao!===";
	}
}
//tim kiem theo nguyen quan
void Tim_kiem_theo_nguyenquan(LIST &l)
{
	int dem = 0;
	int vitri = 1;
	string data;
	cout << "\nNhap vao nguyen quan can tim: ";
	rewind(stdin);
	getline(cin, data);
	cout << "\n\t      Ho va ten\t          " << "Chuc vu\t" << "Ngay sinh\t" << "He so luong\t   " << "Nguyen quan\t\t" << "So CMND" << endl;
	cout << "\t---------------------------------------------------------------------------------------------------------";
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char *)data.c_str(), (char *)k->data.nguyenquan.c_str()) == 0)
		{
			dem++;
			cout << "\n\t" << vitri << " : " << k->data.hoten << "\t" << k->data.chucvu << "\t" << k->data.ngaysinh.ngay << "/" << k->data.ngaysinh.thang << "/" << k->data.ngaysinh.nam << "\t   " << k->data.hesoluong << "\t           " << k->data.nguyenquan << "\t\t" << k->data.cmnd << endl;
		}
		++vitri;
	}
	if (dem == 0)
	{
		cout << "\n===Khong tim thay nhan vien nao!===";
	}
}
//tim kiem theo cmnd
void Tim_kiem_theo_cmnd(LIST &l)
{
	float data;
	int dem = 0;
	int vitri = 1;
	cout << "\nNhap vao cmnd can tim: ";
	while (!(cin >> data)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nKhong hop le! Moi nhap lai: ";
	}
	cout << "\n\t      Ho va ten\t          " << "Chuc vu\t" << "Ngay sinh\t" << "He so luong\t   " << "Nguyen quan\t\t" << "So CMND" << endl;
	cout << "\t---------------------------------------------------------------------------------------------------------";
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (data == k->data.cmnd)
		{
			dem++;
			
			cout << "\n\t" << vitri << " : " << k->data.hoten << "\t" << k->data.chucvu << "\t" << k->data.ngaysinh.ngay << "/" << k->data.ngaysinh.thang << "/" << k->data.ngaysinh.nam << "\t   " << k->data.hesoluong << "\t           " << k->data.nguyenquan << "\t\t" << k->data.cmnd << endl;
		}
		++vitri;
	}
	if (dem == 0)
	{
		cout << "\n===Khong tim thay nhan vien nao!===";
	}
}
//ham ghi thong tin 1 nhan vien vao file
void Ghi_Thong_Tin_1_Nhan_Vien(ofstream &fileout, NHANVIEN nv)
{
	fileout << nv.hoten << "\t\t";
	fileout << nv.chucvu << "\t\t";
	fileout << nv.ngaysinh.ngay << "/" << nv.ngaysinh.thang << "/" << nv.ngaysinh.nam << "\t\t\t\t";
	fileout << nv.hesoluong<<"\t\t\t";
	fileout << nv.nguyenquan << "\t\t\t";
	fileout << nv.cmnd;
}
//luu vao file export
void Xuat_ra_export(LIST l)
{
	ofstream fileout;
	fileout.open("export.txt", ios::out);
	fileout << "=======================================================================================================================================================================" << endl;
	fileout << "Ho va ten\t\t||\tChuc vu\t\t||\tNgay sinh\t\t||\t\tHe so luong\t||\tNguyen quan\t\t||\tCMND" << endl;
	fileout << "=======================================================================================================================================================================" << endl;
	for (NODE *k = l.pHead; k != NULL; k = k-> pNext)
	{
		Ghi_Thong_Tin_1_Nhan_Vien(fileout, k->data);
		fileout << endl;
	}
	fileout.close();
	cout << "\t\t\t==========LUU THANH CONG==========\t\t\t" << endl;
}
void menu()
{
	cout << "\t\n";
	cout << "\n\n\t\t\t\t\tCHUONG TRINH QUAN LY NHAN VIEN! \t\t\t\t\n";
	cout << "\t\t\t*************************************************************************\t\n";
	cout << "\t\t\t\t\t1:Xem danh sach nhan vien.\t\t\t\t\t\n";
	cout << "\t\t\t\t\t2:Sap xep nhan vien.\t\t\t\t\t\t\t\n";
	cout << "\t\t\t\t\t3:Them nhan vien.\t\t\t\t\t\t\t\n";
	cout << "\t\t\t\t\t4:Xoa nhan vien.\t\t\t\t\t\t\t\n";
	cout << "\t\t\t\t\t5:Tim kiem nhan vien.\t\t\t\t\t\t\t\n";
	cout << "\t\t\t\t\t6:Xuat danh sach ra file export.\t\t\t\t\t\n";
	cout << "\t\t\t\t\t0:Ket thuc chuong trinh.\t\t\t\t\t\t\n";
	cout << "\t\t\t*************************************************************************\t\n";
	cout << "Nhap lua chon cua ban:";
	return;
}

int main()
{
	int gt;
	menu();
	NHANVIEN nv;
	LIST l;
	KhoiTaoDanhSach(l);
	ifstream filein;
	filein.open("import.txt", ios::in);
	do
	{
		gt = ktra_giatri(0, 6);
		switch (gt)
		{
		case 1:
			Doc_ds_Nhan_Vien(filein, l);
			Xuat_ds_Nhan_Vien(l);
			break;
		case 2:
			cout << "Ban vui long chon tieu chi sap xep:\n";
			cout << "1. Sap xep theo ngay sinh.\n";
			cout << "2. Sap xep theo he so luong.\n";
			cout << "3. Sap xep theo ten.\n";
			cout << "4. Sap xep theo chuc vu.\n";
			int gt;
			cin >> gt;
			if (gt==1)
			{
				Sap_xep_ngay_sinh(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (gt==2)
			{
				Sap_Xep_Heso(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (gt==3)
			{
				Sap_xep_ten(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (gt == 4)
			{
				Sap_xep_chucvu(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (gt !=1 && gt != 2 && gt !=3 && gt!=4)
			{
				cout << "Khong hop le! Moi nhap lai!" << endl;
			}
			break;
		case 3:
			Chen_nhan_vien(l, nv);
			Sap_xep_ten(l);
			Xuat_ds_Nhan_Vien(l);
			break;
		case 4:
			cout << "Ban vui long chon tieu chi xoa:\n";
			cout << "1. Xoa theo ngay sinh.\n";
			cout << "2. Xoa theo he so luong.\n";
			cout << "3. Xoa theo ten.\n";
			cout << "4. Xoa theo chuc vu.\n";
			cout << "5. Xoa theo nguyen quan.\n";
			cout << "6. Xoa theo cmnd.\n";
			int xoa;
			cin >> xoa;
			if (xoa == 1)
			{
				Xoa_theo_namsinh(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (xoa == 2)
			{
				Xoa_theo_he_so(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (xoa == 3)
			{
				Xoa_theo_ten(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (xoa == 4)
			{
				Xoa_theo_chucvu(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (xoa == 5)
			{
				Xoa_theo_nguyenquan(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (xoa == 6)
			{
				Xoa_theo_cmnd(l);
				Xuat_ds_Nhan_Vien(l);
			}
			if (xoa != 1 && xoa != 2 && xoa != 3 && xoa != 4 && xoa!= 5 && xoa !=6)
			{
				cout << "Khong hop le! Moi nhap lai!" << endl;
			}
			break;
		case 5:
			cout << "Ban vui long chon tieu chi tim kiem:\n";
			cout << "1. Tim kiem theo ten.\n";
			cout << "2. Tim kiem theo chuc vu.\n";
			cout << "3. Tim kiem theo ngay sinh.\n";
			cout << "4. Tim kiem theo he so luong.\n";
			cout << "5. Tim kiem theo nguyen quan.\n";
			cout << "6. Tim kiem theo cmnd.\n";
			int dem;
			cin >> dem;
			if (dem == 1)
			{
				Tim_kiem_theo_ten(l);
			}
			if (dem == 2)
			{
				Tim_kiem_theo_chucvu(l);
			}
			if (dem == 3)
			{
				Tim_kiem_namsinh(l);
			}
			if (dem == 4)
			{
				Tim_kiem_theo_heso(l);
			}
			if (dem == 5)
			{
				Tim_kiem_theo_nguyenquan(l);
			}
			if (dem == 6)
			{
				Tim_kiem_theo_cmnd(l);
			}
			if (dem != 1 && dem != 2 && dem != 3 && dem != 4 && dem != 5 && dem != 6)
			{
				cout << "Khong hop le! Moi nhap lai!" << endl;
			}
			break;
		case 6:
			Xuat_ra_export(l);
			break;
		case 0:
			return 0;
		}
		menu();
	}
	while (gt != '0');
	Giai_Phong_Vung_Nho(l);
	filein.close();
	system("pause");
	return 0;
}
