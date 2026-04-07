function val = encode(binary_data)
    % 半精度浮点数解码函数
    if startsWith(binary_data, '0x')
        binary_data = hex2bin(binary_data);
    end

    binary_data = char(binary_data); % 保证是字符数组
    sign = str2double(binary_data(1)); % 符号位
    exponent = binary_data(2:6); % 指数位
    fraction = binary_data(7:end); % 尾数位

    integer_part = 1;

    if all(exponent == '1') % 如果指数全为1
        val = Inf * (-1)^sign;
        return;
    elseif all(exponent == '0') % 如果指数全为0
        exp = -14;
        integer_part = 0;
    else % 正常情况
        exp = bin2dec(exponent) - 15;
    end

    fraction_value = bin2dec(fraction) / (2^10);
    val = (-1)^sign * (integer_part + fraction_value) * (2^exp);
end

function bin = hex2bin(hex_string)
    % 将十六进制字符串转换为二进制字符串
    if ~startsWith(hex_string, '0x') % 检查是否以'0x'开头
        error("Hexadecimal string must start with '0x'");
    end
    bin = '';
    for i = 3:length(hex_string)
        char_bin = look_up_table(hex_string(i)); % 使用查找表转换每个十六进制字符
        bin = [bin char_bin];
    end
end

function dec = bin2dec(binary_string)
    % 将二进制字符串转换为十进制整数
    dec = 0;
    n = length(binary_string);
    for i = 1:n
        c = binary_string(i);
        if ~ismember(c, ['0', '1'])
            error("Invalid binary character: %s", c);
        end
        dec = dec + str2double(c) * 2^(n - i);
    end
end

function bin = look_up_table(hex_char)
    % 十六进制转二进制查找表
    bin_table = {
        '0000','0001','0010','0011','0100','0101','0110','0111', ...
        '1000','1001','1010','1011','1100','1101','1110','1111'};
    hex_char = upper(hex_char);
    bin = bin_table{hex2dec(hex_char) + 1};
end


