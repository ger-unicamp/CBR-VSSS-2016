#include "video.hpp"
#include "videoio.hpp"
#include "videoio.hpp"
#include "highgui.hpp"
#include "opencv.hpp"
#include <iostream>
#include <math.h>

#include "ger_vsss.hpp"


int main(int argc, char* argv[])
{	
	// if did not receive expected number of arguments, prints usage instructions
	// the user must send the cam number as a parameter
    if(argc != 2) {
		cout << "Usage: " << argv[0] << " <cam number>" << endl;
		return -1;
    }


    VideoCapture cap(argv[1][0] - '0'); // opens the camera whose parameter was given

    if (!cap.isOpened())  // if not success, exits program and prints error message
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame size : " << dWidth << " x " << dHeight << endl; // prints image size

    while (1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        Mat transformed_frame = transform(frame);

		vector<Circle> yellow_circles, green_circles;

        find_circles(transformed_frame, yellow, yellow_circles);
        find_circles(transformed_frame, green, green_circles);

        printf("\nYellow:\n");
        for(int i = 0; i < yellow_circles.size(); i++)
            printf("%.1lf %.1lf %.1f\n", yellow_circles[i].center.x, yellow_circles[i].center.y, yellow_circles[i].radius);

        printf("Green:\n");
        for(int i = 0; i < green_circles.size(); i++)
            printf("%.1lf %.1lf %.1f\n", green_circles[i].center.x, green_circles[i].center.y, green_circles[i].radius);

// A distancia entre o centro do amarelo e o centro do verde deve ser menor que 22
        for(int i = 0; i < yellow_circles.size(); i++) //procura em todos os circulos amarelos
        {
			//se a distancia entre amarelo e verde e menor que 22
			for(int j = 0; j < green_circles.size(); j++)
	        	if (point_distance(yellow_circles[i].center,green_circles[j].center) <= 22)
	        	{
   		     		printf("\nx_robo=%.1f, y_robo=%.1f\n",yellow_circles[i].center.x, yellow_circles[i].center.y);
   		     		printf("robot_dir: %.1lf %.1lf\n", green_circles[j].center.x - yellow_circles[i].center.x, green_circles[j].center.y - yellow_circles[i].center.y);
   		     		break;
	        	}
        }

        imshow("MyVideo_transformed", transformed_frame); //show the frame in "MyVideo_transformed" window

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break; 
		}
    }
    return 0;

}
