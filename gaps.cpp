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
    if ( next_gaps.size() < n * 100 ) // <-- this check is only a performance optimization; not part of orginal algorithm
    {
      for ( int j = 0; j < prime; j++ )
      {
        std::copy( next_gaps.begin(), next_gaps.end(), std::back_inserter( updated_gaps ) );
      }
    }

    // remove illegal gaps from the list
    int sum = prime + gap;
    for ( int j = 0; j < (int) updated_gaps.size(); j++ )
    {
      sum = (sum + updated_gaps[j]) % prime;
      if ( sum == 0 )
      {
        sum = (sum + updated_gaps[j + 1]) % prime;
        updated_gaps[j] += updated_gaps[j + 1];
        updated_gaps.erase( updated_gaps.begin() + j + 1, updated_gaps.begin() + j + 2 );
      }
    }
    next_gaps = updated_gaps;

    std::cout << "Step " << i << ": prime=" << prime << "; gap=" << gap << std::endl;

  }
}

int main( int argc, char *argv[] )
{
  prime_gaps( 1000 );
}
