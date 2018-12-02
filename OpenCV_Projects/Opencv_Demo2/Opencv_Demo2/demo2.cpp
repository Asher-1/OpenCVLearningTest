#include "iostream"
//#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include "highgui.h"
#include "cv.h"
void main03()
{
	const char* name = "视频播放软件";
	const char* filmPath = "E:\\BaiduYunDownload\\最适合自学的C++基础视频_深入浅出版video\\02_C++基础\\c++基础day05\\视频\\13_作业和考试.wmv";
	cvNamedWindow(name, 0);
	//CvCapture* capture = cvCreateFileCapture(filmPath); // 读取视频
	CvCapture* capture = cvCreateCameraCapture(-1);// 读取摄像头(目前不可用，还未找出原因)
	IplImage* frame;
	while (1)
	{
		frame = cvQueryFrame(capture);
		if (!frame)
		{
			break;
		}
		cvShowImage(name,frame);
		char c = cvWaitKey(100); // 设置视频播放帧率为100毫秒一帧的速度
		if(c == 27) break; //判断用户是否点击键盘的esc键退出（esc键对应的AscII码为27）
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow(name);
}

//--------------------------------------播放器加入进度条演示------------------------------------//

/*
	视频播放时加入进度条
*/
//全局变量
int g_slider_position = 0;
CvCapture* g_capture = NULL;
int frame_count = 0; // 进度条位置
//全局函数（用于加入滚动条）即回调函数
void onTrackbarSlide(int pos)
{
	cvSetCaptureProperty(
		g_capture,
		CV_CAP_PROP_POS_FRAMES,
		pos
	);
	frame_count = pos;
}
void main06()
{
	const char* name = "视频播放软件";
	const char* filmPath = "E:\\BaiduYunDownload\\最适合自学的C++基础视频_深入浅出版video\\02_C++基础\\c++基础day06\\视频\\12_中午课程回顾.wmv";
	cvNamedWindow(name, 0);
	g_capture = cvCreateFileCapture(filmPath);
	int frames = (int)cvGetCaptureProperty(
		g_capture,
		CV_CAP_PROP_FRAME_COUNT
		);
	if (frames != 0)
	{
		cvCreateTrackbar(
			"Position",
			name,
			&g_slider_position,
			frames,
			onTrackbarSlide
		);
	}
	IplImage* frame;
	while (1)
	{
		frame = cvQueryFrame(g_capture);
		if (!frame)
		{
			break;
		}
		cvShowImage(name, frame);
		char c = cvWaitKey(55);
		if (c == 27) break; //判断用户是否点击键盘的esc键退出（esc键对应的AscII码为27）
		cvSetTrackbarPos("Position", name, frame_count); // 实现滚动条随着视频播放移动功能
		frame_count++;// 移动进度条

	}
	cvReleaseCapture(&g_capture);
	cvDestroyWindow(name);
}
