#include <iostream>
#include "../lib/sparse_set.hpp"

using namespace std;

int main(int argc, char* argv[]){
  int n = 10000;
  int vmax = 100;
  if (argc >= 2){
    n = atoi(argv[1]);
  }
  if (argc >= 3){
    vmax = atoi(argv[2]);
  }

  cout << "n=" << n << " vmax=" << vmax << endl;

  dag::sparse_set ds(n, vmax / 2 * n + n);
  uint64_t size = 0;
  uint64_t one_num = 0;
  vector<uint64_t> results;
  vector<uint64_t> bv;
  vector<uint64_t> ranks;
  for (int i = 0; i < n; ++i){
    int dif = rand() % vmax;
    size += dif;
    ds.push_back(size);
    results.push_back(size);
    for (int j = 0; j < dif; ++j){
      bv.push_back(0);
      ranks.push_back(one_num);
    }
    ranks.push_back(one_num);
    bv.push_back(1);
    one_num++;
    ++size;
  }

  cout << " alloc_byte_num:" << ds.get_alloc_byte_num() << endl; 

  for (size_t i = 0; i < results.size(); ++i){
    if (results[i] != ds[i]){
      cout << "Error ds.select i=" << i 
           << " results[i]=" << results[i] 
           << " ds.select(i)=" << ds[i] << endl;  
    }
  }

  size_t i = 0;
  dag::sparse_set::const_iterator end = ds.end();
  for (dag::sparse_set::const_iterator it = ds.begin(); it != end; ++it, ++i){
    if (results[i] != *it){
      cout << "Error ds.iterator i=" << i 
           << " results[i]=" << results[i] 
           << " ds.select(i)=" << *it << endl;  
    }
  }

  for (size_t i = 0; i < bv.size(); ++i){
    if (bv[i] != ds.exist(i)){
      cout << "Error ds.get_bit i =" << i
           << " bv[i]=" << bv[i]
           << " ds.get_bit(i)=" << ds.exist(i) << endl;
    }

    if (ranks[i] != ds.rank(i)){
      cout << "Error ds.rank i =" << i
           << " ranks[i]=" << ranks[i]
           << " ds.rank(i)=" << ds.rank(i) << endl;
    }
  }
  
  return 0;
}
