/* License: Apache 2.0. See LICENSE file in root directory.
   Copyright(c) 2015 Intel Corporation. All Rights Reserved. */

#ifndef LIBREALSENSE_RS_H
#define LIBREALSENSE_RS_H

#ifdef __cplusplus
extern "C" {
#endif

#define RS_API_MAJOR_VERSION    2
#define RS_API_MINOR_VERSION    2
#define RS_API_PATCH_VERSION    0

#define STRINGIFY(arg) #arg
#define VAR_ARG_STRING(arg) STRINGIFY(arg)

/* Version in encoded integer format (1,9,x) -> 1090x note that each component is limited into [0-99] range by design*/
#define RS_API_VERSION  (((RS_API_MAJOR_VERSION) * 10000) + ((RS_API_MINOR_VERSION) * 100) + (RS_API_PATCH_VERSION))
/* Return version in "X.Y.Z" format */
#define RS_API_VERSION_STR (VAR_ARG_STRING(RS_API_MAJOR_VERSION.RS_API_MINOR_VERSION.RS_API_PATCH_VERSION))

typedef enum rs_frame_metadata
{
    RS_FRAME_METADATA_ACTUAL_EXPOSURE,
    RS_FRAME_METADATA_COUNT
} rs_frame_metadata;

/* rs_capabilities defines the full set of functionality that a RealSense device might provide
   to check what functionality is supported by a particular device at runtime call dev->supports(capability) */
typedef enum rs_capabilities
{
    RS_CAPABILITIES_DEPTH                   , /**< provides depth stream */
    RS_CAPABILITIES_COLOR                   , /**< provides color stream */
    RS_CAPABILITIES_INFRARED                , /**< provides infrared stream */
    RS_CAPABILITIES_INFRARED2               , /**< provides second infrared stream */
    RS_CAPABILITIES_FISH_EYE                , /**< provides wide field of view (fish-eye) stream */
    RS_CAPABILITIES_MOTION_EVENTS           , /**< provides gyro and accelorometer events */
    RS_CAPABILITIES_MOTION_MODULE_FW_UPDATE , /**< provides method for upgrading motion module firmware */
    RS_CAPABILITIES_ADAPTER_BOARD           , /**< interanlly includes MIPI to USB adapter */
    RS_CAPABILITIES_ENUMERATION             , /**< provides enough basic functionality to be considered supported. this to catch at runtime various outdated engineering samples */
    RS_CAPABILITIES_COUNT                   , 
} rs_capabilities;

typedef enum rs_stream
{
    RS_STREAM_DEPTH                            , /**< Native stream of depth data produced by RealSense device */
    RS_STREAM_COLOR                            , /**< Native stream of color data captured by RealSense device */
    RS_STREAM_INFRARED                         , /**< Native stream of infrared data captured by RealSense device */
    RS_STREAM_INFRARED2                        , /**< Native stream of infrared data captured from a second viewpoint by RealSense device */
    RS_STREAM_FISHEYE                          ,
    RS_STREAM_POINTS                           , /**< Synthetic stream containing point cloud data generated by deprojecting the depth image */
    RS_STREAM_RECTIFIED_COLOR                  , /**< Synthetic stream containing undistorted color data with no extrinsic rotation from the depth stream */
    RS_STREAM_COLOR_ALIGNED_TO_DEPTH           , /**< Synthetic stream containing color data but sharing intrinsic of depth stream */
    RS_STREAM_INFRARED2_ALIGNED_TO_DEPTH       , /**< Synthetic stream containing second viewpoint infrared data but sharing intrinsic of depth stream */
    RS_STREAM_DEPTH_ALIGNED_TO_COLOR           , /**< Synthetic stream containing depth data but sharing intrinsic of color stream */
    RS_STREAM_DEPTH_ALIGNED_TO_RECTIFIED_COLOR ,  /**< Synthetic stream containing depth data but sharing intrinsic of rectified color stream */
    RS_STREAM_DEPTH_ALIGNED_TO_INFRARED2       , /**< Synthetic stream containing depth data but sharing intrinsic of second viewpoint infrared stream */
    RS_STREAM_COUNT
} rs_stream;

typedef enum rs_format
{
    RS_FORMAT_ANY         ,
    RS_FORMAT_Z16         , /**< 16 bit linear depth values. The depth is meters is equal to depth scale * pixel value */
    RS_FORMAT_DISPARITY16 , /**< 16 bit linear disparity values. The depth in meters is equal to depth scale / pixel value */
    RS_FORMAT_XYZ32F      , /**< 32 bit floating point 3D coordinates. */
    RS_FORMAT_YUYV        ,
    RS_FORMAT_RGB8        ,
    RS_FORMAT_BGR8        ,
    RS_FORMAT_RGBA8       ,
    RS_FORMAT_BGRA8       ,
    RS_FORMAT_Y8          ,
    RS_FORMAT_Y16         ,
    RS_FORMAT_RAW10       , /**< Four 10-bit luminance values encoded into a 5-byte macropixel */
    RS_FORMAT_RAW16       ,
    RS_FORMAT_RAW8        ,
    RS_FORMAT_COUNT
} rs_format;

typedef enum rs_output_buffer_format
{
    RS_OUTPUT_BUFFER_FORMAT_CONTINUOUS      ,/**< Makes sure that the output frame is exposed as a single continuous buffer */
    RS_OUTPUT_BUFFER_FORMAT_NATIVE         ,/**< Don't convert buffer to continuous, the user has to handle pitch manually */
    RS_OUTPUT_BUFFER_FORMAT_COUNT
} rs_output_buffer_format;

typedef enum rs_preset
{
    RS_PRESET_BEST_QUALITY     ,
    RS_PRESET_LARGEST_IMAGE    ,
    RS_PRESET_HIGHEST_FRAMERATE,
    RS_PRESET_COUNT
} rs_preset;

typedef enum rs_source
{
    RS_SOURCE_VIDEO          ,
    RS_SOURCE_MOTION_TRACKING,
    RS_SOURCE_ALL            ,
    RS_SOURCE_COUNT
} rs_source;

typedef enum rs_distortion
{
    RS_DISTORTION_NONE                  , /**< Rectilinear images, no distortion compensation required */
    RS_DISTORTION_MODIFIED_BROWN_CONRADY, /**< Equivalent to Brown-Conrady distortion, except that tangential distortion is applied to radially distorted points */
    RS_DISTORTION_INVERSE_BROWN_CONRADY , /**< Equivalent to Brown-Conrady distortion, except undistorts image instead of distorting it */
    RS_DISTORTION_FTHETA                , /**< F-Theta fish-eye distortion model */
    RS_DISTORTION_BROWN_CONRADY         , /**< Unmodified Brown-Conrady distortion model */
    RS_DISTORTION_COUNT                 ,
} rs_distortion;

typedef enum rs_ivcam_preset
{
    RS_IVCAM_PRESET_SHORT_RANGE             ,
    RS_IVCAM_PRESET_LONG_RANGE              ,
    RS_IVCAM_PRESET_BACKGROUND_SEGMENTATION ,
    RS_IVCAM_PRESET_GESTURE_RECOGNITION     ,
    RS_IVCAM_PRESET_OBJECT_SCANNING         ,
    RS_IVCAM_PRESET_FACE_ANALYTICS          ,
    RS_IVCAM_PRESET_FACE_LOGIN              ,
    RS_IVCAM_PRESET_GR_CURSOR               ,
    RS_IVCAM_PRESET_DEFAULT                 ,
    RS_IVCAM_PRESET_MID_RANGE               ,
    RS_IVCAM_PRESET_IR_ONLY                 ,
    RS_IVCAM_PRESET_COUNT
} rs_ivcam_preset;

typedef enum rs_option
{
    RS_OPTION_COLOR_BACKLIGHT_COMPENSATION                    , /**< Enable / disable color backlight compensation*/
    RS_OPTION_COLOR_BRIGHTNESS                                , /**< Color image brightness*/
    RS_OPTION_COLOR_CONTRAST                                  , /**< Color image contrast*/
    RS_OPTION_COLOR_EXPOSURE                                  , /**< Controls exposure time of color camera. Setting any value will disable auto exposure*/
    RS_OPTION_COLOR_GAIN                                      , /**< Color image gain*/
    RS_OPTION_COLOR_GAMMA                                     , /**< Color image gamma setting*/
    RS_OPTION_COLOR_HUE                                       , /**< Color image hue*/
    RS_OPTION_COLOR_SATURATION                                , /**< Color image saturation setting*/
    RS_OPTION_COLOR_SHARPNESS                                 , /**< Color image sharpness setting*/
    RS_OPTION_COLOR_WHITE_BALANCE                             , /**< Controls white balance of color image. Setting any value will disable auto white balance*/
    RS_OPTION_COLOR_ENABLE_AUTO_EXPOSURE                      , /**< Enable / disable color image auto-exposure*/
    RS_OPTION_COLOR_ENABLE_AUTO_WHITE_BALANCE                 , /**< Enable / disable color image auto-white-balance*/
    RS_OPTION_F200_LASER_POWER                                , /**< Power of the F200 / SR300 projector, with 0 meaning projector off*/
    RS_OPTION_F200_ACCURACY                                   , /**< Set the number of patterns projected per frame. The higher the accuracy value the more patterns projected. Increasing the number of patterns help to achieve better accuracy. Note that this control is affecting the Depth FPS */
    RS_OPTION_F200_MOTION_RANGE                               , /**< Motion vs. Range trade-off, with lower values allowing for better motion sensitivity and higher values allowing for better depth range*/
    RS_OPTION_F200_FILTER_OPTION                              , /**< Set the filter to apply to each depth frame. Each one of the filter is optimized per the application requirements*/
    RS_OPTION_F200_CONFIDENCE_THRESHOLD                       , /**< The confidence level threshold used by the Depth algorithm pipe to set whether a pixel will get a valid range or will be marked with invalid range*/
    RS_OPTION_F200_DYNAMIC_FPS                                , /**< (F200-only) Allows to reduce FPS without restarting streaming. Valid values are {2, 5, 15, 30, 60}*/
    RS_OPTION_SR300_AUTO_RANGE_ENABLE_MOTION_VERSUS_RANGE     , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_SR300_AUTO_RANGE_ENABLE_LASER                   , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_SR300_AUTO_RANGE_MIN_MOTION_VERSUS_RANGE        , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_SR300_AUTO_RANGE_MAX_MOTION_VERSUS_RANGE        , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_SR300_AUTO_RANGE_START_MOTION_VERSUS_RANGE      , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_SR300_AUTO_RANGE_MIN_LASER                      , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_SR300_AUTO_RANGE_MAX_LASER                      , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_SR300_AUTO_RANGE_START_LASER                    , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_SR300_AUTO_RANGE_UPPER_THRESHOLD                , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_SR300_AUTO_RANGE_LOWER_THRESHOLD                , /**< Configures SR300 Depth Auto-Range setting. Should not be used directly but through set IVCAM preset method*/
    RS_OPTION_R200_LR_AUTO_EXPOSURE_ENABLED                   , /**< Enables / disables R200 auto-exposure. This will affect both IR and depth image.*/
    RS_OPTION_R200_LR_GAIN                                    , /**< IR image gain*/
    RS_OPTION_R200_LR_EXPOSURE                                , /**< This control allows manual adjustment of the exposure time value for the L/R imagers*/
    RS_OPTION_R200_EMITTER_ENABLED                            , /**< Enables / disables R200 emitter*/
    RS_OPTION_R200_DEPTH_UNITS                                , /**< Micrometers per increment in integer depth values, 1000 is default (mm scale). Set before streaming*/
    RS_OPTION_R200_DEPTH_CLAMP_MIN                            , /**< Minimum depth in current depth units that will be output. Any values less than 'Min Depth' will be mapped to 0 during the conversion between disparity and depth. Set before streaming*/
    RS_OPTION_R200_DEPTH_CLAMP_MAX                            , /**< Maximum depth in current depth units that will be output. Any values greater than 'Max Depth' will be mapped to 0 during the conversion between disparity and depth. Set before streaming*/
    RS_OPTION_R200_DISPARITY_MULTIPLIER                       , /**< The disparity scale factor used when in disparity output mode. Can only be set before streaming*/
    RS_OPTION_R200_DISPARITY_SHIFT                            , /**< {0 - 512}. Can only be set before streaming starts*/
    RS_OPTION_R200_AUTO_EXPOSURE_MEAN_INTENSITY_SET_POINT     , /**< (Requires LR-Auto-Exposure ON) Mean intensity set point*/
    RS_OPTION_R200_AUTO_EXPOSURE_BRIGHT_RATIO_SET_POINT       , /**< (Requires LR-Auto-Exposure ON) Bright ratio set point*/
    RS_OPTION_R200_AUTO_EXPOSURE_KP_GAIN                      , /**< (Requires LR-Auto-Exposure ON) Kp Gain*/
    RS_OPTION_R200_AUTO_EXPOSURE_KP_EXPOSURE                  , /**< (Requires LR-Auto-Exposure ON) Kp Exposure*/
    RS_OPTION_R200_AUTO_EXPOSURE_KP_DARK_THRESHOLD            , /**< (Requires LR-Auto-Exposure ON) Kp Dark Threshold*/
    RS_OPTION_R200_AUTO_EXPOSURE_TOP_EDGE                     , /**< (Requires LR-Auto-Exposure ON) Auto-Exposure region-of-interest top edge (in pixels)*/
    RS_OPTION_R200_AUTO_EXPOSURE_BOTTOM_EDGE                  , /**< (Requires LR-Auto-Exposure ON) Auto-Exposure region-of-interest bottom edge (in pixels)*/
    RS_OPTION_R200_AUTO_EXPOSURE_LEFT_EDGE                    , /**< (Requires LR-Auto-Exposure ON) Auto-Exposure region-of-interest left edge (in pixels)*/
    RS_OPTION_R200_AUTO_EXPOSURE_RIGHT_EDGE                   , /**< (Requires LR-Auto-Exposure ON) Auto-Exposure region-of-interest right edge (in pixels)*/
    RS_OPTION_R200_DEPTH_CONTROL_ESTIMATE_MEDIAN_DECREMENT    , /**< Value to subtract when estimating the median of the correlation surface*/
    RS_OPTION_R200_DEPTH_CONTROL_ESTIMATE_MEDIAN_INCREMENT    , /**< Value to add when estimating the median of the correlation surface*/
    RS_OPTION_R200_DEPTH_CONTROL_MEDIAN_THRESHOLD             , /**< A threshold by how much the winning score must beat the median*/
    RS_OPTION_R200_DEPTH_CONTROL_SCORE_MINIMUM_THRESHOLD      , /**< The minimum correlation score that is considered acceptable*/
    RS_OPTION_R200_DEPTH_CONTROL_SCORE_MAXIMUM_THRESHOLD      , /**< The maximum correlation score that is considered acceptable*/
    RS_OPTION_R200_DEPTH_CONTROL_TEXTURE_COUNT_THRESHOLD      , /**< A parameter for determining whether the texture in the region is sufficient to justify a depth result*/
    RS_OPTION_R200_DEPTH_CONTROL_TEXTURE_DIFFERENCE_THRESHOLD , /**< A parameter for determining whether the texture in the region is sufficient to justify a depth result*/
    RS_OPTION_R200_DEPTH_CONTROL_SECOND_PEAK_THRESHOLD        , /**< A threshold on how much the minimum correlation score must differ from the next best score*/
    RS_OPTION_R200_DEPTH_CONTROL_NEIGHBOR_THRESHOLD           , /**< Neighbor threshold value for depth calculation*/
    RS_OPTION_R200_DEPTH_CONTROL_LR_THRESHOLD                 , /**< Left-Right threshold value for depth calculation*/
    RS_OPTION_FISHEYE_EXPOSURE                                , /**< Fisheye image exposure time in msec*/
    RS_OPTION_FISHEYE_GAIN                                    , /**< Fisheye image gain*/
    RS_OPTION_FISHEYE_STROBE                                  , /**< Enables / disables fisheye strobe. When enabled this will align timestamps to common clock-domain with the motion events*/
    RS_OPTION_FISHEYE_EXTERNAL_TRIGGER                        , /**< Enables / disables fisheye external trigger mode. When enabled fisheye image will be aquired in-sync with the depth image*/
    RS_OPTION_FISHEYE_ENABLE_AUTO_EXPOSURE                    , /**< Enable / disable fisheye auto-exposure */
    RS_OPTION_FISHEYE_AUTO_EXPOSURE_MODE                      , /**< 0 - static auto-exposure, 1 - anti-flicker auto-exposure, 2 - hybrid */
    RS_OPTION_FISHEYE_AUTO_EXPOSURE_ANTIFLICKER_RATE          , /**< Fisheye auto-exposure anti-flicker rate, can be 50 or 60 Hz */
    RS_OPTION_FISHEYE_AUTO_EXPOSURE_PIXEL_SAMPLE_RATE         , /**< In Fisheye auto-exposure sample frame every given number of pixels */
    RS_OPTION_FISHEYE_AUTO_EXPOSURE_SKIP_FRAMES               , /**< In Fisheye auto-exposure sample every given number of frames */
    RS_OPTION_FRAMES_QUEUE_SIZE                               , /**< Number of frames the user is allowed to keep per stream. Trying to hold-on to more frames will cause frame-drops.*/
    RS_OPTION_HARDWARE_LOGGER_ENABLED                         , /**< Enable / disable fetching log data from the device */
    RS_OPTION_TOTAL_FRAME_DROPS                               , /**< Total number of detected frame drops from all streams */
    RS_OPTION_RS400_LASER_POWER                               , /**< RS400 Emitter enabled */
    RS_OPTION_COUNT                                           ,

} rs_option;

typedef enum rs_blob_type {
    RS_BLOB_TYPE_MOTION_MODULE_FIRMWARE_UPDATE,
    RS_BLOB_TYPE_COUNT
}  rs_blob_type;

typedef enum rs_camera_info {
    RS_CAMERA_INFO_DEVICE_NAME                   ,
    RS_CAMERA_INFO_DEVICE_SERIAL_NUMBER          ,
    RS_CAMERA_INFO_CAMERA_FIRMWARE_VERSION       ,
    RS_CAMERA_INFO_ADAPTER_BOARD_FIRMWARE_VERSION,
    RS_CAMERA_INFO_MOTION_MODULE_FIRMWARE_VERSION,
    RS_CAMERA_INFO_CAMERA_TYPE                   ,
    RS_CAMERA_INFO_OEM_ID                        ,
    RS_CAMERA_INFO_ISP_FW_VERSION                ,
    RS_CAMERA_INFO_CONTENT_VERSION               ,
    RS_CAMERA_INFO_MODULE_VERSION                ,
    RS_CAMERA_INFO_IMAGER_MODEL_NUMBER           ,
    RS_CAMERA_INFO_BUILD_DATE                    ,
    RS_CAMERA_INFO_CALIBRATION_DATE              ,
    RS_CAMERA_INFO_PROGRAM_DATE                  ,
    RS_CAMERA_INFO_FOCUS_ALIGNMENT_DATE          ,
    RS_CAMERA_INFO_EMITTER_TYPE                  ,
    RS_CAMERA_INFO_FOCUS_VALUE                   ,
    RS_CAMERA_INFO_LENS_TYPE                     ,
    RS_CAMERA_INFO_3RD_LENS_TYPE                 ,
    RS_CAMERA_INFO_LENS_COATING__TYPE            ,
    RS_CAMERA_INFO_3RD_LENS_COATING_TYPE         ,
    RS_CAMERA_INFO_NOMINAL_BASELINE              ,
    RS_CAMERA_INFO_3RD_NOMINAL_BASELINE          ,
    RS_CAMERA_INFO_COUNT
} rs_camera_info;

typedef enum rs_log_severity {
    RS_LOG_SEVERITY_DEBUG, /* Detailed information about ordinary operations */
    RS_LOG_SEVERITY_INFO , /* Terse information about ordinary operations */
    RS_LOG_SEVERITY_WARN , /* Indication of possible failure */
    RS_LOG_SEVERITY_ERROR, /* Indication of definite failure */
    RS_LOG_SEVERITY_FATAL, /* Indication of unrecoverable failure */
    RS_LOG_SEVERITY_NONE , /* No logging will occur */
    RS_LOG_SEVERITY_COUNT
} rs_log_severity;

typedef enum rs_event_source
{
    RS_EVENT_IMU_ACCEL     ,
    RS_EVENT_IMU_GYRO      ,
    RS_EVENT_IMU_DEPTH_CAM ,
    RS_EVENT_IMU_MOTION_CAM,
    RS_EVENT_G0_SYNC       ,
    RS_EVENT_G1_SYNC       ,
    RS_EVENT_G2_SYNC       ,
    RS_EVENT_SOURCE_COUNT
}rs_event_source;

typedef enum rs_timestamp_domain
{
    RS_TIMESTAMP_DOMAIN_CAMERA         ,
    RS_TIMESTAMP_DOMAIN_MICROCONTROLLER,
    RS_TIMESTAMP_DOMAIN_COUNT
}rs_timestamp_domain;

typedef enum rs_subdevice
{
    RS_SUBDEVICE_COLOR,
    RS_SUBDEVICE_DEPTH,
    RS_SUBDEVICE_COUNT
} rs_subdevice;

typedef struct rs_intrinsics
{
    int           width;     /* width of the image in pixels */
    int           height;    /* height of the image in pixels */
    float         ppx;       /* horizontal coordinate of the principal point of the image, as a pixel offset from the left edge */
    float         ppy;       /* vertical coordinate of the principal point of the image, as a pixel offset from the top edge */
    float         fx;        /* focal length of the image plane, as a multiple of pixel width */
    float         fy;        /* focal length of the image plane, as a multiple of pixel height */
    rs_distortion model;     /* distortion model of the image */
    float         coeffs[5]; /* distortion coefficients */
} rs_intrinsics;

/* represents motion device intrinsic - scale, bias and variances */
typedef struct rs_motion_device_intrinsic
{
    /* Scale X        cross axis        cross axis      Bias X */
    /* cross axis     Scale Y           cross axis      Bias Y */
    /* cross axis     cross axis        Scale Z         Bias Z */
    float data[3][4];

    float noise_variances[3];
    float bias_variances[3];
} rs_motion_device_intrinsic;

/* represents motion module intrinsics including accelerometer and gyro intrinsics */
typedef struct rs_motion_intrinsics
{
    rs_motion_device_intrinsic acc;
    rs_motion_device_intrinsic gyro;
} rs_motion_intrinsics;

typedef struct rs_extrinsics
{
    float rotation[9];    /* column-major 3x3 rotation matrix */
    float translation[3]; /* 3 element translation vector, in meters */
} rs_extrinsics;

typedef struct rs_timestamp_data
{
    double              timestamp;     /* timestamp in milliseconds. hw resolution: 31.25usec */
    rs_event_source     source_id;
    unsigned long long  frame_number;
} rs_timestamp_data;

typedef struct rs_motion_data
{
    rs_timestamp_data   timestamp_data;
    unsigned int        is_valid;   /* boolean */
    float               axes[3];    /* Three [x,y,z] axes; 16 bit data for Gyro [rad/sec], 12 bit for Accelerometer; 2's complement [m/sec^2]*/
} rs_motion_data;


typedef struct rs_context rs_context;
typedef struct rs_device_info rs_device_info;
typedef struct rs_device_info_list rs_device_info_list;
typedef struct rs_device rs_device;
typedef struct rs_error rs_error;
typedef struct rs_stream_lock rs_stream_lock;
typedef struct rs_stream_profile_list rs_stream_profile_list;
typedef struct rs_frame_ref rs_frame_ref;

typedef struct rs_frame_callback rs_frame_callback;
typedef struct rs_log_callback rs_log_callback;

typedef void (*rs_frame_callback_ptr)(const rs_stream_lock*, rs_frame_ref*, void*);
typedef void (*rs_log_callback_ptr)(rs_log_severity min_severity, const char* message, void* user);

rs_context* rs_create_context(int api_version, rs_error** error);
void rs_delete_context(rs_context* context);

rs_device_info_list* rs_query_devices(const rs_context* context, rs_error** error);
int rs_get_device_list_size(const rs_device_info_list* info_list, rs_error** error);
void rs_delete_device_info_list(rs_device_info_list* info_list);

rs_device_info* rs_get_device_info(const rs_device_info_list* info_list, int index, rs_error** error);
void rs_delete_device_info(rs_device_info* info_list);

rs_device* rs_create_device(const rs_context* context, const rs_device_info* info, rs_error** error);
void rs_delete_device(rs_device* device);

int rs_is_subdevice_supported(const rs_device* device, rs_subdevice subdevice, rs_error** error);

rs_stream_profile_list* rs_get_supported_profiles(rs_device* device, rs_subdevice subdevice, rs_error** error);
void rs_get_profile(const rs_stream_profile_list* list, int index, rs_stream* stream, int* width, int* height, int* fps, rs_format* format, rs_error** error);
int rs_get_profile_list_size(const rs_stream_profile_list* list, rs_error** error);
void rs_delete_profiles_list(rs_stream_profile_list* list);

rs_stream_lock* rs_open_subdevice(rs_device* device, rs_subdevice subdevice, rs_stream stream, int width, int height, int fps, rs_format format, rs_error** error);
void rs_release_streaming_lock(rs_stream_lock* lock);

void rs_play(rs_stream_lock* lock, rs_frame_callback_ptr on_frame, void * user, rs_error ** error);
void rs_play_cpp(rs_stream_lock* lock, rs_frame_callback * callback, rs_error ** error);
void rs_stop(rs_stream_lock* lock, rs_error ** error);

double rs_get_frame_metadata(const rs_frame_ref * frame, rs_frame_metadata frame_metadata, rs_error ** error);
int rs_supports_frame_metadata(const rs_frame_ref * frame, rs_frame_metadata frame_metadata, rs_error ** error);
double rs_get_frame_timestamp(const rs_frame_ref * frame, rs_error ** error);
rs_timestamp_domain rs_get_frame_timestamp_domain(const rs_frame_ref * frameset, rs_error ** error);
unsigned long long rs_get_frame_number(const rs_frame_ref * frame, rs_error ** error);
const void * rs_get_frame_data(const rs_frame_ref * frame, rs_error ** error);
int rs_get_frame_width(const rs_frame_ref * frame, rs_error ** error);
int rs_get_frame_height(const rs_frame_ref * frame, rs_error ** error);
int rs_get_frame_stride_in_bytes(const rs_frame_ref * frame, rs_error ** error);
int rs_get_frame_bits_per_pixel(const rs_frame_ref * frame, rs_error ** error);
rs_format rs_get_frame_format(const rs_frame_ref * frame, rs_error ** error);
rs_stream rs_get_frame_stream_type(const rs_frame_ref * frameset, rs_error ** error);
void rs_release_frame(const rs_stream_lock* lock, rs_frame_ref * frame);

float rs_get_subdevice_option(const rs_device* device, rs_subdevice subdevice, rs_option option, rs_error** error);
void rs_set_subdevice_option(const rs_device* device, rs_subdevice subdevice, rs_option option, float value, rs_error** error);
int rs_supports_subdevice_option(const rs_device* device, rs_subdevice subdevice, rs_option option, rs_error** error);

/**
* retrieve the API version from the source code. Evaluate that the value is conformant to the established policies
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
* \return            the version API encoded into integer value "1.9.3" -> 10903
*/
int          rs_get_api_version      (rs_error ** error);

const char * rs_get_failed_function  (const rs_error * error);
const char * rs_get_failed_args      (const rs_error * error);
const char * rs_get_error_message    (const rs_error * error);
void         rs_free_error           (rs_error * error);


const char * rs_stream_to_string     (rs_stream stream);
const char * rs_format_to_string     (rs_format format);
const char * rs_preset_to_string     (rs_preset preset);
const char * rs_distortion_to_string (rs_distortion distortion);
const char * rs_option_to_string     (rs_option option);
const char * rs_capabilities_to_string(rs_capabilities capability);
const char * rs_source_to_string     (rs_source source);
const char * rs_event_to_string      (rs_event_source event);
const char * rs_blob_type_to_string  (rs_blob_type type);
const char * rs_camera_info_to_string(rs_camera_info info);
const char * rs_camera_info_to_string(rs_camera_info info);
const char * rs_timestamp_domain_to_string(rs_timestamp_domain info);
const char * rs_subdevice_to_string  (rs_subdevice subdevice);


void rs_log_to_console(rs_log_severity min_severity, rs_error ** error);
void rs_log_to_file(rs_log_severity min_severity, const char * file_path, rs_error ** error);
void rs_log_to_callback_cpp(rs_log_severity min_severity, rs_log_callback * callback, rs_error ** error);
void rs_log_to_callback(rs_log_severity min_severity, rs_log_callback_ptr on_log, void * user, rs_error ** error);

#ifdef __cplusplus
}
#endif
#endif
