#include<string.h>
#include<string>
#include<queue>
#include<map>
#include<cstdlib>
#include<set>
#include<iostream>
#include<fstream>
#include<unistd.h>
using namespace std;
unsigned int count = { 0 };
unsigned int num = { 0 };
void BFS() {
	set<string> visited;
	string r = "info.ruc.edu.cn"; //set the root URL
	//obtain p via wget or liburl  ��
	char str[128];
	char sstr[128];
	char ssstr[128];
	queue<string> Q;
	Q.push(r);
	visited.insert(r);
	while (!Q.empty()) {
		string Url = Q.front();
		const char* Url_ = Url.c_str();
		num++;
		sprintf(ssstr, "mkdir /home/cpp/Content/%d", num);
		system(ssstr);
		sprintf(ssstr, "/home/cpp/Content/%d/url.txt", num);
		ofstream out_url(ssstr, ios::app);
		out_url << Url ;
		out_url.close();
		sprintf(str, "wget -O %d.txt %s", num, Url_);
		system(str);
		sprintf(sstr, "%d.txt", num);
		fstream in(sstr);
		string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
		in.close();
		const char* p = content.c_str();
		const char* tag = "href=\"";           //����Ѱ�ҳ�����
		const char* pos = strstr(p, tag);     //Ѱ�ҳ�����
		ofstream ofile("url.txt", ios::app);     //д�ļ����� �����ں�����url���뵽�ļ���
		while (pos) {
			pos += strlen(tag);
			const char* nextQ = strstr(pos, "\"");    //�ҵ������ӵĵ�һ��"
			if (nextQ) {
				char* url = new char[nextQ - pos + 1];    //�����洢�ı���
				sscanf(pos, "%[^\"]", url);   //�õ�������
				if (strstr(url, "http")) {
					if(strstr(url,"info.ruc.edu.cn")){}
					else {
						pos = strstr(pos, tag);
						delete[] url;
						continue;
					}
				}
				if(strstr(url, "@ruc.edu.cn")||strstr(url,"upload")||strstr(url,"download")||strstr(url,"css")||strstr(url,"userfiles") {
					pos = strstr(pos, tag);
					delete[] url;
					continue;
				}
				string surl=url;
				if (!strstr(url, "info.ruc.edu.cn"))  surl = "http://info.ruc.edu.cn/" + surl;
				if (visited.find(surl) == visited.end()) {     //check whether they should be visited
					visited.insert(surl);
					ofile << surl << endl;
					count++;
					Q.push(surl);              //push all the visited URL that p contains into Q;
				}
				delete[] url;
				pos = strstr(pos, tag);
			}
		}
		ofile.close();
		Q.pop();
		sleep(1);
	}
	
}
int main() {
	BFS();
	return 0;
}