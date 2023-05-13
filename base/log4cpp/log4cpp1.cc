//步骤：
//准备阶段：
//          1、设置PatternLayout并设置输出格式(通过new获得)
//          2、设置日志的目的地(通过new获得)
//          3、一个目的地对应一个日志布局 
//正式阶段：
//          1、声明一个日志来源(Category)
//          2、设置Category优先级
//          3、设置Category输出目的地(终端、文件、回卷文件)
//          4、设置每条日志的级别
//          5、回收资源(前面new了资源) Category::shutdown();



//test0只设置一个目的地(Appender),OstreamAppender
//test1设置两个目的地(OstreamAppender和FileAppender)
//test2设置目的地为回卷文件
#include <iostream>

using std::cout;
using std::endl;

//第三方库头文件写在标准库下面
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Layout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>

using namespace::log4cpp;

void test0() {
    //前三个步骤是准备工作
    //1、把日志布局换成PatternLayout(调用构造函数)
    PatternLayout *ptn1 = new PatternLayout();
    //格式控制:日期 日志来源(Category) 优先级 消息本身
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    //2、设置日志的目的地为标准输出流
    OstreamAppender *pOsApp = new OstreamAppender("console", &cout);

    //3、每个目的地都有个日志布局
    pOsApp->setLayout(ptn1);


    Category &mycat = Category::getRoot().getInstance("记录日志的名字");
    //设置Category优先级:只有当消息的优先级高于DEBUG才会输出
    mycat.setPriority(Priority::DEBUG);
    //日志输出目的地
    mycat.addAppender(pOsApp);

    //每条日志的优先级
    mycat.emerg("This is a emerg msg");
    mycat.fatal("This is a fatal msg");
    mycat.warn("This is a warn msg");
    mycat.notice("This is a notice msg");

    //回收资源
    Category::shutdown();
}

void test1() {
    //前三个步骤是准备工作
    //1、把日志布局换成PatternLayout(调用构造函数)
    PatternLayout *ptn1 = new PatternLayout();
    //格式控制:日期 日志来源(Category) 优先级 消息本身
    ptn1->setConversionPattern("%d %c [%p] %m%n");


    PatternLayout *ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");


    //2、设置日志的目的地为标准输出流
    OstreamAppender *pOsApp = new OstreamAppender("console", &cout);
    FileAppender *pFileApp = new  FileAppender("pFileApp", "du.log");

    //3、每个目的地都有个日志布局(否则会导致内存泄露)
    pOsApp->setLayout(ptn1);
    pFileApp->setLayout(ptn2);


    Category &mycat = Category::getRoot().getInstance("记录日志的名字");
    //设置Category优先级:只有当消息的优先级高于DEBUG才会输出
    mycat.setPriority(Priority::DEBUG);
    //日志输出目的地
    mycat.addAppender(pOsApp);
    mycat.addAppender(pFileApp);

    //每条日志的优先级
    mycat.emerg("This is a emerg msg");
    mycat.fatal("This is a fatal msg");
    mycat.warn("This is a warn msg");
    mycat.notice("This is a notice msg");

    //回收资源
    Category::shutdown();
}

void test2() {
    PatternLayout *ptn3 = new PatternLayout();
    ptn3->setConversionPattern("%d %c [%p] %m%n");

    RollingFileAppender *pRollFileApp = new RollingFileAppender("pRollingApp", "rolling.log",
                                                                5 * 1024, 3); 
    pRollFileApp->setLayout(ptn3);

    Category &mycat = Category::getRoot().getInstance("起个名字");  
    mycat.setPriority(Priority::DEBUG);
    mycat.setAppender(pRollFileApp);

    
    for(int i = 0; i < 100; ++i) {
        mycat.emerg("This is a emerg msg");
        mycat.fatal("This is a fatal msg");
        mycat.info("This is a info msg");
        mycat.alert("This is a alert msg");
    }

    Category::shutdown();
}

int main()
{
    /* test0(); */
    /* test1(); */
    test2();
    return 0;
}
