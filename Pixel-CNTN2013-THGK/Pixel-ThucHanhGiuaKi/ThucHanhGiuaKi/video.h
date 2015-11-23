#ifndef _VIDEO_
#define _VIDEO

#include "header.h"

void    getProperties(VideoCapture *video, double *height, double *width, int *nframe, int *fps)
{
    *width = video->get(CV_CAP_PROP_FRAME_WIDTH);
    *height = video->get(CV_CAP_PROP_FRAME_HEIGHT);
    *nframe = video->get(CV_CAP_PROP_FRAME_COUNT);
    *fps = video->get(CV_CAP_PROP_FPS);
}

int    readAndShowVideo(VideoCapture *video)
{
    if (!video->isOpened())
    {
        cout << "Error in opening video\n";
        return 0;
    }

    cout << "Getting properties of video...\n";
    double height, width;
    int nframe, fps;
    getProperties(video, &height, &width, &nframe, &fps);

    cout << "Read and Show video...";

    Mat frame;
    for (int i = 0; i < nframe; ++i)
    {
        //read frame ith of video
        *video >> frame;
        //show frame ith of video
        imshow("video", frame);
        //wait 1ms
        waitKey(1);
    }

    return 1;
}
#endif // _VIDEO_
