#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

int main(int argc, char **argv) {
  if (argc != 4) { // 引数チェック
    cout << "Usage : ./a.out <PictDir> <template_img> <DistDir>" << endl;
    return -1;
  }

  struct stat st;
  int st_code;

  st_code = stat(argv[1], &st);
  if (st_code != 0) { // PictDirの存在チェック
    cout << argv[1] << " is not exist." << endl;
    return -1;
  }
  if ((st.st_mode & S_IFDIR) != S_IFDIR) { // PictDir is directory?
    cout << st.st_mode << endl;
    cout << argv[1] << " is not directory." << endl;
    return -1;
  }

  // テンプレート画像の取得
  IplImage *tmp_img;
  if ((tmp_img = cvLoadImage(argv[2], CV_LOAD_IMAGE_COLOR)) == 0) {
    cout << argv[2] << " can't open." << endl;
    return -1;
  }

  st_code = stat(argv[3], &st);
  if (st_code != 0) { // DistDirの存在チェック
    cout << argv[3] << " is not exist." << endl;
    return -1;
  }
  if ((st.st_mode & S_IFDIR) != S_IFDIR) { // DistDir is directory?
    cout << argv[3] << " is not directory." << endl;
    return -1;
  }

  DIR* dir_ptr = opendir(argv[1]);
  if (dir_ptr == NULL) {
    cout << argv[1] << " can't open." << endl;
    return -1;
  }

  struct dirent* dir_entry;
  double min_val, max_val;
  CvPoint min_loc, max_loc;
  CvSize dst_size;
  IplImage *src_img, *dst_img;

  while ((dir_entry = readdir(dir_ptr)) != NULL) {
    string file_path = string(argv[1]) + string(dir_entry->d_name);

    if ((src_img = cvLoadImage(file_path.c_str(), CV_LOAD_IMAGE_COLOR)) == 0) {
      cout << file_path << " can't open." << endl;
      continue;
    }

    dst_size = cvSize(src_img->width - tmp_img->width + 1, src_img->height - tmp_img->height + 1);
    dst_img = cvCreateImage(dst_size, IPL_DEPTH_32F, 1);
    cv::matchTemplate(cv::cvarrToMat(src_img), cv::cvarrToMat(tmp_img), cv::cvarrToMat(dst_img), CV_TM_CCOEFF_NORMED);
    cvMinMaxLoc(dst_img, &min_val, &max_val, &min_loc, &max_loc, NULL);

    cout << file_path << " : " << max_val << endl;

    if (max_val >= 0.5) {
      string dist_dir = (*(string(argv[3]).end()) == '/' ? string(argv[3]) : string(argv[3]) + '/');

      cvRectangle(src_img, max_loc, cvPoint(max_loc.x + tmp_img->width, max_loc.y + tmp_img->height), CV_RGB(255, 0, 0), 3);
      cvSaveImage((dist_dir + "tm_" + string(dir_entry->d_name)).c_str(), src_img);

      cout << "Create " << dist_dir + "tm_" + string(dir_entry->d_name) << endl;
    }

    cvReleaseImage(&src_img);
    cvReleaseImage(&dst_img);
  }

  cvReleaseImage(&tmp_img);
  closedir(dir_ptr);

  return 0;
}
