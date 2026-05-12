from datasets import load_dataset
import numpy as np


ds = load_dataset("ylecun/mnist")
train_ds = ds["train"]
test_ds = ds["test"]

train_images = np.array([np.array(x).flatten() for x in train_ds["image"]], dtype=np.float32) / 255.0
test_images  = np.array([np.array(x).flatten() for x in test_ds["image"]], dtype=np.float32) / 255.0
train_labels = np.array(train_ds["label"], dtype=np.float32)
test_labels  = np.array(test_ds["label"], dtype=np.float32)

train_images.tofile("train_images.mat")
train_labels.tofile("train_labels.mat")
test_images.tofile("test_images.mat")
test_labels.tofile("test_labels.mat")

print(train_images.shape)
print(train_labels.shape)
print(test_images.shape)
print(test_labels.shape)



