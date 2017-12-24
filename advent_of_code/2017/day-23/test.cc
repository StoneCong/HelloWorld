#include "../../../include/txt_file.hpp"

void part_1()
{
  vector<string> data = get_lines();
  map<string, int> registers;

  int cur = 0;
  int count = 0;
  for(;;) {
    if (cur < 0 || cur >= data.size()) break;
    string instr = data[cur];
    vector<string> terms = split_line(instr, " ");
    vector<int> numbers = get_signed_numbers(instr);
    if (terms[0] == "jnz") {
      if (numbers.size() == 1) {
        int num = registers[terms[1]];
        if (num == 0) {
    	  cur++;
        } else {
	  cur += numbers[0];
        }
      } else {
	if (numbers[0] == 0) {
	  cur++;
	} else {
	  cur += numbers[1];
	}
      }
      continue;
    }
    if (numbers.size() == 0) {
      numbers.push_back(registers[terms[2]]);
    }
    if (terms[0] == "set") {
      registers[terms[1]] = numbers[0];
      cur++;
      continue;
    }
    if (terms[0] == "sub") {
      registers[terms[1]] -= numbers[0];
      cur++;
      continue;
    }
    if (terms[0] == "mul") {
      registers[terms[1]] *= numbers[0];
      cur++;
      count++;
      continue;
    }
  }
  cout << count << endl;
}

void part_2()
{
  /*
      b = 81;   
 L2:  c = b;
      if (a) goto L4; 
      goto 8;
 L4:  b = b* 100;       // mul b 100
      b = b + 100000;   // sub b -100000
      c = b;            // set c b
      c += 17000;       // sub c -17000
 L8:  f = 1;            // set f 1
      d = 2;            // set d 2
 L10: e = 2;            // set e 2
 L11: g = d;            // set g d
      g *= e;           // mul g e
      g -= b;           // sub g b
      if (g) goto L2;   // jnz g 2
      f = 0;            // set f 0
      e += 1;           // sub e -1
      g = e;            // set g e
      g -= b;           // sub g b
      if (g) goto L11;  // jnz g -8
      d += 1;           // sub d -1
      g = d;            // set g d
      g -= b;           // sub g b
      if (g) goto L10;  // jnz g -13
      if (f) goto L26;  // jnz f 2
 L25: h += 1;           // sub h -1
      g = b;            // set g b
      g -= c;           // sub g c
      if (g) goto L30;  // jnz g 2
      goto Done;        // jnz 1 3
 L30: b += 17;          // sub b -17
      goto L8;           // jnz 1 -23
 Done: 
  */
  
  int h = 0;
  int a = 1;
  int b = 81 * 100 + 100000;
  int c = 81 * 100 + 100000 + 17000;
  int d = 0;
  int e = 0;
  int f = 0;
  int g = 0;
  
  for (;;) {
      f = 1;            // set f 1
      d = 2;            // set d 2
      do {
	e = 2;            // set e 2
        do {
          g = d;            // set g d
          g *= e;           // mul g e
          g -= b;           // sub g b
          if (g) {
            c = b;
            b = b* 100;       // mul b 100
            b = b + 100000;   // sub b -100000
            c = b;            // set c b
            c += 17000;       // sub c -17000
            f = 1;            // set f 1
            d = 2;            // set d 2
            e = 2;            // set e 2
            g = d;            // set g d
            g *= e;           // mul g e
            g -= b;           // sub g b
  	  }
          f = 0;            // set f 0
          e += 1;           // sub e -1
          g = e;            // set g e
          g -= b;           // sub g b
        } while (g);
        d += 1;           // sub d -1
        g = d;            // set g d
        g -= b;           // sub g b
      } while  (g);
      if (!f) {
        h += 1;
      }
      g = b;            // set g b
      g -= c;           // sub g c
      if (!g) break;
      b += 17;          // sub b -17
  }
  
  cout << h << endl;
}

int main()
{
  part_2();
  return 0;
}
