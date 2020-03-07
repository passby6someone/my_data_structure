#include <iostream>
#include <string>
#include<math.h>
 
template <typename F>
void print(F &a){
    // std::cout<<f()<<std::endl;
    a(2,2,2);
}

template <typename Type, int N>
int arraysize(Type (&array)[N]) {
  return N;
}
 
int main() {
    int define[] = {1,2,3,4,5,6,7,8};
    std::cout <<arraysize(define)<< std::endl;
    int num = 101;
    auto a = [&num](int a,int b,int c) ->int {
        printf("%d",num);
        num++;
        return a;
    };
    // a(2,2,2);
    print(a);
    std::cout<<num<<std::endl;
    num++;
    // print(a(3));
    int x;
    scanf("%d",&x);
    return 0;
}

// #include<iostream>
// using namespace std;

// template<typename T,int N>
// void PrintValues( T (&ia)[N])
// {
//     for (int i = 0; i < N; i++)
//     {
//         cout << ia[i] << endl;
//     }
// }

// int main()
// {
//     int j[2] = { 0, 1 };
//     PrintValues(j);
//     return 0;
// }