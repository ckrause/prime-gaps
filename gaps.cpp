#include <deque>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

struct state
{
  int prime; // will store current prime number
  int gap; // stores the gap to the next prime number
  std::deque<int> next_gaps; // list of next gap
};

void next( state &s, int max )
{
  s.prime += s.gap; // next prime is current prime plus gap

  s.gap = s.next_gaps.front(); // next gap is first gap from list
  s.next_gaps.pop_front(); // move next gap from front...
  s.next_gaps.push_back( s.gap ); // ...to end

  std::deque<int> updated_gaps;

  // make prime number copies of the list
  for ( int j = 0; j < s.prime; j++ )
  {
    std::copy( s.next_gaps.begin(), s.next_gaps.end(), std::back_inserter( updated_gaps ) );

    // since the original algorithm has factorial space complexity
    // we use the following check to stop generating more gaps when
    // we get close to the target size; not part of original algorithm!
    if ( updated_gaps.size() > 2 * max )
    {
      break;
    }

  }

  // remove illegal gaps from the list
  int sum = s.gap;
  for ( int j = 0; j < (int) updated_gaps.size(); j++ )
  {
    sum += updated_gaps[j];
    if ( sum % s.prime == 0 )
    {
      sum += updated_gaps[j + 1];
      updated_gaps[j] += updated_gaps[j + 1];
      updated_gaps.erase( updated_gaps.begin() + j + 1 );
    }
  }
  s.next_gaps = updated_gaps;
}

std::vector<int> load_ground_truth()
{
  std::ifstream bfile( "b001223.txt" );
  if ( !bfile.good() ) throw std::runtime_error( "b-file not found" );
  std::string l;
  std::vector<int> seq;
  int64_t expected_index = 1, index = 0, value = 0;
  while ( std::getline( bfile, l ) )
  {
    if ( l.empty() || l[0] == '#' ) continue;
    std::stringstream ss( l );
    ss >> index >> value;
    if ( index != expected_index || value < 1 ) throw std::runtime_error( "error in b-file" );
    seq.push_back( value );
    ++expected_index;
  }
  return seq;
}

int main( int argc, char *argv[] )
{
  auto ground_truth = load_ground_truth();

  state s;
  s.prime = 1;
  s.gap = 1;
  s.next_gaps = { 1 };

  int max = 10000;
  for ( int i = 0; i < max; i++ )
  {
    next( s, max );
    std::cout << "Step " << i << ": prime=" << s.prime << "; gap=" << s.gap << std::endl;
    if ( s.gap != ground_truth.at( i ) )
    {
      throw std::runtime_error( "unexpected gap!" );
    }
  }
}
