
# 创建一个{0: 1, 1: 0, 2: 3, 3: 2, 4: 5, 5: 4, 6: 7, 7: 6, 8: 9, 9: 8}这样的字典

def generate_dict(n) -> dict:
    verse_channel_dict = {}
    for i in range(0, n, 2):
        verse_channel_dict[i] = i + 1
        verse_channel_dict[i + 1] = i
    return verse_channel_dict

# # 示例：生成一个大小为 10 的字典
# n = 10
# expanded_dict = generate_dict(n)
# print(expanded_dict)

# 获取list中重复元素的全部索引
def duplicate_value_all_index_in_list(value: any, list_: list) -> list:
    duplicate_value_index = [i for i, x in enumerate(list_) if x == value]
    return duplicate_value_index

# 去重函数,主要用于channel的去重
def list_deduplicate(list_: list) ->list:
    list_ = list(dict.fromkeys(list_))
    return list_
