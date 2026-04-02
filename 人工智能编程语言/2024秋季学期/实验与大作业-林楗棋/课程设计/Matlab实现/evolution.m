function evolution(generations_to_evlove, cross_posibility, mutation_posibility, population_size, cross_expectation)
% 进化算法主函数，直接打印每代 min/avg，不写 JSON
    population = generate_population(population_size); % 种群初始化
    n = numel(population);
    func_values = zeros(1, n);
    for i = 1:n
        func_values(i) = evaluate_individual(population{i});
    end
    fprintf("Generation %d: min = %.6f, avg = %.6f\n", ...
            0, min(func_values), mean(func_values));

    for gen = 1:generations_to_evlove
        while numel(population) < cross_expectation
            population = cross_population(cross_posibility, population); 
        end
        population = population(1:cross_expectation);
        population = mutation_population(mutation_posibility, population); 
        population = select_population(population, population_size); 
        n = numel(population);
        func_values = zeros(1, n);
        for i = 1:n
            func_values(i) = evaluate_individual(population{i});
        end
        fprintf("Generation %d: min = %.6f, avg = %.6f\n", ...
                gen, min(func_values), mean(func_values));
    end
end

function population = generate_population(size)
% 生成指定大小的种群，每个个体由1位符号位，5位指数和10位尾数组成，共16位二进制字符串
    population = cell(1, size);
    for i = 1:size
        population{i} = generate_individual();
    end
end

function individual = generate_individual()
% 指数位在01111和10000中随机选择，同时在尾数位中随机生成 0 和 1 
    choices  = ['01111'; '10000'];
    exponent = choices( randi(2), : );
    fraction = num2str( randi([0,1],1,10), '%1d' );
    individual = ['0' exponent fraction];
end

function population = cross_population(posibility, population)
%     随机两两选取种群中的个体进行交换，并有posibility的概率进行交换
%     产生的新个体加入种群中
    population = population(randperm(numel(population)));  % 随机打乱顺序
    for i = 1:2:numel(population)-1
        if rand < posibility
            a = population{i};
            b = population{i+1};
            point = randi([6,15]);  
            [c1, c2] = cross(a, b, point);
            population(end+1:end+2) = {c1, c2};
        end
    end
end

function population = mutation_population(posibility, population)
%   对种群中的个体进行突变操作，每个个体都有posibility的概率进行突变，突变于尾数位进行
    for i = 1:numel(population)
        if rand < posibility
            place = randi([6,15]);
            population{i} = mutation(population{i}, place);
        end
    end
end

function value = evaluate_individual(binary)
% 将个体的大小代入y = (x - 3)^2 并返回数值
    x = encode(binary);
    value = (x - 3)^2;
end

function population = select_population(population, size)
% 从种群中选择函数值较小的个体，保留到新的种群中
    N = numel(population);
    func = zeros(1, N);
    for i = 1:N
        func(i) = evaluate_individual(population{i});
    end
    [~, order] = sort(func);
    population = population(order(1:size));
end