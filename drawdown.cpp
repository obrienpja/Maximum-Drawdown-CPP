#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <functional>
#include <string>

// From plotting script
#define _USE_MATH_DEFINES
#include <cmath>
#include "../matplotlib-cpp/matplotlibcpp.h"

namespace plt = matplotlibcpp;

int randFunc(int num)
{
  return rand() % num;
}

std::vector<int> peaks(std::vector<double> equity)
{
  std::vector<int> inds;
  for(int i = 1; i < equity.size() - 1; i++)
  {
    if((equity.at(i-1) < equity.at(i) && (equity.at(i) > equity.at(i+1))))
      inds.push_back(i);
  }
  return inds;
}

void printVector(std::vector<int> vec)
{
  for(std::vector<int>::iterator i = vec.begin(); i != vec.end(); i++)
    std::cout << *i << std::endl;
}

void printVector(std::vector<double> vec)
{
  for(std::vector<double>::iterator i = vec.begin(); i != vec.end(); i++)
    std::cout << *i << std::endl;
}

std::vector<int> increasingPeaks(std::vector<double> equity)
{
  std::vector<int> peakIndices = peaks(equity);
  std::vector<int> increasingPeakIndices;
  int maxVal = -10000;

  if((equity.at(0) - equity.at(1)) > 0)
  {
    increasingPeakIndices.push_back(0);
    maxVal = equity.at(0);
  }

  for(std::vector<int>::iterator i = peakIndices.begin(); i != peakIndices.end(); i++)
  {
    if(equity.at(*i) > maxVal)
    {
      increasingPeakIndices.push_back(*i);
      maxVal = equity.at(*i);
    }
  }

  return increasingPeakIndices;
}


// std::vector<double> equityCurve(int numDays)
// {}

int main()
{
  /* initialize random seed: */
  srand (time(NULL));

  // std::string filename;
  //
  // std::cout << "Enter .csv file name: " << std::endl;
  // std::cin >> filename;
  //
  // std::cout << "The file name is: " << filename << std::endl;

  std::vector<double> equityCurve;

  int N = 22;

  // std::cout << "Enter the number of days:" << std::endl;
  // std::cin >> N;
  std::vector<double> returnProfile = {1.5, -.5, -.5, -.5};
  std::vector<double> result(4);

  std::cout << "The equity curve is: " << std::endl;
  std::cout << "--------------------------" << std::endl;

  double total = 0;

  // Generates the equity curve
  for(int i = 0; i < N; i++)
  {
    total += *(returnProfile.begin() + randFunc(returnProfile.size()));
    equityCurve.push_back(total);
  }

  // std::partial_sum(returnProfile.begin(), returnProfile.end(),  std::ostream_iterator<double>(std::cout, " "));

  for(std::vector<double>::iterator i = equityCurve.begin() ; i != equityCurve.end(); i++)
  {
    std::cout << *i << std::endl;
  }


  std::cout << "The peaks are: " << std::endl;
  printVector(peaks(equityCurve));

  std::cout << "The increasing peaks are: " << std::endl;
  printVector(increasingPeaks(equityCurve));

  // for(std::vector<double>::iterator i = result.begin() ; i != result.end(); i++)
  // {
  //   std::cout << *i << std::endl;
  // }


  // std::cout << "The value of the thing is: " << *(returnProfile.begin()+1) << std::endl;

  // for(std::vector<double>::iterator i = returnProfile.begin() ; i != returnProfile.end(); i++)
  // {
  //   std::cout << *i << std::endl;
  // }

  // Prepare data.
	int n = equityCurve.size();
	std::vector<double> x(n), y(n);
	for(int i=0; i<n; ++i) {
		x.at(i) = i;
		y.at(i) = 2*log(i);
	}

	// Plot line from given x and y data. Color is selected automatically.
	plt::plot(x, equityCurve, "bo");

	// Set x-axis to interval [0,1000000]
	plt::xlim(0, n);

	// Add graph title
	plt::title("Equity Curve");
	// Enable legend.
	plt::legend();
	// save figure
	plt::save("./basic.jpg");

  return 0;
}
