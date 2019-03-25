## C++ 简明编码规范

### 一、类成员变量以 **m_** 开头，指针类型使用 **p** 开头，指针类型成员变量使用 **m_p** 开头。

```
char* pData;

class A
{
    
private:
	int m_Type;
	T*  m_pInstance;
};
```



### 二、指针类型的星号靠在变量上而不是变量类型上。

**正确的做法**

```
bool CLinkManager::SetTopicID(TIniFile *tinifile, char *fieldmd)
```

**错误的做法**

```
bool CLinkManager::SetTopicID(TIniFile * tinifile, char* fieldmd);
```



### 三、返回指针类型的函数，星号靠在函数名上，而不是返回类型上

**正确的做法**

```
T *getType()
{
    
}
```



**错误的做法**

```
T* getType()
{
    
}
```





### 四、函数第一个花括号单独占一行。

**正确的做法**

```
void func()
{
    
}
```

**错误的做法**

```
void funct(){
    
}
```



### 五、限制头文件重复包含的宏以两个下划线开头，以 H__ 结束，中间所有单词均大写，且单词与单词之间使用一个下划线连接；末尾 #endif 处加上注释 //!宏名

```
#ifndef __LINK_MANAGER_H__
#define __LINK_MANAGER_H__

//your code

#endif //!__LINK_MANAGER_H__
```



### 六、文档注释格式

**每一行冒号后面的文字要对齐**

```
/******************************************************************
** 文件名:	 QmarketMDHandler.h
** 版 权:	  (C) QuantDo
** 创建人:	 shilf
** 日 期:	  2019/3/23 16:52
** 版 本:	  1.0
** 描 述:	  行情级联处理器
** 应 用:   行情系统
********************************************************************/
```



### 七、所有函数参数与参数之间增加一个空格，运算符左右各加一个空格

```
int func(int a, int b, int c);
int a = b;
```



### 八、单词 id，在代码和配置文件中统一成 **Id**

```
string someId;
int topicId;
```





### 九、以 nullptr 代替 NULL

```
m_pMDhandler = nullptr;
m_pSnapConsumer = nullptr;
m_pIncConsumer = nullptr;
```



### 十、函数注释

```
/**函数功能描述
 *@param i 描述
 *@param j 描述
 *@param k 描述（时间类型要交代清楚时间单位和时间显示格式）
 *@return 描述
 */
int func(int i, int j, int k)
{
    return i;
}
```



### 十一、构造函数和析构函数如果使用默认实现，使用 = default 关键字

**正确的做法**

```
A() = default;
~A() = default;
```

**错误的做法**

```
A(){}
~A(){}
```



### 十二、如果一个可以实例化的类，不需要使用其拷贝构造函数和 operator = 函数，使用 = delete 将其删除。

```
A(const A& rhs) = delete;
A& operator = (const A& rhs) = delete;
```



### 十三、每个宏定义或者常量必须写注释说明其含义



### 十四、对于 for-each 循环，尽量使用 const &，其次是 &，最后才是拷贝

```
for (const Json::Value& jMarketBookLevel : jData)
{
       //循环中不会修改 jData 的值                        
}

for (Json::Value& jMarketBookLevel : jData)
{
       //循环中会修改 jData 的值                        
}

for (Json::Value jMarketBookLevel : jData)
{
       //循环中需要拷贝 jData 的值做修改                      
}
```



### 十五、在 Visual Studio 菜单【Tools】->【Options】-> 【Text Editor】-> 【C/C++】-> 【Tabs】将 Tab size 设置成插入四个空格，而不是插入\t。



### 十六、单行 if 也使用花括号

**正确做法**

```
if (a)
{
    printf("hellworld\n");
}
```

**错误做法**

```
if (a)
	printf("hellworld\n");
```



### 十七、申请内存或者栈变量大数组（长度超过 4）尽量使用 4 的倍数

```
//错误的做法
char sz[99];

//正确的做法
char sz[100];
```



### 十八、类名以大写字母 C 开头，结构体不用



### 十九、成员变量名称对齐

**正确的做法**

```
class CKafkaMDClient :public CMarketBase
{
private:
	KafkaMDHandler	                     *m_pMDhandler;
	KConsumer		                     *m_pSnapConsumer;
	KConsumer		                     *m_pIncConsumer;
	std::vector<RdKafka::TopicPartition*> m_vecIncTopicpartitionList;
	std::string		                      m_strSnapTopic;
	std::string		                      m_strIncTopic;

	using SnapInstrumentMap = CHashMap<char *, SnapInstrument *, HashString>;
	SnapInstrumentMap                     m_snapInstrumentMap;
};
```

**错误的做法**

```
class A
{
private:
	// 指向CFtdcMduserApi实例的指针
	CQdFtdcMduserApi *m_pUserApi;
	CQdFtdcReqUserLoginField m_reqUserLogin;
	CMDFlowManager *m_pFlowManager;

	CFTDCPackage m_mdMessage;
	//收报每个报文之前确定主题号
	int m_nTopicID;
	int m_nTopicType;
	//收到每个报文之前确定序号
	int m_nSequenceNo;
	//每个api的号
	int m_nNumber;
    bool m_wsSend;

    QuWSFront *m_qwsfront;
	CMarketDataHandler *m_pMarketDataHandle;
	CTradingDayType m_tradingDay;   
};
```



### 二十、子类重写父类的函数需要加上 override 关键字，不用加 virtual 了。

```
class A : B
{
public:
    void OnRtnMBLMarketData(CQdFtdcMBLMarketDataField *pMBLMarketData) override;
};
```



### 二十一、尽量将类的基元数据类型（bool、char、short、int、long、指针类型）放在一起。

**正确做法**

```
class A
{
private:
	int  a;
    int  b;
    bool c;
    st   s;
    CXX  xx;
};
```

**错误做法**：

```
class A
{
private:
	int  a;
	st   s;
    int  b;
    CXX  xx;
    bool c;  
};
```

