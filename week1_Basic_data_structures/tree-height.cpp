#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;
class Node;
int heightTree(vector<Node> ,int );

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  //freopen("test.in", "r", stdin);
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  int root;
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if(parent_index==-1)
        root = child_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
/*
  int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }
*/
  int maxHeight = heightTree(nodes,root);
  std::cout << maxHeight << std::endl;
  return 0;
}

int heightTree(vector<Node> nodes,int root)
{
    queue<Node> q;
    int height=0;
    if(nodes[root].children.empty() && q.empty())
        return height;

    q.push(nodes[root]);
    while(1)
    {
        int node_count = q.size();
        if(node_count==0)
            return height;
        height++;
        while(node_count>0){
            Node temp = q.front();
            q.pop();
            //cout << "height:" << height << " node :" << temp.key << endl;
            int l = temp.children.size();
            for(int i=0;i<l;i++)
                q.push(*temp.children[i]);
            node_count--;
        }
    }
    return height;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
