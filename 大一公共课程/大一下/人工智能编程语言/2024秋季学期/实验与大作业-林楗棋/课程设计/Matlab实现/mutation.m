function out = mutation(binary, place)
% 在二进制字符串的指定位置进行突变（0变1或1变0），此函数用于辅助随机突变操作。
    val = place + 1; % 适配Python的索引规则    
    % 按位翻转
    if binary(val) == '0'
        binary(val) = '1';
    else
        binary(val) = '0';
    end

    out = binary;
end
