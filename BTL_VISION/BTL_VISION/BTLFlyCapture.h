#pragma once
//=============================================================================
// Macro Definitions
//=============================================================================
//
// The number of images to grab.
//
#define _IMAGES_TO_GRAB 10

//
// The maximum number of cameras on the bus.
//
#define _MAX_CAMS       32

//
// The index of the camera to grab from.
//
#define _CAMERA_INDEX   0

//
// What file format should we save the processed image as?
//
//#define SAVE_FORMAT     FLYCAPTURE_FILEFORMAT_PPM
#define SAVE_FORMAT     FLYCAPTURE_FILEFORMAT_BMP

//#define FILENAME_CONVERTED "converted.ppm"
#define FILENAME_CONVERTED "converted.bmp"
#define FILENAME_RAW       "raw.pgm"

//
// Register defines
// 
#define INITIALIZE         0x000
#define CAMERA_POWER       0x610

class BTLFlyCapture
{
private:
   // The Flycapture error. This should be assigned to the return value of 
   // most API functions and checked to ensure that the operation was completed
   // successfully.
   FlyCaptureError   error;

   // This acts as a handle to the camera.
   FlyCaptureContext context;   

   // Structure to store various information about the camera such as
   // model, serial number and DCAM compliance.
   FlyCaptureInfoEx info;

   //
   // Enumerate the cameras on the bus.
   //
   FlyCaptureInfoEx  arInfo[ _MAX_CAMS ];
   unsigned int	     uiSize;
   	FlyCaptureImage raw_image;


public:
	BTLFlyCapture(void);
	~BTLFlyCapture(void);
private:
	void reportCameraInfo( const FlyCaptureInfoEx* pinfo );
public:
	void SaveImageRawFile();
	Mat flyCap();
	void exitCap();
	Mat flyCapColor();

};
