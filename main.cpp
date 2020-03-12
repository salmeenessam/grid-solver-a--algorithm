#include <iostream>
#include<bits/stdc++.h>
#include <math.h>
using namespace std;

//The maximum number of ROWs and COLUMNs in the grid

#define ROW 5
#define COLM 5

//Defining a type for pair

typedef pair<int,int> Pair;
typedef pair<double,pair<int,int> > dPair;

//Constructing the NODE

struct node
 {
    int par_x , par_y ;
    double f , g , h ;
 };

// A function to check if the node exists in the Grid

bool nod_exists(int row , int colm)
 {
    if((row>-1 && row<ROW)&&(colm>-1 && colm<COLM))
     {
        return true ;
     }
    else
     {
        return false ;
     }
 }

// A function to check if the node blocked or not

bool nod_blocked(int grid[][COLM] , int row , int colm)
 {
   if(grid[row][colm]==0)
    {
      return true;
    }
   else
    {
      return false;
    }
 }

// A function to check if I reached destination

bool dest_reached(int row , int colm , Pair dest)
 {
   if((row==dest.first)&&(colm==dest.second))
    {
      return true ;
    }
   else
    {
      return false;
    }
 }

// Calculate H

double calc_h(int row , int colm , Pair dest)
 {
   double h = sqrt(pow((double)(row-dest.first),2)
                  +
                  (pow((double)(colm-dest.second),2))) ;

   return h;
 }


// A function to trace the path from START to END

void trace_path(node nodinfo[][COLM] , Pair dest)
 {
   int row=dest.first , colm=dest.second ;

   cout<< "\n The path from START to End is : { " ;

   stack<Pair> path ;

   Pair nod ;
   while(!(((nodinfo[row][colm].par_x)==row)&&((nodinfo[row][colm].par_y)==colm)))
    {
      nod=make_pair(row,colm) ;
      path.push(nod) ;
      int temp_row = nodinfo[row][colm].par_x ;
      int temp_colm =nodinfo[row][colm].par_y ;
      row=temp_row ;
      colm=temp_colm ;
    }

   nod=make_pair(row,colm) ;
   path.push(nod) ;

   nod=path.top() ;
   cout<< "(" << nod.first << "," << nod.second << ")" ;
   path.pop() ;
   while(!(path.empty()))
    {
      nod=path.top() ;
      cout<< "-->(" << nod.first << "," << nod.second << ")" ;
      path.pop() ;
    }
    cout<< " }" <<endl ;

 }



// A function to get shortest path

void get_shortestPath(int grid[][COLM] , Pair START , Pair END)
 {
  // Checking that start or end inside the GRID
   if(nod_exists(START.first,START.second) == false)
    {
      cout << "The Start point doesn't exist in the Grid\n " ;
    }
   if(nod_exists(END.first,END.second) == false)
    {
      cout << "The End point doesn't exist in the Grid\n " ;
    }

  // Checking that start or end are blocked
   if(nod_blocked(grid,START.first,START.second) == true)
    {
      cout << "The Start point is blocked\n " ;
    }
   if(nod_blocked(grid,END.first,END.second) == true)
    {
      cout << "The End point is blocked\n " ;
    }

  // Checking that start is the same as end
   if(dest_reached(START.first,START.second,END) == true)
    {
      cout<< "The start and End point are the same\n " ;
    }

  //___________________

   bool closedlist[ROW][COLM] ;
   memset(closedlist,0,sizeof(closedlist)) ;

   node nodinfo[ROW][COLM] ;

   for(int i=0;i<ROW;i++)
    {
      for(int j=0;j<COLM;j++)
       {
          nodinfo[i][j].f = FLT_MAX ;
          nodinfo[i][j].g = FLT_MAX ;
          nodinfo[i][j].h = FLT_MAX ;
          nodinfo[i][j].par_x = -1 ;
          nodinfo[i][j].par_y = -1 ;
       }
    }

   int i=START.first , j=START.second ;

   nodinfo[i][j].f = 0 ;
   nodinfo[i][j].g = 0 ;
   nodinfo[i][j].h = 0 ;
   nodinfo[i][j].par_x = i ;
   nodinfo[i][j].par_y = j ;

   set<dPair> openlist ;

   Pair n=make_pair(i,j) ;
   dPair nd=make_pair(0.0,n) ;
   openlist.insert(nd) ;

   bool destfound = false ;

   while(!openlist.empty())
    {
      nd = *openlist.begin() ;
      openlist.erase(openlist.begin()) ;

      i = nd.second.first;
		  j = nd.second.second;
      closedlist[i][j] = true;

    /*  node-->current node (i, j)
  		  N --> North	      (i-1, j)
        S --> South	      (i+1, j)
	  	  E --> East	      (i, j+1)
		    W --> West	      (i, j-1)   */


		  double newg, newh, newf ;

    // checking the north cell  1

      if(nod_exists(i-1,j))
       {
          if(dest_reached(i-1,j,END))
           {
              nodinfo[i-1][j].par_x=i ;
              nodinfo[i-1][j].par_y=j ;
              cout << "The destination is reached \n" ;
              trace_path(nodinfo,END) ;
              destfound = true ;
              return ;
           }
          else if (closedlist[i-1][j]==false && nod_blocked(grid,i-1,j)==false)
           {
              newg = nodinfo[i][j].g + 1.0;
              newf = calc_h(i-1, j, END);
              newf = newg + newf ;

              if(nodinfo[i-1][j].f==FLT_MAX || nodinfo[i-1][j].f>newf)
               {
                  openlist.insert(make_pair(newf,make_pair(i-1,j))) ;

                  nodinfo[i-1][j].g = newg ;
                  nodinfo[i-1][j].h = newh ;
                  nodinfo[i-1][j].f = newf ;
                  nodinfo[i-1][j].par_x = i ;
                  nodinfo[i-1][j].par_y = j ;
               }

           }
       }

     // checking the south cell  2

      if(nod_exists(i+1,j))
       {
          if(dest_reached(i+1,j,END))
           {
              nodinfo[i+1][j].par_x=i ;
              nodinfo[i+1][j].par_y=j ;
              cout << "The destination is reached \n" ;
              trace_path(nodinfo,END) ;
              destfound = true ;
              return ;
           }
          else if (closedlist[i+1][j]==false && nod_blocked(grid,i+1,j)==false)
           {
              newg = nodinfo[i][j].g + 1.0;
              newf = calc_h(i+1, j, END);
              newf = newg + newf ;

              if(nodinfo[i+1][j].f==FLT_MAX || nodinfo[i+1][j].f>newf)
               {
                  openlist.insert(make_pair(newf,make_pair(i+1,j))) ;

                  nodinfo[i+1][j].g = newg ;
                  nodinfo[i+1][j].h = newh ;
                  nodinfo[i+1][j].f = newf ;
                  nodinfo[i+1][j].par_x = i ;
                  nodinfo[i+1][j].par_y = j ;
               }

           }
       }

     // checking the east cell  3

      if(nod_exists(i,j+1))
       {
          if(dest_reached(i,j+1,END))
           {
              nodinfo[i][j+1].par_x=i ;
              nodinfo[i][j+1].par_y=j ;
              cout << "The destination is reached \n" ;
              trace_path(nodinfo,END) ;
              destfound = true ;
              return ;
           }
          else if (closedlist[i][j+1]==false && nod_blocked(grid,i,j+1)==false)
           {
              newg = nodinfo[i][j].g + 1.0;
              newf = calc_h(i, j+1, END);
              newf = newg + newf ;

              if(nodinfo[i][j+1].f==FLT_MAX || nodinfo[i][j+1].f>newf)
               {
                  openlist.insert(make_pair(newf,make_pair(i,j+1))) ;

                  nodinfo[i][j+1].g = newg ;
                  nodinfo[i][j+1].h = newh ;
                  nodinfo[i][j+1].f = newf ;
                  nodinfo[i][j+1].par_x = i ;
                  nodinfo[i][j+1].par_y = j ;
               }

           }
       }

     // checking the west cell  4

      if(nod_exists(i,j-1))
       {
          if(dest_reached(i,j-1,END))
           {
              nodinfo[i][j-1].par_x=i ;
              nodinfo[i][j-1].par_y=j ;
              cout << "The destination is reached \n" ;
              trace_path(nodinfo,END) ;
              destfound = true ;
              return ;
           }
          else if (closedlist[i][j-1]==false && nod_blocked(grid,i,j-1)==false)
           {
              newg = nodinfo[i][j].g + 1.0;
              newf = calc_h(i, j-1, END);
              newf = newg + newf ;

              if(nodinfo[i][j-1].f==FLT_MAX || nodinfo[i][j-1].f>newf)
               {
                  openlist.insert(make_pair(newf,make_pair(i,j-1))) ;

                  nodinfo[i][j-1].g = newg ;
                  nodinfo[i][j-1].h = newh ;
                  nodinfo[i][j-1].f = newf ;
                  nodinfo[i][j-1].par_x = i ;
                  nodinfo[i][j-1].par_y = j ;
               }

           }
       }

  /*    if(nod_exists(i-1,j+1))
       {
          if(dest_reached(i-1,j+1,END))
           {
              nodinfo[i-1][j+1].par_x=i ;
              nodinfo[i-1][j+1].par_y=j ;
              cout << "The destination is reached \n" ;
              trace_path(nodinfo,END) ;
              destfound = true ;
              return ;
           }
          else if (closedlist[i-1][j+1]==false && nod_blocked(grid,i-1,j+1)==false)
           {
              newg = nodinfo[i][j].g + 1.0;
              newf = calc_h(i-1, j+1, END);
              newf = newg + newf ;

              if(nodinfo[i-1][j+1].f==FLT_MAX || nodinfo[i-1][j+1].f>newf)
               {
                  openlist.insert(make_pair(newf,make_pair(i-1,j+1))) ;

                  nodinfo[i-1][j+1].g = newg ;
                  nodinfo[i-1][j+1].h = newh ;
                  nodinfo[i-1][j+1].f = newf ;
                  nodinfo[i-1][j+1].par_x = i ;
                  nodinfo[i-1][j+1].par_y = j ;
               }

           }
       }

      if(nod_exists(i-1,j-1))
       {
          if(dest_reached(i-1,j-1,END))
           {
              nodinfo[i-1][j-1].par_x=i ;
              nodinfo[i-1][j-1].par_y=j ;
              cout << "The destination is reached \n" ;
              trace_path(nodinfo,END) ;
              destfound = true ;
              return ;
           }
          else if (closedlist[i-1][j-1]==false && nod_blocked(grid,i-1,j-1)==false)
           {
              newg = nodinfo[i][j].g + 1.0;
              newf = calc_h(i-1, j-1, END);
              newf = newg + newf ;

              if(nodinfo[i-1][j-1].f==FLT_MAX || nodinfo[i-1][j-1].f>newf)
               {
                  openlist.insert(make_pair(newf,make_pair(i-1,j-1))) ;

                  nodinfo[i-1][j-1].g = newg ;
                  nodinfo[i-1][j-1].h = newh ;
                  nodinfo[i-1][j-1].f = newf ;
                  nodinfo[i-1][j-1].par_x = i ;
                  nodinfo[i-1][j-1].par_y = j ;
               }

           }
       }

      if(nod_exists(i+1,j+1))
       {
          if(dest_reached(i+1,j+1,END))
           {
              nodinfo[i+1][j+1].par_x=i ;
              nodinfo[i+1][j+1].par_y=j ;
              cout << "The destination is reached \n" ;
              trace_path(nodinfo,END) ;
              destfound = true ;
              return ;
           }
          else if (closedlist[i+1][j+1]==false && nod_blocked(grid,i+1,j+1)==false)
           {
              newg = nodinfo[i][j].g + 1.0;
              newf = calc_h(i+1, j+1, END);
              newf = newg + newf ;

              if(nodinfo[i+1][j+1].f==FLT_MAX || nodinfo[i+1][j+1].f>newf)
               {
                  openlist.insert(make_pair(newf,make_pair(i+1,j+1))) ;

                  nodinfo[i+1][j+1].g = newg ;
                  nodinfo[i+1][j+1].h = newh ;
                  nodinfo[i+1][j+1].f = newf ;
                  nodinfo[i+1][j+1].par_x = i ;
                  nodinfo[i+1][j+1].par_y = j ;
               }

           }
       }

      if(nod_exists(i+1,j-1))
       {
          if(dest_reached(i+1,j-1,END))
           {
              nodinfo[i+1][j-1].par_x=i ;
              nodinfo[i+1][j-1].par_y=j ;
              cout << "The destination is reached \n" ;
              trace_path(nodinfo,END) ;
              destfound = true ;
              return ;
           }
          else if (closedlist[i+1][j-1]==false && nod_blocked(grid,i+1,j+1)==false)
           {
              newg = nodinfo[i][j].g + 1.0;
              newf = calc_h(i+1, j-1, END);
              newf = newg + newf ;

              if(nodinfo[i+1][j-1].f==FLT_MAX || nodinfo[i+1][j-1].f>newf)
               {
                  openlist.insert(make_pair(newf,make_pair(i+1,j-1))) ;

                  nodinfo[i+1][j-1].g = newg ;
                  nodinfo[i+1][j-1].h = newh ;
                  nodinfo[i+1][j-1].f = newf ;
                  nodinfo[i+1][j-1].par_x = i ;
                  nodinfo[i+1][j-1].par_y = j ;
               }

           }
       }*/

    }

   if(destfound == false)
    {
      cout << "Failed to Find path \n" ;
    }

   return ;
 }

int main()
 {

   int grid[ROW][COLM] = {{1,0,1,1,1},
                          {0,0,1,1,0},
                          {0,0,1,0,1},
                          {1,0,1,1,1},
                          {1,1,1,1,1}};

   Pair START = make_pair(4,0) ;

   Pair END = make_pair(0,4) ;

   get_shortestPath(grid,START,END) ;

    return 0;
 }
