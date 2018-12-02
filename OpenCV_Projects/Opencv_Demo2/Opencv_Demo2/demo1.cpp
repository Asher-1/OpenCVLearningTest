#include "iostream"
//显示图像文件  
#include <opencv2/opencv.hpp>
using namespace std;
#include "highgui.h"
#include "cv.h"
#include "cxcore.h"
#include "stdlib.h"
#include "stdio.h"
#include "string"
//--------------------------------读取图片演示--------------------------------------//
int main01()
{
	//const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\一寸照片\\宣传部.jpg";
	const char *pstrimagename = "C:/Users/A/Pictures/Camera Roll/一寸照片/宣传部.jpg"; // “/”符号相当于“\\”符号

	const char *pstrwindowstitle = "opencv第一个程序";
	//从文件中读取图像  
	//IplImage *pimage = cvLoadImage(pstrimagename,0);  // 以灰色模式显示图像
	IplImage *pimage = cvLoadImage(pstrimagename, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);//以图像最原始的模式显示，颜色最真实

	//创建窗口  
	cvNamedWindow(pstrwindowstitle);
	//在指定窗口中显示图像  
	cvShowImage(pstrwindowstitle, pimage);
	//等待按键事件  
	cvWaitKey(0);

	cvDestroyWindow(pstrwindowstitle);
	cvReleaseImage(&pimage);
	return 0;
}

//---------------------------------利用图片制作AVI视频演示-----------------------//

void main04()
{
	CvSize size = cvSize(720, 480);
	double fps = 15;//
	// CV_FOURCC('M', 'J', 'P', 'G')设置视频的编码格式，若将此设置为-1则需要在播放视频时手动设置编码方式
	CvVideoWriter* write = cvCreateVideoWriter("D:\\学习资源\\英语雅思学习\\游戏场景素材 梦幻诛仙场景.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, size);
	//int image_id = 10001; 
	int image_id = 0;
	char filename[256];//存储图片绝对路径
	//sprintf_s(filename, "G:\\develop\\cocosPNG\\[PNG]连帧素材\\云2\\%d.png", image_id);// 构造图片绝对路径
	sprintf_s(filename, "G:\\develop\\cocosPNG\\游戏场景素材 梦幻诛仙场景\\%d.jpg", image_id);// 构造图片绝对路径
	IplImage* src = cvLoadImage(filename);
	if (!src)
	{
		return;
	}
	IplImage* src_resize = cvCreateImage(size, 8, 3);
	cvNamedWindow("avi");
	while (src)
	{
		cvShowImage("avi", src_resize);
		cvWaitKey(1);
		cvResize(src, src_resize);
		cvWriteFrame(write, src_resize);//写入AVI视频
		cvReleaseImage(&src);
		image_id++;
		//sprintf_s(filename, "G:\\develop\\cocosPNG\\[PNG]连帧素材\\云2\\%d.png", image_id);
		sprintf_s(filename, "G:\\develop\\cocosPNG\\游戏场景素材 梦幻诛仙场景\\%d.jpg", image_id);// 构造图片绝对路径
		src = cvLoadImage(filename);
	}
}