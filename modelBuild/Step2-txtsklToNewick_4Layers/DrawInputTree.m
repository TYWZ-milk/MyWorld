function [ output_args ] = DrawInputTree( trunk )
%DRAWINPUTTREE Summary of this function goes here
%   Detailed explanation goes here
trunk.point
point_num = numel(trunk.point);
point_x = [];
point_y = [];
point_z = [];

for k = 1: point_num
    point_x = [point_x, trunk.point(k).x];
    point_y = [point_y, trunk.point(k).y];
    point_z = [point_z, trunk.point(k).z];
end

line_handle = plot3(point_x, point_y, point_z, 'b', 'LineWidth', 3); 
set(line_handle, 'linesmoothing', 'on');
hold on;

% %%%
% child_num  = length(trunk.bifurcation);
% if child_num ==0
%     return;
% end

child_num  = length(trunk.bifurcation);
if isempty(trunk.bifurcation) ==1
    return;
end


% if isempty(child_inds) == 1
%     return;
% end

for i=1: numel(trunk.children)
    
    % 画以trunk的孩子枝干为主干的树
    DrawInputTree(trunk.children{i});    
    hold on;
end

end

