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
int main(int argc,char**argv) {
	Prob7_04D();
	getchar();
	return 0;
}
