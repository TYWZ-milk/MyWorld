function [ output_args ] = DrawInputTree_radius( trunk, move_vec )
%DRAWINPUTTREE Summary of this function goes here
%   Detailed explanation goes here
% trunk.point
point_num = numel(trunk.point);
point_x = [];
point_y = [];
point_z = [];

move_vec = [0, 0, 0];

for k = 1 : point_num-1
    X1 = [trunk.point(k+1).x+ move_vec(1), trunk.point(k+1).y+ move_vec(2), trunk.point(k+1).z+ move_vec(3)];
    X2 = [trunk.point(k).x+ move_vec(1),   trunk.point(k).y+ move_vec(2),   trunk.point(k).z+ move_vec(3)];
    r =  [trunk.point(k+1).r, trunk.point(k).r];

    nn = 5;
    cyl_color = 'b';
    closed = 0;
    Draw_Cone(X1, X2, r, nn, cyl_color, closed, 1);
    hold on;
end

%%%
child_num  = length(trunk.bifurcation);
if child_num ==0
    return;
end

for i=1: child_num
    
    % 画以trunk的孩子枝干为主干的树
    DrawInputTree_radius(trunk.children{i}, move_vec);    
    hold on;
end

end

