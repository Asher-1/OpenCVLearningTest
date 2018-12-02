// openCV_demo1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
//显示图像文件  
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
#include "highgui.h"
#include "cv.h"
int main01(int argc, char** argv)
{
	const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\型男\\8.jpg";
	const char *pstrwindowstitle = "opencv第一个程序";
	//从文件中读取图像  
	IplImage *bigImage = cvLoadImage(pstrimagename);
	IplImage *subImage = cvLoadImage("G:\\develop\\cocosPNG\\png素材1\\会话气泡103.png");
	// 创建矩形区域
	CvRect rect;
	rect.x = 250;
	rect.y = 280;
	rect.height = subImage->height;
	rect.width = subImage->width;//设置矩形区域的大小与该图像相同

	//-----------------------------移花接木演示---------------------------------//
	// 调用Opencv库函数实现移花接木功能
	//cvSetImageROI(pimage, rect); //设置图像的感兴趣区域
	//cvCopy(myImage, pimage);// 复制图像信息
	//cvResetImageROI(pimage);//去除图像的感兴趣区域

	//-----------------另外一种非调用库函数方法实现抠图(移花接木)-------------------//
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
	//创建窗口  
	cvNamedWindow(pstrwindowstitle);
	cvNamedWindow("mySub");
	//在指定窗口中显示图像  
	cvShowImage(pstrwindowstitle, bigImage);
	cvShowImage("mySub", subImage);
	//等待按键事件  
	cvWaitKey(0);
	//内存清理
	cvDestroyWindow(pstrwindowstitle);
	cvDestroyWindow("mySub");
	cvReleaseImage(&bigImage);
	cvReleaseImage(&subImage);
    return 0;
}

//--------------------------------------老师勘误后的实例------------------------------------//
int main(int argc, char** argv)
{
	const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\型男\\12.jpg";
	const char *pstrwindowstitle1 = "目标图方法1";
	const char *pstrwindowstitle2 = "目标图方法2";
	const char *sdtwindowstitle = "原图";
	//从文件中读取图像  
	IplImage *bigImage = cvLoadImage(pstrimagename);

	//创建窗口  
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
	// 这个函数会将数组中的所有通道的元素的值都设置为0
	cvZero(dst1);
	cvZero(dst2);
	cvZero(br);
	cvZero(gr);
	cvZero(rr);

	// 方法1：
	cvSplit(bigImage, b, g, r, 0);	// 将三通道图像分离成三个单通道图像
	// 图像加权混合
	cvAddWeighted(b, 0.131, g, 0.534, 0, br);
	cvAddWeighted(br, 1, r, 0.272, 0, br);

	cvAddWeighted(b, 0.168, g, 0.686, 0, gr);
	cvAddWeighted(gr, 1, r, 0.349, 0, gr);

	cvAddWeighted(b, 0.189, g, 0.769, 0, rr);
	cvAddWeighted(rr, 1, r, 0.393, 0, rr);
	
	cvMerge(br, gr, rr, 0, dst1); // 合并3个单通道图像为一个三通道图像

	//// 方法2：
	for (int y = 0;y < bigImage->height;y++)
	{
		for (int x = 0;x < bigImage->width;x++)
		{
			CvScalar p = cvGet2D(bigImage, y, x); /*这个 CvScalar就是一个可以用来存放4个double数值的数组
												  一般用来存放像素值（不一定是灰度值哦）的，
												  最多可以存放4个通道的。*/
			double m_b = (0.272*p.val[0] + 0.534*p.val[1] + 0.131*p.val[2]);
			double m_g = (0.349*p.val[0] + 0.686*p.val[1] + 0.168*p.val[2]);
			double m_r = (0.393 *p.val[0] + 0.769*p.val[1] + 0.189*p.val[2]);

			CvScalar np = cvScalar(m_b, m_g, m_r);
			cvSet2D(dst2, y, x, np); /*其参数中有两个方向的坐标，但跟我们平常习惯的
									坐标不一样的是，y代表是的行，即高度，
									对应于我们平常坐标系的y, x代表的是列，即宽度，
									对应于我们平常坐标系的x，cvSet2D() 也类似。
									*/
		}
	}

	//在指定窗口中显示图像  
	cvShowImage(sdtwindowstitle, bigImage);
	cvShowImage(pstrwindowstitle1, dst1);
	cvShowImage(pstrwindowstitle2, dst2);
	//等待按键事件  
	cvWaitKey(0);
	//内存清理
	cvDestroyWindow(sdtwindowstitle);
	cvDestroyWindow(pstrwindowstitle1);
	cvDestroyWindow(pstrwindowstitle2);
	cvReleaseImage(&bigImage);
	cvReleaseImage(&dst1);
	cvReleaseImage(&dst2);
	return 0;
}



//--------------------------------------实例1------------------------------------//
int main03(int argc, char** argv)
{
	const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\型男\\12.jpg";
	const char *pstrwindowstitle = "目标图";
	const char *sdtwindowstitle = "原图";
	//从文件中读取图像  
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
	//创建窗口  
	cvNamedWindow(sdtwindowstitle);
	cvNamedWindow(pstrwindowstitle);
	//在指定窗口中显示图像  
	cvShowImage(sdtwindowstitle, bigImage);
	cvShowImage(pstrwindowstitle, sdt);
	//等待按键事件  
	cvWaitKey(0);
	//内存清理
	cvDestroyWindow(sdtwindowstitle);
	cvDestroyWindow(pstrwindowstitle);
	cvReleaseImage(&bigImage);
	cvReleaseImage(&sdt);
	return 0;
}

// 读取图像像素数值方法
void readPixel(Mat &img)
{
	for (int j = 150; j < 200; j++)
	{
		uchar* data = img.ptr<uchar>(j);

		for (int i = 200; i <300; i++)
		{
			//-------------开始处理每个像素-------------------
			cout << static_cast<int>(data[3 * i + 0]) << ";";
			cout << static_cast<int>(data[3 * i + 1]) << ";";
			cout << static_cast<int>(data[3 * i + 2]) << "    ";
			//-------------结束像素处理------------------------
		} //单行处理结束 
		cout << endl;
	}
}


//处理图像方法
void dealPixel(Mat &img) 
{
	vector<Mat> channels;
	split(img, channels);//分离色彩通道
	for (int j = 0; j < img.rows; j++)
	{
		//uchar* data = img.ptr<uchar>(j);
		uchar* b = channels.at(0).ptr<uchar>(j);
		uchar* g = channels.at(1).ptr<uchar>(j);
		uchar* r = channels.at(2).ptr<uchar>(j);
		for (int i = 0; i < img.cols; i++)
		{
			//-------------开始处理每个像素-------------------
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
			//-------------结束像素处理------------------------
		} //单行处理结束                  
	}
	// 将三个独立的单通道重新合并成一个三通道  
	merge(channels, img);
}

//--------------------------------------Mat方法读取图像------------------------------------//
int main07(int argc, char** argv)
{
	const char *pstrimagename = "C:\\Users\\A\\Pictures\\Camera Roll\\型男\\12.jpg";
	const char *pstrwindowstitle = "目标图";
	const char *sdtwindowstitle = "原图";
	//从文件中读取图像  
	Mat src = imread(pstrimagename);
	Mat bigImage = imread(pstrimagename);
	
	//int nc = bigImage.cols * bigImage.channels(); //每行元素的总元素数量
	dealPixel(bigImage);

	Mat ImageRiO;
	ImageRiO = src(Rect(150, 150, 150, 200));
	dealPixel(ImageRiO);
	//readPixel(bigImage);
	//创建窗口  
	cvNamedWindow(sdtwindowstitle);
	cvNamedWindow(pstrwindowstitle);
	cvNamedWindow("提取片段");
	//在指定窗口中显示图像  
	imshow(sdtwindowstitle, src);
	imshow(pstrwindowstitle, bigImage);
	imshow("提取片段", ImageRiO);
	//等待按键事件  
	cvWaitKey(0);
	return 0;
}


//--------------------------------------实例3------------------------------------//
