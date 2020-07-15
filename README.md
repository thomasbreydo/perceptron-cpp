# perceptron

This is a mini-project in which I create a perceptron from scratch in C++.

# What is a perceptron?

# How does a perceptron work?

## Learning rate

# Example usage

First, the program asks us how many samples (points) we would like to define, as well as their dimensionality.
In this case, we are using 2D points on a simple Cartesian plane.
```
How many samples? 6   
How many dimensions? 2
```
The program then asks for the locations of our points.
(Note, `x_0` corresponds to the x-axis, `x_1` corresponds to the y-axis.)

The program also asks for the `is_type_A` value of each sample. In this
example, `is_type_A` means "is a blue point", `0` means no, `1` means yes.
```
Sample 0
x_0: -2
x_1: 1.75
is_type_A: 1  
...
Sample 5
x_0: 0.25
x_1: 1.75
is_type_A: 0
```
At this point, the perceptron is ready to train. The program asks for a learning rate
and a number of epochs.
```
What is the learning rate? 0.1
How many epochs? 200
Before training: Perceptron(weights: {1.00, 1.00}, bias: 0.00, lr: 0.10)
>After training: Perceptron(weights: {-0.30, 0.02}, bias: -0.20, lr: 0.10)
Predicted 1 for Sample({-2.00, 1.75}, is_type_A: 1) ✓
Predicted 1 for Sample({-1.25, 0.25}, is_type_A: 1) ✓
Predicted 1 for Sample({-1.75, -0.50}, is_type_A: 1) ✓
Predicted 0 for Sample({1.00, 2.00}, is_type_A: 0) ✓
Predicted 0 for Sample({0.75, 0.75}, is_type_A: 0) ✓
Predicted 0 for Sample({0.25, 1.75}, is_type_A: 0) ✓
```