#include <sudoku/grid.h>

#ifndef SUDOKU_WITH_OPENCV
void Grid::print() const
{
  constexpr auto line{" -----------"};

  std::cout << line << '\n';

  auto cell{cells.begin()};
  for(auto row = 0; row < 9; ++row)
  {
    std::cout << ' ';
    for(auto col = 0; col < 9; ++col)
    {
      std::cout << (cell++)->symbol();
      if(col == 2 || col == 5)
        std::cout << '|';
      else if(col == 8)
        std::cout << '\n';
    }
    if(row == 2 || row == 5 || row == 8)
      std::cout << line << '\n';
  }
  std::cout << std::endl;
}
void Grid::print(Grid::Cells::const_iterator candidate, bool canceled) const
{
  print();
}
#else
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace {
cv::Mat im;
const auto CV_WHITE{cv::Scalar(255, 255, 255)};
const auto CV_BLACK{cv::Scalar(0,0,0)};
const auto CV_OK{cv::Scalar(180,119,31)};
const auto CV_NOK{cv::Scalar(14,127,255)};
}

cv::Point toPixel(double row, double col)
{
  return cv::Point(static_cast<int>(50 + 100*col),
                   static_cast<int>(50 + 100*row));
}

void displayValue(uint row, uint col, uint v, const cv::Scalar &color)
{
  char text[12];
  sprintf(text, "%i", v);
  if(v < 6)
    cv::putText(im, text, toPixel(row + 0.25 , col + (v-0.5)*0.18), 0, 0.8, color, 2);
  else
    cv::putText(im, text, toPixel(row + 0.9 , col + (v-5.)*0.18), 0, 0.8, color, 2);
}

void Grid::print() const
{
  const static auto im_base = []()
  {
    auto im_base = cv::Mat(1000, 1000, CV_8UC3, CV_WHITE);
    for(uint coord = 0; coord < 10; ++coord)
    {
      const int thickness = (coord % 3) ? 1 : 2;
      cv::line(im_base, toPixel(0, coord), toPixel(9, coord),
               CV_BLACK, thickness);
      cv::line(im_base, toPixel(coord, 0), toPixel(coord, 9),
               CV_BLACK, thickness);
    }
    return im_base;
  }();

  im = im_base.clone();

  auto cell{cells.begin()};
  for(auto row = 0; row < 9; ++row)
  {
    for(auto col = 0; col < 9; ++col)
    {
      if(cell->digit())
      {
        char text[12];
        sprintf(text, "%i", cell->digit());
        cv::putText(im, text, toPixel(row + 0.65 , col + 0.3), 0, 1.5, CV_BLACK, 2);
      }

      // print available guesses
      for(auto guess: cell->candidates())
        displayValue(row, col, guess, CV_OK);

      // highlight dead-end
      const auto pruned{cell->pruned()};
      if(cell->candidates().size() == 0 && pruned.size() > 0)
      {
        const auto c1{toPixel(row+.05, col+.05)};
        const auto c2{toPixel(row+.95, col+.95)};
        cv::rectangle(im, c1, c2, CV_BLACK, -1);
      }

      // print pruned candidates
      for(auto guess: pruned)
        displayValue(row, col, guess, CV_NOK);

      cell++;
    }
  }
  cv::imshow("Sudoku", im);
  cv::waitKey(1);
}

void Grid::print(Grid::Cells::const_iterator candidate, bool canceled) const
{
  print();

  // add canceled or new candidate
  const auto d{std::distance(cells.begin(), candidate)};

  // retrieve row and col
  const auto row{d/9};
  const auto col{d % 9};
  const auto color = canceled ? CV_OK : CV_BLACK;
  if(canceled)
  {
    cv::line(im, toPixel(row+0.25, col+0.25), toPixel(row+0.75, col+0.75), color, 2);
    cv::line(im, toPixel(row+0.75, col+0.25), toPixel(row+0.25, col+0.75), color, 2);
  }
  else
    cv::circle(im, toPixel(row+0.5, col+0.5), 30, color, 2);

  cv::imshow("Sudoku", im);
  cv::waitKey(0);
}
#endif
