function [ trunk ] = calcu_texture_coord( trunk )

circle_num = numel(trunk.circles);
for i=1: circle_num
    for j=1: 11
    uv_coord{i}(j, :) = [1/10*(j-1), 1/(circle_num-1)*(i-1)];
    end
end

trunk.uv_coord = uv_coord;
end

