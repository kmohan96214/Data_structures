#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void display()
  {
      for(int i=1;i<data_.size();i++)
        cout << data_[i] << " ";
      cout << std::endl;
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n+1);
    data_[0]=0;
    for(int i = 1; i <= n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    //for (int i = 0; i < data_.size(); ++i)
    //  for (int j = i + 1; j < data_.size(); ++j) {
    //    if (data_[i] > data_[j]) {
    //      swap(data_[i], data_[j]);
    //     swaps_.push_back(make_pair(i, j));
    //    }
    //  }
    makeHeap();

  }

  void makeHeap()
  {
        for(int i=data_.size()/2;i>0;i--)
            siftDown(i);
  }

  void siftDown(int i)
  {
      int minindex = i;
      int leftchild = 2*i,rightchild=2*i+1;
      if(leftchild < data_.size() && data_[leftchild]<data_[minindex])
        minindex = leftchild;
      if(rightchild < data_.size() && data_[rightchild]<data_[minindex])
        minindex = rightchild;
      if(i!=minindex){
        swap(data_[i],data_[minindex]);
        swaps_.push_back(make_pair(data_[i],data_[minindex]));
        siftDown(minindex);
      }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    //makeHeap();
    WriteResponse();
    //display();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  freopen("input.in","r",stdin);
  heap_builder.Solve();
  return 0;
}
