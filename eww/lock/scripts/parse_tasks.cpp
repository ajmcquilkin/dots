#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void printNthElement(const std::vector<std::vector<std::string>> &vec, int n, int maxRows)
{
  int currRow = 0;

  for (auto row : vec)
  {
    if (currRow >= maxRows)
    {
      std::cout << " "
                << "+ "
                << vec.size() - maxRows << " more" << std::endl;
      return;
    }

    try
    {
      std::string element = row.at(n);

      if (element.size())
      {
        std::cout << " " << row.at(n) << std::endl;
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }

    ++currRow;
  }
}

int main(int argc, char *argv[])
{
  char delim = ',';
  std::vector<std::vector<std::string>> words;
  int currLine = 0;

  if (argc < 2 + 1)
  {
    std::cerr << "Not enough arguments passed (col, maxRows)" << std::endl;
    return -1;
  }

  int col = -1;
  int maxRows = -1;

  try
  {
    col = std::stoi(argv[1]);
    maxRows = std::stoi(argv[2]);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Unable to parse one or more arguments" << std::endl;
    std::cerr << e.what() << std::endl;
    return -2;
  }

  for (std::string line; std::getline(std::cin, line);)
  {
    std::vector<std::string> lineWords;
    std::stringstream sstream(line);
    std::string word;

    while (std::getline(sstream, word, delim))
    {
      lineWords.push_back(word);
    }

    words.push_back(lineWords);
    ++currLine;
  }

  printNthElement(words, col, 4);

  return EXIT_SUCCESS;
}
