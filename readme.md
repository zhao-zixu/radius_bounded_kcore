# Community Search



## Efficient Computing of Radius-Bounded k-Cores

triple-vertex-based

* determined by the three vertices
* determined by the two vertices

binary-vertex-based

* with r

rotating-circle-based (RotC)





minimum covering circle (MCC)

Radius-Bounded k-Core



* maximality constraint check ? （R*N）ignored by other problem defination



core decomposition [11] persistent k core (persistent community search?)

MCC O(c,gamma)

Wr(u,v) a set of binary-vertex-bounded circles with raidus r



图的表示和存储

复制



邻接表

直接复制整张图



* only calculate nearby points of bin-MCC ?
* core maintenance

* 按照y坐标排序，从上向下，每次只考虑下面的点



去除重复。。。





best quality



ac-tree

* 删掉距离大于2r 的边，计算每个点的相似度值
* 反向索引？。。。 inverted index...

* k值计算。。。



bug。。。 

一个圈里面有两个以上connected k-core