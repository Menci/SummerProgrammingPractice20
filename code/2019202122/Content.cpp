//1.��һ��txt   ��
//2.������Ӧ�ļ��� ��������Ӧ��title + content ��txt�ļ�  ��
//3.��ʼ����txt
	//3.1 �ҵ�����title д��title.txt
	//3.2�ҵ�����contentд��content.txt

#include<string.h>
#include<string>
#include<queue>
#include<cstdlib>
#include<unistd.h>
#include<fstream>
#include<iostream>
#include<regex>
using namespace std;
void Gettitle_content() {
	unsigned int num = { 1 };
	char str[128];
	char potitle[128];
	char pocontent[128];
	sprintf(str, "/home/cpp/Crawling/%d.txt", num);
	fstream in(str);
	while (in) {
		string P((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
		in.close();
		sprintf(potitle, "/home/cpp/Content/%d/title.txt", num);
		sprintf(pocontent, "/home/cpp/Content/%d/content.txt", num);
		const char* p = P.c_str();
		//��ȡ��������
		const char* tag1 = "<title>";
		const char* pos1 = strstr(p, tag1);
		ofstream otitle(potitle, ios::app);
		if (pos1) {
			pos1 += strlen(tag1);
			const char* nextQ = strstr(pos1, "</title>");
			if (nextQ) {
				char* title = new char[nextQ - pos1 + 1];
				sscanf(pos1, "%[^<]", title);
				string Title = title;
				delete[]title;
				otitle << Title;
			}
		}
		otitle.close();

		//��ȡ��������
		const char* tag2 = "<p>";
		const char* pos2 = strstr(p, tag2);
		ofstream ocontent(pocontent, ios::app);
		while (pos2) {
			pos2 += strlen(tag2);
			const char* nextQ = strstr(pos2, "</p>");
			if (nextQ) {
				char* content = new char[nextQ - pos2 + 1];
				sscanf(pos2, "%[^<]", content);
				if (strstr(content, "<strong>") || strstr(content, "&nbsp")) {
					pos2 = strstr(pos2, tag2);
					delete[]content;
					continue;
				}
				string Content = content;
				delete[]content;
				ocontent << Content << endl;
			}
			pos2 = strstr(pos2, tag2);
		}
		ocontent.close();
		
		cout << num << endl;
		num++;
		sprintf(str, "/home/cpp/Crawling/%d.txt", num);
		in.open(str);
	}
}

int main() {
	Gettitle_content();
	return 0;
}