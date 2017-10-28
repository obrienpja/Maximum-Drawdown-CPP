#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <functional>
#include <string>

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

// std::vector<double> equityCurve(int numDays)
// {}

int main()
{
  /* initialize random seed: */
  srand (time(NULL));

  std::string filename;

  std::cout << "Enter .csv file name: " << std::endl;
  std::cin >> filename;

  std::cout << "The file name is: " << filename << std::endl;

  std::vector<double> equityCurve;

  int N = 8;

  // std::cout << "Enter the number of days:" << std::endl;
  // std::cin >> N;
  std::vector<double> returnProfile = {1.5, -.5, -.5, -.5};
  std::vector<double> result(4);

  std::cout << "The equity curve is: " << std::endl;
  std::cout << "--------------------------" << std::endl;

  double total = 0;

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

  // for(std::vector<double>::iterator i = result.begin() ; i != result.end(); i++)
  // {
  //   std::cout << *i << std::endl;
  // }


  // std::cout << "The value of the thing is: " << *(returnProfile.begin()+1) << std::endl;

  // for(std::vector<double>::iterator i = returnProfile.begin() ; i != returnProfile.end(); i++)
  // {
  //   std::cout << *i << std::endl;
  // }

  return 0;
}
