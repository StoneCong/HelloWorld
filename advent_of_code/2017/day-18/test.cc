#include "../../../include/txt_file.hpp"

void dump_registers(map<string, long long>& registers)
{
  cout << "Registers: \n";
  for (auto e: registers) {
    cout << "register[" << e.first << "] = " << e.second << endl;
  }
  cout << endl;
}

void part_1()
{
  vector<string> data = get_lines();
  int cur = 0;
  map<string, long long> registers;
  int sound = 0;
  string last_inst = "start";
  for (;;) {
    if (cur < 0 || cur >= data.size()) {
      cout << "Invalid program! out of range for IP: " << cur << endl;
      break;
    }
    string inst = data[cur];
    vector<string> terms = split_line(inst, " ");
    vector<int> numbers = get_signed_numbers(inst);
    cout << last_inst << endl;
    dump_registers(registers);
    last_inst = inst;
    if (terms[0] == "snd") {
      sound = registers[terms[1]];
      cout << "setting sound to " << sound << endl;
      cur++;
      continue;
    }
    if (terms[0] == "rcv") {
      if (registers[terms[1]] != 0) {
        cout << "sound recovered: " << sound << endl;
        break;
      }
      cur++;
      continue;
    }
    if (numbers.size() == 0) {
      numbers.push_back(registers[terms[2]]);
    }
    if (terms[0] == "jgz") {
      if ((numbers.size() == 2 && numbers[0] > 0) ||
          (numbers.size() == 1 && registers[terms[1]] > 0)) {
        cur += numbers.back();
      } else {
        cur++;
      }
      continue;
    }
    if (terms[0] == "set") {
      registers[terms[1]] = numbers[0];
    }
    if (terms[0] == "add") {
      registers[terms[1]] += numbers[0];
    }
    if (terms[0] == "mul") {
      registers[terms[1]] *= numbers[0];
    }
    if (terms[0] == "mod") {
      registers[terms[1]] %= numbers[0];
    }
    cur++;
  }
}

void worker(int process_id, vector<queue<int>>& queues, mutex& m)
{
  vector<string> data = get_lines();
  int cur = 0;
  map<string, long long> registers;
  int sound = 0;
  string last_inst = "start";
  registers["p"] = process_id;
  int send_count = 0;
  printf("Starting: %d\n", process_id);
  for (;;) {
    if (cur < 0 || cur >= data.size()) {
      cout << "Invalid program! out of range for IP: " << cur << endl;
      break;
    }
    string inst = data[cur];
    vector<string> terms = split_line(inst, " ");
    vector<int> numbers = get_signed_numbers(inst);
    // lock so we can group the print together for debugging
    m.lock();
    cout << process_id << ": " << last_inst << endl;
    dump_registers(registers);
    m.unlock();
    last_inst = inst;
    if (terms[0] == "snd") {
      sound = registers[terms[1]];
      cur++;
      send_count++;
      printf("process %d: sending %d (total = %d)\n", process_id, sound, send_count);
      m.lock();
      queues[(process_id + 1) % 2].push(sound);
      m.unlock();
      continue;
    }
    if (terms[0] == "rcv") {
      // cout << "receiving sound with register: " << terms[1] << " (" << registers[terms[1]] << ")" << endl;
      for (;;) {
        m.lock();
        if (queues[process_id].size()) {
          registers[terms[1]] = queues[process_id].front();
          queues[process_id].pop();
          m.unlock();
          break;
        }
        m.unlock();
      }
      cur++;
      continue;
    }
    if (numbers.size() == 0) {
      numbers.push_back(registers[terms[2]]);
    }
    if (terms[0] == "jgz") {
      if ((numbers.size() == 2 && numbers[0] > 0) ||
          (numbers.size() == 1 && registers[terms[1]] > 0)) {
        cur += numbers.back();
      } else {
        cur++;
      }
      continue;
    }
    if (terms[0] == "set") {
      registers[terms[1]] = numbers[0];
    }
    if (terms[0] == "add") {
      registers[terms[1]] += numbers[0];
    }
    if (terms[0] == "mul") {
      registers[terms[1]] *= numbers[0];
    }
    if (terms[0] == "mod") {
      registers[terms[1]] %= numbers[0];
    }
    cur++;
  }
}

int main()
{
  vector<thread> threads;
  vector<queue<int>> queues;
  queue<int> temp;
  queues.push_back(temp);
  queues.push_back(temp);
  mutex m;
  for (int i = 0; i < 2; i++) {
    threads.push_back(thread(worker, i, ref(queues), ref(m)));
  }
  for (auto& t: threads) {
    t.join();
  }
  return 0;
}
