#include "iostream"
//#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include "highgui.h"
#include "cv.h"
void main03()
{
	const char* name = "��Ƶ�������";
	const char* filmPath = "E:\\BaiduYunDownload\\���ʺ���ѧ��C++������Ƶ_����ǳ����video\\02_C++����\\c++����day05\\��Ƶ\\13_��ҵ�Ϳ���.wmv";
	cvNamedWindow(name, 0);
	//CvCapture* capture = cvCreateFileCapture(filmPath); // ��ȡ��Ƶ
	CvCapture* capture = cvCreateCameraCapture(-1);// ��ȡ����ͷ(Ŀǰ�����ã���δ�ҳ�ԭ��)
	IplImage* frame;
	while (1)
	{
		frame = cvQueryFrame(capture);
		if (!frame)
		{
			break;
		}
		cvShowImage(name,frame);
		char c = cvWaitKey(100); // ������Ƶ����֡��Ϊ100����һ֡���ٶ�
		if(c == 27) break; //�ж��û��Ƿ������̵�esc���˳���esc����Ӧ��AscII��Ϊ27��
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow(name);
}

//--------------------------------------�����������������ʾ------------------------------------//

/*
	��Ƶ����ʱ���������
*/
//ȫ�ֱ���
int g_slider_position = 0;
CvCapture* g_capture = NULL;
int frame_count = 0; // ������λ��
//ȫ�ֺ��������ڼ�������������ص�����
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
	const char* name = "��Ƶ�������";
	const char* filmPath = "E:\\BaiduYunDownload\\���ʺ���ѧ��C++������Ƶ_����ǳ����video\\02_C++����\\c++����day06\\��Ƶ\\12_����γ̻ع�.wmv";
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
		if (c == 27) break; //�ж��û��Ƿ������̵�esc���˳���esc����Ӧ��AscII��Ϊ27��
		cvSetTrackbarPos("Position", name, frame_count); // ʵ�ֹ�����������Ƶ�����ƶ�����
		frame_count++;// �ƶ�������

	}
	cvReleaseCapture(&g_capture);
	cvDestroyWindow(name);
}
