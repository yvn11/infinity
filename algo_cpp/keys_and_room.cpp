#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
    void visitRoom(vector<vector<int>>& rooms, unordered_set<int>& visited, int room_id) {
      if (visited.find(room_id) != visited.end()) {
        return;
      }

      visited.insert(room_id);
      for (int i = 0; i < rooms[room_id].size(); ++i) {
        visitRoom(rooms, visited, rooms[room_id][i]);
      }
    }
  
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
      unordered_set<int> visited;
      
      visitRoom(rooms, visited, 0);
      return visited.size() == rooms.size();
    }
};


int main() {
  Solution s;
  vector<vector<int>> v = {
    {1},{2},{3},{}
  };
  cout << s.canVisitAllRooms(v) << endl;
  return 0;
}
