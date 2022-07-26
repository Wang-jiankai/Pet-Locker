# 基于单片机的宠物寄存柜设计

#### 介绍
随着携带宠物外出的现象的增多。出现了越来越多需要进入某些场所，但却被保安告知宠物不许入内的情况。鉴于这种情况，设计一款宠物寄存柜。
该寄存柜可以满足出入某些不能携带宠物的场所时宠物主人暂时寄存宠物的需求。其由单片机控制整个系统的动作，配有触控屏，将各柜位寄存情况、信息输入等界面显示在显示屏上，在输入正确的密码后开锁，或在指纹识别模块识别到匹配的指纹时自动解锁，由电机做相应动作。寄存柜内配有温度、声音传感器，在检测到宠物体温异常或连续发出叫声时，自动发送信息给主人。若寄存期间宠物出现逃跑、生病等情况要及时上报并根据登记的联系方式通知宠物主人。

#### 版本计划
计划在后续版本中加入包括但不限于如下功能
1.  无操作10秒进入待机模式，全屏显示广告图片。触击屏幕任意位置继续
2.  硬件到位后添加宠物体温红外测量功能-------------------------------√
3.  宠物叫声分贝超阈值连续监测功能-----------------------------------√
4.  叫声分贝值模数转换----------------------------------------------√
5.  短信发送功能，在存入宠物或宠物出现异常情况时向主人发送短信通知-----√
6.  作为寄存柜设计项目，加入猫笼作为柜实体
7.  在输入密码成功后，显示本人收款二维码，收取寄存费用
8.  在用户完成缴费后，触击屏幕回到首页-------------------------------√
9.  刷脸支付功能
10. 加入开门电机、电机驱动模块--------------------------------------√
11. 添加指纹模块，在用户有急事短存时，只需记录指纹即可快速存取宠物
12. 设置老板指纹，验证成功该指纹后，可以打开任何笼子
13. 密码短信发送时，将用户电话分段存入EEPROM中-----------------------√
14. 在输入密码时，提示存入宠物时预留的手机号，方便用户寻找密码，方便工作人员在遇到特殊情况需要手动通知时查阅---------------------------------------√
15. 自行设计电路绘制PCB，将本项目从开发板搬到原创硬件电路
16. 任何本人能力范围内、可促进项目成熟、稳定、便利化、商业化、美化的其他功能


#### 软件

1.  Software中提供了软件工程源码
2.  本项目目前为止共有如下几个状态界面
    1. 寄存柜待选择界面
    2. 手机号输入界面
    3. 发送密码界面
    4. 密码输入界面
    5. 收费界面


####  在3.0_Full_Version版本中更新了如下功能

    1. 将密码附在发给用户的短信中，使用户实时可查
    2. 在宠物体温出现多次（具体见main.c）异常时，给用户发送告警短信，并在十分钟内不重复发送
    3. 添加开门电机，由继电器控制，在寄宠物、取宠物时，作开门动作
    4. 将麦克风传感器替换为更灵敏的
    5. 将16号柜的宠物监测信息（声音、温度）与单位名实时显示在对应位置，并优化显示格式
    
    
#### 硬件

1. 硬件目前基于正点原子STM32F1精英开发板、2.8寸TFTLCD、SIM900A等模块
2. Hardware文件夹中包括各模块的原理图与尺寸图
3. 硬件整体连接图
![输入图片说明](2.Hardware/%E6%95%B4%E4%BD%93%E7%A1%AC%E4%BB%B6%E8%BF%9E%E6%8E%A5%E5%9B%BE.jpg)


####  在2.4_Preview版本中更新了如下功能

    1. 实现在存时状态对宠物体表温度的红外测温
    2. 将测得的温度数据实时展示在首页对应柜位

####  在2.3_Preview版本中更新了如下功能

    1. 实现确认手机号后发送密码短信，但尚未将随机密码加入短信内
    2. 实现连续嚎叫时，自动发送告警短信功能，显示发送结果，并在15分钟内不再发送
    3. 其他完善

####  在2.2_Preview版本中更新了如下功能

    1. 实现11位电话号码的掉电保存、取出删除
    2. 取回宠物后显示用户电话号码、抹掉号码数据
    3. SIM900A软件配置
    4. 在用户完成缴费后，触击屏幕回到首页并伴有蜂鸣
    5. 在输入密码时，提示存入宠物时预留的手机号

####  在2.1_Preview版本中更新了如下功能

    1. 添加SIM模块软件、硬件，测试可以正常通信，但相关功能尚未实现
    2. 在16号柜添加MIC模块检测噪声分贝，并在数数转换后显示
    3. 在MIC输出信号超过阈值时，触发短信发送程序
    4. 添加红外测温模块软硬件，但尚未适配

####  在2.0_Preview版本中更新了如下功能

    1. 将密码改为随机生成
    2. 将随机生成的密码即使存入EEPROM并在调试时便捷展示
    3. 完善代码注释
    4. 添加触摸屏校准功能
    5. 将柜位空置状态标志位存入RRPROM防犯掉电失忆
    6. 将存入宠物的时间点存入EEPROM
    7. 在取出宠物时读取对应柜位存入时间，并作差计算寄存时长计算费用并显示
    8. 按删除按钮时，如输入数字已为0，可进一步撤回到上一界面
    9. 添加消噪调试标记，便于快速定位的蜂鸣器操作，方便在夜晚调试
    10. 基本完成全流程可视部分编写，通过中期答辩



#### 开发环境

MDK5.14.0.0





#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

