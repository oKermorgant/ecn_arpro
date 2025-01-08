#ifndef MAZE_H
#define MAZE_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <point.h>

namespace ecn
{

typedef std::pair<int, int> Pair;

class Maze
{
public:
  Maze() {}

  void load(int argc, char** argv)
  {
    if(argc == 2)
      load(argv[1]);
    else
      load(DEFAULT_MAZE);
  }

  void load(const std::string &_filename)
  {
    std::cout << "Loading " << _filename << " ...";
    filename = _filename;
    im = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    std::cout << "ok" << std::endl;
  }

  Maze(int height, int width)
  {
    im = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
  }

  bool isFree(int x, int y) const
  {
    if(x < 0 || y < 0 || x >= im.cols || y >= im.rows)
      return 0;
    return im.at<uchar>(y,x);
  }

  inline bool isFree(const Point &p) const
  {
    return isFree(p.x, p.y);
  }

  inline int height() const {return im.rows;}
  inline int width() const {return im.cols;}


    ecn::Point start()
    {
        Point ret;
        for(ret.y=0;ret.y<im.rows; ++ret.y)
        {
            for(ret.x=0;ret.x<im.cols;++ret.x)
            {
                if(isFree(ret.x, ret.y))
                {
                    std::cout << "Start @ (" << ret.x << ", " << ret.y << ")\n";
                    return ret;
                }
            }
        }
        return ret;
    }

    ecn::Point end()
    {
        Point ret;
        for(ret.y=im.rows-1;ret.y> 0; --ret.y)
        {
            for(ret.x=im.cols-1;ret.x>0;--ret.x)
            {
                if(isFree(ret.x, ret.y))
                {
                    std::cout << "End @ (" << ret.x << ", " << ret.y << ")\n";
                    return ret;
                }
            }
        }
        return ret;
    }


  void passThrough(int x, int y)
  {
    const auto p = cv::Point(x,y);
    if(!path.empty() && path.back() == p)
      return;
    path.emplace_back(p);
  }

  void dig(int x, int y)
  {
    im.at<uchar>(y,x) = 255;
  }

  void display(const std::string &name, const cv::Mat &im)
  {
    if(std::find(windows.begin(), windows.end(), name) == windows.end())
    {
      windows.push_back(name);
      cv::namedWindow(name, cv::WINDOW_NORMAL);
      cv::resizeWindow(name, 1000, (1000*im.rows)/im.cols);
    }
    cv::imshow(name, im);
  }

  void save()
  {
    cv::imwrite(DEFAULT_MAZE, im);
    display("Maze", im);
  }

  void saveSolution(const std::string &suffix)
  {
    cv::Mat out;
    cv::cvtColor(im, out, cv::COLOR_GRAY2BGR);
    const auto len{path.size()};

    cv::Vec3b col{0,0,0};
    for(int i = 0; i < len; ++i)
    {
      col[2] = i*255/(len-1);
      col[0] = 255-col[2];
      out.at<cv::Vec3b>(path[i]) = col;
    }

    // re-write black nodes just to be sure...
    for(int x = 0; x < im.cols; ++x)
    {
      for(int y = 0; y < im.rows; ++y)
      {
        if(!isFree(x,y))
          out.at<cv::Vec3b>(y,x) = {0,0,0};
      }
    }

    const auto dot{filename.find_last_of(".")};
    const auto name{filename.substr(0, dot) + "_" + suffix + ".png"};
    cv::imwrite(name, out);
    display("Solution", out);
  }
protected:
  cv::Mat im;
  std::string filename;
  std::vector<cv::Point> path;
  std::vector<std::string> windows;
};
}


#endif

