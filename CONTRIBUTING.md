# 贡献指南 - Contribution Guidelines

感谢您对 NTU MFE 参考资料库的贡献！

## 如何贡献

### 1. 准备工作
- Fork 本仓库到您的 GitHub 账户
- Clone 到本地：`git clone https://github.com/YOUR_USERNAME/NTU-mfe.git`
- 创建新分支：`git checkout -b feature/add-[course-name]-materials`

### 2. 添加资料
- 选择合适的目录结构（Year/Semester/Course）
- 遵循命名规范：`[课程代码]-[课程名称]`
- 为每个课程创建子文件夹：notes, assignments, projects, exams, references

### 3. 文件要求
- **笔记**：支持 Markdown, PDF, Word 格式
- **代码**：包含注释和 README 说明
- **数据**：提供数据描述和来源说明
- **大文件**：考虑使用 Git LFS 或提供下载链接

### 4. 提交规范
```
git add .
git commit -m "Add: [课程代码] - [具体添加内容]"
git push origin feature/add-[course-name]-materials
```

### 5. 创建 Pull Request
- 详细描述添加的内容
- 说明资料来源和版权情况
- 标注贡献者信息

## 文件组织规范

### 目录结构
```
Course-Name/
├── README.md          # 课程介绍和目录
├── notes/            # 课程笔记
│   ├── lecture-01.md
│   └── summary.pdf
├── assignments/       # 作业和习题
│   ├── hw1/
│   └── hw2/
├── projects/         # 课程项目
│   ├── project1/
│   └── README.md
├── exams/           # 考试资料
│   ├── midterm/
│   └── final/
└── references/      # 参考资料
    ├── textbooks/
    └── papers/
```

### 命名规范
- 文件夹：使用英文，单词间用下划线或连字符
- 文件：简洁明了，包含版本或日期信息
- 课程：`[课程代码]-[英文名称]` 如 `MH6803-Stochastic_Calculus`

## 内容准则

### ✅ 欢迎的内容
- 个人学习笔记和总结
- 课程作业解答（已过deadline）
- 项目代码和报告
- 有用的参考资料链接
- 学习经验分享

### ❌ 禁止的内容
- 正在进行的作业答案
- 违反学术诚信的内容
- 受版权保护的原版教材
- 未经授权的考试题目
- 个人隐私信息

## 版权和引用

### 上传资料时请注明：
- 资料来源和原作者
- 创建日期和贡献者
- 适用的许可证信息
- 使用限制说明

### 引用格式示例：
```markdown
## 资料信息
- **贡献者**：张三 (zhangsan@example.com)
- **课程**：MH6803 Stochastic Calculus
- **学期**：2024 Semester 1
- **来源**：个人课堂笔记
- **许可**：CC BY-SA 4.0
```

## 质量标准

### 文档要求
- 清晰的标题和目录
- 适当的格式和排版
- 准确的内容和公式
- 必要的说明和注释

### 代码要求
- 良好的代码风格
- 充分的注释说明
- 可运行的示例
- 依赖库说明

## 获得帮助

如有疑问，请：
1. 查看现有的 Issues
2. 创建新的 Issue 描述问题
3. 在 Discussions 中讨论
4. 联系仓库维护者

---

再次感谢您的贡献！让我们一起构建更好的学习资源库。