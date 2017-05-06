[原文](https://linyuxuanlin.github.io/2016/09/11/%E9%80%A0%E4%B8%AA%E6%96%B9%E8%88%9F%E5%8F%8D%E5%BA%94%E7%82%89/#more)


> 造一副自己的铁衣
> 
> 这是一个非常长远的目标
> 
> 作为钢铁侠的脑残粉
> 
> 我决定先给自己造个**方舟反应炉**

<!-- more -->

首先，它长这样：

![方舟反应炉.jpg](http://upload-images.jianshu.io/upload_images/2218072-d936790630439789.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 实现的功能：
- 阻止金属碎片进入心脏                 （不可能）
- 提供强大的核反应能量                 （想得美）
- 装装逼 （这个倒可以）

说了这么多，我们来看看它是怎样被造出来的吧
# 1.材料清单

- 一个环形LED模块
- 一块arduino板子
- 小小的锂电池
- 一个小开关（总不能一直亮着吧）
- 泡沫板 （用于把LED光线分散均匀）
- 硬纸板（做个后盖）
- 橡皮筋（方便挂在胸前）



![16位圆形全彩 LED模块.jpg](http://upload-images.jianshu.io/upload_images/2218072-217cccba14da0c21.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



![arduino pro mini.jpg](http://upload-images.jianshu.io/upload_images/2218072-d5449fa211109a5d.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



![锂电池.jpg](http://upload-images.jianshu.io/upload_images/2218072-b991bf877592d720.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



![泡沫板.jpg](http://upload-images.jianshu.io/upload_images/2218072-9c9c86edcc8f0ccc.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


# 2.把程序下载进arduino
程序：https://coding.net/u/linyuxuanlin/p/Arc_reactor/git/tree/master

##### 实现的效果：
- 蓝色呼吸灯
- 开机有彩虹灯的特效

# 3.把主体打印出来
模型文件放在[这](https://coding.net/u/linyuxuanlin/p/Arc_reactor/git/tree/master)
![模型.png](http://upload-images.jianshu.io/upload_images/2218072-6c6e24325bcc8a0f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

# 4.组装

**1. 接线：**

|  LED模块 | Arduino  |
| --- | --- |
| Din | D6 | 
| VCC | 5V  | 
| GND | GND  | 

**2. 到碗里来：**

首先，把泡沫板切一个圆，直接压进去
把Arduino和LED粘在上面
电池可放里面，只是感觉空间太窄我直接把它外接出来
![装载.jpg](http://upload-images.jianshu.io/upload_images/2218072-f14454e6e81c19e5.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

>如果还剩空间可以把打印件剪薄几层，太厚了不好看
>
![残暴.jpg](http://upload-images.jianshu.io/upload_images/2218072-f87f8656f1cc39bc.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

**3. 封印：**
厚纸板上裁个圆，作为后盖


![后盖](http://upload-images.jianshu.io/upload_images/2218072-20bcbbf2c6ff4a8f.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

用502粘上
为了紧固橡皮筋，我另外粘了些胶带

![222029ed8eeayybeebgw38.jpg](http://upload-images.jianshu.io/upload_images/2218072-f800fa338b716caf.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> 史上最丑的设计



#完成！


![反应炉](http://upload-images.jianshu.io/upload_images/2218072-1a0cacb13594119e.jpeg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![反应炉](http://upload-images.jianshu.io/upload_images/2218072-4fe3e0c31c14d146.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


----------
另附：佩戴效果图

![:D](http://upload-images.jianshu.io/upload_images/2218072-c97e599be57aeffa.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


写在最后：

+ 此方舟反应炉功能也许还不完善，我会慢慢加入
+ 如果你有任何问题，或是有更好的建议，欢迎随时和我交流。


---

本文由 [Lin](https://linyuxuanlin.github.io/about/) 创作
可自由转载、引用，但需署名作者且注明文章出处。