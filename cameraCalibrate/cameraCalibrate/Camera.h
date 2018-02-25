/***********************************************************************

							qwertyCamera:
		encapsulation of virtual camera and physical camera

*************************************************************************/
#pragma once
#include <opencv2\opencv.hpp>

namespace qwerty
{
	//encapsulation of screen physical description/mesh descriptor
	class Camera
	{
	public:

		Camera();

		//step 1 : input a photographed chessboard image for camera calibration
		bool RecognizeChessboard(const cv::String& imagePath,bool showImage);

		bool RecognizeChessboard(const cv::Mat& image,bool showImage);

		//step2 : Calibrate Camera

		//corner count must be sufficient (K images,N corners, 2NK >= 6K + 4)
		bool IsOkToCalibrate();

		bool Calibrate();

	private:
		
		static const cv::Size cDefaultChessboardSize;//7x5
		static const cv::Size cDefaultChessboardGridWorldSpaceSize;//20mm x 20mm

		std::vector<std::vector<cv::Point3f>> mObjectPointsW;//(K images x (7x5 point3f) on  3d world space
		std::vector<std::vector<cv::Point2f>> mImagePoints;//(K images x (7x5 point2f) on 2d image
		cv::Size mImagePixelSize;//pixel size of chessboard image
		cv::Mat mDistortionCoeff;//k1,k2,p1,p2,k3
		cv::Mat mIntrinsicParam;//similar to projection * viewport matrix
		cv::Mat mRotationVector;
		cv::Mat mTranslationVector;
		cv::Mat mExtrinsicMatrix;//similar to view matrix (R & T),generate from rot & trans vector
	};
}