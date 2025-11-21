# 代码勇者

## 项目说明

### 游戏背景
此项目为独立 RPG 游戏，玩家将扮演具有高超代码水平的勇者在地牢中闯关，披荆斩棘。通过获得金币购买装备，战胜魔王，最终取得勇者之剑。

## 项目变量声明

### 地图
- **地面**：  
  **0** 代表正常地板，**1** 代表墙壁或边界。

- **传送门**：  
  传送门有多种类型，方便区分的做法是将传送门编号以 **2** 开头，后续数字为具体传送门编号。例如，**21** 代表 BFS 第一个传送门。

- **陷阱**：  
  陷阱是地图中的危险区域。

#### 关于 BFS 系列地图
- 第三个地图存在无法到达问题。


## 日志

### 7月份，备赛码蹄，不再频繁更新 **readme**
#### 7月更新日志
- **奠定游戏主基调**  
  算法学习为主，同时加以游戏的娱乐性质

- **搭建 **mainloop** 模块**  
  main 中的主循环，保证游戏持续运行，退出后总能回到主界面

- **搭建 **player** 模块**
  player 模块极其重视游戏的扩展性，后期添加 api 均在此模块中添加

- **搭建 **map** 模块**
  map 模块负责地图的生成与记录，map 模块记录了早期地图的初步信息  

- **搭建 **textact** 模块**
  textact 模块负责文字的显示与输入，练手阶段，未解决换行问题

### 8.11 更新日志
#### 游戏初步框架搭建
- **模块划分**：  
  游戏初步划分为四个模块：**player**、**map**、**mainloop** 和 **textact**。
- **player 模块**：  
  此模块负责检测玩家当前状态，以及检测玩家走动，拾取金币动作，事件触发等各类功能 api，同时在里面内置放穿墙检测。
- 

### 8.12 更新日志

#### 游戏底层逻辑联立

- **player 模块**：  
  该模块主要负责检测玩家当前状态，控制玩家进入特定区域后触发关卡传送与状态检验。

- **map 模块**：  
  该模块负责地图的生成与记录，并生成不同的图像以存储各个地图的具体情况。

- **mainloop 模块**：  
  该模块保障主地图 **home** 的生成。无论当前状态如何，玩家都可以返回主界面重新选择关卡。

- **textact 模块**：  
  该模块负责文字的显示与输入。

### 8.13 更新日志

#### 添加 Google 断网小恐龙
- **物动人不动**：  
  空格键控制小恐龙进行跳跃，躲避过程中积累得分。
- 添加了 Google 断网小恐龙作为游戏内置模块，待与其他模块整合。

- **dino模块**  
  - **1**：白色 
  - **2**：红色
  - **3**：黑色

**问题**：  
  - Bird 的添加出现了瞬移问题。


### 8.14 更新日志

#### 主界面功能添加
- **主界面退出功能**：  
  添加了主界面的退出功能，并增加了事件响应。

- **金币功能**：  
  玩家可以通过金币购买道具，同时金币也可用于记录游戏得分。

#### 代码优化
- 由于全局变量反复出现不定时报错，已将相关功能迁移至 **main** 函数中。

### 8.15 更新日志

#### 主界面功能更新
- **金币管理**：  
  金币功能已集成至各个关卡中，玩家可以在主界面查看金币数量，每个关卡也可以获得金币。

- **链表传送关卡**：  
  新关卡的核心是让玩家理解链表在内存中不连续存储的特性。

- **Google 断网小恐龙功能更新**：  
  - 添加向下的速度，增强闪避灵活性。

- **金币流畅性增强**：  
  - 采用 3x3 矩阵图片轮换实现金币旋转效果。

### 8.16 更新日志

#### 链表传送关卡修复
- **传送门机制**：  
  修复了传送门之间的反复传送问题。问题源于矩阵和实际屏幕的 **x, y** 坐标不一致。

- **链表关卡退出**：  
  完善了退出机制，玩家在退出时会回到主界面。

### 8.19 更新日志

#### 添加告示板
- **告示板**：  
  告示板将会在玩家停留时显示，提供游戏内容的相关通知。

#### Bug 修复
- **BFS3 地图修复**：  
  修复了 BFS3 地图中的不可达路径问题。

- **地图载入修复**：  
  修复了 BFS3 地图载入失败的问题，之前因为 **switch** 语句缺乏 **break**，导致重复载入了错误的地图。

#### 玩法重大更新
- **输入功能**：  
  算法实战正式开始，输入功能即将添加。

- **图形界面优化**：  
  游戏图形界面进行了进一步的优化。

### 8.26 更新日志

#### 音乐功能添加
- 为不同场景添加了背景音乐。音乐将在进入场景后自动播放。

#### Bug 修复
- **窗口指针问题**：  
  修复了因窗口关闭导致指针归 **NULL** 的问题，避免了报错。

- **音乐播放优化**：  
  优化了音乐播放逻辑，进入场景后可以通过 **close all** 一次性关闭所有音乐并播放当前音乐。

- **地图精细化**：  
  对 BFS 关卡进行重新排列。

### 8.27 更新日志

#### 优化告示板显示
- 优化了告示板显示方式，添加了换行符的处理，使得告示板能够显示多行文字。

### 8.28 更新日志
#### 添加了README文件阅读功能，方便玩家了解游戏背景和玩法。
- **README 文件**：  
  玩家可以通过游戏内置的 README 文件了解游戏背景、玩法和更新日志。

- **bug 修复**：  
  修复了阅读 **README** 文件时可能出现的路径问题，确保文件能够正确加载和显示，以及添加确认阅读按钮保证不会一次性出现多个 **README**打开

### 8.29 更新日志
#### README 文件更新
- **内容添加**  
  尝试丰富化 README 文件内容，添加了更多的游戏背景和玩法说明，以及图标展示

### 8.30 更新日志
- **bug修复**  
  修复了MessageBox函数在某些情况下无法正确显示的问题，确保玩家在游戏过程中能够顺利接收提示信息。
- **性能优化**  
  字符串拼接方式优化，提升了游戏运行效率，修复了空白文本格的出现。

### 9.1 更新日志
- **出门旅游**  
-   旅游回来将继续持续更新README文件，添加了更多的游戏背景故事和玩法说明，提升玩家的游戏体验。  
	
	
### 后记  

**感谢自己两个月来长久的从零开始的不懈开发，如果您对此游戏感到满意，请阅读下文**

# *What is Love?*  
![LOVE](asset/love.jpg){width=300px height=150px}  
**Love is the silent sonnet of two souls dancing in the golden twilight of existence.**

It is the unspoken promise carried by autumn leaves, the way they fall
—**not because they must, but because the wind whispers their names.**

Love is the **art of seeing**—not just with the eyes, but with the trembling heart. 
It is the courage to **hold another’s broken pieces** and call them **sacred**.

It is **not possession, but surrender**—
Not a cage, but **an open sky** where two birds soar, tethered only by choice.

Love is the quiet **"I know"** when the world shouts **"you don't."**
The way a hand finds another in darkness, **not to lead, but to say, *"Here, I am too."***

It is the **first and last breath** of every great story—
The **why** behind every **"I will"** and every **"I still do."**

In the end, love is simply this:
**The universe, whispering to itself in the language of two hearts.**

![disappointed](asset/disappointed.jpg){width=300px height=150px}}




 
__The End__
