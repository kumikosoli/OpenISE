import encode, random

def mutation(binary):
    """
    对二进制字符串进行随机突变，随机选择一个位置进行0和1的互换。由于随机性，结果可能不同，所以没有doctest示例。
    """
    place = random.randint(0, len(binary) - 1)  # 随机选择一个位置
    return mutation_helper(binary, place)  # 调用辅助函数进行突变操作

def mutation_helper(binary, place):
    """
    在二进制字符串的指定位置进行突变（0变1或1变0），此函数用于辅助随机突变操作。
    >>> mutation_helper('0000000000000000', 6)
    '0000001000000000'
    >>> mutation_helper('1111111111111111', 6)
    '1111110111111111'
    """
    place = int(place)
    binary = list(binary)  # 将字符串转换为列表以便修改
    binary[place] = '1' if binary[place] == '0' else '0'
    return "".join(binary)  # 将列表转换回字符串


if __name__ == "__main__":
    import doctest
    doctest.testmod(verbose=True) 