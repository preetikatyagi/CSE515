// list::sort
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

// comparison, not case sensitive.
bool compare_nocase (string first, string second)
{
  unsigned int i=0;
  char tempint = 0;
  
  int temp1=0, temp2=0;
  int pos11 = first.find_first_of(",");
  int pos12 = first.find_first_of(",",pos11+1);
  string sub1 = first.substr(pos11+1, pos12-pos11-1);
  istringstream buffer1(sub1);
  buffer1 >> temp1;

  int pos21 = second.find_first_of(",");
  int pos22 = second.find_first_of(",",pos21+1);
  string sub2 = second.substr(pos21+1, pos22-pos21-1);
  istringstream buffer2(sub2);
  buffer2 >> temp2;

  if(temp1 < temp2) return true;
  else return false;
	
}

int main ()
{
  list<string> mylist;
  list<string>::iterator it;
  int count = 0;
  string line;
  ifstream myfile("C:\\Preetika\\MWD\\ProjectCode\\STR\\inputfile.txt");
  if(myfile.is_open())
  {
	while(myfile.good())
	{
		getline(myfile, line);
		mylist.push_back(line);
		cout << line << endl;
	}
	myfile.close();
  }
  else 
  {
	  cout << "Unable to open file." << endl;
  }
  mylist.sort(compare_nocase);
  cout << "mylist contains:" << endl;
  for (it=mylist.begin(); it!=mylist.end(); ++it)
    cout << *it << endl;
  cout << endl;
  cout << "Number of objects- " << mylist.size() << endl;
  double numSlabs = 0.0;
  int numDesc = 1;
  int pageSize = 10;
  int objSize = 5;
  double numObjects = mylist.size();
  double numObjectsPerPage = pageSize/objSize;
  numSlabs = (numObjects/numObjectsPerPage)*(1/numDesc);
  cout << numSlabs << endl;
  double sizeSlab =  numObjects / numSlabs;
  cout << "Size of each slab: " << sizeSlab << endl;
  int fileNum = 1;
  string fileName;
  char fileN[5];
  int i = 0;
  for (it=mylist.begin(); it!=mylist.end();)
  {
	i = 0;
	ostringstream buffer;
	buffer << fileNum;
	fileName = buffer.str();
	
	cout << fileName << endl;
	for (int inn = 0; inn < fileName.length(); inn++)
	{
		fileN[inn] = fileName[inn];
	}
	ofstream myfile(fileN);
	if(myfile.is_open())
	{
	while(i < sizeSlab)
	{
		myfile << *it << endl;
		cout << fileNum << ": " << *it << endl;
		i++;
		++it;
	}
	}
	else
	{
		myfile.close();
	}
	fileNum++;
  }
  return 0;
}