// Reference: https://github.com/OpenKinect/libfreenect/blob/master/wrappers/cpp/cppview.cpp
// Reference: https://openkinect.org/wiki/C%2B%2BOpenCvExample

#pragma once

#include <libfreenect/libfreenect.hpp>
#include <opencv4/opencv2/opencv.hpp>

#include <cmath>
#include <vector>

#include "mutex.hpp"
#include "scoped_lock.hpp"

class FreenectWebcam : public Freenect::FreenectDevice
{
    public:
        FreenectWebcam(freenect_context *ctx, int _index);
        ~FreenectWebcam();

        void VideoCallback(void *_rgb, uint32_t timestamp);
        void DepthCallback(void *_depth, uint32_t timestamp);

        bool getRGB(cv::Mat &buffer);
        bool getDepth(cv::Mat &buffer);

        // bool getRGB(std::vector<uint8_t> &buffer);
        // bool getDepth(std::vector<uint8_t> &buffer);

    private:
        std::vector<uint8_t> m_buffer_video;
        std::vector<uint8_t> m_buffer_depth;

        cv::Mat rgb_mat;
        cv::Mat depth_mat;
        cv::Mat own_mat;

        std::vector<uint16_t> m_gamma;

        Mutex m_rgb_mutex;
        Mutex m_depth_mutex;

        bool m_new_rgb_frame;
        bool m_new_depth_frame;
};
