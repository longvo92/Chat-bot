/* 							CHATBOT TU HOC
/																Long vo
------------------------------------------------------------------------
/				Gioi thieu: 
/						- Chatbot giao tiep voi nguoi dung dua tren base data
/						- Nguoi dung co the tu day cho bot
/						- Cac chuc nang khac nhu: nhap xuat du lieu,
/
/
/-----------------------------------------------------------------------
/				To do list:
/						- phat trien base data
/						- lam toan thong minh
/
/
/
/
/
------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <set>
#include "textcontrol.h"

using namespace std;

const string Dev_mode = "Dev";
const string Export_file = "Export Data";
const string Import_file = "Import Data";
const string End = "End";


class tinNhan:protected Xulykytu{
	private:
		set < pair <string, string> > Reply;
	public:
		void insert(string a, string b){
			Reply.insert(make_pair(a,b));
		}
		void hoctap(){
			string cauhoi,cautraloi;
			cout << "Hay nhap cau hoi: "<<endl;
			getline(cin,cauhoi);
			ChuanHoakytu(cauhoi);
			for (auto it=Reply.begin();it!=Reply.end();it++){
				string kiemtra = it ->first;
				if(kiemtrakytu(cauhoi,kiemtra)){
					Reply.erase(it);
				}
			}
			cout << "Hay nhap cau tra loi: "<<endl;
			getline(cin,cautraloi);
			ChuanHoakytu(cautraloi);
			insert(cauhoi,cautraloi);
		}
		void traloi(string &a){
			if(!Reply.empty()){
				bool n = false;
				for (auto it=Reply.begin(); it!=Reply.end();it++){
					string kiemtra = it->first;
					if(kiemtrakytu(a,kiemtra)){
						string b= it->second;
						for(int i = 0;i<b.size();i++){
							b[i]=tolower(b[i]);
						}
						cout << "COM: " <<b<<endl; 
						n = true;
					}
				
				}
				if(n==false){
					string cautraloi;
					cout << "COM: Toi chua hoc hay day toi cach tra loi :" <<endl;
					getline(cin,cautraloi);
					ChuanHoakytu(cautraloi);
					insert(a,cautraloi);
				} 
			}
			else cout<<"Chua nhap data\n";
		}
		bool Mofile(){
			string txt,str,word;
			vector<string> words;
			cout << "Nhap ten file: ";
			getline(cin,txt);
			ifstream in(txt.c_str());
			if (in){
				getline(in,str);
				in.close();
			}
			else {
				cout << "Kiem tra lai ten file" <<endl;
				return false;
			}
			istringstream iss(str);
			while (iss >> word){
				words.push_back(word);
			}	
			if (!word.empty()){
				for (int i=0; i< words.size();i+=2){
					string a,b;
					a = words[i];
					b = words[i+1];
					tachchu(a);
					tachchu(b);
					insert(a,b);
				}
			}
			else{
			 	cout << "Khong thanh cong, file trong!" <<endl;
				return false; 
			}
		
		}
		bool out(){
			ofstream out("data.txt");			
			set<pair<string,string> >::iterator it = Reply.begin();
			for (it; it!=Reply.end(); it++){
				string a = it->first;
				string b = it->second;
				ghepchu(a);
				ghepchu(b);
				if (out.is_open()){
					out << a <<" "<< b << " ";
				}
				else {
					cout << "Khong the mo file txt" <<endl;
					return false;
				}
			}
				out.close();
				return true;
		}
		bool Xuatfile(){
			string txt;
			cout << "Nhap ten file: ";
			getline(cin,txt);
			ofstream out(txt.c_str());			
			set<pair<string,string> >::iterator it = Reply.begin();
			for (it; it!=Reply.end(); it++){
				string a = it->first;
				string b = it->second;
				ghepchu(a);
				ghepchu(b);
				if (out.is_open()){
					out << a <<" "<< b << " ";
				}
				else {
					cout << "Khong the mo file txt" <<endl;
				}
			}
			out.close();
			cout << "Luu du lieu thanh cong" <<endl; 
		}
};

class Giaodien:protected tinNhan{
	private:
		int n=0;
	public:
		void setup(){
			cout << "Chao mung den voi ChatBot tu hoc"<<endl;
			string str,word;
			vector<string> words;
			ifstream in("data.txt");
			if (in){
				getline(in,str);
				in.close();
			}
			istringstream iss(str);
			while (iss >> word){
				words.push_back(word);
			}	
			if (!word.empty()){
				for (int i=0; i< words.size();i+=2){
					string a,b;
					a = words[i];
					b = words[i+1];
					tachchu(a);
					tachchu(b);
					insert(a,b);
				}
			}
			else cout << "Vui long kiem tra trong thu muc da co file data.txt chua\n";
		}
		void loop(){
			while(true){
					cout << "Human: "; 
					string a;
					getline(cin,a);
					ChuanHoakytu(a);
					if(a==End) {
						if(out()){
							cout<< "Cam on da su dung ChatBot";
							break;
						}
						else {
							cout << "Du lieu chua duoc luu vao data file";
							break;
						}
					}
					else if(a==Dev_mode) {
						hoctap();
						continue;
					}
					else if(a==Import_file){
						if(tinNhan::Mofile()) cout<< "Successful\n";
						else cout << "Import khong thanh cong!\n";
					}
					else if(a==Export_file){
						if(tinNhan::Xuatfile()) cout<< "Successful\n";
						else cout << "Export khong thanh cong";
					}
					else traloi(a);
			}
		}
};
int main(){
	Giaodien a;
	a.setup();
	a.loop();
	return 0;
}
