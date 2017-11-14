#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <functional>
#include <string>
#include <algorithm>

// From plotting script
#define _USE_MATH_DEFINES
#include <cmath>
#include "../matplotlib-cpp/matplotlibcpp.h"
namespace plt = matplotlibcpp;


int randFunc(int num)
{
  return rand() % num;
}


std::vector<double> equityCurve(std::vector<double> returnProf, int Num)
{
  std::vector<double> equity;
  double total = 0;

  // Generates the equity curve
  for(int i = 0; i < Num; i++)
  {
    total += *(returnProf.begin() + randFunc(returnProf.size()));
    equity.push_back(total);
  }

  return equity;
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

  std::cout << "The increasing peaks are: " << std::endl;
  printVector(increasingPeakIndices);

  return increasingPeakIndices;
}


std::vector<double> negVector(std::vector<double> equity)
{
  std::vector<double> nVector;

  for(std::vector<double>::iterator i = equity.begin(); i != equity.end(); i++)
  {
    nVector.push_back(-(*i));
  }

  return nVector;
}


std::vector<int> valleys(std::vector<double> equity)
{
  return peaks(negVector(equity));
}

std::vector<int> inBetweenValleys(std::vector<int>::iterator incrPeaksInd, std::vector<int> theValleys)
{
  std::vector<int> inValleys;

  std::cout << "The in between valleys are: " << std::endl;

  for(std::vector<int>::iterator j = theValleys.begin(); j != theValleys.end(); j++)
  {
    if((*(incrPeaksInd) < *j) && (*j < *(incrPeaksInd + 1)))
      inValleys.push_back(*j);
  }

  printVector(inValleys);

  return inValleys;
}

std::vector<double> pullValues(std::vector<double> equity, std::vector<int> vals)
{
  std::vector<double> pulledValues;

  for(std::vector<int>::iterator i = vals.begin(); i != vals.end(); i++)
    pulledValues.push_back(equity.at(*i));

  return pulledValues;
}

double findMaxDrawdown(std::vector<double> equity)
{
  std::vector<int> iPeaks = increasingPeaks(equity);
  std::vector<int> allValleys = valleys(equity);
  std::vector<double> drawList;

  std::cout << "The increasing peaks are: " << std::endl;
  printVector(iPeaks);

  if(iPeaks.size() == 0)
    return 0;
  else if(iPeaks.size() == 1)
  {
    return equity.at(*iPeaks.begin()) - *std::min_element(equity.begin() + *iPeaks.begin(), equity.end());
  }
  else
  {
    for(std::vector<int>::iterator i = iPeaks.begin(); i != (iPeaks.end() - 1); i++)
    {
      std::vector<double> selectedValleys = pullValues(equity, inBetweenValleys(i, allValleys));
      drawList.push_back(equity.at(*i) - *(std::min_element(selectedValleys.begin(), selectedValleys.end())));
    }


    std::vector<double> sliced(equity.begin() + iPeaks.back(), equity.end());
    drawList.push_back(equity.at(iPeaks.back()) - *std::min_element(sliced.begin(), sliced.end()));

    std::cout << "The drawdown list is: " << std::endl;

    printVector(drawList);

    return *std::max_element(drawList.begin(), drawList.end());
  }
}


void plotCurves(std::vector<double> equity, std::string filename)
{
// Prepare data.
int n = equity.size();
std::vector<double> x(n);
for(int i=0; i<n; ++i)
  x.at(i) = i;

// Plot line from given x and y data. Color is selected automatically.
plt::plot(x, equity, "bo");

// Set x-axis to interval [0,1000000]
plt::xlim(0, n);

// Add graph title
plt::title("Equity Curve");
// Enable legend.
plt::legend();
// save figure
plt::save(filename);
// plt::show();
}
