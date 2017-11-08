#include "video.hpp"
#include "videoio.hpp"
#include "videoio.hpp"
#include "highgui.hpp"
#include "opencv.hpp"
#include <iostream>
#include <math.h>

#include "ger_vsss.hpp"
#include "strategy_interface.h"

int main(int argc, char* argv[])
{	
	// if did not receive expected number of arguments, prints usage instructions
	// the user must send the cam number as a parameter
	if(argc != 4) {
		cout << "Usage: " << argv[0] << " <cam number>" << " <primary_color> "<< "<flip>"<<  endl;
		return -1;
	}

	StrategyInterface interface; // initializes interface
	// Por algum motivo se essa linha não estiver no início a camera buga

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

	bool play = false;

	while (1)
	{
		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			 cout << "Cannot read a frame from video stream" << endl;
			 break;
		}

		set_border_manually(frame, Point2f(26, 29), Point2f(594, 5), Point2f(630, 456), Point2f(36, 473));
		Mat transformed_frame = transform(frame);
	
		// Nosso gol sempre será o lado esquerdo da tela
		if(argv[3][0] == 'y')
		{
			Mat tmp;
			flip(transformed_frame, tmp, -1);
			transformed_frame = tmp;
		}

		State fieldState = State(); // creates a new state (all set to zero)

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

			if(primary_circles[i].radius < 6 || min_dist > 15)
				continue; // if the radius of the yellow circle is less than 8 or the secondary color is too far away (> 22), it is not a robot

			if(strcmp(argv[2], "blue"))
			{
				// transforms the field positions to the range (10, 160) for x and (0, 130) for y
				fieldState.blue_pos[type] = Point2f((150.0 * primary_circles[i].center.x / dWidth), (130.0 * primary_circles[i].center.y / dHeight));
				// calculates direction in range (0, 360) degrees
				// TODO check if the simulator and this are using the same zero
				fieldState.blue_dir[type] = (M_PI + atan2(secondary_circles[type][index].center.y - primary_circles[i].center.y, secondary_circles[type][index].center.x - primary_circles[i].center.x)) * (180 / M_PI) ;
			}
			else
			{
				fieldState.yellow_pos[type] = Point2f((150.0 * primary_circles[i].center.x / dWidth), (130.0 * primary_circles[i].center.y / dHeight));
				fieldState.yellow_dir[type] = (M_PI + atan2(secondary_circles[type][index].center.y - primary_circles[i].center.y, secondary_circles[type][index].center.x - primary_circles[i].center.x)) * (180 / M_PI); 
			}

	        circle(transformed_frame, primary_circles[i].center, 4, Scalar(255, 255, 255), -1);
	        line(transformed_frame, primary_circles[i].center, primary_circles[i].center + 2*(secondary_circles[type][index].center - primary_circles[i].center), Scalar(255, 255, 255), 2);
			printf("\nx_robo%d=%.1f, y_robo%d=%.1f\n", type, primary_circles[i].center.x, type, primary_circles[i].center.y);
			printf("robo%d_dir: %.1lf %.1lf\n", type, secondary_circles[type][index].center.x - primary_circles[i].center.x, secondary_circles[type][index].center.y - primary_circles[i].center.y);
			printf("robo%d_dir: %.1lf\n", type, (M_PI + atan2(secondary_circles[type][index].center.y - primary_circles[i].center.y, secondary_circles[type][index].center.x - primary_circles[i].center.x)) * (180/M_PI));
		}

		sort(opponent_circles.begin(), opponent_circles.end());
		for(int i = 0; i < 3 && i < opponent_circles.size(); i++)
		{
			if(strcmp(argv[2], "blue"))
			{
				fieldState.yellow_pos[i] = Point2f((150.0 * opponent_circles[i].center.x / dWidth), (130.0 * opponent_circles[i].center.y / dHeight));
				fieldState.yellow_dir[i] = 0;
			}
			else
			{
				fieldState.blue_pos[i] = Point2f((150.0 * opponent_circles[i].center.x / dWidth), (130.0 * opponent_circles[i].center.y / dHeight));
				fieldState.blue_dir[i] = 0;
			}

	        circle(transformed_frame, opponent_circles[i].center, 4, Scalar(255, 255, 255), -1);
			printf("\nx_opponent%d=%.1f, y_opponent%d=%.1f\n", i, opponent_circles[i].center.x, i, opponent_circles[i].center.y);
		}


		sort(ball_circles.begin(), ball_circles.end());
		if(ball_circles.size())
		{
	        circle(transformed_frame, ball_circles[0].center, 4, Scalar(255, 255, 255), -1);
			fieldState.ball_pos = Point2f((150.0 * ball_circles[0].center.x / dWidth), (130.0 * ball_circles[0].center.y / dHeight));
			printf("\nx_ball=%.1f, y_ball=%.1f\n", ball_circles[0].center.x, ball_circles[0].center.y);
		}

		if(play == false) // pretends the ball is not there so players will stop
			fieldState.ball_pos = Point2f(0, 0);

		// sends data to the strategy code
		interface.sendToStrategy(fieldState);

		imshow("MyVideo_transformed", transformed_frame); //show the frame in "MyVideo_transformed" window

		int keypress = waitKey(30);

		if(keypress == 's') // press s to start
		{
			play = true;
			cout << "Game is starting" << endl;
		}
		if(keypress == 'p') // press p to pause
		{
			play = false;
			cout << "Game is paused" << endl;
		}

		if (keypress == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}
	return 0;
}
