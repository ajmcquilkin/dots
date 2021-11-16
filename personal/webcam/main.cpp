// Reference: https://github.com/umlaeute/v4l2loopback/blob/main/examples/test.c

#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <chrono>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>

#include <opencv4/opencv2/opencv.hpp>

#include "libfreenect.hpp"
#include "freenect_webcam.hpp"

#define ROUND_UP_2(num)  (((num)+1)&~1)
#define ROUND_UP_4(num)  (((num)+3)&~3)
#define ROUND_UP_8(num)  (((num)+7)&~7)
#define ROUND_UP_16(num) (((num)+15)&~15)
#define ROUND_UP_32(num) (((num)+31)&~31)
#define ROUND_UP_64(num) (((num)+63)&~63)

#if 0
# define CHECK_REREAD
#endif

#define VIDEO_DEVICE "/dev/video0"
#if 1
# define FRAME_WIDTH  640
# define FRAME_HEIGHT 480
#else
# define FRAME_WIDTH  512
# define FRAME_HEIGHT 512
#endif

#if 0
# define FRAME_FORMAT V4L2_PIX_FMT_YUYV
#else
// # define FRAME_FORMAT V4L2_PIX_FMT_YVU420 
# define FRAME_FORMAT V4L2_PIX_FMT_RGB24
#endif

static int debug = 0;

int format_properties(
    const unsigned int format,
    const unsigned width,
    const unsigned int height,
    size_t *line_width,
    size_t *frame_width)
{
    size_t lw, fw;
    switch (format)
    {
        case V4L2_PIX_FMT_YUV420:
        case V4L2_PIX_FMT_YVU420:
            lw = width;
            fw = ROUND_UP_4(width) * ROUND_UP_2(height);
            fw += 2 * ((ROUND_UP_8(width) / 2) * (ROUND_UP_2(height) / 2));
            break;

        case V4L2_PIX_FMT_UYVY:
        case V4L2_PIX_FMT_Y41P:
        case V4L2_PIX_FMT_YUYV:
        case V4L2_PIX_FMT_YVYU:
            lw = (ROUND_UP_2(width) * 2);
            fw = lw * height;
            break;

        default:
            return 0;
    }

    if (line_width) *line_width = lw;
    if (frame_width) *frame_width = fw;

    return 1;    
}

void print_format(struct v4l2_format *vid_format) {
    printf("	vid_format->type                =%d\n",	vid_format->type );
    printf("	vid_format->fmt.pix.width       =%d\n",	vid_format->fmt.pix.width );
    printf("	vid_format->fmt.pix.height      =%d\n",	vid_format->fmt.pix.height );
    printf("	vid_format->fmt.pix.pixelformat =%d\n",	vid_format->fmt.pix.pixelformat);
    printf("	vid_format->fmt.pix.sizeimage   =%d\n",	vid_format->fmt.pix.sizeimage );
    printf("	vid_format->fmt.pix.field       =%d\n",	vid_format->fmt.pix.field );
    printf("	vid_format->fmt.pix.bytesperline=%d\n",	vid_format->fmt.pix.bytesperline );
    printf("	vid_format->fmt.pix.colorspace  =%d\n",	vid_format->fmt.pix.colorspace );
}

// int loop(int argc, char **argv, FreenectWebcam *device, unsigned int fdwr)
// {
//     std::vector<uint8_t> depth(640*480*4);
//     std::vector<uint8_t> rgb(640*480*4);

//     device->getDepth(depth);
//     device->getRGB(rgb);

//     // Initialize video output

//     struct v4l2_capability vid_caps;
//     struct v4l2_format vid_format;

//     size_t line_width = 640;
//     size_t frame_size = rgb.size();

//     __u8 *buffer;
//     __u8 *check_buffer;
//     int ret_code = 0;

//     ret_code = ioctl(fdwr, VIDIOC_QUERYCAP, &vid_caps);
//     assert(ret_code != -1);

//     memset(&vid_format, 0, sizeof(vid_format));

//     ret_code = ioctl(fdwr, VIDIOC_G_FMT, &vid_format);
//     if (debug) print_format(&vid_format);

//     vid_format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
// 	vid_format.fmt.pix.width = FRAME_WIDTH;
// 	vid_format.fmt.pix.height = FRAME_HEIGHT;
// 	vid_format.fmt.pix.pixelformat = FRAME_FORMAT;
// 	vid_format.fmt.pix.sizeimage = frame_size;
// 	vid_format.fmt.pix.field = V4L2_FIELD_NONE;
// 	vid_format.fmt.pix.bytesperline = line_width;
// 	vid_format.fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;

//     printf("format size: %d\n", vid_format.fmt.pix.sizeimage);

//     if (debug) print_format(&vid_format);
//     ret_code = ioctl(fdwr, VIDIOC_S_FMT, &vid_format);

//     assert(ret_code != -1);

//     if(debug) printf("frame: format=%d\tsize=%lu\n", FRAME_FORMAT, frame_size);
//     // print_format(&vid_format);

//     if (!format_properties(
//         vid_format.fmt.pix.pixelformat,
//         vid_format.fmt.pix.width,
//         vid_format.fmt.pix.height,
//         &line_width,
//         &frame_size))
//     {
//         // printf("unable to guess correct settings for format '%d'\n", FRAME_FORMAT);
//     }

//     buffer = (__u8*) malloc(sizeof(__u8) * frame_size);
//     check_buffer = (__u8*) malloc(sizeof(__u8) * frame_size);

//     // printf("size of rgb: %d, size of frame: %d\n", rgb.size(), sizeof(__u8) * frame_size);

//     // Copy camera information to video output

//     // std::copy(depth.begin(), depth.end(), buffer);
//     // std::copy(depth.begin(), depth.end(), check_buffer);

//     std::copy(rgb.begin(), rgb.end(), buffer);
//     std::copy(rgb.begin(), rgb.end(), check_buffer);

//     // memset(buffer, 0, frame_size);
//     // memset(check_buffer, 0, frame_size);

//     for (int i = 0; i < frame_size; ++i)
//     {
//         check_buffer[i] = 0;
//     }

//     write(fdwr, buffer, frame_size);

//     // Check for optional reread

//     #ifdef CHECK_REREAD
//     do {
//     /* check if we get the same data on output */
//     int fdr = open(video_device, O_RDONLY);
//     read(fdr, check_buffer, framesize);
//     for (i = 0; i < framesize; ++i) {
//         if (buffer[i] != check_buffer[i])
//             assert(0);
//     }
//     close(fdr);
//     } while(0);
//     #endif

//     // pause();

//     free(buffer);
//     free(check_buffer);

//     return 0;
// }

int main(int argc, char *argv[])
{
    // Initialize capture device

    Freenect::Freenect freenect;
    FreenectWebcam* device;
    freenect_video_format requested_format(FREENECT_VIDEO_RGB);

    device = &freenect.createDevice<FreenectWebcam>(0);
	device->startVideo();
	device->startDepth();

    // Initialize device

    const char *video_device = VIDEO_DEVICE;
    int fdwr = 0;
    int ret_code = 0;

    if (argc > 1)
    {
        video_device = argv[1];
        printf("using output device: %s\n", video_device);
    }

    fdwr = open(video_device, O_RDWR);
    assert(fdwr >= 0);

    // Loop

    int n_frames = 0;

    cv::Mat rgb_mat;
    cv::Mat depth_mat;
    cv::Mat own_mat;

    cv::namedWindow("rgb", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("depth", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("out", cv::WINDOW_AUTOSIZE);

    while (true)
    {
        // printf("frame: %d\n", n_frames++);

        // Get frames

        device->getRGB(rgb_mat);
        device->getDepth(depth_mat);

        // Calibrate frames

        cv::stereoRectify()

        // Convert to required formats

        rgb_mat.convertTo(rgb_mat, CV_32FC3, 1.0 / 255.0);
        depth_mat.convertTo(depth_mat, CV_32FC1, 1.0 / 2048.0);

        // rgb_mat.convertTo(rgb_mat, CV_8UC3);
        // depth_mat.convertTo(depthf, CV_8UC1, 255.0 / 2048.0);

        // Variable setup

        cv::Mat alpha_mat = cv::Mat::zeros(rgb_mat.size(), rgb_mat.type());
        cv::Mat out_image_mat = cv::Mat::zeros(rgb_mat.size(), rgb_mat.type());
        cv::Mat background_image_mat(480, 640, rgb_mat.type(), cv::Scalar(255, 0, 0));

        // Display starting images

        cv::imshow("rgb", rgb_mat);
        cv::imshow("depth", depth_mat); // depth_mat

        // Convert depth into three channels

        cv::Mat temp_depth_mat[] = { depth_mat, depth_mat, depth_mat };
        cv::merge(temp_depth_mat, 3, alpha_mat);

        // Multiply images into output image

        cv::Mat temp_mat;
        // cv::multiply(alpha_mat / 1.0, rgb_mat, out_image_mat);
        cv::add(alpha_mat, background_image_mat, out_image_mat);

        // Display output image

        cv::imshow("out", out_image_mat);

        // // depth_mat.convertTo(depthf, CV_8UC1, 255.0 / 2048.0);
        // // cv::imshow("depth", depthf);

        // rgb_mat.convertTo(rgb_mat, CV_32FC3);
        // // depth_mat.convertTo(depth_mat, CV_32FC1, 1.0 / 255.0);

        // cv::Mat alpha_mat = cv::Mat::ones(rgb_mat.size(), rgb_mat.type());

        // // std::vector<cv::Mat> channels { depth_mat, depth_mat, depth_mat };
        // // std::vector<cv::Mat> channels { alpha_mat, alpha_mat, alpha_mat };
        // // cv::merge(channels, alpha_mat);

        // // printf("%d, %d\n", rgb_mat.channels(), depth_mat.channels());
        // cv::Mat out_image = cv::Mat::zeros(rgb_mat.size(), CV_32FC4);
        // // rgb_mat.copyTo(out_image);

        // // Split rgb image into channels
        // std::vector<cv::Mat> rgb_channels;
        // cv::split(rgb_mat, rgb_channels);

        // // Create and merge alpha channel into output
        // cv::Mat updated_alpha = rgb_channels.at(0) + rgb_channels.at(1) + rgb_channels.at(2) + depth_mat;
        // rgb_channels.push_back(updated_alpha);
        // cv::merge(rgb_channels, out_image);

        // // cv::imshow("depth", depth_mat);
        // // cv::multiply(rgb_mat, alpha_mat, out_image);
        // cv::imshow("out", out_image / 255.0);

        // // write(fdwr, rgb_mat.data, rgb_mat.size().width * rgb_mat.size().height * sizeof(__u8));

        char c = (char) cv::waitKey(25);
        if (c == 27) break;
        
        // ret_code = loop(argc, argv, device, fdwr);
        // if (ret_code) break;

        // std::chrono::milliseconds timespan(20);
        // std::this_thread::sleep_for(timespan);
    }

    // Tear down capture device

	device->stopVideo();
	device->stopDepth();

    close(fdwr);
    return ret_code;
}
