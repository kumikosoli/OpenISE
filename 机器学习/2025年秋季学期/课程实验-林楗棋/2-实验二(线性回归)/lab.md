# 实验2实验报告
## 读取文件

先读取数据文件：

```csv
x,y
0.360704666,5.555215392
1.544153456,9.890947992
···
```

参考[Pandas官方文档](https://pandas.pydata.org/docs/reference/api/pandas.read_csv.html)将`csv`文件转为Dataframe，以及使用jupyter notebook内置的操作`?pd.read_csv`来查看函数形参。

```python
Signature:
pd.read_csv(
    filepath_or_buffer: 'FilePath | ReadCsvBuffer[bytes] | ReadCsvBuffer[str]',
    *,
    sep: 'str | None | lib.NoDefault' = <no_default>,
    delimiter: 'str | None | lib.NoDefault' = None,
    header: "int | Sequence[int] | None | Literal['infer']" = 'infer',
    names: 'Sequence[Hashable] | None | lib.NoDefault' = <no_default>,
    index_col: 'IndexLabel | Literal[False] | None' = None,
    usecols: 'UsecolsArgType' = None,
    dtype: 'DtypeArg | None' = None,
    engine: 'CSVEngine | None' = None,
    converters: 'Mapping[Hashable, Callable] | None' = None,
    true_values: 'list | None' = None,
    false_values: 'list | None' = None,
    skipinitialspace: 'bool' = False,
    skiprows: 'list[int] | int | Callable[[Hashable], bool] | None' = None,
    skipfooter: 'int' = 0,
    nrows: 'int | None' = None,
    na_values: 'Hashable | Iterable[Hashable] | Mapping[Hashable, Iterable[Hashable]] | None' = None,
    keep_default_na: 'bool' = True,
    na_filter: 'bool' = True,
    verbose: 'bool | lib.NoDefault' = <no_default>,
    skip_blank_lines: 'bool' = True,
    parse_dates: 'bool | Sequence[Hashable] | None' = None,
```

可以得到：

```Python
file1 = pd.read_csv('train.csv')
df_train = pd.DataFrame(file1)
#读取数据集
#使用函数 pd.read_csv

arr_train = np.array(df_train)
#转化成numpy矩阵
#使用函数 np.array

arr_train
```

结果为：

```
array([[3.60704666e-01, 5.55521539e+00],
       [1.54415346e+00, 9.89094799e+00],
       [2.76704060e+00, 1.39110967e+01],
       [8.16535136e-01, 7.83505417e+00],
       [2.72319697e-01, 5.92490921e+00],
       ...
       [1.50141244e+00, 1.02462963e+01],
       [1.45271758e+00, 9.59420048e+00]])
```

可以发现正常显示，前面一列为x，后面一列为y，读取文件步骤完成。

## 优化参数

### 方法一

将$l(w,b)$分别对$w$和$b$求导，得到
$$
\frac{\partial l(w,b)}{\partial w}=w\sum_{i=1}^m x_i^2 -\sum_{i=1}^m (y_i-b)x_i,
$$
$$
\frac{\partial l(w,b)}{\partial b}=mb -\sum_{i=1}^m (y_i-wx_i),
$$
令上述两式为零即可得到$w$和$b$的解析解：
$$
w=\frac{\sum_{i=1}^m y_i (x_i-\bar{x})}{\sum_{i=1}^m x_i^2-\frac{1}{m}(\sum_{i=1}^m x_i)^2},
$$
$$
b=\frac{1}{m}\sum_{i=1}^m(y_i-wx_i),
$$
其中$\bar{x}=\frac{1}{m}\sum_{i=1}^m x_i$为$x$的均值。

要求使用`np.sum()`函数进行求和，同理，使用`?np.sum`查看此函数签名：

```Python
Signature:      
np.sum(
    a,
    axis=None,
    dtype=None,
    out=None,
    keepdims=<no value>,
    initial=<no value>,
    where=<no value>,
)
Call signature:  np.sum(*args, **kwargs)
Type:            _ArrayFunctionDispatcher
String form:     <function sum at 0x7fcbf4109d00>
File:            ~/miniconda3/lib/python3.13/site-packages/numpy/_core/fromnumeric.py
Docstring:      
Sum of array elements over a given axis.
```

可以发现此函数可以选择哪个维度进行求和，`axis=0`表示在行上进行求和，反之`axis=1`表示在列上求和，我们要运用`axis=1`对列进行求和求平均。具体代码如下：

```python
#使用函数 np.sum
# 需要求yi * (xi-x_mean)， xi^2, x_mean
arr_square = arr_train[:, 0] ** 2 # xi^2
x_mean = np.mean(arr_train, axis=0)[0] # x的均值
arr_numerator = arr_train[:, 1] * (arr_train[:, 0] - x_mean) # yi * (xi - x_mean)， 分子
omega = np.sum(arr_numerator) / (np.sum(arr_square) - np.sum(arr_train, axis = 0)[0] ** 2 / arr_train.shape[0] )# w
mean_dis = arr_train[:, 1] - omega * arr_train[:, 0] # 平均偏移量 b
b = np.sum(mean_dis) / arr_train.shape[0] # b
print(omega, b)
```

具体思路是把需要用到的数据建立一个新的array来储存，并在原始数据的基础上获得，实践中遇到以下几点要注意：

- np对矩阵求切片是先行后列，对列求切片需要用[:, 1]中的冒号表示全取所有行
- 可以用`arr_train.shape[0]`来对实例求维度，0表示行数，1表示列数

最后得到的结果是：

```
3.041478869915313 4.906073659305301
```

### 方法二.梯度下降法

手动实现梯度下降法(不使用机器学习框架，如PyTorch、TensorFlow等)来进行模型的训练。算法步骤如下：

1. 初始化模型参数$w$和$b$的值；

2. 在负梯度的方向上更新参数(批量梯度下降、小批量随机梯度下降或者随机梯度下降均可)，并不断迭代这一步骤，更新公式(以小批量随机梯度下降为例)可以写成：
    $$
    w\gets w-\frac{\eta}{\left|B\right|}\sum_{i\in{B}}x^{(i)}(wx^{(i)}+b-y^{(i)}),
    $$

    和
    $$
    b\gets b-\frac{\eta}{\left|B\right|}\sum_{i\in{B}}(wx^{(i)}+b-y^{(i)})
    $$
    其中$\eta$表示学习率,$B$表示每次迭代中随机抽样的小批量，$\left|B\right|$则表示$B$中的样本数量。

3. 终止条件为迭代次数达到某一上限或者参数更新的幅度小于某个阈值。

```Py
# Your code here
#使用 for循环，函数 np.sum等
l_rate = 0.1
n_iter = 1000
data_size = arr_train.shape[0]
omega = 0
b = 0
for i in range(n_iter):
    omega = omega -  np.sum(arr_train[:, 0] * (arr_train[:, 0] * omega + b - arr_train[:, 1]), axis = 0) * l_rate / data_size
    b = b - np.sum(arr_train[:, 0] * omega + b - arr_train[:, 1]) * l_rate / data_size
print(omega, b)
```

结果为：

```
3.0414788704009217 4.906073658410542
```

### 方法三

用矩阵表示，假设数据集有$m$个样本，特征有$n$维。$X=\left[ \begin{matrix} x_{11} & x_{12} & \cdots & x_{1n} & 1 \\
                         x_{21} & x_{22} & \cdots & x_{2n} & 1 \\
                         \vdots & \vdots &      & \vdots & \vdots \\
                         x_{m1} & x_{m2} & \cdots & x_{mn} & 1 \end{matrix} \right]$,        实际标签$Y=\left[ \begin{matrix} y_{1} \\
                         y_{2} \\
                         \vdots \\
                         y_{m}\end{matrix} \right]$, 参数$B=\left[ \begin{matrix} w_{1} \\
                         w_{2} \\
                         \vdots \\
                         w_{n} \\
                         b\end{matrix} \right]$，则解析解为$B^*=(X^T X)^{-1}X^T Y$。推导过程可参考[这篇文章](https://zhuanlan.zhihu.com/p/74157986)。

代码如下：

```Py
#使用函数 np.c_ np.ones np.linalg.inv
# 此数据集有160个样本, 特征有1维
X = np.hstack((arr_train[:, 0].reshape(-1,1), np.ones((arr_train.shape[0], 1))))
Y = arr_train[:, 1]
w = np.linalg.inv(X.T @ X) @ X.T @ Y
print(w)
```

此处需注意：

- `np.hstack`和`np.ones`都需传入一个元组
- `arr_train[:, 0]`是一个一维数组，形状是(m,)，而`np.ones((arr_train.shape[0], 1))`则是个二位矩阵，只是它只有一列。虽然两个数组都只有一列，但是只有矩阵才能通过`np.hstack`进行拼接。

算出来的结果是：

```
[3.04147887 4.90607366]
```

