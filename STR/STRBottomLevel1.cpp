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

// Global Variables
#define NUMDESC 5
int indexDesc = 0;
int numDesc = 5;
// comparison, not case sensitive.
bool compare_nocase1 (string first, string second)
{
	int localIndex = indexDesc;
	int temp1=0, temp2=0;
	int position1 = 0;
	
	for(int inner = 0; inner < localIndex; inner++)
	{
		position1 = first.find_first_of(",", position1+1);
	}
	int position2 = 0;
	position2 = first.find_first_of(",",position1+1);
	string sub1 = first.substr(position1+1, position2-position1-1);
	istringstream buffer1(sub1);
	buffer1 >> temp1;
  
	position1 = 0;
	for(int inner = 0; inner < localIndex; inner++)
	{
		position1 = second.find_first_of(",",position1+1);
	}
	position2 = 0;
	position2 = second.find_first_of(",",position1+1);
	sub1 = second.substr(position1+1, position2-position1-1);
	istringstream buffer2(sub1);
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
	indexDesc = check;
	mylist.sort(compare_nocase1);
	indexDesc = 0;
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
	int numObjects = 0;
	int diskSize = 1024;
	int numObjPPage = 5;
	int numDimension = numDesc;
	int numObjPSlice;
	for(int counter = 1; counter <= numDesc; counter++)
	{
		//cout << "Counter: " << counter << endl;
		while(!fNamePrev.empty())
		{
			string tempFName = fNamePrev.front();
			mylist = sortObjects(tempFName, counter);
			for (it=mylist.begin(); it!=mylist.end(); it++)
			numObjects = mylist.size();
			numSlice = (double)numObjects/numObjPPage;
			numSlice = pow(numSlice,(double)1/numDimension);
			noSlice = numSlice;
			if(numSlice > noSlice)
			{
				noSlice++;
			}
			numObjPSlice = numObjects/noSlice;
			double numObjPSlice1 = (double)numObjects/noSlice;
			if(numObjPSlice1 > numObjPSlice)
			{
				numObjPSlice++;
			}
			string fileN;
			for (it=mylist.begin(); it!=mylist.end();)
			{
			for(int innerCounter = 1; innerCounter <= noSlice; innerCounter++)
			{
				ostringstream buffer;
				buffer << innerCounter;
				string tempFName1 = tempFName;
				fileN = "";
				fileN = tempFName1.append(buffer.str());
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
	//cout << "Number of objects: " << finalListObjects.size() << endl;
	int count = 0;
	string temp;
	temp = "C:\\Preetika\\MWD\\ProjectCode\\STR\\";
	temp = temp.append("STRLeaf.txt");
	ofstream ffile((char *)temp.c_str());
	int fileC = 1;
	int seekPointer = 0;
	for (it=finalListObjects.begin(); it!=finalListObjects.end();)	
	{
		count = 1;
		if(ffile.is_open())
		{
			ffile.seekp(seekPointer);
			while(count <= numObjPPage && it!=finalListObjects.end())
			{
				ffile << *it << endl;
				++it;
				count++;
			}
			seekPointer = seekPointer + diskSize;
		}
		else
		{
			ffile.close();
		}
		fileC++;
	}

	// Now create the second internal node level to leaf level
	int count1 = 0;
	int blockCounter = 0;
	int getSeekPointer = 0;
	int setSeekPointer = 0;
	int setSeekPointerLocal = 0;
	int noOfInternalNodePPage = 3;
	int localSetSeekPointer2 = 0;
	string secondToLeaf;
	string internalData = "";
	secondToLeaf = "C:\\Preetika\\MWD\\ProjectCode\\STR\\";
	secondToLeaf = secondToLeaf.append("STRSecondToLeaf.txt");
	
	ofstream internalNode1((char *)secondToLeaf.c_str());
	ifstream leafObjects((char *)temp.c_str());
	if(leafObjects.is_open())
	{
		while(leafObjects.good())
		{
			internalData = "";
			list<string> sList;
			leafObjects.seekg(getSeekPointer);
			for(int a1 = 0; a1 < numObjPPage; a1++)
			{
				getline(leafObjects, line);
				if(line != "")
				{
					sList.push_back(line);
				}
			}
			// Write loop
			int position1 = 0;
			int position2 = 0;
			for(int inner = 1; inner <= numDimension; inner++)
			{
				indexDesc = inner;
				sList.sort(compare_nocase1);
				position1 = 0;
				if(!sList.empty())
				{
					for(int inner1 = 0; inner1 < indexDesc; inner1++)
					{
						position1 = sList.front().find_first_of(",", position1+1);
					}
					position2 = 0;
					position2 = sList.front().find_first_of(",",position1+1);
					string sub1 = sList.front().substr(position1+1, position2-position1-1);
					internalData += sub1 + ",";
				}
				position1 = 0;
				if(!sList.empty())
				{
					for(int inner1 = 0; inner1 < indexDesc; inner1++)
					{
						position1 = sList.back().find_first_of(",", position1+1);
					}
					position2 = 0;
					position2 = sList.back().find_first_of(",",position1+1);
					string sub1 = sList.back().substr(position1+1, position2-position1-1);
					internalData += sub1 + ",";
				}
			}
			indexDesc = 0;
			// Write loop
			
			count1++;
			if(internalData != "")
			{
				ostringstream strGetSeekPointer;
				strGetSeekPointer << getSeekPointer;
				internalData = internalData.append(strGetSeekPointer.str());
				//cout << internalData << endl;
			}
			
			// write to second to leaf level file
			if(internalNode1.is_open())
			{
				if(count1 == 1)
				{
					internalNode1.seekp(setSeekPointer);
				}
				else
				{
					internalNode1.seekp(localSetSeekPointer2);
				}
				if(internalData != "")
				{
					internalNode1 << internalData << endl;
					localSetSeekPointer2 = internalNode1.tellp();
					//cout << "JUMPOO " << count1 << " " << internalData << endl;
				}

			}
			getSeekPointer = getSeekPointer + diskSize;
			
			if(count1 == 3)
			{
				count1 = 0;
				blockCounter++;
				setSeekPointer = setSeekPointer + diskSize;
			}
		}
	}
		if(count1 == 0)
		{	
		}
		else
		{
			//cout << "JUMP------" << count1 << endl;
			setSeekPointer = setSeekPointer + diskSize;
			blockCounter++;	
		}
		//cout << "BLOCK COUNTER 1: " << blockCounter << endl;
	count1 = 0;
	leafObjects.close();
	internalNode1.close();
	string internalData1 = "";
	int startPointer = setSeekPointer;
	int getSeekPointer1 = 0;
	int setSeekPointer1 = setSeekPointer;
	int endPointer = 0;
	int perBlock = 3;
	int numberOfBlock = blockCounter;
	
	blockCounter = 0;
	
	int localSetSeekPointer1;
	fstream internalNode((char *)secondToLeaf.c_str(), ios::in | ios::out);
	if(internalNode.is_open())
	{
		while(numberOfBlock != 0)
		{
			for (int global = 0; global < numberOfBlock; global++)
			{
				list<string> slist1;
				internalNode.seekg(getSeekPointer1);
				for(int a1 = 0; a1 < perBlock; a1++)
				{
					getline(internalNode, line);
					if((internalNode.tellg()) >= getSeekPointer1 + diskSize)
					{
						continue;
					}
					if(line != "")
					{
						slist1.push_back(line);
					}
				}
				// create MBR Entry
				list<int> list1;
				list<int> list2;
				list<int> list3;
				list<int> list4;
				list<int> list5;
				int tempNum;
				for (it=slist1.begin(); it!=slist1.end();++it)	
				{
					string t1 = *it;
					int pos11 = t1.find_first_of(",");
					istringstream tempStr1(t1.substr(0,pos11));
					tempStr1 >> tempNum;
					list1.push_back(tempNum);

					int pos12 = t1.find_first_of(",", pos11+1);
					istringstream tempStr2(t1.substr(pos11+1, pos12-pos11-1));
					tempStr2 >> tempNum;
					list2.push_back(tempNum);

					int pos13 = t1.find_first_of(",", pos12+1);
					istringstream tempStr3(t1.substr(pos12+1, pos13-pos12-1));
					tempStr3 >> tempNum;
					list3.push_back(tempNum);

					int pos14 = t1.find_first_of(",", pos13+1);
					istringstream tempStr4(t1.substr(pos13+1, pos14-pos13-1));
					tempStr4 >> tempNum;
					list4.push_back(tempNum);

					int pos15 = t1.find_first_of(",", pos14+1);
					istringstream tempStr5(t1.substr(pos14+1, pos15-pos14-1));
					tempStr5 >> tempNum;
					list4.push_back(tempNum);

					int pos16 = t1.find_first_of(",", pos15+1);
					istringstream tempStr6(t1.substr(pos15+1, pos16-pos15-1));
					tempStr6 >> tempNum;
					list1.push_back(tempNum);

					int pos17 = t1.find_first_of(",", pos16+1);
					istringstream tempStr7(t1.substr(pos16+1, pos17-pos16-1));
					tempStr7 >> tempNum;
					list2.push_back(tempNum);

					int pos18 = t1.find_first_of(",", pos17+1);
					istringstream tempStr8(t1.substr(pos17+1, pos18-pos17-1));
					tempStr8 >> tempNum;
					list3.push_back(tempNum);

					int pos19 = t1.find_first_of(",", pos18+1);
					istringstream tempStr9(t1.substr(pos18+1, pos19-pos18-1));
					tempStr9 >> tempNum;
					list4.push_back(tempNum);

					int pos110 = t1.find_first_of(",", pos19+1);
					istringstream tempStr10(t1.substr(pos19+1, pos110-pos19-1));
					tempStr10 >> tempNum;
					list5.push_back(tempNum);
				}
				string internalData1 = "";
				string internalData2 = "";
				list1.sort();
				list2.sort();
				list3.sort();
				list4.sort();
				list5.sort();
				if(!list1.empty())
				{
					ostringstream buffer1;
					buffer1 << list1.front();
					internalData1 += buffer1.str() + ",";
					ostringstream buffer2;
					buffer2 << list1.back();
					internalData2 += buffer2.str() + ",";
				}
				if(!list2.empty())
				{
					ostringstream buffer1;
					buffer1 << list2.front();
					internalData1 += buffer1.str() + ",";
					ostringstream buffer2;
					buffer2 << list2.back();
					internalData2 += buffer2.str() + ",";
				}
				if(!list3.empty())
				{
					ostringstream buffer1;
					buffer1 << list3.front();
					internalData1 += buffer1.str() + ",";
					ostringstream buffer2;
					buffer2 << list3.back();
					internalData2 += buffer2.str() + ",";
				}
				if(!list4.empty())
				{
					ostringstream buffer1;
					buffer1 << list4.front();
					internalData1 += buffer1.str() + ",";
					ostringstream buffer2;
					buffer2 << list4.back();
					internalData2 += buffer2.str() + ",";
				}
				if(!list5.empty())
				{
					ostringstream buffer1;
					buffer1 << list5.front();
					internalData1 += buffer1.str() + ",";
					ostringstream buffer2;
					buffer2 << list5.back();
					internalData2 += buffer2.str() + ",";
				}
				count1++;
				string fInternalData = internalData1 + internalData2;
				if(count1 == 1)
				{
					internalNode.seekp(setSeekPointer1);
				}
				else
				{
					internalNode.seekp(localSetSeekPointer1);
				}
				if(fInternalData != "")
				{
					internalNode << fInternalData << getSeekPointer1 << endl;
					//cout << fInternalData << endl;
				}
				localSetSeekPointer1 = internalNode.tellp();
				getSeekPointer1 = getSeekPointer1 + diskSize;
				if(count1 == perBlock)
				{
					count1 = 0;
					blockCounter++;
					//cout << "BC: " << blockCounter << endl;
					setSeekPointer1 = setSeekPointer1 + diskSize;
				}
				else if (numberOfBlock == global-1)
				{
					blockCounter++;
				}
			}	
		
			if(count1 == 0)
			{
				//cout << "COUNT1: " << count1 << endl;
				endPointer = setSeekPointer1;
			}
			else
			{
				//cout << "COUNT2: " << count1 << endl;
				//blockCounter++;
				//endPointer = setSeekPointer1 + diskSize;
			}
			endPointer = setSeekPointer1;
			startPointer = setSeekPointer;
			setSeekPointer1 = endPointer;
			numberOfBlock = blockCounter;
			
		//	cout << "Number of Blocks " << numberOfBlock << endl;
			blockCounter = 0;
		}
		internalNode.seekg(9216);
		string l1 ="";
		getline(internalNode, l1);
		//cout << l1 << endl;
		getline(internalNode, l1);
		//cout << l1 << endl;
		getline(internalNode, l1);
		//cout << l1 << endl;
				getline(internalNode, l1);
		//cout << l1 << endl;
				getline(internalNode, l1);
	//	cout << l1 << endl;
	}	
	return 0;
}