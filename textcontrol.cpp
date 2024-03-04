#include "textcontrol.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


	void Xulykytu::ghepchu(string &a){
			for (int i = a.length(); i >=0;i--){
				if (isspace(a[i])) a.erase(a.begin()+i);
			}
		}
	void Xulykytu::tachchu(string &str){
		char kytu= ' ';
		for (int i = str.length(); i >=0;i--){
			if (isupper(str[i])&&i!=0) str.insert(i,1,kytu);
		}
	}
	bool Xulykytu::kiemtrakytu(string kytu,string a){
		int j =0;
		for (int i =0;i<a.length();i++){
			if (kytu[j]==a[i]){
				j++;
			if (j==a.length()) return true;
		}
		else j=0;
	}
		return false;
	}	
	void Xulykytu::ChuanHoakytu(string &str){
		while (str[0]==' '){
			str.erase(str.begin()+0);
		}
		while (str[str.length()-1]==' '){
			str.erase(str.begin()+str.length()-1);
		}
		int TuMoi = 1;
		for (int i = 0; i <str.length();i++){
			if (isspace(str[i])&&isspace(str[i+1])){
				str.erase(str.begin()+i);
				i--;
			}
		}
		for(int i = 0; i < str.length();i++){
			if (TuMoi == 1 && isalpha(str[i])){
				str[i] = toupper(str[i]);
				TuMoi = 0;
			}
			else if (isspace(str[i]) || str[i]=='-'){
				TuMoi=1;
			}
			else {
				str[i] = tolower(str[i]);
				TuMoi = 0;
			}
		}
	}

