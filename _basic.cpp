#include"_basic.h"
#include<Windows.h>


QString N2S(int num)
{
    QString res = "";
    do
    {
        res.append((char)(num % 10 + '0'));
        num /= 10;
    } while (num);

    QString s2 = "";
    for (int i = res.length() - 1; i >= 0; i--)
    {
        s2.append(res[i]);
    }
    return s2;
}

std::string randS(int len)
{
    std::string ans;
    for (int i = 0; i < len; i++)
    {
        int rd = randint(0, 25);
        ans.push_back('A' + rd);
    }
    return ans;
}

QString F2S(float num, int ws)
{
    QString res = N2S(num);
    if (ws <= 0)  return res;
    res.append('.');
    float xs = num - (int)num;
    QString s2 = "";
    for (int i = 0; i < ws; i++) xs *= 10;
    xs += 0.5;
    int n = xs;
    for (int i = 0; i < ws; i++)   {
        s2.append((char)(n % 10 + '0')); n /= 10;
    }
    for (int i = ws - 1; i >= 0; i--)
    {
        res.append(s2[i]);
    }
    return res;
}

int S2N(QString s)                                          //注意检错
{
    int res = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i].toLatin1() > '9' || s[i].toLatin1() < '0') {
            return -1;
        }
        res = res * 10 + ((s[i].toLatin1()) - '0');
    }
    return res;
}


float S2F(QString s)                                          //注意检错
{
    int res = 0;
    float ans = 0;
    float weight = 0.1;
    int i = 0;
    for (; i < s.length() && s[i] != '.'; i++) {
        if (s[i].toLatin1() > '9' || s[i].toLatin1() < '0') {
            return -1;
        }
        res = res * 10 + ((s[i].toLatin1()) - '0');
    }

    for (++i; i < s.length(); i++) {
        if (s[i].toLatin1() > '9' || s[i].toLatin1() < '0') {
            return -1;
        }
        ans = ans + weight * ((s[i].toLatin1()) - '0');
        weight = weight * 0.1;
    }
    return res+ans;
}

int randint(int l, int r)
{
    return (rand() % (r - l + 1)) + l;
}

std::string stringFromSS(std::stringstream& ss)
{
    std::string s;
    std::string tmp;
    while (getline(ss, tmp))
    {
        s = s + "\n" + tmp;
    }
    return s;
}

std::string Wchar2String(const wchar_t* wchar,int len)
{
    std::string str;
	int nLen = WideCharToMultiByte(CP_ACP, 0, wchar, len, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return str;
	}
	char* pElementText = new char[nLen + 1];
	if (pElementText == NULL)
	{
		return str;
	}
	WideCharToMultiByte(CP_ACP, 0, wchar, len, pElementText, nLen, NULL, NULL);
	pElementText[nLen] = '\0';
	str = pElementText;
	delete[] pElementText;
	return str;
}


//将string转换成std::wstring  
std::wstring string2wstring(std::string str)
{
    std::wstring result;
    //获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    TCHAR* buffer = new TCHAR[len + 1];
    //多字节编码转换成宽字节编码  
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';             //添加字符串结尾  
    //删除缓冲区并返回值  
    result.append(buffer);
    delete[] buffer;
    return result;
}

//将std::wstring转换成string  
std::string wstring2string(std::wstring wstr)
{
    std::string result;
    //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
    char* buffer = new char[len + 1];
    //宽字节编码转换成多字节编码  
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    //删除缓冲区并返回值  
    result.append(buffer);
    delete[] buffer;
    return result;
}

QString F2Percentage(float num,int wei)
{
    num *= 100;
    float xs = num - (int)num;
    QString s1 = N2S(num);

    for (int i = 0; i < wei; i++)  xs *= 10;
    xs += 0.5;
    QString s2 = N2S(xs);

    return s1 + "." + s2 + "%";
}
