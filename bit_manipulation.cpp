#include<bits/stdc++.h>
using namespace std;
//Bit Manipulation
int getbit(int n,int pos)
{
    return ((n&(1<<pos))!=0);     
}
int setbit(int n,int pos)
{
    return (n | (1<<pos));
}
//n= 11010 in binary  ,pos =3 
// 1<<3 = 1000       ->      ~1000=0111             ->   11010&0111=10010
int clear(int n,int pos) //unsetbit
{
    return  n&(~(1<<pos)); //~ complement
}
// 8== 1000 ,7== 111 
// 6== 110, 5== 101
// flip all element from rightmost setbit of n ->obtain-> n-1
// if n is power of 2 -> then always have one setbit so flip all bits of n then-> n-1 is obtained
bool is_power_of_2(int n) //check if no. is power of 2 or not
{
    if(n && !(n & n-1)) // n && .. -> n==0 so n-1=-1 is not defined
        return  true;
    return false;
}
//count the no. of set bit
int count_setbit(int n)
{
    int count=0;;
    while (n)
    {
       n=n&n-1;
       count++;
    }
    return count; 
}
//generate all subset of set
//-----------------------------
//find the unique element in vector in which all element present twice except one.
vector<int>v{1,2,3,4,1,3,2};
int unique()
{
    int xor_sum=0;
    for(int i=0;i<v.size();i++)
    {
        xor_sum=xor_sum^v[i];         //^ == xor   1&0=1 ,0&0=0
    }
    return xor_sum;
}
vector<int>v1{1,2,3,4,1,3,2,1,2,3};
//find the unique element in vector in which all element present thrice except one.
void unique_3()
{
    int xor_sum=0;
    for(int i=0;i<v1.size();i++)
    {
        xor_sum=xor_sum^v1[i];         
    }
    int pos=0;
    int xor_sum1=0;
    for(int i=0;i<v1.size();i++)
    {
        if(getbit(v1[i],pos))
        {
            xor_sum1=xor_sum1^v[i];
        }
    }
    cout<<xor_sum1<<" "<<(xor_sum^xor_sum1)<<endl;
    
}
int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    cout<<is_power_of_2(256)<<endl;
    cout<<count_setbit(7)<<endl;
    cout<<unique()<<endl;
}