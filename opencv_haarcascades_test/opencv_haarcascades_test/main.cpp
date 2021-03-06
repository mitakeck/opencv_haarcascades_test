// http://gihyo.jp/dev/feature/01/opencv/0003?page=3
#include <opencv\cv.h>
#include <opencv\highgui.h>

int main(void){

	// 対象画像
	char fileName[] = "sample.jpg";
	IplImage* input = cvLoadImage(fileName, 1);

	// 正面顔検出器の読み込み
	CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_frontalface_default.xml");

	CvMemStorage* strage = cvCreateMemStorage(0);
	CvSeq* faces;
	int i;

	// 顔検出
	faces = cvHaarDetectObjects(input, cascade, strage);

	// 顔領域の描画
	for(int i=0; i<faces->total; i++){
		CvRect face_rect = *(CvRect*)cvGetSeqElem(faces, i);
		cvRectangle(
			input,
			cvPoint(face_rect.x, face_rect.y),
			cvPoint((face_rect.x+face_rect.width),(face_rect.y+face_rect.height)),
			CV_RGB(255, 0, 0),
			3
		);
	}

	// 表示
	cvReleaseMemStorage(&strage);
	cvNamedWindow("face_detect", 0);
	cvShowImage("face_detect", input);

	cvWaitKey(0);

	cvReleaseHaarClassifierCascade(&cascade);
	cvReleaseImage(&input);

	return 0;
}