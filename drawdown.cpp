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

  std::vector<double> indices;

  int N;

  std::cout << "Enter the number of days:" << std::endl;
  std::cin >> N;
  std::vector<double> returnProfile = {1.5, -.5, -.5, -.5};
  std::vector<double> result(4);

  for(int i = 0; i < N; i++)
  {
    indices.push_back(*(returnProfile.begin() + randFunc(4)));
  }

  std::partial_sum(returnProfile.begin(), returnProfile.end(),  std::ostream_iterator<double>(std::cout, " "));

  for(std::vector<double>::iterator i = indices.begin() ; i != indices.end(); i++)
  {
    std::cout << *i << std::endl;
  }

  // for(std::vector<double>::iterator i = result.begin() ; i != result.end(); i++)
  // {
  //   std::cout << *i << std::endl;
  // }


  std::cout << "The value of the thing is: " << *(returnProfile.begin()+1) << std::endl;

  for(std::vector<double>::iterator i = returnProfile.begin() ; i != returnProfile.end(); i++)
  {
    std::cout << *i << std::endl;
  }

  return 0;
}
