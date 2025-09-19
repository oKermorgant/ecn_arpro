#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const int n = 6;    // what we can find with n times the number n

enum class OP{ ADD, SUB, MUL, DIV };

// a structure to store a found result : numbers / operations / priority / result
struct Res
{
  int val;
  vector<OP> op_base;
  vector<int> order_base;
  vector<int> base;
  int score;

  Res(int v, const vector<OP> &_op, const vector<int> &_order, const vector<float> &_base)
    : val(v), op_base(_op), order_base(_order)
  {
    base.clear();
    std::transform(_base.begin(), _base.end(), std::back_inserter(base), [](auto v){return int(v);});

    // count the number of divisions as it is used to get the best result (with less divisions and less substractions)
    score = 3*count(op_base.begin(), op_base.end(),OP::DIV) + count(op_base.begin(), op_base.end(),OP::SUB);
  }

  void Print()
  {
    vector<string> str(base.size());
    for(int i=0;i<base.size();++i)
    {
      stringstream ss;
      ss << base[i];
      str[i] = ss.str();
    }

    string out;

    auto order = order_base;
    auto op = op_base;

    while(order.size())
    {
      auto o = order[0];
      bool parenthesis = false;

      // perform operation o
      switch(op[o])
      {
        case OP::ADD:
          str[o] = str[o] + "+" + str[o+1];
          if(o+1 < op.size())
          {
            if(op[o+1] == OP::MUL || op[o+1] == OP::DIV)
              parenthesis = true;
          }
          if(o != 0)
          {
            if(op[o-1] != OP::ADD)
              parenthesis = true;
          }
          break;
        case OP::SUB: // -
          str[o] = str[o] + "-" + str[o+1];
          if(o+1 < op.size())
          {
            if(op[o+1] == OP::MUL || op[o+1] == OP::DIV)
              parenthesis = true;
          }
          if(o != 0)
          {
            if(op[o-1] != OP::ADD)
              parenthesis = true;
          }
          break;
        case OP::MUL: // *
          str[o] =str[o] +"*"+ str[o+1];
          if(o != 0)
          {
            if(op[o-1] == OP::DIV)
              parenthesis = true;
          }
          break;
        case OP::DIV: // /
          str[o] = str[o] +"/"+ str[o+1] ;
          if(o != 0)
          {
            if(op[o-1] == OP::DIV)
              parenthesis = true;
          }
          if(o+1 < op.size())
          {
            if(op[o+1] == OP::MUL || op[o+1] == OP::DIV)
              parenthesis = true;
          }
          break;
      }

      // check for parenthesis
      if(parenthesis)
        str[o] = "(" + str[o] + ")";

      out = str[o];

      // erase useless element
      str.erase(str.begin()+o+1);

      // erase done operation
      op.erase(op.begin()+o);

      // modify order values
      order.erase(order.begin());
      for(auto &v: order)
        if(v > o)
          v--;
    }
    cout << val << " = " << out << '\n';// "  from " << PrintVec(base) << " with op " << PrintVec(op_base) << " and order " << PrintVec(order_base) << '\n';
  }
};


vector<Res> results;

vector<vector<vector<float>>> all_base;

void build_base(vector<float> prev, int depth = 0)
{
  if(depth == n-1 && prev.size() > 1)
  {
    all_base[n-prev.size()].push_back(prev);

  }
  else if(depth != n-1)
  {
    // continue with concatenation
    vector<float> new_prev = prev;
    new_prev.back() = 10*new_prev.back()+n;
    build_base(new_prev, depth+1);

    // continue without concatenation
    prev.push_back(n);
    build_base(prev, depth+1);
  }
}

void eval(vector<vector<float>> &base, vector<OP> op_base, int depth = 0)
{
  if(depth == op_base.size())  // all operations have been defined
  {
    // build operation priorities
    vector<int> order_base;
    for(int i=0;i<op_base.size();++i)
      order_base.push_back(i);

    // try all priorities for these operations
    do
    {
      for(auto nb: base)  // work on those numbers
      {
        auto order = order_base;
        auto op = op_base;
        //   cout << "Performing operation " << PrintVec(nb) << PrintVec(op) << PrintVec(order) << '\n';

        auto nb_or = nb;
        float res{};
        bool div0 = false;
        while(order.size())
        {

          //  cout << "  now at " << PrintVec(nb) << PrintVec(op) << PrintVec(order) << '\n';
          auto o = order[0];
          // perform operation o
          switch(op[o])
          {
            case OP::ADD: // +
              nb[o] = nb[o] + nb[o+1];
              break;
            case OP::SUB: // -
              nb[o] =  nb[o] - nb[o+1];
              break;
            case OP::MUL: // *
              nb[o] =  nb[o] * nb[o+1];
              break;
            case OP::DIV: // /
              if (nb[o+1] == 0)
                div0 = true;
              else
                nb[o] = nb[o] / nb[o+1];
              break;
          }

          // erase useless element
          nb.erase(nb.begin()+o+1);

          // erase done operation
          op.erase(op.begin()+o);

          // modify order values
          order.erase(order.begin());
          for(auto &v: order)
            if(v > o)
              v--;

          if(!div0)
            res = nb[o];
        }

        //cout << "  final at " << PrintVec(nb) << PrintVec(op) << PrintVec(order) << '\n';
        if(!div0 && res >= 0 && ((int) res) == res)
        {
          //    cout << "result is " << res << endl;
          results.push_back(Res((int) res, op_base, order_base, nb_or));
        }
      }
    } while(next_permutation(order_base.begin(), order_base.end()));
  }
  else                    // define next operation
  {
    for(auto op: {OP::ADD, OP::SUB, OP::MUL, OP::DIV})
    {
      op_base[depth] = op;
      eval(base, op_base, depth+1);
    }
  }

}

int main()
{
  results.clear();
  // obvious solution that messes with my method
  float obvious = n;
  for(int i=0;i<n;++i)
  {
    obvious = 10*obvious + n;
  }

  // 0 to n-1 concatenations
  all_base.resize(n-1);

  // build all base number combinations
  build_base({n}, 0);

  // find values reachables from any number of numbers
  int nb = n-1;
  for(auto &base: all_base)
  {
    vector<OP> op(nb--);
    eval(base, op);
    break;
  }

  int i;
  for(i=0;i<1000;++i)
  {
    vector<Res*> res_nb;
    for(auto &res: results)
    {
      if(res.val == i)
        res_nb.push_back(&res);
    }

    if(res_nb.size() != 0)
    {
      // we have a solution with single digits, find the "best" one (less divisions)
      if(res_nb.back()->order_base.size() == n-1)
      {
        sort(res_nb.begin(), res_nb.end(),[](Res* r1, Res* r2)
        {return r1->base.size() == n && r1->score < r2->score;});

        res_nb[0]->Print();
        cout << '\n';
      }
      else
        break;
    }
    else
      break;
  }
  cout << "Could not build " << i << '\n' << '\n';


  // also print all reached numbers
  vector<int> reached;
  for(auto &res: results)
  {
    if(find(reached.begin(), reached.end(), res.val) == reached.end())
      reached.push_back(res.val);
  }
  sort(reached.begin(), reached.end());
  cout << "Found " << reached.size() << " values" << '\n';
  for(auto v: reached)
    cout << v << ", ";
  cout << '\n';

}
