# 三相无刷直流电机驱动设计

#### 介绍
**stm32直流电机控制**
* 采用STM32F103C8T6作为主控
* 采用三相逆变桥电路
* 采集三相电流
* 前级采用栅极驱动MOS，自带闭锁
* 采集电机驱动电压，与MOS电流
![image](/4.Imgs/SCH1.png)
![image](/4.Imgs/SCH2.png)

#### 版本更新
* 【2023/3/02 09：44】 A01.06：修改原理图分压电阻
* 【2023/2/24 16：26】 A01.05：原理图部分完成，网络标号已添加，请按要求添加封装
* 【2023/2/24 14：10】 A01.04：除网络标号，原理图完成，请按要求添加封装
* 【2023/2/24 13：43】 A01.03：整体原理图模块完成，网络标号待连接
* 【2023/2/24 10：51】 A01.02：完善原理图文档信息
* 【2023/2/23 18：30】 A01.01：完成原理图FOC部分

#### 软件架构
* 分时调度



#### 参与贡献
* [爱学习的王大可](https://gitee.com/zhouqi98)
* [幺幺零1223](https://gitee.com/one-zero-1223)


