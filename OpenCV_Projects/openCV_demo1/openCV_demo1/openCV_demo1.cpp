// openCV_demo1.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
//��ʾͼ���ļ�  
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
#include "highgui.h"
#include "cv.h"
int main01(int argc, char** argv)
{
	const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\����\\8.jpg";
	const char *pstrwindowstitle = "opencv��һ������";
	//���ļ��ж�ȡͼ��  
	IplImage *bigImage = cvLoadImage(pstrimagename);
	IplImage *subImage = cvLoadImage("G:\\develop\\cocosPNG\\png�ز�1\\�Ự����103.png");
	// ������������
	CvRect rect;
	rect.x = 250;
	rect.y = 280;
	rect.height = subImage->height;
	rect.width = subImage->width;//���þ�������Ĵ�С���ͼ����ͬ

	//-----------------------------�ƻ���ľ��ʾ---------------------------------//
	// ����Opencv�⺯��ʵ���ƻ���ľ����
	//cvSetImageROI(pimage, rect); //����ͼ��ĸ���Ȥ����
	//cvCopy(myImage, pimage);// ����ͼ����Ϣ
	//cvResetImageROI(pimage);//ȥ��ͼ��ĸ���Ȥ����

	//-----------------����һ�ַǵ��ÿ⺯������ʵ�ֿ�ͼ(�ƻ���ľ)-------------------//
	for (int y = 0;y < subImage->height;y++ )
	{
		unsigned char* subImageData = (unsigned char*)(subImage->imageData + y*subImage->widthStep);
		unsigned char* bigImageData = (unsigned char*)(bigImage->imageData + (y + rect.y)*bigImage->widthStep);
		for (int x = 0;x < subImage->width;x++)
		{
			bigImageData[3*(x + rect.x) + 0] = subImageData[3 * x + 0];
			bigImageData[3*(x + rect.x) + 1] = subImageData[3 * x + 1];
			bigImageData[3*(x + rect.x) + 2] = subImageData[3 * x + 2];
		}
	}
	//��������  
	cvNamedWindow(pstrwindowstitle);
	cvNamedWindow("mySub");
	//��ָ����������ʾͼ��  
	cvShowImage(pstrwindowstitle, bigImage);
	cvShowImage("mySub", subImage);
	//�ȴ������¼�  
	cvWaitKey(0);
	//�ڴ�����
	cvDestroyWindow(pstrwindowstitle);
	cvDestroyWindow("mySub");
	cvReleaseImage(&bigImage);
	cvReleaseImage(&subImage);
    return 0;
}

//--------------------------------------��ʦ������ʵ��------------------------------------//
int main(int argc, char** argv)
{
	const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\����\\12.jpg";
	const char *pstrwindowstitle1 = "Ŀ��ͼ����1";
	const char *pstrwindowstitle2 = "Ŀ��ͼ����2";
	const char *sdtwindowstitle = "ԭͼ";
	//���ļ��ж�ȡͼ��  
	IplImage *bigImage = cvLoadImage(pstrimagename);

	//��������  
	cvNamedWindow(sdtwindowstitle);
	cvNamedWindow(pstrwindowstitle1);
	cvNamedWindow(pstrwindowstitle2);

	CvSize img_size;
	img_size.width = bigImage->width;
	img_size.height = bigImage->height;

	IplImage *dst1 = cvCreateImage(img_size, 8, 3);
	IplImage *dst2 = cvCreateImage(img_size, 8, 3);
	IplImage* b = cvCreateImage(img_size, 8, 1);
	IplImage* r = cvCreateImage(img_size, 8, 1);
	IplImage* g = cvCreateImage(img_size, 8, 1);

	IplImage* br = cvCreateImage(img_size, 8, 1);
	IplImage* rr = cvCreateImage(img_size, 8, 1);
	IplImage* gr = cvCreateImage(img_size, 8, 1);
	// ��������Ὣ�����е�����ͨ����Ԫ�ص�ֵ������Ϊ0
	cvZero(dst1);
	cvZero(dst2);
	cvZero(br);
	cvZero(gr);
	cvZero(rr);

	// ����1��
	cvSplit(bigImage, b, g, r, 0);	// ����ͨ��ͼ������������ͨ��ͼ��
	// ͼ���Ȩ���
	cvAddWeighted(b, 0.131, g, 0.534, 0, br);
	cvAddWeighted(br, 1, r, 0.272, 0, br);

	cvAddWeighted(b, 0.168, g, 0.686, 0, gr);
	cvAddWeighted(gr, 1, r, 0.349, 0, gr);

	cvAddWeighted(b, 0.189, g, 0.769, 0, rr);
	cvAddWeighted(rr, 1, r, 0.393, 0, rr);
	
	cvMerge(br, gr, rr, 0, dst1); // �ϲ�3����ͨ��ͼ��Ϊһ����ͨ��ͼ��

	//// ����2��
	for (int y = 0;y < bigImage->height;y++)
	{
		for (int x = 0;x < bigImage->width;x++)
		{
			CvScalar p = cvGet2D(bigImage, y, x); /*��� CvScalar����һ�������������4��double��ֵ������
												  һ�������������ֵ����һ���ǻҶ�ֵŶ���ģ�
												  �����Դ��4��ͨ���ġ�*/
			double m_b = (0.272*p.val[0] + 0.534*p.val[1] + 0.131*p.val[2]);
			double m_g = (0.349*p.val[0] + 0.686*p.val[1] + 0.168*p.val[2]);
			double m_r = (0.393 *p.val[0] + 0.769*p.val[1] + 0.189*p.val[2]);

			CvScalar np = cvScalar(m_b, m_g, m_r);
			cvSet2D(dst2, y, x, np); /*���������������������꣬��������ƽ��ϰ�ߵ�
									���겻һ�����ǣ�y�����ǵ��У����߶ȣ�
									��Ӧ������ƽ������ϵ��y, x��������У�����ȣ�
									��Ӧ������ƽ������ϵ��x��cvSet2D() Ҳ���ơ�
									*/
		}
	}

	//��ָ����������ʾͼ��  
	cvShowImage(sdtwindowstitle, bigImage);
	cvShowImage(pstrwindowstitle1, dst1);
	cvShowImage(pstrwindowstitle2, dst2);
	//�ȴ������¼�  
	cvWaitKey(0);
	//�ڴ�����
	cvDestroyWindow(sdtwindowstitle);
	cvDestroyWindow(pstrwindowstitle1);
	cvDestroyWindow(pstrwindowstitle2);
	cvReleaseImage(&bigImage);
	cvReleaseImage(&dst1);
	cvReleaseImage(&dst2);
	return 0;
}



//--------------------------------------ʵ��1------------------------------------//
int main03(int argc, char** argv)
{
	const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\����\\12.jpg";
	const char *pstrwindowstitle = "Ŀ��ͼ";
	const char *sdtwindowstitle = "ԭͼ";
	//���ļ��ж�ȡͼ��  
	IplImage *bigImage = cvLoadImage(pstrimagename);
	CvSize img_size;
	img_size.width = bigImage->width;
	img_size.height = bigImage->height;
	IplImage* b = cvCreateImage(img_size, 8, 1);
	IplImage* g = cvCreateImage(img_size, 8, 1);
	IplImage* r = cvCreateImage(img_size, 8, 1);
	IplImage* sdt = cvCreateImage(img_size, 8, 3);
	cvZero(sdt);
	cvSplit(sdt, b, g, r, 0);
	for (int y = 0;y < bigImage->height;y++)
	{
		unsigned char* bigImageData = (unsigned char*)(bigImage->imageData +
			y * bigImage->widthStep);
		unsigned char* b_Data = (unsigned char*)(b->imageData +
			y * b->widthStep);
		unsigned char* g_Data = (unsigned char*)(g->imageData +
			y * g->widthStep);
		unsigned char* r_Data = (unsigned char*)(r->imageData +
			y * r->widthStep);

		for (int x = 0;x < bigImage->width;x++)
		{
			double B_old = bigImageData[3 * x + 0];
			double G_old = bigImageData[3 * x + 1];
			double R_old = bigImageData[3 * x + 2];
			b_Data[x] = 0.272*R_old + 0.534*G_old + 0.131*B_old;
			g_Data[x] = 0.349*R_old + 0.686*G_old + 0.168*B_old;
			r_Data[x] = 0.393*R_old + 0.769*G_old + 0.189*B_old;
			/*double B_old = bigImageData[3 * x + 0];
			double G_old = bigImageData[3 * x + 1];
			double R_old = bigImageData[3 * x + 2];
			b_Data[x] = 0.272*bigImageData[3 * x + 2] + 
			0.534*bigImageData[3 * x + 1] + 0.131*bigImageData[3 * x + 0];
			g_Data[x] = 0.349*bigImageData[3 * x + 2] + 
			0.686*bigImageData[3 * x + 1] + 0.168*bigImageData[3 * x + 0];
			r_Data[x] = 0.393*bigImageData[3 * x + 2] +
			0.769*bigImageData[3 * x + 1] + 0.189*bigImageData[3 * x + 2];*/
		}
	}
	cvMerge(b, g, r, 0, sdt);
	//��������  
	cvNamedWindow(sdtwindowstitle);
	cvNamedWindow(pstrwindowstitle);
	//��ָ����������ʾͼ��  
	cvShowImage(sdtwindowstitle, bigImage);
	cvShowImage(pstrwindowstitle, sdt);
	//�ȴ������¼�  
	cvWaitKey(0);
	//�ڴ�����
	cvDestroyWindow(sdtwindowstitle);
	cvDestroyWindow(pstrwindowstitle);
	cvReleaseImage(&bigImage);
	cvReleaseImage(&sdt);
	return 0;
}

// ��ȡͼ��������ֵ����
void readPixel(Mat &img)
{
	for (int j = 150; j < 200; j++)
	{
		uchar* data = img.ptr<uchar>(j);

		for (int i = 200; i <300; i++)
		{
			//-------------��ʼ����ÿ������-------------------
			cout << static_cast<int>(data[3 * i + 0]) << ";";
			cout << static_cast<int>(data[3 * i + 1]) << ";";
			cout << static_cast<int>(data[3 * i + 2]) << "    ";
			//-------------�������ش���------------------------
		} //���д������ 
		cout << endl;
	}
}


//����ͼ�񷽷�
void dealPixel(Mat &img) 
{
	vector<Mat> channels;
	split(img, channels);//����ɫ��ͨ��
	for (int j = 0; j < img.rows; j++)
	{
		//uchar* data = img.ptr<uchar>(j);
		uchar* b = channels.at(0).ptr<uchar>(j);
		uchar* g = channels.at(1).ptr<uchar>(j);
		uchar* r = channels.at(2).ptr<uchar>(j);
		for (int i = 0; i < img.cols; i++)
		{
			//-------------��ʼ����ÿ������-------------------
			uchar B_old = b[i];
			uchar G_old = g[i];
			uchar R_old = r[i];

			b[i] = floor(0.272*R_old + 0.534*G_old + 0.131*B_old);
			g[i] = floor(0.349*R_old + 0.686*G_old + 0.168*B_old);
			r[i] = floor(0.393*R_old + 0.769*G_old + 0.189*B_old);

			//uchar B_old = data[3 * (i)+0];
			//uchar G_old = data[3 * (i)+1];
			//uchar R_old = data[3 * (i)+2];

			/*data[3 * i + 0] = int(0.272*R_old + 0.534*G_old + 0.131*B_old);
			data[3 * i + 1] = int(0.349*R_old + 0.686*G_old + 0.168*B_old);
			data[3 * i + 2] = int(0.393*R_old + 0.769*G_old + 0.189*B_old);*/

			/*data[3 * i + 0] = ceil(0.131*R_old + 0.534*G_old + 0.272*B_old);
			data[3 * i + 1] = ceil(0.168*R_old + 0.686*G_old + 0.349*B_old);
			data[3 * i + 2] = ceil(0.189*R_old + 0.769*G_old + 0.393*B_old);*/
			//-------------�������ش���------------------------
		} //���д������                  
	}
	// �����������ĵ�ͨ�����ºϲ���һ����ͨ��  
	merge(channels, img);
}

//--------------------------------------Mat������ȡͼ��------------------------------------//
int main07(int argc, char** argv)
{
	const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\����\\12.jpg";
	const char *pstrwindowstitle = "Ŀ��ͼ";
	const char *sdtwindowstitle = "ԭͼ";
	//���ļ��ж�ȡͼ��  
	Mat src = imread(pstrimagename);
	Mat bigImage = imread(pstrimagename);
	
	//int nc = bigImage.cols * bigImage.channels(); //ÿ��Ԫ�ص���Ԫ������
	dealPixel(bigImage);

	Mat ImageRiO;
	ImageRiO = src(Rect(150, 150, 150, 200));
	dealPixel(ImageRiO);
	//readPixel(bigImage);
	//��������  
	cvNamedWindow(sdtwindowstitle);
	cvNamedWindow(pstrwindowstitle);
	cvNamedWindow("��ȡƬ��");
	//��ָ����������ʾͼ��  
	imshow(sdtwindowstitle, src);
	imshow(pstrwindowstitle, bigImage);
	imshow("��ȡƬ��", ImageRiO);
	//�ȴ������¼�  
	cvWaitKey(0);
	return 0;
}


//--------------------------------------ʵ��3------------------------------------//
