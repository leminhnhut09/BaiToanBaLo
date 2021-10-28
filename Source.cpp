/*
-- Chú thích về tác giả
-- Họ và tên: Lê Minh Nhựt
-- MSSV: 2001180152
-- Lớp: 09DHTH3
-- Phòng A102, Tiết: 10 - 12
-- Nội dung: cài đặt bài toán chia thưởng + balo(tham lam)
*/
// -----------------------------------------------------------------
// Khai báo thư viện
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

using namespace std;
// Khai bao struct
struct DoVat
{
	char ten;
	int trluong, gtri;
	float donGia;
	int slChon;
};
struct DoVat_GioiHan
{
	char ten;
	int trluong, gtri;
	float donGia;
	int slHienCo;
	int slChon;
};
// -----------------------------------------------------------------
// Khai báo hàm
void docFile(DoVat dsDV[], int &n, int &W);
void ghiFile(DoVat dsDV[], int n);
void tinhDonGiaVaSapXepGiamTheoDG(DoVat dsDV[], int n);
void timSoVat(DoVat dsDV[], int n, int W);


void docFile_GioiHan(DoVat_GioiHan dsDV[], int &n, int &W, char* fname);
void ghiFile_GioiHan(DoVat_GioiHan dsDV[], int n, char* fname);
void tinhDonGiaVaSapXepGiamTheoDG_GH(DoVat_GioiHan dsDV[], int n);
void timSoVat_SoLuongCuThe(DoVat_GioiHan dsDV[], int n, int W);


void hoanVi(DoVat &a, DoVat &b);
// mang
void taoMangRD(int a[], int &n);
void xuatMang(int a[], int n);
void InHoanVi(int a[], int n, int k);
void menu();

// -----------------------------------------------------------------
void main()
{
	int opt, k;
	while (true)
	{
		menu();
		do
		{
			printf_s("\nNhap lua chon cua ban: ");
			scanf_s("%d", &opt);
		}
		while (opt < 0 || opt > 5);
		switch (opt)
		{
		case 0: 
			exit(0);
		case 1:
			{
				DoVat dsDV[30];
				int n = 0, W = 0;
				docFile(dsDV, n, W);
				tinhDonGiaVaSapXepGiamTheoDG(dsDV, n);
				timSoVat(dsDV, n , W);
				ghiFile(dsDV, n);
				printf_s(">>Da luu vao file output");
				break;
			}
		case 2:
			{

				DoVat_GioiHan dsDV[30];
				char * nameIn = "input2.txt";
				char * nameOut = "output2.txt";
				int n = 0, W = 0;
				docFile_GioiHan(dsDV, n, W, nameIn);
				for (int i = 0; i < n; i++)
				tinhDonGiaVaSapXepGiamTheoDG_GH(dsDV, n);
				timSoVat_SoLuongCuThe(dsDV, n , W);
				ghiFile_GioiHan(dsDV, n, nameOut);
				printf_s(">>Da luu vao file output");
				break;
			}
		case 3:
			{
				
				DoVat_GioiHan dsDV[30];
				char * nameIn = "input3.txt";
				char * nameOut = "output3.txt";
				int n = 0, W = 0;
				docFile_GioiHan(dsDV, n, W, nameIn);
				tinhDonGiaVaSapXepGiamTheoDG_GH(dsDV, n);
				timSoVat_SoLuongCuThe(dsDV, n , W);
				ghiFile_GioiHan(dsDV, n, nameOut);
				printf_s(">>Da luu vao file output");
				break;
			}
		case 4:
			{
				int a[30], n;
				taoMangRD(a, n);
				xuatMang(a, n);
				printf_s("\n");
				printf("Nhap k  la so phan tu giu lai khong hoan vi: ");
				scanf_s("%d",&k);
				printf("Cac hoan vi cua mang: \n");
				InHoanVi(a, n, k);
				break;
			}
		default:
			break;
		}

	}
}
// -----------------------------------------------------------------
// Thân hàm con
void docFile(DoVat dsDV[], int &n, int &W)
{
	char * filename = "input1.txt";
	ifstream in;
	in.open(filename);
	if(in)
	{
		in >> W;
		in >> n;
		for (int i = 0; i < n; i++)
		{
			in >> dsDV[i].ten;
			in >> dsDV[i].trluong;
			in >> dsDV[i].gtri;
		}
	}
	in.close();
}
void ghiFile(DoVat dsDV[], int n)
{
	char * filename = "output1.txt";
	ofstream out;
	out.open(filename);
	int tongTL = 0, tongGT = 0;
	out << "So luong vat la: " << n << "\n";
	for (int i = 0; i < n; i++)
	{
		out << "Ten vat: " << dsDV[i].ten << "," << "So luong chon:" << dsDV[i].slChon << "\n" ;
		tongTL += dsDV[i].trluong * dsDV[i].slChon;
		tongGT += dsDV[i].gtri * dsDV[i].slChon;
	}
	out << "Tong trong luong la: " << tongTL << "\n";
	out << "Tong gia tri la: " << tongGT << "\n";


	out.close();
}
void hoanVi(DoVat &a, DoVat &b)
{
	DoVat tam = a;
	a = b;
	b = tam;
}
void tinhDonGiaVaSapXepGiamTheoDG(DoVat dsDV[], int n)
{
	for (int i = 0; i < n; i++)
	{
		dsDV[i].donGia = (float)dsDV[i].gtri / dsDV[i].trluong;
	}
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if(dsDV[i].donGia < dsDV[j].donGia)
			{
				hoanVi(dsDV[i], dsDV[j]);
			}
		}
	}
}
void timSoVat(DoVat dsDV[], int n, int W)
{
	for (int i = 0; i < n && W > 0; i++)
	{
		dsDV[i].slChon = W / dsDV[i].trluong;
		W = W - dsDV[i].trluong * dsDV[i].slChon;
	}
}


void docFile_GioiHan(DoVat_GioiHan dsDV[], int &n, int &W, char* fname)
{
	char * filename = fname;
	ifstream in;
	in.open(filename);
	if(in)
	{
		in >> W;
		in >> n;
		for (int i = 0; i < n; i++)
		{
			in >> dsDV[i].ten;
			in >> dsDV[i].trluong;
			in >> dsDV[i].gtri;
			in >> dsDV[i].slHienCo;
		}
	}
	in.close();
}
void ghiFile_GioiHan(DoVat_GioiHan dsDV[], int n, char* fname)
{
	char * filename = fname;
	ofstream out;
	out.open(filename);
	int tongTL = 0, tongGT = 0;
	out << "So luong vat la: " << n << "\n";
	for (int i = 0; i < n; i++)
	{
		out << "Ten vat: " << dsDV[i].ten << ", " << "So luong chon:" << dsDV[i].slChon << "\n" ;
		tongTL += dsDV[i].trluong * dsDV[i].slChon;
		tongGT += dsDV[i].gtri * dsDV[i].slChon;
	}
	out << "Tong trong luong la: " << tongTL << "\n";
	out << "Tong gia tri la: " << tongGT << "\n";


	out.close();
}
void timSoVat_SoLuongCuThe(DoVat_GioiHan dsDV[], int n, int W)
{
	for (int i = 0; i < n && W > 0; i++)
	{
		dsDV[i].slChon = W / dsDV[i].trluong;
		if(dsDV[i].slChon > dsDV[i].slHienCo)
			dsDV[i].slChon = dsDV[i].slHienCo;
		W = W - dsDV[i].trluong * dsDV[i].slChon;
	}
}
void tinhDonGiaVaSapXepGiamTheoDG_GH(DoVat_GioiHan dsDV[], int n)
{
	for (int i = 0; i < n; i++)
	{
		dsDV[i].donGia = (float)dsDV[i].gtri / dsDV[i].trluong;
	}
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if(dsDV[i].donGia < dsDV[j].donGia)
			{
				DoVat_GioiHan a = dsDV[i];
				dsDV[i] = dsDV[j];
				dsDV[j] = a;
			}
		}
	}
}



void taoMangRD(int a[], int &n)
{
	do
	{
		printf_s("Nhap so luong phan tu cua mang:");
		scanf_s("%d", &n);
	}
	while (n <= 0);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 100;
	}
}
void xuatMang(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf_s("%4d", a[i]);
	}
}

void InHoanVi(int a[], int n, int k)
{
	for(int i = 0; i < n; i++)
		printf("%5d", a[i]);
	printf("\n");
	for(int j = k + 1; j < n; j++)
	{
		int temp = a[k];
		a[k] = a[j];
		a[j] = temp;
		InHoanVi(a, n, k + 1);
	}
}
void menu()
{
	printf_s("\n\n\t\t------------------MENU------------------\n");
	printf_s("\t\t0. Thoat\n");
	printf_s("\t\t1. Bai toan ba lo voi so luong khong gioi han\n");
	printf_s("\t\t2. Bai toan balo voi so luong cu the\n");
	printf_s("\t\t3. Bai toan balo voi so luong 1\n");
	printf_s("\t\t4. Xuat cac hoan vi cua day so\n");
	printf_s("\t\t------------------END-------------------");
}