import torchvision.transforms as transforms 
import torchvision.datasets as datasets 
import os 
# 基本的图像转换
transform = transforms.Compose([
    transforms.ToTensor(), 
    transforms.Normalize((0.5,), (0.5,))
])

# 检查数据集是否已经存在
data_path = './data'
if not os.path.exists(data_path):
    os.makedirs(data_path)

# 加载 CIFAR-10 数据集
try:
    dataset = datasets.CIFAR10(root=data_path, train=True, download=True, transform=transform)
except Exception as e:
    print(f"加载数据集时出错：{e}")
from torch.utils.data import random_split 
# Set the student's last digit of the ID (replace with your own last digit)
last_digit_of_id = 9  # Example: Replace this with the last digit of your QMUL ID 
# Define the split ratio based on QMUL ID 
split_ratio = 0.7 if last_digit_of_id <= 4 else 0.8 
# Split the dataset 
train_size = int(split_ratio * len(dataset)) 
val_size = len(dataset) - train_size 
train_dataset, val_dataset = random_split(dataset, 
[train_size, val_size]) 
# DataLoaders 
from torch.utils.data import DataLoader 
batch_size = 32 + last_digit_of_id  # Batch size is 32 + last digit of your QMUL ID 
train_loader = DataLoader(train_dataset, 
batch_size=batch_size, shuffle=True) 
val_loader = DataLoader(val_dataset, 
batch_size=batch_size, shuffle=False) 
print(f"Training on {train_size} images, Validating on {val_size} images.")
import torch
import torch.optim as optim
# Define the model
model = torch.nn.Sequential(
torch.nn.Flatten(),
torch.nn.Linear(32*32*3, 512),
torch.nn.ReLU(),
torch.nn.Linear(512, 10), # 10 output classes for CIFAR-10
)
# Loss function and optimizer
criterion = torch.nn.CrossEntropyLoss()
# Learning rate based on QMUL ID
learning_rate = 0.001 + (last_digit_of_id * 0.0001)
optimizer = optim.Adam(model.parameters(),
lr=learning_rate)
# Number of epochs based on QMUL ID
num_epochs = 10 + last_digit_of_id
print(f"Training for {num_epochs} epochs with learningrate {learning_rate}.")
# Training loop
train_losses = []
train_accuracies = []
val_accuracies = []
for epoch in range(num_epochs):
    model.train()
    running_loss = 0.0
    correct = 0
    total = 0
    for inputs, labels in train_loader:
        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
        running_loss += loss.item()
        _, predicted = torch.max(outputs, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()
        
    train_accuracy = 100 * correct / total
    print(f"Epoch {epoch+1}/{num_epochs}, Loss:{running_loss:.4f}, Training Accuracy:{train_accuracy:.2f}%")
    # Validation step
    model.eval()
    correct = 0
    total = 0
    with torch.no_grad():
        for inputs, labels in val_loader:
            outputs = model(inputs)
            _, predicted = torch.max(outputs, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
    val_accuracy = 100 * correct / total
    print(f"Validation Accuracy after Epoch {epoch + 1}:{val_accuracy:.2f}%")
    train_losses.append(running_loss)
    train_accuracies.append(train_accuracy)
    val_accuracies.append(val_accuracy)
    import matplotlib.pyplot as plt
# Plot Loss
plt.figure()
plt.plot(range(1, num_epochs + 1), train_losses,
label="Training Loss")
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.title("Training Loss")
plt.legend()
plt.show()
# Plot Accuracy
plt.figure()
plt.plot(range(1, num_epochs + 1), train_accuracies,
label="Training Accuracy")
plt.plot(range(1, num_epochs + 1), val_accuracies,
label="Validation Accuracy")
plt.xlabel("Epochs")
plt.ylabel("Accuracy")
plt.title("Training and Validation Accuracy")
plt.legend()
plt.show()