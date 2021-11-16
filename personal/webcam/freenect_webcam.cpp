#include "freenect_webcam.hpp"

FreenectWebcam::FreenectWebcam(freenect_context *_ctx, int _index)
    : Freenect::FreenectDevice(_ctx, _index),
        // m_buffer_depth(freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB).bytes),
        // m_buffer_video(freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB).bytes),
        m_buffer_video(FREENECT_VIDEO_RGB),
        m_buffer_depth(FREENECT_DEPTH_11BIT),        
        rgb_mat(cv::Size(640, 480), CV_8UC3, cv::Scalar(0)),
        depth_mat(cv::Size(640, 480), CV_16UC1, cv::Scalar(0)),
        own_mat(cv::Size(640, 480), CV_8UC3, cv::Scalar(0)),
        m_gamma(2048),
        m_new_rgb_frame(false),
        m_new_depth_frame(false)
{
    for (unsigned int i = 0; i < 2048; ++i)
    {
        float v = i / 2048.0;
        v = std::pow(v, 3) * 6;
        m_gamma[i] = v * 6 * 256;
    }
}

FreenectWebcam::~FreenectWebcam()
{

}

void FreenectWebcam::VideoCallback(void *_rgb, uint32_t timestamp)
{
    ScopedLock lock(m_rgb_mutex);
    uint8_t *rgb = static_cast<uint8_t*>(_rgb);

    rgb_mat.data = rgb;
    m_new_rgb_frame = true;
}

void FreenectWebcam::DepthCallback(void *_depth, uint32_t timestamp)
{
    ScopedLock lock(m_depth_mutex);
    uint16_t *depth = static_cast<uint16_t*>(_depth);

    depth_mat.data = (uchar *) depth;
    m_new_depth_frame = true;
}

bool FreenectWebcam::getRGB(cv::Mat &output)
{
    ScopedLock lock(m_rgb_mutex);
    if (!m_new_rgb_frame) return false;

    cv::cvtColor(rgb_mat, output, cv::COLOR_RGB2BGR);

    m_new_rgb_frame = false;
    return true;
}

bool FreenectWebcam::getDepth(cv::Mat &output)
{
    ScopedLock lock(m_depth_mutex);
    if (!m_new_depth_frame) return false;
    
    depth_mat.copyTo(output);
    // cv::cvtColor(depth_mat, output, cv::COLOR_RGB2BGR);

    m_new_depth_frame = false;
    return true;
}


// void FreenectWebcam::VideoCallback(void *_rgb, uint32_t timestamp)
// {
//     ScopedLock lock(m_rgb_mutex);
//     uint8_t *rgb = static_cast<uint8_t*>(_rgb);
//     std::copy(rgb, rgb + getVideoBufferSize(), m_buffer_video.begin());
//     m_new_rgb_frame = true;
// }

// void FreenectWebcam::DepthCallback(void *_depth, uint32_t timestamp)
// {
//     ScopedLock lock(m_depth_mutex);
//     uint16_t* depth = static_cast<uint16_t*>(_depth);

//     for (unsigned int i = 0; i < 640 * 480; ++i)
//     {
//         int pval = m_gamma[depth[i]];
//         int lb = pval & 0xff;

//         switch (pval >> 8)
//         {
// 			case 0:
// 				m_buffer_depth[3*i+0] = 255;
// 				m_buffer_depth[3*i+1] = 255-lb;
// 				m_buffer_depth[3*i+2] = 255-lb;
// 				break;

// 			case 1:
// 				m_buffer_depth[3*i+0] = 255;
// 				m_buffer_depth[3*i+1] = lb;
// 				m_buffer_depth[3*i+2] = 0;
// 				break;
            
// 			case 2:
// 				m_buffer_depth[3*i+0] = 255-lb;
// 				m_buffer_depth[3*i+1] = 255;
// 				m_buffer_depth[3*i+2] = 0;
// 				break;
            
// 			case 3:
// 				m_buffer_depth[3*i+0] = 0;
// 				m_buffer_depth[3*i+1] = 255;
// 				m_buffer_depth[3*i+2] = lb;
// 				break;
            
// 			case 4:
// 				m_buffer_depth[3*i+0] = 0;
// 				m_buffer_depth[3*i+1] = 255-lb;
// 				m_buffer_depth[3*i+2] = 255;
// 				break;
            
// 			case 5:
// 				m_buffer_depth[3*i+0] = 0;
// 				m_buffer_depth[3*i+1] = 0;
// 				m_buffer_depth[3*i+2] = 255-lb;
// 				break;
            
// 			default:
// 				m_buffer_depth[3*i+0] = 0;
// 				m_buffer_depth[3*i+1] = 0;
// 				m_buffer_depth[3*i+2] = 0;
// 				break;
//         }

//         m_new_depth_frame = true;
//     }
// }

// bool FreenectWebcam::getRGB(std::vector<uint8_t> &buffer)
// {
//     ScopedLock lock(m_rgb_mutex);

//     if (!m_new_rgb_frame) return false;
//     buffer.swap(m_buffer_video);

//     m_new_rgb_frame = false;
//     return true;
// }

// bool FreenectWebcam::getDepth(std::vector<uint8_t> &buffer)
// {
//     ScopedLock lock(m_depth_mutex);
    
//     if (!m_new_depth_frame) return false;
//     buffer.swap(m_buffer_depth);

//     m_new_depth_frame = false;
//     return true;
// }
;