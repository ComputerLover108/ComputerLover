#include "CBigInteger.h"
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
  char fname[100];
  cout << "�����ļ�1��";
  cin >> fname;
  ifstream fin(fname);
  cout << "�����ļ�2��";
  cin >> fname;
  ifstream fin2(fname);
  CBigInteger a, b, c;
  fin >> fname;
  a.Parse(fname, true);
  fin2 >> fname;
  b.Parse(fname, true);
  fin.close(); fin2.close();
  c = a + b;
  cout << "���:";
  cout << c.toString() << endl;
  return 0;
}