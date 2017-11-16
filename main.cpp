#include "drawdown.cpp"

int main()
{
  /* initialize random seed: */
  srand (time(NULL));



  // std::cout << "Enter the number of days:" << std::endl;
  // std::cin >> n_Days;



  std::vector<double> eq1, allDrawdowns;
  std::vector<std::thread> th;
  int n_threads = 18;

  for(int i = 1; i < (n_threads+1); i++)
  {
    th.push_back(std::thread(runAndSave, i));
    // runAndSave(i);
  }

  for(auto &t : th)
  {
    t.join();
  }

  // std::cout << "The theoretical worst case drawdown is:" << worstPossible(returnProfile, n_Days) << std::endl;

  //////////////////////////////////PLOTS/////////////////////////////////
  // plotCurves(eq1, "Figures/basic.jpg");

  return 0;
}
