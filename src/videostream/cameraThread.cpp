#include "cameraThread.h"


CameraThread::CameraThread(void){

}

CameraThread::~CameraThread(void){
    std::cout << "Destructing the uploading object and free the memory" << std::endl;
}

void CameraThread::startSystem(){
    keepRunning = true;
    start();
}

void CameraThread::stopSystem(){
    keepRunning = false;
    stop();
}

/**
 *  Run the video stream collecting and sending pthread
 */
void CameraThread::run(){
#ifdef CAMERADEBUG
    std::cout << "Starting the camera thread" << std::endl;
#endif

    string servAddress(defaultTargetIP);
    unsigned short servPort = Socket::resolveService(defaultCameraPort,"udp");
    try{
        UDPSocket sock;
        int jpegqual =  ENCODE_QUALITY; // Compression Parameter

        Mat frame, send;
        vector < uchar > encoded;
        VideoCapture cap(0); // Grab the camera
        if(!cap.isOpened()){
            cerr << "OpenCV failed to open camera";
            exit(1);
        }
        clock_t last_cycle = clock();
        while (keepRunning) {
#ifdef CAMERADEBUG
            //std::cout << "Running the camera thread" << std::endl;
#endif     
            cap >> frame;
            if(frame.size().width==0)continue;//simple integrity check; skip erroneous data...
            resize(frame, send, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_LINEAR);
            vector < int > compression_params;
            compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
            compression_params.push_back(jpegqual);

            imencode(".jpg", send, encoded, compression_params);
            //imshow("send", send);
            int total_pack = 1 + (encoded.size() - 1) / PACK_SIZE;

            int ibuf[1];
            ibuf[0] = total_pack;
            sock.sendTo(ibuf, sizeof(int), servAddress, servPort);

            for (int i = 0; i < total_pack; i++)
                sock.sendTo( & encoded[i * PACK_SIZE], PACK_SIZE, servAddress, servPort);

            waitKey(FRAME_INTERVAL);

            clock_t next_cycle = clock();
            double duration = (next_cycle - last_cycle) / (double) CLOCKS_PER_SEC;

#ifdef CAMERADEBUG
            cout << "\teffective FPS:" << (1 / duration) << " \tkbps:" << (PACK_SIZE * total_pack / duration / 1024 * 8) << endl;
            cout << next_cycle - last_cycle;

#endif
            last_cycle = next_cycle;
        
        }    
    }catch(SocketException & e){
        cerr << e.what() << endl;
        exit(1);
    }

#ifdef CAMERADEBUG
    std::cout << "Exiting camera thread" << std::endl;
#endif

}
