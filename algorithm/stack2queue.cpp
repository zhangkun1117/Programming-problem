
class Stack
{
public:
        int top();
        void push(int x); // Push an element in stack;
        int pop();  // Pop an element out of stack;
        int count() const;     // Return the number of the elements in stack;
};

class Queue
{
public:
         void Enqueue(int x){
            s1.push(x);
         };
         int Dequeue(){
            if(s2.count() ==0){
                return 0; 
            }
            while(s1.top()){
                s2.push(s1.top());
                s1.pop();
            }
            while(s2.top()){
                s1.push(s2.top());
                s2.pop();
            }
         };
private:
        Stack s1;
        Stack s2;
};