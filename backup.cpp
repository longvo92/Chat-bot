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
/						- Vua vao da co the chat
/						- phat trien base data
/						- Tranh ghi de cau tra loi
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

const int Che_do_phat_trien = 1;
const int Che_do_Giao_tiep =2;
const int Mo_file=3;
const int Xuat_file=4;

class tinNhan:protected Xulykytu{
	private:
		set < pair <string, string> > Reply;
	public:
		void hoctap(){
			string cauhoi,cautraloi;
			//cin.ignore();
			cout << "Hay nhap cau hoi: "<<endl;
			
			getline(cin,cauhoi);
			ChuanHoakytu(cauhoi);
			//cin.ignore();
			cout << "Hay nhap cau tra loi: "<<endl;
			
			getline(cin,cautraloi);
			ChuanHoakytu(cautraloi);
			Reply.insert(make_pair(cauhoi,cautraloi));
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
				if(n==false) cout << "COM: Chua hoc" <<endl;
			}
			else cout<<"Chua nhap data";
		}
		bool Mofile(){
//			for(auto it = Reply.begin();it!=Reply.end();it++){
//				ChuanHoakytu(it->first);
//				ChuanHoakytu(it->second);
//			}
			string txt,str,word;
			vector<string> words;
			cin.ignore();
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
					Reply.insert(make_pair(a,b));	
				}
			}
			else{
			 	cout << "Khong thanh cong, file trong!" <<endl;
				return false; 
			}
				
		}
		bool Xuatfile(){
			string txt;
			cin.ignore();
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
			cout << "Vui long chon 1 tinh nang:\n 1/ Che ho hoc tap \n 2/ Che do giao tiep \n 3/ Nhap \n 4/ Xuat\n";
			cin >> n;
			cin.ignore();
		}
		getif(){
			cout <<"Chon chuc nang tiep theo"<<endl;
			cin >>n;
			cin.ignore();
		}
		void loop(){
			while(true){
				if(n==Che_do_phat_trien) {
					hoctap();
					getif();
				}
				else if(n==Che_do_Giao_tiep){
					cout << "Human: "; 
					string a;
					getline(cin,a);
					ChuanHoakytu(a);
					if(a=="End") getif();
					else traloi(a);
					if(a=="Dev") {
						hoctap();
						getif();
					}
				}
				else if(n==Mo_file){
					if (tinNhan::Mofile()){
						cout<<"Mo file thanh cong"<<endl;
						getif();
					}
					else getif();
				}
				else if(n==Xuat_file){
					if(Xuatfile())	getif();
				}
				else break;
			}
		}
};
int main(){
	Giaodien a;
	a.setup();
	a.loop();
	return 0;
}

