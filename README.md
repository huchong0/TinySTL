# TinySTL
运用模板实现部分STL的容器和算法
主要实现的容器有：

顺序式容器：vector list deque  

关联式容器：set map unordered_set unoedered_map

容器带有allocator，虽然只是简单的包装了一下 operator new 和 operator delete，没有根据对象类型做太多的优化

vector、list以及deque均实现了其内部数据结构以及对应的迭代器，可以用于STL的算法。不过迭代器的trait还是继承自STL的iterator类来完成的

set 和 map 内部结构用红黑树完成，同样也带有双向迭代器。

hash的关联式容器，自带的默认hash函数只是单纯的取模，支持传入仿函数用作hash

algorithm方面：
符合大多数的规范，以两个指针为范围进行操作。
实现了大多数非更易型算法和部分更易型算法和变序算法
