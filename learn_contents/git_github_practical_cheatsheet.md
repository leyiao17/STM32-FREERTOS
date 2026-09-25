# Git → GitHub 实战命令速查表

> 场景：从零创建一个 `todo-app` 项目，然后完成 Git 版本迭代、上传 GitHub、开发新功能、合并分支、同步远程代码。
>
> 目标：以后每次做新工程，只要照着这个例子操作即可。

---

# 0. 你只需要先记住这条主线

```text
创建项目
   ↓
git init
   ↓
写代码
   ↓
git add .
   ↓
git commit
   ↓
连接 GitHub
   ↓
git push
   ↓
继续修改代码
   ↓
git add .
git commit
git push
```

日常最常用的其实就是：

```bash
git status
git add .
git commit -m "feat: xxx"
git push
```

---

# 1. 第一次使用 Git：配置身份

一台电脑通常只需要配置一次。

```bash
git --version
```

配置用户名：

```bash
git config --global user.name "YOUR_NAME"
```

配置邮箱：

```bash
git config --global user.email "YOUR_EMAIL"
```

检查配置：

```bash
git config --global --list
```

---

# 2. 实际例子：创建一个 todo-app 项目

## 第一步：创建工程目录

```bash
mkdir todo-app
cd todo-app
```

现在目录是：

```text
todo-app/
```

---

# 3. 初始化 Git

```bash
git init
```

此时 Git 会在项目内部创建：

```text
todo-app/
└── .git/
```

`.git/` 保存这个项目的版本历史。

不要手动删除它。

---

# 4. 创建项目文件

例如：

```bash
touch README.md
touch main.py
touch .gitignore
```

项目结构：

```text
todo-app/
├── .git/
├── .gitignore
├── README.md
└── main.py
```

---

# 5. 配置 .gitignore

Python 项目可以先写：

```gitignore
__pycache__/
*.pyc

.venv/
venv/

.env

.idea/
.vscode/

.DS_Store

*.log
```

特别注意：

```text
.env
```

通常不要提交，因为里面可能包含：

```text
API Key
数据库密码
Token
Secret
```

---

# 6. 看看 Git 当前状态

```bash
git status
```

你可能看到：

```text
Untracked files:
  .gitignore
  README.md
  main.py
```

意思是：

> Git 已经发现这些文件，但是还没有正式纳入版本。

---

# 7. 第一次提交

把当前文件加入暂存区：

```bash
git add .
```

再次检查：

```bash
git status
```

然后提交：

```bash
git commit -m "chore: initialize project"
```

现在你的项目已经有第一个版本。

查看提交历史：

```bash
git log --oneline
```

你可能看到：

```text
a3f2c91 chore: initialize project
```

---

# 8. 在 GitHub 创建远程仓库

在 GitHub 创建一个仓库：

```text
todo-app
```

如果本地已经有代码，建议 GitHub 上创建仓库时：

```text
不要勾选 README
不要勾选 .gitignore
不要勾选 License
```

也就是创建一个空仓库。

GitHub 会给你一个仓库地址。

SSH 示例：

```text
git@github.com:YOUR_USERNAME/todo-app.git
```

HTTPS 示例：

```text
https://github.com/YOUR_USERNAME/todo-app.git
```

---

# 9. 本地 Git 连接 GitHub

推荐 SSH：

```bash
git remote add origin git@github.com:YOUR_USERNAME/todo-app.git
```

检查是否连接成功：

```bash
git remote -v
```

你应该看到类似：

```text
origin  git@github.com:YOUR_USERNAME/todo-app.git (fetch)
origin  git@github.com:YOUR_USERNAME/todo-app.git (push)
```

---

# 10. 把主分支统一命名为 main

```bash
git branch -M main
```

---

# 11. 第一次上传 GitHub

```bash
git push -u origin main
```

这里的：

```text
origin = GitHub 远程仓库
main   = 本地主分支
-u     = 建立默认关联
```

第一次执行完后，以后通常直接：

```bash
git push
```

即可。

---

# 12. 第一天：开发第一个功能

假设你开始写：

```python
# main.py

tasks = []

def add_task(task):
    tasks.append(task)

add_task("Learn Git")
print(tasks)
```

先看修改：

```bash
git status
```

查看具体改了什么：

```bash
git diff
```

确认没问题：

```bash
git add .
```

提交：

```bash
git commit -m "feat: add task creation"
```

上传 GitHub：

```bash
git push
```

---

# 13. 第二次修改：增加删除任务功能

你继续修改代码。

完成以后：

```bash
git status
```

查看变化：

```bash
git diff
```

加入暂存区：

```bash
git add .
```

提交：

```bash
git commit -m "feat: add task deletion"
```

上传：

```bash
git push
```

现在历史可能是：

```text
c82ea10 feat: add task deletion
91ab210 feat: add task creation
a3f2c91 chore: initialize project
```

查看：

```bash
git log --oneline
```

---

# 14. 修复 Bug

假设删除任务出现 Bug。

修改完成之后：

```bash
git status
git diff
git add .
git commit -m "fix: handle invalid task index"
git push
```

这就是一次完整版本迭代：

```text
修改代码
↓
查看修改
↓
暂存
↓
提交
↓
上传
```

---

# 15. 日常开发最常用流程

以后你每天基本就是：

```bash
git status
git diff

git add .

git commit -m "feat: add xxx"

git push
```

可以记成：

```text
status
↓
diff
↓
add
↓
commit
↓
push
```

---

# 16. 开发大功能：创建分支

假设现在要开发：

```text
用户登录功能
```

不要直接在 `main` 上乱改。

创建新分支：

```bash
git switch -c feature/login
```

查看当前分支：

```bash
git branch
```

可能显示：

```text
* feature/login
  main
```

`*` 表示你当前所在分支。

---

# 17. 在功能分支开发

写代码。

然后：

```bash
git status
git diff
git add .
git commit -m "feat: add user login"
```

如果又继续修改：

```bash
git add .
git commit -m "feat: add password validation"
```

上传这个分支：

```bash
git push -u origin feature/login
```

---

# 18. 功能完成后合并回 main

先切回主分支：

```bash
git switch main
```

先同步远程最新代码：

```bash
git pull
```

然后合并：

```bash
git merge feature/login
```

上传：

```bash
git push
```

现在：

```text
feature/login
      ↓
   merge
      ↓
    main
```

---

# 19. 删除已经完成的本地分支

确认已经合并之后：

```bash
git branch -d feature/login
```

如果也想删除 GitHub 上的远程分支：

```bash
git push origin --delete feature/login
```

---

# 20. 第二台电脑继续开发

假设换电脑了。

不要再 `git init`。

直接：

```bash
git clone git@github.com:YOUR_USERNAME/todo-app.git
```

进入项目：

```bash
cd todo-app
```

然后开发即可。

---

# 21. 开始工作前同步 GitHub 最新代码

如果项目可能被其他电脑或其他人修改：

```bash
git pull
```

建议形成习惯：

```text
开始工作
↓
git pull
↓
写代码
↓
git add
↓
git commit
↓
git push
```

---

# 22. 查看提交历史

简单查看：

```bash
git log --oneline
```

更直观：

```bash
git log --oneline --graph --decorate --all
```

可能看到：

```text
* 81ac002 (HEAD -> main) fix: login validation
* 92ac103 feat: add login
* c82ea10 feat: add task deletion
* 91ab210 feat: add task creation
* a3f2c91 chore: initialize project
```

---

# 23. 只暂存某一个文件

不一定每次都要：

```bash
git add .
```

比如只想提交：

```text
main.py
```

可以：

```bash
git add main.py
```

然后：

```bash
git commit -m "fix: correct task logic"
```

---

# 24. 提交前后悔了：取消 git add

假设执行了：

```bash
git add .
```

但还没有 commit。

可以取消暂存：

```bash
git restore --staged .
```

某一个文件：

```bash
git restore --staged main.py
```

注意：

这不会删除你的代码修改，只是取消暂存。

---

# 25. 修改代码后想恢复到上次提交

假设：

```text
main.py
```

被你改乱了，而且这些修改还没有 commit。

恢复：

```bash
git restore main.py
```

⚠️ 注意：

这个操作会丢掉 `main.py` 当前未提交的修改。

---

# 26. 修改最近一次 commit 的说明

例如刚刚：

```bash
git commit -m "update"
```

发现信息写得太烂。

可以：

```bash
git commit --amend -m "feat: add task search"
```

如果这个 commit 已经 push 到多人协作仓库，修改历史前要谨慎。

---

# 27. 查看远程仓库

```bash
git remote -v
```

---

# 28. 查看所有分支

本地分支：

```bash
git branch
```

本地 + 远程：

```bash
git branch -a
```

---

# 29. 切换分支

```bash
git switch main
```

或者：

```bash
git switch feature/login
```

---

# 30. 创建并立即切换分支

```bash
git switch -c feature/search
```

等价于：

```text
创建 feature/search
+
切换到 feature/search
```

---

# 31. GitHub 上有新代码，拉到本地

```bash
git pull
```

可以理解为：

```text
GitHub
↓
下载
↓
合并到当前本地分支
```

---

# 32. 本地有新 commit，上传 GitHub

```bash
git push
```

可以理解为：

```text
本地 Git
↓
上传
↓
GitHub
```

---

# 33. Git 的四个核心动作

```text
git add
```

意思：

> 把修改放进“准备提交区域”。

```text
git commit
```

意思：

> 在本地创建一个正式版本。

```text
git push
```

意思：

> 把本地版本上传 GitHub。

```text
git pull
```

意思：

> 把 GitHub 最新版本拉到本地。

---

# 34. Commit 信息推荐写法

推荐：

```text
类型: 做了什么
```

常见类型：

```text
feat      新功能
fix       修复 Bug
docs      修改文档
refactor  重构
test      测试
chore     工程配置
style     代码格式
```

例子：

```bash
git commit -m "feat: add user login"
```

```bash
git commit -m "fix: handle empty username"
```

```bash
git commit -m "docs: update README"
```

```bash
git commit -m "refactor: simplify authentication logic"
```

不要长期这样写：

```bash
git commit -m "update"
git commit -m "修改"
git commit -m "改一下"
git commit -m "最终版"
git commit -m "最终版2"
```

---

# 35. 发布正式版本

项目完成 `v1.0.0`：

```bash
git tag v1.0.0
```

查看 Tag：

```bash
git tag
```

上传 Tag：

```bash
git push origin v1.0.0
```

版本号一般：

```text
v1.0.0
 │ │ │
 │ │ └── Bug 修复
 │ └──── 新功能
 └────── 大版本变化
```

例如：

```text
v1.0.0  第一个正式版本
v1.0.1  修复 Bug
v1.1.0  增加功能
v2.0.0  大规模升级
```

---

# 36. 一个项目从 0 到 GitHub 的完整命令

以后创建新项目，可以直接复制下面这套。

```bash
# 创建项目
mkdir todo-app
cd todo-app

# 初始化 Git
git init

# 创建文件
touch README.md
touch .gitignore
touch main.py

# 查看状态
git status

# 第一次提交
git add .
git commit -m "chore: initialize project"

# 主分支命名
git branch -M main

# 连接 GitHub
git remote add origin git@github.com:YOUR_USERNAME/todo-app.git

# 第一次上传
git push -u origin main
```

以后每次修改：

```bash
git status
git diff
git add .
git commit -m "feat: describe your change"
git push
```

---

# 37. 开发新功能的完整命令

例如开发：

```text
用户登录
```

执行：

```bash
# 确保当前主分支最新
git switch main
git pull

# 创建功能分支
git switch -c feature/login

# 写代码……
```

写完：

```bash
git status
git diff
git add .
git commit -m "feat: add user login"

# 第一次上传这个分支
git push -u origin feature/login
```

功能完成后：

```bash
git switch main
git pull
git merge feature/login
git push
```

确认没问题：

```bash
git branch -d feature/login
```

---

# 38. 修 Bug 的完整命令

创建修复分支：

```bash
git switch main
git pull
git switch -c fix/login-error
```

修复代码。

然后：

```bash
git status
git diff
git add .
git commit -m "fix: resolve login error"
git push -u origin fix/login-error
```

合并：

```bash
git switch main
git pull
git merge fix/login-error
git push
```

删除本地分支：

```bash
git branch -d fix/login-error
```

---

# 39. 每天开发时直接看这里

## 开工

```bash
git switch main
git pull
```

## 开发小修改

```bash
# 写代码

git status
git diff
git add .
git commit -m "feat: xxx"
git push
```

## 开发大功能

```bash
git switch main
git pull

git switch -c feature/xxx

# 写代码

git status
git diff
git add .
git commit -m "feat: xxx"

git push -u origin feature/xxx
```

完成后：

```bash
git switch main
git pull
git merge feature/xxx
git push

git branch -d feature/xxx
```

---

# 40. 最重要的 Git 心智模型

```text
你的代码文件
     │
     │ git add
     ▼
  暂存区
     │
     │ git commit
     ▼
本地 Git 仓库
     │
     │ git push
     ▼
   GitHub
```

反过来：

```text
GitHub
   │
   │ git pull
   ▼
本地代码
```

---

# 41. 最终极简速查表

```bash
# 当前状态
git status

# 查看修改
git diff

# 暂存所有修改
git add .

# 提交
git commit -m "feat: xxx"

# 上传
git push

# 拉取
git pull

# 查看历史
git log --oneline

# 查看分支
git branch

# 创建分支
git switch -c feature/xxx

# 切换 main
git switch main

# 合并分支
git merge feature/xxx

# 删除分支
git branch -d feature/xxx

# 查看远程地址
git remote -v

# 克隆项目
git clone git@github.com:YOUR_USERNAME/REPOSITORY.git
```

---

# 42. 你真正需要形成的习惯

每次完成一个“小而完整”的修改：

```bash
git status
git diff
git add .
git commit -m "清楚描述这次修改"
git push
```

不要等到几十个功能全部写完以后才提交。

推荐：

```text
完成登录页面
→ commit

完成登录接口
→ commit

完成 Token 校验
→ commit

修复登录 Bug
→ commit

增加退出登录
→ commit
```

这样 Git 历史才真正有价值。

---

# 43. 一句话记住

```text
git init    = 开始管理这个项目
git status  = 我现在改了什么？
git diff    = 我具体改了什么？
git add     = 这些修改我要提交
git commit  = 创建一个本地版本
git push    = 上传 GitHub
git pull    = 从 GitHub 同步
git switch  = 切换开发分支
git merge   = 合并开发成果
git log     = 查看版本历史
```

## 最常用的五连

```bash
git status
git diff
git add .
git commit -m "feat: xxx"
git push
```

看到这里，你就应该知道下一步该敲什么命令。
