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


		vector<Circle> yellow_circles, green_circles, red_circles, purple_circles;
        find_circles(transformed_frame, yellow, yellow_circles);
        find_circles(transformed_frame, green, green_circles);
        find_circles(transformed_frame, purple, purple_circles);
        find_circles(transformed_frame, red, red_circles);

        printf("\nYellow:\n");
        for(int i = 0; i < yellow_circles.size(); i++)
            printf("%.1lf %.1lf %.1f\n", yellow_circles[i].center.x, yellow_circles[i].center.y, yellow_circles[i].radius);

        printf("Green:\n");
        for(int i = 0; i < green_circles.size(); i++)
            printf("%.1lf %.1lf %.1f\n", green_circles[i].center.x, green_circles[i].center.y, green_circles[i].radius);

        printf("Purple:\n");
        for(int i = 0; i < purple_circles.size(); i++)
            printf("%.1lf %.1lf %.1f\n", purple_circles[i].center.x, purple_circles[i].center.y, purple_circles[i].radius);

        printf("Red:\n");
        for(int i = 0; i < red_circles.size(); i++)
            printf("%.1lf %.1lf %.1f\n", red_circles[i].center.x, red_circles[i].center.y, red_circles[i].radius);


        color_range primary_color = yellow; // or blue // define primary color
        color_range secondary_color[3] = {green, purple, red}; // define secondary colors

        vector<Circle> primary_circles, secondary_circles[3];

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

            if(yellow_circles[i].radius < 6 || min_dist > 22)
                continue; // if the radius of the yellow circle is less than 8 or the secondary color is too far away (> 22), it is not a robot

            printf("\nx_robo%d=%.1f, y_robo%d=%.1f\n", type, primary_circles[i].center.x, type, primary_circles[i].center.y);
            printf("robo%d_dir: %.1lf %.1lf\n", type, secondary_circles[type][index].center.x - primary_circles[i].center.x, secondary_circles[type][index].center.y - primary_circles[i].center.y);

/*            for(int j = 0; j < purple_circles.size(); j++)
            {
                if (point_distance(yellow_circles[i].center,purple_circles[j].center) <= 22)
                {
                    printf("\nx_robo2=%.1f, y_robo2=%.1f\n",yellow_circles[i].center.x, yellow_circles[i].center.y);
                    printf("robo2_dir: %.1lf %.1lf\n", purple_circles[j].center.x - yellow_circles[i].center.x, purple_circles[j].center.y - yellow_circles[i].center.y);
                    break;
                }
            }

            //se a distancia entre amarelo e verde e menor que 22
            for(int j = 0; j < red_circles.size(); j++)
            {
                if (point_distance(yellow_circles[i].center,red_circles[j].center) <= 22)
                {
                    printf("\nx_robo3=%.1f, y_robo3=%.1f\n",yellow_circles[i].center.x, yellow_circles[i].center.y);
                    printf("robo3_dir: %.1lf %.1lf\n", red_circles[j].center.x - yellow_circles[i].center.x, red_circles[j].center.y - yellow_circles[i].center.y);
                    break;
                }
            }*/
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
