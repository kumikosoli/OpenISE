def switch(bin1, bin2, place):
    """
    在两个十六进制字符串的指定位置个字符后进行交换
    >>> switch('0011110000000000', '0011110000000001', 6)
    ('0011110000000001', '0011110000000000')
    >>> switch('1111111111111111', '0000000000000000', 6)
    ('1111110000000000', '0000001111111111')
    """
    place = int(place)
    bin1_re = bin1[:place] + bin2[place:]  # 替换bin1的指定位置
    bin2_re = bin2[:place] + bin1[place:]  # 替换bin2的指定位置
    return bin1_re, bin2_re


if __name__ == "__main__":
    import doctest
    doctest.testmod(verbose=True) 