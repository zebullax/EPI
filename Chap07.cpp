#include <vector>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

string IntToString(int i) {
	string res;
	int last_digit;
	while (i)
	{
		last_digit = (i<10 ? i:i % ((i / 10) * 10));
		res.push_back('0' + last_digit);
		i /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}

int StringToInt(string s) {
	int res=0;
	char last_char;
	for (int i = 0; i < s.size(); ++i) {
		res = res * 10 + s[i] - '0';
	}
	return res;
}
void Prob7_01D() {
	string s("12345");
	int i=12345;
	assert(IntToString(i) == s);
	assert(StringToInt(s) == i);
}

void Prob7_02(string &s) {
	int write_idx = 0; 
	int read_idx = 0;
	int new_size=0;
	while(read_idx < s.size()) {
		if (s[read_idx] == 'a') {
			new_size += 2;
			s[write_idx++] = s[read_idx];
		} else if (s[read_idx] != 'b') {
			new_size += 1;
			s[write_idx++] = s[read_idx];
		}
		read_idx++;			
	}
	read_idx = write_idx-1;
	write_idx = new_size - 1;
	while (read_idx >= 0) {
		if (s[read_idx] == 'a') {
			s[write_idx--] = 'd';
			s[write_idx--] = 'd';
		} else if (s[read_idx] != 'b') {
			s[write_idx--] = s[read_idx];
		}
		read_idx--;
	}
	s.resize(new_size);
}


void Prob7_02D() {
	string s("baobab");// -> ddodd
	Prob7_02(s);
}

void ReverseString(string &s, int s_i, int e_i) {
	for (int i = s_i; i < (e_i+s_i)>>1; ++i) {
		swap(s[i], s[e_i - (i-s_i) - 1]);
	}
}
void Prob7_04(string &s) {
	int word_s = 0;
	ReverseString(s, 0, s.size());
	for(int i=0;i<s.size();++i) {
		if (s[i] == ' ') {
			ReverseString(s, word_s, i);
			while (i<s.size() && s[i] == ' ') ++i;
			word_s = i;
		}
	}
	if (word_s != s.size())
		ReverseString(s, word_s, s.size());
}

void Prob7_04D() {
	string s("Alice likes Bob");
	Prob7_04(s);
	cout << s << endl;
}

string Prob7_06(int n) {
	if (n == 1)
		return ("11");
	string s("1"), r("11");
	
	for (int j = 1; j < n; ++j) {
		s = r;r.clear();
		for (int i = 0; i < s.size(); ++i) {
			int nb = 1;
			while (i + 1 < s.size() && s[i] == s[i + 1]) {
				nb++;
				i++;
			}
			r += to_string(nb) + s[i];
		}
	}
	return r;
}
string RLE_Encoding(string s) {
	string res;
	unsigned int nb = 1;
	for (int i = 0; i < s.size(); ++i) {
		while (i + 1<s.size() && s[i] == s[i + 1]) {
			nb++;
			i++;
		}
		res.push_back('0' + nb);
		res.push_back(s[i]);
		nb = 1;
	}
	return res;
}
string RLE_Decoding(string s) {
	string res;
	char c;
	unsigned int nb;
	for (int i = 0; i < s.size(); ++i) {
		nb = s[i++]-'0';
		c = s[i];
		res.insert(res.end(), nb, c);		
	}
	return res;
}
void Prob7_10D() {
	string s("aaaabcccaa");
	string encoded_s = RLE_Encoding(s);
	string decoded_s = RLE_Decoding(encoded_s);
	assert(decoded_s == s);
}
void Prob7_06D() {
	int n = 7;
	string result = Prob7_06(8);
}
int main(int argc,char**argv) {
	Prob7_10D();
	getchar();
	return 0;
}
