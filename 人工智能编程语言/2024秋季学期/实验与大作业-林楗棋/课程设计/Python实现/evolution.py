import encode, switch, mutation, random, json, os

def generate_individual():
    """
    指数位在01111和10000中随机选择，同时在尾数位中随机生成 0 和 1    
    """
    exponent = random.choice(['01111', '10000'])  # 随机选择指数位
    mantissa = ''.join(random.choice(['0', '1']) for _ in range(10))  # 随机生成10位尾数
    return "0" + exponent + mantissa  # 返回完整的二进制字符串表示个体

def generate_population(size):
    """
    生成指定大小的种群，每个个体由1位符号位，5位指数和10位尾数组成，共16位二进制字符串
    """
    return [generate_individual() for _ in range(size)]  # 返回指定大小的种群列表

def switch_population(posibility, population):
    """
    随机两两选取种群中的个体进行交换，并有posibility的概率进行交换
    产生的新个体加入种群中
    """
    random.shuffle(population)  # 打乱种群顺序
    for i in range(0, len(population), 2):
        if random.random() < posibility and i + 1 < len(population):
            population += list(switch.switch(population[i], population[i + 1], random.randint(6, 15)))  # 随机位置交换两个个体并加入种群、
    return population  # 返回更新后的种群

def mutation_population(posibility, population):
    """
    对种群中的个体进行突变操作，每个个体都有posibility的概率进行突变，突变于尾数位进行
    """
    for i in range(len(population)):
        if random.random() < posibility:
            population[i] = mutation.mutation_helper(population[i], random.randint(6, 15))  # 随机位置突变个体的尾数位
    return population  # 返回更新后的种群

def evaluate_individual(binary):
    """
    将个体的大小代入y = (x - 3)^2 并返回数值
    """    
    x = encode.encode(binary)  # 将二进制字符串转换为半精度浮点数
    return (x - 3) ** 2  # 返回函数值

def select_population(population, size):
    """
    从种群中选择函数值较小的个体，保留到新的种群中
    """
    sorted_pop = sorted(population, key=lambda val: evaluate_individual(val))   # 按照 evaluate_individual 计算的 (x-3)^2 值升序排列
    return sorted_pop[:size]  # 返回前 size 个二进制字符串

def save_population(population, filename, generation):
    """
    将种群的函数值的最小值和平均值保存到json文件中，方便后续分析
    """
    repository = 'population_data'  # 数据存储在一个名为 population_data 的文件夹中
    os.makedirs(repository, exist_ok=True)
    file_path = os.path.join(repository, f"{filename}.json")  # 文件路径
    fitness_values = [evaluate_individual(ind) for ind in population]  # 计算每个个体的函数值
    min_value = min(fitness_values)  # 最小函数值
    avg_value = sum(fitness_values) / len(fitness_values)  # 平均函数值
        
    if os.path.exists(file_path): # 如果文件已存在，就读取已有数据；否则初始化新结构
        with open(file_path, "r", encoding="utf-8") as f:
            try:
                data = json.load(f)
            except json.JSONDecodeError:
                data = {"generations": []}
    else:
        data = {"generations": []}
    
    record = {
        "generation": generation,
        "min_value": float(min_value),
        "avg_value": float(avg_value)
    }

    data.setdefault("generations", []).append(record) # 将本代结果追加到 "generations" 列表

    with open(file_path, "w", encoding="utf-8") as f: # 写回 JSON 文件（覆盖原文件）
        json.dump(data, f, indent=2, ensure_ascii=False)


def evolution(generations_to_evlove, switch_posibility, mutation_posibility, population_size, switch_expectation, generation_filename):
    """
    进化算法主函数，生成初始种群并进行多代进化
    1. 种群初始化，随机(或按照一定的先验信息)生成具有P0(@population_size)个个体的初始种群；
    2. 以概率pc(@switch_posibility)基于初始种群进行交叉操作，得到一些新个体加入种群中，使之规模达到P(@switch_expectation)；
    3. 以概率pm(@mutation_posibility)在种群中执行变异操作，小范围调节个体的基因(即个体的编码)；
    4. 选择操作，从种群中选择一些较优个体，保留进入下一代规模为P0种群；
    5. 终止条件判断，若达到预定进化代数Gen(@generations_to_evlove)，输出当前最优个体，否则回到步骤2)；
    """
    population = generate_population(population_size)  # 生成初始种群
    save_population(population, generation_filename, 0)  # 保存初始种群数据
    for gen in range(generations_to_evlove):
        while len(population) < switch_expectation:  # 确保种群大小达到期望值
            population = switch_population(switch_posibility, population)  # 随机交换种群中的个体
        population = population[:switch_expectation]  # 截断种群到期望大小
        population = mutation_population(mutation_posibility, population) # 对种群进行突变操作
        population = select_population(population, population_size) # 选择函数值较小的个体进入下一代
        save_population(population, generation_filename, gen + 1)  # 保存当前代的种群数据
    
if __name__ == "__main__":
    """
    运行进化算法，参数可以根据需要调整
    """
    evolution(
        generations_to_evlove = 10,
        switch_posibility = 0.6,
        mutation_posibility = 0.2,
        population_size = 10,  
        switch_expectation = 15,  
        generation_filename = "g0" 
    )
    evolution(
        generations_to_evlove = 20,
        switch_posibility = 0.6,
        mutation_posibility = 0.2,
        population_size = 10,  
        switch_expectation = 15,  
        generation_filename = "g1" 
    )
    evolution(
        generations_to_evlove = 20,
        switch_posibility = 0.2,
        mutation_posibility = 0.2,
        population_size = 10,  
        switch_expectation = 15,  
        generation_filename = "g2" 
    )
    evolution(
        generations_to_evlove = 20,
        switch_posibility = 0.6,
        mutation_posibility = 0.2,
        population_size = 20,  
        switch_expectation = 30,  
        generation_filename = "g3" 
    )
    evolution(
        generations_to_evlove = 20,
        switch_posibility = 0.6,
        mutation_posibility = 0.2,
        population_size = 5,  
        switch_expectation = 7,  
        generation_filename = "g4" 
    )