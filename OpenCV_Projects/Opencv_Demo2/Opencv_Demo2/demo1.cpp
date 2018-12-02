#include "iostream"
//��ʾͼ���ļ�  
#include <opencv2/opencv.hpp>
using namespace std;
#include "highgui.h"
#include "cv.h"
#include "cxcore.h"
#include "stdlib.h"
#include "stdio.h"
#include "string"
//--------------------------------��ȡͼƬ��ʾ--------------------------------------//
int main01()
{
	//const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\һ����Ƭ\\������.jpg";
	const char *pstrimagename = "C:/Users/A/Pictures/Camera Roll/һ����Ƭ/������.jpg"; // ��/�������൱�ڡ�\\������

	const char *pstrwindowstitle = "opencv��һ������";
	//���ļ��ж�ȡͼ��  
	//IplImage *pimage = cvLoadImage(pstrimagename,0);  // �Ի�ɫģʽ��ʾͼ��
	IplImage *pimage = cvLoadImage(pstrimagename, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);//��ͼ����ԭʼ��ģʽ��ʾ����ɫ����ʵ

	//��������  
	cvNamedWindow(pstrwindowstitle);
	//��ָ����������ʾͼ��  
	cvShowImage(pstrwindowstitle, pimage);
	//�ȴ������¼�  
	cvWaitKey(0);

	cvDestroyWindow(pstrwindowstitle);
	cvReleaseImage(&pimage);
	return 0;
}

//---------------------------------����ͼƬ����AVI��Ƶ��ʾ-----------------------//

void main04()
{
	CvSize size = cvSize(720, 480);
	double fps = 15;//
	// CV_FOURCC('M', 'J', 'P', 'G')������Ƶ�ı����ʽ������������Ϊ-1����Ҫ�ڲ�����Ƶʱ�ֶ����ñ��뷽ʽ
	CvVideoWriter* write = cvCreateVideoWriter("D:\\ѧϰ��Դ\\Ӣ����˼ѧϰ\\��Ϸ�����ز� �λ����ɳ���.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, size);
	//int image_id = 10001; 
	int image_id = 0;
	char filename[256];//�洢ͼƬ����·��
	//sprintf_s(filename, "G:\\develop\\cocosPNG\\[PNG]��֡�ز�\\��2\\%d.png", image_id);// ����ͼƬ����·��
	sprintf_s(filename, "G:\\develop\\cocosPNG\\��Ϸ�����ز� �λ����ɳ���\\%d.jpg", image_id);// ����ͼƬ����·��
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
		cvWriteFrame(write, src_resize);//д��AVI��Ƶ
		cvReleaseImage(&src);
		image_id++;
		//sprintf_s(filename, "G:\\develop\\cocosPNG\\[PNG]��֡�ز�\\��2\\%d.png", image_id);
		sprintf_s(filename, "G:\\develop\\cocosPNG\\��Ϸ�����ز� �λ����ɳ���\\%d.jpg", image_id);// ����ͼƬ����·��
		src = cvLoadImage(filename);
	}
}