function [out1, out2] = cross(bin1, bin2, place)
% CROSS_BIN 在两个二进制字符串的指定位置后进行交叉（cross）
    place = floor(place);
    out1 = [ bin1(1:place), bin2(place + 1:end) ]; % 替换bin1的指定位置
    out2 = [ bin2(1:place), bin1(place + 1:end) ]; % 替换bin2的指定位置
end
