function [ edges ] = makeBranchesTight( edges, pointers, root, leafNum )
%MAKEBRANCHESTIGHT Summary of this function goes here
%   Detailed explanation goes here
global re_count;
re_count = re_count+2;

% if root == 499
% X = edges{root}(:, 1);
% Y = edges{root}(:, 2);
% Z = edges{root}(:, 3);
% 
% plot3(X, Y, Z, 'k'); hold on;
% % text(X(end), Y(end), Z(end), [num2str(i)]); 
% pause(0.05);
% hold on;
% end

% if root == 372
%     a=1;
%     b=1;
% end

c1 = pointers(root-leafNum, 1);
c2 = pointers(root-leafNum, 2);
clear m_vec1 m_vec2
m_vec1 = edges{root}(5,1:4) - edges{c1}(1, 1:4);
m_vec2 = edges{root}(5,1:4) - edges{c2}(1, 1:4);


edges{c1}(:, 1) = edges{c1}(:, 1) + ones(5,1)*m_vec1(1);
edges{c1}(:, 2) = edges{c1}(:, 2) + ones(5,1)*m_vec1(2);
edges{c1}(:, 3) = edges{c1}(:, 3) + ones(5,1)* m_vec1(3);
% edges{c1}(1, 4) = edges{c1}(1, 4)+ m_vec1(4);



edges{c2}(: ,1) = edges{c2}(:, 1) + ones(5,1)*m_vec2(1);
edges{c2}(: ,2) = edges{c2}(:, 2) + ones(5,1)*m_vec2(2);
edges{c2}(: ,3) = edges{c2}(:, 3) + ones(5,1)* m_vec2(3);
% edges{c2}(1 ,4) = edges{c2}(1, 4)+ m_vec2(4);



% if c1<=leafNum & c2<= leafNum
%     return
% elseif c1> leafNum
%     edges = makeBranchesTight(edges, pointers, c1, leafNum);
% elseif c2> leafNum
%     edges = makeBranchesTight(edges, pointers, c2, leafNum);
% end

if c1<=leafNum & c2<=leafNum
    return;
end

if c1>leafNum
    edges = makeBranchesTight(edges, pointers, c1, leafNum);
end

if c2> leafNum
    edges = makeBranchesTight(edges, pointers, c2, leafNum); 
end






end

