import math

def hex2bin(hex_string):
    """
    将十六进制字符串转换为二进制字符串
    >>> hex2bin('0x1A')
    '00011010'
    >>> hex2bin('0xFF')
    '11111111'
    >>> hex2bin('0x00')
    '00000000'
    >>> hex2bin('0xFFFF')
    '1111111111111111'
    """
    if hex_string[0:2] != '0x': # 检查是否以'0x'开头
        raise ValueError("Hexadecimal string must start with '0x'")
    bin = ''
    for char in hex_string[2:]:
        if char not in '0123456789ABCDEFabcdef':
            raise ValueError("Invalid hexadecimal character: {}".format(char))
        bin += look_up_table(char) # 使用查找表转换每个十六进制字符
    return bin.strip()
    
def bin2dec(binary_string): 
    """
    将二进制字符串转换为十进制整数
    >>> bin2dec('00011010')
    26
    >>> bin2dec('11111111')
    255
    >>> bin2dec('00000000')
    0
    >>> bin2dec('1111111111111111')
    65535
    """
    dec = 0
    for i in range(len(binary_string)):
        if binary_string[i] not in '01':
            raise ValueError(f"Invalid binary character: {binary_string[i]}")
        else:
            dec += int(binary_string[i]) * (2 ** (len(binary_string) - 1 - i))
    return dec
    
def look_up_table(hex):
    """
    十六进制转二进制查找表
    >>> look_up_table('0')
    '0000'
    >>> look_up_table('F')
    '1111'
    """
    hex.upper()
    bin = ['0000', '0001', '0010', '0011', '0100', '0101', '0110', '0111', '1000', '1001', 
           '1010', '1011', '1100', '1101', '1110', '1111']
    return bin[int(hex, 16)]


def encode(binary_data):
    """
    半精度浮点数解码函数
    将二进制字符串或十六进制字符串转换为半精度浮点数
    >>> encode('0000000000000000')
    0.0
    >>> encode('0x0001')
    5.960464477539063e-08
    >>> encode('0x3c00')
    1.0
    >>> encode('0x7bff')
    65504.0
    >>> encode('0x3c01')
    1.0009765625
    >>> encode('0x3555')
    0.333251953125
    >>> encode('0xc000')
    -2.0
    >>> encode('0x7c00')
    inf
    """
    binary_data = str(binary_data)
    if binary_data[0:2] == '0x':
        binary_data = hex2bin(binary_data)
    sign = int(binary_data[0]) # 符号位
    exponent = binary_data[1:6] # 指数位
    fraction = binary_data[6:] # 尾数位
    integer_part = 1
    if not '0' in exponent: # 如果指数位全为1
        return math.inf * (-1 if sign else 1)
    if not '1' in exponent: # 如果指数位全为0
        exp = -14
        integer_part = 0
    else: # 正常情况
        exp = bin2dec(exponent) - 15
    fraction_value = bin2dec(fraction) / (2 ** 10)
    return (-1 if sign else 1) * (integer_part + fraction_value) * (2 ** exp)


if __name__ == "__main__":
    import doctest
    doctest.testmod(verbose=True) 