#include <deque>
#include <iostream>

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
      // we get close to the target size; not part of orginal algorithm!
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

int main( int argc, char *argv[] )
{
  prime_gaps( 10000 );
}
