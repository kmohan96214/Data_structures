#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
using std::string;
typedef unsigned long long ull;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        cout << output[i] << " ";
    cout << "\n";
}

vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}

long long polyhash(const string& s, int prime, int x) {
	unsigned long long hash = 0;
	for (long long i = static_cast<long long> (s.size()) - 1; i >= 0; --i)
		hash = (hash * x + s[i]) % prime;
	return hash;
}

vector<long long> preComputeH(string text,int plen,int p,int x)
{
    vector<long long> H(text.length()-plen+1);
    string s = text.substr(text.length()-plen,plen);
    H[text.length()-plen] = polyhash(s,p,x);

    long long y=1;
    for(int i=1;i<=plen;i++)
        y = (y*x)%p;
    for (int i = text.length() - plen - 1; i >= 0; i--) {
		long long preHash = x * H[i + 1] + text[i] - y * text[i + plen];
		while (preHash < 0) {
			preHash += p;
		}
		H[i] = preHash % p;
	}
    return H;
}
bool areEqual(string s1, string s2){
	if (s1.size() != s2.size())
		return false;
	for (int i = 0; i < s1.size(); ++i) {
		if (s1[i] != s2[i])
			return false;
	}
	return true;
}

vector<int> rabinKarp(const Data& input)
{
    const string& text=input.text,pattern=input.pattern;
    int p = 1000000007;
    int x = rand()%(p-1) + 1;
    vector<int> result;
    vector<long long> H = preComputeH(text,pattern.length(),p,x);
    int phash = polyhash(pattern,p,x);

    for(int i=0;i<=text.length()-pattern.length();i++)
    {
        if(phash!=H[i])
            continue;
        if(areEqual(pattern,text.substr(i,pattern.length())))
            result.push_back(i);
    }
    return result;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    //print_occurrences(get_occurrences(read_input()));
    print_occurrences(rabinKarp(read_input()));
    //string text,pattern;
    //print_occurrences(rabinKarp())
    return 0;
}
