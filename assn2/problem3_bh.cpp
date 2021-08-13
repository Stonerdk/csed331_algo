#include <iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<tuple>
#include<cmath>
using namespace std;


long long divide_box(long long h, long long w, long long l, vector<tuple<long long, long long>>* cur_box)
{
   long long iterator = 0;
   for (long long i = (*cur_box).size() - 1; i >= 0; i--)
   {
      iterator *= 8;
      long long  k = get<0>((*cur_box)[i]);
      long long cur_box_count = (long long) ((h >> k) * (w >> k) * (l >> k)) - iterator;
      if (cur_box_count > get<1>((*cur_box)[i]))
      {
         iterator += get<1>((*cur_box)[i]);
      }
      else
      {
         iterator += cur_box_count;
         get<1>((*cur_box)[i]) = cur_box_count;
      }
   }

   return iterator;
}


int main()
{
   
   long long testcase = 0;
   cin >> testcase;
   vector <vector<long long>> output;

   for (long long t = 0; t < testcase; t++)
   {
      long long box_num = 0;
      vector <tuple<long long, long long>> box;
      long long box_size = 0;
      long long box_amount = 0;

      cin >> box_num;
      for (long long i = 0; i < box_num; i++) {
         cin >> box_size;
         for (int j = 0; j < 30; j++) {
            if (pow(2, j) == box_size) {
               box_size = j; break;
            }
         }
         box.push_back(make_tuple(box_size, 0));
      }

      for (long long i = 0; i < box_num; i++)
      {
         cin >> box_amount;
         get<1>(box[i]) = box_amount;
      }

      long long height, width, length;
      cin >> height >> width >> length;

      vector<tuple<long long, long long>> cur_box;
      for (long long i = 0; i < box.size(); i++)
      {
         cur_box.push_back(make_tuple(get<0>(box[i]), get<1>(box[i])));
      }

      long long output_boxsize = divide_box(height, width, length, &cur_box);
      if (output_boxsize == (long long)width*height*length)
      {
         vector <long long> v1;
         long long sum = 0;
         for (long long i = 0; i < box_num; i++)
         {
            v1.push_back( get<1>(cur_box[i]));
         }
         output.push_back(v1);
      }
      else
      {
         vector <long long> v1;
         v1.push_back(-1);
         output.push_back(v1);
      }
   }

   for (long long i = 0; i < output.size(); i++)
   {
      for (long long j = 0; j < output[i].size(); j++)
      {
         cout << output[i][j]<<" ";
      }
      cout << endl;
   }
}