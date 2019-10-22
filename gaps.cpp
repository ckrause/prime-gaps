#include <chrono>
#include <deque>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

struct state
{
  int prime; // will store current prime number
  std::deque<int> gaps; // list of next gap
};

void print_list( std::deque<int> &l, int max_print )
{
  std::cout << "<";
  for ( size_t i = 0; i < l.size(); i++ )
  {
    int g = l[i];
    std::cout << "\033[0;" << (((g / 2) % 7) + 31) << "m" << g << "\033[0m";
    if ( i + 1 < l.size() ) std::cout << ",";
    if ( i > max_print ) break;
  }
  if ( l.size() > max_print ) std::cout << "...";
  std::cout << ">";
}

void next( state &s, int max )
{
  // checks
  int sum = 0;
  for ( int j = 0; j < (int) s.gaps.size(); j++ )
  {
    sum += s.gaps[j];
    assert( sum <= j + 1 );
  }

  // rotate
  int gap = 0;
  while ( gap == 0 )
  {
    gap = s.gaps.front(); // next gap is first gap from list
    s.gaps.pop_front(); // move next gap from front...
    s.gaps.push_back( gap ); // ...to end
  }

  std::deque<int> updated_gaps;

  // make prime number copies of the list
  for ( int j = 0; j < s.prime; j++ )
  {
    std::copy( s.gaps.begin(), s.gaps.end(), std::back_inserter( updated_gaps ) );

    // since the original algorithm has factorial space complexity
    // we use the following check to stop generating more gaps when
    // we get close to the target size; not part of original algorithm!
    if ( updated_gaps.size() > 30 * max + 100 )
    {
      break;
    }

  }

  // remove illegal gaps from the list
  sum = gap;
  for ( int j = 0; j < (int) updated_gaps.size(); j++ )
  {
    sum += updated_gaps[j];
    if ( sum % s.prime == 0 )
    {
      int k = j + 1;
      while ( k < updated_gaps.size() && updated_gaps[k] == 0 )
        k++;
      sum += updated_gaps[k];
      updated_gaps[k] += updated_gaps[j];
      updated_gaps[j] = 0;
      j = k;
    }
  }
  s.gaps = updated_gaps;
  s.prime += gap; // next prime is current prime plus gap
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
  s.prime = 2;
  s.gaps = { 1 };

  int max_val = 10000;
  int max_print = 50;
  if ( argc > 1 )
  {
    max_val = std::stoi( argv[1] );
  }

  for ( int n = 0; n < max_val; n++ )
  {
    int p = s.prime;
    std::cout << "n=" << n << ": p=" << p << "; G=";
    print_list( s.gaps, max_print );
    std::cout << std::endl;
    int f;
    for ( f = 0; f < s.gaps.size(); f++ )
      if ( s.gaps.at( f ) != 0 ) break;
    if ( s.gaps[f] != ground_truth.at( n ) )
    {
      throw std::runtime_error( "unexpected gap!" );
    }
    next( s, max_val );

    // std::this_thread::sleep_for( std::chrono::milliseconds( 500 / (n + 1) + 50 ) );
  }
}
