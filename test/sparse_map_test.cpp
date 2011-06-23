#include <iostream>
#include "../lib/sparse_map.hpp"

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

  dag::sparse_map<uint64_t> dm(n, vmax / 2 * n + n);
  uint64_t size = 0;
  uint64_t one_num = 0;
  vector<uint64_t> results;
  vector<uint64_t> bv;
  vector<uint64_t> ranks;
  for (int i = 0; i < n; ++i){
    int dif = rand() % vmax;
    size += dif;
    dm.push_back(size, size);
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

  cout << " alloc_byte_num:" << dm.get_alloc_byte_num() << endl; 

  for (size_t i = 0; i < results.size(); ++i){
    if (results[i] != dm.get_pos(i)){
      cout << "Error dm.select i=" << i 
           << " results[i]=" << results[i] 
           << " dm.get_pos(i)=" << dm.get_pos(i) << endl;  
    }
  }

  size_t i = 0;
  dag::sparse_map<uint64_t>::const_iterator end = dm.end();
  for (dag::sparse_map<uint64_t>::const_iterator it = dm.begin(); it != end; ++it, ++i){
    pair<uint64_t, uint64_t> ret = *it;
    if (results[i] != ret.first){
      cout << "Error dm.iterator i=" << i 
           << " results[i]=" << results[i] 
           << " dm*(i).first=" << ret.first << endl;  
    }
  }

  for (size_t i = 0; i < bv.size(); ++i){
    if (bv[i] != dm.exist(i)){
      cout << "Error dm.exist i =" << i
           << " bv[i]=" << bv[i]
           << " dm.exist(i)=" << dm.exist(i) << endl;
    }
  }
  
  return 0;
}
