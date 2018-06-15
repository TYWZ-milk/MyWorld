function [ T ] = add_zero_branch_4_Layers_multi( T )
%ADD_ZERO_BRANCH_4LAYERS Summary of this function goes here
%   Detailed explanation goes here

[T] = add_zero_branch_multi(T);

child_num = numel(T{1}.children);

for i=1: child_num
    clear T_children
    for j = 1: numel(T)
        T_children{j} = T{j}.children{i};
    end
    
    T_children = add_zero_branch_multi(T_children);
    for j=1: numel(T)
        T{j}.children{i} = T_children{j};
    end;
end

