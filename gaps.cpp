#include <deque>
#include <iostream>
#include <sstream>

void prime_gaps( int n )
{
  int prime = 1; // will store current prime number
  int gap = 1; // stores the gap to the next prime number
  std::deque<int> next_gaps = { 1 }; // list of next gap

  std::deque<char> survivors = { '-' };
  char s;
  size_t sl = 300;

  for ( int i = 1; i <= n; i++ )
  {
    prime += gap; // next prime is current prime plus gap
    gap = next_gaps.front(); // next gap is first gap from list

    next_gaps.pop_front(); // move next gap from front...
    next_gaps.push_back( gap ); // ...to end

    s = survivors.front();
    survivors.pop_front();
    survivors.push_back( s );

    std::deque<int> updated_gaps;
    std::deque<char> updated_survivors;

    // make prime number copies of the list
    for ( int j = 0; j < prime; j++ )
    {
      std::copy( next_gaps.begin(), next_gaps.end(), std::back_inserter( updated_gaps ) );
      std::copy( survivors.begin(), survivors.end(), std::back_inserter( updated_survivors ) );

      // since the original algorithm has factorial space complexity
      // we use the following check to stop generating more gaps when
      // we get close to the target size; not part of original algorithm!
      if ( updated_gaps.size() > 10 * n )
      {
        break;
      }

    }

    // TODO: update survivors here
    updated_survivors.pop_back();

    std::string df;

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
        if ( df.size() < sl ) df.push_back('X');
      }
      else if ( df.size() < sl ) df.push_back('-');

    }
    next_gaps = updated_gaps;

    survivors = updated_survivors;


    // print debug info
    std::string ss;
    for (char d : survivors)
    {
  	  ss.push_back(d);
  	  if (ss.size() == sl) break;
    }
//    std::cout << "Step " << i << ": prime=" << prime << "; gap=" << gap << ", survivors=" << ss.str() << std::endl;
    std::cout << "Step " << i << ": prime=" << prime << "; gap=" << gap << std::endl;
    std::cout << "expected: " << df << std::endl;
    std::cout << "     got: " << ss << std::endl << std::endl;

    // checks
    if ( survivors.size() != next_gaps.size() )
    {
//    	throw std::runtime_error("incorrect length of survivors: expected " + std::to_string( next_gaps.size() ) + ", got " + std::to_string( survivors.size() ) );

    }


  }
}

int main( int argc, char *argv[] )
{
  prime_gaps( 20 );
}
