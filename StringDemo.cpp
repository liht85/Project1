#include "StringDemo.h"


#include <string>
using namespace std;
void testfuctong1(string &t)		// string  作为参数 一般用引用
{
	return;	
}
void testfuctong2(const string &t)		// string  作为参数 一般用引用
{
	return;
}

void Demo_String()
{
	string str1("test");
	string str2 = "test2";
	string str3("12345678",3);


	//获取字符串内部的char*
	const char *p = str3.c_str();

	string t1;
	t1.append("something is");			//  附加 字符串
	t1.append(" nothing!");

	//考虑效率问题
	string t2;
	t2.resize(1024);		//调整大小
	t2.clear();				// 清空 
	t2.append("12");
	t2.append("34");
	t2.append("sdfadsfsf34",1,3); //  添加 dfa

	string t3 = "Hello";
	t3[1] = 'i';
	t3.at(1) = 'i';  //at(n)表示返回下标为n的元素的引用。    效果同  t3[1] = 'i';

	// 字符串的比较      string  重载了所有关系操作符（== ,!=, >= <=）
	string t4 = "yes";
	if (t4 == "yes")
	{
		printf("TRUE");
	}

	// 字符串找
	string st5 = "liming is doing homework";
	int pos = st5.find('i');
	pos = st5.rfind('o');  // 存在返回未知  不存在-1
	pos = st5.find("do");

	pos = st5.find_first_of("23fdgh");		// 用于查找若干字符中的一个 ，只有其中任意一个字符匹配即返回。
	pos = st5.find_first_not_of("234325rf"); // 和上面 相反

	//返回子串
	string t6("advasdsdaftt");
	string r1 = t6.substr(4);  // 4后的所有串
	string r2 = t6.substr(4, 2); // 4后的2个字符

	//  replace  insert  string  不适宜进行插入和删除，涉及到 大规模数据的移动，如果频繁的使用 会比较消耗CPU



	printf("%s", p);
	return;
}
#include "vector"
void vector_demo()
{
	vector <int>  arr(16);
	arr.clear();

	arr.push_back(1);		//capacity:16   size 1
	arr.push_back(2);		//capacity 16   size 2
	int ncapacity = arr.capacity();
	int nsize = arr.size();

	// 迭代器遍历
	vector<int>::iterator iter;
	for (iter = arr.begin();iter!=arr.end();iter++)
	{
		int &value = *iter;
		printf("%d", value);
	}

	for (int i = 0; i<arr.size();i++)
	{
		int &value = arr[i];
		printf("%d", value);
	}

}