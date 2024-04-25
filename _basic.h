#pragma once
#include<qstring.h>
#include<iostream>
#include<qtablewidget.h>
#include<QtWidgets/QMessageBox>
#include<sstream>
#include<qlabel.h>
#include<qlayout.h>
#include<qcombobox.h>
#include<qtextedit.h>
static const wchar_t* libxl_cracked_name = L"libxl";
#if defined(WIN32) || defined(WIN64)
static const wchar_t* libxl_cracked_key = L"windows-28232b0208c4ee0369ba6e68abv6v5i3";
#else
static const std::string libxl_cracked_key = "linux-i8i3ibi2i8i4iei3i9iaiei8ibx6x5i3";
#endif

int randint(int l, int r);
QString N2S(int num);
QString F2S(float f,int n = 2);
int S2N(QString);
float S2F(QString);
std::string randS(int len);
std::string stringFromSS(std::stringstream & ss);

std::string Wchar2String(const wchar_t* wchar,int len);

std::wstring string2wstring(std::string str);

std::string wstring2string(std::wstring wstr);

QString F2Percentage(float num,int wei);