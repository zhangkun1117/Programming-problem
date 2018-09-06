#include <bits/stdc++.h>
using namespace std;
class smartprt{
    public:
     void myunique(){
        auto it = make_unique<int[]>(10);
        it[9] = 10;
    }
    void my_unique_ptr3(){
        auto uptr = make_unique<int>(42);
         printf("%d\n", *uptr);//42
        ///std::unique_ptr<int> uptr1 = uptr; ///unique_ptr无拷贝构造函数
         ///std::unique_ptr<int> uptr1(uptr);  ///等效写法
         std::unique_ptr<int> uptr2 = std::move(uptr);
        ///printf("%d\n",*uptr); ///error 所有权已交给uptr2
         printf("%d\n", *uptr2);
    }
    void my_shared_ptr(){
        ///auto sptr = std::make_shared<int[]>(10); //error
        ///sptr[6] = 20;
        auto sptr = std::make_shared<int>();
        
    }
    void auto_run_fun(FILE* f){
        printf("auto running.\n");
        fclose(f);
    }
    void my_shared_ptr2(){
        FILE* f = fopen("data.txt","w");
        std::shared_ptr<FILE> file_ptr(f, auto_run_fun);
    }
    void my_shared_ptr3(){
    /*demo* d = new demo();
    std::shared_ptr<demo> sptr1(d);
    std::shared_ptr<demo> sptr2(d);//~demo() error
    */
    auto sptr3 = std::make_shared<int >();
    std::shared_ptr<int> sptr4(sptr3); ///shared_ptr拷贝构造函数
    }
   ///weak_ptr -> shared_ptr
    void my_weak_ptr(){
        std::weak_ptr<int > wptr;
        {
            auto sptr = std::make_shared<int>();
            wptr = sptr;
            auto sptr2 = wptr.lock();
             if (!wptr.expired()){///等价于sptr2 != nullptr
                 printf("shared_ptr ok\n");
                }
        }
        if (wptr.expired()){
              printf("shared_ptr deleted\n");
        }
    }
};

int main(){
   // smartprt p;
   // p.myunique();
   cout<<"test"<<endl;
    system("pause");
    return 0;
}
