/**
 * 单例分为懒汉和饿汉式
 * */
//饿汉式
class Singleton_Hungry
{
public:
    static Singleton_Hungry& getInstance()
    {
        return m_data;
    }
    
private:
    static Singleton_Hungry m_data; //static data member 在类中声明，在类外定义
    Singleton_Hungry(){}
    ~Singleton_Hungry(){}
};

Singleton_Hungry Singleton_Hungry::m_data;

// 懒汉式
