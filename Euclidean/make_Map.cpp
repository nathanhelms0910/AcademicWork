#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <stdlib.h>
using namespace std;
int main(){
  vector<char> map_chars;
    char start = 'S';
    char finish = 'F';
    char empty_Space = '.';
    char wall = '#';
    int width = 7;
    int height = 7;
    int seed;
    map_chars.push_back(start);
    map_chars.push_back(finish);
    map_chars.push_back(empty_Space);
    map_chars.push_back(wall);
    cout << "provide a randomized seed" << endl;
    cin >> seed;
    cout << "provide a width" << endl;
    cin >> width;
    cout << "provide a height" << endl;
    cin >> height;
    srand(seed);
          freopen("output.txt","w",stdout);


      for(int i = 0; i < width; i++)
       {
         for(int i = 0; i < height; i++)
         {
	   //default_random_engine  generator;
	   //uniform_int_distribution<int> distribution(0, map_chars.size());
	  // int dice_roll = distribution(generator);

 	  int  random_Value = rand() % map_chars.size();
           cout << map_chars[random_Value];
           if(map_chars[random_Value] == 'S')
           {
           auto it = map_chars.begin() + random_Value;
           rotate(it, it + 1, map_chars.end());
           map_chars.pop_back();
           }
   
           if(map_chars[random_Value] == 'F')
           {
             auto it = map_chars.begin() + random_Value;
             rotate(it, it + 1, map_chars.end());
             map_chars.pop_back();
           }
         }
         cout << endl;
   
       }
       return 0;
}
