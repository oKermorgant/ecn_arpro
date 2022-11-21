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
  static std::string mazeFile(const std::string &file = "maze.png")
  {
    std::string abs_file = MAZES;
    return abs_file + "/" + file;
  }
  Maze() {}

  Maze(std::string _filename)
  {
    load(_filename);
  }

  void load(std::string _filename)
  {
    std::cout << "Loading " << _filename << " ...";
    filename = _filename;
    im = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    cv::cvtColor(im, out, cv::COLOR_GRAY2BGR);
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
    path.push_back(cv::Point(x,y));
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

  void write(int x, int y, int r=0, int g=0, int b=0, bool show = true)
  {
    out.at<cv::Vec3b>(y, x) = cv::Vec3b(b, g, r);
    if(show)
    {
      display("Maze", out);
      cv::waitKey(1);
    }
  }

  void save()
  {
    cv::imwrite(mazeFile(), im);
    display("Maze", im);
  }

  void saveSolution(std::string suffix)
  {
    cv::cvtColor(im, out, cv::COLOR_GRAY2BGR);
    cv::Vec3b col(0, 255, 0);

    col[1] = 0;
    for(int i = 0; i < path.size(); ++i)
    {
      col[2] = i*255/path.size();
      col[0] = 255-col[2];
      out.at<cv::Vec3b>(path[i]) = col;
    }

    // re-write black nodes just to be sure...
    for(int x = 0; x < im.cols; ++x)
    {
      for(int y = 0; y < im.rows; ++y)
      {
        if(!isFree(x,y))
          write(x,y,0,0,0,false);
      }
    }

    int dot = filename.find(".");
    std::string name = filename.substr(0, dot) + "_" + suffix + ".png";
    cv::imwrite(mazeFile(name), out);
    display("Solution", out);
  }
protected:
  cv::Mat im, out;
  std::string filename;
  std::vector<cv::Point> path;
  std::vector<std::string> windows;
};
}


#endif

