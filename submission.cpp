#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>
#include <climits>
#include <cmath>
#include <bits/stdc++.h>
#include <numeric>
using namespace std;
#define inf 9999

// Name:
// PID:

///////////////////////////////////////////////////////
//////////////       QUESTION 1 HERE   ////////////////
///////////////////////////////////////////////////////
vector<vector<int>> mySavings(vector<vector<int>>S){


    vector<vector<int> > answer(S.size(),vector<int>(S[0].size(),0));
    for(int x=0;x<S.size();x++)
    {
        for(int y=x+1;y<S[0].size();y++)
        {
            answer[x][y]=S[0][x]+S[0][y]-S[x][y];
        }
    }

    return answer;
  /*
    TODO:

    Write an algorithm that calculates the Savings Heuristic Matrix from the shortest path graph.

    Input:
      vector<vector<int>> S: the shortest path matrix

    Return:
      vector<vector<int>>: the Savings Heuristic Matrix

  */

}

vector<pair<int,int>> ascendingOrder(vector<vector<int>> savings)
{
    vector<pair<int,int>> answer;
    cout<<"This part does work?"<<endl;
    for(int x=0;x<savings.size();x++)
    {
        for(int y=0;y<savings[0].size();y++)
        {
            if(savings[x][y]!=0)
            {
                cout<<x<<","<<y<<endl;
                answer.push_back(make_pair(x,y));
            }
        }
       // cout<<"Here"<<endl;
    }
    cout<<"This part workytuts"<<endl;
     vector<pair<int,int>> answer1=answer;
    for(int x=0;x<answer.size();x++)
    {
        for(int y=x+1;y<answer.size();y++)
        {
            if(savings[answer[x].first][answer[x].second]<savings[answer[x].first][answer[x].second])
            {
                pair<int,int> temp=make_pair(answer[x].first,answer[x].second);
                answer[x]=answer[y];
                answer[y]=temp;
            }
        }
    }
    return answer;
}

bool contains(vector<int> a, int b)
{
    for(int x=0;x<a.size();x++)
    {
        if(a[x]==b)
        {
            return true;
        }
    }
    return false; 
}
vector<int> maxLength(vector<vector<int>> k)
{
    int max=k[0].size();
    vector<int> maxer=k[0];
    for(int x=1;x<k.size();x++)
    {
        if(k[x].size()>max)
        {
          maxer=k[x];
        }
    }
    return maxer;
}

vector<tuple<vector<int>, int, int>> myCVRP(vector<vector<int>> S, vector<int> Q) {
  
   cout<<"jfgdjfgdfg"<<endl;
   vector<vector<int> > saving=mySavings(S);
   cout<<"ghgfhfg"<<endl;
   vector<pair<int,int> > order=ascendingOrder(saving);
   cout<<"Hello hello hello"<<endl;
   vector<vector<int> > pathways; 
   vector<vector<int>>record;
   for(int x=0;x<S.size();x++)
   {
       record.push_back({x});
   }
   vector<pair<int,int>> order1=order;
   while(order1.size()!=0)
   {
      vector<int> maxTour;
      vector<vector<int>> record1=record;
      for(int x=0;x<order1.size();x++)
      {
        pair<int,int> info=order1[x];
        vector<int> a=record1[info.first];
        vector<int> b=record1[info.second];
        int distance=0;
        for(int x=0;x<a.size();x++)
        {
            distance=distance+Q[a[x]];
        }
        for(int y=0;y<b.size();y++)
        {
            distance=distance+Q[b[y]];
        }
        if(distance<Q[0])
        {
            vector<int> merge;
            if(a[a.size()-1]==info.first && b[0]==info.second)
            {
                merge=a;
                for(int x=0;x<b.size();x++)
                {
                    merge.push_back(b[x]);
                }
                vector<int> common;
                for(int x=0;x<record1.size();x++)
                {
                    if(record1[x]==record1[info.first] || record[x]==record1[info.second])
                    {
                        common.push_back(x);
                    }
                }
                for(int x=0;x<common.size();x++)
                {
                    record1[common[x]]=merge;
                }
                /*record1[info.first]=merge;
                record1[info.second]=merge;
                maxTour=maxLength(record1);
                for(int x1=1;x<=record1.size();x1++)
                {
                    if(contains(maxTour,x1))
                    {
                        record1[x1]=maxTour;
                    }
                }*/
            }
            else if(a[a.size()-1]==info.second && b[0]==info.first)
            {
                merge=b;
                for(int x=0;x<a.size();x++)
                {
                    merge.push_back(a[x]);
                }
                vector<int> common;
                for(int x=0;x<record1.size();x++)
                {
                    if(record1[x]==record1[info.first] || record[x]==record1[info.second])
                    {
                        common.push_back(x);
                    }
                }
                for(int x=0;x<common.size();x++)
                {
                    record1[common[x]]=merge;
                }
            }

        }

      }
      maxTour=maxLength(record1);
      pathways.push_back(maxTour);
      for(int x2=0;x2<order1.size();x2++)
      {
         if(contains(maxTour,order1[x2].first))
         {
             order1.erase(x2+order1.begin());
             x2--;
         }
         else if(contains(maxTour,order1[x2].second))
         {
             order1.erase(x2+order1.begin());
             x2--;
         }
      }
     



   }
   vector<int> stored;
   for(int u=1;u<S.size();u++)
   {
       stored.push_back(u);
   }

   for(int x=0;x<pathways.size();x++)
   {
       for(int y=0;y<pathways[0].size();y++)
       {
           vector<int> info=pathways[x];
           for(int z=0;z<stored.size();z++)
           {
               if(contains(info,stored[z]))
               {
                   stored.erase(stored.begin()+z);
                   z--;
               }
           }
       }
   }
   for(int a=0;a<stored.size();a++)
   {
       pathways.push_back({stored[a]});
   }


   vector<int> demand(pathways.size(),0);
   vector<int> distance1(pathways.size(),0);
   for(int x3=0;x3<pathways.size();x3++)
   {
       vector<int> track=pathways[x3];
       for(int x4=0;x4<track.size()+1;x4++)
       {
          if(x4!=track.size())
          {
             demand[x3]=demand[x3]+Q[track[x4]];
          }
          if(x4==0)
          {
              distance1[x3]=S[0][track[0]];
          }
          else if(x4>0)
          {
              if(x4<track.size())
              {
                 distance1[x3]=distance1[x3]+S[track[x4-1]][track[x4]];
              }
             else if(x4==track.size())
              {
                  distance1[x3]=distance1[x3]+S[0][track[x4-1]];
              }
          }
       }
   }
 
     vector<tuple<vector<int>, int, int>> make;
      for(int x5=0;x5<pathways.size();x5++)
      {
          make.push_back(make_tuple(pathways[x5],demand[x5],distance1[x5]));
      }

    return make;
 
  /*
    TODO:

    Write an algorithm that runs the CVRP algorithm from the shortest path graph.

    Input:
      vector<vector<int>> S: the shortest path matrix
      vector<int> Q: Q[0] is the total capacity and for j >= 1, Q[j] is the demand of vertex j 
        (i.e.  A -> 1, B -> 2, C -> 3, and so on).

    Return:
      vector<tuple<vector<int>, int, int>>: a vector containing information of each CVRP tour. The tuple
        contains a vector of the path, the total capacity for this path, and the total length of this path.
        Thus, if there are 3 paths:
          O - A - E - O (capacity 70, length 8)
          O - C - D - O (capacity 30, length 10)
          O - B - O  (capacity 10, length 4)
        Within the first tuple, it will contain
	        1. a vector [1,5]
          2. the capacity 70
          3. the length 8
        This continues for the 2 other paths, and all of these tuples are stored in the outer vector.

   NOTE: Recall, vertices start at 1, not 0. Ie. A -> 1, B -> 2, C -> 3, and so on.
   NOTE: The order of the tours in this vector does not matter and you will receive full points as long 
      as all the tours are present in this vector.
   
   Hint: You may want to call mySavings from this function.
  */
}

int mySavingsLength (vector<vector<int>> S, vector<int>Q) {
  vector<tuple<vector<int>, int, int>> make=myCVRP(S,Q);

  
  int distance=0;
  for(int x=0;x<make.size();x++)
  {
      vector<int> print=get<0>(make[x]);
      for(int y=0;y<print.size();y++)
      {
          cout<<print[y]<<",";
      }
      cout<<endl;
      distance=distance+get<2>(make[x]);
  }

  return distance; 

  
  /*
    TODO:
    
    Write an algorithm that calculates the length of the Savings Heuristic
    
    Input:
      vector<vector<int>> S: the shortest path matrix
      vector<int> Q: Q[0] is the total capacity and for j >= 1, Q[j] is the demand of vertex j 
        (i.e.  A -> 1, B -> 2, C -> 3, and so on).
    
    Return:
      int savingsLength: sum of the lengths of all tours after CVRP

    Hint: You may want to call myCVRP from this function
  */
}


int myRoundTripLength (vector<vector<int>> S, vector<int>Q) {
 vector<int> distance=S[0];
 int distance1=0;
 for(int x=0;x<distance.size();x++)
 {
     distance1=distance1+distance[x];
 }
 return 2*distance1;
 
  /*
    TODO:
    
    Write an algorithm that calculates the length of the Round Trip
    
    Input:
      vector<vector<int>> S: the shortest path matrix
      vector<int> Q: Q[0] is the total capacity and for j >= 1, Q[j] is the demand of vertex j 
        (i.e.  A -> 1, B -> 2, C -> 3, and so on).
    
    Return:
      int roundTripLength: sum of the lengths of all roundtrips before CVRP

    Hint: You may want to call myCVRP from this function
  */
}
/////////////////////////////////////////////////////////
//////////////       QUESTION 2 HERE   //////////////////
/////////////////////////////////////////////////////////

tuple<vector<int>, vector<int>, int> mySimplexLP(vector<vector<int>> A, vector<int> B, vector<int> C) {
/*
    TODO:

    Implement the Simplex algorithm.

    Input:
        vector<vector<int>> A: an m x n array of integers
        vector<int> B: an m-item list of integers
        vector<int> C: an n-item list of integers
    
    return:
        vector<int> optimal: array of length n with optimal values for x1, ..., xn
        vector<int> slack: array of length m with slack variable values for s1, ..., sm
        int value: objective value of the optimal solution
  */
}
