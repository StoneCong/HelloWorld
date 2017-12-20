#include "../../../include/txt_file.hpp"

inline long long get_distance(vector<long long>& p)
{
  return abs(p[0]) + abs(p[1]) + abs(p[2]);
}

inline tuple<long long, long long, long long> get_location(vector<long long>& p)
{
  return make_tuple(p[0], p[1], p[2]);
}

int main()
{
  vector<string> data = get_lines();
  vector<vector<long long>> particles;
  for (auto& e: data) {
    vector<long long> temp;
    for (auto n: get_signed_numbers(e)) {
      temp.push_back(n);
    }
    print_vector(temp);
    particles.push_back(temp);
  }

  // simulation runs for 50K times
  map<int, bool> colided;  // first: particle ID
  for (int i = 0; i < 50000; i++) {
    if (i % 1000 == 0) cout << i << endl;
    map<tuple<long long, long long, long long>, int> locations;
    for (int j = 0; j < particles.size(); j++) {
      if (colided.find(j) != colided.end()) continue;
      particles[j][3] += particles[j][6];
      particles[j][4] += particles[j][7];
      particles[j][5] += particles[j][8];
      particles[j][0] += particles[j][3];
      particles[j][1] += particles[j][4];
      particles[j][2] += particles[j][5];
      if (locations.find(get_location(particles[j])) != locations.end()) {
        colided[j] = true;
        colided[locations[get_location(particles[j])]] = true;
      }
      locations[get_location(particles[j])] = j;
    }
  }

  int index = 0;
  long long closest_distance = get_distance(particles[0]);
  for (int i = 0; i < particles.size(); i++) {
    if (get_distance(particles[i]) < closest_distance) {
      closest_distance = get_distance(particles[i]);
      index = i;
    }
  }
  cout << index << " distance = " << closest_distance << endl;
  cout << particles.size() - colided.size() << endl;
  return 0;
}
