#include "drawdown.cpp"

int main()
{
  /* initialize random seed: */
  srand (time(NULL));

  const int n_Days = 22;
  const int n_Itr = 1000000;

  // std::cout << "Enter the number of days:" << std::endl;
  // std::cin >> n_Days;


  std::string file;
  std::vector<double> eq1, allDrawdowns;

  for(int i = 1; i < 19; i++)
  {
    file = inputFilename(i);
    std::ifstream f(file);
    std::string num;
    std::vector<double> returnProfile;

    while(getline(f, num, '\n'))
    {
      returnProfile.push_back(std::stod(num));
    }

    runSimulation(returnProfile, eq1, allDrawdowns, n_Itr, n_Days);

    sortDescending(allDrawdowns);

    saveData(outputFilename(i), allDrawdowns);
  }




  // runSimulation(returnProfile, eq1, allDrawdowns, n_Itr, n_Days);

  // std::cout << "The simulation worst case drawdown is: " << *std::max_element(allDrawdowns.begin(), allDrawdowns.end()) << std::endl;

  // Sort the drawdowns in descending order
  // sortDescending(allDrawdowns);

  // Save the data to file
  // saveData("Data/allDrawdowns.txt", allDrawdowns);

  // std::cout << "The theoretical worst case drawdown is:" << worstPossible(returnProfile, n_Days) << std::endl;

  //////////////////////////////////PLOTS/////////////////////////////////
  // plotCurves(eq1, "Figures/basic.jpg");

  return 0;
}
