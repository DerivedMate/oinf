#include <stdio.h>
#include <iostream>
#include <vector>

typedef int elT;

struct Pair {
  elT a;
  elT b;

  Pair(elT a, elT b) {
    this->a = a; 
    this->b = b;
  }

  bool isRedundant() {
    return this->a < 1 || this->b < 1;
  }

  bool operator==(Pair& other) {
    return other.a == this -> a && other.b == this->b;
  }
};

struct Trans {
  Pair *tc, *tv, *th, *tvh;

  Trans(elT x0, elT y0, elT x1, elT y1) {
    this->tc  = new Pair(x1    , y1    );
    this->tv  = new Pair(x0 - 1, y1    );
    this->th  = new Pair(x1    , y0 - 1);
    this->tvh = new Pair(x0 - 1, y0 - 1);
  }

  ~Trans() {
    delete this->tc ;
    delete this->tv ;
    delete this->th ;
    delete this->tvh;
  }
};

/**
 * A transformation descriptor
 * T[(x0, y0), (x1, y1)] 
 *  : y0, y1 `in` {1..n}
 *  , x0, x1 `in` {1..m}
*/
struct TransInp
{
  elT x0;
  elT y0;

  elT x1;
  elT y1;

  TransInp(elT x0, elT y0, elT x1, elT y1) {
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
  }

  bool isItsOwnInverse() {
    bool t = this->x0 == 1 && this->y0 == 1;
    return t;
  }

  Trans* inverse() {
    return 
      new Trans( this->x0
               , this->y0
               , this->x1
               , this->y1 );
  }
};

void insertPair(std::vector<Pair> *ts, Pair *t) {
  bool done = false;

  for(auto j = ts->begin(); j < ts->end() && !done; ) {
    if(*j == *t) { // Remove as t^2 = id
      ts->erase(j);
      done = true;
    } else {
      j++;
    }
  }

  if(!done && !t->isRedundant()) {
    ts->push_back(*t);
  }
}

int main() {
  std::vector<Pair> ts;
  int n, m, q;
  std::cin >> n >> m >> q;

  for (int i = 0; i < q; i++) {
    elT x0, y0, x1, y1;
    std::cin >> y0 >> x0 >> y1 >> x1;

    TransInp inp(x0, y0, x1, y1);

    if(inp.isItsOwnInverse()) {
      Pair* t = new Pair(x1, y1);
      insertPair(&ts, t);
    } else {
      Trans t = Trans(x0, y0, x1, y1);
      insertPair(&ts, t.tc );
      insertPair(&ts, t.th );
      insertPair(&ts, t.tv );
      insertPair(&ts, t.tvh);
    }

    std::cout << ts.size() << std::endl;
  }

  return 0;
}