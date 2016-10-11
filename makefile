CFLAGS  = -g -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_stitching -lopencv_imgcodecs -lopencv_videoio

all:
	g++ -o transform.exe transform.cpp $(CFLAGS) 
	g++ -o show_image.exe show_image.cpp $(CFLAGS) 
	g++ -o video_cap.exe video_cap.cpp $(CFLAGS) 
	g++ -o find_color.exe find_color.cpp $(CFLAGS) 
	g++ -o transform_video.exe transform_video.cpp $(CFLAGS) 
	g++ -o encontra_objetos.exe ger_vsss.cpp encontra_objetos.cpp $(CFLAGS)
clean:
	rm -f *.exe
