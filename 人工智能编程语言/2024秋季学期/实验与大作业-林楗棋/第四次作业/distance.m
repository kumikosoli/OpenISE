function dist = distance(dot1, dot2)
    dist = sqrt(sum((dot1 - dot2).^2));
end