#include <opencv2/opencv.hpp>
#include <iostream>
// #include <filesystem> // std::tr2::sys::path etc.
#include <regex>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

int main(int argc, char **argv) {
  IplImage *tmp_img;

  if (argc != 2) {
    return -1;
  }

  DIR* dp = opendir(argv[1]);
  if (dp != NULL) {
    struct dirent* dent;

    do{
      dent = readdir(dp);
      if (dent!=NULL)
        cout << dent->d_name << endl;
    } while (dent!=NULL);

    closedir(dp);
  } else {
    cout << "error" << endl;
  }
  // namespace sys = std::tr2::sys;
  //
  // std::for_each(sys::directory_iterator(p), sys::directory_iterator(), [&tmp_img](const sys::path& p) {
  //     std::regex re("201604");
  //
  //     if (sys::is_regular_file(p) && std::regex_match(p.filename(), re)) {
  //     //OutputDebugString();
  //     cout << "file: " << p.filename() << endl;
  //
  //     double min_val, max_val;
  //     CvPoint min_loc, max_loc;
  //     CvSize dst_size;
  //     IplImage *src_img, *dst_img;
  //
  //     if ((src_img = cvLoadImage(p.filename().c_str(), CV_LOAD_IMAGE_COLOR)) == 0)
  //     exit(-1);
  //
  //     // (1)探索画像全体に対して，テンプレートのマッチング値（指定した手法に依存）を計算
  //     dst_size = cvSize(src_img->width - tmp_img->width + 1, src_img->height - tmp_img->height + 1);
  //     dst_img = cvCreateImage(dst_size, IPL_DEPTH_32F, 1);
  //     cv::matchTemplate(cv::cvarrToMat(src_img), cv::cvarrToMat(tmp_img), cv::cvarrToMat(dst_img), CV_TM_CCOEFF_NORMED);
  //     cvMinMaxLoc(dst_img, &min_val, &max_val, &min_loc, &max_loc, NULL);
  //
  //     // (2)テンプレートに対応する位置に矩形を描画
  //     cvRectangle(src_img, max_loc,
  //         cvPoint(max_loc.x + tmp_img->width, max_loc.y + tmp_img->height), CV_RGB(255, 0, 0), 3);
  //     cvNamedWindow("Image", 1);
  //     cvShowImage("Image", src_img);
  //     cvWaitKey(0);
  //
  //     cvDestroyWindow("Image");
  //     cvReleaseImage(&src_img);
  //     cvReleaseImage(&tmp_img);
  //     cvReleaseImage(&dst_img);
  //     }
  // });

  return 0;
}
