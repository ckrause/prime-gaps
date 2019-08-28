#include <deque>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

void prime_gaps( int n )
{
  int prime = 1; // will store current prime number
  int gap = 1; // stores the gap to the next prime number
  std::deque<int> next_gaps = { 1 }; // list of next gap

  for ( int i = 1; i <= n; i++ )
  {
    prime += gap; // next prime is current prime plus gap
    gap = next_gaps.front(); // next gap is first gap from list

    next_gaps.pop_front(); // move next gap from front...
    next_gaps.push_back( gap ); // ...to end

    std::deque<int> updated_gaps;

    // make prime number copies of the list
    for ( int j = 0; j < prime; j++ )
    {
      std::copy( next_gaps.begin(), next_gaps.end(), std::back_inserter( updated_gaps ) );

      // since the original algorithm has factorial space complexity
      // we use the following check to stop generating more gaps when
      // we get close to the target size; not part of original algorithm!
      if ( updated_gaps.size() > 2 * n )
      {
        break;
      }

    }

    // remove illegal gaps from the list
    int sum = gap;
    for ( int j = 0; j < (int) updated_gaps.size(); j++ )
    {
      sum += updated_gaps[j];
      if ( sum % prime == 0 )
      {
        sum += updated_gaps[j + 1];
        updated_gaps[j] += updated_gaps[j + 1];
        updated_gaps.erase( updated_gaps.begin() + j + 1 );
      }
    }
    next_gaps = updated_gaps;

    std::cout << "Step " << i << ": prime=" << prime << "; gap=" << gap << std::endl;

  }
}

std::vector<int> load_ground_truth() {
	std::ifstream bfile("b001223.txt");
	if (!bfile.good())
		throw std::runtime_error("b-file not found");
	std::string l;
	std::vector<int> seq;
	int64_t expected_index = 1, index = 0, value = 0;
	while (std::getline(bfile, l)) {
		if (l.empty() || l[0] == '#')
			continue;
		std::stringstream ss(l);
		ss >> index >> value;
		if (index != expected_index || value < 1)
			throw std::runtime_error("error in b-file");
		seq.push_back(value);
		++expected_index;
	}
	return seq;
}

int main( int argc, char *argv[] )
{
	auto data = load_ground_truth();
	std::cout << "found: " << data.at(10) << std::endl;
//  prime_gaps( 10000 );
}
