# 宿舍电力控制器（OLED 版本）

[English Version](./README_ENG.md) | 中文版本

![项目横幅]()

一个小巧高效的宿舍电力管理解决方案，具有 OLED 显示屏、用户友好的界面和先进(?)的功能设计。

## 功能

- [x] **OLED 显示屏**：提供宿舍信息以及当前时间实时显示。
- [ ] **蓝牙连接**：支持通过移动应用进行简单配置和状态监控。
- [ ] **用户交互**：配备按钮以便于本地控制和导航。
- [ ] **可扩展设计()**：支持集成加速度传感器等附加模块。

## 硬件需求

1. **ESP32-S3 开发板**
2. **0.96 英寸 OLED 显示屏 (SSD1306)**
3. **按钮**：至少 4 个 按钮，用于导航。
4. **可选模块**：
   - 温湿度传感器 AHT10
   - 无源蜂鸣器 (恼人的音乐)

## 软件需求

- VS Code
- PlatformIO

## 安装步骤

1. **克隆仓库**：
   ```bash
   git clone https://github.com/BakkaBlue/DormitoryElectricityController-OLED-Ver.git
   cd DormitoryElectricityController-OLED-Ver
   ```
2. **安装依赖项**：
   - 通过 PlatformIO 添加必要的库。

3. **配置代码**：
   - 根据您的硬件设置更新文件中的引脚配置或是通信速率。

4. **上传代码**：
   - 连接 ESP32-S3 开发板，并使用您 IDE 上传代码。

## 使用方法

### OLED 导航-Under Construction
- **左右按钮**：在菜单中导航。
- **确认按钮**：选择选项。
- **返回按钮**：返回上一级菜单。

### 蓝牙控制-Under Construction
1. 在手机上打开配套应用。
2. 与 ESP32-S3 设备配对。
3. 实时访问数据并远程配置设置。

### 闹铃
- 每天早上<u>按时</u>听***恼人的蜂鸣器音乐***
- 暂时需要串口设置闹钟

## 贡献

我们欢迎贡献！请遵循以下步骤：

1. Fork 仓库。
2. 创建一个功能分支：
   ```bash
   git checkout -b feature-name
   ```
3. 提交您的更改并推送：
   ```bash
   git push origin feature-name
   ```
4. 创建一个拉取请求。

## 鸣谢

本项目在 OpenAI 的 ChatGPT 的协助下完成代码和概念设计。所有内容均由 Cyren 审核和最终定稿。欢迎贡献，但需遵循本项目的 AGPL-3.0 许可证。

## 许可证

本项目根据 GNU Affero General Public License v3.0 授权。详情参见 [LICENSE](./LICENSE) 文件。

此许可证确保本项目的任何修改或衍生版本都以 AGPL 开源，同时禁止未经许可的商业用途。

## 联系方式

如有问题，请随时联系作者：
- **GitHub**: [BakkaBlue](https://github.com/BakkaBlue)
- **电子邮件**: chip06balabala@gmail.com

---

祝您使用宿舍电力控制器（OLED 版本）愉快！🚀
