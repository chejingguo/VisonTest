#include "StdAfx.h"
#include "BTLFlyCapture.h"

BTLFlyCapture::BTLFlyCapture(void)
{
	uiSize = _MAX_CAMS;
	//
	flycaptureBusEnumerateCamerasEx( arInfo, &uiSize );
	//
	for( unsigned int uiBusIndex = 0; uiBusIndex < uiSize; uiBusIndex++ )
	{
	  FlyCaptureInfoEx* pinfo = &arInfo[ uiBusIndex ];
	  printf( 
		 "Index %u: %s (%u)\n",
		 uiBusIndex,
		 pinfo->pszModelName,
		 pinfo->SerialNumber );
	}
	//
	flycaptureCreateContext( &context );
	//
	flycaptureInitialize( context, _CAMERA_INDEX );
	//
	flycaptureSetCameraRegister( context, INITIALIZE, 0x80000000 );

   //
   // Power-up the camera (for cameras that support this feature)
   //
   flycaptureSetCameraRegister( context, CAMERA_POWER, 0x80000000 );

   //
   // Retrieve information about the camera.
   //
   flycaptureGetCameraInfo( context, &info );
   //
   flycaptureStart(context,FLYCAPTURE_VIDEOMODE_ANY,FLYCAPTURE_FRAMERATE_ANY );

   	memset( &raw_image, 0x0, sizeof( FlyCaptureImage ) );
}

BTLFlyCapture::~BTLFlyCapture(void)
{
	//
	// Destroy the context. This should always be called before exiting
	// the application to prevent memory leaks.
	//
	//flycaptureStop( context );
	//flycaptureDestroyContext( context );

}
//=============================================================================
// Functions
//=============================================================================
void BTLFlyCapture::reportCameraInfo( const FlyCaptureInfoEx* pinfo )
{
   //
   // Print out camera information. This can be obtained by calling
   // flycaptureGetCameraInfo() anytime after the camera has been initialized.
   //
}

void BTLFlyCapture::SaveImageRawFile()
{
	flycaptureSaveImage(context,&raw_image,FILENAME_RAW,FLYCAPTURE_FILEFORMAT_PGM );
}


Mat BTLFlyCapture::flyCap()
{
	flycaptureGrabImage2( context, &raw_image );

	IplImage* src = cvCreateImage(cvSize(raw_image.iCols,raw_image.iRows),8,1);
	for(int i = 0 ; i < src->height; i++)
	{
		for(int j = 0 ; j < src->width ; j++)
		{
			CV_IMAGE_ELEM(src,uchar,i,j) = (unsigned char)raw_image.pData[i*raw_image.iCols + j];        
		}
	}
	Mat image(src,true);
	cvReleaseImage(&src);
    return image;
}
Mat BTLFlyCapture::flyCapColor()
{
	flycaptureGrabImage2(context,&raw_image);

	
   FlyCaptureImage imageConverted;
   imageConverted.pData = new unsigned char[ raw_image.iCols * raw_image.iRows * 3 ];
   imageConverted.pixelFormat = FLYCAPTURE_BGR;

	flycaptureConvertImage( context, &raw_image, &imageConverted );

    IplImage* src = cvCreateImage(cvSize(raw_image.iCols,raw_image.iRows),IPL_DEPTH_8U,3);
	memcpy(src->imageData,imageConverted.pData,raw_image.iCols * raw_image.iRows * 3 );
	Mat image(src,true);
	delete [] imageConverted.pData;
	cvReleaseImage(&src);
    return image;
}
void BTLFlyCapture::exitCap()
{
	flycaptureStop( context );
    flycaptureDestroyContext( context );
}