//============================================================================
// Name        : SegmentSize.cpp
// Author      : Preetika Tyagi
// Description : This program takes the input image file and position of a pixel, and 
//				 calculates the size of a segment including the given pixel position.
//============================================================================

#include <Magick++.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <stack>

using namespace std;
using namespace Magick;

// 2D Array to store the status (whether the pixel has been visited or not) of pixels of an image of size upto 1000x1000
int segArr [1000][1000];
int segmentSize(Image image, int x, int y)
{
	// Two stacks to store the keep track of pixel positions of an image
	ColorYUV pixelColor;
	stack <int> stX;
	stack <int> stY;
	int row = x;
	int col = y;
	int segLabel = 1;

   	// Read the length and width of the give input image
	int imageLength = image.rows();
	int imageWidth = image.columns();
	
	// Displays the image length and width
	cout << "Image Length: " << imageLength << endl;
	cout <<  "Image Width: " << imageWidth << endl;

	// Initialize 2D array elements with values 0 of size of image
	for(int row = 0; row < imageWidth; row++)
	{
      	for(int col=0; col < imageLength; col++)
		{
			segArr[row][col] = 0;
		}
	}
	
	// Set the pushed pixel position as 1 in 2D array
	stX.push(row);
	stY.push(col);
	segArr[row][col] = segLabel;
	pixelColor = image.pixelColor(row, col);
	
	// Run the loop until the stacks become empty
	while((!stX.empty()) || (!stY.empty()))// stack not empty
	{
		// Pop out the top pixel position
		int rr = stX.top();
		int cc = stY.top();	
		stX.pop();
		stY.pop();
		
		// Traverse all possible surrounding pixels (8 pixels based on same color and boundary conditions) in the image and push them into stacks
		if((rr<(imageWidth-1)) && (image.pixelColor(rr+1,cc) == pixelColor) && (segArr[rr+1][cc] !=segLabel)){
			stX.push(rr+1);
			stY.push(cc);
			segArr[rr+1][cc] = segLabel;
		}
		if(rr>0 && image.pixelColor(rr-1,cc) == pixelColor && segArr[rr-1][cc] != segLabel) {
			stX.push(rr-1);
			stY.push(cc);
			segArr[rr-1][cc] = segLabel;
		}
		if(cc<imageLength-1 && image.pixelColor(rr,cc+1) == pixelColor && segArr[rr][cc+1] != segLabel) {
			stX.push(rr);
			stY.push(cc+1);
			segArr[rr][cc+1] = segLabel;
		}
		if(cc>0 && image.pixelColor(rr,cc-1) == pixelColor && segArr[rr][cc-1] != segLabel) {
			stX.push(rr);
			stY.push(cc-1);
			segArr[rr][cc-1] = segLabel;
		}
		if(cc<imageLength-1 && rr<imageWidth-1 && image.pixelColor(rr+1,cc+1) == pixelColor && segArr[rr+1][cc+1] != segLabel) {
			stX.push(rr+1);
			stY.push(cc+1);
			segArr[rr+1][cc+1] = segLabel;
		}
		if(cc>0 && (rr<imageWidth-1) && image.pixelColor(rr+1,cc-1) == pixelColor && segArr[rr+1][cc-1] != segLabel) {
			stX.push(rr+1);
			stY.push(cc-1);
			segArr[rr+1][cc-1] = segLabel;
		}
		if(cc>0 && rr>0 && image.pixelColor(rr-1,cc-1) == pixelColor && segArr[rr-1][cc-1] != segLabel) {
			stX.push(rr-1);
			stY.push(cc-1);
			segArr[rr-1][cc-1] = segLabel;
		}
		if(cc<imageLength-1 && rr>0 && image.pixelColor(rr-1,cc+1) == pixelColor && segArr[rr-1][cc+1] != segLabel) {
			stX.push(rr-1);
			stY.push(cc+1);
			segArr[rr-1][cc+1] = segLabel;
		}
	}

	//Count the number of pixels in the segment
	int segSize = 0;
	for(int row = 0; row < imageWidth; row++)
	{
      	for(int col=0; col < imageLength; col++)
		{
			if(segArr[row][col] == 1)
			{
				segSize++;
			}
		}
	}
	return segSize;
}
int main(int argc,char *argv[])
{
	InitializeMagick(*argv);
	// Declare and Initialize variables here
	// Image variable to read and perform operations on image
	Image image;
	try
	{
		if(argc != 3) 
		{
	        	cout << "Not a valid input format: segment <File Name>" << endl;
	        	return 0;
   		}

      	// Initialize variables for command line input to read the input image name
      	char **segmentCommand = &argv[1];
      	char **inputFileName = &argv[2];
      	string strSegmentCommand(*segmentCommand);
      	string strInputFileName(*inputFileName);   

		// Check if the input command is in valid format <segment <image name>>
      	if(strSegmentCommand != "segment") 
		{
		cout << "Not a valid input." << endl;
        return 0;  
      	}

      	// Read a file into image object
		image.read(strInputFileName);
      	image.quantizeColorSpace(YUVColorspace); //given in project specification
      	image.verbose(false); //Verbose: if set to true, it displays all the information of image segmentation
      
      	// Segment the input image (parameters given in project specifications)
      	image.segment(1.0,1.5); 
		int size = segmentSize(image, 200, 200);

		// Display the total number of segments
		cout << "Size of the segment: " << size << endl;

		// Write the image to a file
      	image.write("seg_" + strInputFileName);
    }
	catch( Exception &error_ ) 
	{
	        cout << "Caught exception: " << error_.what() << endl;
	        return 1;
	}
	return 0;
}