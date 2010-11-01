// list::sort
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype>
#include <math.h>
using namespace std;

// comparison, not case sensitive.
bool compare_nocase1 (string first, string second)
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
bool compare_nocase2 (string first, string second)
{
  unsigned int i=0;
  char tempint = 0;
  
  int temp1=0, temp2=0;
  int pos11 = first.find_first_of(",");
  pos11 = first.find_first_of(",",pos11+1);
  int pos12 = first.find_first_of(",",pos11+1);
  string sub1 = first.substr(pos11+1, pos12-pos11-1);
  istringstream buffer1(sub1);
  buffer1 >> temp1;

  int pos21 = second.find_first_of(",");
  pos21 = second.find_first_of(",",pos21+1);
  int pos22 = second.find_first_of(",",pos21+1);
  string sub2 = second.substr(pos21+1, pos22-pos21-1);
  istringstream buffer2(sub2);
  buffer2 >> temp2;
  //cout << sub1 << " " << pos11 << " " << pos12 << " " << sub2 << " " << pos21 << " " << pos22 << endl;
  //cout << first << " " << second << endl;
  if(temp1 < temp2) return true;
  else return false;
	
}
bool compare_nocase3 (string first, string second)
{
  unsigned int i=0;
  char tempint = 0;
  
  int temp1=0, temp2=0;
  int pos11 = first.find_first_of(",");
  pos11 = first.find_first_of(",",pos11+1);
  pos11 = first.find_first_of(",",pos11+1);
  int pos12 = first.find_first_of(",",pos11+1);
  string sub1 = first.substr(pos11+1, pos12-pos11-1);
  istringstream buffer1(sub1);
  buffer1 >> temp1;

  int pos21 = second.find_first_of(",");
  pos21 = second.find_first_of(",",pos21+1);
  pos21 = second.find_first_of(",",pos21+1);
  int pos22 = second.find_first_of(",",pos21+1);
  string sub2 = second.substr(pos21+1, pos22-pos21-1);
  istringstream buffer2(sub2);
  buffer2 >> temp2;

  if(temp1 < temp2) return true;
  else return false;
	
}
bool compare_nocase4 (string first, string second)
{
  unsigned int i=0;
  char tempint = 0;
  
  int temp1=0, temp2=0;
  int pos11 = first.find_first_of(",");
  pos11 = first.find_first_of(",",pos11+1);
  pos11 = first.find_first_of(",",pos11+1);
  pos11 = first.find_first_of(",",pos11+1);
  int pos12 = first.find_first_of(",",pos11+1);
  string sub1 = first.substr(pos11+1, pos12-pos11-1);
  istringstream buffer1(sub1);
  buffer1 >> temp1;

  int pos21 = second.find_first_of(",");
  pos21 = second.find_first_of(",",pos21+1);
  pos21 = second.find_first_of(",",pos21+1);
  pos21 = second.find_first_of(",",pos21+1);
  int pos22 = second.find_first_of(",",pos21+1);
  string sub2 = second.substr(pos21+1, pos22-pos21-1);
  istringstream buffer2(sub2);
  buffer2 >> temp2;

  if(temp1 < temp2) return true;
  else return false;
	
}
bool compare_nocase5 (string first, string second)
{
  unsigned int i=0;
  char tempint = 0;
  int temp1=0, temp2=0;
  int pos11 = first.find_first_of(",");
  pos11 = first.find_first_of(",",pos11+1);
  pos11 = first.find_first_of(",",pos11+1);
  pos11 = first.find_first_of(",",pos11+1);
  pos11 = first.find_first_of(",",pos11+1);
  string sub1 = first.substr(pos11+1, first.length()-1);
  istringstream buffer1(sub1);
  buffer1 >> temp1;

  int pos21 = second.find_first_of(",");
  pos21 = second.find_first_of(",",pos21+1);
  pos21 = second.find_first_of(",",pos21+1);
  pos21 = second.find_first_of(",",pos21+1);
  pos21 = second.find_first_of(",",pos21+1);
  string sub2 = second.substr(pos21+1, second.length()-1);
  istringstream buffer2(sub2);
  buffer2 >> temp2;
  if(temp1 < temp2) return true;
  else return false;
}

list<string> sortObjects(string fileName, int check)
{
	list<string> mylist;
	int count = 0;
	string line;
	string temp = "C:\\Preetika\\MWD\\ProjectCode\\STR\\";
	fileName = temp.append(fileName);
	fileName = fileName.append(".txt");
	ifstream myfile((char *)fileName.c_str());
	if(myfile.is_open())
	{
		while(myfile.good())
		{
			getline(myfile, line);
			if(line != ""){
			mylist.push_back(line);
			}
		}
		myfile.close();
		remove((char *)fileName.c_str());
	}
	else 
	{
		cout << "Unable to open file. " << fileName << endl;
	}
	if(check == 1)
	{
		mylist.sort(compare_nocase1);
	}
	else if(check == 2)
	{
		mylist.sort(compare_nocase2);
	}
	else if(check == 3)
	{
		mylist.sort(compare_nocase3);
	}
	else if(check == 4)
	{
		mylist.sort(compare_nocase4);
	}
	else if(check == 5)
	{
		mylist.sort(compare_nocase5);
	}
	return mylist;
}
int main ()
{
	list<string> fName;
	list<string> fNamePrev;
	list<string> mylist;
	list<string>::iterator it;
	fNamePrev.push_back("1");
	double numSlice;
	int noSlice;
	int numObjects;
	int numObjPPage = 5;
	int numDimension = 5;
	int numObjPSlice;
	for(int counter = 1; counter <= 5; counter++)
	{
		cout << "Counter: " << counter << endl;
		while(!fNamePrev.empty())
		{
			string tempFName = fNamePrev.front();
			mylist = sortObjects(tempFName, counter);
			//cout << "mylist contains:" << endl;
			//if(counter == 2){
			//cout << "########################" << endl;
			for (it=mylist.begin(); it!=mylist.end(); it++)
			//	cout << "SORTED: " << *it << endl;
			//}
			numObjects = mylist.size();
			numSlice = (double)numObjects/numObjPPage;
			//cout << "No Slice1: " << numSlice << endl;
			numSlice = pow(numSlice,(double)1/numDimension);
			noSlice = numSlice;
			if(numSlice > noSlice)
			{
				noSlice++;
			}
			//cout << "Number of slices: " << numSlice << endl;
			numObjPSlice = numObjects/noSlice;
			double numObjPSlice1 = (double)numObjects/noSlice;
			//cout << "ACTUAL: " << numObjPSlice1 << endl;
			if(numObjPSlice1 > numObjPSlice)
			{
				numObjPSlice++;
			}
			//cout << "Number of objects per slice: " << numObjPSlice << endl;
			string fileN;
			for (it=mylist.begin(); it!=mylist.end();)
			{
			for(int innerCounter = 1; innerCounter <= noSlice; innerCounter++)
			{
				//cout << "writing to slice " << innerCounter << endl;
				ostringstream buffer;
				buffer << innerCounter;
				string tempFName1 = tempFName;
				fileN = "";
				fileN = tempFName1.append(buffer.str());
				//cout << "File Name: " << fileN << endl;
				fName.push_back(fileN.c_str());
				string temp = "C:\\Preetika\\MWD\\ProjectCode\\STR\\";
				fileN = temp.append(fileN);
				fileN = fileN.append(".txt");
				ofstream sliceFile((char *)fileN.c_str());
				int j = 0;
				if(sliceFile.is_open())
				{
					while(j < numObjPSlice && it!=mylist.end())
					{
						sliceFile << *it << endl;
						//cout << innerCounter << " " << *it << endl;
						++it;
						j++;
					}
				}
				else
				{
					sliceFile.close();
				}
			}
			}

			fNamePrev.pop_front();
		}
		while(!fName.empty())
		{
			fNamePrev.push_back(fName.front());
			fName.pop_front();
		}
	}
	fNamePrev.sort();
	list<string> finalListObjects;
	string line;
	for (it=fNamePrev.begin(); it!=fNamePrev.end();++it)	
	{
		//cout << *it << endl;
		string tempFName = "C:\\Preetika\\MWD\\ProjectCode\\STR\\";
		tempFName = tempFName.append(*it);
		tempFName = tempFName.append(".txt");
		ifstream file((char *)tempFName.c_str());
		if(file.is_open())
		{
			while(file.good())
			{
				getline(file, line);
				if(line != "")
				{
					finalListObjects.push_back(line);
				}
			}
			file.close();
			remove((char *)tempFName.c_str());
		}
		else 
		{
			cout << "Unable to open file. " << tempFName << endl;
		}		
	}
	cout << "Number of objects: " << finalListObjects.size() << endl;
	int count = 0;
	string temp;
	int fileC = 1;
	for (it=finalListObjects.begin(); it!=finalListObjects.end();)	
	{
		count = 1;
		temp = "C:\\Preetika\\MWD\\ProjectCode\\STR\\";
		ostringstream t;
		t << fileC;
		temp = temp.append(t.str());
		temp = temp.append(".txt");
		ofstream ffile((char *)temp.c_str());
		if(ffile.is_open())
		{
			while(count <= numObjPPage && it!=finalListObjects.end())
			{
				ffile << *it << endl;
				++it;
				count++;
			}
		}
		else
		{
			ffile.close();
		}
		fileC++;
	}
	return 0;
}