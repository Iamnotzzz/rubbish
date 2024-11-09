import torch
import torch.optim as optim
import torchvision.transforms as transforms
import torchvision.datasets as datasets
import os
import matplotlib.pyplot as plt
from torch.utils.data import random_split, DataLoader

# 自定义数据集类
class MyDataset:
    def __init__(self, dataset, device):
        self.dataset = dataset
        self.data = torch.from_numpy(dataset.data).float().to(device) / 255.0
        self.targets = torch.tensor(dataset.targets).to(device)

    def __len__(self):
        return len(self.dataset)

    def __getitem__(self, idx):
        return self.data[idx], self.targets[idx]

# GPU设备设置：如果有GPU则使用GPU，否则使用CPU
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

# 基本的图像转换，包括将图像转换为 Tensor 并进行归一化处理
transform = transforms.Compose([
    transforms.ToTensor(),  # 将图片转换为 Tensor 格式
    transforms.Normalize((0.5,), (0.5,))  # 归一化处理，mean=0.5，std=0.5
])

# 检查数据集是否已经存在
data_path = './data'
if not os.path.exists(data_path):
    os.makedirs(data_path)  # 如果路径不存在，则创建路径

# 加载 CIFAR-10 数据集并封装到 MyDataset
try:
    dataset = datasets.CIFAR10(root=data_path, train=True, download=True, transform=transform)
    dataset = MyDataset(dataset, device)  # 使用自定义数据集类
except Exception as e:
    print(f"加载数据集时出错：{e}")

# 设置学生的学号最后一位（请根据自己的学号修改）
last_digit_of_id = 9  # 示例：用自己的学号最后一位数字替换
# 根据学号最后一位定义数据集划分比例
split_ratio = 0.7 if last_digit_of_id <= 4 else 0.8  # 如果学号最后一位 <= 4，则训练集占 70%，否则占 80%
# 划分数据集为训练集和验证集
train_size = int(split_ratio * len(dataset)) 
val_size = len(dataset) - train_size 
train_dataset, val_dataset = random_split(dataset, [train_size, val_size]) 

# 创建 DataLoader，设置 batch_size 为 32 + 学号最后一位数字
batch_size = 32 + last_digit_of_id  
train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)  # 训练集数据加载器
val_loader = DataLoader(val_dataset, batch_size=batch_size, shuffle=False)  # 验证集数据加载器
print(f"Training on {train_size} images, Validating on {val_size} images.")

# 定义神经网络模型
model = torch.nn.Sequential(
    torch.nn.Flatten(),  # 将输入展平为一维
    torch.nn.Linear(32*32*3, 512),  # 全连接层，输入维度为 32x32x3，输出维度为 512
    torch.nn.ReLU(),  # 激活函数 ReLU
    torch.nn.Linear(512, 10),  # 输出层，10 个类别（CIFAR-10 数据集有 10 个类别）
).to(device)

# 定义损失函数和优化器
criterion = torch.nn.CrossEntropyLoss()  # 使用交叉熵损失函数
learning_rate = 0.001 + (last_digit_of_id * 0.0001)  # 根据学号最后一位调整学习率
optimizer = optim.Adam(model.parameters(), lr=learning_rate)  # 使用 Adam 优化器

# 设置训练的 epoch 数量，基于学号最后一位
num_epochs = 10 + last_digit_of_id  # 总训练次数
print(f"Training for {num_epochs} epochs with learning rate {learning_rate}.")

# 训练过程
train_losses = []  # 用于存储每个 epoch 的训练损失
train_accuracies = []  # 用于存储每个 epoch 的训练准确率
val_accuracies = []  # 用于存储每个 epoch 的验证准确率

for epoch in range(num_epochs):
    model.train()  # 将模型设置为训练模式
    running_loss = 0.0
    correct = 0
    total = 0
    for inputs, labels in train_loader:
        optimizer.zero_grad()  # 清空梯度
        outputs = model(inputs)  # 前向传播
        loss = criterion(outputs, labels)  # 计算损失
        loss.backward()  # 反向传播
        optimizer.step()  # 更新模型参数

        running_loss += loss.item()  # 累积损失
        _, predicted = torch.max(outputs, 1)  # 获取预测结果
        total += labels.size(0)  # 总样本数
        correct += (predicted == labels).sum().item()  # 计算正确的预测数

    train_accuracy = 100 * correct / total  # 计算训练准确率
    print(f"Epoch {epoch+1}/{num_epochs}, Loss:{running_loss:.4f}, Training Accuracy:{train_accuracy:.2f}%")

    # 验证过程
    model.eval()  # 将模型设置为评估模式
    correct = 0
    total = 0
    with torch.no_grad():  # 禁用梯度计算，节省内存
        for inputs, labels in val_loader:
            outputs = model(inputs)  # 前向传播
            _, predicted = torch.max(outputs, 1)  # 获取预测结果
            total += labels.size(0)  # 总样本数
            correct += (predicted == labels).sum().item()  # 计算正确的预测数

    val_accuracy = 100 * correct / total  # 计算验证准确率
    print(f"Validation Accuracy after Epoch {epoch + 1}:{val_accuracy:.2f}%")
    
    # 记录损失和准确率
    train_losses.append(running_loss)
    train_accuracies.append(train_accuracy)
    val_accuracies.append(val_accuracy)

# 绘制训练损失曲线
plt.figure()
plt.plot(range(1, num_epochs + 1), train_losses, label="Training Loss")
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.title("Training Loss")
plt.legend()
plt.show()

# 绘制准确率曲线
plt.figure()
plt.plot(range(1, num_epochs + 1), train_accuracies, label="Training Accuracy")
plt.plot(range(1, num_epochs + 1), val_accuracies, label="Validation Accuracy")
plt.xlabel("Epochs")
plt.ylabel("Accuracy")
plt.title("Training and Validation Accuracy")
plt.legend()
plt.show()
