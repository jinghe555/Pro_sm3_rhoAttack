#include <iostream>
#include <string>
#include <cmath>
#include<time.h>
using namespace std;

//ʮ����ת������
string dec_bin(int dec)
{
	string bin = "";
	while (dec >= 1)
	{
		bin = to_string(dec % 2) + bin;
		dec = dec / 2;
	}
	return bin;//���ض�Ӧ�Ķ�����
}
//ʮ������ת������
string hex_bin(string str)
{
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
		{
			bin += table[(str[i] - 'A' + 10)];
		}
		else
		{
			bin += table[(str[i] - '0')];
		}
	}
	return bin;
}
//������תʮ������
string bin_hex(string str)
{
	string hex = "";
	int temp = 0;
	while (str.size() % 4 != 0)
	{
		str = '0' + str;
	}
	for (int i = 0; i < str.size(); i += 4)
	{
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0');
		//cout << "temp" << temp;
		if (temp < 10)
		{
			hex += to_string(temp);
		}
		else if (temp == 10)
		{
			hex += 'A';
			//cout <<"hex"<< hex;
		}
		else if (temp == 11)
		{
			hex += 'B';
		}
		else if (temp == 12)
		{
			hex += 'C';
		}
		else if (temp == 13)
		{
			hex += 'D';
		}
		else if (temp == 14)
		{
			hex += 'E';
		}
		else if (temp == 15)
		{
			hex += 'F';
		}
		//cout << "hex" << hex;
	}
	return hex;
}
//ʮ������תʮ����
long long hex_dec(string str)
{
	long long dec = 0;;
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			dec += (str[i] - '0');
		}
		else if ('A' <= str[i] && str[i] <= 'F')
		{
			dec += (str[i] - 'A' + 10);
		}
		if (i < (len - 1))
		{
			dec *= 16;
		}
	}
	return dec;
}
//����λ
string LeftShift(string str, int num)
{
	string res = hex_bin(str);
	res = res.substr(num) + res.substr(0, num);
	return bin_hex(res);
}
//���
string XOR(string str1, string str2)
{
	string res = "";
	str1 = hex_bin(str1);
	str2 = hex_bin(str2);
	for (int i = 0; i < str1.size(); i++)
	{
		if (str1[i] == str2[i])
		{
			res += '0';
		}
		else
		{
			res += '1';
		}
	}
	return bin_hex(res);
}
//P0�û�
string P0(string str)
{
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}
//P1�û�
string P1(string str)
{
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}
//�����
string OR(string str1, string str2)
{
	string res = "";
	str1 = hex_bin(str1);
	str2 = hex_bin(str2);
	for (int i = 0; i < str1.size(); i++)
	{
		if (str1[i] == '0' && str2[i] == '0')
		{
			res += '0';
		}
		else
		{
			res += '1';
		}
	}
	return bin_hex(res);
}
//�ǲ���
string NOT(string str)
{
	string res = "";
	str = hex_bin(str);
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '0')
		{
			res += "1";
		}
		else
		{
			res += "0";
		}
	}
	return bin_hex(res);
}
//�����
string AND(string str1, string str2)
{
	string res = "";
	str1 = hex_bin(str1);
	str2 = hex_bin(str2);
	for (int i = 0; i < str1.size(); i++)
	{
		if (str1[i] == '1' && str2[i] == '1')
		{
			res += '1';
		}
		else
		{
			res += '0';
		}
	}
	return bin_hex(res);
}
//FF_j
string FF_j(string str1, string str2, string str3, int num)
{
	if (0 <= num && num <= 15)
	{
		return XOR(XOR(str1, str2), str3);
	}
	else
	{
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}
//GG_j
string GG_j(string str1, string str2, string str3, int num)
{
	if (0 <= num && num <= 15)
	{
		return XOR(XOR(str1, str2), str3);
	}
	else
	{
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}
//����T��ʼ��
static string init_T(int j)
{
	string T;
	if (0 <= j && j <= 15)
	{
		T = "79CC4519";
	}
	else
	{
		T = "7A879D8A";
	}
	return T;
}
char ccxor(char c1, char c2)
{
	return c1 == c2 ? '0' : '1';
}
char ccand(char c1, char c2)
{
	return (c1 == '1' && c2 == '1') ? '1' : '0';
}
//ģ����
string Mod(string str1, string str2)
{
	string res1 = hex_bin(str1);
	string res2 = hex_bin(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--)
	{
		res = ccxor(ccxor(res1[i], res2[i]), temp) + res;
		if (ccand(res1[i], res2[i]) == '1')
		{
			temp = '1';
		}
		else
		{
			if (ccand(res1[i], res2[i]) == '1')
			{
				temp = ccxor('1', temp);
			}
			else
			{
				temp = '0';
			}
		}
	}
	return bin_hex(res);
}
//��Ϣ���
string padding(string str)
{
	int n;//������Ϣ����
	n = str.length();
	int r_n = n;//��¼ԭʼ��Ϣ����
	int k = 0;
	while ((n + 1 + k) % 512 != 448)
	{
		k += 1;
		str += '0';//���0
	}
	//n = n + 1 + k;//���ڵ���Ϣ����
	string llen = dec_bin(r_n);
	int llength = llen.size();
	for (int i = 0; i <= (64 - llength); i++)
	{
		llen = '0' + llen;
	}
	str = str + llen;//������
	//cout << str;
	return str;
}
//��Ϣ��չ
string extension(string str)
{
	//����Ϣ���黮��Ϊ16����W_i
	string WW = str;//�洢��չ��
	for (int j = 16; j < 68; j++)
	{
		WW += XOR(XOR(P1(XOR(XOR(WW.substr((j - 16) * 8, 8), WW.substr((j - 9) * 8, 8)), LeftShift(WW.substr((j - 3) * 8, 8), 15))), LeftShift(WW.substr((j - 13) * 8, 8), 7)), WW.substr((j - 6) * 8, 8));
	}
	//64��W��
	for (int j = 0; j < 64; j++)
	{
		WW += XOR(WW.substr((j * 8), 8), WW.substr((j + 4) * 8, 8));
	}
	return WW;
}
//��Ϣѹ��
string compress(string str1, string str2)
{
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8),
		D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8),
		G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	for (int j = 0; j < 64; j++)
	{
		SS1 = LeftShift(Mod(Mod(LeftShift(A, 12), E), LeftShift(init_T(j), j % 32)), 7);
		//cout << "SS1 " << SS1 << "\t" << LeftShift(A, 12)<<"ok";
		SS2 = XOR(SS1, LeftShift(A, 12));
		//cout << "ss2" << SS2 <<"ss2ok";
		TT1 = Mod(Mod(Mod(FF_j(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = Mod(Mod(Mod(GG_j(E, F, G, j), H), SS1), str1.substr((j * 8), 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
		//cout << "j  " << j;
	}
	string res = (A + B + C + D + E + F + G + H);
	//cout << "a2" << res;
	return res;
}
//����ѹ������
string iteration(string str)
{
	int num = str.size() / 128;
	//cout << "num" << str.size();
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	//string v = hex_bin(V);
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++)
	{
		B = str.substr((i * 128), 128);
		//cout << "B"<<B;
		//cout << "Bok";
		extensionB = extension(B);
		//cout << extensionB;
		//cout << "extBok";
		compressB = compress(extensionB, V);
		//cout << compressB;
		//cout << "comBok";
		V = XOR(compressB, V);
	}
	return V;
}
string SM3(string message)
{
	//string Mmessage = dec_bin(message);
	string paddingmessage = padding(message);
	paddingmessage = bin_hex(paddingmessage);
	string result = iteration(paddingmessage);
	return result;
}
int main()
{
	cout << "input:";
	int n;//ǰn bit
	cin >> n;
	int num = pow(2, n);
	//cout << "num" << num;
	clock_t start, end;
	start = clock();
	int M1 = rand() % (num + 1);
	string result = SM3(dec_bin(M1));
	string M2=SM3(hex_bin(result));
	//cout << "result" << result << endl;
	//cout << M2 << endl;
	while (result.substr(0, n / 4) != M2.substr(0, n / 4))
	{
		//long long temp = hex_dec(M2);
		//M2 = SM3(hex_dec(M2));
		//cout << "m2"<<temp<<endl;
		M2 = SM3(hex_bin(M2));
		//cout << "M2" << M2 << endl;
	}
	end = clock();
	cout << "succeed, using"<<(float)(end-start)*1000/CLOCKS_PER_SEC<<"ms";
	return 0;
}