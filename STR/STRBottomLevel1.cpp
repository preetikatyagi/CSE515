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
int indexDesc = 0;
int minmax = 0;
int numDesc = 0; //5;
int diskSize = 0; //420;
string filePath = "C:\\Preetika\\MWD\\ProjectCode\\STR\\";
// Function to compare the L values
bool compare_nocase1 (string first, string second)
{
	int localIndex = indexDesc;
	unsigned int temp1=0, temp2=0;
	int position1 = 0;
	
	if(localIndex == 0)
	{
		string substr01 = first.substr(0,first.find_first_of(","));
		string substr02 = second.substr(0,second.find_first_of(","));
		istringstream buffer1(substr01);
		buffer1 >> temp1;
		istringstream buffer2(substr02);
		buffer2 >> temp2;
	}
	else
	{
		position1 = 0;
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
	}
	if(temp1 < temp2) return true;
	else return false;		
}

// Function to compare the internal nodes of the tree
bool compare_nocase2 (string first, string second)
{
	int localIndex = minmax + indexDesc;
	unsigned int temp1=0, temp2=0;
	int position1 = 0;
	if(localIndex == 0)
	{
		position1 = first.find_first_of(",");
		string substr01 = first.substr(0,position1);
		position1 = second.find_first_of(",");
		string substr02 = second.substr(0,position1);
		istringstream buffer1(substr01);
		buffer1 >> temp1;
		istringstream buffer2(substr02);
		buffer2 >> temp2;
	}
	else
	{
		position1 = 0;
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
	}
	if(temp1 < temp2) return true;
	else return false;		
}

// Function to return sorted entries based on Lth parameter
list<string> sortObjects(string fileName, int check)
{
	list<string> mylist;
	int count = 0;
	string line;
	string temp = filePath;
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
		//cout << "Unable to open file. " << fileName << endl;
	}
	indexDesc = check;
	mylist.sort(compare_nocase1);
	indexDesc = 0;
	return mylist;
}
int main ()
{
	// Take input from user - number of descriptors and disk page size
	cout << "Please enter the number of descriptors " << endl;
	cin >> numDesc;
	cout << "Please enter the disk page size " << endl;
	cin >> diskSize;

	list<string> fName;
	list<string> fNamePrev;
	list<string> mylist;
	list<string>::iterator it;
	fNamePrev.push_back("1");
	double numSlice;
	int noSlice;
	int numObjects = 0;
	int numPPage1 = diskSize/((4*(numDesc+1)) + 4);
	int numObjPPage = numPPage1; 
	cout << numObjPPage << endl;
	int numDimension = numDesc;
	int numObjPSlice;

	// This part creates the data file
	for(int counter = 1; counter <= numDesc; counter++)
	{
		while(!fNamePrev.empty())
		{
			string tempFName = fNamePrev.front();
			mylist = sortObjects(tempFName, counter);
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
				//cout << fileN.c_str() << endl;
				string temp = filePath;
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
	// Gather all the objects in a list after performing STR algo
	fNamePrev.sort();
	list<string> finalListObjects;
	string line;
	for (it=fNamePrev.begin(); it!=fNamePrev.end();++it)	
	{
		string tempFName = filePath;
		tempFName = tempFName.append(*it);
		tempFName = tempFName.append(".txt");
		ifstream file((char *)tempFName.c_str());
		if(file.is_open())
		{
			//cout << tempFName.c_str() << endl;
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
			//cout << "Unable to open file... " << tempFName << endl;
		}		
	}
	
	// Write all the objects to data file according to the page size
	int count = 0;
	string temp;
	temp = filePath;
	temp = temp.append("STRLeaf.txt");
	ofstream ffile((char *)temp.c_str(), ios::binary);
	int fileC = 1;
	int seekPointer = 0;
	int pageEntries = 0;
	int checkpoint = 0;
	for (it=finalListObjects.begin(); it!=finalListObjects.end();)	
	{
		
		count = 1;
		if(ffile.is_open())
		{
			pageEntries = 0;
			ffile.seekp(seekPointer);
			ffile.write((char*)&pageEntries, sizeof(int));
			int done1 = 1;
			cout << "before while" << endl;
			while(count <= numObjPPage && it!=finalListObjects.end())
			{
				//ffile << *it << endl;
				cout << "COUNT: " << count << endl;
				done1 = 0;
				checkpoint++;
				pageEntries++;
				int prevpos = 0;
				int pos = 0;
				string tempStr = *it;
				unsigned int abc;
				 //= (tempStr).c_str();
				//cout << "String: " << tempStr << endl;
				prevpos = tempStr.find_first_of(",",0);
				int loop = 0;
				int done = 0;
				abc = 0;
				ffile.write((char*)&abc, sizeof(int));
				while(!done)
				{
					pos = tempStr.find_first_of(",",prevpos+1);
					istringstream buffer1(tempStr.substr(prevpos+1, pos-prevpos-1));
					buffer1 >> abc;
					//cout << abc << " ";
					prevpos = pos;
					loop++;
					
					ffile.write((char*)&abc, sizeof(int));
					if(loop == numDesc)
					{
						done = 1;
						break;
					}
				}	
				++it;
				count++;	
			}
			
			ffile.seekp(seekPointer);
			cout << seekPointer << endl;
			ffile.write((char*)&pageEntries, sizeof(int));
			cout << pageEntries << endl;
			seekPointer = seekPointer + diskSize;
		}
		else
		{
			ffile.close();
		}
		fileC++;
	}
	cout << "checkpoint: " << checkpoint << endl;
	int height = 0;
	ffile.seekp(seekPointer);
	// Now create the second internal node level to leaf level
	int count1 = 0;
	int blockCounter = 0;
	int getSeekPointer = 0;
	int setSeekPointer = 0;
	int setSeekPointerLocal = 0;
	int noOfInternalNodePPage = 2;//diskSize/(4*(numDesc+1)); //Since node is of double size as that of the data entry
	int localSetSeekPointer2 = 0;
	string secondToLeaf;
	string internalData = "";
	string internalData3 = "";
	string internalData4 = "";
	secondToLeaf = filePath;
	secondToLeaf = secondToLeaf.append("STRTree.txt");
	
	ofstream internalNode1((char *)secondToLeaf.c_str());
	ifstream leafObjects((char *)temp.c_str());
	if(leafObjects.is_open())
	{
		while(leafObjects.good())
		{
			internalData = "";
			internalData3 = "";
			internalData4 = "";
			list<string> sList;
			leafObjects.seekg(getSeekPointer);
			unsigned int startno = 0;
			leafObjects.read((char *)&startno, sizeof(int));
			ostringstream buffer2;
			buffer2 << startno;
			cout << "START: " << buffer2.str() << endl;
			for(int a1 = 0; a1 < startno; a1++)//for(int a1 = 0; a1 < numObjPPage; a1++)
			{
				//getline(leafObjects, line);
				unsigned int abc = 0;
				string imageid;
				int loc = 0;
				line = "";
				string line1 = "";
				while(loc < (numDesc+1))
				{
					if(loc == 0)
					{
						leafObjects.read((char *)&abc, sizeof(int));
						line1 += "0,";
					}
					else
					{
						leafObjects.read((char *)&abc, sizeof(int));
						//cout << "abc: " << abc << endl;
						ostringstream buffer;
						buffer << abc;
						line1 += buffer.str() + ",";
					}
					//cout << loc << endl;
					loc++;
					
				}
				//cout << endl;
				line1 = line1.substr(0,line1.length()-1);
				cout << line1 << endl;
				if(line1 != "")
				{
					sList.push_back(line1);
				}
			}
			//cout << endl;
			cout << endl;
			cout << "NODE SIZE: " << sList.size() << endl;
			// Write loop
			int position1 = 0;
			int position2 = 0;
			for(int inner = 1; inner <= sList.size(); inner++)//for(int inner = 1; inner <= numDimension; inner++)
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
					internalData3 += sub1 + ",";
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
					internalData4 += sub1 + ",";
				}
			}
			indexDesc = 0;
			// Write loop
			internalData = internalData3 + internalData4;
			count1++;
			if(internalData != "")
			{
				ostringstream strGetSeekPointer;
				strGetSeekPointer << getSeekPointer;
				internalData = internalData.append("-");
				internalData = internalData.append(strGetSeekPointer.str());
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
					//internalNode1 << internalData << endl;//ascii write
					//Write in binary form
					unsigned int dataminmax = 0;
					int done = 0;
					int pos = 0;
					int prevpos = 0;
					int loop = 0;
					int sizenode = sList.size();
					internalNode1.write((char *)&sizenode, sizeof(int));
					while(loop < sizenode)
					{
						if(loop == 0)
						{
							pos = internalData.find_first_of(",",0);
						}
						else
						{
							pos = internalData.find_first_of(",",prevpos+1);
						}
						istringstream buffer1(internalData.substr(prevpos+1, pos-prevpos-1));
						buffer1 >> dataminmax;
						//cout << abc << " ";
						internalNode1.write((char *)&dataminmax, sizeof(int));
						//cout << dataminmax << " ";
						prevpos = pos;
						loop++;
					}
					int datapointer = 0;
					pos = internalData.find_first_of(",",prevpos+1);
					istringstream buffer1(internalData.substr(prevpos+1, pos-prevpos-1));
					buffer1 >> datapointer;
					internalNode1.write((char *)&datapointer, sizeof(int));
					//cout << datapointer << endl << endl;
					localSetSeekPointer2 = internalNode1.tellp();
				}

			}
			getSeekPointer = getSeekPointer + diskSize;
			
			if(count1 == noOfInternalNodePPage)
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
		setSeekPointer = setSeekPointer + diskSize;
		blockCounter++;	
	}
	
	count1 = 0;
	leafObjects.close();
	internalNode1.close();
	string internalData1 = "";
	int startPointer = setSeekPointer;
	int getSeekPointer1 = 0;
	int setSeekPointer1 = setSeekPointer;
	int endPointer = 0;
	int perBlock = noOfInternalNodePPage;
	int numberOfBlock = blockCounter;
	blockCounter = 0;
	int localSetSeekPointer1;
	int sizeNode = 0;

	fstream internalNode((char *)secondToLeaf.c_str(), ios::in | ios::out | ios::binary);
	
	if(internalNode.is_open())
	{
		while(numberOfBlock != 0)
		{
			for (int global = 0; global < numberOfBlock; global++)
			{
				list<string> slist1;
				list<string> slist2;
				internalNode.seekg(getSeekPointer1);
				/*for(int a1 = 0; a1 < perBlock; a1++)
				{
					//getline(internalNode, line);//read in ascii
					//write code to read in binary format//////////////////////////
									
					if((internalNode.tellg()) >= getSeekPointer1 + diskSize)
					{
						continue;
					}
					
					if(line != "")
					{
						slist1.push_back(line);
						slist2.push_back(line);
					}
				}*/
				
				internalNode.read((char *)&sizeNode, sizeof(int));
				for(int a1 = 0; a1 < sizeNode; a1++)
				{
					unsigned int abc = 0;
					string imageid;
					int loc = 0;
					line = "";
					string line1 = "";
					while(loc < (numDesc*2))
					{
						leafObjects.read((char *)&abc, sizeof(int));
						//cout << "abc: " << abc << endl;
						ostringstream buffer;
						buffer << abc;
						line1 += buffer.str() + ",";
						//cout << loc << endl;
						loc++;
					}
					if(line1 != "")
					{
						slist1.push_back(line1);
						slist2.push_back(line1);
					}
					leafObjects.read((char *)&abc, sizeof(int));
				}
		
				// Write code for MBR
				string internalData1 = "";
				string internalData2 = "";
			
				for(int inn = 0; inn < numDesc; inn++)
				{
					indexDesc = inn;
					minmax = 0;
					slist1.sort(compare_nocase2);
					int localIndex = indexDesc + minmax;
					int position1 = 0;
					int position2 = 0;
					string sub1 = "";
					string sub2 = "";
					if(localIndex == 0)
					{
						position1 = slist1.front().find_first_of(",");
						sub1 = slist1.front().substr(0,position1);
					}
					else
					{
						position1 = 0;
						for(int inner = 0; inner < localIndex; inner++)
						{
							position1 = slist1.front().find_first_of(",", position1+1);
						}
						position2 = 0;
						position2 = slist1.front().find_first_of(",",position1+1);
						sub1 = slist1.front().substr(position1+1, position2-position1-1);
  					}
					internalData1 += sub1 + ",";
					
					indexDesc = inn;
					minmax = numDesc;
					slist2.sort(compare_nocase2);
					localIndex = indexDesc + minmax;
					position1 = 0;
					position2 = 0;
					sub1 = "";
					sub2 = "";
					if(localIndex == 0)
					{
						position2 = slist1.front().find_first_of(",");
						sub2 = slist2.back().substr(0,position1);
					}
					else
					{
						position1 = 0;
						for(int inner = 0; inner < localIndex; inner++)
						{
							position1 = slist2.back().find_first_of(",",position1+1);
						}
						position2 = 0;
						position2 = slist2.back().find_first_of(",",position1+1);
						sub2 = slist2.back().substr(position1+1, position2-position1-1);
					}
					internalData2 += sub2 + ",";
				}
				// create MBR Entry
		
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
					//internalNode << fInternalData << getSeekPointer1 << endl;//write in ascii
					// Write to file in binary format////////////////////////
					unsigned int dataminmax = 0;
					int done = 0;
					int pos = 0;
					int prevpos = 0;
					int loop = 0;
					//int sizenode = 0;
					internalNode.write((char *)&sizeNode, sizeof(int));
					while(loop < 2*numDesc)
					{
						if(loop == 0)
						{
							pos = fInternalData.find_first_of(",",0);
						}
						else
						{
							pos = fInternalData.find_first_of(",",prevpos+1);
						}
						istringstream buffer1(fInternalData.substr(prevpos+1, pos-prevpos-1));
						buffer1 >> dataminmax;
						//cout << abc << " ";
						internalNode.write((char *)&dataminmax, sizeof(int));
						//cout << dataminmax << " ";
						prevpos = pos;
						loop++;
					}
					internalNode.write((char *)&getSeekPointer1,sizeof(int));

				}
				localSetSeekPointer1 = internalNode.tellp();
				getSeekPointer1 = getSeekPointer1 + diskSize;
				if(count1 == perBlock)
				{
					count1 = 0;
					blockCounter++;
					setSeekPointer1 = setSeekPointer1 + diskSize;
				}
				else if (numberOfBlock == global-1)
				{
					blockCounter++;
				}
			}	
			if(count1 == 0)
			{
				endPointer = setSeekPointer1;
			}
			endPointer = setSeekPointer1;
			startPointer = setSeekPointer;
			setSeekPointer1 = endPointer;
			numberOfBlock = blockCounter;
			blockCounter = 0;
		}
	}	
	
	internalNode.flush();
	internalNode.close();

	return 0;
}