题外话：（可以跳过）
关于这次的仓库，我搞乱了好多次
真的很抱歉
--- 
数据库使用了 C语言的库来连接postgresql  
其它模块没有特别注意的
#### 1 使用的库依赖
gcc：(15.2.1+r447+g6a64f6c3ebb8-1)    
gcc-libs：(15.2.1+r447+g6a64f6c3ebb8-1)    
glibc：(2.42+r47+ga1d3294a5bed-1)    
glibc-locales：(2.42+r47+ga1d3294a5bed-1)   
lib32-glibc：(2.42+r47+ga1d3294a5bed-1)     
postgres (PostgreSQL) 18.1 
#### 2 关于main分支的问题  
这个不小心直接将dev分支全部记录拉过来了   
所以看上去可能有些乱并且只有两个人贡献   
贡献主要前往各个分支查看    
#### 3 关于第一次迭代问题   
第一次迭代的功能没有完全实现  
将教师秘书类先搁置一边暂不实现   
#### 4 关于设计的一些问题
如果是想要查看数据库是如何设计的  
表可以在这里看https://github.com/ousuc/CourseSelection/tree/main/doc/dataBase_layer/design-doc   
然后就是测试数据https://github.com/ousuc/CourseSelection/tree/main/doc/dataBase_layer/test_data  
其他的一些比如领域层设计同样在doc文档中  
main分支主要是存取可以直接部署到生产环境中的代码  
其他分支的内容会相对丰富一些  
#### 5 关于视频的问题
视频就是在video分支 这个名字或许不是很恰当  
内部包含PR和AE的工程文件   
