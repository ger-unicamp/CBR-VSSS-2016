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
    if(argc != 3) {
		cout << "Usage: " << argv[0] << " <cam number>" << " <primary_color>"<<  endl;
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

    color_range primary_color = strcmp(argv[2], "yellow") == 0 ? yellow : blue;
    color_range opponent_color = strcmp(argv[2], "yellow") == 0 ? blue : yellow;

    printf("Primary color is: %s", strcmp(argv[2], "yellow") == 0 ? "yellow" : "blue");

    color_range secondary_color[3] = {green, purple, red}; // define secondary colors


    bool unset = true;

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
    
        if(unset)
        {
            set_border_manually(frame, Point2f(111,47), Point2f(566,10), Point2f(579, 415), Point2f(135, 421));
            unset = false;
        }

        vector<Circle> primary_circles, opponent_circles, secondary_circles[3], ball_circles;

        find_circles(transformed_frame, ball_color, ball_circles);
        find_circles(transformed_frame, opponent_color, opponent_circles);
        find_circles(transformed_frame, primary_color, primary_circles);
        for(int i = 0; i < 3; i++)
            find_circles(transformed_frame, secondary_color[i], secondary_circles[i]);

        // A distancia entre o centro do amarelo e o centro do verde deve ser menor que 22
        for(int i = 0; i < primary_circles.size(); i++) // searches all primary_color circles
        {

            int index = 0, type = 0;
            float min_dist = 1e8;
            for(int j = 0; j < 3; j++) // finds closeest secondary color
                for(int k = 0; k < secondary_circles[j].size(); k++)
                    if(point_distance(primary_circles[i].center, secondary_circles[j][k].center) < min_dist)
                    {
                        min_dist = point_distance(primary_circles[i].center, secondary_circles[j][k].center);
                        index = k, type = j;
                    }

            if(primary_circles[i].radius < 6 || min_dist > 22)
                continue; // if the radius of the yellow circle is less than 8 or the secondary color is too far away (> 22), it is not a robot

            printf("\nx_robo%d=%.1f, y_robo%d=%.1f\n", type, primary_circles[i].center.x, type, primary_circles[i].center.y);
            printf("robo%d_dir: %.1lf %.1lf\n", type, secondary_circles[type][index].center.x - primary_circles[i].center.x, secondary_circles[type][index].center.y - primary_circles[i].center.y);
        }

        sort(opponent_circles.begin(), opponent_circles.end());
        for(int i = 0; i < 3 && i < opponent_circles.size(); i++)
            printf("\nx_opponent%d=%.1f, y_opponent%d=%.1f\n", i, opponent_circles[i].center.x, i, opponent_circles[i].center.y);

        sort(ball_circles.begin(), ball_circles.end());
        if(ball_circles.size())
            printf("\nx_ball=%.1f, y_ball=%.1f\n", ball_circles[0].center.x, ball_circles[0].center.y);


        imshow("MyVideo_transformed", transformed_frame); //show the frame in "MyVideo_transformed" window

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break; 
		}
    }
    return 0;

}
