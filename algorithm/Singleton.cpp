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
class Singleton_Lazy
{
public:
    static Singleton_Lazy* getInstance()
    {
        if(!m_data) 
            m_data = new Singleton_Lazy();
        return m_data;
    }
private:
    static Singleton_Lazy* m_data; //static data member 在类中声明，在类外定义
    Singleton_Lazy(){}
    ~Singleton_Lazy(){}
};
Singleton_Lazy* Singleton_Lazy::m_data = nullptr;