// Copyright 2026 Kiwibot

#ifndef USB_CAM__FORMATS__NV12_HPP_
#define USB_CAM__FORMATS__NV12_HPP_

#include "linux/videodev2.h"

#include "opencv2/imgproc.hpp"

#include "usb_cam/formats/pixel_format_base.hpp"
#include "usb_cam/formats/utils.hpp"


namespace usb_cam
{
namespace formats
{

// NV12 is a full luma plane followed by one interleaved half resolution UV plane
class NV122RGB : public pixel_format_base
{
public:
  explicit NV122RGB(const format_arguments_t & args = format_arguments_t())
  : pixel_format_base(
      "nv122rgb",
      V4L2_PIX_FMT_NV12,
      usb_cam::constants::RGB8,
      3,
      8,
      true),
    m_width(args.width),
    m_height(args.height)
  {}

  void convert(const char * & src, char * & dest, const int & bytes_used) override
  {
    (void)bytes_used;
    const cv::Mat cv_img(m_height * 3 / 2, m_width, CV_8UC1, const_cast<char *>(src));
    cv::Mat cv_out(m_height, m_width, CV_8UC3, dest);
    cv::cvtColor(cv_img, cv_out, cv::COLOR_YUV2RGB_NV12);
  }

private:
  int m_width;
  int m_height;
};

}  // namespace formats
}  // namespace usb_cam

#endif  // USB_CAM__FORMATS__NV12_HPP_
