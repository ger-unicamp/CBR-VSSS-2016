CFLAGS  = -g -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_stitching -lopencv_imgcodecs -lopencv_videoio

all:
	g++ -o transform transform.cpp $(CFLAGS) 
	g++ -o show_image show_image.cpp $(CFLAGS) 
	g++ -o video_cap video_cap.cpp $(CFLAGS) 
	g++ -o find_color find_color.cpp $(CFLAGS) 
	g++ -o transform_video transform_video.cpp $(CFLAGS) 

transform:
	g++ -o transform transform.cpp $(CFLAGS) 

show_image:
	g++ -o show_image show_image.cpp $(CFLAGS) 

video_cap: 
	g++ -o video_cap video_cap.cpp $(CFLAGS) 

clean:
	rm -f transform show_image video_cap
